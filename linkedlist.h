#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <QtCore>




class LinkedList :public QObject
{
    Q_OBJECT

    private:
        struct Node
        {
            QString data;
            Node *next;
            Node(){}
        };

    public:
        Node* head;
        Node* current;

        LinkedList()
        {
            head = NULL;
        }

        void Append(QString data);
        QString returnEle(int index);
        int findSize();
};


#endif // LINKEDLIST_H
