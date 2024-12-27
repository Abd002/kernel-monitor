#!/bin/bash

sudo mount $PWD/../target/rootfs.ext4 /mnt

arm-none-linux-gnueabihf-gcc ./main.c

sudo cp ./a.out /mnt/root

sudo umount /mnt

 
