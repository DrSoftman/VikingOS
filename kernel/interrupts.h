#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "util.h"

struct Registers {
    u32 __ignored, fs, es, ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_no;
    u32 eip, cs, efl, useresp, ss;
};

// ISR functions
void isr_install(size_t i, void (*handler)(struct Registers*));
void isr_init();

// FPU functions
void fpu_init();

// IDT functions
void idt_set(u8 index, void (*base)(struct Registers*), u16 selector, u8 flags);
void idt_init();

// IRQ functions
void irq_install(size_t i, void (*handler)(struct Registers*));
void irq_init();

#endif // INTERRUPTS_H
