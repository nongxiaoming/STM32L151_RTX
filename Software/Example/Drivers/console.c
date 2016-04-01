#include "console.h"
#include "RTL.h"



//extern void VCP_put_char(uint8_t buf);
int fputc(int ch, FILE *f)
{

   // serial_put_char((uint8_t)ch);
    //VCP_put_char(ch);
    return  ch;
}

#include <stdarg.h>
/**
 * This function will print a formatted string on system console
 *
 * @param fmt the format
 */
void kprintf(const char *fmt, ...)
{
    va_list args;
    uint32_t length;
    static char log_buf[256];
    
    va_start(args, fmt);
    /* the return value of vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the rt_log_buf, we have to adjust the output
     * length. */
    length = vsnprintf(log_buf, sizeof(log_buf) - 1, fmt, args);
    if (length > 256 - 1)
        length = 256 - 1;

   // serial_write((uint8_t *)log_buf, length);

    va_end(args);
}

