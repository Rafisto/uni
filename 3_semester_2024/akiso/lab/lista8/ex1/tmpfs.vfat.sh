#!/bin/bash

if [ "$1" == "setup" ]; then
    mkdir -p /tmp/vfat.fs/
    dd if=/dev/zero of=/tmp/vfat.img bs=1024 count=1024
    mkfs.vfat /tmp/vfat.img
    sudo mount -t vfat /tmp/vfat.img /tmp/vfat.fs/ -o umask=000,loop
    echo "hello, world" > /tmp/vfat.fs/hello
elif [ "$1" == "destroy" ]; then
    cd /tmp
    sudo umount /tmp/vfat.fs/

    if [ -e /tmp/vfat.fs/ ]; then
        rm -r /tmp/vfat.fs/
    fi
    
    if [ -e vfat.img ]; then
        rm vfat.img
    fi
else
    echo "Usage: $0 {setup|destroy}"
    exit 1
fi
