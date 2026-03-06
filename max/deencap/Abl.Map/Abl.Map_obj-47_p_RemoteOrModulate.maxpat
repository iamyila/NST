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
            279.0,
            235.0,
            708.0,
            540.0
        ],
        "boxes": [
            {
                "box": {
                    "bubble": 1,
                    "bubbleside": 2,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-5",
                    "linecount": 2,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        17.5,
                        11.0,
                        143.0,
                        54.0
                    ],
                    "suppressinlet": 1,
                    "text": "Unmapping only results in a 0 here (not an id 0).",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "id": "obj-4",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        74.0,
                        199.0,
                        63.0,
                        22.0
                    ],
                    "text": "gate"
                }
            },
            {
                "box": {
                    "comment": "(bool) mapped",
                    "id": "obj-3",
                    "index": 2,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        74.0,
                        74.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-1",
                    "linecount": 4,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        311.0,
                        170.0,
                        274.0,
                        65.0
                    ],
                    "suppressinlet": 1,
                    "text": "Disabled stopping modulation when device is disabled for now because disablingthe DSP engine is not in sync with releasing modulation control: sometimes it works, sometimes it doesn't.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubblepoint": 0.0,
                    "bubbleside": 2,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-2",
                    "linecount": 2,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        401.0,
                        62.0,
                        268.0,
                        54.0
                    ],
                    "suppressinlet": 1,
                    "text": "Assumes modulation is active by default, so no need to send out anything on init if use modulation is 1.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-21",
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        183.0,
                        119.0,
                        149.0,
                        26.0
                    ],
                    "suppressinlet": 1,
                    "text": "Prevent an undo on load.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "id": "obj-32",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [
                        "",
                        "int",
                        "int"
                    ],
                    "patching_rect": [
                        118.0,
                        121.0,
                        58.0,
                        22.0
                    ],
                    "text": "change 1"
                }
            },
            {
                "box": {
                    "id": "obj-36",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "int"
                    ],
                    "patching_rect": [
                        268.0,
                        160.0,
                        29.5,
                        22.0
                    ],
                    "text": "t b i"
                }
            },
            {
                "box": {
                    "id": "obj-14",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        250.0,
                        253.0,
                        29.5,
                        22.0
                    ],
                    "text": "&&"
                }
            },
            {
                "box": {
                    "id": "obj-11",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        250.0,
                        229.0,
                        48.0,
                        22.0
                    ],
                    "text": "pak 1 1"
                }
            },
            {
                "box": {
                    "id": "obj-54",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        177.0,
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
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        250.0,
                        287.0,
                        29.5,
                        22.0
                    ],
                    "text": "+ 1"
                }
            },
            {
                "box": {
                    "id": "obj-51",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        250.0,
                        397.0,
                        30.0,
                        22.0
                    ],
                    "text": "id 0"
                }
            },
            {
                "box": {
                    "id": "obj-52",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        250.0,
                        365.0,
                        52.0,
                        22.0
                    ],
                    "text": "gate 2 2"
                }
            },
            {
                "box": {
                    "id": "obj-47",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        177.0,
                        287.0,
                        29.5,
                        22.0
                    ],
                    "text": "+ 1"
                }
            },
            {
                "box": {
                    "id": "obj-45",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "int"
                    ],
                    "patching_rect": [
                        118.0,
                        160.0,
                        77.5,
                        22.0
                    ],
                    "text": "t b i"
                }
            },
            {
                "box": {
                    "id": "obj-44",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        177.0,
                        397.0,
                        30.0,
                        22.0
                    ],
                    "text": "id 0"
                }
            },
            {
                "box": {
                    "id": "obj-43",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        177.0,
                        365.0,
                        52.0,
                        22.0
                    ],
                    "text": "gate 2 1"
                }
            },
            {
                "box": {
                    "id": "obj-12",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        29.0,
                        287.0,
                        38.0,
                        22.0
                    ],
                    "text": "zl reg"
                }
            },
            {
                "box": {
                    "comment": "(bool) use modulation",
                    "id": "obj-38",
                    "index": 3,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        118.0,
                        74.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(lom id) parameter to map",
                    "id": "obj-39",
                    "index": 1,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        29.0,
                        74.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(bool) device is enabled",
                    "id": "obj-40",
                    "index": 4,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        268.0,
                        74.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(lom id) id to live.remote~",
                    "id": "obj-41",
                    "index": 1,
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        177.0,
                        439.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "(lom id) id to live.modulate~",
                    "id": "obj-46",
                    "index": 2,
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        250.0,
                        439.0,
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
                        "obj-14",
                        0
                    ],
                    "source": [
                        "obj-11",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-43",
                        1
                    ],
                    "order": 1,
                    "source": [
                        "obj-12",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-52",
                        1
                    ],
                    "order": 0,
                    "source": [
                        "obj-12",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-50",
                        0
                    ],
                    "source": [
                        "obj-14",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-4",
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
                        "obj-45",
                        0
                    ],
                    "source": [
                        "obj-32",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-11",
                        1
                    ],
                    "disabled": 1,
                    "source": [
                        "obj-36",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-12",
                        0
                    ],
                    "source": [
                        "obj-36",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-32",
                        0
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
                        "obj-12",
                        0
                    ],
                    "source": [
                        "obj-39",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-12",
                        0
                    ],
                    "source": [
                        "obj-4",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-36",
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
                        "obj-41",
                        0
                    ],
                    "source": [
                        "obj-43",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-44",
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
                        "obj-41",
                        0
                    ],
                    "source": [
                        "obj-44",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-11",
                        0
                    ],
                    "order": 0,
                    "source": [
                        "obj-45",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-4",
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
                        "obj-54",
                        0
                    ],
                    "order": 1,
                    "source": [
                        "obj-45",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-43",
                        0
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
                        "obj-52",
                        0
                    ],
                    "source": [
                        "obj-50",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-46",
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
                        "obj-46",
                        0
                    ],
                    "source": [
                        "obj-52",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-51",
                        0
                    ],
                    "source": [
                        "obj-52",
                        0
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
                        "obj-54",
                        0
                    ]
                }
            }
        ]
    }
}