#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../core/util.h"

#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C

#define KEY_0 0x0B
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A

#define KEY_ENTER 0x1C
#define KEY_SPACE 0x39
#define KEY_ESC 0x01
#define KEY_BACKSPACE 0x0E
#define KEY_TAB 0x0F
#define KEY_SHIFT 0x2A
#define KEY_CTRL 0x1D
#define KEY_ALT 0x38

#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x57
#define KEY_F12 0x58

#define KEY_HOME 0x47
#define KEY_END 0x4F
#define KEY_INSERT 0x52
#define KEY_DELETE 0x53
#define KEY_PAGE_UP 0x49
#define KEY_PAGE_DOWN 0x51

#define KEY_UP 0x48
#define KEY_DOWN 0x50
#define KEY_LEFT 0x4B
#define KEY_RIGHT 0x4D

#define KEY_NUM_LOCK 0x45
#define KEY_SCROLL_LOCK 0x46
#define KEY_CAPS_LOCK 0x3A

#define KEY_PAD_0 0x52
#define KEY_PAD_1 0x4F
#define KEY_PAD_2 0x50
#define KEY_PAD_3 0x51
#define KEY_PAD_4 0x4B
#define KEY_PAD_5 0x4C
#define KEY_PAD_6 0x4D
#define KEY_PAD_7 0x47
#define KEY_PAD_8 0x48
#define KEY_PAD_9 0x49
#define KEY_PAD_PLUS 0x4E
#define KEY_PAD_MINUS 0x4A
#define KEY_PAD_MULTIPLY 0x37
#define KEY_PAD_DIVIDE 0x35
#define KEY_PAD_ENTER 0x1C
#define KEY_PAD_DOT 0x53

#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36
#define KEY_LCTRL 0x1D
#define KEY_RCTRL 0x1D // Some keyboards differentiate this
#define KEY_LALT 0x38
#define KEY_RALT 0x38 // Some keyboards differentiate this
#define KEY_WIN_L 0x5B
#define KEY_WIN_R 0x5C
#define KEY_MENU 0x5D

#define KEY_IS_PRESS(scancode)  ((scancode & 0x80) == 0)
#define KEY_SCANCODE(scancode) (scancode & 0x7F)
#define KEY_CHAR(scancode)     (scancode & 0x7F)

typedef enum {
    KEYBOARD_LAYOUT_US = 0,
    KEYBOARD_LAYOUT_SV = 1
} KeyboardLayout;

struct Keyboard {
    bool keys[128];
    u8 chars[128];
    u8 mods;
    enum {
        KEYBOARD_NONE,
        KEYBOARD_PS2,
        KEYBOARD_USB
    } connected_type;
    KeyboardLayout layout; 
};

// TODO: Declare functions for keyboard drivers


#endif // KEYBOARD_H
