#include "Snake.h"

#define MAX_COLUMNS 41
#define MAX_ROWS 20
#define CELL_SIZE 40
#define PADDING 5
#define UPDATE_INTERVAL 0.2f

void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void DrawBody(int startX, int startY, Tbody *head);
void DrawSnake(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);
void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS], int keyPressed);

int main(void)
{
    int screenWidth = 1920;
    int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Snake");
    Vector2 Apple = {GetRandomValue(1, MAX_COLUMNS - 1), GetRandomValue(1, MAX_ROWS - 1)};
    float elapsedTime = 0.0f;

    Snake *snake = InitSnake((Vector2){11, 9});

    int startX = 40;
    int startY = 80;
    int Matrix[MAX_ROWS][MAX_COLUMNS];

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
        float deltaTime = GetFrameTime();
        elapsedTime += deltaTime;

        BeginDrawing();
        DrawText("SNAKE", (screenWidth / 2) - 100, 30, 50, BLUE);

        DrawText(TextFormat("Points: %i", snake->points), 100, 40, 30, BLUE);

        DrawSnake(startX, startY, Matrix);

        if (CheckCollisionRecs((Rectangle){snake->head->pos.x * (CELL_SIZE + PADDING) + startX, snake->head->pos.y * (CELL_SIZE + PADDING) + startY, CELL_SIZE, CELL_SIZE}, (Rectangle){Apple.x * (CELL_SIZE + PADDING) + startX, Apple.y * (CELL_SIZE + PADDING) + startY, CELL_SIZE, CELL_SIZE}))
        {
            Matrix[(int)Apple.y][(int)Apple.x] = 0;
            Apple.x = GetRandomValue(0, MAX_COLUMNS);
            Apple.y = GetRandomValue(0, MAX_ROWS);
            Matrix[(int)Apple.y][(int)Apple.x] = 2;
            AddBody(snake, (Vector2){snake->head->pos.x, snake->head->pos.y});
            Matrix[(int)snake->head->pos.y][(int)snake->head->pos.x - 1] = 1;
            snake->points++;
        }
        DrawBody(startX, startY, snake->head);

        if (elapsedTime >= UPDATE_INTERVAL)
        {
            elapsedTime = 0.0f;
            MoveSnake(&snake->head->pos, snake->head, Matrix, GetKeyPressed());
        }

        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S))
        {
            MoveSnake(&snake->head->pos, snake->head, Matrix, GetKeyPressed());
        }

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

    if (keyPressed == KEY_D)
    {
        nextX++;
    }
    else if (keyPressed == KEY_A)
    {
        nextX--;
    }
    else if (keyPressed == KEY_W)
    {
        nextY--;
    }
    else if (keyPressed == KEY_S)
    {
        nextY++;
    }

    // Verificar si la siguiente posición está dentro de los límites de la matriz
    if (nextX >= 0 && nextX < MAX_COLUMNS && nextY >= 0 && nextY < MAX_ROWS)
    {
        // Actualizar la posición de la serpiente solo si la siguiente posición es válida
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

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            if (Matrix[i][j] != 2)
                Matrix[i][j] = 0;
        }
    }
}
