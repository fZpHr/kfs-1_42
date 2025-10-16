#include "include.h"

void kernel_main() {
    int x = 0, y = 0;
    int dx = 1, dy = 1;
    while (1) {
        clear_screen();
        draw_42(x, y);
        for (volatile int d = 0; d < 1000000; ++d) {
            __asm__ __volatile__("nop");
        }
        x += dx;
        y += dy;
        if (x <= 0 || x >= VGA_WIDTH - 24)
            dx = -dx;
        if (y <= 0 || y >= VGA_HEIGHT - 8)
            dy = -dy;
    }
}

