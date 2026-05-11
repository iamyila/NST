# Codex Handoff: NDI-cv5 Additional Detection

This note covers the `NDI-cv5` changes merged from the `additional-detection` branch.

## Added Detection Option

File:
- `/Users/alastairmcneill/Documents/GitHub/NST/NDI-cv5/src/mtbTracker.h`

Problem:
- background subtraction can learn the interior of slow or static synthetic blobs
- result: hollow detections and broken contours

Change:
- added a parallel brightness-threshold mask
- it is merged into the foreground mask with `cv::bitwise_or`

UI parameters:
- `Use Brightness Fill`
- `Brightness Threshold`

Intent:
- keep this optional
- useful for synthetic feeds and some controlled high-contrast video
- not recommended as a universal default for arbitrary real-world video

## Settings Persistence

Files:
- `/Users/alastairmcneill/Documents/GitHub/NST/NDI-cv5/src/ofApp.cpp`
- `/Users/alastairmcneill/Documents/GitHub/NST/NDI-cv5/src/ofApp.h`

Change:
- settings load is re-enabled with a guard flag `bLoadingSettings`
- settings save on exit
- manual save shortcut: `s`

Reason:
- prevents GUI rebuild during `ofxGui` deserialization
- keeps per-session tracker settings persistent
