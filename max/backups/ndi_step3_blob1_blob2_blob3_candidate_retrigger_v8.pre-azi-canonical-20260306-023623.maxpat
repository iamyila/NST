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
          "text": "Blob1+Blob2+Blob3: notes from alive edges only; Blob1 X/Y/Azi/Dist/Spd/Size mappable in M4L"
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
            840.0,
            220.0,
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
            895.0,
            220.0,
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
            975.0,
            252.0,
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
            1025.0,
            252.0,
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
            895.0,
            252.0,
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
            1100.0,
            252.0,
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
            945.0,
            287.0,
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
            945.0,
            322.0,
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
            840.0,
            252.0,
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
            840.0,
            287.0,
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
            840.0,
            322.0,
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
            840.0,
            357.0,
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
            1020.0,
            395.0,
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
            1085.0,
            395.0,
            45.0,
            22.0
          ],
          "text": "60 0"
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
          "id": "b2_xy_comment",
          "maxclass": "comment",
          "patching_rect": [
            760.0,
            340.0,
            220.0,
            20.0
          ],
          "text": "B2",
          "presentation": 0,
          "presentation_rect": [
            2.0,
            40.0,
            20.0,
            18.0
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
          "presentation": 0,
          "presentation_rect": [
            2.0,
            64.0,
            20.0,
            18.0
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
          "id": "b1_bank_panel",
          "maxclass": "panel",
          "patching_rect": [
            820.0,
            10.0,
            370.0,
            158.0
          ],
          "presentation": 1,
          "presentation_rect": [
            8.0,
            10.0,
            446.0,
            160.0
          ],
          "background": 1,
          "bgcolor": [
            0.08,
            0.08,
            0.08,
            0.9
          ],
          "border": 1
        }
      },
      {
        "box": {
          "id": "b1_bank_title",
          "maxclass": "comment",
          "text": "B1 Map Bank",
          "patching_rect": [
            828.0,
            12.0,
            120.0,
            16.0
          ],
          "presentation": 1,
          "presentation_rect": [
            16.0,
            12.0,
            120.0,
            16.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_hdr_param",
          "maxclass": "comment",
          "text": "Parameter",
          "patching_rect": [
            878.0,
            144.0,
            96.0,
            16.0
          ],
          "presentation": 0,
          "presentation_rect": [
            66.0,
            144.0,
            96.0,
            16.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_hdr_mode",
          "maxclass": "comment",
          "text": "Mode",
          "patching_rect": [
            1000.0,
            144.0,
            80.0,
            16.0
          ],
          "presentation": 0,
          "presentation_rect": [
            188.0,
            144.0,
            80.0,
            16.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_hdr_range",
          "maxclass": "comment",
          "text": "Range",
          "patching_rect": [
            1098.0,
            144.0,
            80.0,
            16.0
          ],
          "presentation": 0,
          "presentation_rect": [
            286.0,
            144.0,
            80.0,
            16.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_x_lab",
          "maxclass": "comment",
          "text": "X",
          "patching_rect": [
            830.0,
            36.0,
            30.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            36.0,
            30.0,
            18.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "b1_x_lane",
          "maxclass": "newobj",
          "text": "p b1_lane_x_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            442.0,
            110.0,
            22.0
          ],
          "patcher": {
            "fileversion": 1,
            "appversion": {
              "major": 9,
              "minor": 1,
              "revision": 0,
              "architecture": "x64",
              "modernui": 1
            },
            "classnamespace": "box",
            "rect": [
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "id": "in_v",
                  "maxclass": "inlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "(float 0..1) value"
                }
              },
              {
                "box": {
                  "id": "in_map",
                  "maxclass": "inlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "map id"
                }
              },
              {
                "box": {
                  "id": "in_stop",
                  "maxclass": "inlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "stop mapping"
                }
              },
              {
                "box": {
                  "id": "in_min",
                  "maxclass": "inlet",
                  "index": 4,
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "min"
                }
              },
              {
                "box": {
                  "id": "in_max",
                  "maxclass": "inlet",
                  "index": 5,
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "max"
                }
              },
              {
                "box": {
                  "id": "in_mode",
                  "maxclass": "inlet",
                  "index": 6,
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mode"
                }
              },
              {
                "box": {
                  "id": "in_pol",
                  "maxclass": "inlet",
                  "index": 7,
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "input polarity"
                }
              },
              {
                "box": {
                  "id": "in_depth",
                  "maxclass": "inlet",
                  "index": 8,
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "depth %"
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "text": "clip 0. 1.",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "text": "speedlim 10",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "text": "sig~ 0.",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
                  "text": "poly~ Abl.Map",
                  "numinlets": 10,
                  "numoutlets": 4,
                  "outlettype": [
                    "",
                    "",
                    "",
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    154.0,
                    88.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
                  "text": "loadbang",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "bang"
                  ],
                  "patching_rect": [
                    150.0,
                    58.0,
                    60.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
                  "text": "0",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    150.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
                  "text": "100",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    186.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
                  "text": "1",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    228.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
                  "text": "50",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    264.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "text": "Abl.Map lane core (stabilized)",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ]
                }
              },
              {
                "box": {
                  "id": "out_v",
                  "maxclass": "outlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "value"
                }
              },
              {
                "box": {
                  "id": "out_wait",
                  "maxclass": "outlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "wait"
                }
              },
              {
                "box": {
                  "id": "out_mapped",
                  "maxclass": "outlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mapped"
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "source": [
                    "in_v",
                    0
                  ],
                  "destination": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "clip",
                    0
                  ],
                  "destination": [
                    "spd",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "spd",
                    0
                  ],
                  "destination": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "sig",
                    0
                  ],
                  "destination": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_map",
                    0
                  ],
                  "destination": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_stop",
                    0
                  ],
                  "destination": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_min",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_max",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_mode",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_pol",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_depth",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    9
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    0
                  ],
                  "destination": [
                    "out_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    1
                  ],
                  "destination": [
                    "out_wait",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    2
                  ],
                  "destination": [
                    "out_mapped",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m100",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m50",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    8
                  ]
                }
              }
            ]
          },
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_y_lab",
          "maxclass": "comment",
          "text": "Y",
          "patching_rect": [
            830.0,
            58.0,
            30.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            58.0,
            30.0,
            18.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "b1_y_lane",
          "maxclass": "newobj",
          "text": "p b1_lane_y_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            552.0,
            110.0,
            22.0
          ],
          "patcher": {
            "fileversion": 1,
            "appversion": {
              "major": 9,
              "minor": 1,
              "revision": 0,
              "architecture": "x64",
              "modernui": 1
            },
            "classnamespace": "box",
            "rect": [
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "id": "in_v",
                  "maxclass": "inlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "(float 0..1) value"
                }
              },
              {
                "box": {
                  "id": "in_map",
                  "maxclass": "inlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "map id"
                }
              },
              {
                "box": {
                  "id": "in_stop",
                  "maxclass": "inlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "stop mapping"
                }
              },
              {
                "box": {
                  "id": "in_min",
                  "maxclass": "inlet",
                  "index": 4,
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "min"
                }
              },
              {
                "box": {
                  "id": "in_max",
                  "maxclass": "inlet",
                  "index": 5,
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "max"
                }
              },
              {
                "box": {
                  "id": "in_mode",
                  "maxclass": "inlet",
                  "index": 6,
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mode"
                }
              },
              {
                "box": {
                  "id": "in_pol",
                  "maxclass": "inlet",
                  "index": 7,
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "input polarity"
                }
              },
              {
                "box": {
                  "id": "in_depth",
                  "maxclass": "inlet",
                  "index": 8,
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "depth %"
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "text": "clip 0. 1.",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "text": "speedlim 10",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "text": "sig~ 0.",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
                  "text": "poly~ Abl.Map",
                  "numinlets": 10,
                  "numoutlets": 4,
                  "outlettype": [
                    "",
                    "",
                    "",
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    154.0,
                    88.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
                  "text": "loadbang",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "bang"
                  ],
                  "patching_rect": [
                    150.0,
                    58.0,
                    60.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
                  "text": "0",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    150.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
                  "text": "100",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    186.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
                  "text": "1",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    228.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
                  "text": "50",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    264.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "text": "Abl.Map lane core (stabilized)",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ]
                }
              },
              {
                "box": {
                  "id": "out_v",
                  "maxclass": "outlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "value"
                }
              },
              {
                "box": {
                  "id": "out_wait",
                  "maxclass": "outlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "wait"
                }
              },
              {
                "box": {
                  "id": "out_mapped",
                  "maxclass": "outlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mapped"
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "source": [
                    "in_v",
                    0
                  ],
                  "destination": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "clip",
                    0
                  ],
                  "destination": [
                    "spd",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "spd",
                    0
                  ],
                  "destination": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "sig",
                    0
                  ],
                  "destination": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_map",
                    0
                  ],
                  "destination": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_stop",
                    0
                  ],
                  "destination": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_min",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_max",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_mode",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_pol",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_depth",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    9
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    0
                  ],
                  "destination": [
                    "out_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    1
                  ],
                  "destination": [
                    "out_wait",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    2
                  ],
                  "destination": [
                    "out_mapped",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m100",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m50",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    8
                  ]
                }
              }
            ]
          },
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_spd_lab",
          "maxclass": "comment",
          "text": "Spd",
          "patching_rect": [
            830.0,
            80.0,
            36.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            80.0,
            36.0,
            18.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "b1_spd_lane",
          "maxclass": "newobj",
          "text": "p b1_lane_azi_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            662.0,
            110.0,
            22.0
          ],
          "patcher": {
            "fileversion": 1,
            "appversion": {
              "major": 9,
              "minor": 1,
              "revision": 0,
              "architecture": "x64",
              "modernui": 1
            },
            "classnamespace": "box",
            "rect": [
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "id": "in_v",
                  "maxclass": "inlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "(float 0..1) value"
                }
              },
              {
                "box": {
                  "id": "in_map",
                  "maxclass": "inlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "map id"
                }
              },
              {
                "box": {
                  "id": "in_stop",
                  "maxclass": "inlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "stop mapping"
                }
              },
              {
                "box": {
                  "id": "in_min",
                  "maxclass": "inlet",
                  "index": 4,
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "min"
                }
              },
              {
                "box": {
                  "id": "in_max",
                  "maxclass": "inlet",
                  "index": 5,
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "max"
                }
              },
              {
                "box": {
                  "id": "in_mode",
                  "maxclass": "inlet",
                  "index": 6,
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mode"
                }
              },
              {
                "box": {
                  "id": "in_pol",
                  "maxclass": "inlet",
                  "index": 7,
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "input polarity"
                }
              },
              {
                "box": {
                  "id": "in_depth",
                  "maxclass": "inlet",
                  "index": 8,
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "depth %"
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "text": "clip 0. 1.",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "text": "speedlim 10",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "text": "sig~ 0.",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
                  "text": "poly~ Abl.Map",
                  "numinlets": 10,
                  "numoutlets": 4,
                  "outlettype": [
                    "",
                    "",
                    "",
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    154.0,
                    88.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
                  "text": "loadbang",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "bang"
                  ],
                  "patching_rect": [
                    150.0,
                    58.0,
                    60.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
                  "text": "0",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    150.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
                  "text": "100",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    186.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
                  "text": "1",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    228.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
                  "text": "50",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    264.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "text": "Abl.Map lane core (stabilized)",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ]
                }
              },
              {
                "box": {
                  "id": "out_v",
                  "maxclass": "outlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "value"
                }
              },
              {
                "box": {
                  "id": "out_wait",
                  "maxclass": "outlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "wait"
                }
              },
              {
                "box": {
                  "id": "out_mapped",
                  "maxclass": "outlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mapped"
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "source": [
                    "in_v",
                    0
                  ],
                  "destination": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "clip",
                    0
                  ],
                  "destination": [
                    "spd",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "spd",
                    0
                  ],
                  "destination": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "sig",
                    0
                  ],
                  "destination": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_map",
                    0
                  ],
                  "destination": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_stop",
                    0
                  ],
                  "destination": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_min",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_max",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_mode",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_pol",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_depth",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    9
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    0
                  ],
                  "destination": [
                    "out_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    1
                  ],
                  "destination": [
                    "out_wait",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    2
                  ],
                  "destination": [
                    "out_mapped",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m100",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m50",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    8
                  ]
                }
              }
            ]
          },
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_size_lab",
          "maxclass": "comment",
          "text": "Size",
          "patching_rect": [
            830.0,
            102.0,
            36.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            102.0,
            36.0,
            18.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "b1_size_lane",
          "maxclass": "newobj",
          "text": "p b1_lane_dist_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            772.0,
            110.0,
            22.0
          ],
          "patcher": {
            "fileversion": 1,
            "appversion": {
              "major": 9,
              "minor": 1,
              "revision": 0,
              "architecture": "x64",
              "modernui": 1
            },
            "classnamespace": "box",
            "rect": [
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "id": "in_v",
                  "maxclass": "inlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "(float 0..1) value"
                }
              },
              {
                "box": {
                  "id": "in_map",
                  "maxclass": "inlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "map id"
                }
              },
              {
                "box": {
                  "id": "in_stop",
                  "maxclass": "inlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "stop mapping"
                }
              },
              {
                "box": {
                  "id": "in_min",
                  "maxclass": "inlet",
                  "index": 4,
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "min"
                }
              },
              {
                "box": {
                  "id": "in_max",
                  "maxclass": "inlet",
                  "index": 5,
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "max"
                }
              },
              {
                "box": {
                  "id": "in_mode",
                  "maxclass": "inlet",
                  "index": 6,
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mode"
                }
              },
              {
                "box": {
                  "id": "in_pol",
                  "maxclass": "inlet",
                  "index": 7,
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "input polarity"
                }
              },
              {
                "box": {
                  "id": "in_depth",
                  "maxclass": "inlet",
                  "index": 8,
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "depth %"
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "text": "clip 0. 1.",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "text": "speedlim 10",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "text": "sig~ 0.",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
                  "text": "poly~ Abl.Map",
                  "numinlets": 10,
                  "numoutlets": 4,
                  "outlettype": [
                    "",
                    "",
                    "",
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    154.0,
                    88.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
                  "text": "loadbang",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "bang"
                  ],
                  "patching_rect": [
                    150.0,
                    58.0,
                    60.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
                  "text": "0",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    150.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
                  "text": "100",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    186.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
                  "text": "1",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    228.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
                  "text": "50",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    264.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "text": "Abl.Map lane core (stabilized)",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ]
                }
              },
              {
                "box": {
                  "id": "out_v",
                  "maxclass": "outlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "value"
                }
              },
              {
                "box": {
                  "id": "out_wait",
                  "maxclass": "outlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "wait"
                }
              },
              {
                "box": {
                  "id": "out_mapped",
                  "maxclass": "outlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mapped"
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "source": [
                    "in_v",
                    0
                  ],
                  "destination": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "clip",
                    0
                  ],
                  "destination": [
                    "spd",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "spd",
                    0
                  ],
                  "destination": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "sig",
                    0
                  ],
                  "destination": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_map",
                    0
                  ],
                  "destination": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_stop",
                    0
                  ],
                  "destination": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_min",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_max",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_mode",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_pol",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_depth",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    9
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    0
                  ],
                  "destination": [
                    "out_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    1
                  ],
                  "destination": [
                    "out_wait",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    2
                  ],
                  "destination": [
                    "out_mapped",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m100",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m50",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    8
                  ]
                }
              }
            ]
          },
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ]
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "id": "b1_x_ui",
          "lockeddragscroll": 0,
          "lockedsize": 0,
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
          "offset": [
            0.0,
            0.0
          ],
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            868.0,
            36.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            34.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "id": "b1_y_ui",
          "lockeddragscroll": 0,
          "lockedsize": 0,
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
          "offset": [
            0.0,
            0.0
          ],
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            868.0,
            58.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            56.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "id": "b1_spd_ui",
          "lockeddragscroll": 0,
          "lockedsize": 0,
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
          "offset": [
            0.0,
            0.0
          ],
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            868.0,
            80.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            78.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "id": "b1_size_ui",
          "lockeddragscroll": 0,
          "lockedsize": 0,
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
          "offset": [
            0.0,
            0.0
          ],
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            868.0,
            102.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            100.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1
        }
      },
      {
        "box": {
          "id": "dbg_val_raw_title",
          "maxclass": "comment",
          "text": "Raw",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            1320.0,
            34.0,
            56.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            12.0,
            40.0,
            18.0
          ]
        }
      },
      {
        "box": {
          "id": "dbg_x_raw",
          "maxclass": "flonum",
          "format": 6,
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1320.0,
            60.0,
            60.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            36.0,
            56.0,
            20.0
          ],
          "parameter_enable": 0
        }
      },
      {
        "box": {
          "id": "dbg_y_raw",
          "maxclass": "flonum",
          "format": 6,
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1320.0,
            86.0,
            60.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            58.0,
            56.0,
            20.0
          ],
          "parameter_enable": 0
        }
      },
      {
        "box": {
          "id": "dbg_spd_raw",
          "maxclass": "flonum",
          "format": 6,
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1320.0,
            112.0,
            60.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            80.0,
            56.0,
            20.0
          ],
          "parameter_enable": 0
        }
      },
      {
        "box": {
          "id": "dbg_size_raw",
          "maxclass": "flonum",
          "format": 6,
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1320.0,
            138.0,
            60.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            102.0,
            56.0,
            20.0
          ],
          "parameter_enable": 0
        }
      },
      {
        "box": {
          "id": "b1_azi_lab",
          "maxclass": "comment",
          "text": "Azi",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            124.0,
            36.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            124.0,
            36.0,
            18.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_dist_lab",
          "maxclass": "comment",
          "text": "Dist",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            146.0,
            36.0,
            18.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            146.0,
            36.0,
            18.0
          ]
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "lockeddragscroll": 0,
          "lockedsize": 0,
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
          "offset": [
            0.0,
            0.0
          ],
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            868.0,
            124.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            122.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1,
          "id": "b1_azi_ui"
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "lockeddragscroll": 0,
          "lockedsize": 0,
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
          "offset": [
            0.0,
            0.0
          ],
          "outlettype": [
            "",
            "",
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            868.0,
            146.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            144.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1,
          "id": "b1_dist_ui"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            882.0,
            140.0,
            22.0
          ],
          "patcher": {
            "fileversion": 1,
            "appversion": {
              "major": 9,
              "minor": 1,
              "revision": 0,
              "architecture": "x64",
              "modernui": 1
            },
            "classnamespace": "box",
            "rect": [
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "id": "in_v",
                  "maxclass": "inlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "(float 0..1) value"
                }
              },
              {
                "box": {
                  "id": "in_map",
                  "maxclass": "inlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "map id"
                }
              },
              {
                "box": {
                  "id": "in_stop",
                  "maxclass": "inlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "stop mapping"
                }
              },
              {
                "box": {
                  "id": "in_min",
                  "maxclass": "inlet",
                  "index": 4,
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "min"
                }
              },
              {
                "box": {
                  "id": "in_max",
                  "maxclass": "inlet",
                  "index": 5,
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "max"
                }
              },
              {
                "box": {
                  "id": "in_mode",
                  "maxclass": "inlet",
                  "index": 6,
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mode"
                }
              },
              {
                "box": {
                  "id": "in_pol",
                  "maxclass": "inlet",
                  "index": 7,
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "input polarity"
                }
              },
              {
                "box": {
                  "id": "in_depth",
                  "maxclass": "inlet",
                  "index": 8,
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "depth %"
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "text": "clip 0. 1.",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "text": "speedlim 10",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "text": "sig~ 0.",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
                  "text": "poly~ Abl.Map",
                  "numinlets": 10,
                  "numoutlets": 4,
                  "outlettype": [
                    "",
                    "",
                    "",
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    154.0,
                    88.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
                  "text": "loadbang",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "bang"
                  ],
                  "patching_rect": [
                    150.0,
                    58.0,
                    60.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
                  "text": "0",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    150.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
                  "text": "100",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    186.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
                  "text": "1",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    228.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
                  "text": "50",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    264.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "text": "Abl.Map lane core (stabilized)",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ]
                }
              },
              {
                "box": {
                  "id": "out_v",
                  "maxclass": "outlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "value"
                }
              },
              {
                "box": {
                  "id": "out_wait",
                  "maxclass": "outlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "wait"
                }
              },
              {
                "box": {
                  "id": "out_mapped",
                  "maxclass": "outlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mapped"
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "source": [
                    "in_v",
                    0
                  ],
                  "destination": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "clip",
                    0
                  ],
                  "destination": [
                    "spd",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "spd",
                    0
                  ],
                  "destination": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "sig",
                    0
                  ],
                  "destination": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_map",
                    0
                  ],
                  "destination": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_stop",
                    0
                  ],
                  "destination": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_min",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_max",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_mode",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_pol",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_depth",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    9
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    0
                  ],
                  "destination": [
                    "out_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    1
                  ],
                  "destination": [
                    "out_wait",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    2
                  ],
                  "destination": [
                    "out_mapped",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m100",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m50",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    8
                  ]
                }
              }
            ]
          },
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_azi_lane",
          "text": "p b1_lane_azi_extra_core"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            992.0,
            150.0,
            22.0
          ],
          "patcher": {
            "fileversion": 1,
            "appversion": {
              "major": 9,
              "minor": 1,
              "revision": 0,
              "architecture": "x64",
              "modernui": 1
            },
            "classnamespace": "box",
            "rect": [
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "id": "in_v",
                  "maxclass": "inlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "(float 0..1) value"
                }
              },
              {
                "box": {
                  "id": "in_map",
                  "maxclass": "inlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "map id"
                }
              },
              {
                "box": {
                  "id": "in_stop",
                  "maxclass": "inlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "stop mapping"
                }
              },
              {
                "box": {
                  "id": "in_min",
                  "maxclass": "inlet",
                  "index": 4,
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "min"
                }
              },
              {
                "box": {
                  "id": "in_max",
                  "maxclass": "inlet",
                  "index": 5,
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "max"
                }
              },
              {
                "box": {
                  "id": "in_mode",
                  "maxclass": "inlet",
                  "index": 6,
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mode"
                }
              },
              {
                "box": {
                  "id": "in_pol",
                  "maxclass": "inlet",
                  "index": 7,
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "input polarity"
                }
              },
              {
                "box": {
                  "id": "in_depth",
                  "maxclass": "inlet",
                  "index": 8,
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ],
                  "comment": "depth %"
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "text": "clip 0. 1.",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "text": "speedlim 10",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "text": "sig~ 0.",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
                  "text": "poly~ Abl.Map",
                  "numinlets": 10,
                  "numoutlets": 4,
                  "outlettype": [
                    "",
                    "",
                    "",
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    154.0,
                    88.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
                  "text": "loadbang",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "bang"
                  ],
                  "patching_rect": [
                    150.0,
                    58.0,
                    60.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
                  "text": "0",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    150.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
                  "text": "100",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    186.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
                  "text": "1",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    228.0,
                    88.0,
                    30.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
                  "text": "50",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    264.0,
                    88.0,
                    36.0,
                    22.0
                  ]
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "text": "Abl.Map lane core (stabilized)",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ]
                }
              },
              {
                "box": {
                  "id": "out_v",
                  "maxclass": "outlet",
                  "index": 1,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "value"
                }
              },
              {
                "box": {
                  "id": "out_wait",
                  "maxclass": "outlet",
                  "index": 2,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "wait"
                }
              },
              {
                "box": {
                  "id": "out_mapped",
                  "maxclass": "outlet",
                  "index": 3,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ],
                  "comment": "mapped"
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "source": [
                    "in_v",
                    0
                  ],
                  "destination": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "clip",
                    0
                  ],
                  "destination": [
                    "spd",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "spd",
                    0
                  ],
                  "destination": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "sig",
                    0
                  ],
                  "destination": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_map",
                    0
                  ],
                  "destination": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_stop",
                    0
                  ],
                  "destination": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_min",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_max",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_mode",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_pol",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "in_depth",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    9
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    0
                  ],
                  "destination": [
                    "out_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    1
                  ],
                  "destination": [
                    "out_wait",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "map",
                    2
                  ],
                  "destination": [
                    "out_mapped",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "lb",
                    0
                  ],
                  "destination": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    3
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m100",
                    0
                  ],
                  "destination": [
                    "map",
                    4
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m0",
                    0
                  ],
                  "destination": [
                    "map",
                    5
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    6
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m50",
                    0
                  ],
                  "destination": [
                    "map",
                    7
                  ]
                }
              },
              {
                "patchline": {
                  "source": [
                    "m1",
                    0
                  ],
                  "destination": [
                    "map",
                    8
                  ]
                }
              }
            ]
          },
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_dist_lane",
          "text": "p b1_lane_dist_extra_core"
        }
      },
      {
        "box": {
          "id": "b1_cx",
          "maxclass": "newobj",
          "text": "expr $f1 - 0.5",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1180.0,
            620.0,
            90.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_cy",
          "maxclass": "newobj",
          "text": "expr $f1 - 0.5",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1278.0,
            620.0,
            90.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_azi_calc",
          "maxclass": "newobj",
          "text": "expr (atan2(-$f1,$f2)/6.2831853) - floor(atan2(-$f1,$f2)/6.2831853)",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1180.0,
            650.0,
            360.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_dist_calc",
          "maxclass": "newobj",
          "text": "expr sqrt(($f1*$f1)+($f2*$f2))/0.70710678",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1180.0,
            680.0,
            250.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_dist_clip",
          "maxclass": "newobj",
          "text": "clip 0. 1.",
          "numinlets": 3,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1440.0,
            680.0,
            60.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "dbg_azi_raw",
          "maxclass": "flonum",
          "format": 6,
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1320.0,
            164.0,
            60.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            124.0,
            56.0,
            20.0
          ],
          "parameter_enable": 0
        }
      },
      {
        "box": {
          "id": "dbg_dist_raw",
          "maxclass": "flonum",
          "format": 6,
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1320.0,
            190.0,
            60.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            386.0,
            146.0,
            56.0,
            20.0
          ],
          "parameter_enable": 0
        }
      },
      {
        "box": {
          "id": "b1_dist_trim",
          "maxclass": "newobj",
          "text": "* 1.25",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1510.0,
            680.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_y_inv",
          "maxclass": "newobj",
          "text": "expr 1. - $f1",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ],
          "patching_rect": [
            1278.0,
            592.0,
            90.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_azi_cal_expr",
          "maxclass": "newobj",
          "patching_rect": [
            1180.0,
            740.0,
            370.0,
            22.0
          ],
          "text": "expr (($f1*$f2)+$f3) - floor((($f1*$f2)+$f3))",
          "numinlets": 3,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ]
        }
      },
      {
        "box": {
          "id": "b1_azi_inv_num",
          "maxclass": "flonum",
          "patching_rect": [
            1180.0,
            770.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "parameter_enable": 0,
          "format": 6
        }
      },
      {
        "box": {
          "id": "b1_azi_off_num",
          "maxclass": "flonum",
          "patching_rect": [
            1250.0,
            770.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "parameter_enable": 0,
          "format": 6
        }
      },
      {
        "box": {
          "id": "b1_dist_gain_num",
          "maxclass": "flonum",
          "patching_rect": [
            1510.0,
            710.0,
            60.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "parameter_enable": 0,
          "format": 6
        }
      },
      {
        "box": {
          "id": "b1_azi_inv_load",
          "maxclass": "newobj",
          "patching_rect": [
            1180.0,
            798.0,
            90.0,
            22.0
          ],
          "text": "loadmess -1."
        }
      },
      {
        "box": {
          "id": "b1_azi_off_load",
          "maxclass": "newobj",
          "patching_rect": [
            1250.0,
            798.0,
            80.0,
            22.0
          ],
          "text": "loadmess 0."
        }
      },
      {
        "box": {
          "id": "b1_dist_gain_load",
          "maxclass": "newobj",
          "patching_rect": [
            1510.0,
            738.0,
            90.0,
            22.0
          ],
          "text": "loadmess 1.25"
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
            "b1_x_ui",
            0
          ],
          "destination": [
            "b1_x_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_ui",
            1
          ],
          "destination": [
            "b1_x_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_ui",
            2
          ],
          "destination": [
            "b1_x_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_ui",
            3
          ],
          "destination": [
            "b1_x_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_ui",
            4
          ],
          "destination": [
            "b1_x_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_ui",
            5
          ],
          "destination": [
            "b1_x_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_ui",
            6
          ],
          "destination": [
            "b1_x_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_lane",
            0
          ],
          "destination": [
            "b1_x_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_lane",
            1
          ],
          "destination": [
            "b1_x_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_lane",
            2
          ],
          "destination": [
            "b1_x_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            0
          ],
          "destination": [
            "b1_y_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            1
          ],
          "destination": [
            "b1_y_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            2
          ],
          "destination": [
            "b1_y_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            3
          ],
          "destination": [
            "b1_y_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            4
          ],
          "destination": [
            "b1_y_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            5
          ],
          "destination": [
            "b1_y_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_ui",
            6
          ],
          "destination": [
            "b1_y_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_lane",
            0
          ],
          "destination": [
            "b1_y_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_lane",
            1
          ],
          "destination": [
            "b1_y_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_lane",
            2
          ],
          "destination": [
            "b1_y_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            0
          ],
          "destination": [
            "b1_spd_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            1
          ],
          "destination": [
            "b1_spd_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            2
          ],
          "destination": [
            "b1_spd_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            3
          ],
          "destination": [
            "b1_spd_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            4
          ],
          "destination": [
            "b1_spd_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            5
          ],
          "destination": [
            "b1_spd_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_ui",
            6
          ],
          "destination": [
            "b1_spd_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_lane",
            0
          ],
          "destination": [
            "b1_spd_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_lane",
            1
          ],
          "destination": [
            "b1_spd_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_lane",
            2
          ],
          "destination": [
            "b1_spd_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            0
          ],
          "destination": [
            "b1_size_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            1
          ],
          "destination": [
            "b1_size_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            2
          ],
          "destination": [
            "b1_size_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            3
          ],
          "destination": [
            "b1_size_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            4
          ],
          "destination": [
            "b1_size_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            5
          ],
          "destination": [
            "b1_size_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_ui",
            6
          ],
          "destination": [
            "b1_size_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_lane",
            0
          ],
          "destination": [
            "b1_size_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_lane",
            1
          ],
          "destination": [
            "b1_size_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_lane",
            2
          ],
          "destination": [
            "b1_size_ui",
            2
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
            "b1_x_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            3
          ],
          "destination": [
            "b1_spd_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            4
          ],
          "destination": [
            "b1_size_lane",
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
            "dbg_x_raw",
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
            "dbg_y_raw",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            3
          ],
          "destination": [
            "dbg_spd_raw",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_unpack",
            4
          ],
          "destination": [
            "dbg_size_raw",
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
            "b1_unpack",
            1
          ],
          "destination": [
            "b1_cx",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_cx",
            0
          ],
          "destination": [
            "b1_azi_calc",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_cy",
            0
          ],
          "destination": [
            "b1_azi_calc",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_cx",
            0
          ],
          "destination": [
            "b1_dist_calc",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_cy",
            0
          ],
          "destination": [
            "b1_dist_calc",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_calc",
            0
          ],
          "destination": [
            "b1_dist_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_calc",
            0
          ],
          "destination": [
            "dbg_azi_raw",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            0
          ],
          "destination": [
            "b1_azi_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            1
          ],
          "destination": [
            "b1_azi_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            2
          ],
          "destination": [
            "b1_azi_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            3
          ],
          "destination": [
            "b1_azi_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            4
          ],
          "destination": [
            "b1_azi_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            5
          ],
          "destination": [
            "b1_azi_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_ui",
            6
          ],
          "destination": [
            "b1_azi_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_lane",
            0
          ],
          "destination": [
            "b1_azi_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_lane",
            1
          ],
          "destination": [
            "b1_azi_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_lane",
            2
          ],
          "destination": [
            "b1_azi_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            0
          ],
          "destination": [
            "b1_dist_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            1
          ],
          "destination": [
            "b1_dist_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            2
          ],
          "destination": [
            "b1_dist_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            3
          ],
          "destination": [
            "b1_dist_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            4
          ],
          "destination": [
            "b1_dist_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            5
          ],
          "destination": [
            "b1_dist_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_ui",
            6
          ],
          "destination": [
            "b1_dist_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_lane",
            0
          ],
          "destination": [
            "b1_dist_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_lane",
            1
          ],
          "destination": [
            "b1_dist_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_lane",
            2
          ],
          "destination": [
            "b1_dist_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_clip",
            0
          ],
          "destination": [
            "b1_dist_trim",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_trim",
            0
          ],
          "destination": [
            "b1_dist_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_trim",
            0
          ],
          "destination": [
            "dbg_dist_raw",
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
            "b1_y_inv",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_inv",
            0
          ],
          "destination": [
            "b1_y_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_inv",
            0
          ],
          "destination": [
            "b1_cy",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_calc",
            0
          ],
          "destination": [
            "b1_azi_cal_expr",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_inv_num",
            0
          ],
          "destination": [
            "b1_azi_cal_expr",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_off_num",
            0
          ],
          "destination": [
            "b1_azi_cal_expr",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_cal_expr",
            0
          ],
          "destination": [
            "b1_azi_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_inv_load",
            0
          ],
          "destination": [
            "b1_azi_inv_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_off_load",
            0
          ],
          "destination": [
            "b1_azi_off_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_gain_num",
            0
          ],
          "destination": [
            "b1_dist_trim",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_gain_load",
            0
          ],
          "destination": [
            "b1_dist_gain_num",
            0
          ]
        }
      }
    ],
    "openrect": [
      0.0,
      0.0,
      230.0,
      169.0
    ],
    "openrectmode": 0
  }
}