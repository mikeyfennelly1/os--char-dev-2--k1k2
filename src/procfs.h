#ifndef PROCFS_H
#define PROCFS_H

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>

#define PROC_FILE_NAME "sysinfo"

ssize_t sysinfo_proc_read(struct file *file, char *whatever_char, size_t whatever_size,  loff_t *offset);
int append_to_proc(struct seq_file *m, void *v);
int my_proc_open(struct inode *inode, struct file *file);
int char_device_proc_init(void);
void char_device_proc_exit(void);

#endif