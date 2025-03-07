/**
 * cpu.c
 * 
 * Gets information about the CPU of the machine that the kernel is running on.
 * 
 * @author Mikey Fennelly
 */

#include <stdint.h>
#include <cpu.h>


/**
 * Get's speed of the host CPU in Hz
 * 
 *  returns this value as an unsigned integer.
 *
 * @brief gets CPU speed in Hz.
 */
unsigned int get_cpu_speed_hz(void)
{
    return cpu_data(0).cpu_khz * 1000;
}