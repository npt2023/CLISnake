/* Implement the snake game in C using ncurses */
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "snake.h"

/* Global Variables */

WINDOW * create_mainboard(void);
bodyNode * head;
bodyNode * tail;


void msleep(unsigned int milliseconds);

int main(int argc, char *argv[]) {

    bool generateCoordinate = true;
    Coordinate foodCoordinate;

    int i, ch = KEY_RIGHT;
    WINDOW * MainBoard;
    /* Start ncurses, disable terminal echoing */    
    initscr();
    noecho();
    curs_set(0); 

    /* Access the buffer in real-time; use halfdelay() to set frametime to 1/10th of a second */

    halfdelay(1);
    
   
    /* Create the playing board */

    MainBoard = create_mainboard(); 
    keypad(MainBoard, true);
    
    /* Initialize the snake */
    
    head = malloc(sizeof(bodyNode));
    tail = head;
    head->bodyCoordinate.y = 2;
    head->bodyCoordinate.x = 2;
    head->bodyDirection = RIGHT;
    head->next = NULL;

    /* Start the game */
    
    /* This loop will handle the following: 
     *
     * 1. Generate a coordinate for the food.
     * 2. Advance the snake according to the direction of the head
     * 3. Overwrite and advance the tail
     * 3. Add a node to the end of the snake when the head hits the food
     * 4. Change the direction of the head when the user enters an input
     * 5. Set up the frametime (done by the above steps)
     *
     */

    while(1) {
        /* To handle food generation, consider the following:
         *
         * 1. Food needs to be generated at the start of the game,
         *    or first loop iteration.
         *
         * 2. When the snake head hits the food, grow the snake by one.
         *
         * 3. Only regenerate the food coordinate when it is hit by the snake
         *
         */
        if(generateCoordinate) {
            generate_coordinate(MainBoard, &foodCoordinate);
            mvwaddch(MainBoard, foodCoordinate.y, foodCoordinate.x, '#');
            generateCoordinate = false;
        }

        advance_head(MainBoard);
        advance_tail(MainBoard);

        if(find_coordinate(foodCoordinate)) {
            push_food();
            mvwaddch(MainBoard, tail->bodyCoordinate.y, tail->bodyCoordinate.x, '#');
            generateCoordinate = true;
        }

        mvwaddch(MainBoard, head->bodyCoordinate.y, head->bodyCoordinate.x, '#');
         
        ch = wgetch(MainBoard); 

        switch(ch) {
            case KEY_UP:
                head->bodyDirection = UP;
                break;
            case KEY_LEFT:
                head->bodyDirection = LEFT;
                break;
            case KEY_RIGHT:
                head->bodyDirection = RIGHT;
                break;
            case KEY_DOWN:
                head->bodyDirection = DOWN;
                break;
        }
        wrefresh(MainBoard);
    } 
    endwin();
}

WINDOW * create_mainboard(void) {
    int max_row, max_col;
    int startY = 0, startX = 0;
    getmaxyx(stdscr, max_row, max_col);
    WINDOW * new_window = newwin(max_row, max_col, startY, startX);
    wborder(new_window, '#', '#', '#', '#', '#', '#', '#', '#');
    wrefresh(new_window);
    return new_window;
}

void msleep(unsigned int milliseconds) {
    /* Convert microseconds to milliseconds */
    usleep((useconds_t) milliseconds * 1000);
}
