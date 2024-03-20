#include "Snake.h"
#include <stdio.h>

#define MAX_COLUMNS 41
#define MAX_ROWS 20
#define CELL_SIZE 40
#define PADDING 5
#define MOVE_SPEED 0.5f

// void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void DrawBody(int startX, int startY, Tbody *head);
void DrawSnake(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS], int keyPressed);
int Detected(int KeyPresed);

int main(void)
{
    int screenWidth = 1920;
    int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Snake");
    Vector2 Apple = {GetRandomValue(1, MAX_COLUMNS - 1), GetRandomValue(1, MAX_ROWS - 1)};

    Snake *snake = InitSnake((Vector2){11, 9});

    int startX = 40;
    int startY = 80;
    int Matrix[MAX_ROWS][MAX_COLUMNS];
    int detctKeyboar = 0;
    int temp;
    SetTargetFPS(60);

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            Matrix[i][j] = 0;
        }
    }

    Matrix[(int)Apple.y][(int)Apple.x] = 2;
    Matrix[(int)snake->head->pos.y][(int)snake->head->pos.x] = 1;
    while (!WindowShouldClose())
    {
        Tbody *currentNode = snake->head;

        // float elapsedTime = GetFrameTime();

        BeginDrawing();
        DrawText("SNAKE", (screenWidth / 2) - 100, 30, 50, BLUE);

        DrawText(TextFormat("Points: %i", snake->points), 100, 40, 30, BLUE);

        DrawSnake(startX, startY, Matrix);

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

        if (snake->head->pos.x == 0 || snake->head->pos.x == MAX_COLUMNS-1|| snake->head->pos.y == 0 || snake->head->pos.y == MAX_ROWS-1)
            CloseWindow();
        
        while(currentNode->next!=NULL)
        {
            if (CheckCollisionRecs((Rectangle){snake->head->pos.x * (CELL_SIZE + PADDING) + startX, snake->head->pos.y * (CELL_SIZE + PADDING) + startY, CELL_SIZE, CELL_SIZE}, (Rectangle){currentNode->next->pos.x * (CELL_SIZE + PADDING) + startX-40, currentNode->next->pos.y * (CELL_SIZE + PADDING) + startY+40, CELL_SIZE, CELL_SIZE}))
            {
                CloseWindow();
            }
            currentNode = currentNode->next;
        }


        DrawBody(startX, startY, snake->head);

        int keyPresed = GetKeyPressed();

        if (keyPresed != 0)
        {
            detctKeyboar = Detected(keyPresed);
            MoveSnake(&snake->head->pos, snake->head, Matrix, detctKeyboar);
        }
        MoveSnake(&snake->head->pos, snake->head, Matrix, detctKeyboar);

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
    FreeSnake(snake);
    return 0;
}

void DrawSnake(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            int cellX = posx + j * (CELL_SIZE + PADDING);
            int cellY = posy + i * (CELL_SIZE + PADDING);
            Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
            if (Matrix[i][j] == 0)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, WHITE);
            if (Matrix[i][j] == 1)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, GREEN);
            if (Matrix[i][j] == 2)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, RED);
        }
    }
}

void DrawBody(int startX, int startY, Tbody *head)
{
    Tbody *currentNode = head;
    while (currentNode != NULL)
    {
        int cellX = startX + currentNode->pos.x * (CELL_SIZE + PADDING);
        int cellY = startY + currentNode->pos.y * (CELL_SIZE + PADDING);
        Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
        DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, GREEN);

        currentNode = currentNode->next; // Avanzamos al siguiente nodo
    }
}

void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS], int keyPressed)
{
    int tempX = pos->x;
    int tempY = pos->y;
    int nextX = tempX;
    int nextY = tempY;
    static int lastKeyPressed = 0;
    static float timer = 0;
    timer += GetFrameTime();
    if (timer < MOVE_SPEED * 0.2f)
        return;

    if (keyPressed == 4 && lastKeyPressed != 3)
    {
        nextX++;
        lastKeyPressed = 4;
    }
    if (keyPressed == 3 && lastKeyPressed != 4)
    {
        nextX--;
        lastKeyPressed = 3;
    }
    if (keyPressed == 2 && lastKeyPressed != 1)
    {
        nextY--;
        lastKeyPressed = 2;
    }
    if (keyPressed == 1 && lastKeyPressed != 2)
    {
        nextY++;
        lastKeyPressed = 1;
    }

    if (nextX >= 0 && nextX < MAX_COLUMNS && nextY >= 0 && nextY < MAX_ROWS)
    {

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
