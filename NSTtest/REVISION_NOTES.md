# NSTtest Revision Notes

Date: 2026-02-06
Base: `/Users/alastairmcneill/Documents/GitHub/NST/NDI-cv5`
Scope: Experimental changes isolated to `NSTtest` only.

## Goals

- Keep original OSC address format unchanged.
- Reduce packet-format inconsistency and slot crosstalk risk.
- Keep `NDI-cv5` source untouched.

## OSC Format (Unchanged)

- `/NDITracker0/<slot>/on`
- `/NDITracker0/<slot>/off`
- `/NDITracker0/<slot>/val`

## Code Changes

1. `src/OscSender.h`
- Changed `sendVal()` from `sender.sendMessage(m);` to `sender.sendMessage(m, false);`
- Reason: keeps `val` send mode consistent with `on/off`, reduces avoidable per-message wrapping overhead.

2. `src/mtbTracker.h`
- Fixed slot reuse logic in dead-label note-off pass.
- Added `slotReusedThisLoop` detection and early skip with cleanup:
  - if a new blob took the same slot in the same frame, stale mapping is dropped without sending conflicting `noteOff`.
- Reason: reduce slot crosstalk when labels remap to limited slot count.

## Build Verification

From `/Users/alastairmcneill/Documents/GitHub/NST/NSTtest`:

```sh
make -j4
```

Build output target:

- `/Users/alastairmcneill/Documents/GitHub/NST/NSTtest/bin/NSTtest.app`

## Repository Hygiene

- `NDI-cv5` source remains unchanged.
- Experimental app artifacts are kept under `NSTtest/bin`.
