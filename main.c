
#include "raylib.h"
#include "sortdata.h"
#include <stdio.h>
int main(void)
{
    SortData data;

    RestoreData(&data);
 
    Visual(&data);                                // Visual sort

    return 0;
}
