/**
 * Sysinfo character device
 * 
 * A kernel module to provide system information.
 * 
 * @author Sarah McDonagh, Danny Quinn, Mikey Fennelly
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "sysinfo_ioctl.h"

#define DEVICE_NAME "sysinfo_cdev"

static int major;
static struct class *dev_class;
static struct cdev sysinfo_cdev;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = sysinfo_ioctl
};

static int __init sysinfo_cdev_init(void)
{
    dev_t dev;

    if (alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME) < 0)
    {
        printk(KERN_ERR "Failed to allocate a major num for %s\n", DEVICE_NAME);
        return -1;
    }
    major = MAJOR(dev);

    if (cdev_add(&sysinfo_cdev, dev, 1) < 0)
    {
        printk("Failed to add os--char-dev--k1\n");
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    dev_class = class_create(DEVICE_NAME);
    if (IS_ERR(dev_class))
    {
        printk("Failed to register device class for %s\n", DEVICE_NAME);
        cdev_del(&sysinfo_cdev);
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    if (device_create(dev_class, NULL, dev, NULL, DEVICE_NAME) == NULL)
    {
        printk("Failed to create device file for %s\n", DEVICE_NAME);
        class_destroy(dev_class);
        cdev_del(&sysinfo_cdev);
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    printk(KERN_INFO "K1 loaded: /dev/%s\n", DEVICE_NAME);
    return 0;
};



static void __exit sysinfo_cdev_exit(void)
{
    device_destroy(dev_class, MKDEV(major, 0));
    class_destroy(dev_class);
    cdev_del(&sysinfo_cdev);
    unregister_chrdev_region(MKDEV(major, 0), 1);
    printk(KERN_INFO "Module unloaded\n");
};


module_init(sysinfo_cdev_init);
module_exit(sysinfo_cdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikey Fennelly");
MODULE_DESCRIPTION("Produces event for another module's (K2) consumption.");