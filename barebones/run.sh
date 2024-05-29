#!/bin/bash
if [ "$1" = "-d" ]; then
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev sdl,id=audio0 -machine pcspk-audiodev=audio0
else
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev sdl,id=audio0 -machine pcspk-audiodev=audio0
fi
