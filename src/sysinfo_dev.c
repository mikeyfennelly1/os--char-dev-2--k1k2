#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/version.h>

#include "./procfs.h"
#include "job.h"

// ioctl definitions
#define SET_CIT_CPU 1
#define SET_CIT_MEMORY 2
#define SET_CIT_DISK 3

// device definitions
#define DEVICE_NAME "sysinfo_cdev"

// device constants
static dev_t dev_num;
static struct cdev sysinfo_cdev;
static struct class *sysinfo_dev_class;

int __init sysinfo_cdev_init(void);
void __exit sysinfo_cdev_exit(void);

static int sysinfo_open(struct inode *inode, struct file *fp)
{
    printk(KERN_INFO "Device %s opened\n", DEVICE_NAME);
    return 0;
}

static int sysinfo_release(struct inode *inode, struct file *filep)
{
    printk(KERN_INFO "release\n");
    return 0;
}

ssize_t sysinfo_read(struct file *filp, char __user *user_buffer, size_t count, loff_t *f_pos)
{
    ssize_t bytes_to_copy, bytes_copied;
    Job* current_job = get_current_job();
    if (current_job == NULL)
    {
        printk("current_job == NULL\n");
        return -1;
    }

    char* current_job_data = run_job(current_job);
    if (current_job_data == NULL)
    {
        printk("current_job_data == NULL\n");
        return -1;
    }

    printk("current_job_data: %s\n", current_job_data);
    printk("job step_count: %d\n", current_job->step_count);

    int message_len = strlen(current_job_data);
    if (message_len <= 0)
    {
        printk("message_len <= 0");
        return -1;
    }

    if (*f_pos >= message_len)
        return 0;

    bytes_to_copy = min(count, (size_t)(message_len - *f_pos));

    bytes_copied = copy_to_user(user_buffer, current_job_data + *f_pos, bytes_to_copy);
    if (bytes_copied)
        return -EFAULT;

    *f_pos += bytes_to_copy;

    return bytes_to_copy;
}

static long sysinfo_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int value;

    switch (cmd)
    {
        case SET_CIT_CPU:
            if (set_current_info_type(CPU) < 0)
            {
                pr_info("Failed to set current_info_type to CPU\n");
                break;
            }
            pr_info("current_info_type set to CPU");
            break;
        case SET_CIT_MEMORY:
            if (set_current_info_type(MEMORY) < 0)
            {
                pr_info("Failed to set current_info_type to MEMORY\n");
                break;
            }
            pr_info("current_info_type set to MEMORY");
            break;
        case SET_CIT_DISK:
            if (set_current_info_type(DISK) < 0)
            {
                pr_info("Failed to set current_info_type to DISK\n");
                break;
            }
            pr_info("current_info_type set to DISK");
            break;
        default:
            return -EINVAL;
    }

    return value;
};

// file operations for interacting with the device
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = sysinfo_open,
    .release = sysinfo_release,
    .unlocked_ioctl = sysinfo_ioctl,
    .read = sysinfo_read
};

/**
 * Initialize the device.
 * 
 * This function also encapsulates the creation of the /proc
 * filesystem for this device. This was done so that the
 * /proc filesystem could be created on module load.
 */
int __init sysinfo_cdev_init(void)
{
    int ret;
    
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
    {
        printk(KERN_INFO "Failed to allocate major\n");
        return ret;
    }
    printk(KERN_INFO "Allocated Major: %d, Minor: %d\n", MAJOR(dev_num), MINOR(dev_num));

    // initialize char device
    cdev_init(&sysinfo_cdev, &fops);
    sysinfo_cdev.owner = THIS_MODULE;

    // add dev to kernel
    ret = cdev_add(&sysinfo_cdev, dev_num, 1);
    if (ret < 0)
    {
        pr_err("Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    sysinfo_dev_class = class_create(DEVICE_NAME);
    if (IS_ERR(sysinfo_dev_class))
    {
        printk(KERN_INFO "Failed to create sysinfo_dev_class\n");
        cdev_del(&sysinfo_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(sysinfo_dev_class);
    }

    // create a device node in /dev directory
    if (device_create(sysinfo_dev_class, NULL, dev_num, NULL, DEVICE_NAME) == NULL)
    {
        printk(KERN_INFO "Failed to create device\n");
        class_destroy(sysinfo_dev_class);
        cdev_del(&sysinfo_cdev);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    // create the /proc fs on module init
    char_device_proc_init();

    printk(KERN_INFO "Sysinfo char dev initialized\n");
    return 0;
};

void __exit sysinfo_cdev_exit(void)
{
    // remove the device from the kernel
    int major;
    major = MAJOR(dev_num);
    device_destroy(sysinfo_dev_class, MKDEV(major, 0)); // destroy device
    class_destroy(sysinfo_dev_class); // destroy device class
    cdev_del(&sysinfo_cdev); // delete character device
    unregister_chrdev_region(MKDEV(major, 0), 1); // unregister the major and minor number of device from kernel

    char_device_proc_exit();
    
    printk(KERN_INFO "Module unloaded\n");
    return;
}

// register the init function for the device
module_init(sysinfo_cdev_init);
// register the exit function for the device
module_exit(sysinfo_cdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sarah McDonagh");
MODULE_AUTHOR("Danny Quinn");
MODULE_AUTHOR("Mikey Fennelly");
MODULE_DESCRIPTION("Sysinfo kernel module");