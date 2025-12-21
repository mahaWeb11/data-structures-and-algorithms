#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class List {
private:
    class Node {
    public:
        T value;
        Node* next;

        Node(T v) : value(v), next(nullptr) {}

        ~Node() {
            cout << "Destructor for value " << value << endl;
        }
    };

    Node* head;

public:
    List() : head(nullptr) {}

    ~List() {
        Node* temp = head;

        while(temp != nullptr) {
            Node* temp2 = temp;
            temp = temp -> next;

            delete temp2;
        }
    }

    void add(T v) {
        Node* newNode = new Node(v);

        newNode -> next = head;
        head = newNode;
    }

    void addToEnd(T v) {
        Node* newNode = new Node(v);

        if(head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;

        while(temp -> next != nullptr) {
            temp = temp -> next;
        }

        temp -> next = newNode;
    }

    void remove(T v) {
        if(head == nullptr) return;

        if(head -> value == v) {
            Node* temp = head;
            head = head -> next;
            delete temp;

            return;
        }


        Node* temp = head;
        Node* previous = nullptr;

        while(temp != nullptr) {
            if(temp -> value == v) {
                previous -> next = temp -> next;
                delete temp;
                return;
            }

            previous = temp;
            temp = temp -> next;
        }

        throw invalid_argument("Ne postoji takaav element");
    }

    void test() {
        Node* temp = head;

        while(temp != nullptr) {
            cout << temp -> value << " ";
            temp = temp -> next;
        }

        cout << endl;
    }
};

void testList() {
    List<int> l;

    l.add(10);
    l.add(20);
    l.add(30);

    l.addToEnd(50);

    l.remove(10);

    l.test();
}
