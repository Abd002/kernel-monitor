# Steps to Create a Root Filesystem (RFS)

Follow these steps to generate a Root Filesystem (RFS) for your system:

## 1. Create a Blank Filesystem Image
Use the following commands to create a blank Ext4 filesystem image:

```bash
dd if=/dev/zero of=rootfs.ext4 bs=1M count=1024
mkfs.ext4 rootfs.ext4
```

- `dd if=/dev/zero of=rootfs.ext4 bs=1M count=1024`: Creates a blank 1GB file named `rootfs.ext4`.
- `mkfs.ext4 rootfs.ext4`: Formats the file with the Ext4 filesystem.

## 2. Mount the Filesystem Image
Mount the newly created `rootfs.ext4` file to a folder (e.g., `/mnt`):

```bash
sudo mount rootfs.ext4 /mnt
```

- `sudo mount rootfs.ext4 /mnt`: Mounts the file to the `/mnt` directory.

## 3. Copy Files to the Mounted Filesystem
Copy the necessary files into the mounted filesystem:

```bash
cp -r busybox/_install /mnt
cp -r compiler_tool/binc/* /mnt
```

- `cp -r busybox/_install /mnt`: Copies the BusyBox installation files to the mounted directory.
- `cp -r compiler_tool/binc/* /mnt`: Copies the compiler tool binaries into the mounted directory.

## 4. Unmount the Filesystem
After copying the files, unmount the filesystem to finalize the RFS creation:

```bash
sudo umount /mnt
```

- `sudo umount /mnt`: Safely unmounts the `rootfs.ext4` file from the `/mnt` directory.

---

Your Root Filesystem (RFS) is now ready. You can customize and use it as needed for your system.
```
[Download File](https://drive.google.com/file/d/1ksTqVTd2jdxr7GRt_ZbFzzFc4V8F4Ggr/view)
