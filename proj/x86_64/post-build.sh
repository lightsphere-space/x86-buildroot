#!/bin/sh

set -u
set -e

# Add a console on tty1
if [ -e ${TARGET_DIR}/etc/inittab ]; then
    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
	sed -i '/GENERIC_SERIAL/a\
tty1::respawn:/sbin/getty -L  tty1 0 vt100 # QEMU graphical window' ${TARGET_DIR}/etc/inittab
fi

# Create /dev/fusion devices using MAKEDEV
# mkdir -p ${TARGET_DIR}/dev
# chroot ${TARGET_DIR} /bin/busybox mdev -s
# chroot ${TARGET_DIR} /bin/busybox mknod -m 666 /dev/fusion c 10 62
### TODO: fix
mkdir -p ${TARGET_DIR}/dev/fusion || true

mknod ${TARGET_DIR}/dev/fusion/0 c 250 0 || true
mknod ${TARGET_DIR}/dev/fusion/1 c 250 1 || true
mknod ${TARGET_DIR}/dev/fusion/2 c 250 2 || true


# Set up to boot directly into sdldemo2
cat <<EOF > ${TARGET_DIR}/etc/init.d/S99sdldemo2
#!/bin/sh
exec /usr/bin/sdldemo2 || /sbin/getty -L tty1 0 vt100
EOF
chmod +x ${TARGET_DIR}/etc/init.d/S99sdldemo2
