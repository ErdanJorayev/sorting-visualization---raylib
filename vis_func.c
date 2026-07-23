#include <stddef.h>
#include "sortdata.h"

static const int screenWidth = 800;
static const int screenHeight = 450;

static bool UpdateButton(MyButton * button);
static void DrawButton(const MyButton * buttons);
static void DrawMenu(const MyButton * arr, size_t sz);
static bool DrawSort(SortData * data, const SortType sortype, const char * sortname);

// Visualization sort data
void Visual(SortData * data)
{
    InitWindow(screenWidth, screenHeight, "Sorting Visualization"); // Initialize the application window
    SetTargetFPS(60);                                               // Set the refresh rate (60 frames per second)

    // Создаем кнопки для алгоритмов сортировки
    MyButton buttons[3] =
    {
        {{300, 90, 200, 60},  GRAY, "Bubble Sort"},
        {{300, 180, 200, 60}, GRAY, "Selection Sort"},
        {{300, 270, 200, 60}, GRAY, "Insertion Sort"}
    };
    MyButton menu_button = {{500, 10, 70, 30}, WHITE, "MENU", false};     // Кнопка меню
    MyButton stop_button = {{600, 10, 70, 30}, WHITE, "STOP", false};     // Кнопка стоп
    MyButton resume_button = {{700, 10, 70, 30}, WHITE, "RESUME", false}; // Кнопка продолжение

    SortType sorttypes[3] = {BUBBLE, SELECT, INSERT}; // Массив состояний  
    
    bool MENU = true;                                 // Флаг для меню
    bool STOP = false;                                // Флаг стопа
    bool RESUME = false;                              // Флаг продолжение

    SortType activeSort = BUBBLE;                     // Включенная сортировка
    const char * srt_text = nullptr;                  // Название сортировки

    // Main render loop (runs 60 times per second)
    while (!WindowShouldClose())
    {
        // Logic (State Update) ____________________________________________________________________________
        if (MENU)                                     // Handle button clicks in the main menu
        {
            for (size_t i = 0; i < 3; i++)
                if (UpdateButton(&buttons[i]))
                {
                    activeSort = sorttypes[i];     // Выбор сортировки
                    srt_text = buttons[i].text;    // Выбор текста сортировки
                    RestoreData(data);             // Сбрасываем массив под новый старт                   
                    MENU = false;                  // Off menu 
                    STOP = false;                  // Сброс кнопки стоп
                    break;                         // Skip checking other buttons in this frame
                }
        }
        else                                                       
        {
            if (UpdateButton(&menu_button))
                MENU = true;
            if (UpdateButton(&stop_button))
                STOP = true;
            if (UpdateButton(&resume_button))
                STOP = false;
            if(!data->finished && !STOP) 
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
        {
            DrawSort(data, activeSort, srt_text);    
            DrawButton(&menu_button);
            DrawButton(&stop_button);
            if (STOP)     // Если нажата кнопка стоп, выводим кнопку продолжение
                DrawButton(&resume_button);
        } 

        EndDrawing();                                               // Finalize drawing and output the finished frame to the monitor
    } 
}

// Рисуем кнопку
static void DrawButton(const MyButton * buttons)
{
    DrawRectangleRec(buttons->rect, buttons->color);                      // Render the main background rectangle of the button
    DrawRectangleLinesEx(buttons->rect, 2, BLACK);                        // Draw a 2-pixel thick black border around the button

    int textWidth = MeasureText(buttons->text, 20);                       // Calculate the text width in pixels at font size 20
    int posX = buttons->rect.x + (buttons->rect.width - textWidth) / 2;   // Center the text horizontally within the button area
    int posY = buttons->rect.y + (buttons->rect.height - 20) / 2;         // Center the text vertically within the button area

    DrawText(buttons->text, posX, posY, 20, BLACK);                        // Render the text label in the center of the button
}

// Рисуем меню
static void DrawMenu(const MyButton * arr, size_t sz)
{
    ClearBackground(RAYWHITE);
    for (size_t i = 0; i < sz; i++)
        DrawButton(&arr[i]);
}

// Рисуем сортировку
static bool DrawSort(SortData * data, const SortType sortype, const char * sortname)
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

    if (!data->finished)
        DrawText(sortname, 10, 20, 20, GREEN); 
    else
        DrawText("DONE!", 10, 20, 20, GREEN);     
    return false;                               
}

// Логика кнопки
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

// Обнуляем все данные 
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

