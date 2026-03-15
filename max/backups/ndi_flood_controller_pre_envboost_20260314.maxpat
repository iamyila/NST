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
      1040.0,
      520.0
    ],
    "openinpresentation": 1,
    "gridsize": [
      15.0,
      15.0
    ],
    "boxes": [
      {
        "box": {
          "maxclass": "comment",
          "text": "Flood Controller (from blobs 5-8 edge hits)",
          "patching_rect": [
            20.0,
            16.0,
            300.0,
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
            46.0,
            104.0,
            22.0
          ],
          "id": "obj-2"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8",
          "patching_rect": [
            20.0,
            76.0,
            620.0,
            22.0
          ],
          "id": "obj-3"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f",
          "patching_rect": [
            20,
            112.0,
            145.0,
            22.0
          ],
          "id": "obj-4"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))",
          "patching_rect": [
            20,
            142.0,
            175.0,
            22.0
          ],
          "id": "obj-5"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f",
          "patching_rect": [
            200,
            112.0,
            145.0,
            22.0
          ],
          "id": "obj-6"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))",
          "patching_rect": [
            200,
            142.0,
            175.0,
            22.0
          ],
          "id": "obj-7"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f",
          "patching_rect": [
            380,
            112.0,
            145.0,
            22.0
          ],
          "id": "obj-8"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))",
          "patching_rect": [
            380,
            142.0,
            175.0,
            22.0
          ],
          "id": "obj-9"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f",
          "patching_rect": [
            560,
            112.0,
            145.0,
            22.0
          ],
          "id": "obj-10"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max(abs(($f1*2.)-1.), abs(($f2*2.)-1.))",
          "patching_rect": [
            560,
            142.0,
            175.0,
            22.0
          ],
          "id": "obj-11"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "pak f f f f",
          "patching_rect": [
            20.0,
            176.0,
            95.0,
            22.0
          ],
          "id": "obj-12"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "unpack f f f f",
          "patching_rect": [
            20.0,
            206.0,
            95.0,
            22.0
          ],
          "id": "obj-13"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max($f1,$f2)",
          "patching_rect": [
            20.0,
            236.0,
            95.0,
            22.0
          ],
          "id": "obj-14"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max($f1,$f2)",
          "patching_rect": [
            130.0,
            236.0,
            95.0,
            22.0
          ],
          "id": "obj-15"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr max($f1,$f2)",
          "patching_rect": [
            240.0,
            236.0,
            95.0,
            22.0
          ],
          "id": "obj-16"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "clip 0. 1.",
          "patching_rect": [
            350.0,
            236.0,
            60.0,
            22.0
          ],
          "id": "obj-17"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "scale 0. 1. 0. 100.",
          "patching_rect": [
            420.0,
            236.0,
            120.0,
            22.0
          ],
          "id": "obj-18"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "parameter_enable": 1,
          "varname": "Flood_EdgeIn",
          "patching_rect": [
            548.0,
            238.0,
            86.0,
            18.0
          ],
          "presentation": 0,
          "presentation_rect": [
            60.0,
            40.0,
            100.0,
            18.0
          ],
          "id": "obj-19"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "EdgeIn",
          "patching_rect": [
            640.0,
            238.0,
            50.0,
            20.0
          ],
          "presentation": 0,
          "presentation_rect": [
            12.0,
            40.0,
            44.0,
            20.0
          ],
          "id": "obj-20"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "expr ($f1>=98.5)*100.",
          "patching_rect": [
            420.0,
            268.0,
            140.0,
            22.0
          ],
          "id": "obj-21"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "parameter_enable": 1,
          "varname": "Flood_EdgeHit",
          "patching_rect": [
            568.0,
            270.0,
            86.0,
            18.0
          ],
          "presentation": 0,
          "presentation_rect": [
            60.0,
            66.0,
            100.0,
            18.0
          ],
          "id": "obj-22"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "EdgeHit",
          "patching_rect": [
            660.0,
            270.0,
            50.0,
            20.0
          ],
          "presentation": 0,
          "presentation_rect": [
            12.0,
            66.0,
            44.0,
            20.0
          ],
          "id": "obj-23"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "change",
          "patching_rect": [
            420.0,
            298.0,
            45.0,
            22.0
          ],
          "id": "obj-24"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "sel 100",
          "patching_rect": [
            474.0,
            298.0,
            52.0,
            22.0
          ],
          "id": "obj-25"
        }
      },
      {
        "box": {
          "maxclass": "message",
          "text": "0, 100 80, 70 260, 0 2200",
          "patching_rect": [
            536.0,
            298.0,
            180.0,
            22.0
          ],
          "id": "obj-26"
        }
      },
      {
        "box": {
          "maxclass": "newobj",
          "text": "line 0.",
          "patching_rect": [
            726.0,
            298.0,
            50.0,
            22.0
          ],
          "id": "obj-27"
        }
      },
      {
        "box": {
          "maxclass": "live.numbox",
          "parameter_enable": 1,
          "varname": "Flood_Env",
          "patching_rect": [
            786.0,
            300.0,
            86.0,
            18.0
          ],
          "presentation": 0,
          "presentation_rect": [
            60.0,
            92.0,
            100.0,
            18.0
          ],
          "id": "obj-28"
        }
      },
      {
        "box": {
          "maxclass": "comment",
          "text": "FloodEnv",
          "patching_rect": [
            878.0,
            300.0,
            60.0,
            20.0
          ],
          "presentation": 0,
          "presentation_rect": [
            12.0,
            92.0,
            48.0,
            20.0
          ],
          "id": "obj-29"
        }
      },
      {
        "box": {
          "id": "f_map_panel",
          "maxclass": "panel",
          "numinlets": 1,
          "numoutlets": 0,
          "angle": 270.0,
          "background": 1,
          "bgcolor": [
            0.08,
            0.08,
            0.08,
            0.9
          ],
          "border": 1,
          "mode": 0,
          "proportion": 0.39,
          "patching_rect": [
            900.0,
            18.0,
            370.0,
            116.0
          ],
          "presentation": 1,
          "presentation_rect": [
            8.0,
            10.0,
            354.0,
            116.0
          ]
        }
      },
      {
        "box": {
          "id": "f_map_title",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Flood Map Bank",
          "patching_rect": [
            908.0,
            20.0,
            140.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            16.0,
            12.0,
            140.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_edge_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Edge",
          "patching_rect": [
            910.0,
            44.0,
            40.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            36.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Hit",
          "patching_rect": [
            910.0,
            66.0,
            40.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            58.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_env_lab",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Env",
          "patching_rect": [
            910.0,
            88.0,
            40.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            18.0,
            80.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_hdr_param",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Parameter",
          "patching_rect": [
            950.0,
            106.0,
            96.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            56.0,
            92.0,
            96.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_hdr_mode",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Mode",
          "patching_rect": [
            1074.0,
            106.0,
            80.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            182.0,
            92.0,
            80.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_hdr_range",
          "maxclass": "comment",
          "numinlets": 1,
          "numoutlets": 0,
          "text": "Range",
          "patching_rect": [
            1172.0,
            106.0,
            80.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            280.0,
            92.0,
            80.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "f_edge_ui",
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
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
            948.0,
            44.0,
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
          "enablehscroll": 0,
          "enablevscroll": 0,
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "offset": [
            0.0,
            0.0
          ],
          "lockeddragscroll": 0,
          "lockedsize": 0
        }
      },
      {
        "box": {
          "id": "f_hit_ui",
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
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
            948.0,
            66.0,
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
          "enablehscroll": 0,
          "enablevscroll": 0,
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "offset": [
            0.0,
            0.0
          ],
          "lockeddragscroll": 0,
          "lockedsize": 0
        }
      },
      {
        "box": {
          "id": "f_env_ui",
          "maxclass": "bpatcher",
          "name": "Abl.MapUi.maxpat",
          "numinlets": 3,
          "numoutlets": 7,
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
            948.0,
            88.0,
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
          "enablehscroll": 0,
          "enablevscroll": 0,
          "bgmode": 0,
          "border": 0,
          "clickthrough": 0,
          "offset": [
            0.0,
            0.0
          ],
          "lockeddragscroll": 0,
          "lockedsize": 0
        }
      },
      {
        "box": {
          "id": "f_edge_lane",
          "maxclass": "newobj",
          "text": "p f_edge_lane_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            460.0,
            118.0,
            22.0
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
          }
        }
      },
      {
        "box": {
          "id": "f_edge_lane_clear_id0",
          "maxclass": "message",
          "text": "0",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1142.0,
            484.0,
            29.5,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_lane",
          "maxclass": "newobj",
          "text": "p f_hit_lane_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            560.0,
            118.0,
            22.0
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
          }
        }
      },
      {
        "box": {
          "id": "f_hit_lane_clear_id0",
          "maxclass": "message",
          "text": "0",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1142.0,
            584.0,
            29.5,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "f_env_lane",
          "maxclass": "newobj",
          "text": "p f_env_lane_core",
          "numinlets": 8,
          "numoutlets": 3,
          "outlettype": [
            "",
            "",
            ""
          ],
          "patching_rect": [
            1008.0,
            660.0,
            118.0,
            22.0
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
          }
        }
      },
      {
        "box": {
          "id": "f_env_lane_clear_id0",
          "maxclass": "message",
          "text": "0",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            1142.0,
            684.0,
            29.5,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_norm",
          "maxclass": "newobj",
          "text": "* 0.01",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            600.0,
            268.0,
            48.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "f_env_norm",
          "maxclass": "newobj",
          "text": "* 0.01",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            790.0,
            298.0,
            48.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "obj-90",
          "maxclass": "newobj",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ],
          "patching_rect": [
            420.0,
            298.0,
            74.0,
            22.0
          ],
          "text": "speedlim 20"
        }
      },
      {
        "box": {
          "id": "blob_sel_lab",
          "maxclass": "comment",
          "text": "Blob",
          "patching_rect": [
            652.0,
            18.0,
            38.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            246.0,
            12.0,
            38.0,
            20.0
          ],
          "numinlets": 1,
          "numoutlets": 0,
          "textcolor": [
            1.0,
            1.0,
            1.0,
            0.6
          ],
          "fontsize": 10.0,
          "fontname": "Arial Bold"
        }
      },
      {
        "box": {
          "id": "blob_sel_num",
          "maxclass": "number",
          "patching_rect": [
            692.0,
            18.0,
            40.0,
            20.0
          ],
          "presentation": 1,
          "presentation_rect": [
            292.0,
            12.0,
            52.0,
            20.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "int",
            "bang"
          ],
          "parameter_enable": 0,
          "triangle": 0,
          "minimum": 1,
          "maximum": 8
        }
      },
      {
        "box": {
          "id": "blob_sel_load",
          "maxclass": "newobj",
          "text": "loadmess 1",
          "patching_rect": [
            644.0,
            44.0,
            72.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            ""
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_clip",
          "maxclass": "newobj",
          "text": "clip 1 8",
          "patching_rect": [
            692.0,
            44.0,
            64.0,
            22.0
          ],
          "numinlets": 3,
          "numoutlets": 1,
          "outlettype": [
            "int"
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_t",
          "maxclass": "newobj",
          "text": "t i i",
          "patching_rect": [
            692.0,
            72.0,
            36.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 2,
          "outlettype": [
            "int",
            "int"
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_set",
          "maxclass": "message",
          "text": "set $1",
          "patching_rect": [
            734.0,
            72.0,
            44.0,
            22.0
          ],
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ]
        }
      },
      {
        "box": {
          "id": "blob_sel_mux",
          "maxclass": "newobj",
          "text": "switch 8 1",
          "patching_rect": [
            20.0,
            112.0,
            76.0,
            22.0
          ],
          "numinlets": 9,
          "numoutlets": 1,
          "outlettype": [
            ""
          ]
        }
      },
      {
        "box": {
          "id": "f_blob_unpack",
          "maxclass": "newobj",
          "text": "unpack i f f f f i f f f f",
          "patching_rect": [
            110.0,
            112.0,
            178.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 10,
          "outlettype": [
            "int",
            "float",
            "float",
            "float",
            "float",
            "int",
            "float",
            "float",
            "float",
            "float"
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_pct",
          "maxclass": "newobj",
          "text": "* 100.",
          "patching_rect": [
            420.0,
            268.0,
            48.0,
            22.0
          ],
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ]
        }
      },
      {
        "box": {
          "id": "f_edge_curve",
          "maxclass": "newobj",
          "text": "expr pow($f1, 1.8)",
          "patching_rect": [
            420.0,
            236.0,
            110.0,
            22.0
          ],
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "float"
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_pulse_msg",
          "maxclass": "message",
          "text": "100, 0 160",
          "patching_rect": [
            536.0,
            330.0,
            84.0,
            22.0
          ],
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            ""
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_pulse_line",
          "maxclass": "newobj",
          "text": "line 0.",
          "patching_rect": [
            630.0,
            330.0,
            50.0,
            22.0
          ],
          "numinlets": 2,
          "numoutlets": 2,
          "outlettype": [
            "float",
            "bang"
          ]
        }
      },
      {
        "box": {
          "id": "f_hit_pulse_norm",
          "maxclass": "newobj",
          "text": "* 0.01",
          "patching_rect": [
            690.0,
            330.0,
            48.0,
            22.0
          ],
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "float"
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
            "obj-18",
            0
          ],
          "destination": [
            "obj-19",
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
            "obj-25",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-25",
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
            "obj-26",
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
            "obj-28",
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
            "f_env_norm",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_norm",
            0
          ],
          "destination": [
            "f_env_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_lane",
            0
          ],
          "destination": [
            "f_edge_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_lane",
            1
          ],
          "destination": [
            "f_edge_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_lane",
            2
          ],
          "destination": [
            "f_edge_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            0
          ],
          "destination": [
            "f_edge_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            1
          ],
          "destination": [
            "f_edge_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            2
          ],
          "destination": [
            "f_edge_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            3
          ],
          "destination": [
            "f_edge_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            4
          ],
          "destination": [
            "f_edge_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            5
          ],
          "destination": [
            "f_edge_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_ui",
            6
          ],
          "destination": [
            "f_edge_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_lane",
            0
          ],
          "destination": [
            "f_hit_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_lane",
            1
          ],
          "destination": [
            "f_hit_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_lane",
            2
          ],
          "destination": [
            "f_hit_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            0
          ],
          "destination": [
            "f_hit_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            1
          ],
          "destination": [
            "f_hit_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            2
          ],
          "destination": [
            "f_hit_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            3
          ],
          "destination": [
            "f_hit_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            4
          ],
          "destination": [
            "f_hit_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            5
          ],
          "destination": [
            "f_hit_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_ui",
            6
          ],
          "destination": [
            "f_hit_lane",
            7
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_lane",
            0
          ],
          "destination": [
            "f_env_ui",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_lane",
            1
          ],
          "destination": [
            "f_env_ui",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_lane",
            2
          ],
          "destination": [
            "f_env_ui",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            0
          ],
          "destination": [
            "f_env_lane",
            1
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            1
          ],
          "destination": [
            "f_env_lane",
            2
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            2
          ],
          "destination": [
            "f_env_lane",
            3
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            3
          ],
          "destination": [
            "f_env_lane",
            4
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            4
          ],
          "destination": [
            "f_env_lane",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            5
          ],
          "destination": [
            "f_env_lane",
            6
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_env_ui",
            6
          ],
          "destination": [
            "f_env_lane",
            7
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
            "blob_sel_mux",
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
            "obj-3",
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
            "obj-3",
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
            "obj-3",
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
            "obj-3",
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
            "obj-3",
            4
          ],
          "destination": [
            "blob_sel_mux",
            5
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-3",
            5
          ],
          "destination": [
            "blob_sel_mux",
            6
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
            "blob_sel_mux",
            7
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
            "blob_sel_mux",
            8
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
            "f_blob_unpack",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_blob_unpack",
            8
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
            "f_blob_unpack",
            9
          ],
          "destination": [
            "f_hit_pct",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_pct",
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
            "obj-17",
            0
          ],
          "destination": [
            "f_edge_curve",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_edge_curve",
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
            "f_edge_curve",
            0
          ],
          "destination": [
            "f_edge_lane",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "obj-25",
            0
          ],
          "destination": [
            "f_hit_pulse_msg",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_pulse_msg",
            0
          ],
          "destination": [
            "f_hit_pulse_line",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_pulse_line",
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
            "f_hit_pulse_line",
            0
          ],
          "destination": [
            "f_hit_pulse_norm",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "f_hit_pulse_norm",
            0
          ],
          "destination": [
            "f_hit_lane",
            0
          ]
        }
      }
    ],
    "name": "ndi_flood_controller",
    "bglocked": 1,
    "devicewidth": 354.0,
    "openrect": [
      0.0,
      0.0,
      354.0,
      116.0
    ],
    "digest": "Selectable per-blob flood edge/hit controller",
    "description": "Flood controller for blobs 1-8 driven by app-side edge and hit values",
    "tags": "NDI flood edge hit"
  }
}
