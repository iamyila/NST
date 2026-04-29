# NST

Nature Scene Tracker repository.

## Current Layout

### Classic blob path
- `NDI-cv5/`
  - current usable blob / motion tracker
- `NDI-test-sender/`
  - current 2D sender used with `NDI-cv5`

### New AI / dance path
- `NST1/`
  - newer AI / pose / dance tracking source tree
  - builds the app called `NSTD`
- `NDI-test-sender-3d/`
  - current 3D sender used with `NST1` / `NSTD`

### Shared / support
- `NDI-osc-mapper28.5.amxd`
- `max/`
- `archive/`

## Status
- `NDI-cv5`: current classic blob tracker
- `NDI-test-sender`: current classic sender for the blob tracker
- `NST1`: current AI / dance / pose development source
- `NSTD`: app built from `NST1`
- `NDI-test-sender-3d`: current 3D sender for the AI / dance path
- `archive/`: older versions and unused branches

## Archive
Older versions were moved out of the top level into `archive/`.

This currently includes:
- `archive/NDI-cv/`
- `archive/NDI-cv2/`
- `archive/NDI-cv3/`
- `archive/NDI-cv4/`
- `archive/NDI-cv6/`
- `archive/NSTtest/`
- `archive/NDI-test/`

## Practical Summary
If you are new to the project:
- use `NDI-cv5` for the classic blob workflow
- use `NDI-test-sender` with `NDI-cv5`
- use `NST1` if you want the newer AI / dance / `NSTD` direction
- use `NDI-test-sender-3d` with `NST1` / `NSTD`
- ignore `archive/` unless you specifically need an old version

## Requirements
- NDI runtime / NDI video sources
- Ableton Live Suite 11 if you are using the Max for Live devices

## Notes
- `CODEX_STATE.md` and `CLAUDE_HANDOFF_2026-04-08.md` contain older handoff/debug notes and may lag behind the latest folder cleanup

Original code lineage:
- Sebastian Frisch: http://freshmania.at/
- Hiroshi Matoba / later NST variants
