#!/bin/bash

if [ "$1" == "setup" ]; then
    mkdir -p /tmp/fat.fs/
    dd if=/dev/zero of=/tmp/fat.img bs=1024 count=1024
    mkfs.msdos /tmp/fat.img
    sudo mount -t msdos /tmp/fat.img /tmp/fat.fs/ -o umask=000,loop
    echo "hello, world" > /tmp/fat.fs//hello
elif [ "$1" == "destroy" ]; then
    cd /tmp
    sudo umount /tmp/fat.fs/

    if [ -e /tmp/fat.fs/ ]; then
        rm -r /tmp/fat.fs/
    fi
    
    if [ -e fat.img ]; then
        rm fat.img
    fi
else
    echo "Usage: $0 {setup|destroy}"
    exit 1
fi
