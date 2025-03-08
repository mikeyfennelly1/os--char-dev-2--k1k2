#include <linux/kernel.h>
#include <linux/file.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>

static char proc_data[100] = "dummy proc file data\n";

static ssize_t proc_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    if (*offset > 0)
    {
        return 0;
    }

    if (copy_to_user(buf, proc_data, strlen(proc_data) + 1))
    {
        return -EFAULT;
    }

    *offset += strlen(proc_data);
    return strlen(proc_data);
};

static const struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

static int __init char_device_proc_init(void)
{
    // Create the proc file at /proc/my_proc_file
    proc_entry = proc_create("my_proc_file", 0666, NULL, &proc_fops);
    if (!proc_entry) {
        pr_err("Failed to create proc file\n");
        return -ENOMEM;
    }

    pr_info("/proc/my_proc_file created\n");
    return 0;
};

static void __exit char_device_proc_exit(void)
{
    // Remove the proc file
    proc_remove(proc_entry);
    pr_info("/proc/my_proc_file removed\n");
};