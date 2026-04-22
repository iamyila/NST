# NST Handoff - 2026-04-08

## Goal

Make `NST1` keep `3` stable tracked IDs through crossovers from the synthetic sender scene, with:

- smooth visible boxes
- smooth OSC
- no long ghost boxes
- no boxes stuck in empty space
- no ID swaps during crossovers

## Apps

- Tracker app:
  - `/Users/alastairmcneill/Documents/GitHub/NST/NST1/bin/NST1.app`
- Sender app:
  - `/Users/alastairmcneill/Documents/GitHub/NST/NDI-test-sender-3d/bin/NDI-test-sender-3d.app`

## Main Code

- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTracker.h`
- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/mtbTrackerBase.h`
- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/OscSender.h`
- `/Users/alastairmcneill/Documents/GitHub/NST/NST1/src/NDISource.h`

## Current Architecture

- YOLO tracked mode is now track-first, not raw slot-first.
- Internal track continuity lives in `yoloTracks`.
- Output slots are assigned in `processYoloTrackedResults(...)`.
- There is hidden slot memory in `yoloSlotMemoryTracks`.
- Visible output / OSC comes from selected slots and `retainedOutputTracks`.

## What Still Fails

- The system usually holds `2` IDs well.
- The `3rd` object still drops out too often during crossovers.
- Recent change improved slot-3 continuity but caused early deaths on slots 1/2.
- Crossovers can still freeze or briefly disappear instead of smoothly reattaching.

## Recent Measured Runs

### Better older baseline

- `/tmp/osc_trackfirst12_raw.json`
- Deaths: `1`
- Resets:
  - `NDITracker1`: `0`
  - `NDITracker2`: `0`
  - `NDITracker3`: `1`
- About `60%` of `100ms` windows had all `3` IDs

### Current recent runs

- `/tmp/osc_trackfirst21_raw.json`
  - Deaths: `0`
  - Resets: `0 / 0 / 0`
  - But `NDITracker3` had a `4.685s` max gap
  - About `48%` of `100ms` windows had all `3` IDs

- `/tmp/osc_trackfirst22_raw.json`
  - Deaths: `2`
    - slot 2 at `t=4.2038`
    - slot 1 at `t=4.3718`
  - Resets: `0 / 0 / 0`
  - slot 3 improved a lot:
    - `NDITracker3` max gap `0.236s`
  - About `52%` of `100ms` windows had all `3` IDs

Interpretation:

- Relaxing same-source recovery helped the disappearing/freeze problem for slot 3.
- But it destabilized slots 1 and 2 early in the run.

## Suspected Remaining Problem

The crossover failure is still inside the assignment / recovery logic in:

- `processYoloTrackedResults(...)`
- `updateSlotFromTrack(...)`

The likely issue is that:

- source-track recovery is necessary
- but the current recovery rule is too permissive for some slots and too strict for others
- visible output, slot memory, and overlap rejection are still interacting badly during 3-way crossovers

## Launch Notes

Do not launch the raw GUI binaries directly from a background shell for live verification.
That previously caused AppKit / GLFW startup crashes.

Use GUI-safe launch:

- `open -na "/Users/alastairmcneill/Documents/GitHub/NST/NDI-test-sender-3d/bin/NDI-test-sender-3d.app"`
- `open -na "/Users/alastairmcneill/Documents/GitHub/NST/NST1/bin/NST1.app"`

## OSC Capture Script

- `/tmp/osc_sniff_nst.py`

Recent output files:

- `/tmp/osc_trackfirst12.json`
- `/tmp/osc_trackfirst12_raw.json`
- `/tmp/osc_trackfirst21.json`
- `/tmp/osc_trackfirst21_raw.json`
- `/tmp/osc_trackfirst22.json`
- `/tmp/osc_trackfirst22_raw.json`

## Suggested Next Direction

Do not keep tuning visual retention first.

Focus on:

1. crossover assignment / source-track recovery in `processYoloTrackedResults(...)`
2. keeping live geometry attached during overlap
3. avoiding early slot death after improved source recovery

