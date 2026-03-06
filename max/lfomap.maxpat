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
        "rect": [ 59.0, 119.0, 1000.0, 717.0 ],
        "boxes": [
            {
                "box": {
                    "bubble": 1,
                    "bubblepoint": 0.06,
                    "bubbleside": 2,
                    "bubbletextmargin": 6,
                    "bubbleusescolors": 1,
                    "fontsize": 11.0,
                    "id": "obj-49",
                    "linecount": 3,
                    "maxclass": "live.comment",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patching_rect": [ 181.0, 641.0, 146.0, 67.0 ],
                    "suppressinlet": 1,
                    "text": "Enable this patch cord for a moving middle line as seen in some oscilloscopes.",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-17",
                    "maxclass": "newobj",
                    "numinlets": 4,
                    "numoutlets": 1,
                    "outlettype": [ "signal" ],
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
                        "rect": [ 107.0, 186.0, 382.0, 258.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                                    "id": "obj-16",
                                    "maxclass": "newobj",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
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
                                        "rect": [ 158.0, 460.0, 469.0, 280.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-1",
                                                    "index": 1,
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 82.0, 183.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 109.0, 72.0, 223.0, 22.0 ],
                                                    "text": "sizeinsamps 8192, fill 1, apply blackman"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "bang" ],
                                                    "patching_rect": [ 82.0, 24.0, 58.0, 22.0 ],
                                                    "text": "loadbang"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-26",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 82.0, 144.0, 152.0, 22.0 ],
                                                    "text": "buf_wavelet ---buf_wavelet"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-32",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [ "float", "bang" ],
                                                    "patching_rect": [ 109.0, 100.0, 206.0, 22.0 ],
                                                    "text": "buffer~ ---buf_wavelet @samps 8192"
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-1", 0 ],
                                                    "source": [ "obj-26", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-32", 0 ],
                                                    "source": [ "obj-3", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-26", 0 ],
                                                    "order": 1,
                                                    "source": [ "obj-9", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 0 ],
                                                    "order": 0,
                                                    "source": [ "obj-9", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 65.0, 83.0, 70.0, 22.0 ],
                                    "text": "p init_glider"
                                }
                            },
                            {
                                "box": {
                                    "color": [ 0.964705882352941, 0.0, 1.0, 1.0 ],
                                    "id": "obj-3",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
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
                                        "rect": [ 120.0, 178.0, 462.0, 197.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "id": "obj-7",
                                                    "maxclass": "newobj",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 369.0, 26.0, 28.0, 22.0 ],
                                                    "text": "in 4"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 209.0, 26.0, 28.0, 22.0 ],
                                                    "text": "in 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "color": [ 0.964705882352941, 0.0, 1.0, 1.0 ],
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
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
                                                        "rect": [ 144.0, 431.0, 947.0, 823.0 ],
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
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 50.0, 68.0, 790.0, 791.0 ]
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-5",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 0,
                                                                    "numoutlets": 1,
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 821.0, 14.0, 28.0, 22.0 ],
                                                                    "text": "in 3"
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-1",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 0,
                                                                    "numoutlets": 1,
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 50.0, 14.0, 28.0, 22.0 ],
                                                                    "text": "in 1"
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-2",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 0,
                                                                    "numoutlets": 1,
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 435.5, 14.0, 28.0, 22.0 ],
                                                                    "text": "in 2"
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-4",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 1,
                                                                    "numoutlets": 0,
                                                                    "patching_rect": [ 50.0, 872.0, 35.0, 22.0 ],
                                                                    "text": "out 1"
                                                                }
                                                            }
                                                        ],
                                                        "lines": [
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-7", 0 ],
                                                                    "source": [ "obj-1", 0 ]
                                                                }
                                                            },
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-7", 1 ],
                                                                    "source": [ "obj-2", 0 ]
                                                                }
                                                            },
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-7", 2 ],
                                                                    "source": [ "obj-5", 0 ]
                                                                }
                                                            },
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-4", 0 ],
                                                                    "source": [ "obj-7", 0 ]
                                                                }
                                                            }
                                                        ]
                                                    },
                                                    "patching_rect": [ 47.0, 104.0, 342.0, 22.0 ],
                                                    "text": "gen @t waveform"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 47.0, 26.0, 28.0, 22.0 ],
                                                    "text": "in 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 128.0, 26.0, 28.0, 22.0 ],
                                                    "text": "in 2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "color": [ 0.964705882352941, 0.0, 1.0, 1.0 ],
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
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
                                                        "rect": [ 84.0, 144.0, 653.0, 641.0 ],
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
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 40.0, 70.0, 524.0, 470.0 ]
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-1",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 0,
                                                                    "numoutlets": 1,
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 40.0, 31.0, 28.0, 22.0 ],
                                                                    "text": "in 1"
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-2",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 0,
                                                                    "numoutlets": 1,
                                                                    "outlettype": [ "" ],
                                                                    "patching_rect": [ 545.0, 31.0, 28.0, 22.0 ],
                                                                    "text": "in 2"
                                                                }
                                                            },
                                                            {
                                                                "box": {
                                                                    "id": "obj-4",
                                                                    "maxclass": "newobj",
                                                                    "numinlets": 1,
                                                                    "numoutlets": 0,
                                                                    "patching_rect": [ 40.0, 557.0, 35.0, 22.0 ],
                                                                    "text": "out 1"
                                                                }
                                                            }
                                                        ],
                                                        "lines": [
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-5", 0 ],
                                                                    "source": [ "obj-1", 0 ]
                                                                }
                                                            },
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-5", 1 ],
                                                                    "source": [ "obj-2", 0 ]
                                                                }
                                                            },
                                                            {
                                                                "patchline": {
                                                                    "destination": [ "obj-4", 0 ],
                                                                    "source": [ "obj-5", 0 ]
                                                                }
                                                            }
                                                        ]
                                                    },
                                                    "patching_rect": [ 47.0, 65.0, 100.0, 22.0 ],
                                                    "text": "gen @t exponent"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 47.0, 143.0, 35.0, 22.0 ],
                                                    "text": "out 1"
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 0 ],
                                                    "source": [ "obj-1", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 1 ],
                                                    "source": [ "obj-2", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-5", 0 ],
                                                    "source": [ "obj-3", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-4", 0 ],
                                                    "source": [ "obj-5", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-5", 1 ],
                                                    "source": [ "obj-6", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-5", 2 ],
                                                    "source": [ "obj-7", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 50.0, 126.0, 235.0, 22.0 ],
                                    "text": "gen~ @t ShapeAndWaveform"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float) frequency",
                                    "id": "obj-10",
                                    "index": 3,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 194.0, 37.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) sync on",
                                    "id": "obj-19",
                                    "index": 4,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 266.0, 37.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) phase",
                                    "id": "obj-93",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 50.0, 37.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(int) waveform select",
                                    "id": "obj-95",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 122.0, 37.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) wave",
                                    "id": "obj-98",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 50.0, 165.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 2 ],
                                    "source": [ "obj-10", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-16", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 3 ],
                                    "source": [ "obj-19", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-98", 0 ],
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-93", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 1 ],
                                    "source": [ "obj-95", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 52.0, 468.0, 304.0, 22.0 ],
                    "text": "p ShapeAndWaveform"
                }
            },
            {
                "box": {
                    "bgmode": 0,
                    "border": 0,
                    "clickthrough": 0,
                    "enablehscroll": 0,
                    "enablevscroll": 0,
                    "id": "obj-1",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 109.0, 898.0, 224.0, 20.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 2.0, 4.0, 229.0, 18.0 ],
                    "viewvisibility": 1
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 0.0 ],
                    "bgcolor": [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 0.0 ],
                    "id": "obj-11",
                    "line_width": 1.5,
                    "maxclass": "live.scope~",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "bang" ],
                    "patching_rect": [ 148.0, 816.0, 91.0, 56.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 2.0, 25.0, 249.0, 58.0 ],
                    "range": [ -0.05, 1.05 ],
                    "samples": 144000.0,
                    "varname": "scope",
                    "vertical_divisions": 2
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-29",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
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
                        "rect": [ 614.0, 506.0, 446.0, 452.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-39",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 76.0, 10.0, 207.0, 22.0 ],
                                    "text": "loadmess getPresentationRect scope"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-53",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 76.0, 49.0, 97.0, 22.0 ],
                                    "saved_object_attributes": {
                                        "filename": "getObjectRect",
                                        "parameter_enable": 0
                                    },
                                    "text": "js getObjectRect"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-15",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 232.0, 194.0, 54.0, 22.0 ],
                                    "text": "pack 0 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-8",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 232.0, 365.0, 136.0, 22.0 ],
                                    "text": "presentation_size $1 10"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-7",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 30.0, 287.0, 53.0, 22.0 ],
                                    "text": "prepend"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-5",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 89.0, 287.0, 72.0, 22.0 ],
                                    "text": "prepend set"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-20",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 149.0, 194.0, 29.5, 22.0 ],
                                    "text": "+ 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-13",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 30.0, 125.0, 32.0, 22.0 ],
                                    "text": "f 0.5"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-12",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "" ],
                                    "patching_rect": [ 76.0, 88.0, 31.77777777777777, 22.0 ],
                                    "text": "t b l"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-63",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 4,
                                    "outlettype": [ "int", "int", "int", "int" ],
                                    "patching_rect": [ 89.0, 125.0, 197.5, 22.0 ],
                                    "text": "unpack 0 0 0 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-1",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 30.0, 326.0, 39.0, 22.0 ],
                                    "text": "round"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-156",
                                    "maxclass": "newobj",
                                    "numinlets": 6,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 30.0, 248.0, 216.5, 22.0 ],
                                    "text": "scale 0. 1. 59. 8."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-157",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 30.0, 365.0, 156.0, 22.0 ],
                                    "text": "presentation_position $1 $2"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(0 - 1) vertical position of line, default 0.5",
                                    "id": "obj-3",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 30.0, 40.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "to line",
                                    "id": "obj-6",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 30.0, 404.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-157", 0 ],
                                    "source": [ "obj-1", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-13", 0 ],
                                    "source": [ "obj-12", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-63", 0 ],
                                    "source": [ "obj-12", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-156", 0 ],
                                    "source": [ "obj-13", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-8", 0 ],
                                    "source": [ "obj-15", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-7", 0 ],
                                    "source": [ "obj-156", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "source": [ "obj-157", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-156", 3 ],
                                    "source": [ "obj-20", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-13", 0 ],
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-53", 0 ],
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-7", 0 ],
                                    "source": [ "obj-5", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 0 ],
                                    "source": [ "obj-53", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-15", 1 ],
                                    "order": 0,
                                    "source": [ "obj-63", 3 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-15", 0 ],
                                    "source": [ "obj-63", 2 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-156", 4 ],
                                    "order": 0,
                                    "source": [ "obj-63", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-20", 1 ],
                                    "order": 1,
                                    "source": [ "obj-63", 3 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-20", 0 ],
                                    "order": 1,
                                    "source": [ "obj-63", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-5", 0 ],
                                    "source": [ "obj-63", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-1", 0 ],
                                    "source": [ "obj-7", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "source": [ "obj-8", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 191.0, 716.0, 91.0, 22.0 ],
                    "text": "p SetOffsetLine"
                }
            },
            {
                "box": {
                    "id": "obj-30",
                    "linecolor": [ 0.24313725490196078, 0.24313725490196078, 0.24313725490196078, 1.0 ],
                    "maxclass": "live.line",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 191.0, 746.0, 97.0, 13.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 2.0, 54.0, 249.0, 10.0 ],
                    "saved_attribute_attributes": {
                        "linecolor": {
                            "expression": "themecolor.live_lcd_frame"
                        }
                    }
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-59",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "bang", "int" ],
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
                        "rect": [ 62.0, 282.0, 290.0, 283.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-3",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 185.0, 168.0, 22.0, 22.0 ],
                                    "text": "t 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-46",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "bang", "" ],
                                    "patching_rect": [ 172.0, 129.0, 44.0, 22.0 ],
                                    "text": "sel 1 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-41",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 50.0, 60.0, 29.5, 22.0 ],
                                    "text": "< 5"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-40",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 50.0, 129.0, 87.0, 22.0 ],
                                    "text": "prepend active"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(int) waveform select",
                                    "id": "obj-51",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 50.0, 13.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "to shape numbox",
                                    "id": "obj-52",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 50.0, 205.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "0 if shape is disabled",
                                    "id": "obj-53",
                                    "index": 2,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 185.0, 205.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-53", 0 ],
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-52", 0 ],
                                    "source": [ "obj-40", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-40", 0 ],
                                    "order": 1,
                                    "source": [ "obj-41", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-46", 0 ],
                                    "order": 0,
                                    "source": [ "obj-41", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-46", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-52", 0 ],
                                    "source": [ "obj-46", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-41", 0 ],
                                    "source": [ "obj-51", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 147.0, 404.0, 91.0, 22.0 ],
                    "text": "p ShapeEnable"
                }
            },
            {
                "box": {
                    "id": "obj-25",
                    "maxclass": "live.comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 215.5, 231.0, 25.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 67.0, 152.0, 27.0, 18.0 ],
                    "text": "×10",
                    "textjustification": 0
                }
            },
            {
                "box": {
                    "annotation": "Multiply the frequency in Hz mode. ",
                    "id": "obj-31",
                    "maxclass": "live.toggle",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "outputmode": 1,
                    "parameter_enable": 1,
                    "patching_rect": [ 194.5, 231.0, 15.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 59.0, 155.0, 11.0, 11.0 ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [ "Off", "On" ],
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_longname": "x10",
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_shortname": "x10",
                            "parameter_type": 2
                        }
                    },
                    "varname": "live.toggle"
                }
            },
            {
                "box": {
                    "id": "obj-18",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "float" ],
                    "patching_rect": [ 349.0, 898.0, 19.0, 22.0 ],
                    "text": "t f"
                }
            },
            {
                "box": {
                    "id": "obj-6",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 383.0, 898.0, 70.0, 22.0 ],
                    "text": "loadmess 1"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-32",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "float" ],
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
                        "rect": [ 196.0, 257.0, 228.0, 367.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-4",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 115.0, 127.0, 29.0, 22.0 ],
                                    "text": "t 10"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-3",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 86.0, 127.0, 22.0, 22.0 ],
                                    "text": "t 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-18",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "bang", "" ],
                                    "patching_rect": [ 86.0, 88.0, 77.0, 22.0 ],
                                    "text": "sel 0 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-25",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "float" ],
                                    "patching_rect": [ 86.0, 196.0, 30.0, 22.0 ],
                                    "text": "t b f"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-22",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 41.0, 244.0, 30.0, 22.0 ],
                                    "text": "* 1."
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float) rate",
                                    "id": "obj-29",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 41.0, 42.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) x 10",
                                    "id": "obj-30",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 86.0, 42.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float) rate",
                                    "id": "obj-31",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 41.0, 283.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-18", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-4", 0 ],
                                    "source": [ "obj-18", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-31", 0 ],
                                    "source": [ "obj-22", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-22", 1 ],
                                    "source": [ "obj-25", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-22", 0 ],
                                    "source": [ "obj-25", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-22", 0 ],
                                    "source": [ "obj-29", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-25", 0 ],
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-18", 0 ],
                                    "source": [ "obj-30", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-25", 0 ],
                                    "source": [ "obj-4", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 52.0, 305.0, 38.0, 22.0 ],
                    "text": "p x10"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-68",
                    "maxclass": "newobj",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [ "signal" ],
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
                        "rect": [ 247.0, 174.0, 315.0, 495.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-1",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 177.0, 234.0, 33.0, 22.0 ],
                                    "text": "!- 25"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-52",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 89.0, 351.0, 30.0, 22.0 ],
                                    "text": "/~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-51",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 89.0, 312.0, 60.0, 22.0 ],
                                    "text": "round~ 1."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-49",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 89.0, 273.0, 30.0, 22.0 ],
                                    "text": "*~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-44",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "int" ],
                                    "patching_rect": [ 49.0, 120.0, 30.0, 22.0 ],
                                    "text": "t b i"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-39",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 49.0, 198.0, 30.0, 22.0 ],
                                    "text": "+ 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-37",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 49.0, 81.0, 30.0, 22.0 ],
                                    "text": "> 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-36",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 49.0, 159.0, 30.0, 22.0 ],
                                    "text": "&&"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-33",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "signal", "signal" ],
                                    "patching_rect": [ 49.0, 234.0, 59.0, 22.0 ],
                                    "text": "gate~ 2 1"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(int) number of steps, 0 = off",
                                    "id": "obj-63",
                                    "index": 3,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 177.0, 18.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) steps active",
                                    "id": "obj-64",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 133.0, 18.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) wave",
                                    "id": "obj-65",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 89.0, 18.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) wave",
                                    "id": "obj-67",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 49.0, 420.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-49", 1 ],
                                    "order": 1,
                                    "source": [ "obj-1", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-52", 1 ],
                                    "order": 0,
                                    "source": [ "obj-1", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-49", 0 ],
                                    "source": [ "obj-33", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-67", 0 ],
                                    "source": [ "obj-33", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-39", 0 ],
                                    "source": [ "obj-36", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-44", 0 ],
                                    "source": [ "obj-37", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-33", 0 ],
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-36", 1 ],
                                    "source": [ "obj-44", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-36", 0 ],
                                    "source": [ "obj-44", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-51", 0 ],
                                    "source": [ "obj-49", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-52", 0 ],
                                    "source": [ "obj-51", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-67", 0 ],
                                    "source": [ "obj-52", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-1", 0 ],
                                    "order": 0,
                                    "source": [ "obj-63", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-37", 0 ],
                                    "order": 1,
                                    "source": [ "obj-63", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-36", 0 ],
                                    "source": [ "obj-64", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-33", 1 ],
                                    "source": [ "obj-65", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 53.0, 565.0, 49.0, 22.0 ],
                    "text": "p Steps"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-28",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "int", "" ],
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
                        "rect": [ 123.0, 215.0, 203.0, 347.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "comment": "(bool) steps active",
                                    "id": "obj-1",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 41.0, 252.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-22",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 76.0, 213.0, 57.0, 22.0 ],
                                    "text": "active $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-16",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 76.0, 144.0, 22.0, 22.0 ],
                                    "text": "t 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-17",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 41.0, 144.0, 22.0, 22.0 ],
                                    "text": "t 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-40",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 4,
                                    "outlettype": [ "bang", "bang", "bang", "" ],
                                    "patching_rect": [ 41.0, 75.0, 54.0, 22.0 ],
                                    "text": "sel 4 5 6"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(int) waveform",
                                    "id": "obj-25",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 41.0, 28.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "to steps control",
                                    "id": "obj-27",
                                    "index": 2,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 76.0, 252.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-1", 0 ],
                                    "order": 1,
                                    "source": [ "obj-16", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-22", 0 ],
                                    "order": 0,
                                    "source": [ "obj-16", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-1", 0 ],
                                    "order": 1,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-22", 0 ],
                                    "order": 0,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-27", 0 ],
                                    "source": [ "obj-22", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-40", 0 ],
                                    "source": [ "obj-25", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-16", 0 ],
                                    "source": [ "obj-40", 3 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-17", 0 ],
                                    "source": [ "obj-40", 2 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-17", 0 ],
                                    "source": [ "obj-40", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-17", 0 ],
                                    "source": [ "obj-40", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 68.0, 514.0, 91.0, 22.0 ],
                    "text": "p ActivateSteps"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-21",
                    "maxclass": "newobj",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
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
                        "rect": [ 310.0, 267.0, 290.0, 313.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-13",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 4,
                                    "outlettype": [ "int", "float", "int", "int" ],
                                    "patching_rect": [ 39.0, 33.0, 61.0, 22.0 ],
                                    "text": "dspstate~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-53",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": [ "", "int", "int" ],
                                    "patching_rect": [ 53.0, 111.0, 48.0, 22.0 ],
                                    "text": "change"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-32",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 53.0, 72.0, 30.0, 22.0 ],
                                    "text": "* 3."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-29",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 53.0, 150.0, 70.0, 22.0 ],
                                    "text": "samples $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-50",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 167.0, 150.0, 57.0, 22.0 ],
                                    "text": "active $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-21",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "int", "int" ],
                                    "patching_rect": [ 135.0, 111.0, 83.0, 22.0 ],
                                    "text": "live.thisdevice"
                                }
                            },
                            {
                                "box": {
                                    "comment": "to scope",
                                    "id": "obj-14",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 53.0, 219.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-32", 0 ],
                                    "source": [ "obj-13", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-50", 0 ],
                                    "source": [ "obj-21", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-14", 0 ],
                                    "source": [ "obj-29", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-53", 0 ],
                                    "source": [ "obj-32", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-14", 0 ],
                                    "source": [ "obj-50", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-29", 0 ],
                                    "source": [ "obj-53", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 249.0, 816.0, 69.0, 22.0 ],
                    "text": "p InitScope"
                }
            },
            {
                "box": {
                    "id": "obj-8",
                    "maxclass": "newobj",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [ "signal" ],
                    "patching_rect": [ 53.0, 816.0, 60.0, 22.0 ],
                    "text": "clip~ 0. 1."
                }
            },
            {
                "box": {
                    "id": "obj-5",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "int", "bang" ],
                    "patching_rect": [ 52.0, 171.0, 246.0, 22.0 ],
                    "text": "t i b"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-7",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 75.0, 933.0, 327.25, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "id": "obj-24",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "patching_rect": [ 53.0, 1147.0, 67.0, 22.0 ],
                    "save": [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
                    "text": "thispatcher"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-12",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [ "bang", "bang", "" ],
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
                        "rect": [ 244.0, 230.0, 623.0, 399.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "comment": "to 10x",
                                    "id": "obj-5",
                                    "index": 3,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 484.0, 271.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-4",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 484.0, 152.0, 33.0, 22.0 ],
                                    "text": "== 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-2",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 484.0, 199.0, 57.0, 22.0 ],
                                    "text": "active $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 17.0, 152.0, 33.0, 22.0 ],
                                    "text": "== 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-8",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 392.0, 152.0, 33.0, 22.0 ],
                                    "text": "== 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-6",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 392.0, 199.0, 61.0, 22.0 ],
                                    "text": "hidden $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-3",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 148.0, 199.0, 61.0, 22.0 ],
                                    "text": "hidden $1"
                                }
                            },
                            {
                                "box": {
                                    "comment": "to synced dial",
                                    "id": "obj-26",
                                    "index": 2,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 279.0, 271.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-29",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 315.0, 199.0, 57.0, 22.0 ],
                                    "text": "active $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-33",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "" ],
                                    "patching_rect": [ 279.0, 152.0, 50.0, 22.0 ],
                                    "text": "select 1"
                                }
                            },
                            {
                                "box": {
                                    "comment": "to free dial",
                                    "id": "obj-25",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 17.0, 271.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-24",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 75.0, 199.0, 57.0, 22.0 ],
                                    "text": "active $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-19",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "" ],
                                    "patching_rect": [ 17.0, 199.0, 50.0, 22.0 ],
                                    "text": "select 1"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) time mode",
                                    "id": "obj-17",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 17.0, 23.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-19", 0 ],
                                    "order": 1,
                                    "source": [ "obj-10", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-24", 0 ],
                                    "order": 0,
                                    "source": [ "obj-10", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-10", 0 ],
                                    "order": 5,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-29", 0 ],
                                    "order": 2,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "order": 4,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-33", 0 ],
                                    "order": 3,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-4", 0 ],
                                    "order": 0,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-8", 0 ],
                                    "order": 1,
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-25", 0 ],
                                    "source": [ "obj-19", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-5", 0 ],
                                    "source": [ "obj-2", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-25", 0 ],
                                    "source": [ "obj-24", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-26", 0 ],
                                    "source": [ "obj-29", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-25", 0 ],
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-26", 0 ],
                                    "source": [ "obj-33", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-2", 0 ],
                                    "source": [ "obj-4", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-26", 0 ],
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "source": [ "obj-8", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 52.0, 201.0, 161.0, 22.0 ],
                    "text": "p TimeMode"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-3",
                    "maxclass": "newobj",
                    "numinlets": 5,
                    "numoutlets": 2,
                    "outlettype": [ "signal", "" ],
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
                        "rect": [ 361.0, 114.0, 1093.0, 756.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-14",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 183.0, 620.0, 89.0, 22.0 ],
                                    "text": "+~ 0."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-15",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 183.0, 660.0, 40.0, 22.0 ],
                                    "text": "%~ 1."
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, 0 - 1) phase offset",
                                    "id": "obj-17",
                                    "index": 4,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 794.0, 32.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-6",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 454.0, 340.0, 30.0, 22.0 ],
                                    "text": "f"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-5",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "int" ],
                                    "patching_rect": [ 275.0, 266.0, 30.0, 22.0 ],
                                    "text": "t b i"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-4",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 370.0, 340.0, 30.0, 22.0 ],
                                    "text": "f"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, hz) rate",
                                    "id": "obj-2",
                                    "index": 2,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 305.0, 411.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleusescolors": 1,
                                    "id": "obj-1",
                                    "linecount": 6,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 682.0, 300.5, 194.0, 91.0 ],
                                    "saved_attribute_attributes": {
                                        "textcolor": {
                                            "expression": "themecolor.live_control_fg"
                                        }
                                    },
                                    "text": "This click~ could be connected directly to the free phasor, but that would slightly change the behaviour compared to earlier versions, so we're keeping this for backward compatibility."
                                }
                            },
                            {
                                "box": {
                                    "coll_data": {
                                        "count": 24,
                                        "data": [
                                            {
                                                "key": 0,
                                                "value": [ 30 ]
                                            },
                                            {
                                                "key": 1,
                                                "value": [ 40 ]
                                            },
                                            {
                                                "key": 2,
                                                "value": [ 60 ]
                                            },
                                            {
                                                "key": 3,
                                                "value": [ 80 ]
                                            },
                                            {
                                                "key": 4,
                                                "value": [ 120 ]
                                            },
                                            {
                                                "key": 5,
                                                "value": [ 160 ]
                                            },
                                            {
                                                "key": 6,
                                                "value": [ 240 ]
                                            },
                                            {
                                                "key": 7,
                                                "value": [ 320 ]
                                            },
                                            {
                                                "key": 8,
                                                "value": [ 360 ]
                                            },
                                            {
                                                "key": 9,
                                                "value": [ 480 ]
                                            },
                                            {
                                                "key": 10,
                                                "value": [ 600 ]
                                            },
                                            {
                                                "key": 11,
                                                "value": [ 640 ]
                                            },
                                            {
                                                "key": 12,
                                                "value": [ 720 ]
                                            },
                                            {
                                                "key": 13,
                                                "value": [ 960 ]
                                            },
                                            {
                                                "key": 14,
                                                "value": [ 1440 ]
                                            },
                                            {
                                                "key": 15,
                                                "value": [ 1920 ]
                                            },
                                            {
                                                "key": 16,
                                                "value": [ 2880 ]
                                            },
                                            {
                                                "key": 17,
                                                "value": [ 3840 ]
                                            },
                                            {
                                                "key": 18,
                                                "value": [ 5760 ]
                                            },
                                            {
                                                "key": 19,
                                                "value": [ 7680 ]
                                            },
                                            {
                                                "key": 20,
                                                "value": [ 11520 ]
                                            },
                                            {
                                                "key": 21,
                                                "value": [ 15360 ]
                                            },
                                            {
                                                "key": 22,
                                                "value": [ 30720 ]
                                            },
                                            {
                                                "key": 23,
                                                "value": [ 61440 ]
                                            }
                                        ]
                                    },
                                    "id": "obj-21",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 4,
                                    "outlettype": [ "", "", "", "" ],
                                    "patching_rect": [ 405.0, 79.0, 63.0, 22.0 ],
                                    "saved_object_attributes": {
                                        "embed": 1,
                                        "precision": 6
                                    },
                                    "text": "coll ---rate"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-44",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 454.0, 242.0, 62.0, 22.0 ],
                                    "text": "switch 2 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-25",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 454.0, 196.0, 30.0, 22.0 ],
                                    "text": "+ 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-20",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "int", "int" ],
                                    "patching_rect": [ 405.0, 118.0, 69.0, 22.0 ],
                                    "text": "t i i"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-16",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 454.0, 157.0, 53.0, 22.0 ],
                                    "text": ">= 1920"
                                }
                            },
                            {
                                "box": {
                                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                                    "id": "obj-8",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
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
                                        "rect": [ 59.0, 106.0, 336.0, 280.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "bubble": 1,
                                                    "bubbleusescolors": 1,
                                                    "id": "obj-14",
                                                    "linecount": 2,
                                                    "maxclass": "comment",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 110.0, 179.0, 174.0, 37.0 ],
                                                    "saved_attribute_attributes": {
                                                        "textcolor": {
                                                            "expression": "themecolor.live_control_fg"
                                                        }
                                                    },
                                                    "text": "Note: continuously outputs updated rates as Live plays"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [ "bang", "int" ],
                                                    "patching_rect": [ 110.0, 142.0, 30.0, 22.0 ],
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "float" ],
                                                    "patching_rect": [ 73.0, 103.0, 48.0, 22.0 ],
                                                    "text": "/ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-28",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [ "int", "int" ],
                                                    "patching_rect": [ 73.0, 64.0, 47.0, 22.0 ],
                                                    "text": "unpack"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-26",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "float" ],
                                                    "patching_rect": [ 73.0, 142.0, 30.0, 22.0 ],
                                                    "text": "* 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-20",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 9,
                                                    "outlettype": [ "int", "int", "int", "float", "list", "float", "float", "int", "int" ],
                                                    "patching_rect": [ 31.0, 25.0, 103.0, 22.0 ],
                                                    "text": "plugsync~"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(int) ticks",
                                                    "id": "obj-4",
                                                    "index": 1,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "int" ],
                                                    "patching_rect": [ 149.0, 25.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(int) ticks",
                                                    "id": "obj-5",
                                                    "index": 1,
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 73.0, 179.0, 30.0, 30.0 ]
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-26", 0 ],
                                                    "source": [ "obj-2", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-28", 0 ],
                                                    "source": [ "obj-20", 4 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-5", 0 ],
                                                    "source": [ "obj-26", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-2", 1 ],
                                                    "source": [ "obj-28", 1 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-2", 0 ],
                                                    "source": [ "obj-28", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-26", 1 ],
                                                    "source": [ "obj-3", 1 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-26", 0 ],
                                                    "source": [ "obj-3", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 0 ],
                                                    "source": [ "obj-4", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 497.0, 196.0, 125.0, 22.0 ],
                                    "text": "p ApplyTimeSignature"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 285.0, 340.0, 30.0, 22.0 ],
                                    "text": "+ 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 285.0, 379.0, 188.0, 22.0 ],
                                    "text": "switch"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-3",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 637.0, 335.0, 39.0, 22.0 ],
                                    "text": "click~"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) time mode",
                                    "id": "obj-23",
                                    "index": 5,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 942.0, 32.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleusescolors": 1,
                                    "id": "obj-35",
                                    "linecount": 5,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 412.0, 450.0, 196.0, 78.0 ],
                                    "saved_attribute_attributes": {
                                        "textcolor": {
                                            "expression": "themecolor.live_control_fg"
                                        }
                                    },
                                    "text": "If the synced phasor is active, always keep the phase of the free running phasor in sync, i.e. when the synced phasor jumps back, reset the free phasor."
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleside": 3,
                                    "bubbleusescolors": 1,
                                    "id": "obj-34",
                                    "linecount": 5,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 14.0, 450.0, 165.0, 78.0 ],
                                    "saved_attribute_attributes": {
                                        "textcolor": {
                                            "expression": "themecolor.live_control_fg"
                                        }
                                    },
                                    "text": "Switch to the free running phasor when playback is stopped or sync mode is off, i.e. if the syned phasor stops changing."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-36",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 347.0, 478.0, 44.0, 22.0 ],
                                    "text": "==~ -1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-33",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 347.0, 443.0, 55.0, 22.0 ],
                                    "text": "change~"
                                }
                            },
                            {
                                "box": {
                                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                                    "id": "obj-31",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
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
                                        "rect": [ 64.0, 115.0, 323.0, 368.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "bubble": 1,
                                                    "bubbleusescolors": 1,
                                                    "id": "obj-2",
                                                    "linecount": 2,
                                                    "maxclass": "comment",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 159.0, 116.5, 118.0, 37.0 ],
                                                    "saved_attribute_attributes": {
                                                        "textcolor": {
                                                            "expression": "themecolor.live_control_fg"
                                                        }
                                                    },
                                                    "text": "Phase Retrigger \n(Audio Rate)"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-11",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 64.0, 163.0, 33.0, 22.0 ],
                                                    "text": "!-~ 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 50.0, 202.0, 33.0, 22.0 ],
                                                    "text": "+~"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 50.0, 241.0, 36.0, 22.0 ],
                                                    "text": "%~ 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-21",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 64.0, 124.0, 84.0, 22.0 ],
                                                    "text": "sah~ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 50.0, 85.0, 54.0, 22.0 ],
                                                    "text": "phasor~"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(float, hz) frequency",
                                                    "id": "obj-12",
                                                    "index": 1,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 50.0, 40.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(signal) click to reset",
                                                    "id": "obj-18",
                                                    "index": 2,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 129.0, 40.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(signal) phase",
                                                    "id": "obj-23",
                                                    "index": 1,
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 50.0, 280.0, 30.0, 30.0 ]
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-5", 0 ],
                                                    "source": [ "obj-10", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-10", 1 ],
                                                    "source": [ "obj-11", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 0 ],
                                                    "source": [ "obj-12", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-21", 1 ],
                                                    "source": [ "obj-18", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-11", 0 ],
                                                    "source": [ "obj-21", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-10", 0 ],
                                                    "order": 1,
                                                    "source": [ "obj-3", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-21", 0 ],
                                                    "order": 0,
                                                    "source": [ "obj-3", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-23", 0 ],
                                                    "source": [ "obj-5", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 285.0, 542.0, 81.0, 22.0 ],
                                    "text": "p FreePhasor"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-30",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 942.0, 266.0, 51.0, 22.0 ],
                                    "text": "pcontrol"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-29",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 942.0, 227.0, 61.0, 22.0 ],
                                    "text": "enable $1"
                                }
                            },
                            {
                                "box": {
                                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                                    "id": "obj-27",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
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
                                        "rect": [ 59.0, 104.0, 206.0, 194.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 29.0, 65.0, 76.0, 22.0 ],
                                                    "text": "append ticks"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-29",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 29.0, 104.0, 116.0, 22.0 ],
                                                    "text": "phasor~ 1n @lock 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(int, ticks) frequency",
                                                    "id": "obj-18",
                                                    "index": 1,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 29.0, 18.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(signal) phase",
                                                    "id": "obj-23",
                                                    "index": 1,
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 29.0, 143.0, 30.0, 30.0 ]
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-29", 0 ],
                                                    "source": [ "obj-1", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-1", 0 ],
                                                    "source": [ "obj-18", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-23", 0 ],
                                                    "source": [ "obj-29", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 942.0, 335.0, 97.0, 22.0 ],
                                    "text": "p SyncedPhasor"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-7",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 183.0, 542.0, 33.0, 22.0 ],
                                    "text": "+~ 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-11",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 183.0, 478.0, 36.0, 22.0 ],
                                    "text": "!=~ 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-12",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 183.0, 581.0, 224.0, 22.0 ],
                                    "text": "selector~ 2 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-19",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 454.0, 280.0, 98.0, 22.0 ],
                                    "text": "translate ticks hz"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bang) resync lfo",
                                    "id": "obj-13",
                                    "index": 3,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "bang" ],
                                    "patching_rect": [ 637.0, 32.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "annotation": "",
                                    "comment": "(signal) phase",
                                    "id": "obj-52",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 183.0, 699.0, 30.0, 30.0 ],
                                    "prototypename": "M4L.Arial10"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, hz) frequency",
                                    "id": "obj-41",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 370.0, 32.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(int) sync rate option",
                                    "id": "obj-42",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 405.0, 32.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 0 ],
                                    "source": [ "obj-10", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-7", 0 ],
                                    "source": [ "obj-11", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-14", 0 ],
                                    "source": [ "obj-12", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-13", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-15", 0 ],
                                    "source": [ "obj-14", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-52", 0 ],
                                    "source": [ "obj-15", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-25", 0 ],
                                    "source": [ "obj-16", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-14", 1 ],
                                    "midpoints": [ 803.5, 612.5, 262.5, 612.5 ],
                                    "source": [ "obj-17", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "source": [ "obj-19", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-16", 0 ],
                                    "source": [ "obj-20", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-44", 1 ],
                                    "order": 1,
                                    "source": [ "obj-20", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-8", 0 ],
                                    "order": 0,
                                    "source": [ "obj-20", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-20", 0 ],
                                    "source": [ "obj-21", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-29", 0 ],
                                    "order": 0,
                                    "source": [ "obj-23", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-5", 0 ],
                                    "order": 1,
                                    "source": [ "obj-23", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-44", 0 ],
                                    "source": [ "obj-25", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 2 ],
                                    "order": 0,
                                    "source": [ "obj-27", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-33", 0 ],
                                    "order": 1,
                                    "source": [ "obj-27", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-30", 0 ],
                                    "source": [ "obj-29", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-33", 0 ],
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-27", 0 ],
                                    "source": [ "obj-30", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 1 ],
                                    "source": [ "obj-31", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-11", 0 ],
                                    "order": 1,
                                    "source": [ "obj-33", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-36", 0 ],
                                    "order": 0,
                                    "source": [ "obj-33", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-31", 1 ],
                                    "source": [ "obj-36", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 1 ],
                                    "source": [ "obj-4", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-4", 0 ],
                                    "source": [ "obj-41", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-21", 0 ],
                                    "source": [ "obj-42", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-19", 0 ],
                                    "order": 1,
                                    "source": [ "obj-44", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-27", 0 ],
                                    "order": 0,
                                    "source": [ "obj-44", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-10", 0 ],
                                    "source": [ "obj-5", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-4", 0 ],
                                    "order": 1,
                                    "source": [ "obj-5", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "order": 0,
                                    "source": [ "obj-5", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 2 ],
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 0 ],
                                    "source": [ "obj-7", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-44", 2 ],
                                    "source": [ "obj-8", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-2", 0 ],
                                    "order": 0,
                                    "source": [ "obj-9", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-31", 0 ],
                                    "order": 1,
                                    "source": [ "obj-9", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 52.0, 335.0, 304.0, 22.0 ],
                    "text": "p TimingAndPhase"
                }
            },
            {
                "box": {
                    "color": [ 0.733333333333333, 1.0, 0.0, 1.0 ],
                    "id": "obj-4",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 0,
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
                        "rect": [ 134.0, 172.0, 269.0, 304.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-4",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "bang", "" ],
                                    "patching_rect": [ 47.0, 110.0, 57.0, 22.0 ],
                                    "text": "sel 1 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-14",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 47.0, 75.0, 56.0, 22.0 ],
                                    "text": "deferlow"
                                }
                            },
                            {
                                "box": {
                                    "annotation": "",
                                    "comment": "(bool) sync / free",
                                    "id": "obj-13",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 47.0, 28.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-12",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 66.0, 188.0, 144.0, 22.0 ],
                                    "text": "edit 0 Main 2 \"Freq Rate\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-11",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 47.0, 149.0, 144.0, 22.0 ],
                                    "text": "edit 0 Main 2 \"Sync Rate\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-2",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 47.0, 255.0, 64.0, 22.0 ],
                                    "text": "live.banks"
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-2", 0 ],
                                    "source": [ "obj-11", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-2", 0 ],
                                    "source": [ "obj-12", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-14", 0 ],
                                    "source": [ "obj-13", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-4", 0 ],
                                    "source": [ "obj-14", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-11", 0 ],
                                    "source": [ "obj-4", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 0 ],
                                    "source": [ "obj-4", 1 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 379.0, 164.0, 79.0, 22.0 ],
                    "text": "p PushBanks"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-47",
                    "maxclass": "newobj",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [ "signal" ],
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
                        "rect": [ 134.0, 172.0, 219.0, 343.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-1",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 124.0, 67.0, 31.0, 22.0 ],
                                    "text": "sig~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-3",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 79.0, 67.0, 31.0, 22.0 ],
                                    "text": "sig~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-40",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 79.0, 141.0, 40.0, 22.0 ],
                                    "text": "*~ 0.5"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-38",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 79.0, 185.0, 64.0, 22.0 ],
                                    "text": "!-~ 0."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-11",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 37.0, 224.0, 61.0, 22.0 ],
                                    "text": "+~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 37.0, 185.0, 30.0, 22.0 ],
                                    "text": "*~"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, 0 - 1) amount",
                                    "id": "obj-36",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 79.0, 20.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, 0 - 1) offset",
                                    "id": "obj-37",
                                    "index": 3,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 124.0, 20.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) to scale",
                                    "id": "obj-44",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 37.0, 20.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) scaled signal",
                                    "id": "obj-46",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 37.0, 263.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-38", 1 ],
                                    "source": [ "obj-1", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-46", 0 ],
                                    "source": [ "obj-11", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-40", 0 ],
                                    "order": 0,
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 1 ],
                                    "order": 1,
                                    "source": [ "obj-3", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-36", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-1", 0 ],
                                    "source": [ "obj-37", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-11", 1 ],
                                    "source": [ "obj-38", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-38", 0 ],
                                    "source": [ "obj-40", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 0 ],
                                    "source": [ "obj-44", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-11", 0 ],
                                    "source": [ "obj-9", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 53.0, 770.0, 114.0, 22.0 ],
                    "text": "p SignalScaling"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-43",
                    "maxclass": "newobj",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [ "signal" ],
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
                        "rect": [ 105.0, 136.0, 321.0, 219.0 ],
                        "enablehscroll": 0,
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-46",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 150.0, 78.0, 30.0, 22.0 ],
                                    "text": "* 2."
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleusescolors": 1,
                                    "id": "obj-1",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 182.0, 78.0, 108.0, 24.0 ],
                                    "saved_attribute_attributes": {
                                        "textcolor": {
                                            "expression": "themecolor.live_control_fg"
                                        }
                                    },
                                    "text": "100% is 200ms"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) wave",
                                    "id": "obj-6",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 53.0, 31.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, %) smoothing",
                                    "id": "obj-5",
                                    "index": 3,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 150.0, 31.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(float, %) jitter",
                                    "id": "obj-4",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 102.0, 31.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) wave",
                                    "id": "obj-3",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 53.0, 156.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                                    "id": "obj-98",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
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
                                        "rect": [ 141.0, 182.0, 237.0, 252.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "id": "obj-18",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 40.0, 148.0, 117.0, 22.0 ],
                                                    "text": "slide~ 44100 44100"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [ "signal", "float" ],
                                                    "patching_rect": [ 80.0, 79.0, 77.0, 22.0 ],
                                                    "text": "mstosamps~"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(float, ms) smoothing",
                                                    "id": "obj-1",
                                                    "index": 2,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "float" ],
                                                    "patching_rect": [ 80.0, 32.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(signal) input",
                                                    "id": "obj-9",
                                                    "index": 1,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 40.0, 32.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(signal) smoothed wave",
                                                    "id": "obj-19",
                                                    "index": 1,
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 40.0, 187.0, 30.0, 30.0 ]
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-5", 0 ],
                                                    "source": [ "obj-1", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-19", 0 ],
                                                    "source": [ "obj-18", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-18", 2 ],
                                                    "order": 0,
                                                    "source": [ "obj-5", 1 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-18", 1 ],
                                                    "order": 1,
                                                    "source": [ "obj-5", 1 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-18", 0 ],
                                                    "source": [ "obj-9", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 53.0, 117.0, 116.0, 22.0 ],
                                    "text": "p Smooth"
                                }
                            },
                            {
                                "box": {
                                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                                    "id": "obj-99",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
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
                                        "rect": [ 121.0, 99.0, 228.0, 306.0 ],
                                        "boxes": [
                                            {
                                                "box": {
                                                    "comment": "(float, %) jitter",
                                                    "id": "obj-23",
                                                    "index": 2,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "" ],
                                                    "patching_rect": [ 118.0, 42.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "float" ],
                                                    "patching_rect": [ 118.0, 119.0, 39.0, 22.0 ],
                                                    "text": "/ 150."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 54.0, 158.0, 83.0, 22.0 ],
                                                    "text": "*~"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 30.0, 197.0, 43.0, 22.0 ],
                                                    "text": "+~"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 54.0, 119.0, 56.0, 22.0 ],
                                                    "text": "rand~ 10"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(signal) in",
                                                    "id": "obj-1",
                                                    "index": 1,
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [ "signal" ],
                                                    "patching_rect": [ 30.0, 42.0, 30.0, 30.0 ]
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "(singal) jittered",
                                                    "id": "obj-19",
                                                    "index": 1,
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [ 30.0, 238.0, 30.0, 30.0 ]
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-8", 0 ],
                                                    "source": [ "obj-1", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 0 ],
                                                    "source": [ "obj-2", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-2", 0 ],
                                                    "order": 1,
                                                    "source": [ "obj-23", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-4", 0 ],
                                                    "order": 0,
                                                    "source": [ "obj-23", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-8", 1 ],
                                                    "source": [ "obj-3", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-3", 1 ],
                                                    "source": [ "obj-4", 0 ]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [ "obj-19", 0 ],
                                                    "source": [ "obj-8", 0 ]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [ 53.0, 78.0, 68.0, 22.0 ],
                                    "text": "p Jitter"
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-99", 1 ],
                                    "source": [ "obj-4", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-98", 1 ],
                                    "source": [ "obj-46", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-46", 0 ],
                                    "source": [ "obj-5", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-99", 0 ],
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-3", 0 ],
                                    "source": [ "obj-98", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-98", 0 ],
                                    "source": [ "obj-99", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 53.0, 595.0, 213.0, 22.0 ],
                    "text": "p RandomizeAndSmooth",
                    "varname": "jitter"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-56",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "signal" ],
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
                        "rect": [ 757.0, 280.0, 310.0, 346.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-20",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 170.0, 139.0, 39.0, 22.0 ],
                                    "text": "click~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-19",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "" ],
                                    "patching_rect": [ 170.0, 101.0, 34.0, 22.0 ],
                                    "text": "sel 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-18",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 154.0, 178.0, 35.0, 22.0 ],
                                    "text": "sah~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-12",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 95.0, 178.0, 30.0, 22.0 ],
                                    "text": "+ 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 95.0, 214.0, 78.0, 22.0 ],
                                    "text": "selector~ 2 1"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) original or held signal",
                                    "id": "obj-1",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 95.0, 263.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) hold",
                                    "id": "obj-5",
                                    "index": 2,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 95.0, 20.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "comment": "(signal) in",
                                    "id": "obj-6",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "signal" ],
                                    "patching_rect": [ 25.0, 20.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 0 ],
                                    "source": [ "obj-12", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 2 ],
                                    "source": [ "obj-18", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-20", 0 ],
                                    "source": [ "obj-19", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-18", 1 ],
                                    "source": [ "obj-20", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 0 ],
                                    "order": 1,
                                    "source": [ "obj-5", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-19", 0 ],
                                    "order": 0,
                                    "source": [ "obj-5", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-18", 0 ],
                                    "order": 0,
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-9", 1 ],
                                    "order": 1,
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-1", 0 ],
                                    "source": [ "obj-9", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 53.0, 650.0, 43.0, 22.0 ],
                    "text": "p Hold"
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 18.0,
                    "id": "obj-92",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 8.0, 8.0, 43.0, 28.0 ],
                    "prototypename": "ML.subpatcher-title",
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "LFO"
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-123",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 53.0, 16.0, 136.0, 20.0 ],
                    "prototypename": "M4L.patcher-summary",
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "Generic Modulation LFO"
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 11.0,
                    "id": "obj-124",
                    "linecount": 3,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 8.0, 38.0, 502.0, 46.0 ],
                    "prototypename": "M4L.patcher-story",
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "LFO offers a periodic waveform to modulate parameters, either specific to Live or of 3rd party plug-ins. It has 8 different waveforms, rate and modulation depth, beat sync, jitter and smoothing of the waveform, phase control / inversion and easy mapping to the target parameters.  "
                }
            },
            {
                "box": {
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [ "signal", "signal" ],
                    "patching_rect": [ 383.0, 1082.0, 55.0, 22.0 ],
                    "text": "plugout~"
                }
            },
            {
                "box": {
                    "id": "obj-15",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [ "signal", "signal" ],
                    "patching_rect": [ 383.0, 1053.0, 53.0, 22.0 ],
                    "text": "plugin~"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-66",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
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
                        "rect": [ 209.0, 112.0, 449.0, 601.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-2",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 188.0, 474.0, 140.0, 22.0 ],
                                    "text": "prepend activebgoncolor"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-99",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "int", "int" ],
                                    "patching_rect": [ 57.0, 28.0, 83.0, 22.0 ],
                                    "text": "live.thisdevice"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-98",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "", "" ],
                                    "patching_rect": [ 188.0, 313.0, 55.0, 22.0 ],
                                    "text": "zl slice 3"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-97",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 289.0, 313.0, 32.0, 22.0 ],
                                    "text": "t 0.5"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-96",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "float" ],
                                    "patching_rect": [ 259.0, 313.0, 25.0, 22.0 ],
                                    "text": "t 1."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-95",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 259.0, 353.0, 72.0, 22.0 ],
                                    "text": "prepend set"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-94",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "", "" ],
                                    "patching_rect": [ 188.0, 274.0, 38.0, 22.0 ],
                                    "text": "zl reg"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-81",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "bang", "int" ],
                                    "patching_rect": [ 188.0, 210.0, 90.0, 22.0 ],
                                    "text": "t b i"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-83",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": [ "", "" ],
                                    "patching_rect": [ 57.0, 205.0, 114.0, 22.0 ],
                                    "text": "route lcd_control_fg"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-84",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 97.0, 83.0, 22.0 ],
                                    "text": "lcd_control_fg"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-85",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": [ "", "bang" ],
                                    "patching_rect": [ 57.0, 136.0, 62.0, 22.0 ],
                                    "text": "live.colors"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-87",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "bang", "" ],
                                    "patching_rect": [ 259.0, 274.0, 79.0, 22.0 ],
                                    "text": "sel 1 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-88",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 188.0, 434.0, 62.0, 22.0 ],
                                    "text": "append 1."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-6",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "parameter_enable": 0,
                                    "patching_rect": [ 188.0, 152.0, 24.0, 24.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-16",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "bang" ],
                                    "patching_rect": [ 209.0, 108.0, 69.0, 22.0 ],
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
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 188.0, 58.0, 30.0, 30.0 ]
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
                                    "patching_rect": [ 188.0, 517.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "source": [ "obj-16", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-2", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-81", 0 ],
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-16", 0 ],
                                    "order": 0,
                                    "source": [ "obj-60", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-6", 0 ],
                                    "order": 1,
                                    "source": [ "obj-60", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-87", 0 ],
                                    "source": [ "obj-81", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-94", 0 ],
                                    "source": [ "obj-81", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-94", 1 ],
                                    "source": [ "obj-83", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-85", 0 ],
                                    "source": [ "obj-84", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-83", 0 ],
                                    "source": [ "obj-85", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-84", 0 ],
                                    "midpoints": [ 109.5, 181.0, 149.0, 181.0, 149.0, 69.0, 66.5, 69.0 ],
                                    "source": [ "obj-85", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-96", 0 ],
                                    "source": [ "obj-87", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-97", 0 ],
                                    "source": [ "obj-87", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-2", 0 ],
                                    "source": [ "obj-88", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-98", 0 ],
                                    "source": [ "obj-94", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-88", 0 ],
                                    "source": [ "obj-95", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-95", 0 ],
                                    "source": [ "obj-96", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-95", 0 ],
                                    "source": [ "obj-97", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-88", 0 ],
                                    "source": [ "obj-98", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-84", 0 ],
                                    "source": [ "obj-99", 0 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 122.0, 625.0, 45.0, 22.0 ],
                    "text": "p Blink"
                }
            },
            {
                "box": {
                    "bgcolor": [ 0.285714, 0.256629, 0.217237, 0.0 ],
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-57",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 106.0, 433.5, 35.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 62.0, 83.0, 38.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Shape",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.94902, 0.376471, 0.0, 0.0 ],
                    "activeslidercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "activetricolor2": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "annotation": "Shape the LFO Waveform -  the  changes depend on the waveform -  e.g. pulsewidth for Square.",
                    "annotation_name": "Jitter",
                    "appearance": 4,
                    "focusbordercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "id": "obj-54",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 147.0, 435.0, 43.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 65.0, 98.0, 33.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activebgcolor": {
                            "expression": ""
                        },
                        "activeslidercolor": {
                            "expression": ""
                        },
                        "activetricolor2": {
                            "expression": ""
                        },
                        "focusbordercolor": {
                            "expression": ""
                        },
                        "textcolor": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "WaveShape",
                            "parameter_mmax": 100.0,
                            "parameter_mmin": -100.0,
                            "parameter_modmode": 2,
                            "parameter_shortname": "WaveShape",
                            "parameter_type": 0,
                            "parameter_units": "%.0f %",
                            "parameter_unitstyle": 9
                        }
                    },
                    "textcolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "textjustification": 0,
                    "varname": "WaveShape"
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.94902, 0.376471, 0.0, 0.0 ],
                    "activeslidercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "activetricolor2": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "annotation": "Add 'steps' to the Waveform. Off = no steps are added. ",
                    "annotation_name": "Smooth",
                    "appearance": 4,
                    "bordercolor": [ 1.0, 1.0, 1.0, 0.0 ],
                    "focusbordercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "id": "obj-13",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 132.0, 567.0, 26.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 111.0, 98.0, 26.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activebgcolor": {
                            "expression": ""
                        },
                        "activeslidercolor": {
                            "expression": ""
                        },
                        "activetricolor2": {
                            "expression": ""
                        },
                        "bordercolor": {
                            "expression": ""
                        },
                        "focusbordercolor": {
                            "expression": ""
                        },
                        "textcolor": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_enum": [ "Off", "24", "23", "22", "21", "20", "19", "18", "17", "16", "15", "14", "13", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1" ],
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "Steps",
                            "parameter_mmax": 24,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Steps",
                            "parameter_type": 2,
                            "parameter_unitstyle": 9
                        }
                    },
                    "textcolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "textjustification": 0,
                    "varname": "Steps"
                }
            },
            {
                "box": {
                    "bgcolor": [ 0.285714, 0.256629, 0.217237, 0.0 ],
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-14",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 132.0, 544.0, 35.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 107.0, 83.0, 38.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Steps",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "bgcolor": [ 0.285714, 0.256629, 0.217237, 0.0 ],
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-61",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 188.0, 364.0, 52.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 2.0, 83.0, 52.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Waveform",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.94902, 0.376471, 0.0, 0.0 ],
                    "activeslidercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "activetricolor2": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "annotation": "Introduces some randomness in the LFO signal.",
                    "annotation_name": "Jitter",
                    "appearance": 4,
                    "focusbordercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "id": "obj-10",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 185.0, 567.0, 43.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 158.0, 98.0, 32.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activebgcolor": {
                            "expression": ""
                        },
                        "activeslidercolor": {
                            "expression": ""
                        },
                        "activetricolor2": {
                            "expression": ""
                        },
                        "focusbordercolor": {
                            "expression": ""
                        },
                        "textcolor": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "Jitter",
                            "parameter_mmax": 100.0,
                            "parameter_modmode": 4,
                            "parameter_shortname": "Jitter",
                            "parameter_type": 1,
                            "parameter_unitstyle": 5
                        }
                    },
                    "textcolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "textjustification": 0,
                    "varname": "Jitter"
                }
            },
            {
                "box": {
                    "id": "obj-35",
                    "maxclass": "live.line",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 331.0, 118.0, 6.0, 5.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 48.0, 136.0, 7.0, 5.0 ]
                }
            },
            {
                "box": {
                    "annotation": "Shifts the center point of the LFO waveform.",
                    "annotation_name": "Offset",
                    "id": "obj-120",
                    "maxclass": "live.dial",
                    "needlemode": 2,
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 140.0, 688.0, 27.0, 48.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 148.0, 118.0, 34.0, 48.0 ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "Offset",
                            "parameter_mmax": 100.0,
                            "parameter_mmin": -100.0,
                            "parameter_modmode": 4,
                            "parameter_shortname": "Offset",
                            "parameter_type": 1,
                            "parameter_unitstyle": 5
                        }
                    },
                    "varname": "Offset"
                }
            },
            {
                "box": {
                    "annotation": "Toggles between Beat Sync and Free running (Hz).",
                    "annotation_name": "Time Mode",
                    "fontsize": 9.0,
                    "id": "obj-26",
                    "livemode": 1,
                    "maxclass": "live.tab",
                    "num_lines_patching": 2,
                    "num_lines_presentation": 2,
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [ "", "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 340.0, 103.0, 21.0, 31.0 ],
                    "pictures": [ "hz-icon.svg", "beat-icon.svg" ],
                    "presentation": 1,
                    "presentation_rect": [ 59.0, 121.0, 21.0, 31.0 ],
                    "remapsvgcolors": 1,
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [ "Free", "Sync" ],
                            "parameter_linknames": 1,
                            "parameter_longname": "Time Mode",
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Time Mode",
                            "parameter_type": 2,
                            "parameter_unitstyle": 9
                        }
                    },
                    "usepicture": 1,
                    "usesvgviewbox": 1,
                    "varname": "Time Mode"
                }
            },
            {
                "box": {
                    "activeslidercolor": [ 0.278431, 0.839216, 1.0, 1.0 ],
                    "activetricolor2": [ 0.278431, 0.839216, 1.0, 1.0 ],
                    "annotation": "Shift the Phase of the LFO.",
                    "appearance": 1,
                    "id": "obj-140",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 246.75, 308.0, 38.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 198.0, 132.0, 45.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activeslidercolor": {
                            "expression": ""
                        },
                        "activetricolor2": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "Phase",
                            "parameter_mmax": 100.0,
                            "parameter_modmode": 4,
                            "parameter_shortname": "Phase",
                            "parameter_type": 1,
                            "parameter_unitstyle": 5
                        }
                    },
                    "varname": "Phase"
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.94902, 0.376471, 0.0, 0.0 ],
                    "activeslidercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "activetricolor2": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "annotation": "Smooths value changes (and jitter, as well).",
                    "annotation_name": "Smooth",
                    "appearance": 4,
                    "bordercolor": [ 1.0, 1.0, 1.0, 0.0 ],
                    "focusbordercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "id": "obj-69",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 247.0, 567.0, 51.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 203.0, 98.0, 32.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activebgcolor": {
                            "expression": ""
                        },
                        "activeslidercolor": {
                            "expression": ""
                        },
                        "activetricolor2": {
                            "expression": ""
                        },
                        "bordercolor": {
                            "expression": ""
                        },
                        "focusbordercolor": {
                            "expression": ""
                        },
                        "textcolor": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "Smooth",
                            "parameter_mmax": 100.0,
                            "parameter_modmode": 4,
                            "parameter_shortname": "Smooth",
                            "parameter_type": 1,
                            "parameter_unitstyle": 5
                        }
                    },
                    "textcolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "textjustification": 0,
                    "varname": "Smooth"
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-9",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 247.0, 544.0, 46.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 200.0, 83.0, 44.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Smooth",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "bgcolor": [ 0.285714, 0.256629, 0.217237, 0.0 ],
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-138",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 185.0, 544.0, 35.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 155.0, 83.0, 34.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Jitter",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "annotation": "Re-triggers the phase of the LFO.",
                    "automation": "Off",
                    "automationon": "On",
                    "id": "obj-94",
                    "maxclass": "live.text",
                    "mode": 0,
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 194.5, 305.0, 21.0, 21.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 228.0, 148.0, 15.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [ "Off", "On" ],
                            "parameter_longname": "Re-Trigger",
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Re-Trigger",
                            "parameter_type": 2
                        }
                    },
                    "text": "R",
                    "varname": "re-trigger"
                }
            },
            {
                "box": {
                    "annotation": "The base rate of the LFO expressed in note values.",
                    "annotation_name": "Sync Rate",
                    "hidden": 1,
                    "id": "obj-58",
                    "maxclass": "live.dial",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 123.0, 231.0, 31.0, 48.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 9.0, 118.0, 45.0, 48.0 ],
                    "prototypename": "M4L.dial.tiny",
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [ "1/64", "1/48", "1/32", "1/24", "1/16", "1/12", "1/8", "1/6", "3/16", "1/4", "5/16", "1/3", "3/8", "1/2", "3/4", "1", "1.5", "2", "3", "4", "6", "8", "16", "32" ],
                            "parameter_initial": [ 15 ],
                            "parameter_initial_enable": 1,
                            "parameter_linknames": 1,
                            "parameter_longname": "Sync Rate",
                            "parameter_mapping_index": 3,
                            "parameter_mmax": 23,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Rate",
                            "parameter_type": 2,
                            "parameter_unitstyle": 9
                        }
                    },
                    "varname": "Sync Rate"
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.0, 0.0, 0.0, 0.0 ],
                    "annotation": "Shape of the LFO waveform.",
                    "annotation_name": "LFO",
                    "appearance": 1,
                    "bordercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "focusbordercolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "hltcolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "id": "obj-79",
                    "maxclass": "live.menu",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "outlettype": [ "", "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 242.0, 365.0, 54.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 3.0, 98.0, 55.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activebgcolor": {
                            "expression": ""
                        },
                        "bordercolor": {
                            "expression": ""
                        },
                        "focusbordercolor": {
                            "expression": ""
                        },
                        "hltcolor": {
                            "expression": ""
                        },
                        "textcolor": {
                            "expression": ""
                        },
                        "tricolor": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_enum": [ "Sine", "Up", "Down", "Triangle", "Square", "Random", "Bin", "Stray", "Glider" ],
                            "parameter_linknames": 1,
                            "parameter_longname": "Shape",
                            "parameter_mapping_index": 2,
                            "parameter_mmax": 8,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Shape",
                            "parameter_type": 2
                        }
                    },
                    "textcolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "tricolor": [ 1.0, 0.709804, 0.196078, 1.0 ],
                    "varname": "Shape"
                }
            },
            {
                "box": {
                    "activebgoncolor": [ 1.0, 0.6784313725490196, 0.33725490196078434, 0.5 ],
                    "activetextoncolor": [ 0.094118, 0.117647, 0.137255, 1.0 ],
                    "annotation": "Momentary holds current output value.",
                    "annotation_name": "Hold",
                    "automation": "Off",
                    "automationon": "On",
                    "id": "obj-55",
                    "maxclass": "live.text",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 74.0, 625.0, 40.0, 15.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 198.0, 148.0, 29.0, 15.0 ],
                    "saved_attribute_attributes": {
                        "activebgoncolor": {
                            "expression": ""
                        },
                        "activetextoncolor": {
                            "expression": ""
                        },
                        "valueof": {
                            "parameter_enum": [ "Off", "On" ],
                            "parameter_linknames": 1,
                            "parameter_longname": "Hold",
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Hold",
                            "parameter_type": 2
                        }
                    },
                    "text": "Hold",
                    "texton": "Hold",
                    "varname": "Hold"
                }
            },
            {
                "box": {
                    "annotation": "Depth of the LFO modulation.",
                    "annotation_name": "Depth",
                    "id": "obj-99",
                    "maxclass": "live.dial",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 92.0, 688.0, 27.0, 48.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 98.0, 118.0, 43.0, 48.0 ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_initial": [ 100 ],
                            "parameter_initial_enable": 1,
                            "parameter_longname": "Depth",
                            "parameter_mapping_index": 5,
                            "parameter_mmax": 100.0,
                            "parameter_modmode": 2,
                            "parameter_shortname": "Depth",
                            "parameter_type": 0,
                            "parameter_unitstyle": 5
                        }
                    },
                    "varname": "Depth"
                }
            },
            {
                "box": {
                    "annotation": "The base rate of the LFO expressed in Hz.",
                    "annotation_name": "Frequency Rate",
                    "id": "obj-89",
                    "maxclass": "live.dial",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "float" ],
                    "parameter_enable": 1,
                    "patching_rect": [ 52.0, 231.0, 28.0, 48.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 9.0, 118.0, 45.0, 48.0 ],
                    "prototypename": "freq",
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_exponent": 2.666666,
                            "parameter_initial": [ 1 ],
                            "parameter_initial_enable": 1,
                            "parameter_longname": "Freq Rate",
                            "parameter_mapping_index": 4,
                            "parameter_mmax": 40.0,
                            "parameter_modmode": 2,
                            "parameter_shortname": "Rate",
                            "parameter_type": 0,
                            "parameter_unitstyle": 3
                        }
                    },
                    "varname": "FreqRate"
                }
            },
            {
                "box": {
                    "id": "obj-19",
                    "maxclass": "live.comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 246.75, 288.0, 34.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 198.0, 118.0, 45.0, 18.0 ],
                    "text": "Phase",
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "angle": 270.0,
                    "bgcolor": [ 0.09411764705882353, 0.09411764705882353, 0.09411764705882353, 1.0 ],
                    "id": "obj-20",
                    "maxclass": "panel",
                    "mode": 0,
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 287.0, 1111.0, 32.0, 26.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 2.0, 4.0, 249.0, 111.0 ],
                    "proportion": 0.5,
                    "rounded": 4,
                    "saved_attribute_attributes": {
                        "bgfillcolor": {
                            "expression": "themecolor.live_lcd_bg"
                        }
                    }
                }
            },
            {
                "box": {
                    "id": "obj-44",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "int", "bang" ],
                    "patching_rect": [ 533.0, 1171.0, 29.5, 22.0 ],
                    "text": "t i b"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleusescolors": 1,
                    "id": "obj-16",
                    "linecount": 2,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 512.0, 1336.0, 202.0, 37.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "Prevent the size from updating before we have the correct width."
                }
            },
            {
                "box": {
                    "id": "obj-46",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "int" ],
                    "patching_rect": [ 627.0, 1245.0, 29.5, 22.0 ],
                    "text": "t l 1"
                }
            },
            {
                "box": {
                    "id": "obj-45",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 471.0, 1343.0, 32.0, 22.0 ],
                    "text": "gate"
                }
            },
            {
                "box": {
                    "id": "obj-22",
                    "maxclass": "newobj",
                    "numinlets": 4,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 484.0, 1289.0, 68.0, 22.0 ],
                    "text": "pak 0 0 0 0"
                }
            },
            {
                "box": {
                    "id": "obj-23",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "patching_rect": [ 659.0, 1073.0, 47.0, 22.0 ],
                    "text": "zl nth 3"
                }
            },
            {
                "box": {
                    "id": "obj-39",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 627.0, 987.0, 172.0, 22.0 ],
                    "text": "loadmess getPresentationRect"
                }
            },
            {
                "box": {
                    "id": "obj-40",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 627.0, 1026.0, 97.0, 22.0 ],
                    "saved_object_attributes": {
                        "filename": "getObjectRect",
                        "parameter_enable": 0
                    },
                    "text": "js getObjectRect"
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleside": 0,
                    "bubbleusescolors": 1,
                    "id": "obj-38",
                    "linecount": 3,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 98.0, 1677.0, 172.0, 66.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "We wrap the abstractions in [poly~]s to be able to mute them when they are not used."
                }
            },
            {
                "box": {
                    "id": "obj-27",
                    "linecolor": [ 0.24313725490196078, 0.24313725490196078, 0.24313725490196078, 1.0 ],
                    "maxclass": "live.line",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 608.0, 1501.0, 12.0, 9.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 209.0, 153.0, 12.0, 9.0 ],
                    "saved_attribute_attributes": {
                        "linecolor": {
                            "expression": "themecolor.live_lcd_frame"
                        }
                    }
                }
            },
            {
                "box": {
                    "id": "obj-33",
                    "linecolor": [ 0.24313725490196078, 0.24313725490196078, 0.24313725490196078, 1.0 ],
                    "maxclass": "live.line",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 588.0, 1501.0, 12.0, 9.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 157.0, 153.0, 12.0, 9.0 ],
                    "saved_attribute_attributes": {
                        "linecolor": {
                            "expression": "themecolor.live_lcd_frame"
                        }
                    }
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-34",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 588.0, 1518.0, 35.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 169.0, 144.0, 40.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Range",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-41",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 547.0, 1518.0, 32.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 90.0, 144.0, 44.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Mode",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "bubble": 1,
                    "bubbleside": 0,
                    "bubbleusescolors": 1,
                    "id": "obj-42",
                    "linecount": 3,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 797.0, 1187.0, 189.0, 66.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_control_fg"
                        }
                    },
                    "text": "Scale the background and place the multimap button depending on the width of the bpatcher."
                }
            },
            {
                "box": {
                    "bgmode": 0,
                    "border": 0,
                    "clickthrough": 0,
                    "enablehscroll": 0,
                    "enablevscroll": 0,
                    "id": "obj-48",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1596.0, 170.0, 21.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 112.0, 249.0, 22.0 ],
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
                    "id": "obj-50",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1505.0, 170.0, 21.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 96.0, 249.0, 22.0 ],
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
                    "id": "obj-51",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1413.0, 170.0, 21.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 80.0, 249.0, 22.0 ],
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
                    "id": "obj-52",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1321.0, 170.0, 21.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 64.0, 249.0, 22.0 ],
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
                    "id": "obj-53",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1230.0, 170.0, 21.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 48.0, 249.0, 22.0 ],
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
                    "id": "obj-60",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1138.0, 170.0, 20.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 32.0, 249.0, 22.0 ],
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
                    "id": "obj-62",
                    "lockeddragscroll": 0,
                    "lockedsize": 0,
                    "maxclass": "bpatcher",
                    "name": "Abl.MapUi.maxpat",
                    "numinlets": 3,
                    "numoutlets": 7,
                    "offset": [ 0.0, 0.0 ],
                    "outlettype": [ "", "", "", "", "", "", "" ],
                    "patching_rect": [ 123.0, 1042.0, 170.0, 22.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 16.0, 249.0, 22.0 ],
                    "viewvisibility": 1
                }
            },
            {
                "box": {
                    "id": "obj-63",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 697.0, 1109.0, 296.0, 22.0 ],
                    "text": "script sendbox displaybg presentation_rect 0 0 $1 163"
                }
            },
            {
                "box": {
                    "id": "obj-64",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "patching_rect": [ 659.0, 1187.0, 67.0, 22.0 ],
                    "save": [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
                    "text": "thispatcher"
                }
            },
            {
                "box": {
                    "id": "obj-65",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "int" ],
                    "patching_rect": [ 659.0, 1109.0, 30.0, 22.0 ],
                    "text": "- 18"
                }
            },
            {
                "box": {
                    "id": "obj-67",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 659.0, 1148.0, 327.0, 22.0 ],
                    "text": "script sendbox multimapbutton presentation_rect $1 3 15 15"
                }
            },
            {
                "box": {
                    "id": "obj-70",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "int" ],
                    "patching_rect": [ 565.0, 1245.0, 35.0, 22.0 ],
                    "text": "t 165"
                }
            },
            {
                "box": {
                    "id": "obj-71",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "int" ],
                    "patching_rect": [ 533.0, 1245.0, 29.0, 22.0 ],
                    "text": "t 18"
                }
            },
            {
                "box": {
                    "id": "obj-72",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 471.0, 1382.0, 301.0, 22.0 ],
                    "text": "script sendbox multimap presentation_rect $1 $2 $3 $4"
                }
            },
            {
                "box": {
                    "id": "obj-73",
                    "maxclass": "newobj",
                    "numinlets": 3,
                    "numoutlets": 3,
                    "outlettype": [ "bang", "bang", "" ],
                    "patching_rect": [ 533.0, 1207.0, 83.0, 22.0 ],
                    "text": "sel 0 1"
                }
            },
            {
                "box": {
                    "id": "obj-74",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [ "int" ],
                    "patching_rect": [ 537.0, 1065.0, 30.0, 22.0 ],
                    "text": "> 0"
                }
            },
            {
                "box": {
                    "color": [ 1.0, 0.694117647058824, 0.0, 1.0 ],
                    "id": "obj-75",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
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
                        "rect": [ 130.0, 162.0, 943.0, 586.0 ],
                        "boxes": [
                            {
                                "box": {
                                    "id": "obj-6",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 80.0, 70.0, 70.0, 22.0 ],
                                    "text": "loadmess 0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 690.0, 421.0, 19.0, 22.0 ],
                                    "text": "t l"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-11",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 702.0, 219.0, 163.0, 22.0 ],
                                    "text": "bordercolor \"LCD Text / Icon\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-12",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "bang", "" ],
                                    "patching_rect": [ 690.0, 162.0, 44.0, 22.0 ],
                                    "text": "sel 0 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-13",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 690.0, 195.0, 216.0, 22.0 ],
                                    "text": "bordercolor \"LCD Text / Icon (Inactive)\""
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleside": 2,
                                    "bubbleusescolors": 1,
                                    "fontsize": 11.0,
                                    "id": "obj-9",
                                    "linecount": 3,
                                    "maxclass": "live.comment",
                                    "numinlets": 0,
                                    "numoutlets": 0,
                                    "patching_rect": [ 744.0, 127.0, 147.0, 65.0 ],
                                    "suppressinlet": 1,
                                    "text": "Border color does not have an (Inactive) mode, so we need to do that ourselves.",
                                    "textjustification": 0
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleside": 2,
                                    "bubbleusescolors": 1,
                                    "fontsize": 11.0,
                                    "id": "obj-4",
                                    "linecount": 2,
                                    "maxclass": "live.comment",
                                    "numinlets": 0,
                                    "numoutlets": 0,
                                    "patching_rect": [ 447.0, 133.0, 118.0, 52.0 ],
                                    "suppressinlet": 1,
                                    "text": "Colors when multiple mappings are active.",
                                    "textjustification": 0
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleside": 2,
                                    "bubbleusescolors": 1,
                                    "fontsize": 11.0,
                                    "id": "obj-16",
                                    "linecount": 2,
                                    "maxclass": "live.comment",
                                    "numinlets": 0,
                                    "numoutlets": 0,
                                    "patching_rect": [ 80.0, 133.0, 130.0, 52.0 ],
                                    "suppressinlet": 1,
                                    "text": "Colors when zero or one mappings are active.",
                                    "textjustification": 0
                                }
                            },
                            {
                                "box": {
                                    "comment": "(symbol symbol) attribute, color name",
                                    "id": "obj-75",
                                    "index": 1,
                                    "maxclass": "outlet",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [ 27.0, 519.0, 30.0, 30.0 ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-74",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 370.0, 170.0, 22.0 ],
                                    "text": "textoffcolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-73",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 370.0, 213.0, 22.0 ],
                                    "text": "textoffcolor \"LCD Text / Icon (Inactive)\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-61",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 391.0, 421.0, 19.0, 22.0 ],
                                    "text": "t l"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-62",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 318.0, 194.0, 22.0 ],
                                    "text": "bgcolor \"LCD Text / Icon (Inactive)\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-63",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 292.0, 208.0, 22.0 ],
                                    "text": "bgoncolor \"LCD Text / Icon (Inactive)\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-64",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 344.0, 157.0, 22.0 ],
                                    "text": "textcolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-65",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 266.0, 202.0, 22.0 ],
                                    "text": "activetextoncolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-66",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 240.0, 188.0, 22.0 ],
                                    "text": "activetextcolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-67",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 215.0, 186.0, 22.0 ],
                                    "text": "activebgoncolor \"LCD Text / Icon\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-68",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "bang" ],
                                    "patching_rect": [ 389.0, 162.0, 22.0, 22.0 ],
                                    "text": "t b"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-70",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 419.0, 189.0, 173.0, 22.0 ],
                                    "text": "activebgcolor \"LCD Text / Icon\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-59",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 27.0, 421.0, 19.0, 22.0 ],
                                    "text": "t l"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-55",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 318.0, 151.0, 22.0 ],
                                    "text": "bgcolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-53",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 292.0, 164.0, 22.0 ],
                                    "text": "bgoncolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-51",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 344.0, 200.0, 22.0 ],
                                    "text": "textcolor \"LCD Text / Icon (Inactive)\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-50",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 266.0, 192.0, 22.0 ],
                                    "text": "activetextoncolor \"LCD Text / Icon\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-49",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 240.0, 179.0, 22.0 ],
                                    "text": "activetextcolor \"LCD Text / Icon\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-46",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 215.0, 196.0, 22.0 ],
                                    "text": "activebgoncolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-39",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [ "bang" ],
                                    "patching_rect": [ 27.0, 162.0, 22.0, 22.0 ],
                                    "text": "t b"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-38",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [ "" ],
                                    "patching_rect": [ 57.0, 189.0, 182.0, 22.0 ],
                                    "text": "activebgcolor \"LCD Background\""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-89",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "bang", "" ],
                                    "patching_rect": [ 27.0, 70.0, 44.0, 22.0 ],
                                    "text": "sel 0 1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-77",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": [ "bang", "int", "int" ],
                                    "patching_rect": [ 658.0, 70.0, 83.0, 22.0 ],
                                    "text": "live.thisdevice"
                                }
                            },
                            {
                                "box": {
                                    "comment": "(bool) something is mapped",
                                    "id": "obj-1",
                                    "index": 1,
                                    "maxclass": "inlet",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [ "int" ],
                                    "patching_rect": [ 27.0, 23.0, 30.0, 30.0 ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": [ "obj-89", 0 ],
                                    "source": [ "obj-1", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-75", 0 ],
                                    "source": [ "obj-10", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-10", 0 ],
                                    "source": [ "obj-11", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-11", 0 ],
                                    "source": [ "obj-12", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-13", 0 ],
                                    "source": [ "obj-12", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-10", 0 ],
                                    "source": [ "obj-13", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-38", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-38", 0 ],
                                    "order": 7,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-46", 0 ],
                                    "order": 6,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-49", 0 ],
                                    "order": 5,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-50", 0 ],
                                    "order": 4,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-51", 0 ],
                                    "order": 1,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-53", 0 ],
                                    "order": 3,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-55", 0 ],
                                    "order": 2,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-73", 0 ],
                                    "order": 0,
                                    "source": [ "obj-39", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-46", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-49", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-50", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-51", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-53", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-55", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-75", 0 ],
                                    "source": [ "obj-59", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-89", 0 ],
                                    "source": [ "obj-6", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-75", 0 ],
                                    "source": [ "obj-61", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-62", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-63", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-64", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-65", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-66", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-67", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-62", 0 ],
                                    "order": 2,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-63", 0 ],
                                    "order": 3,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-64", 0 ],
                                    "order": 1,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-65", 0 ],
                                    "order": 4,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-66", 0 ],
                                    "order": 5,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-67", 0 ],
                                    "order": 6,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-70", 0 ],
                                    "order": 7,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-74", 0 ],
                                    "order": 0,
                                    "source": [ "obj-68", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-70", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-59", 0 ],
                                    "source": [ "obj-73", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-61", 0 ],
                                    "source": [ "obj-74", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-12", 0 ],
                                    "source": [ "obj-77", 1 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-39", 0 ],
                                    "source": [ "obj-89", 0 ]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": [ "obj-68", 0 ],
                                    "source": [ "obj-89", 1 ]
                                }
                            }
                        ]
                    },
                    "patching_rect": [ 537.0, 1104.0, 82.0, 22.0 ],
                    "text": "p ButtonColor"
                }
            },
            {
                "box": {
                    "activebgcolor": [ 0.09411764705882353, 0.09411764705882353, 0.09411764705882353, 1.0 ],
                    "activebgoncolor": [ 0.09411764705882353, 0.09411764705882353, 0.09411764705882353, 1.0 ],
                    "activetextcolor": [ 1.0, 0.6784313725490196, 0.33725490196078434, 1.0 ],
                    "activetextoncolor": [ 1.0, 0.6784313725490196, 0.33725490196078434, 1.0 ],
                    "annotation": "Shows or hides the device's Multimap browser.",
                    "annotation_name": "Show/Hide Multimap",
                    "automation": "Hide",
                    "automationon": "Show",
                    "bgcolor": [ 0.09411764705882353, 0.09411764705882353, 0.09411764705882353, 1.0 ],
                    "bgoncolor": [ 0.09411764705882353, 0.09411764705882353, 0.09411764705882353, 1.0 ],
                    "bordercolor": [ 1.0, 0.6784313725490196, 0.33725490196078434, 1.0 ],
                    "id": "obj-76",
                    "maxclass": "live.text",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "outputmode": 1,
                    "parameter_enable": 1,
                    "patching_rect": [ 537.0, 1139.0, 15.0, 15.0 ],
                    "pictures": [ "multimap-closed-off.svg", "multimap-open-off.svg" ],
                    "presentation": 1,
                    "presentation_rect": [ 231.0, 3.0, 15.0, 15.0 ],
                    "remapsvgcolors": 1,
                    "saved_attribute_attributes": {
                        "activebgcolor": {
                            "expression": "themecolor.live_lcd_bg"
                        },
                        "activebgoncolor": {
                            "expression": "themecolor.live_lcd_bg"
                        },
                        "activetextcolor": {
                            "expression": "themecolor.live_lcd_control_fg"
                        },
                        "activetextoncolor": {
                            "expression": "themecolor.live_lcd_control_fg"
                        },
                        "bgcolor": {
                            "expression": "themecolor.live_lcd_bg"
                        },
                        "bgoncolor": {
                            "expression": "themecolor.live_lcd_bg"
                        },
                        "bordercolor": {
                            "expression": "themecolor.live_lcd_control_fg"
                        },
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        },
                        "textoffcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        },
                        "valueof": {
                            "parameter_enum": [ "Hide", "Show" ],
                            "parameter_initial": [ 0 ],
                            "parameter_initial_enable": 1,
                            "parameter_invisible": 2,
                            "parameter_longname": "Show Multimap[3]",
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_shortname": "Multimap",
                            "parameter_type": 2
                        }
                    },
                    "text": "Off",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textoffcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "texton": "On",
                    "usepicture": 1,
                    "usesvgviewbox": 1,
                    "varname": "multimapbutton"
                }
            },
            {
                "box": {
                    "id": "obj-77",
                    "maxclass": "newobj",
                    "numinlets": 2,
                    "numoutlets": 2,
                    "outlettype": [ "", "" ],
                    "patching_rect": [ 537.0, 1026.0, 43.0, 22.0 ],
                    "text": "zl sum"
                }
            },
            {
                "box": {
                    "id": "obj-78",
                    "maxclass": "newobj",
                    "numinlets": 7,
                    "numoutlets": 1,
                    "outlettype": [ "" ],
                    "patching_rect": [ 345.0, 1703.0, 82.0, 22.0 ],
                    "text": "pak i i i i i i i"
                }
            },
            {
                "box": {
                    "fontname": "Ableton Sans Medium",
                    "fontsize": 9.5,
                    "id": "obj-80",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 475.0, 1518.0, 53.0, 18.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 3.0, 144.0, 70.0, 18.0 ],
                    "saved_attribute_attributes": {
                        "textcolor": {
                            "expression": "themecolor.live_lcd_control_fg_zombie"
                        }
                    },
                    "text": "Parameter",
                    "textcolor": [ 0.5254901960784314, 0.5254901960784314, 0.5254901960784314, 1.0 ],
                    "textjustification": 1
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-82",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1631.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-83",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1540.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-84",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1448.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-85",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1356.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-86",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1265.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-87",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1173.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "color": [ 0.0, 1.0, 0.694117647058824, 1.0 ],
                    "id": "obj-90",
                    "maxclass": "newobj",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [ "", "", "", "" ],
                    "patching_rect": [ 98.0, 1081.0, 244.75, 22.0 ],
                    "text": "poly~ Abl.Map"
                }
            },
            {
                "box": {
                    "angle": 270.0,
                    "bgcolor": [ 0.09411764705882353, 0.09411764705882353, 0.09411764705882353, 1.0 ],
                    "border": 1,
                    "bordercolor": [ 1.0, 1.0, 1.0, 0.0 ],
                    "id": "obj-131",
                    "maxclass": "panel",
                    "mode": 0,
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [ 471.0, 1466.0, 235.0, 77.0 ],
                    "presentation": 1,
                    "presentation_rect": [ 0.0, 0.0, 249.0, 163.0 ],
                    "proportion": 0.39,
                    "rounded": 4,
                    "saved_attribute_attributes": {
                        "bgfillcolor": {
                            "expression": "themecolor.live_lcd_bg"
                        }
                    },
                    "varname": "displaybg"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [ "obj-7", 7 ],
                    "source": [ "obj-1", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 6 ],
                    "source": [ "obj-1", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 5 ],
                    "source": [ "obj-1", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 4 ],
                    "source": [ "obj-1", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 3 ],
                    "source": [ "obj-1", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 2 ],
                    "source": [ "obj-1", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 1 ],
                    "source": [ "obj-1", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-43", 1 ],
                    "source": [ "obj-10", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-31", 0 ],
                    "source": [ "obj-12", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-58", 0 ],
                    "source": [ "obj-12", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-89", 0 ],
                    "source": [ "obj-12", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-29", 0 ],
                    "disabled": 1,
                    "source": [ "obj-120", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-47", 2 ],
                    "source": [ "obj-120", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-68", 2 ],
                    "source": [ "obj-13", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-3", 3 ],
                    "source": [ "obj-140", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-2", 1 ],
                    "source": [ "obj-15", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-2", 0 ],
                    "source": [ "obj-15", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-68", 0 ],
                    "source": [ "obj-17", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 8 ],
                    "order": 0,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 8 ],
                    "order": 1,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 8 ],
                    "order": 2,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 8 ],
                    "order": 3,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 8 ],
                    "order": 4,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 8 ],
                    "order": 5,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 8 ],
                    "order": 6,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 8 ],
                    "order": 7,
                    "source": [ "obj-18", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-11", 0 ],
                    "source": [ "obj-21", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-45", 1 ],
                    "source": [ "obj-22", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-63", 0 ],
                    "order": 0,
                    "source": [ "obj-23", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-65", 0 ],
                    "order": 1,
                    "source": [ "obj-23", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-3", 4 ],
                    "order": 1,
                    "source": [ "obj-26", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-4", 0 ],
                    "order": 0,
                    "source": [ "obj-26", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-5", 0 ],
                    "order": 2,
                    "source": [ "obj-26", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-13", 0 ],
                    "source": [ "obj-28", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-68", 1 ],
                    "source": [ "obj-28", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-30", 0 ],
                    "source": [ "obj-29", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-17", 3 ],
                    "source": [ "obj-3", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-17", 0 ],
                    "source": [ "obj-3", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-32", 1 ],
                    "source": [ "obj-31", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-3", 0 ],
                    "source": [ "obj-32", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-40", 0 ],
                    "source": [ "obj-39", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-23", 0 ],
                    "order": 0,
                    "source": [ "obj-40", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-46", 0 ],
                    "order": 1,
                    "source": [ "obj-40", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-56", 0 ],
                    "source": [ "obj-43", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-39", 0 ],
                    "source": [ "obj-44", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-73", 0 ],
                    "source": [ "obj-44", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-72", 0 ],
                    "source": [ "obj-45", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-22", 0 ],
                    "source": [ "obj-46", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-45", 0 ],
                    "midpoints": [ 647.0, 1323.5, 480.5, 1323.5 ],
                    "source": [ "obj-46", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-8", 0 ],
                    "source": [ "obj-47", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 7 ],
                    "source": [ "obj-48", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 6 ],
                    "source": [ "obj-48", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 5 ],
                    "source": [ "obj-48", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 4 ],
                    "source": [ "obj-48", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 3 ],
                    "source": [ "obj-48", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 2 ],
                    "source": [ "obj-48", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 1 ],
                    "source": [ "obj-48", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-12", 0 ],
                    "source": [ "obj-5", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-3", 2 ],
                    "source": [ "obj-5", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 7 ],
                    "source": [ "obj-50", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 6 ],
                    "source": [ "obj-50", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 5 ],
                    "source": [ "obj-50", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 4 ],
                    "source": [ "obj-50", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 3 ],
                    "source": [ "obj-50", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 2 ],
                    "source": [ "obj-50", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 1 ],
                    "source": [ "obj-50", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 7 ],
                    "source": [ "obj-51", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 6 ],
                    "source": [ "obj-51", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 5 ],
                    "source": [ "obj-51", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 4 ],
                    "source": [ "obj-51", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 3 ],
                    "source": [ "obj-51", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 2 ],
                    "source": [ "obj-51", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 1 ],
                    "source": [ "obj-51", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 7 ],
                    "source": [ "obj-52", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 6 ],
                    "source": [ "obj-52", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 5 ],
                    "source": [ "obj-52", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 4 ],
                    "source": [ "obj-52", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 3 ],
                    "source": [ "obj-52", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 2 ],
                    "source": [ "obj-52", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 1 ],
                    "source": [ "obj-52", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 7 ],
                    "source": [ "obj-53", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 6 ],
                    "source": [ "obj-53", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 5 ],
                    "source": [ "obj-53", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 4 ],
                    "source": [ "obj-53", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 3 ],
                    "source": [ "obj-53", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 2 ],
                    "source": [ "obj-53", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 1 ],
                    "source": [ "obj-53", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-17", 1 ],
                    "source": [ "obj-54", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-56", 1 ],
                    "order": 1,
                    "source": [ "obj-55", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-66", 0 ],
                    "order": 0,
                    "source": [ "obj-55", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-47", 0 ],
                    "source": [ "obj-56", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-3", 1 ],
                    "source": [ "obj-58", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-17", 1 ],
                    "source": [ "obj-59", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-54", 0 ],
                    "source": [ "obj-59", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 9 ],
                    "order": 0,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 9 ],
                    "order": 1,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 9 ],
                    "order": 2,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 9 ],
                    "order": 3,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 9 ],
                    "order": 4,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 9 ],
                    "order": 5,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 9 ],
                    "order": 6,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 9 ],
                    "order": 7,
                    "source": [ "obj-6", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 7 ],
                    "source": [ "obj-60", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 6 ],
                    "source": [ "obj-60", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 5 ],
                    "source": [ "obj-60", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 4 ],
                    "source": [ "obj-60", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 3 ],
                    "source": [ "obj-60", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 2 ],
                    "source": [ "obj-60", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 1 ],
                    "source": [ "obj-60", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 7 ],
                    "source": [ "obj-62", 6 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 6 ],
                    "source": [ "obj-62", 5 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 5 ],
                    "source": [ "obj-62", 4 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 4 ],
                    "source": [ "obj-62", 3 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 3 ],
                    "source": [ "obj-62", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 2 ],
                    "source": [ "obj-62", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 1 ],
                    "source": [ "obj-62", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-64", 0 ],
                    "source": [ "obj-63", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-67", 0 ],
                    "source": [ "obj-65", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-55", 0 ],
                    "source": [ "obj-66", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-64", 0 ],
                    "source": [ "obj-67", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-43", 0 ],
                    "source": [ "obj-68", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-43", 2 ],
                    "source": [ "obj-69", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-1", 2 ],
                    "source": [ "obj-7", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-1", 1 ],
                    "source": [ "obj-7", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-1", 0 ],
                    "source": [ "obj-7", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-22", 3 ],
                    "source": [ "obj-70", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-22", 3 ],
                    "source": [ "obj-71", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-24", 0 ],
                    "source": [ "obj-72", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-70", 0 ],
                    "source": [ "obj-73", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-71", 0 ],
                    "source": [ "obj-73", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-75", 0 ],
                    "source": [ "obj-74", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-76", 0 ],
                    "source": [ "obj-75", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-44", 0 ],
                    "source": [ "obj-76", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-74", 0 ],
                    "source": [ "obj-77", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-77", 0 ],
                    "source": [ "obj-78", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-17", 2 ],
                    "order": 0,
                    "source": [ "obj-79", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-28", 0 ],
                    "order": 2,
                    "source": [ "obj-79", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-59", 0 ],
                    "order": 1,
                    "source": [ "obj-79", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-11", 0 ],
                    "order": 0,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-7", 0 ],
                    "order": 8,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-82", 0 ],
                    "order": 1,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-83", 0 ],
                    "order": 2,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-84", 0 ],
                    "order": 3,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-85", 0 ],
                    "order": 4,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-86", 0 ],
                    "order": 5,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-87", 0 ],
                    "order": 6,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-90", 0 ],
                    "order": 7,
                    "source": [ "obj-8", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-48", 2 ],
                    "order": 1,
                    "source": [ "obj-82", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-48", 1 ],
                    "source": [ "obj-82", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-48", 0 ],
                    "source": [ "obj-82", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 0 ],
                    "order": 0,
                    "source": [ "obj-82", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-50", 2 ],
                    "order": 1,
                    "source": [ "obj-83", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-50", 1 ],
                    "source": [ "obj-83", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-50", 0 ],
                    "source": [ "obj-83", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 1 ],
                    "order": 0,
                    "source": [ "obj-83", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-51", 2 ],
                    "order": 1,
                    "source": [ "obj-84", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-51", 1 ],
                    "source": [ "obj-84", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-51", 0 ],
                    "source": [ "obj-84", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 2 ],
                    "order": 0,
                    "source": [ "obj-84", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-52", 2 ],
                    "order": 1,
                    "source": [ "obj-85", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-52", 1 ],
                    "source": [ "obj-85", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-52", 0 ],
                    "source": [ "obj-85", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 3 ],
                    "order": 0,
                    "source": [ "obj-85", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-53", 2 ],
                    "order": 1,
                    "source": [ "obj-86", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-53", 1 ],
                    "source": [ "obj-86", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-53", 0 ],
                    "source": [ "obj-86", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 4 ],
                    "order": 0,
                    "source": [ "obj-86", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-60", 2 ],
                    "order": 1,
                    "source": [ "obj-87", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-60", 1 ],
                    "source": [ "obj-87", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-60", 0 ],
                    "source": [ "obj-87", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 5 ],
                    "order": 0,
                    "source": [ "obj-87", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-32", 0 ],
                    "source": [ "obj-89", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-62", 2 ],
                    "order": 1,
                    "source": [ "obj-90", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-62", 1 ],
                    "source": [ "obj-90", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-62", 0 ],
                    "source": [ "obj-90", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-78", 6 ],
                    "order": 0,
                    "source": [ "obj-90", 2 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-3", 2 ],
                    "source": [ "obj-94", 0 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-18", 0 ],
                    "order": 0,
                    "source": [ "obj-99", 1 ]
                }
            },
            {
                "patchline": {
                    "destination": [ "obj-47", 1 ],
                    "order": 1,
                    "source": [ "obj-99", 1 ]
                }
            }
        ],
        "parameters": {
            "obj-10": [ "Jitter", "Jitter", 0 ],
            "obj-120": [ "Offset", "Offset", 0 ],
            "obj-13": [ "Steps", "Steps", 0 ],
            "obj-140": [ "Phase", "Phase", 0 ],
            "obj-1::obj-103": [ "border[25]", "border", 0 ],
            "obj-1::obj-2": [ "mode[13]", "Modulation", 0 ],
            "obj-1::obj-25": [ "Map[5]", "Map", 0 ],
            "obj-1::obj-26": [ "border[26]", "border", 0 ],
            "obj-1::obj-30": [ "Unmap[4]", "Unmap", 0 ],
            "obj-1::obj-32": [ "TargetMax[13]", "Max", 0 ],
            "obj-1::obj-33": [ "TargetMin[13]", "Min", 0 ],
            "obj-1::obj-6": [ "Modulation Polarity 1[7]", "Polarity", 0 ],
            "obj-1::obj-9": [ "Modulation Amount 1[7]", "ModAmount", 0 ],
            "obj-26": [ "Time Mode", "Time Mode", 0 ],
            "obj-31": [ "x10", "x10", 0 ],
            "obj-48::obj-103": [ "border[24]", "border", 0 ],
            "obj-48::obj-2": [ "mode[5]", "Modulation", 0 ],
            "obj-48::obj-25": [ "Map[4]", "Map", 0 ],
            "obj-48::obj-26": [ "border[23]", "border", 0 ],
            "obj-48::obj-30": [ "Unmap[20]", "Unmap", 0 ],
            "obj-48::obj-32": [ "TargetMax[12]", "Max", 0 ],
            "obj-48::obj-33": [ "TargetMin[12]", "Min", 0 ],
            "obj-48::obj-6": [ "Modulation Polarity 1[6]", "Polarity", 0 ],
            "obj-48::obj-9": [ "Modulation Amount 1[6]", "ModAmount", 0 ],
            "obj-50::obj-103": [ "border[21]", "border", 0 ],
            "obj-50::obj-2": [ "mode[4]", "Modulation", 0 ],
            "obj-50::obj-25": [ "Map[18]", "Map", 0 ],
            "obj-50::obj-26": [ "border[22]", "border", 0 ],
            "obj-50::obj-30": [ "Unmap[19]", "Unmap", 0 ],
            "obj-50::obj-32": [ "TargetMax[11]", "Max", 0 ],
            "obj-50::obj-33": [ "TargetMin[11]", "Min", 0 ],
            "obj-50::obj-6": [ "Modulation Polarity 1[5]", "Polarity", 0 ],
            "obj-50::obj-9": [ "Modulation Amount 1[5]", "ModAmount", 0 ],
            "obj-51::obj-103": [ "border[4]", "border", 0 ],
            "obj-51::obj-2": [ "mode[3]", "Modulation", 0 ],
            "obj-51::obj-25": [ "Map[3]", "Map", 0 ],
            "obj-51::obj-26": [ "border[5]", "border", 0 ],
            "obj-51::obj-30": [ "Unmap[3]", "Unmap", 0 ],
            "obj-51::obj-32": [ "TargetMax[10]", "Max", 0 ],
            "obj-51::obj-33": [ "TargetMin[10]", "Min", 0 ],
            "obj-51::obj-6": [ "Modulation Polarity 1[4]", "Polarity", 0 ],
            "obj-51::obj-9": [ "Modulation Amount 1[4]", "ModAmount", 0 ],
            "obj-52::obj-103": [ "border[2]", "border", 0 ],
            "obj-52::obj-2": [ "mode[12]", "Modulation", 0 ],
            "obj-52::obj-25": [ "Map[2]", "Map", 0 ],
            "obj-52::obj-26": [ "border[3]", "border", 0 ],
            "obj-52::obj-30": [ "Unmap[2]", "Unmap", 0 ],
            "obj-52::obj-32": [ "TargetMax[9]", "Max", 0 ],
            "obj-52::obj-33": [ "TargetMin[9]", "Min", 0 ],
            "obj-52::obj-6": [ "Modulation Polarity 1[3]", "Polarity", 0 ],
            "obj-52::obj-9": [ "Modulation Amount 1[3]", "ModAmount", 0 ],
            "obj-53::obj-103": [ "border[20]", "border", 0 ],
            "obj-53::obj-2": [ "mode[2]", "Modulation", 0 ],
            "obj-53::obj-25": [ "Map[1]", "Map", 0 ],
            "obj-53::obj-26": [ "border[19]", "border", 0 ],
            "obj-53::obj-30": [ "Unmap[1]", "Unmap", 0 ],
            "obj-53::obj-32": [ "TargetMax[1]", "Max", 0 ],
            "obj-53::obj-33": [ "TargetMin[1]", "Min", 0 ],
            "obj-53::obj-6": [ "Modulation Polarity 1[2]", "Polarity", 0 ],
            "obj-53::obj-9": [ "Modulation Amount 1[2]", "ModAmount", 0 ],
            "obj-54": [ "WaveShape", "WaveShape", 0 ],
            "obj-55": [ "Hold", "Hold", 0 ],
            "obj-58": [ "Sync Rate", "Rate", 0 ],
            "obj-60::obj-103": [ "border[18]", "border", 0 ],
            "obj-60::obj-2": [ "mode[1]", "Modulation", 0 ],
            "obj-60::obj-25": [ "Map[17]", "Map", 0 ],
            "obj-60::obj-26": [ "border[1]", "border", 0 ],
            "obj-60::obj-30": [ "Unmap[18]", "Unmap", 0 ],
            "obj-60::obj-32": [ "TargetMax[8]", "Max", 0 ],
            "obj-60::obj-33": [ "TargetMin[8]", "Min", 0 ],
            "obj-60::obj-6": [ "Modulation Polarity 1[1]", "Polarity", 0 ],
            "obj-60::obj-9": [ "Modulation Amount 1[1]", "ModAmount", 0 ],
            "obj-62::obj-103": [ "border[17]", "border", 0 ],
            "obj-62::obj-2": [ "mode[11]", "Modulation", 0 ],
            "obj-62::obj-25": [ "Map[16]", "Map", 0 ],
            "obj-62::obj-26": [ "border[10]", "border", 0 ],
            "obj-62::obj-30": [ "Unmap[17]", "Unmap", 0 ],
            "obj-62::obj-32": [ "TargetMax[7]", "Max", 0 ],
            "obj-62::obj-33": [ "TargetMin[7]", "Min", 0 ],
            "obj-62::obj-6": [ "Modulation Polarity 1", "Polarity", 0 ],
            "obj-62::obj-9": [ "Modulation Amount 1", "ModAmount", 0 ],
            "obj-69": [ "Smooth", "Smooth", 0 ],
            "obj-76": [ "Show Multimap[3]", "Multimap", 0 ],
            "obj-79": [ "Shape", "Shape", 0 ],
            "obj-89": [ "Freq Rate", "Rate", 0 ],
            "obj-94": [ "Re-Trigger", "Re-Trigger", 0 ],
            "obj-99": [ "Depth", "Depth", 0 ],
            "parameterbanks": {
                "0": {
                    "index": 0,
                    "name": "",
                    "parameters": [ "-", "Shape", "Sync Rate", "Freq Rate", "Depth", "-", "-", "-" ],
                    "buttons": [ "-", "-", "-", "-", "-", "-", "-", "-" ]
                }
            },
            "parameter_overrides": {
                "obj-1::obj-103": {
                    "parameter_longname": "border[25]"
                },
                "obj-1::obj-2": {
                    "parameter_longname": "mode[13]"
                },
                "obj-1::obj-25": {
                    "parameter_longname": "Map[5]"
                },
                "obj-1::obj-26": {
                    "parameter_longname": "border[26]"
                },
                "obj-1::obj-30": {
                    "parameter_longname": "Unmap[4]"
                },
                "obj-1::obj-32": {
                    "parameter_longname": "TargetMax[13]"
                },
                "obj-1::obj-33": {
                    "parameter_longname": "TargetMin[13]"
                },
                "obj-1::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[7]"
                },
                "obj-1::obj-9": {
                    "parameter_longname": "Modulation Amount 1[7]"
                },
                "obj-48::obj-103": {
                    "parameter_longname": "border[24]"
                },
                "obj-48::obj-2": {
                    "parameter_longname": "mode[5]"
                },
                "obj-48::obj-25": {
                    "parameter_longname": "Map[4]"
                },
                "obj-48::obj-26": {
                    "parameter_longname": "border[23]"
                },
                "obj-48::obj-30": {
                    "parameter_longname": "Unmap[20]"
                },
                "obj-48::obj-32": {
                    "parameter_longname": "TargetMax[12]"
                },
                "obj-48::obj-33": {
                    "parameter_longname": "TargetMin[12]"
                },
                "obj-48::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[6]"
                },
                "obj-48::obj-9": {
                    "parameter_longname": "Modulation Amount 1[6]"
                },
                "obj-50::obj-103": {
                    "parameter_longname": "border[21]"
                },
                "obj-50::obj-2": {
                    "parameter_longname": "mode[4]"
                },
                "obj-50::obj-25": {
                    "parameter_longname": "Map[18]"
                },
                "obj-50::obj-26": {
                    "parameter_longname": "border[22]"
                },
                "obj-50::obj-30": {
                    "parameter_longname": "Unmap[19]"
                },
                "obj-50::obj-32": {
                    "parameter_longname": "TargetMax[11]"
                },
                "obj-50::obj-33": {
                    "parameter_longname": "TargetMin[11]"
                },
                "obj-50::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[5]"
                },
                "obj-50::obj-9": {
                    "parameter_longname": "Modulation Amount 1[5]"
                },
                "obj-51::obj-103": {
                    "parameter_longname": "border[4]"
                },
                "obj-51::obj-2": {
                    "parameter_longname": "mode[3]"
                },
                "obj-51::obj-25": {
                    "parameter_longname": "Map[3]"
                },
                "obj-51::obj-26": {
                    "parameter_longname": "border[5]"
                },
                "obj-51::obj-30": {
                    "parameter_longname": "Unmap[3]"
                },
                "obj-51::obj-32": {
                    "parameter_longname": "TargetMax[10]"
                },
                "obj-51::obj-33": {
                    "parameter_longname": "TargetMin[10]"
                },
                "obj-51::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[4]"
                },
                "obj-51::obj-9": {
                    "parameter_longname": "Modulation Amount 1[4]"
                },
                "obj-52::obj-103": {
                    "parameter_longname": "border[2]"
                },
                "obj-52::obj-2": {
                    "parameter_longname": "mode[12]"
                },
                "obj-52::obj-25": {
                    "parameter_longname": "Map[2]"
                },
                "obj-52::obj-26": {
                    "parameter_longname": "border[3]"
                },
                "obj-52::obj-30": {
                    "parameter_longname": "Unmap[2]"
                },
                "obj-52::obj-32": {
                    "parameter_longname": "TargetMax[9]"
                },
                "obj-52::obj-33": {
                    "parameter_longname": "TargetMin[9]"
                },
                "obj-52::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[3]"
                },
                "obj-52::obj-9": {
                    "parameter_longname": "Modulation Amount 1[3]"
                },
                "obj-53::obj-103": {
                    "parameter_longname": "border[20]"
                },
                "obj-53::obj-2": {
                    "parameter_longname": "mode[2]"
                },
                "obj-53::obj-25": {
                    "parameter_longname": "Map[1]"
                },
                "obj-53::obj-26": {
                    "parameter_longname": "border[19]"
                },
                "obj-53::obj-30": {
                    "parameter_longname": "Unmap[1]"
                },
                "obj-53::obj-32": {
                    "parameter_longname": "TargetMax[1]"
                },
                "obj-53::obj-33": {
                    "parameter_longname": "TargetMin[1]"
                },
                "obj-53::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[2]"
                },
                "obj-53::obj-9": {
                    "parameter_longname": "Modulation Amount 1[2]"
                },
                "obj-60::obj-103": {
                    "parameter_longname": "border[18]"
                },
                "obj-60::obj-2": {
                    "parameter_longname": "mode[1]"
                },
                "obj-60::obj-25": {
                    "parameter_longname": "Map[17]"
                },
                "obj-60::obj-26": {
                    "parameter_longname": "border[1]"
                },
                "obj-60::obj-30": {
                    "parameter_longname": "Unmap[18]"
                },
                "obj-60::obj-32": {
                    "parameter_longname": "TargetMax[8]"
                },
                "obj-60::obj-33": {
                    "parameter_longname": "TargetMin[8]"
                },
                "obj-60::obj-6": {
                    "parameter_longname": "Modulation Polarity 1[1]"
                },
                "obj-60::obj-9": {
                    "parameter_longname": "Modulation Amount 1[1]"
                }
            },
            "inherited_shortname": 1
        },
        "autosave": 0
    }
}