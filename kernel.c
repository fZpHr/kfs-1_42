void kernel_main() {
    const char *str = "42";
    char *video_memory = (char*)0xb8000;
    
    while (*str) {
        *video_memory++ = *str++;
        *video_memory++ = 0x07; // attribut couleur
    }
    
    for (;;);
}