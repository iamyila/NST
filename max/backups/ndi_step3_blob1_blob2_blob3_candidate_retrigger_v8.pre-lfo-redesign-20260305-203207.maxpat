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
        "bglocked": 0,
        "rect": [
            34.0,
            87.0,
            1900.0,
            900.0
        ],
        "openinpresentation": 0,
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
                    "patching_rect": [
                        40.0,
                        10.0,
                        560.0,
                        20.0
                    ],
                    "text": "Blob1+Blob2+Blob3: notes from alive edges only; Blob1 X/Y/Speed/Size mappable in M4L"
                }
            },
            {
                "box": {
                    "id": "obj-1",
                    "maxclass": "newobj",
                    "patching_rect": [
                        40.0,
                        40.0,
                        95.0,
                        22.0
                    ],
                    "text": "udpreceive 12345"
                }
            },
            {
                "box": {
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "patching_rect": [
                        40.0,
                        75.0,
                        790.0,
                        22.0
                    ],
                    "text": "route NDITracker1 NDITracker2 NDITracker3 NDITracker4 NDITracker5 NDITracker6 NDITracker7 NDITracker8 NDITracker9 NDITracker10"
                }
            },
            {
                "box": {
                    "id": "b1_tlb",
                    "maxclass": "newobj",
                    "patching_rect": [
                        40.0,
                        120.0,
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
                    "patching_rect": [
                        95.0,
                        120.0,
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
                    "patching_rect": [
                        160.0,
                        152.0,
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
                    "patching_rect": [
                        210.0,
                        152.0,
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
                    "patching_rect": [
                        95.0,
                        152.0,
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
                    "patching_rect": [
                        285.0,
                        152.0,
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
                    "patching_rect": [
                        135.0,
                        187.0,
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
                    "patching_rect": [
                        135.0,
                        222.0,
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
                    "patching_rect": [
                        40.0,
                        152.0,
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
                    "patching_rect": [
                        40.0,
                        187.0,
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
                    "patching_rect": [
                        40.0,
                        222.0,
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
                    "patching_rect": [
                        40.0,
                        257.0,
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
                    "patching_rect": [
                        220.0,
                        295.0,
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
                    "patching_rect": [
                        285.0,
                        295.0,
                        45.0,
                        22.0
                    ],
                    "text": "60 0"
                }
            },
            {
                "box": {
                    "id": "b1_pkt",
                    "maxclass": "newobj",
                    "patching_rect": [
                        370.0,
                        120.0,
                        90.0,
                        22.0
                    ],
                    "text": "print BLOB1_PKT"
                }
            },
            {
                "box": {
                    "id": "b1_lbl",
                    "maxclass": "newobj",
                    "patching_rect": [
                        100.0,
                        187.0,
                        100.0,
                        22.0
                    ],
                    "text": "print BLOB1_LABEL"
                }
            },
            {
                "box": {
                    "id": "b2_tlb",
                    "maxclass": "newobj",
                    "patching_rect": [
                        760.0,
                        120.0,
                        40.0,
                        22.0
                    ],
                    "text": "t l b"
                }
            },
            {
                "box": {
                    "id": "b2_alive_t",
                    "maxclass": "newobj",
                    "patching_rect": [
                        815.0,
                        120.0,
                        50.0,
                        22.0
                    ],
                    "text": "t b b b"
                }
            },
            {
                "box": {
                    "id": "b2_stop",
                    "maxclass": "message",
                    "patching_rect": [
                        880.0,
                        152.0,
                        40.0,
                        22.0
                    ],
                    "text": "stop"
                }
            },
            {
                "box": {
                    "id": "b2_delay",
                    "maxclass": "newobj",
                    "patching_rect": [
                        930.0,
                        152.0,
                        65.0,
                        22.0
                    ],
                    "text": "delay 220"
                }
            },
            {
                "box": {
                    "id": "b2_1",
                    "maxclass": "message",
                    "patching_rect": [
                        815.0,
                        152.0,
                        30.0,
                        22.0
                    ],
                    "text": "1"
                }
            },
            {
                "box": {
                    "id": "b2_0",
                    "maxclass": "message",
                    "patching_rect": [
                        1005.0,
                        152.0,
                        30.0,
                        22.0
                    ],
                    "text": "0"
                }
            },
            {
                "box": {
                    "id": "b2_alive_ch",
                    "maxclass": "newobj",
                    "patching_rect": [
                        855.0,
                        187.0,
                        50.0,
                        22.0
                    ],
                    "text": "change"
                }
            },
            {
                "box": {
                    "id": "b2_sel",
                    "maxclass": "newobj",
                    "patching_rect": [
                        855.0,
                        222.0,
                        60.0,
                        22.0
                    ],
                    "text": "sel 1 0"
                }
            },
            {
                "box": {
                    "id": "b2_unpack",
                    "maxclass": "newobj",
                    "patching_rect": [
                        760.0,
                        152.0,
                        130.0,
                        22.0
                    ],
                    "text": "unpack i f f f f i f f"
                }
            },
            {
                "box": {
                    "id": "b2_label_ch",
                    "maxclass": "newobj",
                    "patching_rect": [
                        760.0,
                        187.0,
                        50.0,
                        22.0
                    ],
                    "text": "change"
                }
            },
            {
                "box": {
                    "id": "b2_lbl_t",
                    "maxclass": "newobj",
                    "patching_rect": [
                        760.0,
                        222.0,
                        40.0,
                        22.0
                    ],
                    "text": "t b b"
                }
            },
            {
                "box": {
                    "id": "b2_delay1",
                    "maxclass": "newobj",
                    "patching_rect": [
                        760.0,
                        257.0,
                        50.0,
                        22.0
                    ],
                    "text": "delay 1"
                }
            },
            {
                "box": {
                    "id": "b2_on",
                    "maxclass": "message",
                    "patching_rect": [
                        940.0,
                        295.0,
                        55.0,
                        22.0
                    ],
                    "text": "62 100"
                }
            },
            {
                "box": {
                    "id": "b2_off",
                    "maxclass": "message",
                    "patching_rect": [
                        1005.0,
                        295.0,
                        45.0,
                        22.0
                    ],
                    "text": "62 0"
                }
            },
            {
                "box": {
                    "id": "b2_pkt",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1090.0,
                        120.0,
                        90.0,
                        22.0
                    ],
                    "text": "print BLOB2_PKT"
                }
            },
            {
                "box": {
                    "id": "b2_lbl",
                    "maxclass": "newobj",
                    "patching_rect": [
                        820.0,
                        187.0,
                        100.0,
                        22.0
                    ],
                    "text": "print BLOB2_LABEL"
                }
            },
            {
                "box": {
                    "id": "obj-40",
                    "maxclass": "newobj",
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
                    "id": "obj-42",
                    "maxclass": "newobj",
                    "patching_rect": [
                        650.0,
                        340.0,
                        95.0,
                        22.0
                    ],
                    "text": "print NOTE_EVENT"
                }
            },
            {
                "box": {
                    "id": "b3_tlb",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1120.0,
                        120.0,
                        40.0,
                        22.0
                    ],
                    "text": "t l b"
                }
            },
            {
                "box": {
                    "id": "b3_alive_t",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1175.0,
                        120.0,
                        50.0,
                        22.0
                    ],
                    "text": "t b b b"
                }
            },
            {
                "box": {
                    "id": "b3_stop",
                    "maxclass": "message",
                    "patching_rect": [
                        1240.0,
                        152.0,
                        40.0,
                        22.0
                    ],
                    "text": "stop"
                }
            },
            {
                "box": {
                    "id": "b3_delay",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1290.0,
                        152.0,
                        65.0,
                        22.0
                    ],
                    "text": "delay 220"
                }
            },
            {
                "box": {
                    "id": "b3_1",
                    "maxclass": "message",
                    "patching_rect": [
                        1175.0,
                        152.0,
                        30.0,
                        22.0
                    ],
                    "text": "1"
                }
            },
            {
                "box": {
                    "id": "b3_0",
                    "maxclass": "message",
                    "patching_rect": [
                        1365.0,
                        152.0,
                        30.0,
                        22.0
                    ],
                    "text": "0"
                }
            },
            {
                "box": {
                    "id": "b3_alive_ch",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1215.0,
                        187.0,
                        50.0,
                        22.0
                    ],
                    "text": "change"
                }
            },
            {
                "box": {
                    "id": "b3_sel",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1215.0,
                        222.0,
                        60.0,
                        22.0
                    ],
                    "text": "sel 1 0"
                }
            },
            {
                "box": {
                    "id": "b3_unpack",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1120.0,
                        152.0,
                        130.0,
                        22.0
                    ],
                    "text": "unpack i f f f f i f f"
                }
            },
            {
                "box": {
                    "id": "b3_label_ch",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1120.0,
                        187.0,
                        50.0,
                        22.0
                    ],
                    "text": "change"
                }
            },
            {
                "box": {
                    "id": "b3_lbl_t",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1120.0,
                        222.0,
                        40.0,
                        22.0
                    ],
                    "text": "t b b"
                }
            },
            {
                "box": {
                    "id": "b3_delay1",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1120.0,
                        257.0,
                        50.0,
                        22.0
                    ],
                    "text": "delay 1"
                }
            },
            {
                "box": {
                    "id": "b3_on",
                    "maxclass": "message",
                    "patching_rect": [
                        1300.0,
                        295.0,
                        55.0,
                        22.0
                    ],
                    "text": "64 100"
                }
            },
            {
                "box": {
                    "id": "b3_off",
                    "maxclass": "message",
                    "patching_rect": [
                        1365.0,
                        295.0,
                        45.0,
                        22.0
                    ],
                    "text": "64 0"
                }
            },
            {
                "box": {
                    "id": "b3_pkt",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1450.0,
                        120.0,
                        90.0,
                        22.0
                    ],
                    "text": "print BLOB3_PKT"
                }
            },
            {
                "box": {
                    "id": "b3_lbl",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1180.0,
                        187.0,
                        100.0,
                        22.0
                    ],
                    "text": "print BLOB3_LABEL"
                }
            },
            {
                "box": {
                    "id": "b2_xy_comment",
                    "maxclass": "comment",
                    "patching_rect": [
                        760.0,
                        340.0,
                        220.0,
                        20.0
                    ],
                    "text": "B2",
                    "presentation": 0,
                    "presentation_rect": [
                        2.0,
                        40.0,
                        20.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "b3_xy_comment",
                    "maxclass": "comment",
                    "patching_rect": [
                        1120.0,
                        340.0,
                        220.0,
                        20.0
                    ],
                    "text": "B3",
                    "presentation": 0,
                    "presentation_rect": [
                        2.0,
                        64.0,
                        20.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "b3_lbl_speedlim",
                    "maxclass": "newobj",
                    "patching_rect": [
                        1185.0,
                        222.0,
                        80.0,
                        22.0
                    ],
                    "text": "speedlim 120"
                }
            },
            {
                "box": {
                    "id": "pres_x_header",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        930.0,
                        280.0,
                        20.0,
                        16.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        34.0,
                        2.0,
                        20.0,
                        16.0
                    ],
                    "text": "X"
                }
            },
            {
                "box": {
                    "id": "pres_y_header",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        1070.0,
                        280.0,
                        20.0,
                        16.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        170.0,
                        2.0,
                        20.0,
                        16.0
                    ],
                    "text": "Y"
                }
            },
            {
                "box": {
                    "id": "pres_x_val_header",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        930.0,
                        344.0,
                        32.0,
                        16.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        34.0,
                        34.0,
                        32.0,
                        16.0
                    ],
                    "text": "Spd"
                }
            },
            {
                "box": {
                    "id": "pres_y_val_header",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        1070.0,
                        344.0,
                        36.0,
                        16.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        170.0,
                        34.0,
                        36.0,
                        16.0
                    ],
                    "text": "Size"
                }
            },
            {
                "box": {
                    "id": "b1_map_panel",
                    "maxclass": "panel",
                    "patching_rect": [
                        980.0,
                        258.0,
                        236.0,
                        128.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        8.0,
                        14.0,
                        236.0,
                        122.0
                    ],
                    "bgcolor": [
                        0.11,
                        0.11,
                        0.11,
                        0.75
                    ],
                    "border": 1,
                    "background": 1
                }
            },
            {
                "box": {
                    "id": "b1_map_title",
                    "maxclass": "comment",
                    "text": "B1 Mapper",
                    "patching_rect": [
                        990.0,
                        262.0,
                        140.0,
                        20.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        14.0,
                        16.0,
                        160.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_inlet_value",
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        990.0,
                        286.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_lbl",
                    "maxclass": "comment",
                    "text": "X",
                    "patching_rect": [
                        988.0,
                        378.0,
                        20.0,
                        18.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        18.0,
                        40.0,
                        16.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_clip",
                    "maxclass": "newobj",
                    "text": "clip 0. 1.",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1026.0,
                        286.0,
                        62.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_speedlim",
                    "maxclass": "newobj",
                    "text": "speedlim 20",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1094.0,
                        286.0,
                        72.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_value_box",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        "bang"
                    ],
                    "patching_rect": [
                        1172.0,
                        286.0,
                        58.0,
                        22.0
                    ],
                    "parameter_enable": 0,
                    "presentation": 1,
                    "presentation_rect": [
                        38.0,
                        38.0,
                        56.0,
                        20.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_map_btn",
                    "maxclass": "live.text",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "text": "Map",
                    "texton": "Stop",
                    "mode": 1,
                    "parameter_enable": 1,
                    "patching_rect": [
                        1236.0,
                        286.0,
                        64.0,
                        22.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        100.0,
                        38.0,
                        64.0,
                        20.0
                    ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [
                                "Off",
                                "On"
                            ],
                            "parameter_type": 2,
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_invisible": 2,
                            "parameter_longname": "B1 X Map",
                            "parameter_shortname": "Map",
                            "parameter_initial": [
                                0
                            ],
                            "parameter_initial_enable": 1
                        },
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
                        }
                    }
                }
            },
            {
                "box": {
                    "id": "mx_sig_src",
                    "maxclass": "newobj",
                    "text": "sig~ 0.",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        1306.0,
                        286.0,
                        45.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_abl_map",
                    "maxclass": "newobj",
                    "text": "poly~ Abl.Map",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [
                        "",
                        "",
                        "",
                        ""
                    ],
                    "patching_rect": [
                        1356.0,
                        286.0,
                        92.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_out_norm",
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        1432.0,
                        286.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_lb",
                    "maxclass": "newobj",
                    "text": "loadbang",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "bang"
                    ],
                    "patching_rect": [
                        990.0,
                        324.0,
                        58.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_m0",
                    "maxclass": "message",
                    "text": "0",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1054.0,
                        324.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_m1",
                    "maxclass": "message",
                    "text": "1",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1090.0,
                        324.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_m100",
                    "maxclass": "message",
                    "text": "100",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1126.0,
                        324.0,
                        40.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mx_defaults_note",
                    "maxclass": "comment",
                    "text": "Abl.Map defaults: min/max 0..100, remote mode, depth 1, unipolar input",
                    "patching_rect": [
                        1172.0,
                        326.0,
                        300.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_inlet_value",
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        990.0,
                        312.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_lbl",
                    "maxclass": "comment",
                    "text": "Y",
                    "patching_rect": [
                        988.0,
                        404.0,
                        20.0,
                        18.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        18.0,
                        64.0,
                        16.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_clip",
                    "maxclass": "newobj",
                    "text": "clip 0. 1.",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1026.0,
                        312.0,
                        62.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_speedlim",
                    "maxclass": "newobj",
                    "text": "speedlim 20",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1094.0,
                        312.0,
                        72.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_value_box",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        "bang"
                    ],
                    "patching_rect": [
                        1172.0,
                        312.0,
                        58.0,
                        22.0
                    ],
                    "parameter_enable": 0,
                    "presentation": 1,
                    "presentation_rect": [
                        38.0,
                        62.0,
                        56.0,
                        20.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_map_btn",
                    "maxclass": "live.text",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "text": "Map",
                    "texton": "Stop",
                    "mode": 1,
                    "parameter_enable": 1,
                    "patching_rect": [
                        1236.0,
                        312.0,
                        64.0,
                        22.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        100.0,
                        62.0,
                        64.0,
                        20.0
                    ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [
                                "Off",
                                "On"
                            ],
                            "parameter_type": 2,
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_invisible": 2,
                            "parameter_longname": "B1 Y Map",
                            "parameter_shortname": "Map",
                            "parameter_initial": [
                                0
                            ],
                            "parameter_initial_enable": 1
                        },
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
                        }
                    }
                }
            },
            {
                "box": {
                    "id": "my_sig_src",
                    "maxclass": "newobj",
                    "text": "sig~ 0.",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        1306.0,
                        312.0,
                        45.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_abl_map",
                    "maxclass": "newobj",
                    "text": "poly~ Abl.Map",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [
                        "",
                        "",
                        "",
                        ""
                    ],
                    "patching_rect": [
                        1356.0,
                        312.0,
                        92.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_out_norm",
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        1432.0,
                        312.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_lb",
                    "maxclass": "newobj",
                    "text": "loadbang",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "bang"
                    ],
                    "patching_rect": [
                        990.0,
                        350.0,
                        58.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_m0",
                    "maxclass": "message",
                    "text": "0",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1054.0,
                        350.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_m1",
                    "maxclass": "message",
                    "text": "1",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1090.0,
                        350.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_m100",
                    "maxclass": "message",
                    "text": "100",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1126.0,
                        350.0,
                        40.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "my_defaults_note",
                    "maxclass": "comment",
                    "text": "Abl.Map defaults: min/max 0..100, remote mode, depth 1, unipolar input",
                    "patching_rect": [
                        1172.0,
                        352.0,
                        300.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_inlet_value",
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        990.0,
                        338.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_lbl",
                    "maxclass": "comment",
                    "text": "Spd",
                    "patching_rect": [
                        988.0,
                        430.0,
                        20.0,
                        18.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        18.0,
                        88.0,
                        16.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_scale",
                    "maxclass": "newobj",
                    "text": "scale 0. 20. 0. 1.",
                    "numinlets": 6,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1026.0,
                        338.0,
                        110.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_clip",
                    "maxclass": "newobj",
                    "text": "clip 0. 1.",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1142.0,
                        338.0,
                        62.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_speedlim",
                    "maxclass": "newobj",
                    "text": "speedlim 20",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1210.0,
                        338.0,
                        72.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_value_box",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        "bang"
                    ],
                    "patching_rect": [
                        1172.0,
                        338.0,
                        58.0,
                        22.0
                    ],
                    "parameter_enable": 0,
                    "presentation": 1,
                    "presentation_rect": [
                        38.0,
                        86.0,
                        56.0,
                        20.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_map_btn",
                    "maxclass": "live.text",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "text": "Map",
                    "texton": "Stop",
                    "mode": 1,
                    "parameter_enable": 1,
                    "patching_rect": [
                        1236.0,
                        338.0,
                        64.0,
                        22.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        100.0,
                        86.0,
                        64.0,
                        20.0
                    ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [
                                "Off",
                                "On"
                            ],
                            "parameter_type": 2,
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_invisible": 2,
                            "parameter_longname": "B1 Spd Map",
                            "parameter_shortname": "Map",
                            "parameter_initial": [
                                0
                            ],
                            "parameter_initial_enable": 1
                        },
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
                        }
                    }
                }
            },
            {
                "box": {
                    "id": "ms_sig_src",
                    "maxclass": "newobj",
                    "text": "sig~ 0.",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        1306.0,
                        338.0,
                        45.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_abl_map",
                    "maxclass": "newobj",
                    "text": "poly~ Abl.Map",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [
                        "",
                        "",
                        "",
                        ""
                    ],
                    "patching_rect": [
                        1356.0,
                        338.0,
                        92.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_out_norm",
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        1432.0,
                        338.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_lb",
                    "maxclass": "newobj",
                    "text": "loadbang",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "bang"
                    ],
                    "patching_rect": [
                        990.0,
                        376.0,
                        58.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_m0",
                    "maxclass": "message",
                    "text": "0",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1054.0,
                        376.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_m1",
                    "maxclass": "message",
                    "text": "1",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1090.0,
                        376.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_m100",
                    "maxclass": "message",
                    "text": "100",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1126.0,
                        376.0,
                        40.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "ms_defaults_note",
                    "maxclass": "comment",
                    "text": "Abl.Map defaults: min/max 0..100, remote mode, depth 1, unipolar input",
                    "patching_rect": [
                        1172.0,
                        378.0,
                        300.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_inlet_value",
                    "maxclass": "inlet",
                    "numinlets": 0,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        990.0,
                        364.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_lbl",
                    "maxclass": "comment",
                    "text": "Size",
                    "patching_rect": [
                        988.0,
                        456.0,
                        20.0,
                        18.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        18.0,
                        112.0,
                        16.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_clip",
                    "maxclass": "newobj",
                    "text": "clip 0. 1.",
                    "numinlets": 3,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1026.0,
                        364.0,
                        62.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_speedlim",
                    "maxclass": "newobj",
                    "text": "speedlim 20",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1094.0,
                        364.0,
                        72.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_value_box",
                    "maxclass": "live.numbox",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        "bang"
                    ],
                    "patching_rect": [
                        1172.0,
                        364.0,
                        58.0,
                        22.0
                    ],
                    "parameter_enable": 0,
                    "presentation": 1,
                    "presentation_rect": [
                        38.0,
                        110.0,
                        56.0,
                        20.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_map_btn",
                    "maxclass": "live.text",
                    "numinlets": 1,
                    "numoutlets": 2,
                    "outlettype": [
                        "",
                        ""
                    ],
                    "text": "Map",
                    "texton": "Stop",
                    "mode": 1,
                    "parameter_enable": 1,
                    "patching_rect": [
                        1236.0,
                        364.0,
                        64.0,
                        22.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        100.0,
                        110.0,
                        64.0,
                        20.0
                    ],
                    "saved_attribute_attributes": {
                        "valueof": {
                            "parameter_enum": [
                                "Off",
                                "On"
                            ],
                            "parameter_type": 2,
                            "parameter_mmax": 1,
                            "parameter_modmode": 0,
                            "parameter_invisible": 2,
                            "parameter_longname": "B1 Size Map",
                            "parameter_shortname": "Map",
                            "parameter_initial": [
                                0
                            ],
                            "parameter_initial_enable": 1
                        },
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
                        }
                    }
                }
            },
            {
                "box": {
                    "id": "mz_sig_src",
                    "maxclass": "newobj",
                    "text": "sig~ 0.",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "signal"
                    ],
                    "patching_rect": [
                        1306.0,
                        364.0,
                        45.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_abl_map",
                    "maxclass": "newobj",
                    "text": "poly~ Abl.Map",
                    "numinlets": 10,
                    "numoutlets": 4,
                    "outlettype": [
                        "",
                        "",
                        "",
                        ""
                    ],
                    "patching_rect": [
                        1356.0,
                        364.0,
                        92.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_out_norm",
                    "maxclass": "outlet",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        1432.0,
                        364.0,
                        24.0,
                        24.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_lb",
                    "maxclass": "newobj",
                    "text": "loadbang",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        "bang"
                    ],
                    "patching_rect": [
                        990.0,
                        402.0,
                        58.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_m0",
                    "maxclass": "message",
                    "text": "0",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1054.0,
                        402.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_m1",
                    "maxclass": "message",
                    "text": "1",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1090.0,
                        402.0,
                        30.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_m100",
                    "maxclass": "message",
                    "text": "100",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        1126.0,
                        402.0,
                        40.0,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "id": "mz_defaults_note",
                    "maxclass": "comment",
                    "text": "Abl.Map defaults: min/max 0..100, remote mode, depth 1, unipolar input",
                    "patching_rect": [
                        1172.0,
                        404.0,
                        300.0,
                        18.0
                    ]
                }
            },
            {
                "box": {
                    "id": "b1_hdr_val",
                    "maxclass": "comment",
                    "text": "Val",
                    "patching_rect": [
                        1040.0,
                        262.0,
                        30.0,
                        16.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        40.0,
                        22.0,
                        26.0,
                        14.0
                    ]
                }
            },
            {
                "box": {
                    "id": "b1_hdr_map",
                    "maxclass": "comment",
                    "text": "Map",
                    "patching_rect": [
                        1102.0,
                        262.0,
                        30.0,
                        16.0
                    ],
                    "presentation": 1,
                    "presentation_rect": [
                        114.0,
                        22.0,
                        32.0,
                        14.0
                    ]
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "source": [
                        "obj-1",
                        0
                    ],
                    "destination": [
                        "obj-2",
                        0
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
                        "b1_tlb",
                        0
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
                        "b1_pkt",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_tlb",
                        0
                    ],
                    "destination": [
                        "b1_unpack",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_tlb",
                        1
                    ],
                    "destination": [
                        "b1_alive_t",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_alive_t",
                        2
                    ],
                    "destination": [
                        "b1_stop",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_stop",
                        0
                    ],
                    "destination": [
                        "b1_delay",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_alive_t",
                        1
                    ],
                    "destination": [
                        "b1_delay",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_alive_t",
                        0
                    ],
                    "destination": [
                        "b1_1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_1",
                        0
                    ],
                    "destination": [
                        "b1_alive_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_delay",
                        0
                    ],
                    "destination": [
                        "b1_0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_0",
                        0
                    ],
                    "destination": [
                        "b1_alive_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_alive_ch",
                        0
                    ],
                    "destination": [
                        "b1_sel",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_sel",
                        0
                    ],
                    "destination": [
                        "b1_on",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_sel",
                        1
                    ],
                    "destination": [
                        "b1_off",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_unpack",
                        0
                    ],
                    "destination": [
                        "b1_label_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_label_ch",
                        0
                    ],
                    "destination": [
                        "b1_lbl_t",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_label_ch",
                        0
                    ],
                    "destination": [
                        "b1_lbl",
                        0
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
                        "b2_tlb",
                        0
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
                        "b2_pkt",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_tlb",
                        0
                    ],
                    "destination": [
                        "b2_unpack",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_tlb",
                        1
                    ],
                    "destination": [
                        "b2_alive_t",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_alive_t",
                        2
                    ],
                    "destination": [
                        "b2_stop",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_stop",
                        0
                    ],
                    "destination": [
                        "b2_delay",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_alive_t",
                        1
                    ],
                    "destination": [
                        "b2_delay",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_alive_t",
                        0
                    ],
                    "destination": [
                        "b2_1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_1",
                        0
                    ],
                    "destination": [
                        "b2_alive_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_delay",
                        0
                    ],
                    "destination": [
                        "b2_0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_0",
                        0
                    ],
                    "destination": [
                        "b2_alive_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_alive_ch",
                        0
                    ],
                    "destination": [
                        "b2_sel",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_sel",
                        0
                    ],
                    "destination": [
                        "b2_on",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_sel",
                        1
                    ],
                    "destination": [
                        "b2_off",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_unpack",
                        0
                    ],
                    "destination": [
                        "b2_label_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_label_ch",
                        0
                    ],
                    "destination": [
                        "b2_lbl_t",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_label_ch",
                        0
                    ],
                    "destination": [
                        "b2_lbl",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_on",
                        0
                    ],
                    "destination": [
                        "obj-40",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_off",
                        0
                    ],
                    "destination": [
                        "obj-40",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_on",
                        0
                    ],
                    "destination": [
                        "obj-40",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_off",
                        0
                    ],
                    "destination": [
                        "obj-40",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "obj-40",
                        0
                    ],
                    "destination": [
                        "obj-41",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "obj-40",
                        1
                    ],
                    "destination": [
                        "obj-41",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_on",
                        0
                    ],
                    "destination": [
                        "obj-42",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_off",
                        0
                    ],
                    "destination": [
                        "obj-42",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_on",
                        0
                    ],
                    "destination": [
                        "obj-42",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b2_off",
                        0
                    ],
                    "destination": [
                        "obj-42",
                        0
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
                        "b3_tlb",
                        0
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
                        "b3_pkt",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_tlb",
                        0
                    ],
                    "destination": [
                        "b3_unpack",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_tlb",
                        1
                    ],
                    "destination": [
                        "b3_alive_t",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_alive_t",
                        2
                    ],
                    "destination": [
                        "b3_stop",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_stop",
                        0
                    ],
                    "destination": [
                        "b3_delay",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_alive_t",
                        1
                    ],
                    "destination": [
                        "b3_delay",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_alive_t",
                        0
                    ],
                    "destination": [
                        "b3_1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_1",
                        0
                    ],
                    "destination": [
                        "b3_alive_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_delay",
                        0
                    ],
                    "destination": [
                        "b3_0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_0",
                        0
                    ],
                    "destination": [
                        "b3_alive_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_alive_ch",
                        0
                    ],
                    "destination": [
                        "b3_sel",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_sel",
                        0
                    ],
                    "destination": [
                        "b3_on",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_sel",
                        1
                    ],
                    "destination": [
                        "b3_off",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_unpack",
                        0
                    ],
                    "destination": [
                        "b3_label_ch",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_label_ch",
                        0
                    ],
                    "destination": [
                        "b3_lbl",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_on",
                        0
                    ],
                    "destination": [
                        "obj-40",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_off",
                        0
                    ],
                    "destination": [
                        "obj-40",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_on",
                        0
                    ],
                    "destination": [
                        "obj-42",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_off",
                        0
                    ],
                    "destination": [
                        "obj-42",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_label_ch",
                        0
                    ],
                    "destination": [
                        "b3_lbl_speedlim",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b3_lbl_speedlim",
                        0
                    ],
                    "destination": [
                        "b3_lbl_t",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_inlet_value",
                        0
                    ],
                    "destination": [
                        "mx_clip",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_clip",
                        0
                    ],
                    "destination": [
                        "mx_speedlim",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_speedlim",
                        0
                    ],
                    "destination": [
                        "mx_value_box",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_speedlim",
                        0
                    ],
                    "destination": [
                        "mx_sig_src",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_speedlim",
                        0
                    ],
                    "destination": [
                        "mx_out_norm",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_sig_src",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_map_btn",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_abl_map",
                        2
                    ],
                    "destination": [
                        "mx_map_btn",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_lb",
                        0
                    ],
                    "destination": [
                        "mx_m0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_lb",
                        0
                    ],
                    "destination": [
                        "mx_m1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_lb",
                        0
                    ],
                    "destination": [
                        "mx_m100",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m0",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        3
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m100",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        4
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m0",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        5
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m1",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        6
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m100",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        7
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m1",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        8
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mx_m0",
                        0
                    ],
                    "destination": [
                        "mx_abl_map",
                        9
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_unpack",
                        1
                    ],
                    "destination": [
                        "mx_inlet_value",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_inlet_value",
                        0
                    ],
                    "destination": [
                        "my_clip",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_clip",
                        0
                    ],
                    "destination": [
                        "my_speedlim",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_speedlim",
                        0
                    ],
                    "destination": [
                        "my_value_box",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_speedlim",
                        0
                    ],
                    "destination": [
                        "my_sig_src",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_speedlim",
                        0
                    ],
                    "destination": [
                        "my_out_norm",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_sig_src",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_map_btn",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_abl_map",
                        2
                    ],
                    "destination": [
                        "my_map_btn",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_lb",
                        0
                    ],
                    "destination": [
                        "my_m0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_lb",
                        0
                    ],
                    "destination": [
                        "my_m1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_lb",
                        0
                    ],
                    "destination": [
                        "my_m100",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m0",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        3
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m100",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        4
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m0",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        5
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m1",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        6
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m100",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        7
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m1",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        8
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "my_m0",
                        0
                    ],
                    "destination": [
                        "my_abl_map",
                        9
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_unpack",
                        2
                    ],
                    "destination": [
                        "my_inlet_value",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_inlet_value",
                        0
                    ],
                    "destination": [
                        "ms_scale",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_scale",
                        0
                    ],
                    "destination": [
                        "ms_clip",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_clip",
                        0
                    ],
                    "destination": [
                        "ms_speedlim",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_speedlim",
                        0
                    ],
                    "destination": [
                        "ms_value_box",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_speedlim",
                        0
                    ],
                    "destination": [
                        "ms_sig_src",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_speedlim",
                        0
                    ],
                    "destination": [
                        "ms_out_norm",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_sig_src",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_map_btn",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_abl_map",
                        2
                    ],
                    "destination": [
                        "ms_map_btn",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_lb",
                        0
                    ],
                    "destination": [
                        "ms_m0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_lb",
                        0
                    ],
                    "destination": [
                        "ms_m1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_lb",
                        0
                    ],
                    "destination": [
                        "ms_m100",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m0",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        3
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m100",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        4
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m0",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        5
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m1",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        6
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m100",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        7
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m1",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        8
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "ms_m0",
                        0
                    ],
                    "destination": [
                        "ms_abl_map",
                        9
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_unpack",
                        3
                    ],
                    "destination": [
                        "ms_inlet_value",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_inlet_value",
                        0
                    ],
                    "destination": [
                        "mz_clip",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_clip",
                        0
                    ],
                    "destination": [
                        "mz_speedlim",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_speedlim",
                        0
                    ],
                    "destination": [
                        "mz_value_box",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_speedlim",
                        0
                    ],
                    "destination": [
                        "mz_sig_src",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_speedlim",
                        0
                    ],
                    "destination": [
                        "mz_out_norm",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_sig_src",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_map_btn",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_abl_map",
                        2
                    ],
                    "destination": [
                        "mz_map_btn",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_lb",
                        0
                    ],
                    "destination": [
                        "mz_m0",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_lb",
                        0
                    ],
                    "destination": [
                        "mz_m1",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_lb",
                        0
                    ],
                    "destination": [
                        "mz_m100",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m0",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        3
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m100",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        4
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m0",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        5
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m1",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        6
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m100",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        7
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m1",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        8
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "mz_m0",
                        0
                    ],
                    "destination": [
                        "mz_abl_map",
                        9
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "b1_unpack",
                        4
                    ],
                    "destination": [
                        "mz_inlet_value",
                        0
                    ]
                }
            }
        ],
        "openrect": [
            0.0,
            0.0,
            230.0,
            169.0
        ],
        "openrectmode": 0
    }
}