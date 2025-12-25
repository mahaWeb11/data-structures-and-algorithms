#include <iostream>
#include <stdexcept>

// Double linked list

using namespace std;

template<typename T>
class DLList {
private:
    class DLListElement {
    public:
        T value;
        DLListElement* next;
        DLListElement* prev;

        DLListElement(T v) : value(v), next(nullptr), prev(nullptr) {}
    };
    DLListElement* head;
    DLListElement* tail;
public:
    class DLListIterator {
    public:
        DLListElement* ptr;

        DLListIterator(DLListElement* vPtr) : ptr(vPtr) {}

        inline bool operator ==(const DLListIterator rhs) { return this -> ptr == rhs.ptr; }

        inline bool operator !=(const DLListIterator rhs) { return !(*this == rhs); }

        DLListIterator& operator ++() {
            if(ptr == nullptr) throw runtime_error("Invalidd pointer");

            ptr = ptr -> next;
            return *this;
        }

        DLListIterator operator ++(int) {
            if(ptr == nullptr) throw runtime_error("Invalidd pointer");

            auto temp = *this;
            ptr = ptr -> next;
            return temp;
        }

        T& operator*() {
            if(ptr == nullptr) throw runtime_error("Invalidd pointer");

            return ptr -> value;
        }
    };

    DLList() : head(nullptr), tail(nullptr) {}

    ~DLList() {
        auto temp = head;

        while(temp != nullptr) {
            auto temp2 = temp;
            temp = temp -> next;
            delete temp2;
        }
    }

    void PushFront(T v) {
        DLListElement* newElement = new DLListElement(v);

        if(head == nullptr) {
            head = tail = newElement;
        } else {
            newElement -> next = head;
            head -> prev = newElement;
            head = newElement;
        }
    }

    void PushBack(T v) {
        DLListElement* newElement = new DLListElement(v);

        if(head == nullptr) {
            head = tail = newElement;
        } else {
            tail -> next = newElement;
            newElement -> prev = tail;
            tail = newElement;
        }
    }

    void Test() {
        DLListElement* temp = head;

        while(temp != nullptr) {
            cout << temp -> value << " ";
            temp = temp -> next;
        }
    }

    DLListIterator begin() { return DLListIterator(head); }
    DLListIterator end() { return DLListIterator(nullptr); }
};

void testDList() {
    DLList<int> l;

    l.PushBack(10);
    l.PushBack(20);
    l.PushBack(30);

    l.Test();

    DLList<int>::DLListIterator it = l.begin();

    cout << endl;

    while(it != l.end()) {
        cout << *it++ << " ";
    }
}
