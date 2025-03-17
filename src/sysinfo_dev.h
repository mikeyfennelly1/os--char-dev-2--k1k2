#ifndef SYSINFO_DEV_H
#define SYSINFO_DEV_H

#define DEVICE_NAME "sysinfo"

int sysinfo_cdev_init(void);
void sysinfo_cdev_exit(void);
int get_times_read(void);
int get_time_since_loading_ns(void);

#endif