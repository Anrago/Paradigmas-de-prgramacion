#include "Snake.h"
#include <stdio.h>

#define MAX_COLUMNS 41
#define MAX_ROWS 20
#define CELL_SIZE 40
#define PADDING 5
#define MOVE_SPEED 0.5f

// void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void DrawBody(int startX, int startY, Tbody *head);
void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS], int keyPressed, bool *CloseGame);
int Detected(int KeyPresed);

void Game();

int main(void)
{
    InitWindow(1920, 1080, "Snake");
    Vector2 Mouse;
    Rectangle Start = {960, 540, 250, 140};
    Rectangle Close = {450, 889, 100, 100};
    bool MouseStartGame = 0;
    bool MouseCloseGame = 0;
    bool CloseGame = 0;
    while (!WindowShouldClose() && !CloseGame)
    {
        BeginDrawing();
        Mouse = GetMousePosition();

        DrawRectangleRec(Start, BLUE);
        DrawRectangleRec(Close, RED);
        MouseStartGame = CheckCollisionPointRec(Mouse, Start);
        MouseCloseGame = CheckCollisionPointRec(Mouse, Close);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (MouseStartGame)
                Game();

            if (MouseCloseGame)
                CloseGame = 1;
        }

        EndDrawing();
    }

    return 0;
}

//------------------------Funciones------------------------------

void Game()
{
    int screenWidth = 1920;
    int screenHeight = 1080;
    Vector2 Apple = {GetRandomValue(1, MAX_COLUMNS - 1), GetRandomValue(1, MAX_ROWS - 1)};

    Snake *snake = InitSnake((Vector2){11, 9});

    int startX = 40;
    int startY = 80;
    int Matrix[MAX_ROWS][MAX_COLUMNS];
    int detctKeyboar = 0;
    int temp;
    bool CloseGame = false;
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
    while (!WindowShouldClose() && !CloseGame)
    {
        Tbody *currentNode = snake->head->next;

        BeginDrawing();
        DrawText("SNAKE", (screenWidth / 2) - 100, 30, 50, BLUE);

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

    CloseWindow();
    FreeSnake(snake);
}

void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            int cellX = posx + j * (CELL_SIZE + PADDING);
            int cellY = posy + i * (CELL_SIZE + PADDING);
            Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
            if (Matrix[i][j] == 0)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, SKYBLUE);
            if (Matrix[i][j] == 2)
                DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, ORANGE);
        }
    }
}

void DrawBody(int startX, int startY, Tbody *head)
{
    int iter = 0;
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
        if (iter % 2 == 0 && iter != 0)
            DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, WHITE);
        if (iter % 2 != 0 && iter != 1)
            DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, DARKGRAY);
        iter++;

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
            *CloseGame = true; // Colisión detectada, finalizar el juego
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
