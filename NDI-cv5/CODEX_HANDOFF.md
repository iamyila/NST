# Codex AI Handoff Document: NDI-cv5 Updates

This document summarizes recent architectural changes, bug fixes, and feature additions to the `NDI-cv5` openFrameworks application. This context will help Codex AI understand the current state of the codebase, especially regarding the tracking pipeline and GUI persistence.

## 1. Intensity Mask Merge (Tracking Pipeline)
**Files Affected:** `NDI-cv5/src/mtbTracker.h`

**Problem:** The app tracks synthetic video where blobs often lack texture and move slowly. The standard OpenCV background subtractors (MOG2/KNN) "learn" the static interior of these blobs as the background, resulting in hollow blob detections (the "sleeping person" or "interior learning" problem). 

**Solution:** Implemented a parallel intensity-based thresholding step that merges with the background subtraction mask.
*   **New GUI Parameters:** Added `bUseIntensity` (bool toggle) and `intensityThreshold` (int 0-255) to the `bgGrp`.
*   **Logic:** In `mtbTracker::update(cv::Mat & currentMat)`:
    1. The standard `pBackSub->apply()` generates the motion-based `foregroundMat`.
    2. If `bUseIntensity` is true, the incoming `currentMat` is converted to grayscale (`cv::COLOR_RGB2GRAY`).
    3. `cv::threshold` is applied using the `intensityThreshold`.
    4. The resulting threshold mask is merged into the motion mask using `cv::bitwise_or()`.

**Reasoning:** 
We chose parallel intensity thresholding because the source video is synthetic. Unlike noisy real-world camera feeds, synthetic shapes often have uniform, predictable brightness. Relying solely on motion history (MOG2/KNN) fails when these shapes stop or move very slowly, as their static interiors quickly blend into the background model. By extracting an absolute brightness mask (`cv::threshold`) and logically OR-ing it with the motion mask, we guarantee the blob remains solid and true to its shape, completely bypassing the temporal limitations of background subtractors. 
*(Note: Morphological closing was attempted first but reverted. It only patches small gaps, potentially destroying sharp edge features, and fails to recreate massive missing interior areas without severely distorting the overall contour).*

## 2. Settings Persistence & Segfault Fix
**Files Affected:** `NDI-cv5/src/ofApp.h`, `NDI-cv5/src/ofApp.cpp`

**Problem 1:** GUI settings were not saving between sessions. The `loadFromFile` call was commented out.
**Problem 2:** Re-enabling `gui.loadFromFile()` caused a segmentation fault on the second launch. This occurred because loading the settings triggered the `guiScaleEnabled` listener, which immediately called `gui.clear()` and rebuilt the UI *while* the JSON deserialization was still traversing the old UI structure.

**Solution:**
*   **Persistence:** 
    *   Uncommented `gui.loadFromFile(kGuiSettingsFile)` in `setup()`.
    *   Added `ofApp::exit()` which calls `gui.saveToFile(kGuiSettingsFile)` to auto-save on close.
    *   Added `'s'` to `ofApp::keyPressed()` to allow manual saving, and updated the on-screen shortcuts string.
*   **Segfault Guard:** 
    *   Introduced a boolean flag `bool bLoadingSettings` in `ofApp.h`.
    *   In `setup()`, the flag is set to `true` right before `gui.loadFromFile()` and `false` immediately after.
    *   The `guiScaleEnabled` listener in `setupGui()` now wraps its UI-rebuilding logic in `if (!bLoadingSettings) { ... }`, safely ignoring the trigger during startup.

**Reasoning:**
The `ofxGui` library's JSON deserialization process sequentially updates parameters. Updating the `guiScaleEnabled` parameter fired its listener, which executed `gui.clear()` and `gui.setup()`. Doing this *while* the parent `loadFromFile` loop was still iterating over the old GUI component tree caused a fatal memory access violation (segfault). Implementing the `bLoadingSettings` flag was chosen as the most robust, surgical fix. It effectively temporarily mutes the destructive side-effects of listeners during the fragile load phase without requiring a massive architectural rewrite of the application's event system.

## 3. OSC Port Limit Increase
**Files Affected:** `NDI-cv5/src/OscSender.h`

**Problem:** The GUI parameter for the OSC port was hardcapped at `12345`, restricting network configurations.
**Solution:** Updated the `ofParameter<int> oscPort` declaration to allow a maximum value of `65535`.
*   *Code:* `ofParameter<int> oscPort{"port", 12345, 0, 65535};`

**Reasoning:**
The original limit of `12345` was an arbitrary placeholder. Changing the UI maximum to `65535` aligns the application with the actual standard limit for UDP/TCP network ports, ensuring compatibility with complex external routing environments and preventing users from being artificially locked out of valid port assignments.

---
*Generated for Codex AI context parsing.*