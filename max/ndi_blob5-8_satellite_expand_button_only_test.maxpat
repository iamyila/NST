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
      134.0,
      172.0,
      750.0,
      444.0
    ],
    "openrect": [
      0.0,
      0.0,
      230.0,
      169.0
    ],
    "openrectmode": 0,
    "openinpresentation": 1,
    "boxes": [
      {
        "box": {
          "id": "c0",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            40.0,
            10.0,
            560.0,
            20.0
          ],
          "text": "Blob 5: notes + X/Y/Spd/Size/Azi/Dist + map lanes (master style)"
        }
      },
      {
        "box": {
          "id": "obj-1",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            40.0,
            40.0,
            104.0,
            22.0
          ],
          "text": "udpreceive 12345"
        }
      },
      {
        "box": {
          "id": "obj-2",
          "maxclass": "newobj",
          "numinlets": 5,
          "numoutlets": 5,
          "outlettype": [
            "",
            "",
            "",
            "",
            ""
          ],
          "patching_rect": [
            40.0,
            75.0,
            790.0,
            22.0
          ],
          "text": "route NDITracker5 NDITracker6 NDITracker7 NDITracker8"
        }
      },
      {
        "box": {
          "id": "b1_tlb",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
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
          "numinlets": 1,
          "numoutlets": 3,
          "outlettype": [
            "bang",
            "bang",
            "bang"
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "bang"
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
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
          "numinlets": 1,
          "numoutlets": 3,
          "outlettype": [
            "",
            "int",
            "int"
          ],
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
          "numinlets": 3,
          "numoutlets": 3,
          "outlettype": [
            "bang",
            "bang",
            ""
          ],
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
          "numinlets": 1,
          "numoutlets": 8,
          "outlettype": [
            "int",
            "float",
            "float",
            "float",
            "float",
            "int",
            "float",
            "float"
          ],
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
          "numinlets": 1,
          "numoutlets": 3,
          "outlettype": [
            "",
            "int",
            "int"
          ],
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
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "bang",
            "bang"
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "bang"
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
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
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
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
          "id": "obj-40",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "int",
            "int"
          ],
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
          "numinlets": 3,
          "numoutlets": 0,
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
          "angle": 270.0,
          "background": 1,
          "bgcolor": [
            0.08,
            0.08,
            0.08,
            0.9
          ],
          "border": 1,
          "id": "b1_bank_panel",
          "maxclass": "panel",
          "mode": 0,
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            820.0,
            10.0,
            370.0,
            180.0
          ],
          "presentation": 1,
          "presentation_rect": [
            8.0,
            10.0,
            354.0,
            182.0
          ],
          "proportion": 0.39
        }
      },
      {
        "box": {
          "id": "b1_bank_title",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            828.0,
            12.0,
            120.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            16.0,
            12.0,
            120.0,
            20.0
          ],
          "text": "B5-8 Map Bank"
        }
      },
      {
        "box": {
          "id": "b1_hdr_param",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            878.0,
            144.0,
            96.0,
            20.0
          ],
          "text": "Parameter"
        }
      },
      {
        "box": {
          "id": "b1_hdr_mode",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            1000.0,
            144.0,
            80.0,
            20.0
          ],
          "text": "Mode"
        }
      },
      {
        "box": {
          "id": "b1_hdr_range",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            1098.0,
            144.0,
            80.0,
            20.0
          ],
          "text": "Range"
        }
      },
      {
        "box": {
          "id": "b1_x_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            36.0,
            30.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            36.0,
            30.0,
            20.0
          ],
          "text": "X"
        }
      },
      {
        "box": {
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_x_lane",
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
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
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "comment": "(float 0..1) value",
                  "id": "in_v",
                  "index": 1,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "map id",
                  "id": "in_map",
                  "index": 2,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "stop mapping",
                  "id": "in_stop",
                  "index": 3,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "min",
                  "id": "in_min",
                  "index": 4,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "max",
                  "id": "in_max",
                  "index": 5,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mode",
                  "id": "in_mode",
                  "index": 6,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "input polarity",
                  "id": "in_pol",
                  "index": 7,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "depth %",
                  "id": "in_depth",
                  "index": 8,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ],
                  "text": "clip 0. 1."
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ],
                  "text": "speedlim 5"
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ],
                  "text": "sig~ 0."
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
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
                  ],
                  "text": "poly~ Abl.Map"
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
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
                  ],
                  "text": "loadbang"
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
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
                  ],
                  "text": "0"
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
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
                  ],
                  "text": "1"
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
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
                  ],
                  "text": "50"
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ],
                  "text": "Abl.Map lane core (stabilized)"
                }
              },
              {
                "box": {
                  "comment": "value",
                  "id": "out_v",
                  "index": 1,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "wait",
                  "id": "out_wait",
                  "index": 2,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mapped",
                  "id": "out_mapped",
                  "index": 3,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "destination": [
                    "spd",
                    0
                  ],
                  "source": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "in_depth",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    1
                  ],
                  "source": [
                    "in_map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "in_max",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "source": [
                    "in_min",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "source": [
                    "in_mode",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "source": [
                    "in_pol",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    2
                  ],
                  "source": [
                    "in_stop",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "clip",
                    0
                  ],
                  "source": [
                    "in_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m0",
                    0
                  ],
                  "order": 3,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m1",
                    0
                  ],
                  "order": 1,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m100",
                    0
                  ],
                  "order": 2,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m50",
                    0
                  ],
                  "order": 0,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "order": 0,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "order": 1,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    9
                  ],
                  "order": 0,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    8
                  ],
                  "order": 1,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "order": 2,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_mapped",
                    0
                  ],
                  "source": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_v",
                    0
                  ],
                  "source": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_wait",
                    0
                  ],
                  "source": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    0
                  ],
                  "source": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "sig",
                    0
                  ],
                  "source": [
                    "spd",
                    0
                  ]
                }
              }
            ]
          },
          "patching_rect": [
            1008.0,
            442.0,
            110.0,
            22.0
          ],
          "text": "p b1_lane_x_core"
        }
      },
      {
        "box": {
          "id": "b1_y_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            58.0,
            30.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            58.0,
            30.0,
            20.0
          ],
          "text": "Y"
        }
      },
      {
        "box": {
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_y_lane",
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
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
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "comment": "(float 0..1) value",
                  "id": "in_v",
                  "index": 1,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "map id",
                  "id": "in_map",
                  "index": 2,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "stop mapping",
                  "id": "in_stop",
                  "index": 3,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "min",
                  "id": "in_min",
                  "index": 4,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "max",
                  "id": "in_max",
                  "index": 5,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mode",
                  "id": "in_mode",
                  "index": 6,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "input polarity",
                  "id": "in_pol",
                  "index": 7,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "depth %",
                  "id": "in_depth",
                  "index": 8,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ],
                  "text": "clip 0. 1."
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ],
                  "text": "speedlim 5"
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ],
                  "text": "sig~ 0."
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
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
                  ],
                  "text": "poly~ Abl.Map"
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
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
                  ],
                  "text": "loadbang"
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
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
                  ],
                  "text": "0"
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
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
                  ],
                  "text": "1"
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
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
                  ],
                  "text": "50"
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ],
                  "text": "Abl.Map lane core (stabilized)"
                }
              },
              {
                "box": {
                  "comment": "value",
                  "id": "out_v",
                  "index": 1,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "wait",
                  "id": "out_wait",
                  "index": 2,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mapped",
                  "id": "out_mapped",
                  "index": 3,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "destination": [
                    "spd",
                    0
                  ],
                  "source": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "in_depth",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    1
                  ],
                  "source": [
                    "in_map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "in_max",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "source": [
                    "in_min",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "source": [
                    "in_mode",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "source": [
                    "in_pol",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    2
                  ],
                  "source": [
                    "in_stop",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "clip",
                    0
                  ],
                  "source": [
                    "in_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m0",
                    0
                  ],
                  "order": 3,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m1",
                    0
                  ],
                  "order": 1,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m100",
                    0
                  ],
                  "order": 2,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m50",
                    0
                  ],
                  "order": 0,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "order": 0,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "order": 1,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    9
                  ],
                  "order": 0,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    8
                  ],
                  "order": 1,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "order": 2,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_mapped",
                    0
                  ],
                  "source": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_v",
                    0
                  ],
                  "source": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_wait",
                    0
                  ],
                  "source": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    0
                  ],
                  "source": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "sig",
                    0
                  ],
                  "source": [
                    "spd",
                    0
                  ]
                }
              }
            ]
          },
          "patching_rect": [
            1008.0,
            552.0,
            110.0,
            22.0
          ],
          "text": "p b1_lane_y_core"
        }
      },
      {
        "box": {
          "id": "b1_spd_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            102.0,
            36.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            102.0,
            36.0,
            20.0
          ],
          "text": "Spd"
        }
      },
      {
        "box": {
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_spd_lane",
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
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
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "comment": "(float 0..1) value",
                  "id": "in_v",
                  "index": 1,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "map id",
                  "id": "in_map",
                  "index": 2,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "stop mapping",
                  "id": "in_stop",
                  "index": 3,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "min",
                  "id": "in_min",
                  "index": 4,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "max",
                  "id": "in_max",
                  "index": 5,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mode",
                  "id": "in_mode",
                  "index": 6,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "input polarity",
                  "id": "in_pol",
                  "index": 7,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "depth %",
                  "id": "in_depth",
                  "index": 8,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ],
                  "text": "clip 0. 1."
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ],
                  "text": "speedlim 5"
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ],
                  "text": "sig~ 0."
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
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
                  ],
                  "text": "poly~ Abl.Map"
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
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
                  ],
                  "text": "loadbang"
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
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
                  ],
                  "text": "0"
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
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
                  ],
                  "text": "1"
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
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
                  ],
                  "text": "50"
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ],
                  "text": "Abl.Map lane core (stabilized)"
                }
              },
              {
                "box": {
                  "comment": "value",
                  "id": "out_v",
                  "index": 1,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "wait",
                  "id": "out_wait",
                  "index": 2,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mapped",
                  "id": "out_mapped",
                  "index": 3,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "destination": [
                    "spd",
                    0
                  ],
                  "source": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "in_depth",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    1
                  ],
                  "source": [
                    "in_map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "in_max",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "source": [
                    "in_min",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "source": [
                    "in_mode",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "source": [
                    "in_pol",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    2
                  ],
                  "source": [
                    "in_stop",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "clip",
                    0
                  ],
                  "source": [
                    "in_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m0",
                    0
                  ],
                  "order": 3,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m1",
                    0
                  ],
                  "order": 1,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m100",
                    0
                  ],
                  "order": 2,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m50",
                    0
                  ],
                  "order": 0,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "order": 0,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "order": 1,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    9
                  ],
                  "order": 0,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    8
                  ],
                  "order": 1,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "order": 2,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_mapped",
                    0
                  ],
                  "source": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_v",
                    0
                  ],
                  "source": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_wait",
                    0
                  ],
                  "source": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    0
                  ],
                  "source": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "sig",
                    0
                  ],
                  "source": [
                    "spd",
                    0
                  ]
                }
              }
            ]
          },
          "patching_rect": [
            1008.0,
            662.0,
            113.0,
            22.0
          ],
          "text": "p b1_lane_azi_core"
        }
      },
      {
        "box": {
          "id": "b1_size_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            124.0,
            36.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            124.0,
            36.0,
            20.0
          ],
          "text": "Size"
        }
      },
      {
        "box": {
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_size_lane",
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
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
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "comment": "(float 0..1) value",
                  "id": "in_v",
                  "index": 1,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "map id",
                  "id": "in_map",
                  "index": 2,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "stop mapping",
                  "id": "in_stop",
                  "index": 3,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "min",
                  "id": "in_min",
                  "index": 4,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "max",
                  "id": "in_max",
                  "index": 5,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mode",
                  "id": "in_mode",
                  "index": 6,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "input polarity",
                  "id": "in_pol",
                  "index": 7,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "depth %",
                  "id": "in_depth",
                  "index": 8,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ],
                  "text": "clip 0. 1."
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ],
                  "text": "speedlim 5"
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ],
                  "text": "sig~ 0."
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
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
                  ],
                  "text": "poly~ Abl.Map"
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
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
                  ],
                  "text": "loadbang"
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
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
                  ],
                  "text": "0"
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
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
                  ],
                  "text": "1"
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
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
                  ],
                  "text": "50"
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ],
                  "text": "Abl.Map lane core (stabilized)"
                }
              },
              {
                "box": {
                  "comment": "value",
                  "id": "out_v",
                  "index": 1,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "wait",
                  "id": "out_wait",
                  "index": 2,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mapped",
                  "id": "out_mapped",
                  "index": 3,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "destination": [
                    "spd",
                    0
                  ],
                  "source": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "in_depth",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    1
                  ],
                  "source": [
                    "in_map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "in_max",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "source": [
                    "in_min",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "source": [
                    "in_mode",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "source": [
                    "in_pol",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    2
                  ],
                  "source": [
                    "in_stop",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "clip",
                    0
                  ],
                  "source": [
                    "in_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m0",
                    0
                  ],
                  "order": 3,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m1",
                    0
                  ],
                  "order": 1,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m100",
                    0
                  ],
                  "order": 2,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m50",
                    0
                  ],
                  "order": 0,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "order": 0,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "order": 1,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    9
                  ],
                  "order": 0,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    8
                  ],
                  "order": 1,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "order": 2,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_mapped",
                    0
                  ],
                  "source": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_v",
                    0
                  ],
                  "source": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_wait",
                    0
                  ],
                  "source": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    0
                  ],
                  "source": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "sig",
                    0
                  ],
                  "source": [
                    "spd",
                    0
                  ]
                }
              }
            ]
          },
          "patching_rect": [
            1008.0,
            772.0,
            117.0,
            22.0
          ],
          "text": "p b1_lane_dist_core"
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
          "viewvisibility": 1
        }
      },
      {
        "box": {
          "id": "b1_azi_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            146.0,
            36.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            146.0,
            36.0,
            20.0
          ],
          "text": "Azi"
        }
      },
      {
        "box": {
          "id": "b1_dist_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            830.0,
            168.0,
            36.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            168.0,
            36.0,
            20.0
          ],
          "text": "Dist"
        }
      },
      {
        "box": {
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "enablehscroll": 0,
          "enablevscroll": 0,
          "id": "b1_azi_ui",
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
          "id": "b1_dist_ui",
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
            168.0,
            300.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            166.0,
            300.0,
            20.0
          ],
          "viewvisibility": 1
        }
      },
      {
        "box": {
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_azi_lane",
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
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
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "comment": "(float 0..1) value",
                  "id": "in_v",
                  "index": 1,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "map id",
                  "id": "in_map",
                  "index": 2,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "stop mapping",
                  "id": "in_stop",
                  "index": 3,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "min",
                  "id": "in_min",
                  "index": 4,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "max",
                  "id": "in_max",
                  "index": 5,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mode",
                  "id": "in_mode",
                  "index": 6,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "input polarity",
                  "id": "in_pol",
                  "index": 7,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "depth %",
                  "id": "in_depth",
                  "index": 8,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ],
                  "text": "clip 0. 1."
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ],
                  "text": "speedlim 5"
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ],
                  "text": "sig~ 0."
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
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
                  ],
                  "text": "poly~ Abl.Map"
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
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
                  ],
                  "text": "loadbang"
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
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
                  ],
                  "text": "0"
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
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
                  ],
                  "text": "1"
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ],
                  "text": "Abl.Map lane core (stabilized)"
                }
              },
              {
                "box": {
                  "comment": "value",
                  "id": "out_v",
                  "index": 1,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "wait",
                  "id": "out_wait",
                  "index": 2,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mapped",
                  "id": "out_mapped",
                  "index": 3,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "destination": [
                    "spd",
                    0
                  ],
                  "source": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "in_depth",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    1
                  ],
                  "source": [
                    "in_map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "in_max",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "source": [
                    "in_min",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "source": [
                    "in_mode",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "source": [
                    "in_pol",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    2
                  ],
                  "source": [
                    "in_stop",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "clip",
                    0
                  ],
                  "source": [
                    "in_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m0",
                    0
                  ],
                  "order": 3,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m1",
                    0
                  ],
                  "order": 1,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m100",
                    0
                  ],
                  "order": 2,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m50",
                    0
                  ],
                  "order": 0,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "order": 0,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "order": 1,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    9
                  ],
                  "order": 0,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    8
                  ],
                  "order": 1,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "order": 2,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_mapped",
                    0
                  ],
                  "source": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_v",
                    0
                  ],
                  "source": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_wait",
                    0
                  ],
                  "source": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    0
                  ],
                  "source": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "sig",
                    0
                  ],
                  "source": [
                    "spd",
                    0
                  ]
                }
              }
            ]
          },
          "patching_rect": [
            1008.0,
            882.0,
            147.0,
            22.0
          ],
          "text": "p b1_lane_azi_extra_core"
        }
      },
      {
        "box": {
          "color": [
            0.686275,
            0.686275,
            0.686275,
            1.0
          ],
          "id": "b1_dist_lane",
          "maxclass": "newobj",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
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
              76.0,
              121.0,
              420.0,
              260.0
            ],
            "boxes": [
              {
                "box": {
                  "comment": "(float 0..1) value",
                  "id": "in_v",
                  "index": 1,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    "float"
                  ],
                  "patching_rect": [
                    20.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "map id",
                  "id": "in_map",
                  "index": 2,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    55.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "stop mapping",
                  "id": "in_stop",
                  "index": 3,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    90.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "min",
                  "id": "in_min",
                  "index": 4,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    125.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "max",
                  "id": "in_max",
                  "index": 5,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    160.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mode",
                  "id": "in_mode",
                  "index": 6,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    195.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "input polarity",
                  "id": "in_pol",
                  "index": 7,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    230.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "depth %",
                  "id": "in_depth",
                  "index": 8,
                  "maxclass": "inlet",
                  "numinlets": 0,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    265.0,
                    20.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "id": "clip",
                  "maxclass": "newobj",
                  "numinlets": 3,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    58.0,
                    58.0,
                    22.0
                  ],
                  "text": "clip 0. 1."
                }
              },
              {
                "box": {
                  "id": "spd",
                  "maxclass": "newobj",
                  "numinlets": 2,
                  "numoutlets": 1,
                  "outlettype": [
                    ""
                  ],
                  "patching_rect": [
                    20.0,
                    88.0,
                    70.0,
                    22.0
                  ],
                  "text": "speedlim 5"
                }
              },
              {
                "box": {
                  "id": "sig",
                  "maxclass": "newobj",
                  "numinlets": 1,
                  "numoutlets": 1,
                  "outlettype": [
                    "signal"
                  ],
                  "patching_rect": [
                    20.0,
                    118.0,
                    48.0,
                    22.0
                  ],
                  "text": "sig~ 0."
                }
              },
              {
                "box": {
                  "id": "map",
                  "maxclass": "newobj",
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
                  ],
                  "text": "poly~ Abl.Map"
                }
              },
              {
                "box": {
                  "id": "lb",
                  "maxclass": "newobj",
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
                  ],
                  "text": "loadbang"
                }
              },
              {
                "box": {
                  "id": "m0",
                  "maxclass": "message",
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
                  ],
                  "text": "0"
                }
              },
              {
                "box": {
                  "id": "m100",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "m1",
                  "maxclass": "message",
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
                  ],
                  "text": "1"
                }
              },
              {
                "box": {
                  "id": "m50",
                  "maxclass": "message",
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
                  ],
                  "text": "100"
                }
              },
              {
                "box": {
                  "id": "note",
                  "maxclass": "comment",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    115.0,
                    154.0,
                    170.0,
                    20.0
                  ],
                  "text": "Abl.Map lane core (stabilized)"
                }
              },
              {
                "box": {
                  "comment": "value",
                  "id": "out_v",
                  "index": 1,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    20.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "wait",
                  "id": "out_wait",
                  "index": 2,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    55.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              },
              {
                "box": {
                  "comment": "mapped",
                  "id": "out_mapped",
                  "index": 3,
                  "maxclass": "outlet",
                  "numinlets": 1,
                  "numoutlets": 0,
                  "patching_rect": [
                    90.0,
                    196.0,
                    25.0,
                    25.0
                  ]
                }
              }
            ],
            "lines": [
              {
                "patchline": {
                  "destination": [
                    "spd",
                    0
                  ],
                  "source": [
                    "clip",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "in_depth",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    1
                  ],
                  "source": [
                    "in_map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "in_max",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "source": [
                    "in_min",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "source": [
                    "in_mode",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "source": [
                    "in_pol",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    2
                  ],
                  "source": [
                    "in_stop",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "clip",
                    0
                  ],
                  "source": [
                    "in_v",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m0",
                    0
                  ],
                  "order": 3,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m1",
                    0
                  ],
                  "order": 1,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m100",
                    0
                  ],
                  "order": 2,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "m50",
                    0
                  ],
                  "order": 0,
                  "source": [
                    "lb",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    5
                  ],
                  "order": 0,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    3
                  ],
                  "order": 1,
                  "source": [
                    "m0",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    9
                  ],
                  "order": 0,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    8
                  ],
                  "order": 1,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    6
                  ],
                  "order": 2,
                  "source": [
                    "m1",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    4
                  ],
                  "source": [
                    "m100",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    7
                  ],
                  "source": [
                    "m50",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_mapped",
                    0
                  ],
                  "source": [
                    "map",
                    2
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_v",
                    0
                  ],
                  "source": [
                    "map",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "out_wait",
                    0
                  ],
                  "source": [
                    "map",
                    1
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "map",
                    0
                  ],
                  "source": [
                    "sig",
                    0
                  ]
                }
              },
              {
                "patchline": {
                  "destination": [
                    "sig",
                    0
                  ],
                  "source": [
                    "spd",
                    0
                  ]
                }
              }
            ]
          },
          "patching_rect": [
            1008.0,
            992.0,
            150.0,
            22.0
          ],
          "text": "p b1_lane_dist_extra_core"
        }
      },
      {
        "box": {
          "id": "b1_cx",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1180.0,
            620.0,
            90.0,
            22.0
          ],
          "text": "expr $f1 - 0.5"
        }
      },
      {
        "box": {
          "id": "b1_cy",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1278.0,
            620.0,
            90.0,
            22.0
          ],
          "text": "expr $f1 - 0.5"
        }
      },
      {
        "box": {
          "id": "b1_azi_calc",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1180.0,
            650.0,
            417.0,
            22.0
          ],
          "text": "expr (0.5 - atan2(-$f1\\,$f2)/6.2831853) - floor(0.5 - atan2(-$f1\\,$f2)/6.2831853)"
        }
      },
      {
        "box": {
          "id": "b1_dist_calc",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1180.0,
            680.0,
            287.0,
            22.0
          ],
          "text": "expr pow((sqrt(($f1*$f1)+($f2*$f2))/0.70710678)\\,1.1)"
        }
      },
      {
        "box": {
          "id": "b1_dist_clip",
          "maxclass": "newobj",
          "numinlets": 3,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1440.0,
            680.0,
            60.0,
            22.0
          ],
          "text": "clip 0. 1."
        }
      },
      {
        "box": {
          "id": "b1_dist_trim",
          "maxclass": "newobj",
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
          ],
          "text": "* 1."
        }
      },
      {
        "box": {
          "id": "b1_y_inv",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1278.0,
            592.0,
            90.0,
            22.0
          ],
          "text": "expr 1. - $f1"
        }
      },
      {
        "box": {
          "id": "b1_azi_cal_expr",
          "maxclass": "newobj",
          "numinlets": 3,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1180.0,
            740.0,
            370.0,
            22.0
          ],
          "text": "expr (($f1*$f2)+$f3) - floor((($f1*$f2)+$f3))"
        }
      },
      {
        "box": {
          "format": 6,
          "id": "b1_azi_inv_num",
          "maxclass": "flonum",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "parameter_enable": 0,
          "patching_rect": [
            1180.0,
            770.0,
            60.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "format": 6,
          "id": "b1_azi_off_num",
          "maxclass": "flonum",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "parameter_enable": 0,
          "patching_rect": [
            1250.0,
            770.0,
            60.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "format": 6,
          "id": "b1_dist_gain_num",
          "maxclass": "flonum",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "parameter_enable": 0,
          "patching_rect": [
            1510.0,
            710.0,
            60.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_azi_inv_load",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1180.0,
            798.0,
            90.0,
            22.0
          ],
          "text": "loadmess 1."
        }
      },
      {
        "box": {
          "id": "b1_azi_off_load",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
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
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1510.0,
            738.0,
            90.0,
            22.0
          ],
          "text": "loadmess 0.5"
        }
      },
      {
        "box": {
          "id": "bus_send",
          "maxclass": "newobj",
          "text": "s ndi_tracker_bus",
          "patching_rect": [
            220.0,
            62.0,
            120.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "b1_azi_lane_clear_id0",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1173.0,
            882.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b1_dist_lane_clear_id0",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1173.0,
            992.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b1_size_lane_clear_id0",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1173.0,
            772.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b1_spd_lane_clear_id0",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1173.0,
            662.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b1_x_lane_clear_id0",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1173.0,
            442.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "b1_y_lane_clear_id0",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1173.0,
            552.0,
            30.0,
            22.0
          ],
          "text": "0"
        }
      },
      {
        "box": {
          "id": "blob_sel_label",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Blob",
          "patching_rect": [
            1168.0,
            12.0,
            36.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            258.0,
            12.0,
            36.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_num",
          "maxclass": "number",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "",
            "bang"
          ],
          "patching_rect": [
            1206.0,
            12.0,
            40.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            286.0,
            12.0,
            50.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_load",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "text": "loadmess 5",
          "patching_rect": [
            1158.0,
            44.0,
            72.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_clip",
          "maxclass": "newobj",
          "numinlets": 3,
          "numoutlets": 1,
          "outlettype": [
            "int"
          ],
          "text": "clip 5 8",
          "patching_rect": [
            1206.0,
            44.0,
            64.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_t",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "int",
            "int"
          ],
          "text": "t i i",
          "patching_rect": [
            1206.0,
            72.0,
            36.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_set",
          "maxclass": "message",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "text": "set $1",
          "patching_rect": [
            1248.0,
            72.0,
            44.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_idx",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "int"
          ],
          "text": "expr $i1 - 4",
          "patching_rect": [
            1206.0,
            100.0,
            84.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_mux",
          "maxclass": "newobj",
          "numinlets": 5,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "text": "switch 4 1",
          "patching_rect": [
            840.0,
            190.0,
            76.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_y_map_a_scale",
          "maxclass": "newobj",
          "text": "scale 0. 1. 0.08 0.9",
          "numinlets": 6,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1248.0,
            585.0,
            130.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "b1_expand_btn",
          "maxclass": "textbutton",
          "numinlets": 1,
          "numoutlets": 3,
          "outlettype": [
            "",
            "int",
            "int"
          ],
          "text": "---",
          "texton": "---",
          "patching_rect": [
            1228.0,
            12.0,
            18.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            338.0,
            12.0,
            18.0,
            20.0
          ],
          "bgcolor": [
            0.05,
            0.05,
            0.05,
            1.0
          ],
          "bgoncolor": [
            0.12,
            0.12,
            0.12,
            1.0
          ],
          "textcolor": [
            1.0,
            0.75,
            0.35,
            1.0
          ],
          "textoncolor": [
            0.278431,
            0.839216,
            1.0,
            1.0
          ],
          "rounded": 2.0
        }
      },
      {
        "box": {
          "id": "b1_expand_hint",
          "maxclass": "comment",
          "text": "expand",
          "fontsize": 9.0,
          "textcolor": [
            1.0,
            1.0,
            1.0,
            0.45
          ],
          "patching_rect": [
            1228.0,
            34.0,
            42.0,
            16.0
          ],
          "presentation": 1,
          "presentation_rect": [
            300.0,
            32.0,
            38.0,
            14.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "destination": [
            "b1_alive_ch",
            0
          ],
          "source": [
            "b1_0",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_alive_ch",
            0
          ],
          "source": [
            "b1_1",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_sel",
            0
          ],
          "source": [
            "b1_alive_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_1",
            0
          ],
          "source": [
            "b1_alive_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_delay",
            0
          ],
          "source": [
            "b1_alive_t",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_stop",
            0
          ],
          "source": [
            "b1_alive_t",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            0
          ],
          "source": [
            "b1_azi_cal_expr",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_cal_expr",
            0
          ],
          "source": [
            "b1_azi_calc",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_inv_num",
            0
          ],
          "source": [
            "b1_azi_inv_load",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_cal_expr",
            1
          ],
          "source": [
            "b1_azi_inv_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_ui",
            2
          ],
          "source": [
            "b1_azi_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_ui",
            1
          ],
          "source": [
            "b1_azi_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_ui",
            0
          ],
          "source": [
            "b1_azi_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_off_num",
            0
          ],
          "source": [
            "b1_azi_off_load",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_cal_expr",
            2
          ],
          "source": [
            "b1_azi_off_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            7
          ],
          "source": [
            "b1_azi_ui",
            6
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            6
          ],
          "source": [
            "b1_azi_ui",
            5
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            5
          ],
          "source": [
            "b1_azi_ui",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            4
          ],
          "source": [
            "b1_azi_ui",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            3
          ],
          "source": [
            "b1_azi_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            2
          ],
          "source": [
            "b1_azi_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_lane",
            1
          ],
          "source": [
            "b1_azi_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_calc",
            0
          ],
          "order": 1,
          "source": [
            "b1_cx",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_calc",
            0
          ],
          "order": 0,
          "source": [
            "b1_cx",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_azi_calc",
            1
          ],
          "order": 0,
          "source": [
            "b1_cy",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_calc",
            1
          ],
          "order": 1,
          "source": [
            "b1_cy",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_0",
            0
          ],
          "source": [
            "b1_delay",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_clip",
            0
          ],
          "source": [
            "b1_dist_calc",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_trim",
            0
          ],
          "source": [
            "b1_dist_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_gain_num",
            0
          ],
          "source": [
            "b1_dist_gain_load",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_trim",
            1
          ],
          "source": [
            "b1_dist_gain_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_ui",
            2
          ],
          "source": [
            "b1_dist_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_ui",
            1
          ],
          "source": [
            "b1_dist_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_ui",
            0
          ],
          "source": [
            "b1_dist_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            0
          ],
          "source": [
            "b1_dist_trim",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            7
          ],
          "source": [
            "b1_dist_ui",
            6
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            6
          ],
          "source": [
            "b1_dist_ui",
            5
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            5
          ],
          "source": [
            "b1_dist_ui",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            4
          ],
          "source": [
            "b1_dist_ui",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            3
          ],
          "source": [
            "b1_dist_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            2
          ],
          "source": [
            "b1_dist_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_dist_lane",
            1
          ],
          "source": [
            "b1_dist_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_lbl_t",
            0
          ],
          "source": [
            "b1_label_ch",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "obj-40",
            0
          ],
          "source": [
            "b1_off",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "obj-40",
            0
          ],
          "source": [
            "b1_on",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_off",
            0
          ],
          "source": [
            "b1_sel",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_on",
            0
          ],
          "source": [
            "b1_sel",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_ui",
            2
          ],
          "source": [
            "b1_size_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_ui",
            1
          ],
          "source": [
            "b1_size_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_ui",
            0
          ],
          "source": [
            "b1_size_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            7
          ],
          "source": [
            "b1_size_ui",
            6
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            6
          ],
          "source": [
            "b1_size_ui",
            5
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            5
          ],
          "source": [
            "b1_size_ui",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            4
          ],
          "source": [
            "b1_size_ui",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            3
          ],
          "source": [
            "b1_size_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            2
          ],
          "source": [
            "b1_size_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            1
          ],
          "source": [
            "b1_size_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_ui",
            2
          ],
          "source": [
            "b1_spd_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_ui",
            1
          ],
          "source": [
            "b1_spd_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_ui",
            0
          ],
          "source": [
            "b1_spd_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            7
          ],
          "source": [
            "b1_spd_ui",
            6
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            6
          ],
          "source": [
            "b1_spd_ui",
            5
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            5
          ],
          "source": [
            "b1_spd_ui",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            4
          ],
          "source": [
            "b1_spd_ui",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            3
          ],
          "source": [
            "b1_spd_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            2
          ],
          "source": [
            "b1_spd_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            1
          ],
          "source": [
            "b1_spd_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_delay",
            0
          ],
          "source": [
            "b1_stop",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_alive_t",
            0
          ],
          "source": [
            "b1_tlb",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_unpack",
            0
          ],
          "source": [
            "b1_tlb",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_cx",
            0
          ],
          "order": 0,
          "source": [
            "b1_unpack",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_label_ch",
            0
          ],
          "source": [
            "b1_unpack",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_size_lane",
            0
          ],
          "source": [
            "b1_unpack",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_spd_lane",
            0
          ],
          "source": [
            "b1_unpack",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            0
          ],
          "order": 1,
          "source": [
            "b1_unpack",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_inv",
            0
          ],
          "source": [
            "b1_unpack",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_ui",
            2
          ],
          "source": [
            "b1_x_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_ui",
            1
          ],
          "source": [
            "b1_x_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_ui",
            0
          ],
          "source": [
            "b1_x_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            7
          ],
          "source": [
            "b1_x_ui",
            6
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            6
          ],
          "source": [
            "b1_x_ui",
            5
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            5
          ],
          "source": [
            "b1_x_ui",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            4
          ],
          "source": [
            "b1_x_ui",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            3
          ],
          "source": [
            "b1_x_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            2
          ],
          "source": [
            "b1_x_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_x_lane",
            1
          ],
          "source": [
            "b1_x_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_ui",
            2
          ],
          "source": [
            "b1_y_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_ui",
            1
          ],
          "source": [
            "b1_y_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_ui",
            0
          ],
          "source": [
            "b1_y_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            7
          ],
          "source": [
            "b1_y_ui",
            6
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            6
          ],
          "source": [
            "b1_y_ui",
            5
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            5
          ],
          "source": [
            "b1_y_ui",
            4
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            4
          ],
          "source": [
            "b1_y_ui",
            3
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            3
          ],
          "source": [
            "b1_y_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            2
          ],
          "source": [
            "b1_y_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "b1_y_lane",
            1
          ],
          "source": [
            "b1_y_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "obj-2",
            0
          ],
          "source": [
            "obj-1",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "obj-41",
            1
          ],
          "source": [
            "obj-40",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "obj-41",
            0
          ],
          "source": [
            "obj-40",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-1",
            0
          ],
          "destination": [
            "bus_send",
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
            "b1_azi_lane_clear_id0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_azi_lane_clear_id0",
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
            "b1_dist_lane",
            1
          ],
          "destination": [
            "b1_dist_lane_clear_id0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_dist_lane_clear_id0",
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
            "b1_size_lane",
            1
          ],
          "destination": [
            "b1_size_lane_clear_id0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_size_lane_clear_id0",
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
            "b1_spd_lane",
            1
          ],
          "destination": [
            "b1_spd_lane_clear_id0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_spd_lane_clear_id0",
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
            "b1_x_lane",
            1
          ],
          "destination": [
            "b1_x_lane_clear_id0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_x_lane_clear_id0",
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
            "b1_y_lane",
            1
          ],
          "destination": [
            "b1_y_lane_clear_id0",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_lane_clear_id0",
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
            "obj-2",
            0
          ],
          "destination": [
            "blob_sel_mux",
            1
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
            "blob_sel_mux",
            2
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
            "blob_sel_mux",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-2",
            3
          ],
          "destination": [
            "blob_sel_mux",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_mux",
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
            "blob_sel_load",
            0
          ],
          "destination": [
            "blob_sel_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_num",
            0
          ],
          "destination": [
            "blob_sel_clip",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_clip",
            0
          ],
          "destination": [
            "blob_sel_t",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_t",
            0
          ],
          "destination": [
            "blob_sel_idx",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_t",
            1
          ],
          "destination": [
            "blob_sel_set",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_set",
            0
          ],
          "destination": [
            "blob_sel_num",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "blob_sel_idx",
            0
          ],
          "destination": [
            "blob_sel_mux",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_y_map_a_scale",
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
            "b1_y_inv",
            0
          ],
          "destination": [
            "b1_y_map_a_scale",
            0
          ]
        }
      }
    ],
    "parameters": {
      "b1_azi_ui::obj-103": [
        "border[18]",
        "border",
        0
      ],
      "b1_azi_ui::obj-2": [
        "mode[5]",
        "Modulation",
        0
      ],
      "b1_azi_ui::obj-25": [
        "Map[7]",
        "Map",
        0
      ],
      "b1_azi_ui::obj-26": [
        "border[14]",
        "border",
        0
      ],
      "b1_azi_ui::obj-30": [
        "Unmap[19]",
        "Unmap",
        0
      ],
      "b1_azi_ui::obj-32": [
        "TargetMax[10]",
        "Max",
        0
      ],
      "b1_azi_ui::obj-33": [
        "TargetMin[10]",
        "Min",
        0
      ],
      "b1_azi_ui::obj-6": [
        "Modulation Polarity 1[7]",
        "Polarity",
        0
      ],
      "b1_azi_ui::obj-9": [
        "Modulation Amount 1[7]",
        "ModAmount",
        0
      ],
      "b1_dist_ui::obj-103": [
        "border[13]",
        "border",
        0
      ],
      "b1_dist_ui::obj-2": [
        "mode[4]",
        "Modulation",
        0
      ],
      "b1_dist_ui::obj-25": [
        "Map[6]",
        "Map",
        0
      ],
      "b1_dist_ui::obj-26": [
        "border[12]",
        "border",
        0
      ],
      "b1_dist_ui::obj-30": [
        "Unmap[5]",
        "Unmap",
        0
      ],
      "b1_dist_ui::obj-32": [
        "TargetMax[9]",
        "Max",
        0
      ],
      "b1_dist_ui::obj-33": [
        "TargetMin[9]",
        "Min",
        0
      ],
      "b1_dist_ui::obj-6": [
        "Modulation Polarity 1[6]",
        "Polarity",
        0
      ],
      "b1_dist_ui::obj-9": [
        "Modulation Amount 1[6]",
        "ModAmount",
        0
      ],
      "b1_size_ui::obj-103": [
        "border[15]",
        "border",
        0
      ],
      "b1_size_ui::obj-2": [
        "mode[6]",
        "Modulation",
        0
      ],
      "b1_size_ui::obj-25": [
        "Map[8]",
        "Map",
        0
      ],
      "b1_size_ui::obj-26": [
        "border[19]",
        "border",
        0
      ],
      "b1_size_ui::obj-30": [
        "Unmap[6]",
        "Unmap",
        0
      ],
      "b1_size_ui::obj-32": [
        "TargetMax[11]",
        "Max",
        0
      ],
      "b1_size_ui::obj-33": [
        "TargetMin[11]",
        "Min",
        0
      ],
      "b1_size_ui::obj-6": [
        "Modulation Polarity 1[8]",
        "Polarity",
        0
      ],
      "b1_size_ui::obj-9": [
        "Modulation Amount 1[8]",
        "ModAmount",
        0
      ],
      "b1_spd_ui::obj-103": [
        "border[21]",
        "border",
        0
      ],
      "b1_spd_ui::obj-2": [
        "mode[14]",
        "Modulation",
        0
      ],
      "b1_spd_ui::obj-25": [
        "Map[9]",
        "Map",
        0
      ],
      "b1_spd_ui::obj-26": [
        "border[20]",
        "border",
        0
      ],
      "b1_spd_ui::obj-30": [
        "Unmap[7]",
        "Unmap",
        0
      ],
      "b1_spd_ui::obj-32": [
        "TargetMax[12]",
        "Max",
        0
      ],
      "b1_spd_ui::obj-33": [
        "TargetMin[12]",
        "Min",
        0
      ],
      "b1_spd_ui::obj-6": [
        "Modulation Polarity 1[9]",
        "Polarity",
        0
      ],
      "b1_spd_ui::obj-9": [
        "Modulation Amount 1[9]",
        "ModAmount",
        0
      ],
      "b1_x_ui::obj-103": [
        "border[24]",
        "border",
        0
      ],
      "b1_x_ui::obj-2": [
        "mode[16]",
        "Modulation",
        0
      ],
      "b1_x_ui::obj-25": [
        "Map[11]",
        "Map",
        0
      ],
      "b1_x_ui::obj-26": [
        "border[25]",
        "border",
        0
      ],
      "b1_x_ui::obj-30": [
        "Unmap[9]",
        "Unmap",
        0
      ],
      "b1_x_ui::obj-32": [
        "TargetMax[14]",
        "Max",
        0
      ],
      "b1_x_ui::obj-33": [
        "TargetMin[14]",
        "Min",
        0
      ],
      "b1_x_ui::obj-6": [
        "Modulation Polarity 1[11]",
        "Polarity",
        0
      ],
      "b1_x_ui::obj-9": [
        "Modulation Amount 1[11]",
        "ModAmount",
        0
      ],
      "b1_y_ui::obj-103": [
        "border[23]",
        "border",
        0
      ],
      "b1_y_ui::obj-2": [
        "mode[15]",
        "Modulation",
        0
      ],
      "b1_y_ui::obj-25": [
        "Map[10]",
        "Map",
        0
      ],
      "b1_y_ui::obj-26": [
        "border[22]",
        "border",
        0
      ],
      "b1_y_ui::obj-30": [
        "Unmap[8]",
        "Unmap",
        0
      ],
      "b1_y_ui::obj-32": [
        "TargetMax[13]",
        "Max",
        0
      ],
      "b1_y_ui::obj-33": [
        "TargetMin[13]",
        "Min",
        0
      ],
      "b1_y_ui::obj-6": [
        "Modulation Polarity 1[10]",
        "Polarity",
        0
      ],
      "b1_y_ui::obj-9": [
        "Modulation Amount 1[10]",
        "ModAmount",
        0
      ],
      "b2_azi_ui::obj-103": [
        "border[1]",
        "border",
        0
      ],
      "b2_azi_ui::obj-2": [
        "mode[1]",
        "Modulation",
        0
      ],
      "b2_azi_ui::obj-25": [
        "Map[1]",
        "Map",
        0
      ],
      "b2_azi_ui::obj-26": [
        "border[2]",
        "border",
        0
      ],
      "b2_azi_ui::obj-30": [
        "Unmap[1]",
        "Unmap",
        0
      ],
      "b2_azi_ui::obj-32": [
        "TargetMax[1]",
        "Max",
        0
      ],
      "b2_azi_ui::obj-33": [
        "TargetMin[1]",
        "Min",
        0
      ],
      "b2_azi_ui::obj-6": [
        "Modulation Polarity 1[1]",
        "Polarity",
        0
      ],
      "b2_azi_ui::obj-9": [
        "Modulation Amount 1[1]",
        "ModAmount",
        0
      ],
      "b2_dist_ui::obj-103": [
        "border[17]",
        "border",
        0
      ],
      "b2_dist_ui::obj-2": [
        "mode[11]",
        "Modulation",
        0
      ],
      "b2_dist_ui::obj-25": [
        "Map[16]",
        "Map",
        0
      ],
      "b2_dist_ui::obj-26": [
        "border[10]",
        "border",
        0
      ],
      "b2_dist_ui::obj-30": [
        "Unmap[17]",
        "Unmap",
        0
      ],
      "b2_dist_ui::obj-32": [
        "TargetMax[7]",
        "Max",
        0
      ],
      "b2_dist_ui::obj-33": [
        "TargetMin[7]",
        "Min",
        0
      ],
      "b2_dist_ui::obj-6": [
        "Modulation Polarity 1",
        "Polarity",
        0
      ],
      "b2_dist_ui::obj-9": [
        "Modulation Amount 1",
        "ModAmount",
        0
      ],
      "b2_size_ui::obj-103": [
        "border[4]",
        "border",
        0
      ],
      "b2_size_ui::obj-2": [
        "mode[12]",
        "Modulation",
        0
      ],
      "b2_size_ui::obj-25": [
        "Map[2]",
        "Map",
        0
      ],
      "b2_size_ui::obj-26": [
        "border[3]",
        "border",
        0
      ],
      "b2_size_ui::obj-30": [
        "Unmap[2]",
        "Unmap",
        0
      ],
      "b2_size_ui::obj-32": [
        "TargetMax[2]",
        "Max",
        0
      ],
      "b2_size_ui::obj-33": [
        "TargetMin[2]",
        "Min",
        0
      ],
      "b2_size_ui::obj-6": [
        "Modulation Polarity 1[2]",
        "Polarity",
        0
      ],
      "b2_size_ui::obj-9": [
        "Modulation Amount 1[2]",
        "ModAmount",
        0
      ],
      "b2_spd_ui::obj-103": [
        "border[6]",
        "border",
        0
      ],
      "b2_spd_ui::obj-2": [
        "mode[2]",
        "Modulation",
        0
      ],
      "b2_spd_ui::obj-25": [
        "Map[3]",
        "Map",
        0
      ],
      "b2_spd_ui::obj-26": [
        "border[5]",
        "border",
        0
      ],
      "b2_spd_ui::obj-30": [
        "Unmap[18]",
        "Unmap",
        0
      ],
      "b2_spd_ui::obj-32": [
        "TargetMax[3]",
        "Max",
        0
      ],
      "b2_spd_ui::obj-33": [
        "TargetMin[3]",
        "Min",
        0
      ],
      "b2_spd_ui::obj-6": [
        "Modulation Polarity 1[3]",
        "Polarity",
        0
      ],
      "b2_spd_ui::obj-9": [
        "Modulation Amount 1[3]",
        "ModAmount",
        0
      ],
      "b2_x_ui::obj-103": [
        "border[9]",
        "border",
        0
      ],
      "b2_x_ui::obj-2": [
        "mode[3]",
        "Modulation",
        0
      ],
      "b2_x_ui::obj-25": [
        "Map[5]",
        "Map",
        0
      ],
      "b2_x_ui::obj-26": [
        "border[11]",
        "border",
        0
      ],
      "b2_x_ui::obj-30": [
        "Unmap[4]",
        "Unmap",
        0
      ],
      "b2_x_ui::obj-32": [
        "TargetMax[8]",
        "Max",
        0
      ],
      "b2_x_ui::obj-33": [
        "TargetMin[8]",
        "Min",
        0
      ],
      "b2_x_ui::obj-6": [
        "Modulation Polarity 1[5]",
        "Polarity",
        0
      ],
      "b2_x_ui::obj-9": [
        "Modulation Amount 1[5]",
        "ModAmount",
        0
      ],
      "b2_y_ui::obj-103": [
        "border[7]",
        "border",
        0
      ],
      "b2_y_ui::obj-2": [
        "mode[13]",
        "Modulation",
        0
      ],
      "b2_y_ui::obj-25": [
        "Map[4]",
        "Map",
        0
      ],
      "b2_y_ui::obj-26": [
        "border[8]",
        "border",
        0
      ],
      "b2_y_ui::obj-30": [
        "Unmap[3]",
        "Unmap",
        0
      ],
      "b2_y_ui::obj-32": [
        "TargetMax[4]",
        "Max",
        0
      ],
      "b2_y_ui::obj-33": [
        "TargetMin[4]",
        "Min",
        0
      ],
      "b2_y_ui::obj-6": [
        "Modulation Polarity 1[4]",
        "Polarity",
        0
      ],
      "b2_y_ui::obj-9": [
        "Modulation Amount 1[4]",
        "ModAmount",
        0
      ],
      "parameterbanks": {
        "0": {
          "index": 0,
          "name": "",
          "parameters": [
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-"
          ],
          "buttons": [
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-"
          ]
        }
      },
      "parameter_overrides": {
        "b1_azi_ui::obj-103": {
          "parameter_longname": "border[18]"
        },
        "b1_azi_ui::obj-2": {
          "parameter_longname": "mode[5]"
        },
        "b1_azi_ui::obj-25": {
          "parameter_longname": "Map[7]"
        },
        "b1_azi_ui::obj-26": {
          "parameter_longname": "border[14]"
        },
        "b1_azi_ui::obj-30": {
          "parameter_longname": "Unmap[19]"
        },
        "b1_azi_ui::obj-32": {
          "parameter_longname": "TargetMax[10]"
        },
        "b1_azi_ui::obj-33": {
          "parameter_longname": "TargetMin[10]"
        },
        "b1_azi_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[7]"
        },
        "b1_azi_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[7]"
        },
        "b1_dist_ui::obj-103": {
          "parameter_longname": "border[13]"
        },
        "b1_dist_ui::obj-2": {
          "parameter_longname": "mode[4]"
        },
        "b1_dist_ui::obj-25": {
          "parameter_longname": "Map[6]"
        },
        "b1_dist_ui::obj-26": {
          "parameter_longname": "border[12]"
        },
        "b1_dist_ui::obj-30": {
          "parameter_longname": "Unmap[5]"
        },
        "b1_dist_ui::obj-32": {
          "parameter_longname": "TargetMax[9]"
        },
        "b1_dist_ui::obj-33": {
          "parameter_longname": "TargetMin[9]"
        },
        "b1_dist_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[6]"
        },
        "b1_dist_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[6]"
        },
        "b1_size_ui::obj-103": {
          "parameter_longname": "border[15]"
        },
        "b1_size_ui::obj-2": {
          "parameter_longname": "mode[6]"
        },
        "b1_size_ui::obj-25": {
          "parameter_longname": "Map[8]"
        },
        "b1_size_ui::obj-26": {
          "parameter_longname": "border[19]"
        },
        "b1_size_ui::obj-30": {
          "parameter_longname": "Unmap[6]"
        },
        "b1_size_ui::obj-32": {
          "parameter_longname": "TargetMax[11]"
        },
        "b1_size_ui::obj-33": {
          "parameter_longname": "TargetMin[11]"
        },
        "b1_size_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[8]"
        },
        "b1_size_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[8]"
        },
        "b1_spd_ui::obj-103": {
          "parameter_longname": "border[21]"
        },
        "b1_spd_ui::obj-2": {
          "parameter_longname": "mode[14]"
        },
        "b1_spd_ui::obj-25": {
          "parameter_longname": "Map[9]"
        },
        "b1_spd_ui::obj-26": {
          "parameter_longname": "border[20]"
        },
        "b1_spd_ui::obj-30": {
          "parameter_longname": "Unmap[7]"
        },
        "b1_spd_ui::obj-32": {
          "parameter_longname": "TargetMax[12]"
        },
        "b1_spd_ui::obj-33": {
          "parameter_longname": "TargetMin[12]"
        },
        "b1_spd_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[9]"
        },
        "b1_spd_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[9]"
        },
        "b1_x_ui::obj-103": {
          "parameter_longname": "border[24]"
        },
        "b1_x_ui::obj-2": {
          "parameter_longname": "mode[16]"
        },
        "b1_x_ui::obj-25": {
          "parameter_longname": "Map[11]"
        },
        "b1_x_ui::obj-26": {
          "parameter_longname": "border[25]"
        },
        "b1_x_ui::obj-30": {
          "parameter_longname": "Unmap[9]"
        },
        "b1_x_ui::obj-32": {
          "parameter_longname": "TargetMax[14]"
        },
        "b1_x_ui::obj-33": {
          "parameter_longname": "TargetMin[14]"
        },
        "b1_x_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[11]"
        },
        "b1_x_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[11]"
        },
        "b1_y_ui::obj-103": {
          "parameter_longname": "border[23]"
        },
        "b1_y_ui::obj-2": {
          "parameter_longname": "mode[15]"
        },
        "b1_y_ui::obj-25": {
          "parameter_longname": "Map[10]"
        },
        "b1_y_ui::obj-26": {
          "parameter_longname": "border[22]"
        },
        "b1_y_ui::obj-30": {
          "parameter_longname": "Unmap[8]"
        },
        "b1_y_ui::obj-32": {
          "parameter_longname": "TargetMax[13]"
        },
        "b1_y_ui::obj-33": {
          "parameter_longname": "TargetMin[13]"
        },
        "b1_y_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[10]"
        },
        "b1_y_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[10]"
        },
        "b2_azi_ui::obj-103": {
          "parameter_longname": "border[1]"
        },
        "b2_azi_ui::obj-2": {
          "parameter_longname": "mode[1]"
        },
        "b2_azi_ui::obj-25": {
          "parameter_longname": "Map[1]"
        },
        "b2_azi_ui::obj-26": {
          "parameter_longname": "border[2]"
        },
        "b2_azi_ui::obj-30": {
          "parameter_longname": "Unmap[1]"
        },
        "b2_azi_ui::obj-32": {
          "parameter_longname": "TargetMax[1]"
        },
        "b2_azi_ui::obj-33": {
          "parameter_longname": "TargetMin[1]"
        },
        "b2_azi_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[1]"
        },
        "b2_azi_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[1]"
        },
        "b2_size_ui::obj-103": {
          "parameter_longname": "border[4]"
        },
        "b2_size_ui::obj-2": {
          "parameter_longname": "mode[12]"
        },
        "b2_size_ui::obj-25": {
          "parameter_longname": "Map[2]"
        },
        "b2_size_ui::obj-26": {
          "parameter_longname": "border[3]"
        },
        "b2_size_ui::obj-30": {
          "parameter_longname": "Unmap[2]"
        },
        "b2_size_ui::obj-32": {
          "parameter_longname": "TargetMax[2]"
        },
        "b2_size_ui::obj-33": {
          "parameter_longname": "TargetMin[2]"
        },
        "b2_size_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[2]"
        },
        "b2_size_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[2]"
        },
        "b2_spd_ui::obj-103": {
          "parameter_longname": "border[6]"
        },
        "b2_spd_ui::obj-2": {
          "parameter_longname": "mode[2]"
        },
        "b2_spd_ui::obj-25": {
          "parameter_longname": "Map[3]"
        },
        "b2_spd_ui::obj-26": {
          "parameter_longname": "border[5]"
        },
        "b2_spd_ui::obj-30": {
          "parameter_longname": "Unmap[18]"
        },
        "b2_spd_ui::obj-32": {
          "parameter_longname": "TargetMax[3]"
        },
        "b2_spd_ui::obj-33": {
          "parameter_longname": "TargetMin[3]"
        },
        "b2_spd_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[3]"
        },
        "b2_spd_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[3]"
        },
        "b2_x_ui::obj-103": {
          "parameter_longname": "border[9]"
        },
        "b2_x_ui::obj-2": {
          "parameter_longname": "mode[3]"
        },
        "b2_x_ui::obj-25": {
          "parameter_longname": "Map[5]"
        },
        "b2_x_ui::obj-26": {
          "parameter_longname": "border[11]"
        },
        "b2_x_ui::obj-30": {
          "parameter_longname": "Unmap[4]"
        },
        "b2_x_ui::obj-32": {
          "parameter_longname": "TargetMax[8]"
        },
        "b2_x_ui::obj-33": {
          "parameter_longname": "TargetMin[8]"
        },
        "b2_x_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[5]"
        },
        "b2_x_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[5]"
        },
        "b2_y_ui::obj-103": {
          "parameter_longname": "border[7]"
        },
        "b2_y_ui::obj-2": {
          "parameter_longname": "mode[13]"
        },
        "b2_y_ui::obj-25": {
          "parameter_longname": "Map[4]"
        },
        "b2_y_ui::obj-26": {
          "parameter_longname": "border[8]"
        },
        "b2_y_ui::obj-30": {
          "parameter_longname": "Unmap[3]"
        },
        "b2_y_ui::obj-32": {
          "parameter_longname": "TargetMax[4]"
        },
        "b2_y_ui::obj-33": {
          "parameter_longname": "TargetMin[4]"
        },
        "b2_y_ui::obj-6": {
          "parameter_longname": "Modulation Polarity 1[4]"
        },
        "b2_y_ui::obj-9": {
          "parameter_longname": "Modulation Amount 1[4]"
        }
      },
      "inherited_shortname": 1
    },
    "autosave": 0
  }
}