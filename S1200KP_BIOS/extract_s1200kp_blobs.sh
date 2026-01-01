#!/usr/bin/env bash
set -euo pipefail

# This script extracts the Intel descriptor, ME, and GbE blobs from the
# OEM S1200KP firmware image and places them where the coreboot build
# expects them.

# Determine repository root relative to this script
REPO_ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")"/.. && pwd)
# Note: the directory name uses all uppercase characters in this repo.
DEFAULT_IMAGE="$REPO_ROOT/S1200KP_BIOS/OEM_Bios/W25Q32BV_s1200kp.bin"
IMAGE=${1:-"$DEFAULT_IMAGE"}
OUTPUT_DIR="$REPO_ROOT/coreboot/3rdparty/blobs/mainboard/intel/s1200kp"

if [[ ! -f "$IMAGE" ]]; then
  echo "Firmware image not found: $IMAGE" >&2
  echo "Usage: $0 [path/to/W25Q32BV_s1200kp.bin]" >&2
  exit 1
fi

# Find ifdtool (either installed or built in-tree)
if command -v ifdtool >/dev/null 2>&1; then
  IFD=ifdtool
elif [[ -x "$REPO_ROOT/coreboot/util/ifdtool/ifdtool" ]]; then
  IFD="$REPO_ROOT/coreboot/util/ifdtool/ifdtool"
else
  echo "ifdtool not found. Build it with: make -C coreboot util/ifdtool/ifdtool" >&2
  exit 1
fi

TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

pushd "$TMPDIR" >/dev/null
"$IFD" -x "$IMAGE"
popd >/dev/null

mkdir -p "$OUTPUT_DIR"
install -m 0644 "$TMPDIR/flashregion_0_flashdescriptor.bin" "$OUTPUT_DIR/descriptor.bin"
install -m 0644 "$TMPDIR/flashregion_2_intel_me.bin" "$OUTPUT_DIR/me.bin"
install -m 0644 "$TMPDIR/flashregion_3_gbe.bin" "$OUTPUT_DIR/gbe.bin"

# Ship the BIOS region for reference only; not required for the build.
if [[ -f "$TMPDIR/flashregion_1_bios.bin" ]]; then
  install -m 0644 "$TMPDIR/flashregion_1_bios.bin" "$OUTPUT_DIR/bios_region.bin"
fi

echo "Extracted blobs to $OUTPUT_DIR:" 
ls -lh "$OUTPUT_DIR"/descriptor.bin "$OUTPUT_DIR"/me.bin "$OUTPUT_DIR"/gbe.bin
