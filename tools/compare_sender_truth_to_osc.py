#!/usr/bin/env python3
import argparse
import bisect
import csv
import json
import math
from collections import Counter, defaultdict


def load_truth(path):
    frames = []
    by_time = []
    with open(path, newline="") as f:
        reader = csv.DictReader(f)
        grouped = defaultdict(list)
        for row in reader:
            try:
                wall = float(row["wall_time"])
                grouped[wall].append(
                    {
                        "wall": wall,
                        "index": int(row["index"]),
                        "kind": row["kind"],
                        "x": float(row["x"]),
                        "y": float(row["y"]),
                        "radius": float(row["radius"]),
                        "visible_count": int(row.get("visible_count", "0") or 0),
                    }
                )
            except (KeyError, TypeError, ValueError):
                continue
    for wall in sorted(grouped):
        items = grouped[wall]
        frames.append({"wall": wall, "items": items})
        by_time.append(wall)
    return by_time, frames


def nearest_truth_frame(times, frames, wall, max_dt):
    if not times:
        return None, None
    pos = bisect.bisect_left(times, wall)
    candidates = []
    if pos < len(times):
        candidates.append(pos)
    if pos > 0:
        candidates.append(pos - 1)
    best = None
    best_dt = None
    for idx in candidates:
        dt = abs(times[idx] - wall)
        if best is None or dt < best_dt:
            best = frames[idx]
            best_dt = dt
    if best is None or best_dt is None or best_dt > max_dt:
        return None, None
    return best, best_dt


def nearest_item(items, x, y):
    best = None
    best_dist = None
    for item in items:
        dist = math.hypot(item["x"] - x, item["y"] - y)
        if best is None or dist < best_dist:
            best = item
            best_dist = dist
    return best, best_dist


def percentile(values, pct):
    if not values:
        return None
    ordered = sorted(values)
    idx = min(len(ordered) - 1, int((pct / 100.0) * len(ordered)))
    return ordered[idx]


def main():
    parser = argparse.ArgumentParser(
        description="Compare NST tracker OSC slot positions against synthetic sender ground truth."
    )
    parser.add_argument("--truth", required=True, help="CSV written by NST_SENDER_TRUTH_PATH")
    parser.add_argument("--osc", required=True, help="Raw JSON written by osc_sniff_nst.py")
    parser.add_argument("--out", required=True, help="Summary JSON output path")
    parser.add_argument("--max-dt", type=float, default=0.08, help="Maximum wall-time match in seconds")
    parser.add_argument("--lock-distance", type=float, default=0.08, help="Normalized distance counted as locked")
    args = parser.parse_args()

    truth_times, truth_frames = load_truth(args.truth)
    with open(args.osc) as f:
        osc = json.load(f)

    per_slot = defaultdict(
        lambda: {
            "samples": 0,
            "matched_truth_frames": 0,
            "locked_samples": 0,
            "distances": [],
            "nearest": Counter(),
            "nearest_kind": Counter(),
            "switches": 0,
            "last_nearest": None,
        }
    )

    for message in osc:
        addr = message.get("addr", "")
        if not addr.startswith("NDITracker") or addr in {"NDITrackerDeath", "NDITrackerMerge"}:
            continue
        args_ = message.get("args", [])
        if len(args_) < 3:
            continue
        wall = message.get("wall")
        if wall is None:
            continue
        try:
            slot = int(addr.replace("NDITracker", ""))
            x = float(args_[1])
            y = float(args_[2])
        except ValueError:
            continue

        stats = per_slot[slot]
        stats["samples"] += 1
        frame, dt = nearest_truth_frame(truth_times, truth_frames, float(wall), args.max_dt)
        if frame is None:
            continue
        stats["matched_truth_frames"] += 1
        item, dist = nearest_item(frame["items"], x, y)
        if item is None or dist is None:
            continue
        key = f"{item['kind']}#{item['index']}"
        stats["nearest"][key] += 1
        stats["nearest_kind"][item["kind"]] += 1
        stats["distances"].append(dist)
        if dist <= args.lock_distance:
            stats["locked_samples"] += 1
        if stats["last_nearest"] is not None and stats["last_nearest"] != key:
            stats["switches"] += 1
        stats["last_nearest"] = key

    out = {
        "truth_frames": len(truth_frames),
        "osc_messages": len(osc),
        "max_dt": args.max_dt,
        "lock_distance": args.lock_distance,
        "slots": {},
    }
    for slot in sorted(per_slot):
        stats = per_slot[slot]
        distances = stats["distances"]
        matched = stats["matched_truth_frames"]
        out["slots"][f"NDITracker{slot}"] = {
            "samples": stats["samples"],
            "matched_truth_frames": matched,
            "locked_samples": stats["locked_samples"],
            "locked_ratio": round(stats["locked_samples"] / matched, 4) if matched else 0.0,
            "nearest": dict(stats["nearest"].most_common()),
            "nearest_kind": dict(stats["nearest_kind"].most_common()),
            "switches": stats["switches"],
            "distance_avg": round(sum(distances) / len(distances), 5) if distances else None,
            "distance_p95": round(percentile(distances, 95), 5) if distances else None,
            "distance_max": round(max(distances), 5) if distances else None,
        }

    with open(args.out, "w") as f:
        json.dump(out, f, indent=2)
    print(args.out)


if __name__ == "__main__":
    main()
