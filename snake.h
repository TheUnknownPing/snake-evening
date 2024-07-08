#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>

#define HEIGHT 16
#define WIDTH 16

#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_RIGHT 'a'
#define MOVE_LEFT 'd'

typedef struct {
   int x, y;
} vec2;

typedef struct snake_segment {
   struct snake_segment* next;
   vec2 position;
} snake_segment;

typedef struct {
   snake_segment* head;
   vec2 direction;
   int score;
} snake;

typedef struct {
   vec2 position;
} fruit;

void addSnakeSegment(snake* s);
void moveSnake(snake* s);

#endif
