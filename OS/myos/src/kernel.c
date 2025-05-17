// src/kernel.c

// Forward-Declaration für die in boot.asm aufgerufene Funktion
void kernel_main(void);

void kernel_main(void) {
    const char* msg = "Hello from MyOS!";
    // VGA-Textmodus: 0xB8000 ist der Framebuffer
    volatile unsigned short* video = (unsigned short*)0xB8000;
    
    // Clear Screen & Schreibe Nachricht in die erste Zeile
    for (int i = 0; i < 80 * 25; i++) {
        video[i] = (unsigned short)(' ' | (0x0F << 8));
    }
    for (int i = 0; msg[i] != '\0'; i++) {
        video[i] = (unsigned short)(msg[i] | (0x0F << 8));
    }

    // Endlosschleife, damit das OS nicht zurück in den Bootloader springt
    for (;;) { __asm__ volatile ("hlt"); }
}
