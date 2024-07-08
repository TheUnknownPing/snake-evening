#include "snake.h"

struct termios originalTerm, modifiedTerm;

void setupTerminal() {
    tcgetattr(STDIN_FILENO, &originalTerm);
    modifiedTerm = originalTerm;
    modifiedTerm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &modifiedTerm);

}

void resetTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTerm);
}

void* inputHandle(void* argSnake) {
    snake* s = (snake*)argSnake;
    char input;
    while(1) {
        if (read(STDIN_FILENO, &input, 1)) {
            switch (input)
            {
            case MOVE_UP:
                s->direction = (s->direction.y == 1) ? (vec2){0, 1} : (vec2){0, -1};
                break;
            case MOVE_DOWN:
                s->direction = (s->direction.y == -1) ? (vec2){0, -1} : (vec2){0, 1};
                break;
            case MOVE_RIGHT:
                s->direction = (s->direction.x == 1) ? (vec2){1, 0} : (vec2){-1, 0};
                break;
            case MOVE_LEFT:
                s->direction = (s->direction.x == -1) ? (vec2){-1, 0} : (vec2){1, 0};
                break;
            default:
                break;
            }
        }
    }

}

void addSnakeSegment(snake* s) {
    snake_segment* current = s->head;
    while (current->next != NULL)
        current = current->next;
    current->next = malloc(sizeof(snake_segment));
    current->next->position = (vec2){current->position.x-s->direction.x, current->position.y-s->direction.y};
}

void moveSnake(snake* s) {
    snake_segment* current = s->head;
    vec2 oldPosition, newPosition = {current->position.x, current->position.y};
    current->position.x += s->direction.x;
    current->position.y += s->direction.y;
    while (current->next != NULL) {
        current = current->next;
        oldPosition = current->position;
        current->position = newPosition;
        newPosition = oldPosition;
    }
}

void checkFruitCollision(snake* s, fruit* f) {
    if ((s->head->position.x == f->position.x) && (s->head->position.y == f->position.y)) {
        f->position = (vec2){rand() % WIDTH, rand() % HEIGHT};
        s->score++;
        addSnakeSegment(s);
    }
}

int checkWallCollision(snake* s) {
    if (s->head->position.x < 0 || s->head->position.x > WIDTH-1) 
        return 1;
    if (s->head->position.y < 0 || s->head->position.y > HEIGHT-1)
        return 1;
    return 0;
}

int checkSnakeCollision(snake* s) {
    snake_segment* current = s->head;
    while (current->next != NULL) {
        if (current->next->position.x == s->head->position.x) {
            if (current->next->position.y == s->head->position.y)
                return 1;
        }
        current = current->next;
    }
    return 0;

}

void drawGame(snake* s, fruit* f) {
    system("clear");

    char image[WIDTH][HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[j][i] = '.';
        }
    }

    snake_segment* current = s->head;
    image[current->position.x][current->position.y] = '&';
    while (current->next != NULL) {
        current = current->next;
        image[current->position.x][current->position.y] = '#';
    }

    image[f->position.x][f->position.y] = '%';

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(' ');
            putchar(image[j][i]);
            putchar(' ');
        }
        putchar('\n');
    }
}

snake mySnake = {NULL, {0,0}, 0};
fruit myFruit = {{WIDTH/2 + 2, HEIGHT/2}};

int main(int argc, char** argv) {
    setupTerminal();

    mySnake.head = malloc(sizeof(snake_segment));
    mySnake.head->position = (vec2){WIDTH/2 - 2, HEIGHT/2};
    mySnake.direction.x = 1;
    
    pthread_t thread;
    pthread_create(&thread, NULL, inputHandle, (void*)&mySnake);

    for (;;) {
        moveSnake(&mySnake);
        if (checkWallCollision(&mySnake)) {
            break;
        }
        checkFruitCollision(&mySnake, &myFruit);
        if (checkSnakeCollision(&mySnake)) {
            break;
        }
        drawGame(&mySnake, &myFruit);
        usleep(100000);
    }

    printf("Game over! Score: %d\n", mySnake.score);

    resetTerminal();
    return 0;
}
