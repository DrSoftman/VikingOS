#include "mjölnir-ui.h"
#include "../mem/mem.h"
#include "../core/util.h"
#include "system/screen.h"

void draw_rectangle(int x, int y, int width, int height, u8 color) {
    screen_fill(color, x, y, width, height);
}
