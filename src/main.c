/**
 * A kernel module to provide system information to userspace.
 * 
 * @author Sarah McDonagh
 * @author Danny Quinn
 * @author Mikey Fennelly
 */

// Initialize char device on module init

#include "device/sysinfo_dev.h"

// register the init function for the device
module_init(sysinfo_cdev_init);
// register the exit function for the device
module_exit(sysinfo_cdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sarah McDonagh");
MODULE_AUTHOR("Danny Quinn");
MODULE_AUTHOR("Mikey Fennelly");
MODULE_DESCRIPTION("Sysinfo kernel module");