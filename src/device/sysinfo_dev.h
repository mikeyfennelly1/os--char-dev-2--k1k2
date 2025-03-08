#ifndef SYSINFO_DEV_H
#define SYSINFO_DEV_H

static int sysinfo_open(struct inode *inode, struct file *fp);
static int sysinfo_release(struct inode *inode, struct file *filep);
static long sysinfo_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static int __init sysinfo_cdev_init(void);
static void __exit sysinfo_cdev_exit(void);

#endif