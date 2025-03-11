#ifndef PROCFS_H
#define PROCFS_H

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define PROC_FILE_NAME "sysinfo"

static ssize_t sysinfo_proc_read(struct file *file, char *whatever_char, size_t whatever_size,  loff_t *offset);
static int __init char_device_proc_init(void);

#endif