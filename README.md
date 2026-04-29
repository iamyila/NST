# NST

Nature Scene Tracker repo.

This repo currently has two main directions:

## Status
- `NDI-cv5`: current usable blob / motion tracker
- `NST1` / `NSTD`: current experimental AI / dance / pose direction
- `NDI-test-sender`: current classic sender for `NDI-cv5`
- `NDI-test-sender-3d`: current 3D sender for `NST1` / `NSTD`
- `archive/`: older versions, tests, or unused branches moved out of the way

## 1. `NDI-cv5` = current blob / motion tracker
- This is the current working blob-based tracker.
- Use this if you want the older contour / motion workflow.
- This is the version to pair with the existing Max for Live blob mapping workflow.
- Main idea: camera or NDI video in -> blob tracking -> OSC / Max for Live.

Related files:
- `NDI-cv5/`
- `NDI-osc-mapper28.5.amxd`
- `max/`

## 2. `NST1` -> builds as `NSTD` = new AI / dance direction
- The source folder is `NST1/`.
- The built app name is `NSTD`.
- This is the newer AI / pose / dance-tracking direction.
- Main idea: move beyond simple blobs toward person / pose / dance control.
- This is the current experimental branch, not the old stable blob path.

Important detail:
- `NST1` is the source tree.
- `NSTD` is the app name produced by that source tree.

## 3. Older folders
Older versions and unused branches have been moved to:
- `archive/`

This currently includes:
- `archive/NDI-cv/`
- `archive/NDI-cv2/`
- `archive/NDI-cv3/`
- `archive/NDI-cv4/`
- `archive/NDI-cv6/`
- `archive/NSTtest/`
- `archive/NDI-test/`

Current senders kept active:
- `NDI-test-sender/` for the `NDI-cv5` blob path
- `NDI-test-sender-3d/` for the `NST1` / `NSTD` path

## Practical Summary
If you are new to this repo:
- Use `NDI-cv5` if you want the blob tracker path.
- Use `NST1` / `NSTD` if you want the new AI / dance path.
- Use `NDI-test-sender` with `NDI-cv5`.
- Use `NDI-test-sender-3d` with `NST1` / `NSTD`.
- Ignore `archive/` unless you specifically need an old version.

## Requirements
- NDI runtime / NDI video sources
- Ableton Live Suite 11 if you are using the Max for Live devices

## More Detail
For live handoff / state notes, see:
- `CODEX_STATE.md`
- `CLAUDE_HANDOFF_2026-04-08.md`

Original code lineage:
- Sebastian Frisch: http://freshmania.at/
- Hiroshi Matoba / later NST variants
