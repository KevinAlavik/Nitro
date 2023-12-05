#!/bin/bash
OS_NAME="Nitro"

make -C limine
make

mkdir -p iso_root
cp -v bin/"$OS_NAME" kfont.psf limine.cfg limine/limine-bios.sys \
    limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/

mkdir -p iso_root/EFI/BOOT
cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/


xorriso -as mkisofs -b limine-bios-cd.bin \
    -no-emul-boot -boot-load-size 4 -boot-info-table \
    --efi-boot limine-uefi-cd.bin \
    -efi-boot-part --efi-boot-image --protective-msdos-label \
    iso_root -o image.iso

./limine/limine bios-install image.iso
rm -rf iso_root
# Execute qemu-system-x86_64 with passed arguments
qemu-system-x86_64 -hda image.iso "${@}"  