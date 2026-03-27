# NDI Test Sender (Moving Image)

Standalone openFrameworks app that publishes a moving NDI video stream for blob-tracker testing.

## Stream name

`NST Motion Test`

## Build

From this folder:

```bash
make -j4
```

## Run

```bash
open bin/NDI-test-sender.app
```

In `NDI-cv5`, select source name: `NST Motion Test`.

## Controls

- `space`: pause/resume motion
- `+` / `-`: speed up / slow down
