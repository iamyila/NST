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
        "classnamespace": "dsp.gen",
        "rect": [
            84.0,
            144.0,
            653.0,
            641.0
        ],
        "boxes": [
            {
                "box": {
                    "code": "//============================================================\n// Generate exponential curve.\n//============================================================\n\n\nexponent(x, amount)\n{\n    y = 0;\n    \n    if (amount != 0)\n    {\n        a = abs(amount);\n        \n        if (amount > 0)\n        {\n            y = exp(ln(x) * (1 / (1 - a)));\n        }\n        else\n        {\n            y = 1 - (exp(ln(1 - x) * (1 / (1 - a))));\n        }\n    \n        return y;\n    }\n    else {\n        return x;\n    }\n}\n\nout1 = exponent(in1, in2 * 0.0095);",
                    "fontface": 0,
                    "fontname": "<Monospaced>",
                    "fontsize": 12.0,
                    "id": "obj-5",
                    "maxclass": "codebox",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        40.0,
                        70.0,
                        524.0,
                        470.0
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-1",
                    "maxclass": "newobj",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        40.0,
                        31.0,
                        28.0,
                        22.0
                    ],
                    "text": "in 1"
                }
            },
            {
                "box": {
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        545.0,
                        31.0,
                        28.0,
                        22.0
                    ],
                    "text": "in 2"
                }
            },
            {
                "box": {
                    "id": "obj-4",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        40.0,
                        557.0,
                        35.0,
                        22.0
                    ],
                    "text": "out 1"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [
                        "obj-5",
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
                        "obj-5",
                        1
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
                        "obj-4",
                        0
                    ],
                    "source": [
                        "obj-5",
                        0
                    ]
                }
            }
        ]
    }
}