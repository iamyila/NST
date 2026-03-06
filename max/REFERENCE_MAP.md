# Max Patch Reference Map

Purpose: preserve decisions while keeping one clean active patch.

## Canonical Working Files
- `/Users/alastairmcneill/Documents/GitHub/NST/max/ndi_step3_blob1_blob2_blob3_candidate_retrigger_v8.maxpat`
  - Current main patch, with Blob1 mapper lanes embedded in-file (no external lane patch dependencies).
- `/Users/alastairmcneill/Documents/GitHub/NST/max/Abl.Map de encapsulate.maxpat`
  - Primary mapping reference (de-encapsulated Ableton map engine).
- `/Users/alastairmcneill/Documents/GitHub/NST/max/lfomap.maxpat`
  - Secondary reference for current Ableton map UX flow and wiring pattern.

## Archived Step Lineage
- `/Users/alastairmcneill/Documents/GitHub/NST/max/archive/2026-03-05/cleanup-20260305-002033`
- Backups index:
  - `/Users/alastairmcneill/Documents/GitHub/NST/max/backups/BACKUP_INDEX.md`

## Max for Live Mapping Notes (Researched 2026-03-05)
- Device UI space:
  - Live device height is fixed to `169 px`.
  - Use Presentation Mode and `View -> Set Device Width` for compact layout.
- Exposed parameters:
  - Use `live.*` UI objects (`live.numbox`, `live.dial`, etc.) with parameter enabled.
  - Set unique `Long Name` and short `Short Name` per parameter.
  - `Parameter Visibility`:
    - `Automated and Stored`: appears in automation.
    - `Stored Only`: stored in presets but no automation.
    - `Hidden`: excluded from store/recall.
- Mapping flow:
  - Baseline now follows Ableton's `Abl.Map` engine (same core behavior as LFO devices).
  - `Abl.Map` inlet contract (from de-encapsulated patch):
    - `in~ 1`: signal to map
    - `in 2`: map on/off
    - `in 3`: stop mapping
    - `in 4/5`: remote min/max (%)
    - `in 6/7/8/9/10`: modulation/polarity/depth/scaling controls
  - `Abl.Map` outlet contract:
    - `out 1`: mapped id
    - `out 2`: mapping stopped bang
    - `out 3`: mapped bool (UI feedback)
- Runtime control:
  - Input control values are normalized (`0..1`) before mapping.
  - Blob1 mapper bank is modularized in-file as 4 lane groups (`X/Y/Speed/Size`), each with internal `poly~ Abl.Map`.
  - Each Blob1 lane exposes LFO-style mapping controls:
    - `Map`
    - `Mode` (`Rmt`/`Mod`)
    - polarity (`+` / `±`)
    - range/depth (`%`)
  - Main patch wiring is reduced to clean source routing: `b1_unpack` -> embedded lane groups.
  - Explicit defaults are pushed on load to match LFO-style mapper assumptions:
    - remote min/max = `0 / 100`
    - use modulation = `0` (remote mode)
    - modulation polarity = `1`
    - modulation target depth = `100`
    - incoming depth = `1`
    - input bipolar flag = `0`
  - Live API mapping still follows official `live.map`/`live.remote~` semantics internally.

## Next Session Focus
- Validate Blob 1 `X/Y/Speed/Size` map buttons in Live device view.
- Keep visible map controls compact in Presentation and non-overlapping in patching view.
- Expand same pattern to Blob 2 and Blob 3 only after Blob 1 is confirmed in Live.
