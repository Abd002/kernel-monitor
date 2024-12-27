#!/bin/bash

sudo mount $PWD/../target/rootfs.ext4 /mnt

sudo rm /mnt/root/kernel_module.ko
sudo cp ./kernel_module.ko /mnt/root

sudo umount /mnt

 
