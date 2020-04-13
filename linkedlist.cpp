#include "linkedlist.h"
#include<QtCore>


void LinkedList::Append(QString data)
{
    Node* newNode = new Node;
    newNode->data=data;

    if(head==NULL)
    {
        head = newNode;
    }

    else
    {
        current = head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next=newNode;
    }

}

int LinkedList::findSize()
{
    int count = 0;
    Node* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

QString LinkedList::returnEle(int index)
{
    Node* current = head;

        int count = 0;
        while (current != NULL)
        {
            if (count == index) {
                return(current->data);
            }
            count++;
            current = current->next;
        }
    //return(current->data);
}

