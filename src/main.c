/**
 * A kernel module to provide system information to userspace.
 * 
 * @author Sarah McDonagh
 * @author Danny Quinn
 * @author Mikey Fennelly
 */

#include "procfs.h"
#include "sysinfo_dev.h"
#include "job.h"

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/version.h>