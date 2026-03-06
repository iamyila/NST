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
            1210.0,
            253.0,
            821.0,
            814.0
        ],
        "boxes": [
            {
                "box": {
                    "id": "obj-3",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        364.0,
                        216.0,
                        33.0,
                        22.0
                    ],
                    "text": "* 0.5"
                }
            },
            {
                "box": {
                    "id": "obj-69",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "float"
                    ],
                    "patching_rect": [
                        439.0,
                        298.0,
                        29.5,
                        22.0
                    ],
                    "text": "t b f"
                }
            },
            {
                "box": {
                    "id": "obj-64",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "float"
                    ],
                    "patching_rect": [
                        153.0,
                        595.0,
                        29.5,
                        22.0
                    ],
                    "text": "t b f"
                }
            },
            {
                "box": {
                    "id": "obj-63",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "float"
                    ],
                    "patching_rect": [
                        439.0,
                        384.0,
                        29.5,
                        22.0
                    ],
                    "text": "t b f"
                }
            },
            {
                "box": {
                    "id": "obj-62",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "float"
                    ],
                    "patching_rect": [
                        364.0,
                        253.0,
                        33.0,
                        22.0
                    ],
                    "text": "t b f"
                }
            },
            {
                "box": {
                    "id": "obj-61",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "int"
                    ],
                    "patching_rect": [
                        306.0,
                        216.0,
                        33.0,
                        22.0
                    ],
                    "text": "t b i"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleusescolors": 1,
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-60",
                    "linecount": 2,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        484.0,
                        249.0,
                        158.0,
                        37.0
                    ],
                    "text": "Make depth offset negative for unipolar input."
                }
            },
            {
                "box": {
                    "id": "obj-59",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        439.0,
                        256.0,
                        29.5,
                        22.0
                    ],
                    "text": "- 1."
                }
            },
            {
                "box": {
                    "id": "obj-58",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        439.0,
                        216.0,
                        29.5,
                        22.0
                    ],
                    "text": "* 2."
                }
            },
            {
                "box": {
                    "id": "obj-56",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        439.0,
                        345.0,
                        31.0,
                        22.0
                    ],
                    "text": "* -1."
                }
            },
            {
                "box": {
                    "id": "obj-55",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        364.0,
                        298.0,
                        33.0,
                        22.0
                    ],
                    "text": "* 0."
                }
            },
            {
                "box": {
                    "id": "obj-53",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        306.0,
                        253.0,
                        33.0,
                        22.0
                    ],
                    "text": "== 0"
                }
            },
            {
                "box": {
                    "id": "obj-50",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        484.0,
                        217.0,
                        190.0,
                        20.0
                    ],
                    "text": "CALCULATE INPUT OFFSET"
                }
            },
            {
                "box": {
                    "id": "obj-49",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        171.0,
                        519.0,
                        201.0,
                        20.0
                    ],
                    "text": "CALCULATE OUTPUT SCALING"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleside": 3,
                    "bubbleusescolors": 1,
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-48",
                    "linecount": 3,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        212.0,
                        284.0,
                        138.0,
                        50.0
                    ],
                    "text": "If input and output polarities don't match, offset by 0.5 * depth. "
                }
            },
            {
                "box": {
                    "id": "obj-47",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        439.0,
                        423.0,
                        29.5,
                        22.0
                    ],
                    "text": "+ 0."
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleusescolors": 1,
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-46",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        175.0,
                        632.0,
                        160.0,
                        24.0
                    ],
                    "text": "Scale again by target depth"
                }
            },
            {
                "box": {
                    "id": "obj-45",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        135.0,
                        633.0,
                        29.5,
                        22.0
                    ],
                    "text": "* 1."
                }
            },
            {
                "box": {
                    "id": "obj-43",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        135.0,
                        518.0,
                        33.0,
                        22.0
                    ],
                    "text": "== 0"
                }
            },
            {
                "box": {
                    "id": "obj-42",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        135.0,
                        555.0,
                        29.5,
                        22.0
                    ],
                    "text": "+ 1."
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleusescolors": 1,
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-41",
                    "linecount": 2,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        171.0,
                        548.0,
                        168.0,
                        37.0
                    ],
                    "text": "If output is bipolar, multiply output by 2, otherwise by 1"
                }
            },
            {
                "box": {
                    "id": "obj-40",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        56.0,
                        517.0,
                        29.5,
                        22.0
                    ],
                    "text": "+~"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleusescolors": 1,
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-39",
                    "linecount": 2,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        538.0,
                        385.0,
                        148.0,
                        37.0
                    ],
                    "text": "If input is bipolar, subtract 0.5 from input."
                }
            },
            {
                "box": {
                    "id": "obj-26",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        56.0,
                        681.0,
                        34.0,
                        22.0
                    ],
                    "text": "*~ 1."
                }
            },
            {
                "box": {
                    "id": "obj-20",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        492.0,
                        392.0,
                        37.0,
                        22.0
                    ],
                    "text": "* -0.5"
                }
            },
            {
                "box": {
                    "fontname": "Courier New",
                    "id": "obj-17",
                    "linecount": 6,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        135.0,
                        23.0,
                        488.0,
                        88.0
                    ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "Input    | Output\n         |\n         | Unipolar                         Bipolar\n         |--------------------------------------------------------\nUnipolar | out = in                         out = in - 0.5 * depth\nBipolar  | out = in - 0.5 + 0.5 * depth     out = in - 0.5"
                }
            },
            {
                "box": {
                    "comment": "(bool) modulation output polarity: 0 = bipolar, 1 = unipolar",
                    "id": "obj-30",
                    "index": 2,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        135.0,
                        145.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(float) depth",
                    "id": "obj-37",
                    "index": 3,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        364.0,
                        145.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(float, 0 - 1) target depth",
                    "id": "obj-38",
                    "index": 5,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        694.0,
                        149.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(signal) in",
                    "id": "obj-51",
                    "index": 1,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        56.0,
                        145.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(bool) is input bipolar?",
                    "id": "obj-52",
                    "index": 4,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        439.0,
                        145.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(signal, -1 - 1) modulation out",
                    "id": "obj-54",
                    "index": 1,
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        56.0,
                        718.0,
                        30.0,
                        30.0
                    ]
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [
                        "obj-47",
                        0
                    ],
                    "source": [
                        "obj-20",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-54",
                        0
                    ],
                    "source": [
                        "obj-26",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-62",
                        0
                    ],
                    "source": [
                        "obj-3",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-43",
                        0
                    ],
                    "order": 1,
                    "source": [
                        "obj-30",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-53",
                        0
                    ],
                    "order": 0,
                    "source": [
                        "obj-30",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-3",
                        0
                    ],
                    "source": [
                        "obj-37",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-64",
                        0
                    ],
                    "midpoints": [
                        703.5,
                        590.0,
                        162.5,
                        590.0
                    ],
                    "source": [
                        "obj-38",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-26",
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
                    "destination": [
                        "obj-45",
                        0
                    ],
                    "source": [
                        "obj-42",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-42",
                        0
                    ],
                    "source": [
                        "obj-43",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-26",
                        1
                    ],
                    "source": [
                        "obj-45",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-40",
                        1
                    ],
                    "source": [
                        "obj-47",
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
                        "obj-51",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-20",
                        0
                    ],
                    "order": 0,
                    "source": [
                        "obj-52",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-58",
                        0
                    ],
                    "order": 1,
                    "source": [
                        "obj-52",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-61",
                        0
                    ],
                    "order": 2,
                    "source": [
                        "obj-52",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-55",
                        0
                    ],
                    "source": [
                        "obj-53",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-56",
                        0
                    ],
                    "source": [
                        "obj-55",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-63",
                        0
                    ],
                    "source": [
                        "obj-56",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-59",
                        0
                    ],
                    "source": [
                        "obj-58",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-69",
                        0
                    ],
                    "source": [
                        "obj-59",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-53",
                        1
                    ],
                    "source": [
                        "obj-61",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-53",
                        0
                    ],
                    "source": [
                        "obj-61",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-55",
                        1
                    ],
                    "source": [
                        "obj-62",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-55",
                        0
                    ],
                    "source": [
                        "obj-62",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-47",
                        1
                    ],
                    "source": [
                        "obj-63",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-47",
                        0
                    ],
                    "source": [
                        "obj-63",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-45",
                        1
                    ],
                    "source": [
                        "obj-64",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-45",
                        0
                    ],
                    "source": [
                        "obj-64",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-56",
                        1
                    ],
                    "source": [
                        "obj-69",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-56",
                        0
                    ],
                    "source": [
                        "obj-69",
                        0
                    ]
                }
            }
        ]
    }
}