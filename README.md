# NST

Nature Scene Tracker repo.

This repo currently has two main directions:

## Status
- `NDI-cv5`: current usable blob / motion tracker
- `NST1` / `NSTD`: current experimental AI / dance / pose direction
- Older `NDI-cv*` and `NST*` folders: previous versions, tests, or archive material

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
These are mostly older versions, tests, or archive material:
- `NDI-cv/`
- `NDI-cv2/`
- `NDI-cv3/`
- `NDI-cv4/`
- `NDI-cv6/`
- `NSTtest/`
- `NDI-test/`
- `NDI-test-sender/`
- `NDI-test-sender-3d/`

## Practical Summary
If you are new to this repo:
- Use `NDI-cv5` if you want the blob tracker path.
- Use `NST1` / `NSTD` if you want the new AI / dance path.
- Treat the other folders as history, experiments, support tools, or archive material unless you know you need them.

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
