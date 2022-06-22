#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    NORMAL_EXIT = 0,
    BAD_EXIT = 1,
    SNAKE_OUT_OF_BOUNDS = 2
} ExitStatus;

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef enum {
    ALIVE,
    DEAD
} SnakeState;

typedef struct {
    int x_pos;
    int y_pos;
} Coordinate;

typedef struct Position {
    Coordinate coord;
    int ref;
    struct Position* next;
} Position;

typedef struct {
    int length;
    Position* head_pos;
} Snake;

typedef struct {
    int x_len;
    int y_len;
    Snake* snake;
} board;

Snake* init_snake(int x_start, int y_start, Direction facing, 
		int length, int x_max, int y_max) {
    Snake* snake = malloc(sizeof(Snake));
    snake->length = length;
    int x_pos = x_start;
    int y_pos = y_start;
    Position* pos = snake->head_pos;
    for (int i = 0; i < length; i++){
        if ((x_pos < 0 ) || (y_pos < 0) || 
			((x_pos > (x_max - 1)) || 
			 (y_pos > (y_max - 1)))) {
            pos = snake->head_pos;
	    Position* next = pos->next;
	    while (pos != NULL) {
                free(pos);
		pos = next;
		next = pos->next;
	    }
            free(snake);	    
            return NULL;
        }
        pos = malloc(sizeof(Position));
        pos->ref = i;
        Coordinate coord = {x_pos, y_pos};
        pos->coord = coord;
	printf("(%d, %d)\n", coord.x_pos, coord.y_pos);
        switch (facing) {
            case NORTH:
                y_pos = y_pos + 1;
                break;
            case SOUTH:
                y_pos = y_pos - 1;
                break;
            case EAST:
                x_pos = x_pos - 1;
                break;
            case WEST:
                x_pos = x_pos + 1;
                break;
        }
        pos = pos->next;
	pos = NULL;
    }
    return snake;
}

SnakeState move_forward(Snake* snake, Direction facing, 
        bool growth) {
   SnakeState state = ALIVE;
   Position* current = snake->head_pos;
   Position* next = current->next;
   Position* end = current;
   Position* previous;
   if (!growth) {
       //while(next != NULL) {
	   //previous = end;
           //end = next;
           //next = end->next;   
       //}
       //free(end);
       //previous->next = NULL;
   }
   Position* new;
   switch (facing) {
        case NORTH:
            new->coord.x_pos = current->coord.x_pos - 1;
	    break;
        case SOUTH:
	    new->coord.x_pos = current->coord.x_pos + 1;
	    break;
        case EAST:
	    new->coord.y_pos = current->coord.y_pos + 1;
            break;
        case WEST:
	    new->coord.y_pos = current->coord.y_pos - 1;
            break;
   }
   new->next = current;
   snake->head_pos = new;
   return state;   
}

int main(int argc, char** argv){
    ExitStatus status = NORMAL_EXIT;
    init_snake(3, 4, WEST, 8, 10, 10);
    return status;
}
