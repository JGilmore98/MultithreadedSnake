//CLASS FOR NCURSES LOGIC FOR SNAKE GAME
#include <ncurses.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include "player.h"

bool gameover = false;
pthread_mutex_t lock;

void *initNcurses(void *arg)
{
    initscr();
    noecho();
    keypad(stdscr, true);
    return NULL;
}

void *createGameWindow(void *arg)
{
    WINDOW *gameScreen = newwin(30, 100, 0, 0);
    refresh();
    box(gameScreen, 0, 0);
    wrefresh(gameScreen);
    return (void *)gameScreen;
}
void *createFruit(void *arg)
{
    sleep(3);
    int yLoc, xLoc;
    while (!gameover)
    {
        WINDOW *gameScreen = (WINDOW *)arg;
        yLoc = rand() % 27 + 1;
        xLoc = rand() % 100 + 1;
        if (mvwinch(gameScreen, yLoc, xLoc) == ' ')
        {
            mvwaddch(gameScreen, yLoc, xLoc, 'A');
        }
        sleep(2);
    }
    return NULL;
}
void *createScoreBoard(void *arg)
{
    Player *user = (Player *)arg;
    pthread_mutex_lock(&lock);
    WINDOW *ScoreWindow = newwin(10, 40, 20, 100);
    int tempScore = 0;
    box(ScoreWindow, 0, 0);
    mvwprintw(ScoreWindow, 0, 5, "Score");
    wrefresh(ScoreWindow);
    pthread_mutex_unlock(&lock);
    
    while (!gameover)
    {
        if (user->getScore() != tempScore)
        {
            pthread_mutex_lock(&lock);
            //sleep(1);
            mvwprintw(ScoreWindow, 2, 5,"%d",user->getScore());
            tempScore = user->getScore();
            wrefresh(ScoreWindow);
            pthread_mutex_unlock(&lock);
        }
    }
    
    return NULL;
}
void *createControlWindow(void *arg)
{

    //CREATE CONTROL WINDOW
    pthread_mutex_lock(&lock);
    WINDOW *ControlWindow = newwin(20, 40, 0, 100);
    box(ControlWindow, 0, 0);
    mvwprintw(ControlWindow, 0, 5, "CONTROLS");
    mvwprintw(ControlWindow, 2, 4, "ARROW KEYS");
    mvwprintw(ControlWindow, 4, 4, "UP KEY(MOVES SNAKE UP)");
    mvwprintw(ControlWindow, 6, 4, "DOWN KEY(MOVES SNAKE DOWN)");
    mvwprintw(ControlWindow, 8, 4, "LEFT KEY(MOVES SNAKE LEFT)");
    mvwprintw(ControlWindow, 10, 4, "RIGHT KEY(MOVES SNAKE RIGHT)");
    wrefresh(ControlWindow);
    pthread_mutex_unlock(&lock);
    return (void *)ControlWindow;
}


int main()
{
    pthread_t NcursesThread, GameWindowThread, FruitThread, ControlThread, ScoreThread;
    /*Thread responsible for initializing Ncurses*/
    pthread_create(&NcursesThread, NULL, initNcurses, NULL);
    pthread_join(NcursesThread, NULL);
    /*Thread responsbile for creating play field*/
    pthread_create(&GameWindowThread, NULL, createGameWindow, NULL);
    void *temp;
    WINDOW *gameWindow;
    pthread_join(GameWindowThread, &temp);
    gameWindow = (WINDOW *)temp;
    temp = NULL;
    /*CREATES THE PLAYER*/
    Player user(gameWindow);
    user.display();
    wrefresh(gameWindow);

    //CREATE CONTROL WINDOW
    pthread_create(&ControlThread, NULL, createControlWindow, NULL);
    pthread_join(ControlThread, &temp);
    //Create Score Window
    pthread_create(&ScoreThread, NULL, createScoreBoard,&user);
    pthread_create(&FruitThread, NULL, createFruit, (void *)gameWindow);
    int action = 0;
    while (!gameover)
    {
        action = user.getmv();
        pthread_mutex_lock(&lock);
        user.move();
        user.display();
        wrefresh(gameWindow);
        pthread_mutex_unlock(&lock);
        if (user.isGameOver())
        {
            gameover = true;
        }
    }
    pthread_join(FruitThread, NULL);
    pthread_join(ScoreThread, NULL);
    endwin();
}
