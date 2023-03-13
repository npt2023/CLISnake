#include "snake.h"
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern bodyNode * head;
extern bodyNode * tail;


void clear_coordinate(WINDOW * Win, Coordinate * c) {
    mvwaddch(Win, c->y, c->x, ' ');   
}

/* void advance_tail(WINDOW * Win);
 *
 * Write a function that advances
 * the tail by one node.
 *
 * The coordinate occupied by the tail should
 * be cleared by invoking clear_coordinate
 *
 */
void advance_tail(WINDOW * Win) {
    bodyNode * tmp = tail;

    /* Overwrite the tail */

    clear_coordinate(Win, &tail->bodyCoordinate);

    /* Advance the tail to the next node */

    tail = tail->next;
    free(tmp);
}

/* Write a function that takes the address of a Coordinate
 * value and gives it a random value on the board */

void generate_coordinate(WINDOW * Win, Coordinate * c) {
    srand((unsigned) time(NULL));
    int row, col;
    getmaxyx(Win, row, col);
    /* Initialize x. Can be 1 thru N-1 */
    c->x = rand() % (col-2) + 1; 
    /* Initiailze y. Can be 1 thru N-1 */
    c->y = rand() % (row-2) + 1;
}
/* Write a function that grows the snake by 1.
 *
 * In order to accomplish this, do the following:
 *
 * 1. Allocate a new node.
 * 2. Set the coordinates of this node according to the
 *    direction of the tail. For example, if the direction
 *    of the tail is KEY_RIGHT, the x value of this coordinate
 *    should be tail->bodyCoordinate.x-1.
 * 3. Make this new node point to the tail.
 * 4. Make the tail point to this new node
 */

void push_food(void) {
    /* Allocate the node */

    bodyNode * new_node = malloc(sizeof(bodyNode));
    new_node->next = tail;

    /* Set the coordinates to that of the tail */

    new_node->bodyCoordinate = tail->bodyCoordinate;
    new_node->bodyDirection = tail->bodyDirection;

    /* Set the coordinates of this node. It should be done
     * by INVERSING the direction of tail->bodyDirection
     * and call increment_coordinate */
    switch(tail->bodyDirection) {
        case UP:
            increment_coordinate(&new_node->bodyCoordinate, DOWN);
            break;
        case DOWN:
            increment_coordinate(&new_node->bodyCoordinate, UP);
            break;
        case LEFT:
            increment_coordinate(&new_node->bodyCoordinate, RIGHT);
            break;
        case RIGHT:
            increment_coordinate(&new_node->bodyCoordinate, LEFT);
            break;
    }
/* Make this new node the last node */
    tail = new_node;

}
/* 
 * void advance_head(WINDOW * Win);
 *
 * This function allocates a new node, 
 * sets its direction to that of the head
 * Sets its coordinate to the increment of the direction
 * of the head
 *
 */

void advance_head(WINDOW * Win) {
    /* Allocate a new node and insert it at the beginning of the list */

    bodyNode * new_node = malloc(sizeof(bodyNode));
    new_node->next = NULL;

    /* Set the node direction to that of the head */

    new_node->bodyDirection = head->bodyDirection;
    
    /* Set the coordinate to that of the head */

    new_node->bodyCoordinate = head->bodyCoordinate;
    
    /* Increment these coordinates according to the head */

    increment_coordinate(&new_node->bodyCoordinate, new_node->bodyDirection);

    /* Check to see if this coordinate is legal */

    check_coordinate(Win, new_node->bodyCoordinate); 

    
    head->next = new_node;

    /* Let the head now point to this node */

    head = new_node;
}
/* void check_coordinate(WINDOW *Win, Coordinate c):
 *
 * Check if coordinate c exists within the snake or
 * is off bounds of the window 
 */
void check_coordinate(WINDOW * Win, Coordinate c) {
    int row, col;
    getmaxyx(Win, row, col);
    /* Check to see if the coordinates are out of bounds
     * of the window
     */
    /* Overextend LEFT or RIGHT */
    if(c.x <=0 || c.x >= col-1) {
        gameover(Win);
    }
    /* Overextend UP or DOWN */
    if(c.y <= 0 || c.y >= row-1) {
        gameover(Win);
    }
    if(find_coordinate(c)) {
        gameover(Win);
    }
}


/* Walk the snake list to find coordinate c */
bool find_coordinate(Coordinate c) {
    bodyNode * p;
    for(p = tail; p != NULL; p = p->next) {
        if(p->bodyCoordinate.x == c.x && p->bodyCoordinate.y == c.y) {
            return true;
        }
    }
    return false;
}


void increment_coordinate(Coordinate * c, Direction d) {
    switch(d) {
        case UP: 
            --c->y;
            break;
        case DOWN:
            ++c->y;
            break;
        case LEFT:
            --c->x;
            break;
        case RIGHT:
            ++c->x;
            break;
    }
}
/* Clear the window, free the snake */

void gameover(WINDOW * Win) {
    struct node *tmp = tail;
    wborder(Win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    clear();
    delwin(Win);
    endwin();
    exit(EXIT_FAILURE);
}
