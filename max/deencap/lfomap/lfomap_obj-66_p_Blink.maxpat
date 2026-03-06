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
            209.0,
            112.0,
            449.0,
            601.0
        ],
        "boxes": [
            {
                "box": {
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        188.0,
                        474.0,
                        140.0,
                        22.0
                    ],
                    "text": "prepend activebgoncolor"
                }
            },
            {
                "box": {
                    "id": "obj-99",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [
                        "bang",
                        "int",
                        "int"
                    ],
                    "patching_rect": [
                        57.0,
                        28.0,
                        83.0,
                        22.0
                    ],
                    "text": "live.thisdevice"
                }
            },
            {
                "box": {
                    "id": "obj-98",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        188.0,
                        313.0,
                        55.0,
                        22.0
                    ],
                    "text": "zl slice 3"
                }
            },
            {
                "box": {
                    "id": "obj-97",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        289.0,
                        313.0,
                        32.0,
                        22.0
                    ],
                    "text": "t 0.5"
                }
            },
            {
                "box": {
                    "id": "obj-96",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "float"
                    ],
                    "patching_rect": [
                        259.0,
                        313.0,
                        25.0,
                        22.0
                    ],
                    "text": "t 1."
                }
            },
            {
                "box": {
                    "id": "obj-95",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        259.0,
                        353.0,
                        72.0,
                        22.0
                    ],
                    "text": "prepend set"
                }
            },
            {
                "box": {
                    "id": "obj-94",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        188.0,
                        274.0,
                        38.0,
                        22.0
                    ],
                    "text": "zl reg"
                }
            },
            {
                "box": {
                    "id": "obj-81",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "bang",
                        "int"
                    ],
                    "patching_rect": [
                        188.0,
                        210.0,
                        90.0,
                        22.0
                    ],
                    "text": "t b i"
                }
            },
            {
                "box": {
                    "id": "obj-83",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        57.0,
                        205.0,
                        114.0,
                        22.0
                    ],
                    "text": "route lcd_control_fg"
                }
            },
            {
                "box": {
                    "id": "obj-84",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        57.0,
                        97.0,
                        83.0,
                        22.0
                    ],
                    "text": "lcd_control_fg"
                }
            },
            {
                "box": {
                    "id": "obj-85",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        "bang"
                    ],
                    "patching_rect": [
                        57.0,
                        136.0,
                        62.0,
                        22.0
                    ],
                    "text": "live.colors"
                }
            },
            {
                "box": {
                    "id": "obj-87",
                    "maxclass": "newobj",
                    "numinlets": 3,
                    "numoutlets": 3,
                    "outlettype": [
                        "bang",
                        "bang",
                        ""
                    ],
                    "patching_rect": [
                        259.0,
                        274.0,
                        79.0,
                        22.0
                    ],
                    "text": "sel 1 0"
                }
            },
            {
                "box": {
                    "id": "obj-88",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        188.0,
                        434.0,
                        62.0,
                        22.0
                    ],
                    "text": "append 1."
                }
            },
            {
                "box": {
                    "id": "obj-6",
                    "maxclass": "toggle",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "parameter_enable": 0,
                    "patching_rect": [
                        188.0,
                        152.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-16",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "bang"
                    ],
                    "patching_rect": [
                        209.0,
                        108.0,
                        69.0,
                        22.0
                    ],
                    "text": "qmetro 200"
                }
            },
            {
                "box": {
                    "comment": "(bool) blink",
                    "id": "obj-60",
                    "index": 1,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        188.0,
                        58.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "comment": "to button",
                    "id": "obj-61",
                    "index": 1,
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        188.0,
                        517.0,
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
                        "obj-6",
                        0
                    ],
                    "source": [
                        "obj-16",
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
                    "source": [
                        "obj-2",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-81",
                        0
                    ],
                    "source": [
                        "obj-6",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-16",
                        0
                    ],
                    "order": 0,
                    "source": [
                        "obj-60",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-6",
                        0
                    ],
                    "order": 1,
                    "source": [
                        "obj-60",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-87",
                        0
                    ],
                    "source": [
                        "obj-81",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-94",
                        0
                    ],
                    "source": [
                        "obj-81",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-94",
                        1
                    ],
                    "source": [
                        "obj-83",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-85",
                        0
                    ],
                    "source": [
                        "obj-84",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-83",
                        0
                    ],
                    "source": [
                        "obj-85",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-84",
                        0
                    ],
                    "midpoints": [
                        109.5,
                        181.0,
                        149.0,
                        181.0,
                        149.0,
                        69.0,
                        66.5,
                        69.0
                    ],
                    "source": [
                        "obj-85",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-96",
                        0
                    ],
                    "source": [
                        "obj-87",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-97",
                        0
                    ],
                    "source": [
                        "obj-87",
                        1
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
                        "obj-88",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-98",
                        0
                    ],
                    "source": [
                        "obj-94",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-88",
                        0
                    ],
                    "source": [
                        "obj-95",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-95",
                        0
                    ],
                    "source": [
                        "obj-96",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-95",
                        0
                    ],
                    "source": [
                        "obj-97",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-88",
                        0
                    ],
                    "source": [
                        "obj-98",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-84",
                        0
                    ],
                    "source": [
                        "obj-99",
                        0
                    ]
                }
            }
        ]
    }
}