# NST
Nature Scene Tracker - Openframeworks Blob/motion tracker w NDI video in and out x10

NDI-cv5 is the current version

https://github.com/iamyila/NST/blob/master/NDI-cv-mapper_28.5._2.amxd is the corresponding Maxforlive device. 
  
you will need Ableton live suite 11 + NDI runtime / NDI video sources

Orginal code by Sebastian Frisch http://freshmania.at/ - Hiroshi Matabo v5

## Recent Notes (2026-02-27)

- `NDI-cv5/src/OscSender.h`: OSC base address is currently hard-wired to `/NDITracker0` for consistent naming.
- `max/NDI-osc-mapper28.5.maxpat`: ingress now expects true OSC packet parsing with `oscparse -> list trim -> route`.
- Added Max debug/reference files:
  - `max/ndi_cv5_true_osc_receiver_template.maxpat`
  - `max/NDI-osc-mapper28.5.maxpat.bak`

