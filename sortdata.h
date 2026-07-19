#include <raylib.h>
#include <time.h>
// Structure for sorting algorithms state
typedef struct
{
    unsigned int values[100];    // Array of numbers
    unsigned int size;           // Current size
    unsigned int i, j, min_idx;  // Algorithm indices
    bool finished;               // Completion flag
} SortData;


// Enumeration for button types
typedef enum { BUBBLE, SELECT, INSERT } SortType;

// Structure for buttons
typedef struct
{
    Rectangle rect;              // Button rectangle
    Color color;                 // Current button color
    const char *text;            // Label text (optional)
    bool clicked;                // Click in mouse
} MyButton;

// Sorting functions
void SelectionSortStep(SortData * data);                        // Selection sort step
void BubbleSortStep(SortData * data);                           // Bubble sort step
void InsertionSortStep(SortData * data);                        // Insertion sort step

// Drawing functions
void Visual(SortData * data);                                   // Main visualization function
void RestoreData(SortData * data);
