# Max Patch Reference Map

Purpose: preserve old thinking while moving to cleaner working files.

## Canonical Working Files
- `max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v3.maxpat`
  - Current 3-blob MIDI note-on/off test patch.
- `max/ndi_step2_blob1_blob2_candidate_retrigger_v2.maxpat`
  - Stable 2-blob baseline.
- `max/ndi_step1_blob1_candidate_retrigger.maxpat`
  - Minimal single-blob baseline.

## Legacy / Original Reference
- `max/NDI-osc-mapper28.5.maxpat`
  - Main historical patch structure from the original AMXD workflow.
- `NDI-osc-mapper28.5.amxd`
  - Device-level historical source of truth.

## Why This Exists
- Keep human decisions from old patches.
- Avoid re-solving already-solved routing / note logic.
- Allow cleanup without losing context.

## Cleanup Rule
- Archive experiments to `max/archive/<date>/` (move, do not delete).
- Keep canonical files above at top level.
- Update this map whenever a canonical patch changes.
