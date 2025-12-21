#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class Queue {
private:
    class QueueElement {
    public:
        T value;
        QueueElement* next;

        QueueElement(T v) : value(v), next(nullptr) {}
    };

    QueueElement* head;
    QueueElement* tail;
    size_t q_size;


public:
    Queue() : head(nullptr), tail(nullptr), q_size(0) {}

    Queue(const Queue& q) {
        QueueElement* temp = q.head;

        head = nullptr;
        tail = nullptr;
        q_size = 0;

        while(temp != nullptr) {
            Push(temp -> value);
            temp = temp -> next;
        }
    }

    Queue& operator =(const Queue& q) {
        if(this == &q) return *this;

        while(!Empty()) Pop();

        QueueElement* temp = q.head;

        while(temp != nullptr) {
            Push(temp -> value);
            temp = temp -> next;
        }

        return *this;
    }

    ~Queue() {
        QueueElement* temp = head;

        while(temp != nullptr) {
            QueueElement* temp2 = temp;
            temp = temp -> next;

            delete temp2;
        }
    }

    void Push(T v) {
        QueueElement* newQueueElement = new QueueElement(v);

        if(head == nullptr) {
            head = newQueueElement;
            tail = newQueueElement;
        } else {
            tail -> next = newQueueElement;
            tail = newQueueElement;
        }

        q_size++;
    }

    T& Front() {
        if(head == nullptr) throw runtime_error("Queue is emptyyy");

        return head -> value;
    }

    T& Back() {
        if(head == nullptr) throw runtime_error("Queue is emptyyy");

        return tail -> value;
    }

    void Pop() {
        if(head == nullptr) throw runtime_error("Queue is emptyy");

        QueueElement* temp = head;
        head = head -> next;
        delete temp;

        q_size--;
    }

    bool Empty() { return head == nullptr; }

    size_t Size() { return q_size; }

    void Test() {
        QueueElement* temp = head;

        while(temp != nullptr) {
            cout << temp -> value << " ";
            temp = temp -> next;
        }

        cout << endl;
    }
};

void testQueue() {
    Queue<int> q;

    q.Push(10);
    q.Push(20);
    q.Push(30);

    q.Test();

    q.Pop();

    q.Test();

    Queue<int> q2(q);

    q2.Test();
}
