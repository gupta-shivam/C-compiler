#include "shubz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    while(!match(EOI))
    {
        stmt();
    }
}
