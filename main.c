
#include "raylib.h"
#include "sortdata.h"
#include <time.h>
#include <stdio.h>
int main(void)
{
    SortData data;
    data.size = 100;
    data.i = 0;
    data.j = 1;
    data.min_idx = 0;
    data.finished = false;

    SetRandomSeed(time(NULL));

    for (size_t k = 0; k < data.size; k++)
        data.values[k] = GetRandomValue(10, 400); // Random  

    Visual(&data);                                // Visual sort

    return 0;
}
