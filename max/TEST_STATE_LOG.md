# TEST_STATE_LOG

## How We Track
- Append-only log.
- One entry per patch state change.
- Keep each entry to:
  - `State ID`
  - `Patch file`
  - `Trigger/change`
  - `Works`
  - `Broken`
  - `Notes`

## Entries

### 2026-03-06 — State S01 (known good reference)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/backups/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.before-xy-rollback-20260306-004025.maxpat`
- Trigger/change: baseline before later mapper regressions.
- Works:
  - Blob note behavior in prior testing context.
  - B1 mapping bank path using `Abl.MapUi` rows.
- Broken:
  - Included later-added `Azi/Dist` experiment + extra rows that became unstable during subsequent edits.
- Notes:
  - This is the rollback anchor for recovering mapping behavior.

### 2026-03-06 — State S02 (regression)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat` (intermediate broken revisions)
- Trigger/change: lane-core rewiring + additional conversion/mapping refactors.
- Works:
  - N/A (unstable state).
- Broken:
  - Mapper clear/map behavior inconsistent.
  - Some values stopped updating.
  - Console spam (`live.remote~` too many lines).
  - At points: `inlet out of range` patchcord deletion.
- Notes:
  - Not a state to reuse.

### 2026-03-06 — State S03 (current active)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
- Trigger/change: restore to pre-`Azi/Dist` mapper pattern and remove unstable additions.
- Works (expected):
  - B1 rows: `X`, `Y`, `Spd`, `Size`.
  - `Abl.MapUi` presentation rows restored.
  - Raw feeds:
    - `X <- b1_unpack[1]`
    - `Y <- b1_unpack[2]`
    - `Spd <- b1_unpack[3]`
    - `Size <- b1_unpack[4]`
- Broken (known):
  - `Azi/Dist` mapping not included in this recovered state.
- Notes:
  - Use this as the stable base before adding any new mapping mode.

### 2026-03-06 — State S04 (hotfix: raw data missing on B1)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
- Trigger/change: user reported notes still triggering but `X/Y/Spd/Size` readouts flat.
- Works:
  - Notes still trigger from alive-edge logic.
  - B1 raw payload restored after rewiring.
- Broken (found cause):
  - Missing patchline `b1_tlb[0] -> b1_unpack[0]`.
  - This cut B1 value list flow while note bang flow still worked.
- Fix applied:
  - Re-added `b1_tlb[0] -> b1_unpack[0]`.
  - Structural validation passes (no inlet/outlet out-of-range lines).

### 2026-03-06 — State S05 (root-cause note)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/backups/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.before-xy-rollback-20260306-004025.maxpat`
- Trigger/change: rollback target was assumed “known good”.
- What was actually wrong in that rollback file:
  - Missing connection into `b1_unpack`:
    - absent `b1_tlb[0] -> b1_unpack[0]`
- Why notes still fired while values were dead:
  - Note path used `b1_tlb[1] -> b1_alive_t` (bang path), so note on/off logic kept running.
  - Value path depended on `b1_unpack`, which had no input, so `X/Y/Spd/Size` stayed flat.
- Process fix:
  - Rollback candidates now must pass data-path validation (confirm every `*_unpack` has an inbound line).

### 2026-03-06 — State S06 (debug UI cleanup)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
- Trigger/change: user requested mapped debug readouts removed; keep raw only.
- Works:
  - Raw presentation readouts remain for `X`, `Y`, `Spd`, `Size`.
  - Note path and map rows unchanged.
- Removed:
  - `Mapped` debug column (`dbg_*_map` + title).
- Notes:
  - This keeps UI simpler while preserving in-device data visibility.

### 2026-03-06 — State S07 (Azi/Dist re-added on top of working base)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
- Backup before change:
  - `/Users/alastairmcneill/Documents/GitHub/NST/max/backups/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.pre-azi-dist-add-20260306-012146.maxpat`
- Trigger/change: user requested adding `Azi`/`Dist` without breaking existing `X/Y/Spd/Size`.
- Works (expected):
  - Existing rows unchanged:
    - `X <- b1_unpack[1]`
    - `Y <- b1_unpack[2]`
    - `Spd <- b1_unpack[3]`
    - `Size <- b1_unpack[4]`
  - Added rows:
    - `Azi <- atan2(cy, cx)` normalized to `[0..1]`
    - `Dist <- sqrt(cx^2 + cy^2)` normalized/clipped to `[0..1]`
  - Raw readouts now include `Azi` and `Dist`.
- Structural validation:
  - No missing objects in patchlines.
  - No inlet/outlet out-of-range patchlines.
  - `b1_tlb[0] -> b1_unpack[0]` confirmed present.

### 2026-03-06 — State S08 (orientation adjustment)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
- Backup before change:
  - `/Users/alastairmcneill/Documents/GitHub/NST/max/backups/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.pre-yflip-20260306-014216.maxpat`
- Trigger/change: user reported XY/Azi/Dist not visually correlating; Y appeared inverted.
- Fix applied:
  - Inserted `b1_y_inv = expr 1. - $f1`.
  - Rewired mapper feed:
    - removed `b1_unpack[2] -> b1_y_lane[0]`
    - added `b1_unpack[2] -> b1_y_inv -> b1_y_lane[0]`
- Notes:
  - `Azi/Dist` calculation already used flipped Y (`0.5 - y`), so this brings Y mapper row into the same orientation convention.

### 2026-03-06 — State S09 (clean orientation policy)
- Patch file: `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
- Backup before change:
  - `/Users/alastairmcneill/Documents/GitHub/NST/max/backups/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.pre-orientation-clean-20260306-014621.maxpat`
- Trigger/change: user requested clean/correct coordinate handling.
- Policy now:
  - `X/Y` rows = raw image-space values from NDI (`x: left->right`, `y: top->bottom`).
  - `Azi/Dist` rows = cartesian-derived values from centered coords (`cx=x-0.5`, `cy=0.5-y`).
- Fix applied:
  - Removed `b1_y_inv` mapper feed and restored `b1_unpack[2] -> b1_y_lane[0]`.
  - Kept `Azi/Dist` conversion chain unchanged.
