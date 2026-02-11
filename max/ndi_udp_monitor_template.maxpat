{
  "patcher": {
    "fileversion": 1,
    "appversion": {
      "major": 9,
      "minor": 0,
      "revision": 10,
      "architecture": "x64",
      "modernui": 1
    },
    "classnamespace": "box",
    "rect": [80.0, 90.0, 1280.0, 760.0],
    "gridsize": [15.0, 15.0],
    "boxes": [
      { "box": { "id": "obj-1", "maxclass": "comment", "text": "NDI UDP monitor template (copy objects into your AMXD)", "patching_rect": [20.0, 15.0, 360.0, 20.0] } },
      { "box": { "id": "obj-2", "maxclass": "newobj", "text": "udpreceive 12345", "patching_rect": [20.0, 50.0, 104.0, 22.0] } },
      { "box": { "id": "obj-3", "maxclass": "newobj", "text": "print UDP_RAW", "patching_rect": [140.0, 50.0, 95.0, 22.0] } },
      { "box": { "id": "obj-4", "maxclass": "comment", "text": "1) Confirm packets arrive", "patching_rect": [250.0, 50.0, 180.0, 20.0] } },

      { "box": { "id": "obj-5", "maxclass": "newobj", "text": "route /NDItracker0/1/val /NDItracker0/1/on /NDItracker0/1/off", "patching_rect": [20.0, 95.0, 410.0, 22.0] } },
      { "box": { "id": "obj-6", "maxclass": "newobj", "text": "print VAL_HIT", "patching_rect": [450.0, 95.0, 86.0, 22.0] } },
      { "box": { "id": "obj-7", "maxclass": "newobj", "text": "print ON_HIT", "patching_rect": [545.0, 95.0, 82.0, 22.0] } },
      { "box": { "id": "obj-8", "maxclass": "newobj", "text": "print OFF_HIT", "patching_rect": [636.0, 95.0, 88.0, 22.0] } },
      { "box": { "id": "obj-9", "maxclass": "comment", "text": "2) See which route branch is matching", "patching_rect": [735.0, 95.0, 230.0, 20.0] } },

      { "box": { "id": "obj-10", "maxclass": "newobj", "text": "unpack i f f f f i f f", "patching_rect": [20.0, 140.0, 145.0, 22.0] } },
      { "box": { "id": "obj-11", "maxclass": "comment", "text": "label", "patching_rect": [20.0, 170.0, 36.0, 20.0] } },
      { "box": { "id": "obj-12", "maxclass": "number", "patching_rect": [20.0, 190.0, 54.0, 22.0] } },
      { "box": { "id": "obj-13", "maxclass": "comment", "text": "x", "patching_rect": [85.0, 170.0, 18.0, 20.0] } },
      { "box": { "id": "obj-14", "maxclass": "flonum", "patching_rect": [85.0, 190.0, 62.0, 22.0] } },
      { "box": { "id": "obj-15", "maxclass": "comment", "text": "y", "patching_rect": [158.0, 170.0, 18.0, 20.0] } },
      { "box": { "id": "obj-16", "maxclass": "flonum", "patching_rect": [158.0, 190.0, 62.0, 22.0] } },
      { "box": { "id": "obj-17", "maxclass": "comment", "text": "speed", "patching_rect": [231.0, 170.0, 42.0, 20.0] } },
      { "box": { "id": "obj-18", "maxclass": "flonum", "patching_rect": [231.0, 190.0, 62.0, 22.0] } },
      { "box": { "id": "obj-19", "maxclass": "comment", "text": "area", "patching_rect": [304.0, 170.0, 34.0, 20.0] } },
      { "box": { "id": "obj-20", "maxclass": "flonum", "patching_rect": [304.0, 190.0, 62.0, 22.0] } },
      { "box": { "id": "obj-21", "maxclass": "comment", "text": "age", "patching_rect": [377.0, 170.0, 28.0, 20.0] } },
      { "box": { "id": "obj-22", "maxclass": "number", "patching_rect": [377.0, 190.0, 54.0, 22.0] } },
      { "box": { "id": "obj-23", "maxclass": "comment", "text": "angle", "patching_rect": [442.0, 170.0, 38.0, 20.0] } },
      { "box": { "id": "obj-24", "maxclass": "flonum", "patching_rect": [442.0, 190.0, 62.0, 22.0] } },
      { "box": { "id": "obj-25", "maxclass": "comment", "text": "len", "patching_rect": [515.0, 170.0, 24.0, 20.0] } },
      { "box": { "id": "obj-26", "maxclass": "flonum", "patching_rect": [515.0, 190.0, 62.0, 22.0] } },
      { "box": { "id": "obj-27", "maxclass": "newobj", "text": "print VAL_PARSED", "patching_rect": [590.0, 140.0, 102.0, 22.0] } },
      { "box": { "id": "obj-28", "maxclass": "comment", "text": "3) Parsed values monitor", "patching_rect": [705.0, 140.0, 170.0, 20.0] } },

      { "box": { "id": "obj-29", "maxclass": "newobj", "text": "zl len", "patching_rect": [20.0, 240.0, 42.0, 22.0] } },
      { "box": { "id": "obj-30", "maxclass": "number", "patching_rect": [70.0, 240.0, 54.0, 22.0] } },
      { "box": { "id": "obj-31", "maxclass": "comment", "text": "arg count for val", "patching_rect": [130.0, 241.0, 100.0, 20.0] } },

      { "box": { "id": "obj-32", "maxclass": "newobj", "text": "t b", "patching_rect": [20.0, 290.0, 24.0, 22.0] } },
      { "box": { "id": "obj-33", "maxclass": "button", "patching_rect": [52.0, 291.0, 20.0, 20.0] } },
      { "box": { "id": "obj-34", "maxclass": "newobj", "text": "counter", "patching_rect": [80.0, 290.0, 52.0, 22.0] } },
      { "box": { "id": "obj-35", "maxclass": "number", "patching_rect": [140.0, 290.0, 70.0, 22.0] } },
      { "box": { "id": "obj-36", "maxclass": "newobj", "text": "metro 1000", "patching_rect": [220.0, 290.0, 70.0, 22.0] } },
      { "box": { "id": "obj-37", "maxclass": "toggle", "patching_rect": [300.0, 290.0, 24.0, 24.0] } },
      { "box": { "id": "obj-38", "maxclass": "newobj", "text": "t b b", "patching_rect": [334.0, 291.0, 38.0, 22.0] } },
      { "box": { "id": "obj-39", "maxclass": "newobj", "text": "i", "patching_rect": [382.0, 290.0, 24.0, 22.0] } },
      { "box": { "id": "obj-40", "maxclass": "newobj", "text": "-", "patching_rect": [414.0, 290.0, 24.0, 22.0] } },
      { "box": { "id": "obj-41", "maxclass": "number", "patching_rect": [446.0, 290.0, 70.0, 22.0] } },
      { "box": { "id": "obj-42", "maxclass": "comment", "text": "val packets/sec", "patching_rect": [526.0, 291.0, 95.0, 20.0] } },
      { "box": { "id": "obj-43", "maxclass": "newobj", "text": "loadmess 1", "patching_rect": [300.0, 324.0, 70.0, 22.0] } },

      { "box": { "id": "obj-44", "maxclass": "comment", "text": "Tip: if you use /NDITracker0 (capital T), duplicate route object with that case.", "patching_rect": [20.0, 370.0, 480.0, 20.0] } }
    ],
    "lines": [
      { "patchline": { "source": ["obj-2", 0], "destination": ["obj-3", 0] } },
      { "patchline": { "source": ["obj-2", 0], "destination": ["obj-5", 0] } },

      { "patchline": { "source": ["obj-5", 0], "destination": ["obj-6", 0] } },
      { "patchline": { "source": ["obj-5", 1], "destination": ["obj-7", 0] } },
      { "patchline": { "source": ["obj-5", 2], "destination": ["obj-8", 0] } },

      { "patchline": { "source": ["obj-5", 0], "destination": ["obj-27", 0] } },
      { "patchline": { "source": ["obj-5", 0], "destination": ["obj-29", 0] } },
      { "patchline": { "source": ["obj-29", 0], "destination": ["obj-30", 0] } },
      { "patchline": { "source": ["obj-5", 0], "destination": ["obj-10", 0] } },

      { "patchline": { "source": ["obj-10", 0], "destination": ["obj-12", 0] } },
      { "patchline": { "source": ["obj-10", 1], "destination": ["obj-14", 0] } },
      { "patchline": { "source": ["obj-10", 2], "destination": ["obj-16", 0] } },
      { "patchline": { "source": ["obj-10", 3], "destination": ["obj-18", 0] } },
      { "patchline": { "source": ["obj-10", 4], "destination": ["obj-20", 0] } },
      { "patchline": { "source": ["obj-10", 5], "destination": ["obj-22", 0] } },
      { "patchline": { "source": ["obj-10", 6], "destination": ["obj-24", 0] } },
      { "patchline": { "source": ["obj-10", 7], "destination": ["obj-26", 0] } },

      { "patchline": { "source": ["obj-5", 0], "destination": ["obj-32", 0] } },
      { "patchline": { "source": ["obj-32", 0], "destination": ["obj-33", 0] } },
      { "patchline": { "source": ["obj-32", 0], "destination": ["obj-34", 0] } },
      { "patchline": { "source": ["obj-34", 0], "destination": ["obj-35", 0] } },
      { "patchline": { "source": ["obj-34", 0], "destination": ["obj-39", 1] } },

      { "patchline": { "source": ["obj-43", 0], "destination": ["obj-37", 0] } },
      { "patchline": { "source": ["obj-37", 0], "destination": ["obj-36", 0] } },
      { "patchline": { "source": ["obj-36", 0], "destination": ["obj-38", 0] } },
      { "patchline": { "source": ["obj-38", 0], "destination": ["obj-39", 0] } },
      { "patchline": { "source": ["obj-38", 1], "destination": ["obj-40", 0] } },
      { "patchline": { "source": ["obj-39", 0], "destination": ["obj-40", 1] } },
      { "patchline": { "source": ["obj-40", 0], "destination": ["obj-41", 0] } }
    ]
  }
}
