#include <iostream>
#include <stdexcept>

using namespace std;

// Circular linked list

template<typename T>
class CList {
private:
    class CListElement {
    public:
        T value;
        CListElement* next;
        CListElement* prev;

        CListElement(T v) : value(v) {}
    };

    CListElement* head;
    CListElement* tail;
    size_t Size;

public:
    class CListIterator {
    public:
        CListElement* ptr;

        CListIterator(CListElement* vPtr) : ptr(vPtr) {}

        inline bool operator ==(CListIterator rhs) { return this -> ptr == rhs.ptr; }

        inline bool operator !=(CListIterator rhs) { return !(*this == rhs); }

        CListIterator& operator++() {
            if(ptr == nullptr) throw runtime_error("Invalid pointeer");

            ptr = ptr -> next;
            return *this;
        }

        CListIterator operator++(int) {
            if(ptr == nullptr) throw runtime_error("Invalid pointeer");

            auto temp = *this;
            ptr = ptr -> next;
            return temp;
        }

        T& operator*() {
            if(ptr == nullptr) throw runtime_error("Invalid pointeer");

            return ptr -> value;
        }
    };

    CList() : head(nullptr), tail(nullptr), Size(0) {}

    ~CList() {
        while(Size > 0) {
            remove(begin());
        }
    }

    void PushBack(T v) {
        CListElement* newElement = new CListElement(v);

        if(head == nullptr) {
            head = newElement;
            tail = newElement;
            newElement -> next = newElement;
            newElement -> prev = newElement;
        } else {
            tail -> next = newElement;
            newElement -> next = head;
            newElement -> prev = tail;
            head -> prev = newElement;
            tail = newElement;
        }

        Size++;
    }

    CListIterator remove(CListIterator it) {
        CListElement* node = it.ptr;

        if(node == head && node == tail) {
            head = tail = nullptr;
            delete node;
            Size--;

            return CListIterator(nullptr);
        }

        node -> prev -> next = node -> next;
        node -> next -> prev = node -> prev;

        if(node == head) {
            head = node -> next;
        }

        if(node == tail) {
            tail = tail -> prev;
        }

        CListIterator newNode = CListIterator(node -> next);

        delete node;
        Size--;
        return newNode;
    }

    size_t getSize() { return Size; }

    CListIterator begin() { return CListIterator(head); }
    CListIterator end() { return CListIterator(nullptr); }
};

void testCList() {
    CList<int> l;

    for(int i = 1; i <= 41; i++) l.PushBack(i);

    CList<int>::CListIterator it = l.begin();

    while(l.getSize() > 2) {
        ++it;
        ++it;
        it = l.remove(it);
    }

    cout << *it << " ";
    it++;
    cout << *it << " ";
}
