{
  "patcher": {
    "fileversion": 1,
    "appversion": {
      "major": 9,
      "minor": 1,
      "revision": 2,
      "architecture": "x64",
      "modernui": 1
    },
    "classnamespace": "box",
    "bglocked": 0,
    "rect": [34.0, 87.0, 1400.0, 860.0],
    "openinpresentation": 0,
    "default_fontsize": 12.0,
    "default_fontface": 0,
    "default_fontname": "Arial",
    "gridonopen": 1,
    "gridsize": [15.0, 15.0],
    "gridsnaponopen": 1,
    "toolbarvisible": 1,
    "boxes": [
      {"box": {"id": "obj-0", "maxclass": "comment", "text": "Blob1 retrigger: NoteOn on alive edge AND when label changes", "patching_rect": [40.0, 10.0, 420.0, 20.0]}},
      {"box": {"id": "obj-1", "maxclass": "newobj", "text": "udpreceive 12345", "patching_rect": [40.0, 40.0, 95.0, 22.0]}},
      {"box": {"id": "obj-2", "maxclass": "newobj", "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8 NDITracker9 NDITracker10", "patching_rect": [40.0, 75.0, 790.0, 22.0]}},
      {"box": {"id": "obj-3", "maxclass": "newobj", "text": "t l b", "patching_rect": [40.0, 115.0, 40.0, 22.0]}},

      {"box": {"id": "obj-4", "maxclass": "newobj", "text": "t b b b", "patching_rect": [95.0, 115.0, 50.0, 22.0]}},
      {"box": {"id": "obj-5", "maxclass": "message", "text": "stop", "patching_rect": [160.0, 147.0, 40.0, 22.0]}},
      {"box": {"id": "obj-6", "maxclass": "newobj", "text": "delay 700", "patching_rect": [210.0, 147.0, 65.0, 22.0]}},
      {"box": {"id": "obj-7", "maxclass": "message", "text": "1", "patching_rect": [95.0, 147.0, 30.0, 22.0]}},
      {"box": {"id": "obj-8", "maxclass": "message", "text": "0", "patching_rect": [285.0, 147.0, 30.0, 22.0]}},
      {"box": {"id": "obj-9", "maxclass": "newobj", "text": "change", "patching_rect": [135.0, 182.0, 50.0, 22.0]}},
      {"box": {"id": "obj-10", "maxclass": "newobj", "text": "sel 1 0", "patching_rect": [135.0, 217.0, 60.0, 22.0]}},

      {"box": {"id": "obj-11", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [40.0, 147.0, 130.0, 22.0]}},
      {"box": {"id": "obj-12", "maxclass": "newobj", "text": "change", "patching_rect": [40.0, 182.0, 50.0, 22.0]}},
      {"box": {"id": "obj-13", "maxclass": "newobj", "text": "t b b", "patching_rect": [40.0, 217.0, 40.0, 22.0]}},
      {"box": {"id": "obj-14", "maxclass": "newobj", "text": "delay 1", "patching_rect": [40.0, 252.0, 50.0, 22.0]}},

      {"box": {"id": "obj-20", "maxclass": "message", "text": "60 100", "patching_rect": [220.0, 290.0, 55.0, 22.0]}},
      {"box": {"id": "obj-21", "maxclass": "message", "text": "60 0", "patching_rect": [285.0, 290.0, 45.0, 22.0]}},
      {"box": {"id": "obj-22", "maxclass": "newobj", "text": "unpack i i", "patching_rect": [240.0, 330.0, 65.0, 22.0]}},
      {"box": {"id": "obj-23", "maxclass": "newobj", "text": "noteout", "patching_rect": [240.0, 365.0, 50.0, 22.0]}},

      {"box": {"id": "obj-30", "maxclass": "newobj", "text": "print BLOB1_PKT", "patching_rect": [370.0, 115.0, 90.0, 22.0]}},
      {"box": {"id": "obj-31", "maxclass": "newobj", "text": "print BLOB1_LABEL", "patching_rect": [100.0, 182.0, 100.0, 22.0]}},
      {"box": {"id": "obj-32", "maxclass": "newobj", "text": "print NOTE_ON_EDGE", "patching_rect": [220.0, 252.0, 110.0, 22.0]}},
      {"box": {"id": "obj-33", "maxclass": "newobj", "text": "print NOTE_OFF_EDGE", "patching_rect": [335.0, 252.0, 110.0, 22.0]}},
      {"box": {"id": "obj-34", "maxclass": "newobj", "text": "print NOTE_RETRIG", "patching_rect": [40.0, 290.0, 100.0, 22.0]}}
    ],
    "lines": [
      {"patchline": {"source": ["obj-1", 0], "destination": ["obj-2", 0]}},
      {"patchline": {"source": ["obj-2", 0], "destination": ["obj-3", 0]}},
      {"patchline": {"source": ["obj-2", 0], "destination": ["obj-30", 0]}},

      {"patchline": {"source": ["obj-3", 0], "destination": ["obj-11", 0]}},
      {"patchline": {"source": ["obj-3", 1], "destination": ["obj-4", 0]}},

      {"patchline": {"source": ["obj-4", 2], "destination": ["obj-5", 0]}},
      {"patchline": {"source": ["obj-5", 0], "destination": ["obj-6", 0]}},
      {"patchline": {"source": ["obj-4", 1], "destination": ["obj-6", 0]}},
      {"patchline": {"source": ["obj-4", 0], "destination": ["obj-7", 0]}},
      {"patchline": {"source": ["obj-7", 0], "destination": ["obj-9", 0]}},
      {"patchline": {"source": ["obj-6", 0], "destination": ["obj-8", 0]}},
      {"patchline": {"source": ["obj-8", 0], "destination": ["obj-9", 0]}},
      {"patchline": {"source": ["obj-9", 0], "destination": ["obj-10", 0]}},
      {"patchline": {"source": ["obj-10", 0], "destination": ["obj-20", 0]}},
      {"patchline": {"source": ["obj-10", 1], "destination": ["obj-21", 0]}},
      {"patchline": {"source": ["obj-10", 0], "destination": ["obj-32", 0]}},
      {"patchline": {"source": ["obj-10", 1], "destination": ["obj-33", 0]}},

      {"patchline": {"source": ["obj-11", 0], "destination": ["obj-12", 0]}},
      {"patchline": {"source": ["obj-12", 0], "destination": ["obj-13", 0]}},
      {"patchline": {"source": ["obj-12", 0], "destination": ["obj-31", 0]}},
      {"patchline": {"source": ["obj-13", 1], "destination": ["obj-21", 0]}},
      {"patchline": {"source": ["obj-13", 0], "destination": ["obj-14", 0]}},
      {"patchline": {"source": ["obj-14", 0], "destination": ["obj-20", 0]}},
      {"patchline": {"source": ["obj-13", 0], "destination": ["obj-34", 0]}},

      {"patchline": {"source": ["obj-20", 0], "destination": ["obj-22", 0]}},
      {"patchline": {"source": ["obj-21", 0], "destination": ["obj-22", 0]}},
      {"patchline": {"source": ["obj-22", 0], "destination": ["obj-23", 0]}},
      {"patchline": {"source": ["obj-22", 1], "destination": ["obj-23", 1]}}
    ]
  }
}
