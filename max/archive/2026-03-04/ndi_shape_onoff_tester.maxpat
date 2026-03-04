{
  "patcher": {
    "fileversion": 1,
    "appversion": {"major": 9, "minor": 1, "revision": 2, "architecture": "x64", "modernui": 1},
    "classnamespace": "box",
    "bglocked": 0,
    "rect": [60.0, 90.0, 1200.0, 760.0],
    "openinpresentation": 0,
    "default_fontsize": 12.0,
    "default_fontface": 0,
    "default_fontname": "Arial",
    "gridonopen": 1,
    "gridsize": [15.0, 15.0],
    "gridsnaponopen": 1,
    "toolbarvisible": 1,
    "boxes": [
      {"box": {"id": "c0", "maxclass": "comment", "text": "NDI Shape On/Off Tester: sends NDITracker1/2 packets to UDP 12345", "patching_rect": [30.0, 10.0, 460.0, 20.0]}},
      {"box": {"id": "u1", "maxclass": "newobj", "text": "udpsend 127.0.0.1 12345", "patching_rect": [30.0, 40.0, 145.0, 22.0]}},

      {"box": {"id": "c1", "maxclass": "comment", "text": "Blob 1 stream", "patching_rect": [30.0, 90.0, 100.0, 20.0]}},
      {"box": {"id": "t1", "maxclass": "toggle", "patching_rect": [30.0, 115.0, 24.0, 24.0]}},
      {"box": {"id": "m1", "maxclass": "newobj", "text": "metro 50", "patching_rect": [65.0, 116.0, 55.0, 22.0]}},
      {"box": {"id": "msg1", "maxclass": "message", "text": "1 0.42 0.58 0.18 0.09 12 0.00 0.00", "patching_rect": [130.0, 116.0, 210.0, 22.0]}},
      {"box": {"id": "pre1", "maxclass": "newobj", "text": "prepend NDITracker1", "patching_rect": [350.0, 116.0, 130.0, 22.0]}},
      {"box": {"id": "p1", "maxclass": "newobj", "text": "print TESTER_BLOB1", "patching_rect": [490.0, 116.0, 110.0, 22.0]}},

      {"box": {"id": "c2", "maxclass": "comment", "text": "Blob 2 stream", "patching_rect": [30.0, 170.0, 100.0, 20.0]}},
      {"box": {"id": "t2", "maxclass": "toggle", "patching_rect": [30.0, 195.0, 24.0, 24.0]}},
      {"box": {"id": "m2", "maxclass": "newobj", "text": "metro 65", "patching_rect": [65.0, 196.0, 55.0, 22.0]}},
      {"box": {"id": "msg2", "maxclass": "message", "text": "2 0.68 0.35 0.22 0.12 10 0.00 0.00", "patching_rect": [130.0, 196.0, 210.0, 22.0]}},
      {"box": {"id": "pre2", "maxclass": "newobj", "text": "prepend NDITracker2", "patching_rect": [350.0, 196.0, 130.0, 22.0]}},
      {"box": {"id": "p2", "maxclass": "newobj", "text": "print TESTER_BLOB2", "patching_rect": [490.0, 196.0, 110.0, 22.0]}},

      {"box": {"id": "c3", "maxclass": "comment", "text": "Auto on/off", "patching_rect": [30.0, 270.0, 100.0, 20.0]}},
      {"box": {"id": "ta", "maxclass": "toggle", "patching_rect": [30.0, 295.0, 24.0, 24.0]}},
      {"box": {"id": "ma1", "maxclass": "newobj", "text": "metro 2800", "patching_rect": [65.0, 296.0, 70.0, 22.0]}},
      {"box": {"id": "ra1", "maxclass": "newobj", "text": "random 2", "patching_rect": [145.0, 296.0, 60.0, 22.0]}},
      {"box": {"id": "ma2", "maxclass": "newobj", "text": "metro 3700", "patching_rect": [65.0, 331.0, 70.0, 22.0]}},
      {"box": {"id": "ra2", "maxclass": "newobj", "text": "random 2", "patching_rect": [145.0, 331.0, 60.0, 22.0]}},
      {"box": {"id": "c4", "maxclass": "comment", "text": "Use manual toggles or enable Auto", "patching_rect": [220.0, 298.0, 220.0, 20.0]}}
    ],
    "lines": [
      {"patchline": {"source": ["t1", 0], "destination": ["m1", 0]}},
      {"patchline": {"source": ["m1", 0], "destination": ["msg1", 0]}},
      {"patchline": {"source": ["msg1", 0], "destination": ["pre1", 0]}},
      {"patchline": {"source": ["pre1", 0], "destination": ["u1", 0]}},
      {"patchline": {"source": ["pre1", 0], "destination": ["p1", 0]}},

      {"patchline": {"source": ["t2", 0], "destination": ["m2", 0]}},
      {"patchline": {"source": ["m2", 0], "destination": ["msg2", 0]}},
      {"patchline": {"source": ["msg2", 0], "destination": ["pre2", 0]}},
      {"patchline": {"source": ["pre2", 0], "destination": ["u1", 0]}},
      {"patchline": {"source": ["pre2", 0], "destination": ["p2", 0]}},

      {"patchline": {"source": ["ta", 0], "destination": ["ma1", 0]}},
      {"patchline": {"source": ["ta", 0], "destination": ["ma2", 0]}},
      {"patchline": {"source": ["ma1", 0], "destination": ["ra1", 0]}},
      {"patchline": {"source": ["ma2", 0], "destination": ["ra2", 0]}},
      {"patchline": {"source": ["ra1", 0], "destination": ["t1", 0]}},
      {"patchline": {"source": ["ra2", 0], "destination": ["t2", 0]}}
    ]
  }
}
