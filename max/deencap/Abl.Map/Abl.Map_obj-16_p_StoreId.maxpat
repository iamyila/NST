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
            778.0,
            589.0,
            944.0,
            485.0
        ],
        "boxes": [
            {
                "box": {
                    "bubble": 1,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-41",
                    "linecount": 3,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        576.0,
                        100.0,
                        195.0,
                        52.0
                    ],
                    "suppressinlet": 1,
                    "text": "Note: we can't set the 'id' property as an argument because that creates an undo on load.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "id": "obj-25",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        478.0,
                        154.0,
                        65.0,
                        22.0
                    ],
                    "text": "property id"
                }
            },
            {
                "box": {
                    "id": "obj-18",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        "bang"
                    ],
                    "patching_rect": [
                        478.0,
                        115.0,
                        29.5,
                        22.0
                    ],
                    "text": "t l b"
                }
            },
            {
                "box": {
                    "id": "obj-8",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        478.0,
                        269.0,
                        29.5,
                        22.0
                    ],
                    "text": "t l l"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-16",
                    "linecount": 3,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        529.0,
                        349.0,
                        353.0,
                        52.0
                    ],
                    "suppressinlet": 1,
                    "text": "No need to send out id 0 when the parameter was removed; the mapping will not have effect anyway and we would create an undo. Do make sure to notify the UI of the mapping being gone though.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "id": "obj-11",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        356.0,
                        115.0,
                        19.0,
                        22.0
                    ],
                    "text": "t l"
                }
            },
            {
                "box": {
                    "id": "obj-9",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        467.0,
                        70.0,
                        29.5,
                        22.0
                    ],
                    "text": "id 0"
                }
            },
            {
                "box": {
                    "comment": "(bang) mapping failed",
                    "id": "obj-3",
                    "index": 2,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        "bang"
                    ],
                    "patching_rect": [
                        467.0,
                        23.0,
                        30.0,
                        30.0
                    ],
                    "prototypename": "M4L.Arial10"
                }
            },
            {
                "box": {
                    "id": "obj-10",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        356.0,
                        364.0,
                        29.5,
                        22.0
                    ],
                    "text": "id 0"
                }
            },
            {
                "box": {
                    "id": "obj-4",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        356.0,
                        325.0,
                        70.0,
                        22.0
                    ],
                    "text": "substitute 0"
                }
            },
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
                        478.0,
                        230.0,
                        54.0,
                        22.0
                    ],
                    "text": "deferlow"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleside": 3,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-7",
                    "linecount": 11,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        32.0,
                        257.0,
                        203.0,
                        158.0
                    ],
                    "suppressinlet": 1,
                    "text": "To prevent unwanted undos: no need to send out id 0 on init, when mapping disappears through undo or when param disappears. In all these cases, live.remote and live.modulate will be changed directly. UI updates will be done through the mapped bool.\n\nOnly send id 0 when the mapping is reset by the user.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "id": "obj-6",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        251.0,
                        325.0,
                        70.0,
                        22.0
                    ],
                    "text": "substitute 0"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleside": 3,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-1",
                    "linecount": 2,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        111.0,
                        185.0,
                        130.0,
                        39.0
                    ],
                    "suppressinlet": 1,
                    "text": "Parameter stored by persistent mapping.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-20",
                    "linecount": 4,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [
                        576.0,
                        172.0,
                        195.0,
                        65.0
                    ],
                    "suppressinlet": 1,
                    "text": "Keeps track of id changes of the parameter. Outputs id 0 when param disappears and old id when it re-appears, i.e after undo.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "comment": "(id) parameter id",
                    "id": "obj-78",
                    "index": 1,
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        302.0,
                        422.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-34",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        478.0,
                        325.0,
                        49.0,
                        22.0
                    ],
                    "text": "route id"
                }
            },
            {
                "box": {
                    "comment": "(bool) mapped",
                    "id": "obj-27",
                    "index": 2,
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        478.0,
                        422.0,
                        30.0,
                        30.0
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-31",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        "int"
                    ],
                    "patching_rect": [
                        478.0,
                        364.0,
                        30.0,
                        22.0
                    ],
                    "text": "!= 0"
                }
            },
            {
                "box": {
                    "id": "obj-5",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "patching_rect": [
                        478.0,
                        193.0,
                        77.0,
                        22.0
                    ],
                    "saved_object_attributes": {
                        "_persistence": 1
                    },
                    "text": "live.observer"
                }
            },
            {
                "box": {
                    "id": "obj-37",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        251.0,
                        154.0,
                        35.0,
                        22.0
                    ],
                    "text": "getid"
                }
            },
            {
                "box": {
                    "id": "obj-40",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [
                        "bang",
                        "int",
                        "int"
                    ],
                    "patching_rect": [
                        251.0,
                        115.0,
                        83.0,
                        22.0
                    ],
                    "text": "live.thisdevice"
                }
            },
            {
                "box": {
                    "comment": "(id) object id to store",
                    "id": "obj-51",
                    "index": 1,
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        356.0,
                        23.0,
                        30.0,
                        30.0
                    ],
                    "prototypename": "M4L.Arial10"
                }
            },
            {
                "box": {
                    "id": "obj-130",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        251.0,
                        193.0,
                        62.0,
                        22.0
                    ],
                    "saved_object_attributes": {
                        "_persistence": 1
                    },
                    "text": "live.object"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [
                        "obj-78",
                        0
                    ],
                    "source": [
                        "obj-10",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-130",
                        1
                    ],
                    "order": 2,
                    "source": [
                        "obj-11",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-18",
                        0
                    ],
                    "order": 0,
                    "source": [
                        "obj-11",
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
                    "order": 1,
                    "source": [
                        "obj-11",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-34",
                        0
                    ],
                    "order": 0,
                    "source": [
                        "obj-130",
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
                        "obj-130",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-25",
                        0
                    ],
                    "source": [
                        "obj-18",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-5",
                        1
                    ],
                    "source": [
                        "obj-18",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-8",
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
                        "obj-5",
                        0
                    ],
                    "source": [
                        "obj-25",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-9",
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
                        "obj-27",
                        0
                    ],
                    "source": [
                        "obj-31",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-31",
                        0
                    ],
                    "source": [
                        "obj-34",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-130",
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
                        "obj-10",
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
                        "obj-37",
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
                        "obj-2",
                        0
                    ],
                    "source": [
                        "obj-5",
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
                    "source": [
                        "obj-51",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-78",
                        0
                    ],
                    "source": [
                        "obj-6",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-34",
                        0
                    ],
                    "source": [
                        "obj-8",
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
                    "source": [
                        "obj-8",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-11",
                        0
                    ],
                    "source": [
                        "obj-9",
                        0
                    ]
                }
            }
        ]
    }
}