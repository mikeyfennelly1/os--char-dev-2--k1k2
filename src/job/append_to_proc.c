/**
 * Write to the /proc file for this module
 */

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/kernel.h>

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