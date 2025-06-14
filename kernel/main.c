#include "core/interrupts.h"
#include "ui/system/screen.h"
#include "core/system.h"
#include "core/util.h"

void _main(u32 magic) {
    // TODO: Add other init functions for the rest of the os components
    idt_init();	
    isr_init();	
    fpu_init(); 
    irq_init();
	
    screen_init();
    bool quit = false;
    
    while (quit != true) {
        screen_clear(COLOR(0, 0, 7));
        screen_swap();
    }

    // if we ever end up here, loop infinitly...
    for (;;) {}
}
