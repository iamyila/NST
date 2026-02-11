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
    "rect": [50.0, 80.0, 1210.0, 780.0],
    "gridsize": [15.0, 15.0],
    "boxes": [
      { "box": { "id": "obj-1", "maxclass": "comment", "text": "Fake NDI-cv5 sender (no oscformat): /NDItracker0/<slot>/{val,on,off} -> localhost:12345", "patching_rect": [20.0, 18.0, 620.0, 20.0] } },
      { "box": { "id": "obj-2", "maxclass": "toggle", "patching_rect": [20.0, 52.0, 24.0, 24.0] } },
      { "box": { "id": "obj-3", "maxclass": "newobj", "text": "metro 33", "patching_rect": [56.0, 53.0, 62.0, 22.0] } },
      { "box": { "id": "obj-4", "maxclass": "newobj", "text": "counter 0 1000000", "patching_rect": [130.0, 53.0, 116.0, 22.0] } },
      { "box": { "id": "obj-5", "maxclass": "number", "patching_rect": [258.0, 53.0, 64.0, 22.0] } },
      { "box": { "id": "obj-6", "maxclass": "newobj", "text": "loadmess 1", "patching_rect": [20.0, 86.0, 70.0, 22.0] } },

      { "box": { "id": "obj-20", "maxclass": "comment", "text": "slot", "patching_rect": [20.0, 126.0, 38.0, 20.0] } },
      { "box": { "id": "obj-21", "maxclass": "number", "patching_rect": [20.0, 146.0, 64.0, 22.0] } },
      { "box": { "id": "obj-22", "maxclass": "newobj", "text": "loadmess 1", "patching_rect": [92.0, 146.0, 70.0, 22.0] } },

      { "box": { "id": "obj-10", "maxclass": "newobj", "text": "expr $i1 % 16", "patching_rect": [130.0, 110.0, 82.0, 22.0] } },
      { "box": { "id": "obj-11", "maxclass": "newobj", "text": "expr (($i1*3)%100)/99.", "patching_rect": [224.0, 110.0, 150.0, 22.0] } },
      { "box": { "id": "obj-12", "maxclass": "newobj", "text": "expr (($i1*7+13)%100)/99.", "patching_rect": [386.0, 110.0, 168.0, 22.0] } },
      { "box": { "id": "obj-13", "maxclass": "newobj", "text": "expr (($i1 % 20)+1)/100.", "patching_rect": [566.0, 110.0, 165.0, 22.0] } },
      { "box": { "id": "obj-14", "maxclass": "newobj", "text": "expr (($i1 % 50)+10)/1000.", "patching_rect": [743.0, 110.0, 174.0, 22.0] } },
      { "box": { "id": "obj-15", "maxclass": "newobj", "text": "expr sin($i1*0.1)*180.", "patching_rect": [929.0, 110.0, 153.0, 22.0] } },
      { "box": { "id": "obj-16", "maxclass": "newobj", "text": "expr (sin($i1*0.07)*0.995)+1.005", "patching_rect": [1094.0, 110.0, 220.0, 22.0] } },

      { "box": { "id": "obj-17", "maxclass": "newobj", "text": "pak i i f f f f i f f", "patching_rect": [224.0, 158.0, 154.0, 22.0] } },
      { "box": { "id": "obj-18", "maxclass": "newobj", "text": "sprintf /NDItracker0/%ld/val %ld %f %f %f %f %ld %f %f", "patching_rect": [224.0, 188.0, 330.0, 22.0] } },
      { "box": { "id": "obj-19", "maxclass": "comment", "text": "val args: label x y speed area age angle len", "patching_rect": [566.0, 189.0, 290.0, 20.0] } },

      { "box": { "id": "obj-40", "maxclass": "newobj", "text": "udpsend localhost 12345", "patching_rect": [224.0, 332.0, 150.0, 22.0] } },

      { "box": { "id": "obj-50", "maxclass": "newobj", "text": "expr $i1 % 120", "patching_rect": [130.0, 238.0, 86.0, 22.0] } },
      { "box": { "id": "obj-51", "maxclass": "newobj", "text": "sel 0 60", "patching_rect": [130.0, 268.0, 56.0, 22.0] } },
      { "box": { "id": "obj-52", "maxclass": "comment", "text": "on every 120 ticks, off at +60", "patching_rect": [198.0, 269.0, 190.0, 20.0] } },

      { "box": { "id": "obj-53", "maxclass": "newobj", "text": "i", "patching_rect": [20.0, 238.0, 24.0, 22.0] } },
      { "box": { "id": "obj-54", "maxclass": "newobj", "text": "i", "patching_rect": [54.0, 238.0, 24.0, 22.0] } },
      { "box": { "id": "obj-55", "maxclass": "newobj", "text": "pak i i", "patching_rect": [20.0, 302.0, 52.0, 22.0] } },
      { "box": { "id": "obj-56", "maxclass": "newobj", "text": "sprintf /NDItracker0/%ld/on %ld", "patching_rect": [20.0, 332.0, 190.0, 22.0] } },

      { "box": { "id": "obj-57", "maxclass": "newobj", "text": "i", "patching_rect": [20.0, 394.0, 24.0, 22.0] } },
      { "box": { "id": "obj-58", "maxclass": "newobj", "text": "i", "patching_rect": [54.0, 394.0, 24.0, 22.0] } },
      { "box": { "id": "obj-59", "maxclass": "newobj", "text": "pak i i", "patching_rect": [20.0, 428.0, 52.0, 22.0] } },
      { "box": { "id": "obj-60", "maxclass": "newobj", "text": "sprintf /NDItracker0/%ld/off %ld", "patching_rect": [20.0, 458.0, 196.0, 22.0] } }
    ],
    "lines": [
      { "patchline": { "source": ["obj-6", 0], "destination": ["obj-2", 0] } },
      { "patchline": { "source": ["obj-2", 0], "destination": ["obj-3", 0] } },
      { "patchline": { "source": ["obj-3", 0], "destination": ["obj-4", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-5", 0] } },

      { "patchline": { "source": ["obj-22", 0], "destination": ["obj-21", 0] } },
      { "patchline": { "source": ["obj-21", 0], "destination": ["obj-17", 0] } },
      { "patchline": { "source": ["obj-21", 0], "destination": ["obj-53", 1] } },
      { "patchline": { "source": ["obj-21", 0], "destination": ["obj-57", 1] } },

      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-10", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-11", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-12", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-13", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-14", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-15", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-16", 0] } },
      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-17", 6] } },

      { "patchline": { "source": ["obj-10", 0], "destination": ["obj-17", 1] } },
      { "patchline": { "source": ["obj-10", 0], "destination": ["obj-54", 1] } },
      { "patchline": { "source": ["obj-10", 0], "destination": ["obj-58", 1] } },
      { "patchline": { "source": ["obj-11", 0], "destination": ["obj-17", 2] } },
      { "patchline": { "source": ["obj-12", 0], "destination": ["obj-17", 3] } },
      { "patchline": { "source": ["obj-13", 0], "destination": ["obj-17", 4] } },
      { "patchline": { "source": ["obj-14", 0], "destination": ["obj-17", 5] } },
      { "patchline": { "source": ["obj-15", 0], "destination": ["obj-17", 7] } },
      { "patchline": { "source": ["obj-16", 0], "destination": ["obj-17", 8] } },

      { "patchline": { "source": ["obj-17", 0], "destination": ["obj-18", 0] } },
      { "patchline": { "source": ["obj-18", 0], "destination": ["obj-40", 0] } },

      { "patchline": { "source": ["obj-4", 0], "destination": ["obj-50", 0] } },
      { "patchline": { "source": ["obj-50", 0], "destination": ["obj-51", 0] } },

      { "patchline": { "source": ["obj-51", 0], "destination": ["obj-53", 0] } },
      { "patchline": { "source": ["obj-53", 0], "destination": ["obj-55", 0] } },
      { "patchline": { "source": ["obj-54", 0], "destination": ["obj-55", 1] } },
      { "patchline": { "source": ["obj-55", 0], "destination": ["obj-56", 0] } },
      { "patchline": { "source": ["obj-56", 0], "destination": ["obj-40", 0] } },

      { "patchline": { "source": ["obj-51", 1], "destination": ["obj-57", 0] } },
      { "patchline": { "source": ["obj-57", 0], "destination": ["obj-59", 0] } },
      { "patchline": { "source": ["obj-58", 0], "destination": ["obj-59", 1] } },
      { "patchline": { "source": ["obj-59", 0], "destination": ["obj-60", 0] } },
      { "patchline": { "source": ["obj-60", 0], "destination": ["obj-40", 0] } }
    ]
  }
}
