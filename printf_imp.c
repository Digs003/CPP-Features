#include <stdarg.h>
#include <unistd.h>
int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    write(STDOUT_FILENO, buffer, len); //libc function to write to stdout
    return len;
}