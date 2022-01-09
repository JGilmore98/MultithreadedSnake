#ifndef _DoubleLinkedList_H_
#define _DoubleLinkedList_H_
#include <string>
#include <unistd.h>
#include <list>
#include <assert.h>
#include <iostream>
using namespace std;

struct SnakeSegment
{
    int yLocation;
    int xLocation;
    char character;
};
struct Node
{
    SnakeSegment segment;
    struct Node *prev;
    struct Node *next;
};

class Double_Linked_List
{
    Node *head;
    Node *tail;

public:
    Double_Linked_List()
    {
        head = NULL;
        tail = NULL;
    }
    void add_front(SnakeSegment segment);
    void add_end(SnakeSegment segment);
    void update_head_value(int x, int y);
    void forward_traverse();
    SnakeSegment getSegmentAtIndex(int index);
};

void Double_Linked_List::add_front(SnakeSegment segment)
{
    Node *temp;
    temp = new Node();
    temp->segment = segment;
    temp->prev = NULL;
    temp->next = head;
    if (head == NULL)
    {
        tail = temp;
    }
    else
    {
        head->prev = temp;
    }
    head = temp;
}
void Double_Linked_List::add_end(SnakeSegment segment)
{
    Node *temp;
    temp = new Node();
    temp->segment = segment;
    temp->prev = tail;
    temp->next = NULL;
    if (tail == NULL)
    {
        head = temp;
    }
    else
    {
        tail->next = temp;
    }
    tail = temp;
}

void Double_Linked_List ::forward_traverse()
{
    Node *trav;
    trav = head;
    while (trav != NULL)
    {
        cout << trav->segment.character << endl;
        cout << trav->segment.xLocation << endl;
        cout << trav->segment.yLocation << endl;
        trav = trav->next;
    }
}
/*Method to replace x,y values of the head node and transfer the previous values to the next node*/
void Double_Linked_List ::update_head_value(int yloc, int xloc)
{
    Node *trav;
    //tempx1 tempy1 contain the previous nodes x and y values
    int tempx1, tempy1, tempx2, tempy2;
    trav = head;
    tempx2 = xloc;
    tempy2 = yloc;
    while (trav != NULL)
    {
        tempx1 = trav->segment.xLocation;
        tempy1 = trav->segment.yLocation;
        trav->segment.xLocation = tempx2;
        trav->segment.yLocation = tempy2;
        tempx2 = tempx1;
        tempy2 = tempy1;
        trav = trav->next;
    }
}
SnakeSegment Double_Linked_List::getSegmentAtIndex(int index)
{
    SnakeSegment* ptr = NULL;
    Node *trav;
    trav = head;
    int count = 0;
    while (trav != NULL)
    {
        if(count == index){
            return trav->segment;
        }
        count++;
        trav = trav->next;
    }
    //RETURNS LAST SEGMENT IF NOT IN LIST
    SnakeSegment anull;
    anull.xLocation = -999;
    anull.yLocation = -999;
    anull.character = '$';
    return anull;
}

#endif
