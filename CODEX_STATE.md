# NST Codex State

Last updated: `2026-04-12` (post generic-path live check)

If chat history is missing in a future session, start here.

## Goal

Make `NST1` hold `3` stable tracked IDs through crossovers from the synthetic sender scene, with:

- smooth visible boxes
- smooth OSC
- no long ghost boxes
- no boxes stuck in empty space
- no ID swaps during crossovers

## Apps

- Tracker:
  - `/Users/alastairmcneill/Documents/GitHub/NST/NST1/bin/NST1.app`
- Sender:
  - `/Users/alastairmcneill/Documents/GitHub/NST/NDI-test-sender-3d/bin/NDI-test-sender-3d.app`

## Main Files

- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h`
- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTrackerBase.h`
- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/OscSender.h`
- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/NDISource.h`

## Current Architecture

- YOLO tracked mode is `track-first`, not raw slot-first.
- Internal continuity lives in `yoloTracks`.
- Output slots are assigned in `processYoloTrackedResults(...)`.
- Hidden slot continuity memory is in `yoloSlotMemoryTracks`.
- Visible output and OSC come from selected slots and `retainedOutputTracks`.

## What Was Working Best Recently

Best recent short run:

- `/tmp/osc_trackfirst28.json`
- `/tmp/osc_trackfirst28_raw.json`
- Deaths: `0`
- Resets: `0 / 0 / 0`
- Max gaps:
  - `NDITracker1`: `0.154s`
  - `NDITracker2`: `0.209s`
  - `NDITracker3`: `0.955s`
- All `3` IDs present in `72.6%` of `100ms` windows

Interpretation:

- This was the best recent short crossover run.
- It still was not good enough, but it was materially better than the older unstable runs.

## What Still Fails

- Long `3`-object crossover runs still degrade.
- One slot can still disappear for too long during messy overlap.
- Short runs can look decent while longer stress runs still show long max gaps.

Longer stress run on the same safer line:

- `/tmp/osc_trackfirst29.json`
- `/tmp/osc_trackfirst29_raw.json`
- Deaths: `0`
- Resets: `0 / 0 / 0`
- Max gaps:
  - `NDITracker1`: `6.217s`
  - `NDITracker2`: `3.884s`
  - `NDITracker3`: `1.405s`
- All `3` IDs present in `35.5%` of `100ms` windows

Interpretation:

- Short-run crossover continuity improved.
- Long-run continuity is still not solved.

## Rejected Regression

A stronger `source-track prelock` was tested and rejected.

Bad run:

- `/tmp/osc_trackfirst30.json`
- `/tmp/osc_trackfirst30_raw.json`
- Deaths: `1`
- `NDITracker1` reset and had a `9.022s` max gap
- All `3` IDs present in only `4.0%` of `100ms` windows

Interpretation:

- Hard prelocking the source track made the tracker much worse.
- That change was rolled back immediately.

## Current Code Line

The last attempted architectural cleanup on `2026-04-12` was a regression:

- disabled the sender-specific `three-class scene` tracking mode in
  `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h`
- changed the default `YOLO Class Filter` to empty in
  `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTrackerBase.h`

That generic-path pass was live-validated and was worse:

- `/tmp/osc_generic_20.json`
- `/tmp/osc_generic_20_raw.json`
- only `NDITrackerDeath` packets
- `3` deaths in `20s`
- `0` live tracker packets

Those two changes were then rolled back in source and rebuilt:

- restored `useThreeClassSceneLabeling()` logic in
  `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h`
- restored default `YOLO Class Filter` to `person,car,cat` in
  `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTrackerBase.h`

Fresh live check after that rollback:

- `/tmp/osc_reverted_20.json`
- `/tmp/osc_reverted_20_raw.json`
- still bad: only `NDITrackerDeath` packets
- `2` deaths in `20s`
- `0` live tracker packets

Interpretation:

- the generic cleanup clearly made things worse
- rolling back just those two changes was not enough to restore the older `trackfirst28` quality
- treat `/tmp/osc_trackfirst28_raw.json` as the last genuinely better validated reference point, not the current rebuilt app

## Launch Notes

Do not launch raw GUI binaries in a background shell for live verification.
That previously caused AppKit/GLFW startup crashes.

Use:

- `open -na "/Users/alastairmcneill/Documents/GitHub/NST/NDI-test-sender-3d/bin/NDI-test-sender-3d.app"`
- `open -na "/Users/alastairmcneill/Documents/GitHub/NST/NST1/bin/NST1.app"`

## OSC Capture

Script:

- `/tmp/osc_sniff_nst.py`

Useful recent files:

- `/tmp/osc_trackfirst28.json`
- `/tmp/osc_trackfirst28_raw.json`
- `/tmp/osc_trackfirst29.json`
- `/tmp/osc_trackfirst29_raw.json`
- `/tmp/osc_trackfirst30.json`
- `/tmp/osc_trackfirst30_raw.json`
- `/tmp/osc_generic_20.json`
- `/tmp/osc_generic_20_raw.json`
- `/tmp/osc_reverted_20.json`
- `/tmp/osc_reverted_20_raw.json`

## Practical Next Step

Do not revisit the hard prelock idea.

Before any new crossover tuning, first restore behavior to at least the old `trackfirst28` baseline.

The next pass should stay inside `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h` and focus on:

1. identifying what changed between the old `trackfirst28`-quality line and the current rebuilt app
2. restoring live tracker packet output first
3. only then improving `3`-way crossover recovery
4. validating every change with OSC, not screenshots alone

## 2026-04-12 Restore/Crash Check
- Rebuilt `NST1` after restoring `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/NDISource.h` processing back to `1280x720`.
- Clean GUI-safe relaunch of sender + `NST1` did **not** reproduce a fresh tracking crash.
- Latest visible `.ips` remains the old raw-binary GLFW/AppKit startup abort: `/Users/alastairmcneill/Library/Logs/DiagnosticReports/NST1-2026-04-12-150913.ips`.
- Added temporary debug logging in `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/OscSender.h`, `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/NDISource.h`, and `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h`.
- Important finding: `NST1` is again emitting live value OSC internally; `/tmp/nst1_osc_debug.log` shows thousands of `sendVal` calls with live slots/labels/positions.
- Important caveat: the localhost OSC sniff helper produced misleading results and is not currently trustworthy as the sole validator.
- Current live state is therefore: app stays up, NDI is connected, YOLO selects 1-3 tracks, and internal OSC sends are happening; remaining issue is behavior quality/stability, not a reproduced crash.

## 2026-04-22 NDI Video Restore
- User reported no video showing in the tracker and glitchy FPS after the restore attempts.
- Cause identified: the restore pass changed `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/NDISource.h` to a shallow `cv::Mat` pixel path and still depended too much on one-time startup NDI discovery.
- Restored the NDI update path to copy through `inImg.setFromPixels(pix)` before converting to OpenCV, matching the earlier reliable preview path.
- Changed default NDI source match from `SENDER1` to the actual sender name `NST Motion Test 3D`.
- Added a disconnected-source retry in `NDISource::update()` so NST1 reconnects if discovery misses the sender at startup.
- Rebuilt `/Users/alastairmcneill/Documents/GitHub/NST/NST1/bin/NST1.app` and relaunched sender then NST1.
- Current process evidence after relaunch: sender and NST1 both running; NST1 CPU high enough to indicate active frame/YOLO processing, and UDP sockets open for OSC/NDI.
- This fixes source discovery/preview reliability first; tracker quality is still not declared restored to `trackfirst28` until a separate valid behavior run.

## 2026-04-22 VPN / NDI Discovery Note
- User identified the immediate no-video issue as VPN being enabled.
- Treat VPN as a known NDI failure mode: NDI source discovery/video can fail or appear connected-but-blank when VPN/network filtering is active.
- Before changing tracker/source code for "no video", first verify VPN is off and relaunch sender then NST1.
- Do not misdiagnose VPN-caused NDI failure as a tracker regression.

## 2026-04-22 VPN-Off Restart Baseline
- After VPN was identified as the no-video cause, sender and NST1 were relaunched together.
- Sender process: `/Users/alastairmcneill/Documents/GitHub/NST/NDI-test-sender-3d/bin/NDI-test-sender-3d.app/Contents/MacOS/NDI-test-sender-3d`.
- NST1 process: `/Users/alastairmcneill/Documents/GitHub/NST/NST1/bin/NST1.app/Contents/MacOS/NST1`.
- Logs show sender ready as `NST Motion Test 3D` and NST1 finding/connecting to `MAC (NST Motion Test 3D)` with exact source match.
- NST1 log shows `Loaded YOLO backend: Core ML`.
- OSC capture `/tmp/osc_vpn_off_test.json` recorded `1172` packets in `20s`, proving NDI frames, tracking path, and OSC output are active again.
- Remaining issue is not NDI/video input: tracker quality still needs work because slot labels swap and OSC jumps remain.

## 2026-04-22 Template Tracker / Crash State
- VPN was confirmed as the NDI no-video cause; do not treat VPN-caused blank video as tracker failure.
- Current tracker line in `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h` now combines YOLO slot assignment with a lightweight template tracker fallback using `cv::matchTemplate` when YOLO misses a slot.
- Last completed OSC run before the crash report check: `/tmp/osc_template_smooth_30.json` and `/tmp/osc_template_smooth_30_raw.json`.
- That run produced live OSC for all three slots with stable labels and no gaps:
  - `NDITracker1`: 737 packets, labels `[1]`, gapN `0`, jump_max `0.03752`, jumpN `0`.
  - `NDITracker2`: 746 packets, labels `[2]`, gapN `0`, jump_max `0.08258`, jumpN `8`.
  - `NDITracker3`: 747 packets, labels `[3]`, gapN `0`, jump_max `0.08149`, jumpN `4`.
- Crash report `/Users/alastairmcneill/Library/Logs/DiagnosticReports/NST1-2026-04-22-161946.ips` points at `mtbTracker::updateSlotVisualTracker()` via `cv::Mat(cv::Mat const&, cv::Rect_<int> const&)`, meaning an invalid OpenCV ROI crop in the template-tracker path.
- A guard patch was added immediately after: every template/search/update ROI is clipped to frame bounds and wrapped with catch/fail behavior. Build still needs re-run after that guard patch.
- Current status is **not final-fixed**: no-gap OSC was achieved, but the ROI crash guard must be built and validated, and remaining jumps around `0.08` normalized still need smoothing/verification on live video.

## 2026-04-22 GitHub Large File Issue
- User attempted to commit/push to `master` and GitHub rejected files over `100 MB`.
- Likely causes are YOLO/model/build artifacts such as `.mlmodelc`, `.mlpackage`, `.onnx`, `.pt`, or generated binaries.
- Next step: identify exact tracked/staged files over 100 MB, then either move them to Git LFS or remove them from Git history/index and add ignore rules. Do not blindly delete model files from disk because NST currently depends on local model paths.

## 2026-04-22 GitHub Large File Update
- GitHub Desktop warned about >100MB files inside `NST1/.venv`.
- `.gitignore` now contains `.venv/` and `**/.venv/`, and `git check-ignore` confirms both large `.venv` files are ignored.
- The 188MB sender car OBJ is also ignored by the existing `*/bin` rule.
- No staged files and no tracked files over 95MiB were found at this check.
- If GitHub Desktop still shows the old dialog, cancel it and refresh/retry after the `.gitignore` change is committed.
