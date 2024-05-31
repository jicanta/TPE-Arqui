#!/bin/bash
if [ "$1" = "-d" ]; then
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=speaker -machine pcspk-audiodev=speaker
else
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=speaker -machine pcspk-audiodev=speaker
fi

#jbirsa y jicanta
# -audiodev alsa,id=speaker -machine pcspk-audiodev=speaker

#jgonzalezcornet
# -audiodev coreaudio,id=speaker -machine pcspk-audiodev=speaker