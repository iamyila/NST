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
    "rect": [
      34.0,
      87.0,
      1200.0,
      700.0
    ],
    "openinpresentation": 0,
    "default_fontsize": 12.0,
    "default_fontface": 0,
    "default_fontname": "Arial",
    "gridonopen": 1,
    "gridsize": [
      15.0,
      15.0
    ],
    "gridsnaponopen": 1,
    "toolbarvisible": 1,
    "boxes": [
      {
        "box": {
          "id": "obj-1",
          "maxclass": "newobj",
          "text": "udpreceive 12345",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            40.0,
            40.0,
            95.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-2",
          "maxclass": "newobj",
          "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8 NDITracker9 NDITracker10",
          "numinlets": 11,
          "numoutlets": 11,
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            40.0,
            80.0,
            780.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-3",
          "maxclass": "button",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "bang"
          ],
          "patching_rect": [
            40.0,
            130.0,
            24.0,
            24.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-4",
          "maxclass": "message",
          "text": "60",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            80.0,
            132.0,
            35.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-5",
          "maxclass": "newobj",
          "text": "makenote 100 120",
          "numinlets": 3,
          "numoutlets": 2,
          "outlettype": [
            "int",
            "int"
          ],
          "patching_rect": [
            130.0,
            132.0,
            105.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-6",
          "maxclass": "newobj",
          "text": "noteout",
          "numinlets": 3,
          "numoutlets": 0,
          "patching_rect": [
            250.0,
            132.0,
            50.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-7",
          "maxclass": "newobj",
          "text": "print T1_HIT",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            40.0,
            180.0,
            80.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-8",
          "maxclass": "newobj",
          "text": "counter",
          "numinlets": 5,
          "numoutlets": 4,
          "outlettype": [
            "int",
            "",
            "",
            "int"
          ],
          "patching_rect": [
            140.0,
            180.0,
            55.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-9",
          "maxclass": "number",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            210.0,
            180.0,
            50.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-10",
          "maxclass": "comment",
          "text": "STEP 1: any /NDITracker1 packet triggers MIDI note 60 (auto note-off via makenote)",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            40.0,
            10.0,
            560.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-11",
          "maxclass": "comment",
          "text": "If this works, we add clean on/off logic next.",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            40.0,
            215.0,
            280.0,
            20.0
          ]
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "source": [
            "obj-1",
            0
          ],
          "destination": [
            "obj-2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            0
          ],
          "destination": [
            "obj-3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-3",
            0
          ],
          "destination": [
            "obj-4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-4",
            0
          ],
          "destination": [
            "obj-5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-5",
            0
          ],
          "destination": [
            "obj-6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-5",
            1
          ],
          "destination": [
            "obj-6",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            0
          ],
          "destination": [
            "obj-7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            0
          ],
          "destination": [
            "obj-8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            0
          ],
          "destination": [
            "obj-9",
            0
          ]
        }
      }
    ]
  }
}