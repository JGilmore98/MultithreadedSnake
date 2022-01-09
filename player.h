#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <stdlib.h>
#include "snake.h"
using namespace std;
class Player
{
public:
    Player(WINDOW *win);
    void mvup();
    void mvdown();
    void mvleft();
    void mvright();

    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();

    int getmv();
    int getScore();
    void move();
    void display();
    bool isGameOver();

private:
    Snake player_snake;
    SnakeSegment head;
    int xLoc, yLoc, xMax, yMax, snakesize,playerScore;

    char headDirection = 'n';
    WINDOW *curwin;
    bool gameover;
};
//Initialize the head of the snake
//and 2 additional body parts
Player::Player(WINDOW *win)
{
    curwin = win;
    gameover = false;
    curs_set(0);
    keypad(curwin, true);
    wtimeout(curwin, 100);
    getmaxyx(curwin, yMax, xMax);
    yLoc = 9;
    xLoc = 15;
    player_snake.createHead(yLoc, xLoc);
    snakesize = 1;

    player_snake.createSegment(yLoc, xLoc + 1);
    snakesize++;

    player_snake.createSegment(yLoc, xLoc + 2);
    snakesize++;
    SnakeSegment head = player_snake.get_Segment(0);
    playerScore = 0;
    /*
    //Two more additional segments have been created now we move the cursor to the front of the snakes head
    move(yLoc,xLoc-3);
    */
}

void Player::mvup()
{
    SnakeSegment blank = player_snake.get_Segment(snakesize - 1);

    yLoc--;
    if(mvwinch(curwin,yLoc,xLoc) == 'A'){
        player_snake.createSegment(blank.yLocation++,blank.xLocation);
        snakesize++;
        playerScore+=10;
    }
     if(mvwinch(curwin,yLoc,xLoc) == 'O'){
        gameover=true;
    }
    if (yLoc < 1)
    {
        yLoc = 1;
        gameover=true;
    }
    else
    {
        mvwaddch(curwin, blank.yLocation, blank.xLocation, ' ');
        player_snake.updateHeadValue(yLoc, xLoc);
        
    }
}
void Player::mvdown()
{
    SnakeSegment blank = player_snake.get_Segment(snakesize - 1);
    yLoc++;
    if(mvwinch(curwin,yLoc,xLoc) == 'A'){
        player_snake.createSegment(blank.yLocation--,blank.xLocation);
        snakesize++;
        playerScore+=10;
    }
     if(mvwinch(curwin,yLoc,xLoc) == 'O'){
        gameover=true;
    }
    if (yLoc > yMax - 2)
    {
        yLoc = yMax - 2;
        gameover=true;
    }
    else
    {

        mvwaddch(curwin, blank.yLocation, blank.xLocation, ' ');
        player_snake.updateHeadValue(yLoc, xLoc);
    }
}
void Player::mvleft()
{
    SnakeSegment blank = player_snake.get_Segment(snakesize - 1);
    xLoc--;
    if(mvwinch(curwin,yLoc,xLoc) == 'A'){
        player_snake.createSegment(blank.yLocation,blank.xLocation++);
        snakesize++;
        playerScore+=10;
    }
    if(mvwinch(curwin,yLoc,xLoc) == 'O'){
        gameover=true;
    }
    
    if (xLoc < 1)
    {
        xLoc = 1;
        gameover=true;
    }
    else
    {

        mvwaddch(curwin, blank.yLocation, blank.xLocation, ' ');
        player_snake.updateHeadValue(yLoc, xLoc);
    }
}
void Player::mvright()
{
    SnakeSegment blank = player_snake.get_Segment(snakesize - 1);
    xLoc++;
    if(mvwinch(curwin,yLoc,xLoc) == 'A'){
        player_snake.createSegment(blank.yLocation,blank.xLocation--);
        snakesize++;
        playerScore+=10;
    }
     if(mvwinch(curwin,yLoc,xLoc) == 'O'){
        gameover=true;
    }
    if (xLoc > xMax - 2)
    {
        xLoc = xMax - 2;
        gameover=true;
    }
    else
    {
    
        mvwaddch(curwin, blank.yLocation, blank.xLocation, ' ');
        player_snake.updateHeadValue(yLoc, xLoc);
    }
}

int Player::getmv()
{
    int action = wgetch(curwin);
    switch (action)
    {
    case KEY_UP:
        turnUp();
        break;
    case KEY_DOWN:
        turnDown();
        break;
    case KEY_LEFT:
        turnLeft();
        break;
    case KEY_RIGHT:
        turnRight();
        break;
    }
    return action;
}
void Player::move()
{
    switch (headDirection)
    {
    case 'n':
        mvup();
        break;
    case 's':
        mvdown();
        break;
    case 'w':
        mvleft();
        break;
    case 'e':
        mvright();
        break;
    }
}

void Player::turnUp()
{
    headDirection = 'n';
}
void Player::turnDown()
{
    headDirection = 's';
}
void Player::turnLeft()
{
    headDirection = 'w';
}
void Player::turnRight()
{
    headDirection = 'e';
}

void Player::display()
{
    SnakeSegment section;
    for (int i = 0; i < snakesize; i++)
    {
        section = player_snake.get_Segment(i);
        mvwaddch(curwin, section.yLocation, section.xLocation, section.character);
    }
}
bool Player::isGameOver(){
    return gameover;
}
int Player::getScore(){
    return playerScore;
}
#endif