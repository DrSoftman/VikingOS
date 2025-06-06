#include "core/util.h"
#include "core/interrupts.h"

void quit() {
    _asm("hlt");
}

void _main(u32 magic) {
    idt_init();
    isr_init();
    fpu_init();
    irq_init();

    screen_init();
    int running = 1; // 1 = true ; 0 = false 

    while (running == 1) {
        draw_rectangle(50, 50, 100, 40, COLOR(7, 3, 1)); // Example color
        screen_swap(); // Swap buffers to display the rectangle
        
    }
}

void _main(u32 magic) {
  for (;;) {}
}
