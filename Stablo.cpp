#include <iostream>

using namespace std;

// Binary search tree

template<typename T>
class Tree {
private:
    class Node {
    public:
        T value;
        Node* right;
        Node* left;

        Node(T v) : value(v), right(nullptr), left(nullptr) {}
    };

    Node* head;

public:
    Tree() : head(nullptr) {}

    ~Tree() {
        deleteAll(head);
        head = nullptr;
    }

    void add(T v) {
        Node* newNode = new Node(v);

        if(head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;

        while(true) {
            if(temp -> value >= newNode -> value) {
                // idii lijevoo
                if(temp -> left == nullptr) {
                    temp -> left = newNode;
                    return;
                }

                temp = temp -> left;
            } else {
                // idi desno
                if(temp -> right == nullptr) {
                    temp -> right = newNode;
                    return;
                }

                temp = temp -> right;
            }
        }
    }

    void innerAdd2(Node*& temp, Node* newNode) {
        if(temp == nullptr) {
            temp = newNode;
            return;
        }

        if(temp -> value >= newNode -> value) {
            innerAdd2(temp -> left, newNode);
        } else {
            innerAdd2(temp -> right, newNode);
        }
    }

    void Add2(T v) {
        innerAdd2(head, new Node(v));
    }

    int getHeight2(Node* node) {
        if(node == nullptr) return 0;

        return 1 + max(getHeight2(node -> left), getHeight2(node -> right));
    }

    int getHeight() {
        return getHeight2(head);
    }

    void test2(Node* node) {
        if(node == nullptr) return;

        test2(node -> left);
        cout << node -> value << " ";
        test2(node -> right);
    }

    void test() {
        test2(head);
    }

    T Min() {
        if(head == nullptr) throw runtime_error("The tree is emptyy");

        Node* temp = head;

        while(temp -> left != nullptr) {
            temp = temp -> left;
        }

        return temp -> value;
    }

    T Max() {
        if(head == nullptr) throw runtime_error("The tree is emptyy");

        Node* temp = head;

        while(temp -> right != nullptr) {
            temp = temp -> right;
        }

        return temp -> value;
    }

    bool doesExist2(Node* temp, T v) {
        if(temp == nullptr) return false;

        if(temp -> value == v) return true;

        if(temp -> value >= v) {
            return doesExist2(temp -> left, v);
        } else {
            return doesExist2(temp -> right, v);
        }
    }

    bool doesExist(T v) {
        return doesExist2(head, v);
    }

    void Remove(T v) {
        Node* temp = head;
        Node** temp2 = &head;

        while(temp != nullptr) {
            if(temp -> value == v) {
                break;
            }

            if(temp -> value >= v) {
                temp2 = &temp -> left;
                temp = temp -> left;
            } else {
                temp2 = &temp -> right;
                temp = temp -> right;
            }
        }

        if(temp == nullptr) throw invalid_argument("Not foundd");

        if(temp -> left == nullptr && temp -> right == nullptr) {
            *temp2 = nullptr;
        } else if(temp -> left == nullptr) {
            *temp2 = temp -> right;
        } else if(temp -> right == nullptr) {
            *temp2 = temp -> left;
        } else {
            *temp2 = temp -> right;
            auto minimal = temp -> right;

            while(minimal -> left != nullptr) {
                minimal = minimal -> left;
            }

            minimal -> left = temp -> left;
        }

        delete temp;
    }

    void deleteAll(Node* node) {
        if(node == nullptr) return;

        deleteAll(node -> left);
        deleteAll(node -> right);

        delete node;
    }
};

void testStablo() {
    Tree<int> s;

    s.Add2(10);
    s.Add2(50);
    s.Add2(25);
    s.Add2(30);
    s.Add2(1);
    s.Add2(45);
    s.Add2(80);

    s.test();

    cout << endl << s.getHeight() << endl;

    cout << "Biggest element: " << s.Max() << endl;
    cout << "Smallest element: " << s.Min() << endl;

    cout << s.doesExist(100) << " " << s.doesExist(10) << endl;

    s.Remove(30);

    s.test();
}
