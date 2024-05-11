#include <stdlib.h>
#include "raylib.h"

typedef struct _body {
    Vector2 pos;
    struct _body *next;
} Tbody;

typedef struct {
    Tbody *head;
    int points;
} Snake;

Tbody *CreateBody(Vector2 position)
{
    Tbody *body = (Tbody *)malloc(sizeof(Tbody));
    if (body != NULL) {
        body->pos = position;
        body->next = NULL;
    }
    return body;
}
 
 
void AddBody(Snake *snake, Vector2 position)
{
    Tbody *newNode = CreateBody(position);
    if (newNode == NULL)
    {
        return;
    }

    Tbody *currentNode = snake->head;
    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
}

void FreeBody(Tbody *node) 
{
    free(node);
}

Snake *InitSnake(Vector2 position) 
{
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    if (snake != NULL) {
        snake->head = CreateBody(position);
        snake->points = 0;
    }
    return snake;
}

void FreeSnake(Snake *snake) {
    Tbody *current = snake->head;
    while (current != NULL) {
        Tbody *next = current->next;
        FreeBody(current);
        current = next;
    }
    free(snake);
}
