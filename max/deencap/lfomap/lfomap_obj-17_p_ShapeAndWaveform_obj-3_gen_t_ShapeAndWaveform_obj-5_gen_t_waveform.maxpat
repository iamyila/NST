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
            144.0,
            431.0,
            947.0,
            823.0
        ],
        "boxes": [
            {
                "box": {
                    "code": "\r\n\r\n//============================================================\n// FUNCTIONS\n\r\n//------------------------------------------------------------\n// 1 dimensional stray noise functions\n\nclock(p)\n{\n    History x1(0);\n\n    x  = p <= 0.5;\n    y  = x-x1 == 1;\n    x1 = x;\n\n    return y;\n}\n\nstray(buf_wavelet, phase, gain)\n{\n    History aNext(0);\n    History aCurr(0);\n\n    phaseNext  = phase;\n    phaseCurr  = wrap(phaseNext+0.5, 0, 1);\n    \n    trigNext   = clock(phaseNext);\r\n    trigCurr   = clock(phaseCurr);\n\n    if(trigNext==1)\n    {\n        aNext = noise()*gain;\n    }\r\n    if(trigCurr==1)\n    {\n        aCurr = noise()*gain;\n    }\n\n    yNext = nearest(buf_wavelet, phaseNext) * aNext * (phaseNext*2-1);\n    yCurr = nearest(buf_wavelet, phaseCurr) * aCurr * (phaseCurr*2-1);\n\n    return mix(yCurr, yNext, 0.5);\n}\n\n//============================================================\n// BUFFERS\n\r\n//------------------------------------------------------------\n// 1 dimensional stray noise buffers\n\nBuffer buf_wavelet(\"\");\n\r\n\r\n//============================================================\n// STATE\r\n\r\n//------------------------------------------------------------\n// Type 6 + 7 SAH Noise\n\r\nHistory sah_noise(0);\r\n\r\n\r\n//------------------------------------------------------------\n// Type 9 Glider\n\r\nHistory g_oldDrive();\r\nHistory g_b();\r\nHistory g_a();\r\n\r\n\r\n//============================================================\n// MAIN LOOP\r\n\r\nphase = in1;\r\ntype = in2 + 1;\r\nrate = in3;\r\nval = 0;\r\n\r\n\r\nif (type == 1) { \r\n//------------------------------------------------------------\n// Type 1: Cosine\r\n\r\n\tval = (cos(phase * TWOPI) + 1.) * 0.5;\t\r\n\r\n} else if (type == 2) { \r\n//------------------------------------------------------------\n// Type 2: Phasor (Upward Ramp)\r\n\r\n\tval = phase; \r\n\r\n} else if (type == 3) { \r\n//------------------------------------------------------------\n// Type 3: Inverse Phasor (Downward Ramp)\r\n\r\n\tval = 1. - phase;\r\n\r\n} else if (type == 4) {\r\n//------------------------------------------------------------\n// Type 4: Triangle\r\n\r\n\tval = fold(2 * phase, 0, 1);\r\n\r\n} else if (type == 5) {\r\n//------------------------------------------------------------\n// Type 5: Square\r\n\t\r\n\tval = phase > 0.5;\r\n\t\r\n} else if (type == 6) {\r\n//------------------------------------------------------------\n// Type 6: SAH Noise\r\n\r\n\tif (delta(phase) < 0) {\r\n\t\tsah_noise = noise();\r\n\t}\r\n\tval = (sah_noise + 1.) * 0.5;\r\n\r\n} else if (type == 7) { \r\n//------------------------------------------------------------\n// Type 7: Binary SAH Noise\r\n\r\n\t// TODO: need to verify exactly same behavior as max version\r\n\tif (delta(phase) < 0) {\r\n\t\tsah_noise = noise();\r\n\t}\r\n\tval = sah_noise > 0.;\r\n\t\r\n} else if (type == 8) {\r\n//------------------------------------------------------------\n// Type 8: Stray Noise\r\n\r\n\tval = 0.5 + 0.5 * fastsin(stray(buf_wavelet, in1, 4) * 2.3);\r\n} else if (type == 9) {\r\n//------------------------------------------------------------\n// Type 9: Glider\r\n\r\n\tdrive = phase;\r\n\r\n\tif ((drive - g_oldDrive) < 0)\r\n\t{\r\n\t    g_b = g_a;\r\n\t    g_a = abs(noise());\r\n\t}\r\n\t\r\n\tg_oldDrive = drive;\r\n\tsinDrive = 0.5 + (0.5 * fastsin(drive * pi - pi / 2));\r\n\t\r\n\tval = sinDrive * g_a + (1 - sinDrive) * g_b;\r\n}\r\n\r\n\r\nout1 = val;",
                    "fontface": 0,
                    "fontname": "<Monospaced>",
                    "fontsize": 12.0,
                    "id": "obj-7",
                    "maxclass": "codebox",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        50.0,
                        68.0,
                        790.0,
                        791.0
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-5",
                    "maxclass": "newobj",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        821.0,
                        14.0,
                        28.0,
                        22.0
                    ],
                    "text": "in 3"
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
                        50.0,
                        14.0,
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
                        435.5,
                        14.0,
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
                        50.0,
                        872.0,
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
                        "obj-7",
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
                        "obj-7",
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
                        "obj-7",
                        2
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
                        "obj-4",
                        0
                    ],
                    "source": [
                        "obj-7",
                        0
                    ]
                }
            }
        ]
    }
}