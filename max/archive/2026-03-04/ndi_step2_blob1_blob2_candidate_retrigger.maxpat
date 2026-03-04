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
      1500.0,
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
          "text": "Blob1+Blob2 candidate retrigger: note-on on alive edge AND label change"
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
            "b1_lbl_t",
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
            "b1_lbl_t",
            0
          ],
          "destination": [
            "b1_delay1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b1_delay1",
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
            "b2_lbl_t",
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
            "b2_lbl_t",
            0
          ],
          "destination": [
            "b2_delay1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "b2_delay1",
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
      }
    ]
  }
}
