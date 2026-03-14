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
      120.0,
      120.0,
      560.0,
      360.0
    ],
    "gridsize": [
      15.0,
      15.0
    ],
    "boxes": [
      {
        "box": {
          "id": "obj-1",
          "maxclass": "comment",
          "text": "Merge Event Note",
          "patching_rect": [
            20.0,
            15.0,
            160.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            10.0,
            8.0,
            150.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-2",
          "maxclass": "newobj",
          "text": "udpreceive 12345",
          "patching_rect": [
            20.0,
            48.0,
            104.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-3",
          "maxclass": "newobj",
          "text": "route NDITrackerMerge NDITrackerDeath",
          "patching_rect": [
            20.0,
            80.0,
            235.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-4",
          "maxclass": "newobj",
          "text": "t l l",
          "patching_rect": [
            20.0,
            112.0,
            34.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-5",
          "maxclass": "newobj",
          "text": "print MERGE_EVENT",
          "patching_rect": [
            66.0,
            112.0,
            118.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-6",
          "maxclass": "newobj",
          "text": "t b b",
          "patching_rect": [
            20.0,
            148.0,
            35.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-7",
          "maxclass": "number",
          "patching_rect": [
            290.0,
            52.0,
            52.0,
            22.0
          ],
          "presentation": 1,
          "presentation_rect": [
            10.0,
            56.0,
            62.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-8",
          "maxclass": "number",
          "patching_rect": [
            350.0,
            52.0,
            52.0,
            22.0
          ],
          "presentation": 1,
          "presentation_rect": [
            88.0,
            56.0,
            62.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-9",
          "maxclass": "number",
          "patching_rect": [
            410.0,
            52.0,
            52.0,
            22.0
          ],
          "presentation": 1,
          "presentation_rect": [
            166.0,
            56.0,
            62.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-10",
          "maxclass": "comment",
          "text": "Note",
          "patching_rect": [
            290.0,
            30.0,
            35.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            10.0,
            34.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-11",
          "maxclass": "comment",
          "text": "Vel",
          "patching_rect": [
            350.0,
            30.0,
            35.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            88.0,
            34.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-12",
          "maxclass": "comment",
          "text": "Dur",
          "patching_rect": [
            410.0,
            30.0,
            55.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            166.0,
            34.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-13",
          "maxclass": "newobj",
          "text": "loadmess 65",
          "patching_rect": [
            290.0,
            82.0,
            75.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-14",
          "maxclass": "newobj",
          "text": "loadmess 100",
          "patching_rect": [
            370.0,
            82.0,
            83.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-15",
          "maxclass": "newobj",
          "text": "loadmess 120",
          "patching_rect": [
            458.0,
            82.0,
            83.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-16",
          "maxclass": "newobj",
          "text": "pack i i",
          "patching_rect": [
            20.0,
            188.0,
            58.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-17",
          "maxclass": "newobj",
          "text": "delay",
          "patching_rect": [
            90.0,
            188.0,
            44.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-18",
          "maxclass": "newobj",
          "text": "pack i i",
          "patching_rect": [
            90.0,
            222.0,
            58.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-19",
          "maxclass": "message",
          "text": "0",
          "patching_rect": [
            156.0,
            222.0,
            30.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-20",
          "maxclass": "newobj",
          "text": "noteout",
          "patching_rect": [
            20.0,
            264.0,
            55.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-21",
          "maxclass": "newobj",
          "text": "unpack i i i",
          "patching_rect": [
            20.0,
            146.0,
            78.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-22",
          "maxclass": "newobj",
          "text": "expr (($i1 >= 2) && ($i2 == 1))",
          "patching_rect": [
            20.0,
            178.0,
            174.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-23",
          "maxclass": "newobj",
          "text": "speedlim",
          "patching_rect": [
            20.0,
            210.0,
            58.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-24",
          "maxclass": "newobj",
          "text": "sel 1",
          "patching_rect": [
            20.0,
            242.0,
            36.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-25",
          "maxclass": "comment",
          "text": "fires only when 2+ blobs collapse to 1",
          "patching_rect": [
            120.0,
            210.0,
            220.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-26",
          "maxclass": "comment",
          "text": "Cool",
          "patching_rect": [
            470.0,
            30.0,
            40.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            244.0,
            34.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-27",
          "maxclass": "number",
          "patching_rect": [
            470.0,
            52.0,
            62.0,
            22.0
          ],
          "presentation": 1,
          "presentation_rect": [
            244.0,
            56.0,
            70.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-28",
          "maxclass": "newobj",
          "text": "loadmess 250",
          "patching_rect": [
            470.0,
            82.0,
            83.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-29",
          "maxclass": "newobj",
          "text": "t l b",
          "patching_rect": [
            270.0,
            112.0,
            35.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-30",
          "maxclass": "newobj",
          "text": "print DEATH_EVENT",
          "patching_rect": [
            317.0,
            112.0,
            121.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-32",
          "maxclass": "live.toggle",
          "annotation": "Choose Merge or Death trigger mode.",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "outputmode": 1,
          "parameter_enable": 1,
          "patching_rect": [
            328.0,
            56.0,
            24.0,
            24.0
          ],
          "presentation": 1,
          "presentation_rect": [
            326.0,
            54.0,
            24.0,
            24.0
          ],
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_enum": [
                "Merge",
                "Death"
              ],
              "parameter_initial": [
                0
              ],
              "parameter_initial_enable": 1,
              "parameter_longname": "Merge/Death Mode",
              "parameter_mmax": 1,
              "parameter_modmode": 0,
              "parameter_shortname": "Mode",
              "parameter_type": 2
            }
          },
          "varname": "merge_death_mode"
        }
      },
      {
        "box": {
          "id": "obj-34",
          "maxclass": "comment",
          "text": "Mode",
          "patching_rect": [
            328.0,
            12.0,
            44.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            326.0,
            8.0,
            44.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-35",
          "maxclass": "comment",
          "text": "Merge",
          "patching_rect": [
            358.0,
            34.0,
            50.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            356.0,
            34.0,
            50.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-36",
          "maxclass": "comment",
          "text": "Death",
          "patching_rect": [
            358.0,
            58.0,
            50.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            356.0,
            58.0,
            50.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-37",
          "maxclass": "newobj",
          "text": "loadmess 0",
          "patching_rect": [
            366.0,
            86.0,
            75.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-61",
          "maxclass": "newobj",
          "text": "== 0",
          "patching_rect": [
            328.0,
            86.0,
            33.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-62",
          "maxclass": "newobj",
          "text": "== 1",
          "patching_rect": [
            366.0,
            86.0,
            33.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-63",
          "maxclass": "newobj",
          "text": "spigot 1",
          "patching_rect": [
            20.0,
            272.0,
            54.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-64",
          "maxclass": "newobj",
          "text": "spigot 0",
          "patching_rect": [
            88.0,
            272.0,
            54.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-65",
          "maxclass": "newobj",
          "text": "t b",
          "patching_rect": [
            20.0,
            304.0,
            24.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-66",
          "maxclass": "newobj",
          "text": "t b",
          "patching_rect": [
            88.0,
            304.0,
            24.0,
            22.0
          ]
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
            "obj-6",
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
            "obj-6",
            1
          ],
          "destination": [
            "obj-17",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-17",
            0
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
            "obj-16",
            0
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
            0
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
            "obj-7",
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
            "obj-7",
            0
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
            "obj-8",
            0
          ],
          "destination": [
            "obj-16",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-9",
            0
          ],
          "destination": [
            "obj-17",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-19",
            0
          ],
          "destination": [
            "obj-18",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-13",
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
            "obj-14",
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
            "obj-15",
            0
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
            "obj-4",
            0
          ],
          "destination": [
            "obj-21",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-4",
            1
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
            "obj-21",
            0
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
            "obj-21",
            1
          ],
          "destination": [
            "obj-22",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-22",
            0
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
            "obj-27",
            0
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
            "obj-28",
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
            "obj-3",
            1
          ],
          "destination": [
            "obj-29",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-29",
            0
          ],
          "destination": [
            "obj-30",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-37",
            0
          ],
          "destination": [
            "obj-32",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-32",
            0
          ],
          "destination": [
            "obj-61",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-32",
            0
          ],
          "destination": [
            "obj-62",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-61",
            0
          ],
          "destination": [
            "obj-63",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-62",
            0
          ],
          "destination": [
            "obj-64",
            1
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
            "obj-63",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-29",
            1
          ],
          "destination": [
            "obj-64",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-63",
            0
          ],
          "destination": [
            "obj-65",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-64",
            0
          ],
          "destination": [
            "obj-66",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-65",
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
            "obj-66",
            0
          ],
          "destination": [
            "obj-6",
            0
          ]
        }
      }
    ],
    "openrect": [
      0.0,
      0.0,
      430.0,
      92.0
    ],
    "openrectmode": 0,
    "default_fontsize": 12.0,
    "default_fontface": 0,
    "default_fontname": "Arial",
    "devicewidth": 430.0,
    "openinpresentation": 1,
    "bglocked": 1,
    "name": "ndi_merge_event_note",
    "title": "ndi_merge_event_note",
    "digest": "Merge/death note trigger device"
  }
}