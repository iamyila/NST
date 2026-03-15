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
      960.0,
      540.0
    ],
    "bglocked": 0,
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
          "text": "3-Channel Crossfade (one knob / one Y input)",
          "patching_rect": [
            30.0,
            15.0,
            320.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "c1",
          "maxclass": "comment",
          "text": "Y in (0..1)",
          "patching_rect": [
            30.0,
            52.0,
            80.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "in1",
          "maxclass": "inlet",
          "patching_rect": [
            30.0,
            76.0,
            25.0,
            25.0
          ],
          "numinlets": 0,
          "numoutlets": 1,
          "outlettype": [
            ""
          ]
        }
      },
      {
        "box": {
          "id": "dial1",
          "maxclass": "live.dial",
          "patching_rect": [
            120.0,
            62.0,
            58.0,
            58.0
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "XFade",
              "parameter_shortname": "XFade",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_unitstyle": 1,
              "parameter_type": 0
            }
          }
        }
      },
      {
        "box": {
          "id": "load",
          "maxclass": "newobj",
          "text": "loadmess 0.5",
          "patching_rect": [
            190.0,
            80.0,
            80.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "clip",
          "maxclass": "newobj",
          "text": "clip 0. 1.",
          "patching_rect": [
            300.0,
            80.0,
            70.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "t1",
          "maxclass": "newobj",
          "text": "t f f f",
          "patching_rect": [
            390.0,
            80.0,
            52.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "e1",
          "maxclass": "newobj",
          "text": "expr clip(1. - (2.*$f1), 0., 1.)",
          "patching_rect": [
            470.0,
            48.0,
            245.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "e2",
          "maxclass": "newobj",
          "text": "expr 1. - abs((2.*$f1) - 1.)",
          "patching_rect": [
            470.0,
            80.0,
            190.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "e3",
          "maxclass": "newobj",
          "text": "expr clip((2.*$f1) - 1., 0., 1.)",
          "patching_rect": [
            470.0,
            112.0,
            232.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "n1",
          "maxclass": "live.numbox",
          "patching_rect": [
            740.0,
            48.0,
            66.0,
            20.0
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "CH1_Level",
              "parameter_shortname": "CH1",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_unitstyle": 1,
              "parameter_type": 0
            }
          }
        }
      },
      {
        "box": {
          "id": "n2",
          "maxclass": "live.numbox",
          "patching_rect": [
            740.0,
            80.0,
            66.0,
            20.0
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "CH2_Level",
              "parameter_shortname": "CH2",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_unitstyle": 1,
              "parameter_type": 0
            }
          }
        }
      },
      {
        "box": {
          "id": "n3",
          "maxclass": "live.numbox",
          "patching_rect": [
            740.0,
            112.0,
            66.0,
            20.0
          ],
          "parameter_enable": 1,
          "saved_attribute_attributes": {
            "valueof": {
              "parameter_longname": "CH3_Level",
              "parameter_shortname": "CH3",
              "parameter_mmin": 0.0,
              "parameter_mmax": 1.0,
              "parameter_unitstyle": 1,
              "parameter_type": 0
            }
          }
        }
      },
      {
        "box": {
          "id": "cch1",
          "maxclass": "comment",
          "text": "CH1",
          "patching_rect": [
            814.0,
            48.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "cch2",
          "maxclass": "comment",
          "text": "CH2",
          "patching_rect": [
            814.0,
            80.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "cch3",
          "maxclass": "comment",
          "text": "CH3",
          "patching_rect": [
            814.0,
            112.0,
            40.0,
            20.0
          ]
        }
      },
      {
        "box": {
          "id": "out1",
          "maxclass": "outlet",
          "patching_rect": [
            890.0,
            48.0,
            25.0,
            25.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "out2",
          "maxclass": "outlet",
          "patching_rect": [
            890.0,
            80.0,
            25.0,
            25.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "out3",
          "maxclass": "outlet",
          "patching_rect": [
            890.0,
            112.0,
            25.0,
            25.0
          ],
          "numinlets": 1,
          "numoutlets": 0
        }
      },
      {
        "box": {
          "id": "c2",
          "maxclass": "comment",
          "linecount": 3,
          "text": "Curve: CH1<->CH2<->CH3 linear overlap.\n0.0 = CH1, 0.5 = CH2, 1.0 = CH3.\nMap CH1/CH2/CH3 to your 3 track volumes.",
          "patching_rect": [
            30.0,
            150.0,
            390.0,
            52.0
          ]
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "source": [
            "in1",
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
            "dial1",
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
            "load",
            0
          ],
          "destination": [
            "dial1",
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
            "t1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "t1",
            0
          ],
          "destination": [
            "e1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "t1",
            1
          ],
          "destination": [
            "e2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "t1",
            2
          ],
          "destination": [
            "e3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "e1",
            0
          ],
          "destination": [
            "n1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "e2",
            0
          ],
          "destination": [
            "n2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "e3",
            0
          ],
          "destination": [
            "n3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "n1",
            0
          ],
          "destination": [
            "out1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "n2",
            0
          ],
          "destination": [
            "out2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "n3",
            0
          ],
          "destination": [
            "out3",
            0
          ]
        }
      }
    ]
  }
}