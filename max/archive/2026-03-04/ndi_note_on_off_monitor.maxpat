{
  "patcher": {
    "fileversion": 1,
    "appversion": {
      "major": 8,
      "minor": 6,
      "revision": 0,
      "architecture": "x64",
      "modernui": 1
    },
    "classnamespace": "box",
    "rect": [
      48.0,
      102.0,
      1000.0,
      460.0
    ],
    "bglocked": 0,
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
          "maxclass": "comment",
          "patching_rect": [
            20.0,
            10.0,
            420.0,
            20.0
          ],
          "text": "NDI-cv5 Note Monitor (fixes oscparse/list routing)"
        }
      },
      {
        "box": {
          "id": "obj-2",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            40.0,
            110.0,
            22.0
          ],
          "text": "udpreceive 12345"
        }
      },
      {
        "box": {
          "id": "obj-3",
          "maxclass": "newobj",
          "patching_rect": [
            150.0,
            40.0,
            110.0,
            22.0
          ],
          "text": "print UDP_PACKET"
        }
      },
      {
        "box": {
          "id": "obj-4",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            70.0,
            70.0,
            22.0
          ],
          "text": "oscparse"
        }
      },
      {
        "box": {
          "id": "obj-5",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            100.0,
            70.0,
            22.0
          ],
          "text": "route list"
        }
      },
      {
        "box": {
          "id": "obj-6",
          "maxclass": "newobj",
          "patching_rect": [
            110.0,
            100.0,
            100.0,
            22.0
          ],
          "text": "print OSC_LIST"
        }
      },
      {
        "box": {
          "id": "obj-7",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            150.0,
            760.0,
            22.0
          ],
          "text": "route /NDITracker1/1/on /NDITracker1/2/on /NDITracker1/3/on /NDITracker1/4/on /NDITracker1/5/on /NDITracker1/6/on /NDITracker1/7/on /NDITracker1/8/on /NDITracker1/9/on /NDITracker1/10/on"
        }
      },
      {
        "box": {
          "id": "obj-8",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            300.0,
            760.0,
            22.0
          ],
          "text": "route /NDITracker1/1/off /NDITracker1/2/off /NDITracker1/3/off /NDITracker1/4/off /NDITracker1/5/off /NDITracker1/6/off /NDITracker1/7/off /NDITracker1/8/off /NDITracker1/9/off /NDITracker1/10/off"
        }
      },
      {
        "box": {
          "id": "obj-on-1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_1"
        }
      },
      {
        "box": {
          "id": "obj-on-2",
          "maxclass": "newobj",
          "patching_rect": [
            95.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_2"
        }
      },
      {
        "box": {
          "id": "obj-on-3",
          "maxclass": "newobj",
          "patching_rect": [
            170.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_3"
        }
      },
      {
        "box": {
          "id": "obj-on-4",
          "maxclass": "newobj",
          "patching_rect": [
            245.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_4"
        }
      },
      {
        "box": {
          "id": "obj-on-5",
          "maxclass": "newobj",
          "patching_rect": [
            320.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_5"
        }
      },
      {
        "box": {
          "id": "obj-on-6",
          "maxclass": "newobj",
          "patching_rect": [
            395.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_6"
        }
      },
      {
        "box": {
          "id": "obj-on-7",
          "maxclass": "newobj",
          "patching_rect": [
            470.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_7"
        }
      },
      {
        "box": {
          "id": "obj-on-8",
          "maxclass": "newobj",
          "patching_rect": [
            545.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_8"
        }
      },
      {
        "box": {
          "id": "obj-on-9",
          "maxclass": "newobj",
          "patching_rect": [
            620.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_9"
        }
      },
      {
        "box": {
          "id": "obj-on-10",
          "maxclass": "newobj",
          "patching_rect": [
            695.0,
            200.0,
            70.0,
            22.0
          ],
          "text": "print ON_10"
        }
      },
      {
        "box": {
          "id": "obj-off-1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_1"
        }
      },
      {
        "box": {
          "id": "obj-off-2",
          "maxclass": "newobj",
          "patching_rect": [
            95.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_2"
        }
      },
      {
        "box": {
          "id": "obj-off-3",
          "maxclass": "newobj",
          "patching_rect": [
            170.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_3"
        }
      },
      {
        "box": {
          "id": "obj-off-4",
          "maxclass": "newobj",
          "patching_rect": [
            245.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_4"
        }
      },
      {
        "box": {
          "id": "obj-off-5",
          "maxclass": "newobj",
          "patching_rect": [
            320.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_5"
        }
      },
      {
        "box": {
          "id": "obj-off-6",
          "maxclass": "newobj",
          "patching_rect": [
            395.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_6"
        }
      },
      {
        "box": {
          "id": "obj-off-7",
          "maxclass": "newobj",
          "patching_rect": [
            470.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_7"
        }
      },
      {
        "box": {
          "id": "obj-off-8",
          "maxclass": "newobj",
          "patching_rect": [
            545.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_8"
        }
      },
      {
        "box": {
          "id": "obj-off-9",
          "maxclass": "newobj",
          "patching_rect": [
            620.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_9"
        }
      },
      {
        "box": {
          "id": "obj-off-10",
          "maxclass": "newobj",
          "patching_rect": [
            695.0,
            350.0,
            75.0,
            22.0
          ],
          "text": "print OFF_10"
        }
      },
      {
        "box": {
          "id": "obj-9",
          "maxclass": "comment",
          "patching_rect": [
            20.0,
            390.0,
            640.0,
            20.0
          ],
          "text": "If OSC_LIST prints but ON/OFF does not: address mismatch. Must be /NDITracker1 (capital T)."
        }
      },
      {
        "box": {
          "id": "obj-10",
          "maxclass": "comment",
          "patching_rect": [
            20.0,
            410.0,
            620.0,
            20.0
          ],
          "text": "If UDP_PACKET prints but OSC_LIST does not: packet is not valid OSC for oscparse."
        }
      }
    ],
    "lines": [
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
            "obj-2",
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
            "obj-5",
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
            "obj-7",
            0
          ],
          "destination": [
            "obj-on-1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            1
          ],
          "destination": [
            "obj-on-2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            2
          ],
          "destination": [
            "obj-on-3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            3
          ],
          "destination": [
            "obj-on-4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            4
          ],
          "destination": [
            "obj-on-5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            5
          ],
          "destination": [
            "obj-on-6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            6
          ],
          "destination": [
            "obj-on-7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            7
          ],
          "destination": [
            "obj-on-8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            8
          ],
          "destination": [
            "obj-on-9",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-7",
            9
          ],
          "destination": [
            "obj-on-10",
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
            "obj-off-1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            1
          ],
          "destination": [
            "obj-off-2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            2
          ],
          "destination": [
            "obj-off-3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            3
          ],
          "destination": [
            "obj-off-4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            4
          ],
          "destination": [
            "obj-off-5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            5
          ],
          "destination": [
            "obj-off-6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            6
          ],
          "destination": [
            "obj-off-7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            7
          ],
          "destination": [
            "obj-off-8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            8
          ],
          "destination": [
            "obj-off-9",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-8",
            9
          ],
          "destination": [
            "obj-off-10",
            0
          ]
        }
      }
    ]
  }
}