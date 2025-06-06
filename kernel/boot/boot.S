.code16
.org 0

.text

.global _start
_start:
    cli /* disable interrupts to ensure a stable environment for booting */

%macro setup_segments 0
    /* initialize all segment registers to match the code segment */
    mov %cs, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
%endmacro

    /* define essential constants */
    .equ KERNEL_SEGMENT 0x1000 /* memory segment for kernel loading */
    .equ NUM_SECTORS 20 /* number of sectors to read */

    /* set up the stack pointer in free memory space */
    movw $0x3000, %sp

    /* store drive number for later use in loading the kernel */
    mov %dl, drive_num

    sti /* re-enable interrupts */

    /* display startup message: "Booting VikingOS..." */
    movw $boot_message, %si
    call print

    /* load kernel into memory at segment 0x1000 */
    movw $NUM_SECTORS, %cx /* number of sectors to read */
    movb drive_num, %dl /* use stored drive number */
    movw $disk_packet, %si /* point to disk packet */
    movw $KERNEL_SEGMENT, segment /* initial segment for loading */
    movw $1, sector /* start at sector 1 */
sector_loop:
    /* read sector using BIOS interrupt 0x13 */
    movb $0x42, %ah
    int $0x13
    jc disk_error /* if an error occurs, jump to disk error handler */

    /* increment sector and offset */
    addw $64, sector
    addw $0x8000, offset
    jnc sector_same_segment /* if offset didn't overflow, continue */

    /* adjust segment and reset offset on overflow */
    addw $0x1000, segment
    movw $0x0000, offset
sector_same_segment:
    /* decrements %cx and loops if nonzero */
    loop sector_loop

    /* set video mode to 320x200 @ 16 colors */
    movb $0x00, %ah
    movb $0x13, %al
    int $0x10

    /* enable A20 line for accessing high memory */
    cli
    call enable_a20_wait0
    movb $0xD0, %al
    outb $0x64
    call enable_a20_wait1
    xorw %ax, %ax
    inb $0x60

    /* set A20 line state */
    pushw %ax
    call enable_a20_wait0
    movb $0xD1, %al
    outb $0x64
    call enable_a20_wait0
    popw %ax
    orw $0x2, %ax
    outb $0x60

    /* enable protected mode */
    movl %cr0, %eax
    orl $0x1, %eax
    movl %eax, %cr0

    /* jump to flush prefetch queue */
    jmp flush
flush:
    lidt idt /* load Interrupt Descriptor Table */
    lgdt gdtp /* load Global Descriptor Table */

    /* set segment registers for protected mode */
    movw $(gdt_data_segment - gdt_start), %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    movl $0x3000, %esp /* set up the stack */

    /* perform long jump to kernel entry point */
    ljmp $0x8, $entry32

.code32
entry32:
    /* jump to kernel loaded at memory location 0x10000 */
    movl $0x10000, %eax
    jmpl *%eax

_loop:
    jmp _loop /* infinite loop in case execution reaches here */

.code16
enable_a20_wait0:
    /* wait for A20 gate to be ready */
    xorw %ax, %ax
    inb $0x64
    btw $1, %ax
    jc enable_a20_wait0
    ret

enable_a20_wait1:
    /* wait for A20 line status */
    xorw %ax, %ax
    inb $0x64
    btw $0, %ax
    jnc enable_a20_wait1
    ret

disk_error:
    /* handle disk errors by displaying an error message */
    movw $disk_error_str, %si
    call print
    cli 
    hlt /* halt system on error */

print:
    /* print a string pointed to by %ds:si */
    xorb %bh, %bh
    movb $0x0E, %ah

    lodsb /* load next character */
    cmpb $0, %al /* check for null termination */
    je 1f

    /* print character */
    int $0x10
    jmp print

1:  ret /* return from function */

boot_message:
    .asciz "Booting VikingOS...\n"
disk_error_str:
    .asciz "DISK ERROR\n"

drive_num:
    .word 0x0000 /* stores drive number */

/* INT 13H PACKET */
disk_packet:
    .byte 0x10
    .byte 0x00
num_sectors:
    .word 0x0040
offset:
    .word 0x0000
segment:
    .word 0x0000
sector:
    .quad 0x00000000

.align 16
gdtp:
    .word gdt_end - gdt_start - 1  /* GDT size */
    /* .long (0x07C0 << 4) + gdt  /* GDT location */
    .long gdt_start

.align 16
gdt_start:
gdt_null:
    .quad 0  /* null descriptor */
gdt_code_segment:
    .word 0xffff
    .word 0x0000
    .byte 0x00
    .byte 0b10011010  /* code segment descriptor */
    .byte 0b11001111
    .byte 0x00
gdt_data_segment:
    .word 0xffff
    .word 0x0000
    .byte 0x00
    .byte 0b10010010  /* data segment descriptor */
    .byte 0b11001111
    .byte 0x00
gdt_end:

idt:
    .word 0
    .long 0  /* empty IDT */

/* MBR BOOT SIGNATURE */
.fill 510-(.-_start), 1, 0
.word 0xAA55 /* boot signature */
