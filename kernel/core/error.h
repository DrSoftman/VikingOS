#ifndef ERROR_H
#define ERROR_H

#include "system.h"
#include "../ui/system/screen.h"
#include "../ui/system/font.h"

// returns and writes error to screen and returns N/A (Not Applicable)  
void panic(const char *err);

#endif // ERROR_H
