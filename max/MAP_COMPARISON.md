# Mapping Design Comparison (Blob1 v8 vs LFO/Abl.Map)

## References used
- `/Users/alastairmcneill/Documents/GitHub/NST/max/Abl.Map de encapsulate.maxpat`
- `/Users/alastairmcneill/Documents/GitHub/NST/max/lfomap.maxpat`
- `/Users/alastairmcneill/Documents/GitHub/NST/max/deencap/Abl.Map/INDEX.md`
- `/Users/alastairmcneill/Documents/GitHub/NST/max/deencap/lfomap/INDEX.md`

## Matched to LFO/Abl.Map
- Uses `Abl.Map` engine for each Blob1 lane (`X`, `Y`, `Speed`, `Size`).
- Uses modular lane architecture embedded directly in the main patch (single-file workflow), mirroring LFO's mapper modularity pattern.
- Each lane now exposes the same control concepts as LFO mapping rows:
  - `Map`
  - `Mode` (`Rmt`/`Mod`)
  - polarity toggle (`+` / `±`)
  - depth/range (`%`)
- Uses `live.text` map toggles with mapped-state feedback from `Abl.Map` outlet 3.
- Uses normalized signal input path (`sig~`) into `Abl.Map` signal inlet.
- Pushes mapper defaults on load (same operating assumptions as LFO mapper wiring):
  - min/max: `0/100`
  - remote mode enabled (`use modulation = 0`)
  - incoming depth `1`
  - unipolar input (`bipolar = 0`)

## Intentionally not copied from LFO
- `Abl.MapUi.maxpat` multimap browser UI and banked map UX (not required for this device scope).
- LFO-specific waveform/time controls that feed mapper depth dynamically.

## Current architecture result
- Internal map logic quality is based on the same Ableton mapper core (`Abl.Map`), not the old ad-hoc `live.map + live.remote~` chain.
- Main patch is structurally cleaner: top-level routing + modular embedded mapper lanes instead of dense per-parameter wire mesh.
- Core routing is encapsulated per lane in embedded subpatchers (`p b1_lane_*_core`) to keep top-level patching readable.
