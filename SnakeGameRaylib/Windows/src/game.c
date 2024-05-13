/* 
JUEGO HECHO POR: ANTONIO RAMOS GONZALEZ
SNAKE CON LISTAS ENLAZADAS Y USO DE RAYLIB
*/

#include "Snake.h" //Incluimos biblioteca de snake 


#define MAX_COLUMNS 41 //Nuemero de columnas
#define MAX_ROWS 20 //Numero de filas
#define CELL_SIZE 40 //Tamanio de las celdas de la matriz
#define PADDING 5 //Separacion entre celdas
#define MOVE_SPEED 0.5f //Velocidad de la serpiente
#define WIDTH 1920 //Ancho pantalla
#define HEIGHT 1040//Largo pantalla


void DrawBody(int startX, int startY, Tbody *head); //Dibujar cuerpo  de serpiente
void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]);//Dibujar matriz de juego
void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS],
               int keyPressed, bool *CloseGame); //Mover a serpiente
void BackRec();//Pintar fondo de menu
void GameOver(int points);//Pantalla de fin del juego
void Game();//Funcion principal de inicio de juego
int Detected(int KeyPresed);//Detecta la tecla presionada

int main(void) {
    // Declaración de variables
    Vector2 Mouse;
    Rectangle Start = {685, 454, 558, 155};
    Rectangle Close = {685, 687, 558, 155};
    Color DARKRED = {139, 0, 0, 255};
    Color font = {50, 60, 57, 255};
    bool MouseStartGame = false;
    bool MouseCloseGame = false;
    bool CloseGame = false;

    // Configuración inicial de la ventana
    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "Snake");

    // Bucle principal del juego
    while (!CloseGame && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIME); // Limpiar el fondo
        Mouse = GetMousePosition(); // Obtener la posición del ratón
        BackRec(); // Dibujar el fondo

        // Dibujar el título y los botones "Start" y "Close"
        DrawText("SNAKE", (WIDTH / 2) - 325, 150, 200, font);
        DrawRectangleRec(Start, BLUE);
        DrawRectangleRec(Close, RED);

        // Verificar si el ratón está sobre los botones "Start" y "Close"
        MouseStartGame = CheckCollisionPointRec(Mouse, Start);
        MouseCloseGame = CheckCollisionPointRec(Mouse, Close);

        // Resaltar el botón "Start" si el ratón está sobre él
        if (MouseStartGame) {
            DrawRectangleLines(Start.x, Start.y, Start.width, Start.height, BLACK);
            DrawRectangleRec(Start, DARKBLUE);
        }

        // Resaltar el botón "Close" si el ratón está sobre él
        if (MouseCloseGame) {
            DrawRectangleLines(Close.x, Close.y, Close.width, Close.height, BLACK);
            DrawRectangleRec(Close, DARKRED);
        }

        // Dibujar los textos "Start" y "Close"
        DrawText("Start", Start.x + 125, Start.y + 30, 100, font);
        DrawText("Close", Close.x + 125, Close.y + 30, 100, font);

        // Verificar si se hace clic en los botones
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (MouseStartGame)
                Game(); // Iniciar el juego si se hace clic en "Start"
            if (MouseCloseGame)
                CloseGame = true; // Cerrar el juego si se hace clic en "Close"
        }

        // Dibujar información adicional
        DrawText("Create by: Antonio Ramos Gonzalez", 1410, 1000, 20, GREEN);

        EndDrawing();
    }

    // Cerrar la ventana y salir del programa
    CloseWindow();
    return 0;
}

//------------------------Funciones------------------------------
void BackRec() {
    Rectangle leftBorder = {0, 0, 150, HEIGHT}; // Borde izquierdo
    Rectangle rightBorder = {WIDTH - 150, 0, 150, HEIGHT}; // Borde derecho
    Rectangle topBorder = {0, 0, WIDTH, 70}; // Borde superior
    Rectangle bottomBorder = {0, HEIGHT - 70, WIDTH, 70}; // Borde inferior

    // Dibuja los bordes
    DrawRectangleRec(leftBorder, DARKGREEN);
    DrawRectangleRec(rightBorder, DARKGREEN);
    DrawRectangleRec(topBorder, DARKGREEN);
    DrawRectangleRec(bottomBorder, DARKGREEN);
}

void Game(){
    //Declaracion de variables
    Vector2 Apple = {25, 9};
    Snake *snake = InitSnake((Vector2){11, 9});
    int startX = 40;
    int startY = 80;
    int Matrix[MAX_ROWS][MAX_COLUMNS];
    int detctKeyboar = 4;
    int temp;
    bool CloseGame = false;

    //Ciclo que limpia la matriz
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            Matrix[i][j] = 0;
        }
    }
    //Se indica la posicion de las manzanas y la serpiente
    Matrix[(int)Apple.y][(int)Apple.x] = 2;
    Matrix[(int)snake->head->pos.y][(int)snake->head->pos.x] = 1;
    //Inicia ciclo de juego
    while (!CloseGame && !WindowShouldClose()){
        //Dibujamos la matriz, el titulo y los puntos
        BeginDrawing();
        DrawText("SNAKE", (WIDTH / 2) - 100, 30, 50, BLUE);
        DrawText(TextFormat("Points: %i", snake->points), 100, 40, 30, BLUE);
        DrawMatrix(startX, startY, Matrix);

        //Checamos colision de la cabeza de la serpiente con la manzana
        if (CheckCollisionRecs((Rectangle){snake->head->pos.x * (CELL_SIZE+
            PADDING) + startX, snake->head->pos.y * (CELL_SIZE + PADDING) +
            startY, CELL_SIZE, CELL_SIZE}, (Rectangle){Apple.x * (CELL_SIZE
            + PADDING) + startX, Apple.y * (CELL_SIZE + PADDING) + startY, 
            CELL_SIZE, CELL_SIZE})){
            
            //Verificamos la posicion de la serpiente
            Tbody *Nodo=snake->head;
            //Eliminamos a la manzana de la matriz
            Matrix[(int)Apple.y][(int)Apple.x] = 0;
            while(Nodo!=NULL){
                //Le damos valor 1 para que las manzanas no se generen en su posicion
                Matrix[(int)Nodo->pos.y][(int)Nodo->pos.x]=1;
                Nodo=Nodo->next;
            }
            FreeBody(Nodo);

            //Generamos una nueva manzana en una posicion random
            do{
                Apple.x = GetRandomValue(1, MAX_COLUMNS - 1);
                Apple.y = GetRandomValue(1, MAX_ROWS - 1);
            } while (Matrix[(int)Apple.y][(int)Apple.x] != 0);

            //En la nueva posicion dibujamos manzana
            Matrix[(int)Apple.y][(int)Apple.x] = 2;
            
            //Aniadimos un nuevo cuerpo a la serpiente y sumamos puntos
            AddBody(snake, (Vector2){snake->head->pos.x, snake->head->pos.y});
            snake->points++;
        }
        
        //Comprobamos que la serpiente se encuentre en los limites de la matriz
        if (snake->head->pos.x == -1 || snake->head->pos.x == MAX_COLUMNS || 
            snake->head->pos.y == -1 || snake->head->pos.y == MAX_ROWS)
            CloseGame = true;

        //Dibujamos cuerpo
        DrawBody(startX, startY, snake->head);

        //Obtener tecla y mover a la serpiente
        int keyPresed = GetKeyPressed();
        if (keyPresed != 0){
            detctKeyboar = Detected(keyPresed);
            MoveSnake(&snake->head->pos, snake->head, Matrix, detctKeyboar,
                     &CloseGame);
        }
        MoveSnake(&snake->head->pos, snake->head, Matrix, detctKeyboar, 
                  &CloseGame);
        //Limpiamos el fondo
        ClearBackground(BLACK);
        EndDrawing();
    }
    //Movemos a la pantalla de game over y liberamos memoria
    GameOver(snake->points);
    FreeSnake(snake);
}


void DrawMatrix(int posx, int posy, int Matrix[MAX_ROWS][MAX_COLUMNS]) {
    Color DARKRED = {192, 0, 0, 255};
    
    // Ciclo para recorrer filas
    for (int i = 0; i < MAX_ROWS; i++) {
        // Ciclo para recorrer columnas
        for (int j = 0; j < MAX_COLUMNS; j++) {
            // Calcula las coordenadas de la celda
            int cellX = posx + j * (CELL_SIZE + PADDING);
            int cellY = posy + i * (CELL_SIZE + PADDING);
            
            // Define el rectángulo de la celda
            Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
            
            // Verifica el valor de la matriz en la celda
            switch (Matrix[i][j]) {
                case 0: // Si es 0, dibuja con DARKGREEN
                    DrawRectangle(cellRect.x, cellRect.y, cellRect.width,
                                  cellRect.height, DARKGREEN);
                    break;
                case 2: // Si es 2, dibuja con DARKRED
                    DrawRectangle(cellRect.x, cellRect.y, cellRect.width,
                                  cellRect.height, DARKRED);
                    break;
                default: // Si no es ninguno de los anteriores, no dibuja nada
                    break;
            }
        }
    }
}
void DrawBody(int startX, int startY, Tbody *head) {
    bool isFirst = true;
    Color bodyColor = {100, 156, 0, 255}; // Color del cuerpo
    Tbody *currentNode = head;
    
    // Ciclo para recorrer los nodos del cuerpo
    while (currentNode != NULL) {
        // Calcula las coordenadas de la celda
        int cellX = startX + currentNode->pos.x * (CELL_SIZE + PADDING);
        int cellY = startY + currentNode->pos.y * (CELL_SIZE + PADDING);
        
        // Define el rectángulo de la celda
        Rectangle cellRect = {cellX, cellY, CELL_SIZE, CELL_SIZE};
        
        // Dibuja la celda
        if (isFirst) { // Dibuja la primera celda en negro
            DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height,
                          BLACK);
            isFirst = false;
        } else { // Dibuja las demás celdas con el color del cuerpo
            DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height,
                          bodyColor);
        }

        // Avanza al siguiente nodo del cuerpo
        currentNode = currentNode->next;
    }
}

void MoveSnake(Vector2 *pos, Tbody *head, int Matrix[MAX_ROWS][MAX_COLUMNS],
               int keyPressed, bool *CloseGame) {
    static int currentDirection = 4; // Dirección actual (4: Derecha, 3: Izquierda, 2: Arriba, 1: Abajo)
    static float timer = 0;
    int tempX = pos->x;
    int tempY = pos->y;
    int nextX = tempX;
    int nextY = tempY;

    // Incrementa el temporizador
    timer += GetFrameTime();

    // Si no ha pasado suficiente tiempo, regresa
    if (timer < MOVE_SPEED * 0.2f)
        return;

    // Actualiza la dirección actual según la tecla presionada
    switch (keyPressed) {
        case 4:
            if (currentDirection != 3)
                currentDirection = 4; // Derecha
            break;
        case 3:
            if (currentDirection != 4)
                currentDirection = 3; // Izquierda
            break;
        case 2:
            if (currentDirection != 1)
                currentDirection = 2; // Arriba
            break;
        case 1:
            if (currentDirection != 2)
                currentDirection = 1; // Abajo
            break;
    }

    // Mueve la serpiente según la dirección actual
    if (currentDirection == 4)
        nextX++;
    else if (currentDirection == 3)
        nextX--;
    else if (currentDirection == 2)
        nextY--;
    else if (currentDirection == 1)
        nextY++;

    // Comprueba colisión con la serpiente misma
    Tbody *CollisionNode = head->next;
    while (CollisionNode != NULL) {
        if (nextX == CollisionNode->pos.x && nextY == CollisionNode->pos.y) {
            *CloseGame = true;
            return;
        }
        CollisionNode = CollisionNode->next;
    }

    // Mueve la cabeza de la serpiente
    if (nextX >= -1 && nextX < MAX_COLUMNS+1 && nextY >= -1 && nextY < MAX_ROWS+1) {
        Matrix[nextY][nextX] = 1;
        pos->x = nextX;
        pos->y = nextY;
    }

    // Mueve el cuerpo de la serpiente
    Tbody *currentNode = head->next;
    while (currentNode != NULL) {
        int tempNextX = currentNode->pos.x;
        int tempNextY = currentNode->pos.y;
        currentNode->pos.x = tempX;
        currentNode->pos.y = tempY;
        tempX = tempNextX;
        tempY = tempNextY;
        currentNode = currentNode->next;
    }

    // Reinicia el temporizador
    timer = 0;

    // Borra el rastro de la serpiente en la matriz
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
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

void GameOver(int points) {
    static int Record = 0; // Record del juego
    Rectangle BackToMenu = {685, 502, 558, 235}; // Área para volver al menú
    Vector2 MousePosition; // Posición del ratón
    Color font = {50, 60, 57, 255}; // Color del texto
    Color purp = {105, 0, 105, 255}; // Color púrpura
    bool MouseBackToMenu = false; // Indica si el ratón está sobre "Back to Menu"
    bool CloseGame = false; // Indica si se debe cerrar el juego

    // Actualiza el record si es necesario
    if (points > Record)
        Record = points;

    // Mientras no se cierre la ventana y no se cierre el juego
    while (!WindowShouldClose() && !CloseGame) {
        BeginDrawing();
        ClearBackground(LIME); // Limpia el fondo

        // Dibuja el fondo
        BackRec();

        // Dibuja los puntos y el record
        DrawText(TextFormat("Points: %i", points), 750, 250, 100, font);
        DrawText(TextFormat("Record: %i", Record), 720, 350, 100, font);

        // Dibuja el botón "Back to Menu"
        DrawRectangleRec(BackToMenu, DARKPURPLE);

        // Verifica si el ratón está sobre el botón "Back to Menu"
        MousePosition = GetMousePosition();
        MouseBackToMenu = CheckCollisionPointRec(MousePosition, BackToMenu);

        // Resalta el botón si el ratón está sobre él
        if (MouseBackToMenu) {
            DrawRectangleLines(BackToMenu.x, BackToMenu.y, BackToMenu.width,
                               BackToMenu.height, BLACK);
            DrawRectangleRec(BackToMenu, purp);
        }

        // Dibuja el texto "Game Over" y "Back to Menu"
        DrawText("Game Over", 575, 75, 150, font);
        DrawText("Back to", BackToMenu.x + 75, BackToMenu.y + 30, 100, font);
        DrawText("Menu", BackToMenu.x + 150, BackToMenu.y + 130, 100, font);

        // Verifica si se hace clic en el botón "Back to Menu"
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (MouseBackToMenu)
                CloseGame = true; // Cierra el juego si se hace clic en el botón "Back to Menu"
        }

        EndDrawing();
    }
}
