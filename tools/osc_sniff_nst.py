#!/usr/bin/env python3
import json
import os
import socket
import struct
import time
from collections import defaultdict

PORT = int(os.environ.get("OSC_PORT", "12345"))
DURATION = float(os.environ.get("OSC_DURATION", "20"))
OUT = os.environ.get("OSC_OUT", "/tmp/osc_nst.json")
RAW_OUT = os.environ.get("OSC_RAW_OUT", "/tmp/osc_nst_raw.json")


def read_i32(data, i):
    return int.from_bytes(data[i:i + 4], "big", signed=True), i + 4


def read_f32(data, i):
    return float(struct.unpack(">f", data[i:i + 4])[0]), i + 4


def read_padded_str(data, i):
    end = data.find(b"\0", i)
    if end == -1:
        end = len(data)
    value = data[i:end].decode("utf-8", errors="replace")
    i = end + 1
    while i % 4 != 0:
        i += 1
    return value, i


def parse_osc_packet(data):
    addr, i = read_padded_str(data, 0)
    tags, i = read_padded_str(data, i)
    args = []
    if tags.startswith(","):
        for tag in tags[1:]:
            if tag == "i":
                value, i = read_i32(data, i)
                args.append(value)
            elif tag == "f":
                value, i = read_f32(data, i)
                args.append(value)
            elif tag == "s":
                value, i = read_padded_str(data, i)
                args.append(value)
            else:
                break
    return addr.lstrip("/"), args


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("127.0.0.1", PORT))
sock.settimeout(0.25)

start = time.time()
samples = []
while time.time() - start < DURATION:
    try:
        data, _ = sock.recvfrom(65535)
    except socket.timeout:
        continue
    try:
        addr, args = parse_osc_packet(data)
    except Exception:
        continue
    samples.append({"t": round(time.time() - start, 4), "addr": addr, "args": args})

by_addr = defaultdict(list)
for sample in samples:
    by_addr[sample["addr"]].append(sample)

summary = {
    "duration": DURATION,
    "count": len(samples),
    "by_addr": {},
    "samples": samples[:120],
}

for addr, messages in by_addr.items():
    entry = {"count": len(messages)}
    if addr.startswith("NDITracker") and addr not in {"NDITrackerDeath", "NDITrackerMerge"}:
        labels = []
        ages = []
        xs = []
        ys = []
        jumps = []
        prev = None
        for message in messages:
            args = message["args"]
            if len(args) < 6:
                continue
            labels.append(args[0])
            xs.append(float(args[1]))
            ys.append(float(args[2]))
            ages.append(int(args[5]))
            if prev is not None:
                dx = float(args[1]) - prev[0]
                dy = float(args[2]) - prev[1]
                jumps.append((dx * dx + dy * dy) ** 0.5)
            prev = (float(args[1]), float(args[2]))
        if labels:
            entry["labels_seen"] = sorted(set(labels))
            entry["age_min"] = min(ages)
            entry["age_max"] = max(ages)
            entry["x_range"] = [round(min(xs), 4), round(max(xs), 4)]
            entry["y_range"] = [round(min(ys), 4), round(max(ys), 4)]
        if jumps:
            jumps_sorted = sorted(jumps)
            p95 = jumps_sorted[min(len(jumps_sorted) - 1, int(0.95 * len(jumps_sorted)))]
            entry["jump_avg"] = round(sum(jumps) / len(jumps), 5)
            entry["jump_p95"] = round(p95, 5)
            entry["jump_max"] = round(max(jumps), 5)
    summary["by_addr"][addr] = entry

with open(OUT, "w") as f:
    json.dump(summary, f, indent=2)
with open(RAW_OUT, "w") as f:
    json.dump(samples, f)
print(OUT)
