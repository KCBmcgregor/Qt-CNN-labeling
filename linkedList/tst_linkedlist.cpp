#include <QtTest>
#include <QCoreApplication>

class linkedList : public QObject
{
    Q_OBJECT
//private slots:
  //  void test_case1();

private:
    struct Node
    {
        QString data;
        Node *next;
        Node(){}
    };

public:
    linkedList();
    ~linkedList();
    Node* head =NULL;
    Node* current;



    void Append(QString data);
    QString returnEle(int index);
    int findSize();
};



linkedList::linkedList()
{

}

linkedList::~linkedList()
{

}

void linkedList::Append(QString data)
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

int linkedList::findSize()
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

QString linkedList::returnEle(int index)
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
    return(current->data);
}
QTEST_MAIN(linkedList)

#include "tst_linkedlist.moc"
