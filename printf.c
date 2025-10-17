#include "include.h"


void putchar(char c) {
    static int pos = 0;
    volatile char *video = (volatile char*)VIDEO_MEMORY;
    if (c == '\n') {
        pos += 80 - (pos % 80);
    } else {
        video[pos * 2] = c;
        video[pos * 2 + 1] = 0x0F;
        pos++;
    }
}

void putnbr(int n) {
    if (n == 0) {
        putchar('0');
        return;
    }
    char buf[10];
    int i = 0;
    while (n > 0 && i < 10) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    while (i > 0) {
        putchar(buf[--i]);
    }
}

void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    for (; *fmt; ++fmt) {
        if (*fmt == '%' && *(fmt+1)) {
            ++fmt;
            if (*fmt == 's') {
                const char *s = va_arg(args, const char*);
                while (*s) putchar(*s++);
            } else if (*fmt == 'c') {
                char c = (char)va_arg(args, int);
                putchar(c);
            }
            else if (*fmt == 'd') {
                int n = va_arg(args, int);
                putnbr(n);
            }
            else {
                putchar('%');
                putchar(*fmt);
            }
        } else {
            putchar(*fmt);
        }
    }
    va_end(args);
}