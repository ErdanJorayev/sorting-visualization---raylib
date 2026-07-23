#include "sortdata.h"

void SelectionSortStep(SortData * data)
{
    if (data->finished) return;
        
    if (data->i < data->size - 1)
    {
        if (data->j < data->size)
        {
            if (data->values[data->j] < data->values[data->min_idx])
                data->min_idx = data->j;
            data->j++;
        }
        else
        {
            unsigned int temp = data->values[data->i];
            data->values[data->i] = data->values[data->min_idx];
            data->values[data->min_idx] = temp;

            data->i++;
            data->min_idx = data->i;
            data->j = data->i + 1;
        }
    }
    else
        data->finished = true;
}

void BubbleSortStep(SortData * data)
{
    if (data->finished) return;

    if (data->values[data->j] > data->values[data->j + 1])
    {
        int temp = data->values[data->j];
        data->values[data->j] = data->values[data->j + 1];
        data->values[data->j + 1] = temp;
    }
    data->j++;

    if (data->j >= data->size - data->i - 1)
    {
        data->j = 0;
        data->i++;
    }

    if (data->i >= data->size - 1)
        data->finished = true;
}

void InsertionSortStep(SortData *data)
{
    if (data->finished) return;

    if (data->i < data->size) 
    {
    
        if (data->j > 0 && data->values[data->j] < data->values[data->j - 1]) 
        {
            unsigned int temp = data->values[data->j];
            data->values[data->j] = data->values[data->j - 1];
            data->values[data->j - 1] = temp;

            data->j--; 
        } 
        else 
        {
            data->i++;
            data->j = data->i; 
        }
    } 
    else 
        data->finished = true;
}

