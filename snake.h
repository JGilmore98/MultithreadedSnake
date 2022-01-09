#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <string>
#include <unistd.h>
#include "DoubleLinkedList.h"

using namespace std;


class Snake{
    public:
    Snake(){
    }
    void createHead(int y,int x);
    void createSegment(int y,int x);
    void traverseSnake();
    void updateHeadValue(int y,int x);
    SnakeSegment get_Segment(int index);
    private:
    Double_Linked_List snake_parts;
};

void Snake::createHead(int y,int x){
    SnakeSegment head;
    head.xLocation = x;
    head.yLocation = y;
    head.character = '@';
    snake_parts.add_front(head);
}

void Snake::createSegment(int y,int x){
    SnakeSegment seg;
    seg.xLocation = x;
    seg.yLocation = y;
    seg.character = 'O';
    snake_parts.add_end(seg);
}

void Snake::traverseSnake(){
    snake_parts.forward_traverse();
}
void Snake::updateHeadValue(int y,int x){
    snake_parts.update_head_value(y,x);
}

SnakeSegment Snake::get_Segment(int index){
    return snake_parts.getSegmentAtIndex(index);
}



#endif