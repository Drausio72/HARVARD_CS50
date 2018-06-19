//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 60

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3




// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

// create an array of GRects to store the bricks
GRect brick[5][10];

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;
    
    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // update scoreboard for the first time
    updateScoreboard(window, label, points);
    
    double velocityX = 1;
    double velocityY = 1;
    
    
    
    // keep playing until game over
    while(true)
    {
    
    GEvent event2 = getNextEvent(MOUSE_EVENT);
    
    if (event2 != NULL)
    {
        if (getEventType(event2) == MOUSE_CLICKED)
        {   
            while (lives > 0 && bricks > 0)
            {
                // DOING

                GEvent event = getNextEvent(MOUSE_EVENT);
                
                if (event != NULL)
                {
                    if (getEventType(event) == MOUSE_MOVED)
                    {
                        double x = getX(event) - (PADDLE_WIDTH / 2);
                        setLocation(paddle, x, HEIGHT - PADDLE_WIDTH);
                    }
                }
                
                move(ball, velocityX * drand48(), velocityY * drand48());

                
                if (getX(ball) + getWidth(ball) >= getWidth(window))
                {
                    velocityX = -velocityX;
                }
                else if (getY(ball) + getWidth(ball) >= HEIGHT)
                {
                    setLocation(ball,(WIDTH / 2) - 10, HEIGHT /2);
                    lives--;
                    if (lives == 0)
                    {
                        GLabel lose = newGLabel("You lose! :(");
                        setFont(lose, "SansSerif-36");
                        setColor(lose, "RED");
                        setLocation(lose, (WIDTH / 2) - 100, (HEIGHT / 2) + 80);
                        add(window, lose);
                        pause(2000);
                        break;
                    }
                    pause(1000);
                    
                    
                }
                else if (getX(ball) <= 0)
                {
                    velocityX = -velocityX;
                }
                else if (getY(ball) <= 0)
                {
                    velocityY = -velocityY;
                }
                
                GObject object = detectCollision(window, ball);
                
                if (object == paddle)
                {
                    velocityX = -velocityX;
                    velocityY = -velocityY;
                }
                
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        if (object == brick[i][j])
                        {
                            removeGWindow (window, brick[i][j]);
                            velocityX = -velocityX;
                            velocityY = -velocityY;
                            points++;
                            updateScoreboard(window, label, points);
                            bricks--;
                            
                        }
                    }
                }
                

                
                if (bricks == 0)
                {
                    GLabel win = newGLabel("You win! :)");
                    setFont(win, "SansSerif-36");
                    setColor(win, "GREEN");
                    setLocation(win, (WIDTH / 2) - 100, (HEIGHT / 2) + 80);
                    add(window, win);
                    initBricks(window);
                    setLocation(ball,(WIDTH / 2) - 10, HEIGHT /2);
                    pause(2000);
                    removeGWindow(window, win);
                    bricks = (ROWS * COLS);
                    points = 0;
                    lives = LIVES;
                    updateScoreboard(window, label, points);
                    move(ball, velocityX * drand48(), velocityY * drand48());
                    break;
                    
                }
                
                    
                
                
                pause(1);
                
            }
    
        }
    }
    
    if (bricks <= 0 || lives <= 0)
    {
        break;
    }
    
    }
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;


}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // DONE
    
    for (int i = 0, y = 50; i < ROWS; i++, y += 15)
    {
        for (int j = 0, x = 2; j < COLS; j++, x += 40)
        {
            
            brick[i][j] = newGRect(x, y, 35, 10);
            setFilled(brick[i][j], true);
            switch (i)
            {
                case 0:
                setColor(brick[i][j], "RED");
                break;
                
                case 1: 
                setColor(brick[i][j], "ORANGE");
                break;  
                
                case 2:
                setColor(brick[i][j], "YELLOW");
                break;
                
                case 3:
                setColor(brick[i][j], "GREEN");
                break;
                
                case 4:
                setColor(brick[i][j], "CYAN");
                break;
                
                default:
                break;
            }
            add(window, brick[i][j]);
            
            
        }
            
    }

    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // DONE
    GOval ball = newGOval((WIDTH / 2) - 10, HEIGHT /2, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // DONE
    GRect paddle = newGRect((WIDTH / 2) - (PADDLE_WIDTH / 2),
                   HEIGHT -  PADDLE_WIDTH, 60, 10);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // DONE
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-42");
    setColor(label, "GRAY");
    add(window, label);

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
