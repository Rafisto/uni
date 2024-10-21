// ACPI - Advanced Configuration and Power Interface

static inline void outw(unsigned short port, unsigned short data) {
    __asm__ volatile ("outw %0, %1" : : "a"(data), "Nd"(port));
}

void shutdown() {
    // ACPI shutdown
    outw(0x604, 0x2000);
    outw(0xB004, 0x2000);
    
    // loop forever if not dead
    while (1) {
        __asm__ volatile ("hlt");
    }
}
