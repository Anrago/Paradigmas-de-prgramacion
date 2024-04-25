#include "Snake.h"
#include <stdio.h>

#define MAX_COLUMNS 41
#define MAX_ROWS 20
#define CELL_SIZE 40
#define PADDING 5
#define MOVE_SPEED 0.5f
#define WIDTH 1920
#define HEIGHT 1080

// void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void DrawBody(int startX, int startY, Tbody *head);
void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS], int keyPressed, bool *CloseGame);
void BackRec();
int Detected(int KeyPresed);
void GameOver(int points);
void Game();

int main(void)
{
    Vector2 Mouse;
    Rectangle Start = {685, 454, 558, 155};
    Rectangle Close = {685, 687, 558, 155};
    Color DARKRED = {139, 0, 0, 255};
    Color font = {50, 60, 57, 255};
    int Points = 0;
    bool MouseStartGame = 0;
    bool MouseCloseGame = 0;
    bool CloseGame = false;

    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "Snake");

    while (!CloseGame && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIME);
        Mouse = GetMousePosition();
        BackRec();
        DrawText("SNAKE", (WIDTH / 2) - 325, 150, 200, font );
        DrawRectangleRec(Start, BLUE);
        DrawRectangleRec(Close, RED);
    
        MouseStartGame = CheckCollisionPointRec(Mouse, Start);
        MouseCloseGame = CheckCollisionPointRec(Mouse, Close);

        if (MouseStartGame)
        {
            DrawRectangleLines(Start.x, Start.y, Start.width, Start.height, BLACK);
            DrawRectangleRec(Start, DARKBLUE);
        }
        if (MouseCloseGame)
        {
            DrawRectangleLines(Close.x, Close.y, Close.width, Close.height, BLACK);
            DrawRectangleRec(Close, DARKRED);
        }
        DrawText("Start", Start.x + 125, Start.y + 30, 100, font);
        DrawText("Close", Close.x + 125, Close.y + 30, 100, font);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (MouseStartGame)
                Game();

            if (MouseCloseGame)
                CloseGame = 1;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
//------------------------Funciones------------------------------
void BackRec()
{
    DrawRectangleRec((Rectangle){0,0,150,HEIGHT}, DARKGREEN);
    DrawRectangleRec((Rectangle){1920-150,0,150,HEIGHT}, DARKGREEN);
    DrawRectangleRec((Rectangle){0,0,WIDTH,70}, DARKGREEN);
    DrawRectangleRec((Rectangle){0,1080-120,WIDTH,70}, DARKGREEN);    
}

void Game()
{
    Vector2 Apple = {GetRandomValue(1, MAX_COLUMNS - 1), GetRandomValue(1, MAX_ROWS - 1)};
    Snake *snake = InitSnake((Vector2){11, 9});
    int startX = 40;
    int startY = 80;
    int Matrix[MAX_ROWS][MAX_COLUMNS];
    int detctKeyboar = 4;
    int temp;
    bool CloseGame = false;

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            Matrix[i][j] = 0;
        }
    }

    Matrix[(int)Apple.y][(int)Apple.x] = 2;
    Matrix[(int)snake->head->pos.y][(int)snake->head->pos.x] = 1;
    while (!CloseGame && !WindowShouldClose())
    {
        BeginDrawing();
        DrawText("SNAKE", (WIDTH / 2) - 100, 30, 50, BLUE);

        DrawText(TextFormat("Points: %i", snake->points), 100, 40, 30, BLUE);

        DrawMatrix(startX, startY, Matrix);

        if (CheckCollisionRecs((Rectangle){snake->head->pos.x * (CELL_SIZE + PADDING) + startX, snake->head->pos.y * (CELL_SIZE + PADDING) + startY, CELL_SIZE, CELL_SIZE}, (Rectangle){Apple.x * (CELL_SIZE + PADDING) + startX, Apple.y * (CELL_SIZE + PADDING) + startY, CELL_SIZE, CELL_SIZE}))
        {
            Matrix[(int)Apple.y][(int)Apple.x] = 0;
            do
            {
                Apple.x = GetRandomValue(1, MAX_COLUMNS - 1);
                Apple.y = GetRandomValue(1, MAX_ROWS - 1);
            } while (Matrix[(int)Apple.y][(int)Apple.x] != 0);

            Matrix[(int)Apple.y][(int)Apple.x] = 2;
            AddBody(snake, (Vector2){snake->head->pos.x, snake->head->pos.y});
            Matrix[(int)snake->head->pos.y][(int)snake->head->pos.x - 1] = 1;
            snake->points++;
        }

        if (snake->head->pos.x == -1 || snake->head->pos.x == MAX_COLUMNS || snake->head->pos.y == -1 || snake->head->pos.y == MAX_ROWS)
            CloseGame = true;

        DrawBody(startX, startY, snake->head);

        int keyPresed = GetKeyPressed();

        if (keyPresed != 0)
        {
            detctKeyboar = Detected(keyPresed);
            MoveSnake(&snake->head->pos, snake->head, Matrix, detctKeyboar, &CloseGame);
        }
        MoveSnake(&snake->head->pos, snake->head, Matrix, detctKeyboar, &CloseGame);

        ClearBackground(BLACK);
        EndDrawing();
    }

    GameOver(snake->points);
    FreeSnake(snake);
}

void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS])
{
    Color DARKRED = {192, 0, 0, 255};
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            int cellX = posx + j * (CELL_SIZE + PADDING);
            int cellY = posy + i * (CELL_SIZE + PADDING);
            Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
            if (Matrix[i][j] == 0)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, DARKGREEN);
            if (Matrix[i][j] == 2)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, DARKRED);
        }
    }
}

void DrawBody(int startX, int startY, Tbody *head)
{
    int iter = 0;
    Color body = {100, 156, 0, 255};
    Tbody *currentNode = head;
    while (currentNode != NULL)
    {
        int cellX = startX + currentNode->pos.x * (CELL_SIZE + PADDING);
        int cellY = startY + currentNode->pos.y * (CELL_SIZE + PADDING);
        Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
        if (iter == 0)
        {
            DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, BLACK);
            iter = 1;
        }
        else
            DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, body);

        currentNode = currentNode->next;
    }
}

void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS], int keyPressed, bool *CloseGame)
{
    int tempX = pos->x;
    int tempY = pos->y;
    int nextX = tempX;
    int nextY = tempY;
    static int currentDirection = 4;
    static float timer = 0;
    timer += GetFrameTime();
    if (timer < MOVE_SPEED * 0.2f)
        return;
    if (keyPressed == 4 && currentDirection != 3)
        currentDirection = 4; // Derecha
    else if (keyPressed == 3 && currentDirection != 4)
        currentDirection = 3; // Izquierda
    else if (keyPressed == 2 && currentDirection != 1)
        currentDirection = 2; // Arriba
    else if (keyPressed == 1 && currentDirection != 2)
        currentDirection = 1; // Abajo

    // Mover la serpiente según la dirección actual
    if (currentDirection == 4)
    {
        nextX++;
    }
    else if (currentDirection == 3)
    {
        nextX--;
    }
    else if (currentDirection == 2)
    {
        nextY--;
    }
    else if (currentDirection == 1)
    {
        nextY++;
    }

    Tbody *CollisionNode = head->next;
    while (CollisionNode != NULL)
    {
        if (nextX == CollisionNode->pos.x && nextY == CollisionNode->pos.y)
        {
            *CloseGame = true;
            return;
        }
        CollisionNode = CollisionNode->next;
    }

    if (nextX >= -1 && nextX < MAX_COLUMNS + 1 && nextY >= -1 && nextY < MAX_ROWS + 1)
    {
        Matrix[nextY][nextX] = 1;
        pos->x = nextX;
        pos->y = nextY;
    }

    Tbody *currentNode = head->next;
    while (currentNode != NULL)
    {
        int tempNextX = currentNode->pos.x;
        int tempNextY = currentNode->pos.y;
        currentNode->pos.x = tempX;
        currentNode->pos.y = tempY;
        tempX = tempNextX;
        tempY = tempNextY;
        currentNode = currentNode->next;
    }
    timer += GetFrameTime();

    timer = 0;

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            if (Matrix[i][j] != 2)
                Matrix[i][j] = 0;
        }
    }
}


int Detected(int KeyPresed)
{
    if (KeyPresed == KEY_D)
        return 4;
    if (KeyPresed == KEY_A)
        return 3;
    if (KeyPresed == KEY_W)
        return 2;
    if (KeyPresed == KEY_S)
        return 1;
}

void GameOver(int points)
{
    static int Record = 0;
    Rectangle BackToMenu = {685, 502, 558, 235};
    Vector2 MousePosition;
    Color font = {50, 60, 57, 255};
    Color purp = {105, 0, 105, 255};
    bool MouseBackToMenu = false;
    bool CloseGame = false;

    if (points > Record)
        Record = points;

    while (!WindowShouldClose() && !CloseGame)
    {
        BeginDrawing();
        ClearBackground(LIME);
        BackRec();
        DrawText(TextFormat("Points: %i", points), 750, 250, 100, font);
        DrawText(TextFormat("Record: %i", Record), 720, 350, 100, font);

        DrawRectangleRec(BackToMenu, DARKPURPLE);

        MousePosition = GetMousePosition();
        MouseBackToMenu = CheckCollisionPointRec(MousePosition, BackToMenu);

        if (MouseBackToMenu)
        {
            DrawRectangleLines(BackToMenu.x, BackToMenu.y, BackToMenu.width, BackToMenu.height, BLACK);
            DrawRectangleRec(BackToMenu, purp );
        }
        DrawText("Game Over", 575, 75, 150, font);

        DrawText("Back to", BackToMenu.x + 75, BackToMenu.y + 30, 100, font);
        DrawText("Menu", BackToMenu.x + 150, BackToMenu.y + 130, 100, font);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (MouseBackToMenu)
                CloseGame = true;
        }
        EndDrawing();
    }
}
