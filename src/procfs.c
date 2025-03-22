/**
 * procfs.c
 * 
 * Functions for the /proc filesystem for this device.
 * 
 * @author Mikey Fennelly
 */

#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>

#include "sysinfo_dev.h"
#include "job.h"

#define PROC_FILE_NAME "sysinfo"

ssize_t sysinfo_proc_read(struct file *file, char *read_buffer, size_t whatever_size,  loff_t *offset);
int append_to_proc(struct seq_file *m, void *v);
int my_proc_open(struct inode *inode, struct file *file);
int __init char_device_proc_init(void);
void __exit char_device_proc_exit(void);

/**
 * @brief called when userspace file reads /proc/sysinfo
 * 
 * @param file - pointer to /proc file struct in kernel space
 * @param read_buffer - buffer which the function data will be copied
 * @param available_bytes - number of bytes the reader is allowed to read
 * @param offset - offset for start of read within the file
 * 
 * @return size of the read in bytes
 */
ssize_t sysinfo_proc_read(struct file *file, char *read_buffer, size_t available_bytes,  loff_t *offset)
{
    char buffer[256];

    if (*offset > 0)
        return 0;

    sprintf(buffer, "device name:%s\nread count: %d\ncurrent_info_type: %s\n", DEVICE_NAME, get_times_read(), get_current_job()->job_title);

    size_t len = strlen(buffer);
    if (whatever_size < len)
        len = whatever_size;

    if (copy_to_user(whatever_char, buffer, len)) {
        return -EFAULT;
    }

    *offset += len;
    return len;
};

struct proc_dir_entry *proc_entry;

static const struct proc_ops proc_ops = {
    .proc_read = sysinfo_proc_read,
    .proc_open = my_proc_open,
};

/**
 * @brief function to initialize /proc file
 * 
 * Creates a proc entry in kernel space. Sets permissions 
 * and operations on that file.
 * 
 * @return int status code
 */
int __init char_device_proc_init(void)
{
    // Create the proc file at /proc/PROC_FILE_NAME
    proc_entry = proc_create(PROC_FILE_NAME, 0666, NULL, &proc_ops);
    if (!proc_entry) {
        pr_err("Failed to create /proc/%s\n", PROC_FILE_NAME);
        return -ENOMEM;
    }

    pr_info("/proc/%s created\n", PROC_FILE_NAME);
    return 0;
};

/**
 * @brief function to remove /proc file
 */
void __exit char_device_proc_exit(void)
{
    // Remove the proc file
    proc_remove(proc_entry);
    pr_info("/proc/%s removed\n", PROC_FILE_NAME);
};

/**
 * @brief function to run when proc file is opened.
 * 
 * @param inode - pointer to proc file inode.
 * @param file - function to call on open of proc file.
 * 
 * @return status code
 */
int my_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, append_to_proc, NULL);
}

MODULE_LICENSE("GPL");