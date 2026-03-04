{
  "patcher": {
    "fileversion": 1,
    "appversion": {"major": 9, "minor": 1, "revision": 2, "architecture": "x64", "modernui": 1},
    "classnamespace": "box",
    "bglocked": 0,
    "rect": [50.0, 80.0, 1400.0, 900.0],
    "openinpresentation": 0,
    "default_fontsize": 12.0,
    "default_fontface": 0,
    "default_fontname": "Arial",
    "gridonopen": 1,
    "gridsize": [15.0, 15.0],
    "gridsnaponopen": 1,
    "toolbarvisible": 1,
    "boxes": [
      {"box": {"id": "c0", "maxclass": "comment", "text": "NDI Test Sender (video): two white blobs on black, manual or auto on/off", "patching_rect": [30.0, 10.0, 520.0, 20.0]}},

      {"box": {"id": "t_run", "maxclass": "toggle", "patching_rect": [30.0, 40.0, 24.0, 24.0]}},
      {"box": {"id": "m_run", "maxclass": "message", "text": "enable $1", "patching_rect": [65.0, 41.0, 70.0, 22.0]}},
      {"box": {"id": "w", "maxclass": "newobj", "text": "jit.world ndi_test @size 1280 720 @fps 30. @erase_color 0 0 0 1 @floating 1", "patching_rect": [150.0, 41.0, 420.0, 22.0]}},
      {"box": {"id": "fps", "maxclass": "newobj", "text": "jit.fpsgui", "patching_rect": [590.0, 41.0, 60.0, 22.0]}},

      {"box": {"id": "c1", "maxclass": "comment", "text": "Blob 1", "patching_rect": [30.0, 90.0, 60.0, 20.0]}},
      {"box": {"id": "t1", "maxclass": "toggle", "patching_rect": [30.0, 115.0, 24.0, 24.0]}},
      {"box": {"id": "m1", "maxclass": "message", "text": "enable $1", "patching_rect": [65.0, 116.0, 70.0, 22.0]}},
      {"box": {"id": "g1", "maxclass": "newobj", "text": "jit.gl.gridshape ndi_test @shape sphere @lighting_enable 0 @color 1 1 1 1 @position -0.35 -0.05 0 @scale 0.18 0.18 0.18", "patching_rect": [150.0, 116.0, 620.0, 22.0]}},

      {"box": {"id": "c2", "maxclass": "comment", "text": "Blob 2", "patching_rect": [30.0, 160.0, 60.0, 20.0]}},
      {"box": {"id": "t2", "maxclass": "toggle", "patching_rect": [30.0, 185.0, 24.0, 24.0]}},
      {"box": {"id": "m2", "maxclass": "message", "text": "enable $1", "patching_rect": [65.0, 186.0, 70.0, 22.0]}},
      {"box": {"id": "g2", "maxclass": "newobj", "text": "jit.gl.gridshape ndi_test @shape sphere @lighting_enable 0 @color 1 1 1 1 @position 0.35 0.2 0 @scale 0.14 0.14 0.14", "patching_rect": [150.0, 186.0, 610.0, 22.0]}},

      {"box": {"id": "c3", "maxclass": "comment", "text": "Auto toggle", "patching_rect": [30.0, 250.0, 90.0, 20.0]}},
      {"box": {"id": "ta", "maxclass": "toggle", "patching_rect": [30.0, 275.0, 24.0, 24.0]}},
      {"box": {"id": "mta1", "maxclass": "newobj", "text": "metro 1300", "patching_rect": [65.0, 276.0, 70.0, 22.0]}},
      {"box": {"id": "ra1", "maxclass": "newobj", "text": "random 2", "patching_rect": [145.0, 276.0, 60.0, 22.0]}},
      {"box": {"id": "mta2", "maxclass": "newobj", "text": "metro 1900", "patching_rect": [65.0, 311.0, 70.0, 22.0]}},
      {"box": {"id": "ra2", "maxclass": "newobj", "text": "random 2", "patching_rect": [145.0, 311.0, 60.0, 22.0]}},

      {"box": {"id": "ar", "maxclass": "newobj", "text": "jit.gl.asyncread ndi_test", "patching_rect": [150.0, 360.0, 130.0, 22.0]}},
      {"box": {"id": "ndi", "maxclass": "newobj", "text": "jit.ndi.send @name NDI_TEST_SENDER", "patching_rect": [290.0, 360.0, 200.0, 22.0]}},
      {"box": {"id": "pndi", "maxclass": "newobj", "text": "print NDI_SEND", "patching_rect": [500.0, 360.0, 85.0, 22.0]}},

      {"box": {"id": "c4", "maxclass": "comment", "text": "In NDI-cv5 set NDI Source Match to NDI_TEST_SENDER", "patching_rect": [30.0, 420.0, 330.0, 20.0]}}
    ],
    "lines": [
      {"patchline": {"source": ["t_run", 0], "destination": ["m_run", 0]}},
      {"patchline": {"source": ["m_run", 0], "destination": ["w", 0]}},
      {"patchline": {"source": ["w", 1], "destination": ["fps", 0]}},

      {"patchline": {"source": ["t1", 0], "destination": ["m1", 0]}},
      {"patchline": {"source": ["m1", 0], "destination": ["g1", 0]}},

      {"patchline": {"source": ["t2", 0], "destination": ["m2", 0]}},
      {"patchline": {"source": ["m2", 0], "destination": ["g2", 0]}},

      {"patchline": {"source": ["ta", 0], "destination": ["mta1", 0]}},
      {"patchline": {"source": ["ta", 0], "destination": ["mta2", 0]}},
      {"patchline": {"source": ["mta1", 0], "destination": ["ra1", 0]}},
      {"patchline": {"source": ["ra1", 0], "destination": ["t1", 0]}},
      {"patchline": {"source": ["mta2", 0], "destination": ["ra2", 0]}},
      {"patchline": {"source": ["ra2", 0], "destination": ["t2", 0]}},

      {"patchline": {"source": ["w", 0], "destination": ["ar", 0]}},
      {"patchline": {"source": ["ar", 0], "destination": ["ndi", 0]}},
      {"patchline": {"source": ["ar", 0], "destination": ["pndi", 0]}}
    ]
  }
}
