#include <raylib.h>

// Structure for sorting algorithms state
typedef struct
{
    unsigned int values[100];    // Array of numbers
    unsigned int size;           // Current size
    unsigned int i, j, min_idx;  // Algorithm indices
    bool finished;               // Completion flag
} SortData;

// Enumeration for button types
typedef enum { MENU, BUBBLE, SELECT, INSERT } SortType;

// Structure for UI drawing
typedef struct
{
    Rectangle rect;              // Button rectangle
    Color color;                 // Current button color
    const char *text;            // Label text (optional)
    SortType type;               // Sort types
    bool clicked;                // Click in mouse
} MyButton;

bool UpdateButton(MyButton * button);                           // Mouse interaction logic

// Sorting functions
void SelectionSortStep(SortData * data);                        // Selection sort step
void BubbleSortStep(SortData * data);                           // Bubble sort step
void InsertionSortStep(SortData * data);                        // Insertion sort step

// Drawing functions
void Visual(SortData * data);                                   // Main visualization function
void DrawMenu(const MyButton * buttons);                        // Menu rendering
void DrawSort(const SortData * data, const MyButton * buttons); // Sorting state rendering
