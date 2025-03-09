#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/kernel.h>

// proc file definitions
#define PROC_FILE_NAME "sysinfo"

/* /proc file initialisation and functions*/

static ssize_t sysinfo_proc_read(struct file *file, char *whatever_char, size_t whatever_size,  loff_t *offset)
{
    printk("proc file read\n");
    return 0;
};

struct proc_dir_entry *proc_entry;

static const struct proc_ops proc_ops = {
    .proc_read = sysinfo_proc_read,
};

static int __init char_device_proc_init(void)
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

static void __exit char_device_proc_exit(void)
{
    // Remove the proc file
    proc_remove(proc_entry);
    pr_info("/proc/%s removed\n", PROC_FILE_NAME);
};

#define PROC_FILENAME "/proc/sysinfo"

int append_to_proc(struct seq_file *m, void *v)
{
    seq_printf(m, "initial content"\n);
    seq_printf(m, "more data\n");
    return 0;
};

static int my_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, my_proc_show, NULL);
}