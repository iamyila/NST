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
      1000.0,
      680.0
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
          "id": "t1",
          "maxclass": "newobj",
          "text": "t b b b",
          "numinlets": 1,
          "numoutlets": 3,
          "outlettype": [
            "bang",
            "bang",
            "bang"
          ],
          "patching_rect": [
            40.0,
            85.0,
            50.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "mstop",
          "maxclass": "message",
          "text": "stop",
          "numinlets": 2,
          "numoutlets": 1,
          "patching_rect": [
            105.0,
            117.0,
            40.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "d1",
          "maxclass": "newobj",
          "text": "delay 700",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "bang"
          ],
          "patching_rect": [
            155.0,
            117.0,
            65.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "onv",
          "maxclass": "message",
          "text": "1",
          "numinlets": 2,
          "numoutlets": 1,
          "patching_rect": [
            40.0,
            117.0,
            30.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "offv",
          "maxclass": "message",
          "text": "0",
          "numinlets": 2,
          "numoutlets": 1,
          "patching_rect": [
            230.0,
            117.0,
            30.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "chg",
          "maxclass": "newobj",
          "text": "change",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "int"
          ],
          "patching_rect": [
            80.0,
            155.0,
            50.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "sel",
          "maxclass": "newobj",
          "text": "sel 1 0",
          "numinlets": 1,
          "numoutlets": 3,
          "outlettype": [
            "bang",
            "bang",
            ""
          ],
          "patching_rect": [
            80.0,
            191.0,
            60.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "non",
          "maxclass": "message",
          "text": "60 100",
          "numinlets": 2,
          "numoutlets": 1,
          "patching_rect": [
            40.0,
            227.0,
            55.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "noff",
          "maxclass": "message",
          "text": "60 0",
          "numinlets": 2,
          "numoutlets": 1,
          "patching_rect": [
            110.0,
            227.0,
            45.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "out1",
          "maxclass": "outlet",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            80.0,
            270.0,
            25.0,
            25.0
          ]
        }
      },
      {
        "box": {
          "id": "p1",
          "maxclass": "newobj",
          "text": "print GATE1_NOTE",
          "numinlets": 1,
          "numoutlets": 0,
          "patching_rect": [
            140.0,
            270.0,
            95.0,
            22.0
          ]
        }
      },
      {
        "box": {
          "id": "c1",
          "maxclass": "comment",
          "text": "Gate-only module (no inlet object): connect route NDITracker1 outlet directly to [t b b b]",
          "patching_rect": [
            40.0,
            10.0,
            520.0,
            20.0
          ]
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "source": [
            "t1",
            2
          ],
          "destination": [
            "mstop",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "mstop",
            0
          ],
          "destination": [
            "d1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "t1",
            1
          ],
          "destination": [
            "d1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "t1",
            0
          ],
          "destination": [
            "onv",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "onv",
            0
          ],
          "destination": [
            "chg",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "d1",
            0
          ],
          "destination": [
            "offv",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "offv",
            0
          ],
          "destination": [
            "chg",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "chg",
            0
          ],
          "destination": [
            "sel",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "sel",
            0
          ],
          "destination": [
            "non",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "sel",
            1
          ],
          "destination": [
            "noff",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "non",
            0
          ],
          "destination": [
            "out1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "noff",
            0
          ],
          "destination": [
            "out1",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "non",
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
            "noff",
            0
          ],
          "destination": [
            "p1",
            0
          ]
        }
      }
    ]
  }
}