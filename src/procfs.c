#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>

#include "sysinfo_dev.h"
#include "job.h"

#define PROC_FILE_NAME "sysinfo"

ssize_t sysinfo_proc_read(struct file *file, char *whatever_char, size_t whatever_size,  loff_t *offset);
int append_to_proc(struct seq_file *m, void *v);
int my_proc_open(struct inode *inode, struct file *file);
int __init char_device_proc_init(void);
void __exit char_device_proc_exit(void);

/**
 * Function called when userspace file reads /proc/sysinfo
 * 
 * @return 
 */
ssize_t sysinfo_proc_read(struct file *file, char *whatever_char, size_t whatever_size,  loff_t *offset)
{
    Job* current_job = get_current_job();
    const char *buffer = run_job(current_job);

    if (*offset > 0)
        return 0;

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
 * Function to run on initialization of proc file
 * 
 * @return -1 if error, else 0
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
 * Function to run on exit of end of life for /proc/sysinfo.
 * i.e. when module is removed.
 */
void __exit char_device_proc_exit(void)
{
    // Remove the proc file
    proc_remove(proc_entry);
    pr_info("/proc/%s removed\n", PROC_FILE_NAME);
};

int append_to_proc(struct seq_file *m, void *v)
{
    seq_printf(m, "initial content\n");
    seq_printf(m, "more data\n");
    return 0;
};

int my_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, append_to_proc, NULL);
}

MODULE_LICENSE("GPL");