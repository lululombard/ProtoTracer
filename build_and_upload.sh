#!/bin/bash
set -e

# Build and upload ProtoTracer firmware to Teensy 4.0

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Kill any existing Teensy uploader UI
killall teensy || true

# Build and upload (shows Teensy uploader GUI on the displays)
DISPLAY=:0 ../env/bin/pio run -t upload -e teensy40ws35

# Wait for upload to complete, then kill the uploader UI
sleep 15
killall teensy || true
