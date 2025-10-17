#ifndef INCLUDE_H
#define INCLUDE_H


#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define RED_ON_BLACK 0x0C
#define WHITE_ON_BLACK 0x0F // 0x 0 - > background, F - > foreground https://wiki.osdev.org/Text_UI
#define BLUE_ON_BLACK 0x09
#define VIDEO_MEMORY 0xb8000 // 0xB8000 for CGA and text modes https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer

typedef __builtin_va_list va_list;   // https://stackoverflow.com/questions/56412342/where-is-builtin-va-start-defined
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type)   __builtin_va_arg(ap, type)
#define va_end(ap)         __builtin_va_end(ap)


void printf(const char *fmt, ...);
void draw_42(int x, int y);
void clear_screen();

#endif