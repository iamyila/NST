# NST
Nature Scene Tracker - Openframeworks Blob/motion tracker w NDI video in and out x10

NDI-cv5 is the current version

https://github.com/iamyila/NST/blob/master/NDI-cv-mapper_28.5._2.amxd is the corresponding Maxforlive device. 
  
you will need Ableton live suite 11 + NDI runtime / NDI video sources

Orginal code by Sebastian Frisch http://freshmania.at/ - Hiroshi Matabo v5

## OSC + Max Debug Notes (2026-02-27)

### Current OSC naming in NDI-cv5
- File: `NDI-cv5/src/OscSender.h`
- OSC base address is hard-wired to: `/NDITracker1`
- Per blob slot, app sends:
  - `/NDITracker1/<slot>/val`
  - `/NDITracker1/<slot>/on`
  - `/NDITracker1/<slot>/off`
- Slot index is 1-based (`1..10`).

### Required Max parsing chain
- If using `udpreceive`, parse true OSC packets with:
  - `oscparse -> list trim -> route ...`
- Do not route raw strings directly from `udpreceive` for this stream format.

### Max files for testing/debug
- Main patch under test: `max/NDI-osc-mapper28.5.maxpat`
- Backup before edits: `max/NDI-osc-mapper28.5.maxpat.bak`
- Fake sender for repeatable OSC tests: `max/fake_ndi5cv_osc_sender.maxpat`
- UDP monitor template: `max/ndi_udp_monitor_template.maxpat`
- True OSC receiver template: `max/ndi_cv5_true_osc_receiver_template.maxpat`

### Known mismatch that breaks routing
- Old pattern: `route NDITracker0 ...`
- Current stream is address-based (`/NDITracker1/...`), so routing must match full parsed OSC addresses.

### Practical debug technique
- First verify packet arrival at `udpreceive`.
- Then verify parsed address/value after `oscparse` and `list trim` (use `print` or message box).
- Only after parse is correct, route to each encapsulated blob module.

## Tracking Technique Notes (Blob vs YOLO)

### Current state
- Tracking mode parameter exists in `NDI-cv5/src/mtbTrackerBase.h`:
  - `Tracking Technique (0 Blob, 1 YOLO)`
- Runtime dispatch exists in `NDI-cv5/src/mtbTracker.h`.
- Current behavior:
  - `0` runs blob tracking (active implementation).
  - `1` logs a warning once and falls back to blob tracking.

### Decision tree (current)
- `trackingTechnique == 0`:
  - Process contours -> select blobs -> send OSC on/off/val.
- `trackingTechnique == 1`:
  - Enter YOLO placeholder branch -> fallback to blob path.

### Integration point for future YOLO work
- Add YOLO detector/tracker in `NDI-cv5/src/mtbTracker.h` where the YOLO placeholder branch currently lives.
- Keep OSC emitter (`NDI-cv5/src/OscSender.h`) unchanged so Max mappings remain stable.
