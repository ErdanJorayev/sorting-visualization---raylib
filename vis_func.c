#include <stddef.h>
#include "sortdata.h"
#define N 3            

static const int screenWidth = 800;
static const int screenHeight = 450;

static bool UpdateButton(MyButton * button);
static void DrawButton(const MyButton * buttons);
static void DrawMenu(const MyButton * arr, size_t sz);
static bool DrawSort(SortData * data, const SortType sortype, const MyButton * arr, size_t sz);

// Visualization sort data
void Visual(SortData * data)
{
    InitWindow(screenWidth, screenHeight, "Sorting Visualization"); // Initialize the application window
    SetTargetFPS(60);                                               // Set the refresh rate (60 frames per second)

    // Configure the array of screen buttons for algorithm selection
    MyButton buttons[N] =
    {
        {{300, 90, 200, 60},  GRAY, "Bubble Sort"},
        {{300, 180, 200, 60}, GRAY, "Selection Sort"},
        {{300, 270, 200, 60}, GRAY, "Insertion Sort"}
    };

    SortType sorttypes[3] = {BUBBLE, SELECT, INSERT}; 
    bool MENU = true;  // Menu flag
    SortType activeSort = 0;


    // Main render loop (runs 60 times per second)
    while (!WindowShouldClose())
    {
        // Logic (State Update) ____________________________________________________________________________
        if (MENU)                                     // Handle button clicks in the main menu
        {
            for (size_t i = 0; i < N; i++)
                if (UpdateButton(&buttons[i]))
                {
                    activeSort = sorttypes[i];                      // Switch state to the selected sorting mode
                    MENU = false;                                   // Off menu 
                    break;                                          // Skip checking other buttons in this frame
                }
        }
        else                                                        // Algorithm visualization mode
        {
                // Execute exactly ONE step of the sorting algorithm per frame
                switch (activeSort)
                {
                    case BUBBLE: BubbleSortStep(data);    break;
                    case SELECT: SelectionSortStep(data); break;
                    case INSERT: InsertionSortStep(data); break;
                    default: break;
                }
        }
        
        // Rendering (Frame Drawing) ______________________________________________________________________________
        BeginDrawing();                                             // Prepare a clean canvas for the current frame

        if (MENU)
            DrawMenu(buttons, 3);                          
        else 
            MENU = DrawSort(data, activeSort, buttons, 3);    

        EndDrawing();                                               // Finalize drawing and output the finished frame to the monitor
    } 
}

static void DrawButton(const MyButton * buttons)
{
    DrawRectangleRec(buttons->rect, buttons->color);                      // Render the main background rectangle of the button
    DrawRectangleLinesEx(buttons->rect, 2, BLACK);                        // Draw a 2-pixel thick black border around the button

    int textWidth = MeasureText(buttons->text, 20);                       // Calculate the text width in pixels at font size 20
    int posX = buttons->rect.x + (buttons->rect.width - textWidth) / 2;   // Center the text horizontally within the button area
    int posY = buttons->rect.y + (buttons->rect.height - 20) / 2;         // Center the text vertically within the button area

    DrawText(buttons->text, posX, posY, 20, BLACK);                        // Render the text label in the center of the button
}

static void DrawMenu(const MyButton * arr, size_t sz)
{
    ClearBackground(RAYWHITE);
    for (size_t i = 0; i < N; i++)
        DrawButton(&arr[i]);
}

// Render the sorting visualization screen
static bool DrawSort(SortData * data, const SortType sortype, const MyButton * arr, size_t sz)
{
    ClearBackground(BLACK);                                                      // Clear the screen with a solid black color
    float barWidth = (float)screenWidth / data->size;                            // Calculate the width of a single element bar
    for (unsigned int k = 0; k < data->size; k++)
    {
        Color color = WHITE;                                                     // Default bar color is white
        if (k == data->min_idx && sortype == SELECT) color = RED;                // Highlight the minimum element found so far in red
        else if (k == data->j) color = YELLOW;                                   // Highlight the currently scanned element in yellow
        else if (k < data->i) color = GREEN;                                     // Highlight the already sorted partition in green

        DrawRectangleV                                                           // Draw the bar using vector positions
        (
            (Vector2){k * barWidth, screenHeight - data->values[k]},             // Invert Y coordinate to grow bars from bottom to top
            (Vector2){barWidth - 1, (float)data->values[k]}, color               // Subtract 1 pixel from width to create gap between bars
        );
    }

    MyButton menu_button = {{500, 10, 70, 30}, WHITE, "MENU", false};
    DrawButton(&menu_button);
    if (UpdateButton(&menu_button))
    {
        RestoreData(data);
        DrawMenu(arr, sz);
        return true;
    }
    
    const char * sortyps[3] = {"Bubble Sort", "Selection Sort", "Insertion Sort"};
    if (!data->finished)
        DrawText(sortyps[sortype], 10, 20, 20, GREEN); 
    else
        DrawText("DONE!", 10, 20, 20, GREEN);     
    return false;                               
}

// Handle mouse interaction logic for a button
static bool UpdateButton(MyButton * button)
{
    const Vector2 mousePoint = GetMousePosition();                              // Get current screen coordinates of the mouse
    button->clicked = false;                                                    // Reset the click flag for the current frame

    if (CheckCollisionPointRec(mousePoint, button->rect))                       // Check if the mouse cursor hovers over the button rectangle
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
             button->color = DARKGRAY;                                          // Set darker color while the button is being held down
        else 
             button->color = LIGHTGRAY;                                         // Set lighter color when the mouse is hovering over it

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
             button->clicked = true;                                            // Trigger click event upon mouse button release
    }
    else
        button->color = GRAY;                                                   // Restore default color when mouse leaves the button area

    return button->clicked;                                                     // Return the current frame state of the button click
}

// Resotre all data 
void RestoreData(SortData * data)
{
    data->size = 100;
    data->i = 0;
    data->j = 1;
    data->min_idx = 0;
    data->finished = false;

    SetRandomSeed(time(NULL));

    for (size_t k = 0; k < data->size; k++)
        data->values[k] = GetRandomValue(10, 400);
}

