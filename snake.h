#ifndef SNAKE_H
#define SNAKE_H

#include <curses.h>
#include <stdbool.h>

/* Store the coordinate of each node of the snake body */

typedef struct {
    int y, x;
} Coordinate;

/* Each node in the snake will have a direction, can be
 * either up, down, left or right
 */

typedef enum direction { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct node {
    Direction bodyDirection;
    Coordinate bodyCoordinate;
    struct node * next;
} bodyNode;

/* Write prototypes for manipulating the snake.
 *
 * The actions that must be done are as follows:
 *
 * 1. Take the tail of the snake.
 * 2. Overwrite its coordinates with whitespace
 * 3. Advance it to the next node
 * 4. Free the node that was previously the tail
 * 5. Allocate a new node for the head
 * 6. Make its coordinates in line with the direction
 *    of the previous node
 * 7. Make the head->next point to this node
 * 8. Make head point to this node
 * 
 */

void clear_coordinate(WINDOW * Win, Coordinate * c);
void advance_tail(WINDOW * Win);
void advance_head(WINDOW * Win);
void increment_coordinate(Coordinate * c, Direction d);

/* In order to make the snake living and breathing, he needs to
 * eat and grow. Write prototypes that do the following:
 *
 * 1. Generate a coordinate for food.
 * 2. Grow the snake by one */

void generate_coordinate(WINDOW * Win, Coordinate * c);
void push_food(void);

/* In order to test whether or not the coordinates of the head
 * are valid, do the following:
 *
 * 1. Test if the coordinates are off the game board
 * 2. Walk the snake to see if any of the nodes have
 *    matching coordinates
 * 3. If any of these conditions are true, end the game.
 *
 */

bool find_coordinate(Coordinate c);
void check_coordinate(WINDOW * Win, Coordinate c);

void gameover(WINDOW * Win);

#endif
