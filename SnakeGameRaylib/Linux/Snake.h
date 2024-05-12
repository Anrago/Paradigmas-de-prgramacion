/* 
JUEGO HECHO POR: ANTONIO RAMOS GONZALEZ
SNAKE CON LISTAS ENLAZADAS Y USO DE RAYLIB
*/

//Incluimos bibliotecas "stdlib y raylib"
#include <stdlib.h>
#include "raylib.h"

//Definicion dato Tbody
typedef struct _body{
    Vector2 pos;
    struct _body *next;
} Tbody;

//Definicion de cabeza y puntaje
typedef struct{
    Tbody *head;
    int points;
} Snake;

//Creacion de nuevo cuerpo
Tbody *CreateBody(Vector2 position){
    // Reservar memoria para el nuevo nodo
    Tbody *body = (Tbody *)malloc(sizeof(Tbody));
    // Verificar si se pudo reservar memoria correctamente
    if (body != NULL){
        //Asignamos posicion a nuevo nodo
        body->pos = position;
        body->next = NULL;
    }
    return body;
}

//Aniade nuevo cuerpo a serpiente
void AddBody(Snake *snake, Vector2 position)
{
    // Crear un nuevo nodo para el cuerpo
    Tbody *newNode = CreateBody(position);

    // Verificar si se pudo crear el nuevo nodo
    if (newNode == NULL)
    {
        // Manejar el error de memoria insuficiente
        return;
    }

    // Buscar el último nodo en la serpiente
    Tbody *currentNode = snake->head;
    while (currentNode->next != NULL){
        currentNode = currentNode->next;
    }

    // Asignar el nuevo nodo al final de la serpiente
    currentNode->next = newNode;
}

//Libera memoria de cuerpo
void FreeBody(Tbody *node){
    
    //Libera cuerpo
    free(node);
}

//Creacion de cabeza de la serpiente
Snake *InitSnake(Vector2 position){

    // Reservar memoria para la cabeza
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    //Verifica que se haya reservado la memoria correctamente
    if (snake != NULL){
        //Crea la cabeza de la serpiente
        snake->head = CreateBody(position);
        //Inicializa los puntos en 0
        snake->points = 0;
    }
    return snake;
}

//Libera memoria de la serpiente
void FreeSnake(Snake *snake){
    //Guarda direccion de la serpiente en nuevo nodo
    Tbody *current = snake->head;
    //Verifica que el nodo actual no sea el ultimo
    while (current != NULL)
    {
        //Guerdamos la poscicion actual en next
        Tbody *next = current->next;
        //Liberamos el nodo
        FreeBody(current);

        //Mover al siguiente nodo
        current = next;
    }
    //Liberamos memoria de la serpiente
    free(snake);
}
