#include <stddef.h>
#include "sortdata.h"
#define N 3                                                         // For buttons
static const int screenWidth = 800;
static const int screenHeight = 450;


void Visual(SortData * data)
{
    InitWindow(screenWidth, screenHeight, "Sorting Visualization"); // Initialize the application window
    SetTargetFPS(60);                                               // Set the refresh rate (60 frames per second)

    SortType activeSort = MENU;                                     // Initial application state — display the menu

    // Configure the array of screen buttons for algorithm selection
    MyButton buttons[N] =
    {
        {{300, 90, 200, 60},  GRAY, "Bubble Sort",    BUBBLE},
        {{300, 180, 200, 60}, GRAY, "Selection Sort", SELECT},
        {{300, 270, 200, 60}, GRAY, "Insertion Sort", INSERT}
    };

    size_t chosenIdx = 0;                                           // Index of the button selected by the user
    
    // Main render loop (runs 60 times per second)
    while (!WindowShouldClose())
    {
        // Game Logic (State Update) ____________________________________________________________________________
        if (activeSort == MENU)                                     // Handle button clicks in the main menu
        {
            for (size_t i = 0; i < N; i++)
                if (UpdateButton(&buttons[i]))
                {
                    activeSort = buttons[i].type;                   // Switch state to the selected sorting mode
                    chosenIdx = i;                                  // Remember which sorting algorithm is active
                    break;                                          // Skip checking other buttons in this frame
                }
        }
        else                                                        // Algorithm visualization mode
        {
            if (!data->finished)
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
        }
        
        // Rendering (Frame Drawing) ______________________________________________________________________________
        BeginDrawing();                                             // Prepare a clean canvas for the current frame

        if (activeSort == MENU)
            DrawMenu(buttons);                                      // Render the menu UI elements
        else
            DrawSort(data, &buttons[chosenIdx]);                    // Render the bar chart for the current sorting step

        EndDrawing();                                               // Finalize drawing and output the finished frame to the monitor
    } 
}


// Handle mouse interaction logic for a button
bool UpdateButton(MyButton * button)
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


// Render the main menu screen
void DrawMenu(const MyButton * buttons)
{
    ClearBackground(RAYWHITE);                                                  // Clear the screen background with a light gray color
    for (size_t i = 0; i < N; i++)
    {
        DrawRectangleRec(buttons[i].rect, buttons[i].color);                    // Render the main background rectangle of the button
        DrawRectangleLinesEx(buttons[i].rect, 2, BLACK);                        // Draw a 2-pixel thick black border around the button

        int textWidth = MeasureText(buttons[i].text, 20);                       // Calculate the text width in pixels at font size 20
        int posX = buttons[i].rect.x + (buttons[i].rect.width - textWidth) / 2; // Center the text horizontally within the button area
        int posY = buttons[i].rect.y + (buttons[i].rect.height - 20) / 2;       // Center the text vertically within the button area

        DrawText(buttons[i].text, posX, posY, 20, BLACK);                       // Render the text label in the center of the button
    }
}


// Render the sorting visualization screen
void DrawSort(const SortData * data, const MyButton * buttons)
{
    ClearBackground(BLACK);                                                      // Clear the screen with a solid black color

    float barWidth = (float)screenWidth / data->size;                            // Calculate the width of a single element bar
    for (size_t k = 0; k < data->size; k++)
    {
        Color color = WHITE;                                                     // Default bar color is white
        if (k == data->min_idx &&  buttons->type == SELECT) color = RED;         // Highlight the minimum element found so far in red
        else if (k == data->j) color = YELLOW;                                   // Highlight the currently scanned element in yellow
        else if (k < data->i) color = GREEN;                                     // Highlight the already sorted partition in green

        DrawRectangleV                                                           // Draw the bar using vector positions
        (
            (Vector2){k * barWidth, screenHeight - data->values[k]},             // Invert Y coordinate to grow bars from bottom to top
            (Vector2){barWidth - 1, (float)data->values[k]}, color               // Subtract 1 pixel from width to create gap between bars
        );
    }
    if (!data->finished)
        DrawText(buttons->text, 10, 10, 20, GREEN);                              // Display the name of the active sorting algorithm
    else
        DrawText("DONE!", 10, 20, 20, GREEN);                                    // Display completion status when sorting is finished
}

