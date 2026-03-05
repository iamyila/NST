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
    "rect": [
      34.0,
      87.0,
      1900.0,
      900.0
    ],
    "openinpresentation": 1,
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
          "id": "c0",
          "maxclass": "comment",
          "patching_rect": [
            40.0,
            10.0,
            560.0,
            20.0
          ],
          "text": "Blob1+Blob2+Blob3: notes from alive edges only; XY mappable separately"
        }
      },
      {
        "box": {
          "id": "obj-1",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            40.0,
            95.0,
            22.0
          ],
          "text": "udpreceive 12345"
        }
      },
      {
        "box": {
          "id": "obj-2",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            75.0,
            790.0,
            22.0
          ],
          "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8 NDITracker9 NDITracker10"
        }
      },
      {
        "box": {
          "id": "b1_tlb",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            120.0,
            40.0,
            22.0
          ],
          "text": "t l b"
        }
      },
      {
        "box": {
          "id": "b1_alive_t",
          "maxclass": "newobj",
          "patching_rect": [
            95.0,
            120.0,
            50.0,
            22.0
          ],
          "text": "t b b b"
        }
      },
      {
        "box": {
          "id": "b1_stop",
          "maxclass": "message",
          "patching_rect": [
            160.0,
            152.0,
            40.0,
            22.0
          ],
          "text": "stop"
        }
      },
      {
        "box": {
          "id": "b1_delay",
          "maxclass": "newobj",
          "patching_rect": [
            210.0,
            152.0,
            65.0,
            22.0
          ],
          "text": "delay 220"
        }
      },
      {
        "box": {
          "id": "b1_1",
          "maxclass": "message",
          "patching_rect": [
            95.0,
            152.0,
            30.0,
            22.0
          ],
          "text": "1"
        }
      },
      {
        "box": {
          "id": "b1_0",
          "maxclass": "message",
          "patching_rect": [
            285.0,
            152.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b1_alive_ch",
          "maxclass": "newobj",
          "patching_rect": [
            135.0,
            187.0,
            50.0,
            22.0
          ],
          "text": "change"
        }
      },
      {
        "box": {
          "id": "b1_sel",
          "maxclass": "newobj",
          "patching_rect": [
            135.0,
            222.0,
            60.0,
            22.0
          ],
          "text": "sel 1 0"
        }
      },
      {
        "box": {
          "id": "b1_unpack",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            152.0,
            130.0,
            22.0
          ],
          "text": "unpack i f f f f i f f"
        }
      },
      {
        "box": {
          "id": "b1_label_ch",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            187.0,
            50.0,
            22.0
          ],
          "text": "change"
        }
      },
      {
        "box": {
          "id": "b1_lbl_t",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            222.0,
            40.0,
            22.0
          ],
          "text": "t b b"
        }
      },
      {
        "box": {
          "id": "b1_delay1",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            257.0,
            50.0,
            22.0
          ],
          "text": "delay 1"
        }
      },
      {
        "box": {
          "id": "b1_on",
          "maxclass": "message",
          "patching_rect": [
            220.0,
            295.0,
            55.0,
            22.0
          ],
          "text": "60 100"
        }
      },
      {
        "box": {
          "id": "b1_off",
          "maxclass": "message",
          "patching_rect": [
            285.0,
            295.0,
            45.0,
            22.0
          ],
          "text": "60 0"
        }
      },
      {
        "box": {
          "id": "b1_pkt",
          "maxclass": "newobj",
          "patching_rect": [
            370.0,
            120.0,
            90.0,
            22.0
          ],
          "text": "print BLOB1_PKT"
        }
      },
      {
        "box": {
          "id": "b1_lbl",
          "maxclass": "newobj",
          "patching_rect": [
            100.0,
            187.0,
            100.0,
            22.0
          ],
          "text": "print BLOB1_LABEL"
        }
      },
      {
        "box": {
          "id": "b2_tlb",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            120.0,
            40.0,
            22.0
          ],
          "text": "t l b"
        }
      },
      {
        "box": {
          "id": "b2_alive_t",
          "maxclass": "newobj",
          "patching_rect": [
            815.0,
            120.0,
            50.0,
            22.0
          ],
          "text": "t b b b"
        }
      },
      {
        "box": {
          "id": "b2_stop",
          "maxclass": "message",
          "patching_rect": [
            880.0,
            152.0,
            40.0,
            22.0
          ],
          "text": "stop"
        }
      },
      {
        "box": {
          "id": "b2_delay",
          "maxclass": "newobj",
          "patching_rect": [
            930.0,
            152.0,
            65.0,
            22.0
          ],
          "text": "delay 220"
        }
      },
      {
        "box": {
          "id": "b2_1",
          "maxclass": "message",
          "patching_rect": [
            815.0,
            152.0,
            30.0,
            22.0
          ],
          "text": "1"
        }
      },
      {
        "box": {
          "id": "b2_0",
          "maxclass": "message",
          "patching_rect": [
            1005.0,
            152.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b2_alive_ch",
          "maxclass": "newobj",
          "patching_rect": [
            855.0,
            187.0,
            50.0,
            22.0
          ],
          "text": "change"
        }
      },
      {
        "box": {
          "id": "b2_sel",
          "maxclass": "newobj",
          "patching_rect": [
            855.0,
            222.0,
            60.0,
            22.0
          ],
          "text": "sel 1 0"
        }
      },
      {
        "box": {
          "id": "b2_unpack",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            152.0,
            130.0,
            22.0
          ],
          "text": "unpack i f f f f i f f"
        }
      },
      {
        "box": {
          "id": "b2_label_ch",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            187.0,
            50.0,
            22.0
          ],
          "text": "change"
        }
      },
      {
        "box": {
          "id": "b2_lbl_t",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            222.0,
            40.0,
            22.0
          ],
          "text": "t b b"
        }
      },
      {
        "box": {
          "id": "b2_delay1",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            257.0,
            50.0,
            22.0
          ],
          "text": "delay 1"
        }
      },
      {
        "box": {
          "id": "b2_on",
          "maxclass": "message",
          "patching_rect": [
            940.0,
            295.0,
            55.0,
            22.0
          ],
          "text": "62 100"
        }
      },
      {
        "box": {
          "id": "b2_off",
          "maxclass": "message",
          "patching_rect": [
            1005.0,
            295.0,
            45.0,
            22.0
          ],
          "text": "62 0"
        }
      },
      {
        "box": {
          "id": "b2_pkt",
          "maxclass": "newobj",
          "patching_rect": [
            1090.0,
            120.0,
            90.0,
            22.0
          ],
          "text": "print BLOB2_PKT"
        }
      },
      {
        "box": {
          "id": "b2_lbl",
          "maxclass": "newobj",
          "patching_rect": [
            820.0,
            187.0,
            100.0,
            22.0
          ],
          "text": "print BLOB2_LABEL"
        }
      },
      {
        "box": {
          "id": "obj-40",
          "maxclass": "newobj",
          "patching_rect": [
            580.0,
            340.0,
            65.0,
            22.0
          ],
          "text": "unpack i i"
        }
      },
      {
        "box": {
          "id": "obj-41",
          "maxclass": "newobj",
          "patching_rect": [
            580.0,
            375.0,
            50.0,
            22.0
          ],
          "text": "noteout"
        }
      },
      {
        "box": {
          "id": "obj-42",
          "maxclass": "newobj",
          "patching_rect": [
            650.0,
            340.0,
            95.0,
            22.0
          ],
          "text": "print NOTE_EVENT"
        }
      },
      {
        "box": {
          "id": "b3_tlb",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            120.0,
            40.0,
            22.0
          ],
          "text": "t l b"
        }
      },
      {
        "box": {
          "id": "b3_alive_t",
          "maxclass": "newobj",
          "patching_rect": [
            1175.0,
            120.0,
            50.0,
            22.0
          ],
          "text": "t b b b"
        }
      },
      {
        "box": {
          "id": "b3_stop",
          "maxclass": "message",
          "patching_rect": [
            1240.0,
            152.0,
            40.0,
            22.0
          ],
          "text": "stop"
        }
      },
      {
        "box": {
          "id": "b3_delay",
          "maxclass": "newobj",
          "patching_rect": [
            1290.0,
            152.0,
            65.0,
            22.0
          ],
          "text": "delay 220"
        }
      },
      {
        "box": {
          "id": "b3_1",
          "maxclass": "message",
          "patching_rect": [
            1175.0,
            152.0,
            30.0,
            22.0
          ],
          "text": "1"
        }
      },
      {
        "box": {
          "id": "b3_0",
          "maxclass": "message",
          "patching_rect": [
            1365.0,
            152.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b3_alive_ch",
          "maxclass": "newobj",
          "patching_rect": [
            1215.0,
            187.0,
            50.0,
            22.0
          ],
          "text": "change"
        }
      },
      {
        "box": {
          "id": "b3_sel",
          "maxclass": "newobj",
          "patching_rect": [
            1215.0,
            222.0,
            60.0,
            22.0
          ],
          "text": "sel 1 0"
        }
      },
      {
        "box": {
          "id": "b3_unpack",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            152.0,
            130.0,
            22.0
          ],
          "text": "unpack i f f f f i f f"
        }
      },
      {
        "box": {
          "id": "b3_label_ch",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            187.0,
            50.0,
            22.0
          ],
          "text": "change"
        }
      },
      {
        "box": {
          "id": "b3_lbl_t",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            222.0,
            40.0,
            22.0
          ],
          "text": "t b b"
        }
      },
      {
        "box": {
          "id": "b3_delay1",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            257.0,
            50.0,
            22.0
          ],
          "text": "delay 1"
        }
      },
      {
        "box": {
          "id": "b3_on",
          "maxclass": "message",
          "patching_rect": [
            1300.0,
            295.0,
            55.0,
            22.0
          ],
          "text": "64 100"
        }
      },
      {
        "box": {
          "id": "b3_off",
          "maxclass": "message",
          "patching_rect": [
            1365.0,
            295.0,
            45.0,
            22.0
          ],
          "text": "64 0"
        }
      },
      {
        "box": {
          "id": "b3_pkt",
          "maxclass": "newobj",
          "patching_rect": [
            1450.0,
            120.0,
            90.0,
            22.0
          ],
          "text": "print BLOB3_PKT"
        }
      },
      {
        "box": {
          "id": "b3_lbl",
          "maxclass": "newobj",
          "patching_rect": [
            1180.0,
            187.0,
            100.0,
            22.0
          ],
          "text": "print BLOB3_LABEL"
        }
      },
      {
        "box": {
          "id": "b1_xy_comment",
          "maxclass": "comment",
          "patching_rect": [
            40.0,
            340.0,
            220.0,
            20.0
          ],
          "text": "B1",
          "presentation": 1,
          "presentation_rect": [
            2.0,
            18.0,
            20.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_x_clip",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            365.0,
            65.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b1_x_map",
          "maxclass": "live.numbox",
          "patching_rect": [
            185.0,
            365.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            ""
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "Blob1 X",
              "parameter_shortname": "B1 X",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_type": 0,
              "parameter_modmode": 0,
              "parameter_initial": [
                0.0
              ],
              "parameter_initial_enable": 1,
              "parameter_invisible": 0
            }
          },
          "varname": "blob1_x",
          "presentation": 1,
          "parameter_type": 0,
          "presentation_rect": [
            24.0,
            16.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_y_clip",
          "maxclass": "newobj",
          "patching_rect": [
            40.0,
            395.0,
            65.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b1_y_map",
          "maxclass": "live.numbox",
          "patching_rect": [
            185.0,
            395.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            ""
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "Blob1 Y",
              "parameter_shortname": "B1 Y",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_type": 0,
              "parameter_modmode": 0,
              "parameter_initial": [
                0.0
              ],
              "parameter_initial_enable": 1,
              "parameter_invisible": 0
            }
          },
          "varname": "blob1_y",
          "presentation": 1,
          "parameter_type": 0,
          "presentation_rect": [
            84.0,
            16.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_x_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            110.0,
            365.0,
            70.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "b1_y_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            110.0,
            395.0,
            70.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "b2_xy_comment",
          "maxclass": "comment",
          "patching_rect": [
            760.0,
            340.0,
            220.0,
            20.0
          ],
          "text": "B2",
          "presentation": 1,
          "presentation_rect": [
            2.0,
            46.0,
            20.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "b2_x_clip",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            365.0,
            65.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b2_x_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            830.0,
            365.0,
            70.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "b2_x_map",
          "maxclass": "live.numbox",
          "patching_rect": [
            905.0,
            365.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            ""
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "Blob2 X",
              "parameter_shortname": "B2 X",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_type": 0,
              "parameter_modmode": 0,
              "parameter_initial": [
                0.0
              ],
              "parameter_initial_enable": 1,
              "parameter_invisible": 0
            }
          },
          "varname": "blob2_x",
          "presentation": 1,
          "parameter_type": 0,
          "presentation_rect": [
            24.0,
            44.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b2_y_clip",
          "maxclass": "newobj",
          "patching_rect": [
            760.0,
            395.0,
            65.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b2_y_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            830.0,
            395.0,
            70.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "b2_y_map",
          "maxclass": "live.numbox",
          "patching_rect": [
            905.0,
            395.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            ""
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "Blob2 Y",
              "parameter_shortname": "B2 Y",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_type": 0,
              "parameter_modmode": 0,
              "parameter_initial": [
                0.0
              ],
              "parameter_initial_enable": 1,
              "parameter_invisible": 0
            }
          },
          "varname": "blob2_y",
          "presentation": 1,
          "parameter_type": 0,
          "presentation_rect": [
            84.0,
            44.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b3_xy_comment",
          "maxclass": "comment",
          "patching_rect": [
            1120.0,
            340.0,
            220.0,
            20.0
          ],
          "text": "B3",
          "presentation": 1,
          "presentation_rect": [
            2.0,
            74.0,
            20.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "b3_x_clip",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            365.0,
            65.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b3_x_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            1190.0,
            365.0,
            70.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "b3_x_map",
          "maxclass": "live.numbox",
          "patching_rect": [
            1265.0,
            365.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            ""
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "Blob3 X",
              "parameter_shortname": "B3 X",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_type": 0,
              "parameter_modmode": 0,
              "parameter_initial": [
                0.0
              ],
              "parameter_initial_enable": 1,
              "parameter_invisible": 0
            }
          },
          "varname": "blob3_x",
          "presentation": 1,
          "parameter_type": 0,
          "presentation_rect": [
            24.0,
            72.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b3_y_clip",
          "maxclass": "newobj",
          "patching_rect": [
            1120.0,
            395.0,
            65.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b3_y_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            1190.0,
            395.0,
            70.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "b3_y_map",
          "maxclass": "live.numbox",
          "patching_rect": [
            1265.0,
            395.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            ""
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "Blob3 Y",
              "parameter_shortname": "B3 Y",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_type": 0,
              "parameter_modmode": 0,
              "parameter_initial": [
                0.0
              ],
              "parameter_initial_enable": 1,
              "parameter_invisible": 0
            }
          },
          "varname": "blob3_y",
          "presentation": 1,
          "parameter_type": 0,
          "presentation_rect": [
            84.0,
            72.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b3_lbl_speedlim",
          "maxclass": "newobj",
          "patching_rect": [
            1185.0,
            222.0,
            80.0,
            22.0
          ],
          "text": "speedlim 120"
        }
      },
      {
        "box": {
          "id": "b1_x_map_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            280.0,
            338.0,
            80.0,
            20.0
          ],
          "presentation": 0,
          "text": "X Map"
        }
      },
      {
        "box": {
          "id": "b1_y_map_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            280.0,
            396.0,
            80.0,
            20.0
          ],
          "presentation": 0,
          "text": "Y Map"
        }
      },
      {
        "box": {
          "id": "b1_x_livemap",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 5,
          "outlettype": [
            "",
            "int",
            "",
            "int",
            ""
          ],
          "patching_rect": [
            360.0,
            360.0,
            130.0,
            22.0
          ],
          "presentation": 0,
          "text": "live.map @strict 1",
          "varname": "blob1_x_livemap"
        }
      },
      {
        "box": {
          "id": "b1_y_livemap",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 5,
          "outlettype": [
            "",
            "int",
            "",
            "int",
            ""
          ],
          "patching_rect": [
            360.0,
            390.0,
            130.0,
            22.0
          ],
          "presentation": 0,
          "text": "live.map @strict 1",
          "varname": "blob1_y_livemap"
        }
      },
      {
        "box": {
          "id": "b1_x_remote",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            500.0,
            360.0,
            190.0,
            22.0
          ],
          "text": "live.remote~ @normalized 1 @smoothing 10",
          "varname": "blob1_x_remote"
        }
      },
      {
        "box": {
          "id": "b1_y_remote",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            500.0,
            390.0,
            190.0,
            22.0
          ],
          "text": "live.remote~ @normalized 1 @smoothing 10",
          "varname": "blob1_y_remote"
        }
      },
      {
        "box": {
          "id": "b2_x_map_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            280.0,
            338.0,
            80.0,
            20.0
          ],
          "presentation": 0,
          "text": "X Map"
        }
      },
      {
        "box": {
          "id": "b2_y_map_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            280.0,
            396.0,
            80.0,
            20.0
          ],
          "presentation": 0,
          "text": "Y Map"
        }
      },
      {
        "box": {
          "id": "b2_x_livemap",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 5,
          "outlettype": [
            "",
            "int",
            "",
            "int",
            ""
          ],
          "patching_rect": [
            360.0,
            360.0,
            130.0,
            22.0
          ],
          "presentation": 0,
          "text": "live.map @strict 1",
          "varname": "b2_x_livemap"
        }
      },
      {
        "box": {
          "id": "b2_y_livemap",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 5,
          "outlettype": [
            "",
            "int",
            "",
            "int",
            ""
          ],
          "patching_rect": [
            360.0,
            390.0,
            130.0,
            22.0
          ],
          "presentation": 0,
          "text": "live.map @strict 1",
          "varname": "b2_y_livemap"
        }
      },
      {
        "box": {
          "id": "b2_x_remote",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            700.0,
            360.0,
            190.0,
            22.0
          ],
          "text": "live.remote~ @normalized 1 @smoothing 10",
          "varname": "b2_x_remote"
        }
      },
      {
        "box": {
          "id": "b2_y_remote",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            700.0,
            390.0,
            190.0,
            22.0
          ],
          "text": "live.remote~ @normalized 1 @smoothing 10",
          "varname": "b2_y_remote"
        }
      },
      {
        "box": {
          "id": "b3_x_map_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            280.0,
            448.0,
            80.0,
            20.0
          ],
          "presentation": 0,
          "text": "X Map"
        }
      },
      {
        "box": {
          "id": "b3_y_map_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            280.0,
            506.0,
            80.0,
            20.0
          ],
          "presentation": 0,
          "text": "Y Map"
        }
      },
      {
        "box": {
          "id": "b3_x_livemap",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 5,
          "outlettype": [
            "",
            "int",
            "",
            "int",
            ""
          ],
          "patching_rect": [
            360.0,
            450.0,
            130.0,
            22.0
          ],
          "presentation": 0,
          "text": "live.map @strict 1",
          "varname": "b3_x_livemap"
        }
      },
      {
        "box": {
          "id": "b3_y_livemap",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 5,
          "outlettype": [
            "",
            "int",
            "",
            "int",
            ""
          ],
          "patching_rect": [
            360.0,
            480.0,
            130.0,
            22.0
          ],
          "presentation": 0,
          "text": "live.map @strict 1",
          "varname": "b3_y_livemap"
        }
      },
      {
        "box": {
          "id": "b3_x_remote",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            700.0,
            450.0,
            190.0,
            22.0
          ],
          "text": "live.remote~ @normalized 1 @smoothing 10",
          "varname": "b3_x_remote"
        }
      },
      {
        "box": {
          "id": "b3_y_remote",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            700.0,
            480.0,
            190.0,
            22.0
          ],
          "text": "live.remote~ @normalized 1 @smoothing 10",
          "varname": "b3_y_remote"
        }
      },
      {
        "box": {
          "id": "pres_x_header",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            24.0,
            0.0,
            20.0,
            16.0
          ],
          "presentation": 1,
          "presentation_rect": [
            24.0,
            0.0,
            20.0,
            16.0
          ],
          "text": "X"
        }
      },
      {
        "box": {
          "id": "pres_y_header",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            84.0,
            0.0,
            20.0,
            16.0
          ],
          "presentation": 1,
          "presentation_rect": [
            84.0,
            0.0,
            20.0,
            16.0
          ],
          "text": "Y"
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
            "b1_tlb",
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
            "b1_pkt",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_tlb",
            0
          ],
          "destination": [
            "b1_unpack",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_tlb",
            1
          ],
          "destination": [
            "b1_alive_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_alive_t",
            2
          ],
          "destination": [
            "b1_stop",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_stop",
            0
          ],
          "destination": [
            "b1_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_alive_t",
            1
          ],
          "destination": [
            "b1_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_alive_t",
            0
          ],
          "destination": [
            "b1_1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_1",
            0
          ],
          "destination": [
            "b1_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_delay",
            0
          ],
          "destination": [
            "b1_0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_0",
            0
          ],
          "destination": [
            "b1_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_alive_ch",
            0
          ],
          "destination": [
            "b1_sel",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_sel",
            0
          ],
          "destination": [
            "b1_on",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_sel",
            1
          ],
          "destination": [
            "b1_off",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            0
          ],
          "destination": [
            "b1_label_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_label_ch",
            0
          ],
          "destination": [
            "b1_lbl_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_label_ch",
            0
          ],
          "destination": [
            "b1_lbl",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            1
          ],
          "destination": [
            "b2_tlb",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            1
          ],
          "destination": [
            "b2_pkt",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_tlb",
            0
          ],
          "destination": [
            "b2_unpack",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_tlb",
            1
          ],
          "destination": [
            "b2_alive_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_alive_t",
            2
          ],
          "destination": [
            "b2_stop",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_stop",
            0
          ],
          "destination": [
            "b2_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_alive_t",
            1
          ],
          "destination": [
            "b2_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_alive_t",
            0
          ],
          "destination": [
            "b2_1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_1",
            0
          ],
          "destination": [
            "b2_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_delay",
            0
          ],
          "destination": [
            "b2_0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_0",
            0
          ],
          "destination": [
            "b2_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_alive_ch",
            0
          ],
          "destination": [
            "b2_sel",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_sel",
            0
          ],
          "destination": [
            "b2_on",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_sel",
            1
          ],
          "destination": [
            "b2_off",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_unpack",
            0
          ],
          "destination": [
            "b2_label_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_label_ch",
            0
          ],
          "destination": [
            "b2_lbl_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_label_ch",
            0
          ],
          "destination": [
            "b2_lbl",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_on",
            0
          ],
          "destination": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_off",
            0
          ],
          "destination": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_on",
            0
          ],
          "destination": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_off",
            0
          ],
          "destination": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-40",
            0
          ],
          "destination": [
            "obj-41",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-40",
            1
          ],
          "destination": [
            "obj-41",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_on",
            0
          ],
          "destination": [
            "obj-42",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_off",
            0
          ],
          "destination": [
            "obj-42",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_on",
            0
          ],
          "destination": [
            "obj-42",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_off",
            0
          ],
          "destination": [
            "obj-42",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            2
          ],
          "destination": [
            "b3_tlb",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            2
          ],
          "destination": [
            "b3_pkt",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_tlb",
            0
          ],
          "destination": [
            "b3_unpack",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_tlb",
            1
          ],
          "destination": [
            "b3_alive_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_alive_t",
            2
          ],
          "destination": [
            "b3_stop",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_stop",
            0
          ],
          "destination": [
            "b3_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_alive_t",
            1
          ],
          "destination": [
            "b3_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_alive_t",
            0
          ],
          "destination": [
            "b3_1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_1",
            0
          ],
          "destination": [
            "b3_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_delay",
            0
          ],
          "destination": [
            "b3_0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_0",
            0
          ],
          "destination": [
            "b3_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_alive_ch",
            0
          ],
          "destination": [
            "b3_sel",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_sel",
            0
          ],
          "destination": [
            "b3_on",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_sel",
            1
          ],
          "destination": [
            "b3_off",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_unpack",
            0
          ],
          "destination": [
            "b3_label_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_label_ch",
            0
          ],
          "destination": [
            "b3_lbl",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_on",
            0
          ],
          "destination": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_off",
            0
          ],
          "destination": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_on",
            0
          ],
          "destination": [
            "obj-42",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_off",
            0
          ],
          "destination": [
            "obj-42",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            1
          ],
          "destination": [
            "b1_x_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            2
          ],
          "destination": [
            "b1_y_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_clip",
            0
          ],
          "destination": [
            "b1_x_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_speedlim",
            0
          ],
          "destination": [
            "b1_x_map",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_clip",
            0
          ],
          "destination": [
            "b1_y_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_speedlim",
            0
          ],
          "destination": [
            "b1_y_map",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_unpack",
            1
          ],
          "destination": [
            "b2_x_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_x_clip",
            0
          ],
          "destination": [
            "b2_x_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_x_speedlim",
            0
          ],
          "destination": [
            "b2_x_map",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_unpack",
            2
          ],
          "destination": [
            "b2_y_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_y_clip",
            0
          ],
          "destination": [
            "b2_y_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_y_speedlim",
            0
          ],
          "destination": [
            "b2_y_map",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_unpack",
            1
          ],
          "destination": [
            "b3_x_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_x_clip",
            0
          ],
          "destination": [
            "b3_x_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_x_speedlim",
            0
          ],
          "destination": [
            "b3_x_map",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_unpack",
            2
          ],
          "destination": [
            "b3_y_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_y_clip",
            0
          ],
          "destination": [
            "b3_y_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_y_speedlim",
            0
          ],
          "destination": [
            "b3_y_map",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_label_ch",
            0
          ],
          "destination": [
            "b3_lbl_speedlim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_lbl_speedlim",
            0
          ],
          "destination": [
            "b3_lbl_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_speedlim",
            0
          ],
          "destination": [
            "b1_x_remote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_speedlim",
            0
          ],
          "destination": [
            "b1_y_remote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_livemap",
            1
          ],
          "destination": [
            "b1_x_remote",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_livemap",
            1
          ],
          "destination": [
            "b1_y_remote",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_x_speedlim",
            0
          ],
          "destination": [
            "b2_x_remote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_y_speedlim",
            0
          ],
          "destination": [
            "b2_y_remote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_x_livemap",
            1
          ],
          "destination": [
            "b2_x_remote",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_y_livemap",
            1
          ],
          "destination": [
            "b2_y_remote",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_x_speedlim",
            0
          ],
          "destination": [
            "b3_x_remote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_y_speedlim",
            0
          ],
          "destination": [
            "b3_y_remote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_x_livemap",
            1
          ],
          "destination": [
            "b3_x_remote",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b3_y_livemap",
            1
          ],
          "destination": [
            "b3_y_remote",
            1
          ]
        }
      }
    ]
  }
}