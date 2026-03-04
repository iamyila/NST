{
  "patcher": {
    "fileversion": 1,
    "appversion": {
      "major": 8,
      "minor": 6,
      "revision": 0,
      "architecture": "x64",
      "modernui": 1
    },
    "classnamespace": "box",
    "rect": [
      60.0,
      80.0,
      1110.0,
      380.0
    ],
    "bglocked": 0,
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
          "id": "c1",
          "maxclass": "comment",
          "patching_rect": [
            20.0,
            10.0,
            420.0,
            20.0
          ],
          "text": "CNMAT Monitor (no oscparse): uses unpackOSC + osc-route"
        }
      },
      {
        "box": {
          "id": "u1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            40.0,
            110.0,
            22.0
          ],
          "text": "udpreceive 12345"
        }
      },
      {
        "box": {
          "id": "p1",
          "maxclass": "newobj",
          "patching_rect": [
            150.0,
            40.0,
            110.0,
            22.0
          ],
          "text": "print UDP_RAW"
        }
      },
      {
        "box": {
          "id": "u2",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            70.0,
            80.0,
            22.0
          ],
          "text": "unpackOSC"
        }
      },
      {
        "box": {
          "id": "p2",
          "maxclass": "newobj",
          "patching_rect": [
            150.0,
            70.0,
            110.0,
            22.0
          ],
          "text": "print UNPACKED"
        }
      },
      {
        "box": {
          "id": "rbase",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            100.0,
            270.0,
            22.0
          ],
          "text": "osc-route /NDItracker0 /NDITracker1"
        }
      },
      {
        "box": {
          "id": "c2",
          "maxclass": "comment",
          "patching_rect": [
            320.0,
            102.0,
            280.0,
            20.0
          ],
          "text": "Supports both base names; either outlet works"
        }
      },
      {
        "box": {
          "id": "rslot",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            130.0,
            330.0,
            22.0
          ],
          "text": "osc-route /1 /2 /3 /4 /5 /6 /7 /8 /9 /10"
        }
      },
      {
        "box": {
          "id": "rs1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_1"
        }
      },
      {
        "box": {
          "id": "off1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_1"
        }
      },
      {
        "box": {
          "id": "val1",
          "maxclass": "newobj",
          "patching_rect": [
            20.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_1"
        }
      },
      {
        "box": {
          "id": "rs2",
          "maxclass": "newobj",
          "patching_rect": [
            116.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on2",
          "maxclass": "newobj",
          "patching_rect": [
            116.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_2"
        }
      },
      {
        "box": {
          "id": "off2",
          "maxclass": "newobj",
          "patching_rect": [
            116.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_2"
        }
      },
      {
        "box": {
          "id": "val2",
          "maxclass": "newobj",
          "patching_rect": [
            116.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_2"
        }
      },
      {
        "box": {
          "id": "rs3",
          "maxclass": "newobj",
          "patching_rect": [
            212.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on3",
          "maxclass": "newobj",
          "patching_rect": [
            212.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_3"
        }
      },
      {
        "box": {
          "id": "off3",
          "maxclass": "newobj",
          "patching_rect": [
            212.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_3"
        }
      },
      {
        "box": {
          "id": "val3",
          "maxclass": "newobj",
          "patching_rect": [
            212.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_3"
        }
      },
      {
        "box": {
          "id": "rs4",
          "maxclass": "newobj",
          "patching_rect": [
            308.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on4",
          "maxclass": "newobj",
          "patching_rect": [
            308.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_4"
        }
      },
      {
        "box": {
          "id": "off4",
          "maxclass": "newobj",
          "patching_rect": [
            308.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_4"
        }
      },
      {
        "box": {
          "id": "val4",
          "maxclass": "newobj",
          "patching_rect": [
            308.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_4"
        }
      },
      {
        "box": {
          "id": "rs5",
          "maxclass": "newobj",
          "patching_rect": [
            404.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on5",
          "maxclass": "newobj",
          "patching_rect": [
            404.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_5"
        }
      },
      {
        "box": {
          "id": "off5",
          "maxclass": "newobj",
          "patching_rect": [
            404.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_5"
        }
      },
      {
        "box": {
          "id": "val5",
          "maxclass": "newobj",
          "patching_rect": [
            404.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_5"
        }
      },
      {
        "box": {
          "id": "rs6",
          "maxclass": "newobj",
          "patching_rect": [
            500.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on6",
          "maxclass": "newobj",
          "patching_rect": [
            500.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_6"
        }
      },
      {
        "box": {
          "id": "off6",
          "maxclass": "newobj",
          "patching_rect": [
            500.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_6"
        }
      },
      {
        "box": {
          "id": "val6",
          "maxclass": "newobj",
          "patching_rect": [
            500.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_6"
        }
      },
      {
        "box": {
          "id": "rs7",
          "maxclass": "newobj",
          "patching_rect": [
            596.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on7",
          "maxclass": "newobj",
          "patching_rect": [
            596.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_7"
        }
      },
      {
        "box": {
          "id": "off7",
          "maxclass": "newobj",
          "patching_rect": [
            596.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_7"
        }
      },
      {
        "box": {
          "id": "val7",
          "maxclass": "newobj",
          "patching_rect": [
            596.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_7"
        }
      },
      {
        "box": {
          "id": "rs8",
          "maxclass": "newobj",
          "patching_rect": [
            692.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on8",
          "maxclass": "newobj",
          "patching_rect": [
            692.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_8"
        }
      },
      {
        "box": {
          "id": "off8",
          "maxclass": "newobj",
          "patching_rect": [
            692.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_8"
        }
      },
      {
        "box": {
          "id": "val8",
          "maxclass": "newobj",
          "patching_rect": [
            692.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_8"
        }
      },
      {
        "box": {
          "id": "rs9",
          "maxclass": "newobj",
          "patching_rect": [
            788.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on9",
          "maxclass": "newobj",
          "patching_rect": [
            788.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_9"
        }
      },
      {
        "box": {
          "id": "off9",
          "maxclass": "newobj",
          "patching_rect": [
            788.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_9"
        }
      },
      {
        "box": {
          "id": "val9",
          "maxclass": "newobj",
          "patching_rect": [
            788.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_9"
        }
      },
      {
        "box": {
          "id": "rs10",
          "maxclass": "newobj",
          "patching_rect": [
            884.0,
            170.0,
            90.0,
            22.0
          ],
          "text": "osc-route /on /off /val"
        }
      },
      {
        "box": {
          "id": "on10",
          "maxclass": "newobj",
          "patching_rect": [
            884.0,
            200.0,
            80.0,
            22.0
          ],
          "text": "print ON_10"
        }
      },
      {
        "box": {
          "id": "off10",
          "maxclass": "newobj",
          "patching_rect": [
            884.0,
            230.0,
            80.0,
            22.0
          ],
          "text": "print OFF_10"
        }
      },
      {
        "box": {
          "id": "val10",
          "maxclass": "newobj",
          "patching_rect": [
            884.0,
            260.0,
            80.0,
            22.0
          ],
          "text": "print VAL_10"
        }
      },
      {
        "box": {
          "id": "c3",
          "maxclass": "comment",
          "patching_rect": [
            20.0,
            300.0,
            360.0,
            20.0
          ],
          "text": "If UDP_RAW prints but UNPACKED does not, packet is not OSC."
        }
      },
      {
        "box": {
          "id": "c4",
          "maxclass": "comment",
          "patching_rect": [
            20.0,
            320.0,
            360.0,
            20.0
          ],
          "text": "If UNPACKED prints but ON/OFF does not, base path mismatch."
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "source": [
            "rslot",
            0
          ],
          "destination": [
            "rs1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs1",
            0
          ],
          "destination": [
            "on1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs1",
            1
          ],
          "destination": [
            "off1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs1",
            2
          ],
          "destination": [
            "val1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            1
          ],
          "destination": [
            "rs2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs2",
            0
          ],
          "destination": [
            "on2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs2",
            1
          ],
          "destination": [
            "off2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs2",
            2
          ],
          "destination": [
            "val2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            2
          ],
          "destination": [
            "rs3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs3",
            0
          ],
          "destination": [
            "on3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs3",
            1
          ],
          "destination": [
            "off3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs3",
            2
          ],
          "destination": [
            "val3",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            3
          ],
          "destination": [
            "rs4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs4",
            0
          ],
          "destination": [
            "on4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs4",
            1
          ],
          "destination": [
            "off4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs4",
            2
          ],
          "destination": [
            "val4",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            4
          ],
          "destination": [
            "rs5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs5",
            0
          ],
          "destination": [
            "on5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs5",
            1
          ],
          "destination": [
            "off5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs5",
            2
          ],
          "destination": [
            "val5",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            5
          ],
          "destination": [
            "rs6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs6",
            0
          ],
          "destination": [
            "on6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs6",
            1
          ],
          "destination": [
            "off6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs6",
            2
          ],
          "destination": [
            "val6",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            6
          ],
          "destination": [
            "rs7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs7",
            0
          ],
          "destination": [
            "on7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs7",
            1
          ],
          "destination": [
            "off7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs7",
            2
          ],
          "destination": [
            "val7",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            7
          ],
          "destination": [
            "rs8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs8",
            0
          ],
          "destination": [
            "on8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs8",
            1
          ],
          "destination": [
            "off8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs8",
            2
          ],
          "destination": [
            "val8",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            8
          ],
          "destination": [
            "rs9",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs9",
            0
          ],
          "destination": [
            "on9",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs9",
            1
          ],
          "destination": [
            "off9",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs9",
            2
          ],
          "destination": [
            "val9",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rslot",
            9
          ],
          "destination": [
            "rs10",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs10",
            0
          ],
          "destination": [
            "on10",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs10",
            1
          ],
          "destination": [
            "off10",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rs10",
            2
          ],
          "destination": [
            "val10",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "u1",
            0
          ],
          "destination": [
            "p1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "u1",
            0
          ],
          "destination": [
            "u2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "u2",
            0
          ],
          "destination": [
            "p2",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "u2",
            0
          ],
          "destination": [
            "rbase",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rbase",
            0
          ],
          "destination": [
            "rslot",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "rbase",
            1
          ],
          "destination": [
            "rslot",
            0
          ]
        }
      }
    ]
  }
}