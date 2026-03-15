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
      80.0,
      80.0,
      980.0,
      420.0
    ],
    "openinpresentation": 1,
    "default_fontsize": 12.0,
    "default_fontname": "Arial",
    "gridsize": [
      15.0,
      15.0
    ],
    "boxes": [
      {
        "box": {
          "maxclass": "comment",
          "text": "NDI-cv5 Blob 7-8 satellite (Azi/Dist + EdgeNear/EdgeHit mappable)",
          "patching_rect": [
            20.0,
            15.0,
            520.0,
            20.0
          ],
          "id": "obj-1"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "udpreceive 12345",
          "patching_rect": [
            20.0,
            45.0,
            104.0,
            22.0
          ],
          "id": "obj-2"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8 NDITracker9 NDITracker10",
          "patching_rect": [
            20.0,
            75.0,
            760.0,
            22.0
          ],
          "id": "obj-3"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "B7 Control",
          "patching_rect": [
            20.0,
            120.0,
            100.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            8.0,
            120.0,
            20.0
          ],
          "id": "obj-4"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f",
          "patching_rect": [
            20.0,
            144.0,
            145.0,
            22.0
          ],
          "id": "obj-5"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "Azi",
          "patching_rect": [
            20.0,
            178.0,
            28.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            34.0,
            36.0,
            20.0
          ],
          "id": "obj-6"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            54.0,
            176.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B7_Azi",
          "presentation": 1,
          "presentation_rect": [
            60.0,
            34.0,
            86.0,
            18.0
          ],
          "id": "obj-7"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "Dist",
          "patching_rect": [
            154.0,
            178.0,
            30.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            60.0,
            36.0,
            20.0
          ],
          "id": "obj-8"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            186.0,
            176.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B7_Dist",
          "presentation": 1,
          "presentation_rect": [
            60.0,
            60.0,
            86.0,
            18.0
          ],
          "id": "obj-9"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))",
          "patching_rect": [
            20.0,
            208.0,
            236.0,
            22.0
          ],
          "id": "obj-10"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "scale 0. 1. 0. 100.",
          "patching_rect": [
            20.0,
            236.0,
            120.0,
            22.0
          ],
          "id": "obj-11"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "EdgeIn",
          "patching_rect": [
            226.0,
            240.0,
            54.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            86.0,
            48.0,
            20.0
          ],
          "id": "obj-12"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            168.0,
            238.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B7_EdgeNear",
          "presentation": 1,
          "presentation_rect": [
            70.0,
            86.0,
            86.0,
            18.0
          ],
          "id": "obj-13"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr ($f1>=0.985)*100.",
          "patching_rect": [
            20.0,
            266.0,
            145.0,
            22.0
          ],
          "id": "obj-14"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "EdgeHit",
          "patching_rect": [
            270.0,
            270.0,
            56.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            112.0,
            56.0,
            20.0
          ],
          "id": "obj-15"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            192.0,
            268.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B7_EdgeHit",
          "presentation": 1,
          "presentation_rect": [
            70.0,
            112.0,
            86.0,
            18.0
          ],
          "id": "obj-16"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "B8 Control",
          "patching_rect": [
            360.0,
            120.0,
            100.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            248.0,
            8.0,
            120.0,
            20.0
          ],
          "id": "obj-17"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f",
          "patching_rect": [
            360.0,
            144.0,
            145.0,
            22.0
          ],
          "id": "obj-18"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "Azi",
          "patching_rect": [
            360.0,
            178.0,
            28.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            248.0,
            34.0,
            36.0,
            20.0
          ],
          "id": "obj-19"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            394.0,
            176.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B8_Azi",
          "presentation": 1,
          "presentation_rect": [
            290.0,
            34.0,
            86.0,
            18.0
          ],
          "id": "obj-20"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "Dist",
          "patching_rect": [
            494.0,
            178.0,
            30.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            248.0,
            60.0,
            36.0,
            20.0
          ],
          "id": "obj-21"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            526.0,
            176.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B8_Dist",
          "presentation": 1,
          "presentation_rect": [
            290.0,
            60.0,
            86.0,
            18.0
          ],
          "id": "obj-22"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))",
          "patching_rect": [
            360.0,
            208.0,
            236.0,
            22.0
          ],
          "id": "obj-23"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "scale 0. 1. 0. 100.",
          "patching_rect": [
            360.0,
            236.0,
            120.0,
            22.0
          ],
          "id": "obj-24"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "EdgeIn",
          "patching_rect": [
            566.0,
            240.0,
            54.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            248.0,
            86.0,
            48.0,
            20.0
          ],
          "id": "obj-25"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            508.0,
            238.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B8_EdgeNear",
          "presentation": 1,
          "presentation_rect": [
            300.0,
            86.0,
            86.0,
            18.0
          ],
          "id": "obj-26"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr ($f1>=0.985)*100.",
          "patching_rect": [
            360.0,
            266.0,
            145.0,
            22.0
          ],
          "id": "obj-27"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "EdgeHit",
          "patching_rect": [
            610.0,
            270.0,
            56.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            248.0,
            112.0,
            56.0,
            20.0
          ],
          "id": "obj-28"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "patching_rect": [
            532.0,
            268.0,
            72.0,
            18.0
          ],
          "parameter_enable": 1,
          "varname": "B8_EdgeHit",
          "presentation": 1,
          "presentation_rect": [
            300.0,
            112.0,
            86.0,
            18.0
          ],
          "id": "obj-29"
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
            "obj-3",
            6
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
            6
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
            7
          ],
          "destination": [
            "obj-9",
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
            "obj-10",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-5",
            2
          ],
          "destination": [
            "obj-10",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-10",
            0
          ],
          "destination": [
            "obj-11",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-11",
            0
          ],
          "destination": [
            "obj-13",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-10",
            0
          ],
          "destination": [
            "obj-14",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-14",
            0
          ],
          "destination": [
            "obj-16",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-3",
            7
          ],
          "destination": [
            "obj-18",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-18",
            6
          ],
          "destination": [
            "obj-20",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-18",
            7
          ],
          "destination": [
            "obj-22",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-18",
            1
          ],
          "destination": [
            "obj-23",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-18",
            2
          ],
          "destination": [
            "obj-23",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-23",
            0
          ],
          "destination": [
            "obj-24",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-24",
            0
          ],
          "destination": [
            "obj-26",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-23",
            0
          ],
          "destination": [
            "obj-27",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-27",
            0
          ],
          "destination": [
            "obj-29",
            0
          ]
        }
      }
    ]
  }
}