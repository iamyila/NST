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
    "rect": [80.0, 80.0, 1480.0, 860.0],
    "gridsize": [15.0, 15.0],
    "boxes": [
      { "box": { "id": "obj-1", "maxclass": "comment", "text": "NDI Rain Receiver (8 blobs) + Edge Peak output", "patching_rect": [20.0, 16.0, 360.0, 20.0] } },
      { "box": { "id": "obj-2", "maxclass": "newobj", "text": "udpreceive 12345", "patching_rect": [20.0, 46.0, 105.0, 22.0] } },
      { "box": { "id": "obj-3", "maxclass": "newobj", "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8", "patching_rect": [20.0, 78.0, 760.0, 22.0] } },
      { "box": { "id": "obj-4", "maxclass": "comment", "text": "Per blob edge metric: max(abs(2x-1), abs(2y-1))  -> 0 center, 1 edge", "patching_rect": [20.0, 108.0, 460.0, 20.0] } },

      { "box": { "id": "obj-10", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [20.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-11", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [20.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-12", "maxclass": "flonum", "patching_rect": [20.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-13", "maxclass": "comment", "text": "B1", "patching_rect": [88.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-20", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [190.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-21", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [190.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-22", "maxclass": "flonum", "patching_rect": [190.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-23", "maxclass": "comment", "text": "B2", "patching_rect": [258.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-30", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [360.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-31", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [360.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-32", "maxclass": "flonum", "patching_rect": [360.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-33", "maxclass": "comment", "text": "B3", "patching_rect": [428.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-40", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [530.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-41", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [530.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-42", "maxclass": "flonum", "patching_rect": [530.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-43", "maxclass": "comment", "text": "B4", "patching_rect": [598.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-50", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [700.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-51", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [700.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-52", "maxclass": "flonum", "patching_rect": [700.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-53", "maxclass": "comment", "text": "B5", "patching_rect": [768.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-60", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [870.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-61", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [870.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-62", "maxclass": "flonum", "patching_rect": [870.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-63", "maxclass": "comment", "text": "B6", "patching_rect": [938.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-70", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [1040.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-71", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [1040.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-72", "maxclass": "flonum", "patching_rect": [1040.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-73", "maxclass": "comment", "text": "B7", "patching_rect": [1108.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-80", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [1210.0, 136.0, 145.0, 22.0] } },
      { "box": { "id": "obj-81", "maxclass": "newobj", "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))", "patching_rect": [1210.0, 166.0, 236.0, 22.0] } },
      { "box": { "id": "obj-82", "maxclass": "flonum", "patching_rect": [1210.0, 196.0, 64.0, 22.0] } },
      { "box": { "id": "obj-83", "maxclass": "comment", "text": "B8", "patching_rect": [1278.0, 198.0, 24.0, 20.0] } },

      { "box": { "id": "obj-90", "maxclass": "newobj", "text": "pak f f f f f f f f", "patching_rect": [20.0, 246.0, 190.0, 22.0] } },
      { "box": { "id": "obj-91", "maxclass": "newobj", "text": "unpack f f f f f f f f", "patching_rect": [20.0, 276.0, 165.0, 22.0] } },
      { "box": { "id": "obj-92", "maxclass": "newobj", "text": "expr max($f1, $f2)", "patching_rect": [20.0, 306.0, 105.0, 22.0] } },
      { "box": { "id": "obj-93", "maxclass": "newobj", "text": "expr max($f1, $f2)", "patching_rect": [140.0, 306.0, 105.0, 22.0] } },
      { "box": { "id": "obj-94", "maxclass": "newobj", "text": "expr max($f1, $f2)", "patching_rect": [260.0, 306.0, 105.0, 22.0] } },
      { "box": { "id": "obj-95", "maxclass": "newobj", "text": "expr max($f1, $f2)", "patching_rect": [380.0, 306.0, 105.0, 22.0] } },
      { "box": { "id": "obj-96", "maxclass": "newobj", "text": "expr max($f1, $f2)", "patching_rect": [500.0, 306.0, 105.0, 22.0] } },
      { "box": { "id": "obj-97", "maxclass": "newobj", "text": "expr max($f1, $f2)", "patching_rect": [620.0, 306.0, 105.0, 22.0] } },
      { "box": { "id": "obj-98", "maxclass": "newobj", "text": "clip 0. 1.", "patching_rect": [740.0, 306.0, 60.0, 22.0] } },
      { "box": { "id": "obj-99", "maxclass": "flonum", "patching_rect": [820.0, 306.0, 70.0, 22.0] } },
      { "box": { "id": "obj-100", "maxclass": "comment", "text": "EDGE_PEAK (0..1)", "patching_rect": [896.0, 308.0, 130.0, 20.0] } },
      { "box": { "id": "obj-101", "maxclass": "newobj", "text": "s EDGE_PEAK", "patching_rect": [1040.0, 306.0, 86.0, 22.0] } },
      { "box": { "id": "obj-102", "maxclass": "newobj", "text": "scale 0. 1. 0 127", "patching_rect": [1140.0, 306.0, 110.0, 22.0] } },
      { "box": { "id": "obj-103", "maxclass": "number", "patching_rect": [1260.0, 306.0, 54.0, 22.0] } },
      { "box": { "id": "obj-104", "maxclass": "comment", "text": "Optional MIDI CC out", "patching_rect": [1322.0, 308.0, 130.0, 20.0] } },
      { "box": { "id": "obj-105", "maxclass": "newobj", "text": "ctlout 20 1", "patching_rect": [1260.0, 336.0, 72.0, 22.0] } }
    ],
    "lines": [
      { "patchline": { "source": ["obj-2", 0], "destination": ["obj-3", 0] } },

      { "patchline": { "source": ["obj-3", 0], "destination": ["obj-10", 0] } },
      { "patchline": { "source": ["obj-3", 1], "destination": ["obj-20", 0] } },
      { "patchline": { "source": ["obj-3", 2], "destination": ["obj-30", 0] } },
      { "patchline": { "source": ["obj-3", 3], "destination": ["obj-40", 0] } },
      { "patchline": { "source": ["obj-3", 4], "destination": ["obj-50", 0] } },
      { "patchline": { "source": ["obj-3", 5], "destination": ["obj-60", 0] } },
      { "patchline": { "source": ["obj-3", 6], "destination": ["obj-70", 0] } },
      { "patchline": { "source": ["obj-3", 7], "destination": ["obj-80", 0] } },

      { "patchline": { "source": ["obj-10", 1], "destination": ["obj-11", 0] } },
      { "patchline": { "source": ["obj-10", 2], "destination": ["obj-11", 1] } },
      { "patchline": { "source": ["obj-11", 0], "destination": ["obj-12", 0] } },
      { "patchline": { "source": ["obj-11", 0], "destination": ["obj-90", 0] } },

      { "patchline": { "source": ["obj-20", 1], "destination": ["obj-21", 0] } },
      { "patchline": { "source": ["obj-20", 2], "destination": ["obj-21", 1] } },
      { "patchline": { "source": ["obj-21", 0], "destination": ["obj-22", 0] } },
      { "patchline": { "source": ["obj-21", 0], "destination": ["obj-90", 1] } },

      { "patchline": { "source": ["obj-30", 1], "destination": ["obj-31", 0] } },
      { "patchline": { "source": ["obj-30", 2], "destination": ["obj-31", 1] } },
      { "patchline": { "source": ["obj-31", 0], "destination": ["obj-32", 0] } },
      { "patchline": { "source": ["obj-31", 0], "destination": ["obj-90", 2] } },

      { "patchline": { "source": ["obj-40", 1], "destination": ["obj-41", 0] } },
      { "patchline": { "source": ["obj-40", 2], "destination": ["obj-41", 1] } },
      { "patchline": { "source": ["obj-41", 0], "destination": ["obj-42", 0] } },
      { "patchline": { "source": ["obj-41", 0], "destination": ["obj-90", 3] } },

      { "patchline": { "source": ["obj-50", 1], "destination": ["obj-51", 0] } },
      { "patchline": { "source": ["obj-50", 2], "destination": ["obj-51", 1] } },
      { "patchline": { "source": ["obj-51", 0], "destination": ["obj-52", 0] } },
      { "patchline": { "source": ["obj-51", 0], "destination": ["obj-90", 4] } },

      { "patchline": { "source": ["obj-60", 1], "destination": ["obj-61", 0] } },
      { "patchline": { "source": ["obj-60", 2], "destination": ["obj-61", 1] } },
      { "patchline": { "source": ["obj-61", 0], "destination": ["obj-62", 0] } },
      { "patchline": { "source": ["obj-61", 0], "destination": ["obj-90", 5] } },

      { "patchline": { "source": ["obj-70", 1], "destination": ["obj-71", 0] } },
      { "patchline": { "source": ["obj-70", 2], "destination": ["obj-71", 1] } },
      { "patchline": { "source": ["obj-71", 0], "destination": ["obj-72", 0] } },
      { "patchline": { "source": ["obj-71", 0], "destination": ["obj-90", 6] } },

      { "patchline": { "source": ["obj-80", 1], "destination": ["obj-81", 0] } },
      { "patchline": { "source": ["obj-80", 2], "destination": ["obj-81", 1] } },
      { "patchline": { "source": ["obj-81", 0], "destination": ["obj-82", 0] } },
      { "patchline": { "source": ["obj-81", 0], "destination": ["obj-90", 7] } },

      { "patchline": { "source": ["obj-90", 0], "destination": ["obj-91", 0] } },

      { "patchline": { "source": ["obj-91", 0], "destination": ["obj-92", 0] } },
      { "patchline": { "source": ["obj-91", 1], "destination": ["obj-92", 1] } },
      { "patchline": { "source": ["obj-91", 2], "destination": ["obj-93", 0] } },
      { "patchline": { "source": ["obj-91", 3], "destination": ["obj-93", 1] } },
      { "patchline": { "source": ["obj-91", 4], "destination": ["obj-94", 0] } },
      { "patchline": { "source": ["obj-91", 5], "destination": ["obj-94", 1] } },
      { "patchline": { "source": ["obj-91", 6], "destination": ["obj-95", 0] } },
      { "patchline": { "source": ["obj-91", 7], "destination": ["obj-95", 1] } },

      { "patchline": { "source": ["obj-92", 0], "destination": ["obj-96", 0] } },
      { "patchline": { "source": ["obj-93", 0], "destination": ["obj-96", 1] } },
      { "patchline": { "source": ["obj-94", 0], "destination": ["obj-97", 0] } },
      { "patchline": { "source": ["obj-95", 0], "destination": ["obj-97", 1] } },

      { "patchline": { "source": ["obj-96", 0], "destination": ["obj-98", 0] } },
      { "patchline": { "source": ["obj-97", 0], "destination": ["obj-98", 1] } },

      { "patchline": { "source": ["obj-98", 0], "destination": ["obj-99", 0] } },
      { "patchline": { "source": ["obj-98", 0], "destination": ["obj-101", 0] } },
      { "patchline": { "source": ["obj-98", 0], "destination": ["obj-102", 0] } },
      { "patchline": { "source": ["obj-102", 0], "destination": ["obj-103", 0] } },
      { "patchline": { "source": ["obj-103", 0], "destination": ["obj-105", 0] } }
    ]
  }
}
