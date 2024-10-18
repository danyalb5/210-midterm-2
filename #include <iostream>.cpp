#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    bool pop_front() {
        if (!head) {
            return false;
        }
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        cout << temp->data << " is served" << endl;
        delete temp;
        return true;
    }

    bool remove_last() {
        if (!tail) {
            return false;
        }
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        cout << temp->data << " (at the rear) left the line" << endl;
        delete temp;
        return true;
    }

    
};

    void remove_random() {
        if (!head) {
            return;
        }
        int count = 0;
        Node* current = head;
        while (current) {
            current = current->next;
            count++;
        }
        int removeIndex = rand() % count;
        Node* temp = head;
        for (int i = 0; i < removeIndex; i++) {
            temp = temp->next;
        }
        if (temp == head) {
            pop_front();
        } else if (temp == tail) {
            remove_last();
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            cout << temp->data << " left the line" << endl;
            delete temp;
        }
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
;

int main() {
    srand(time(NULL));  // Initialize random seed
    DoublyLinkedList coffeeShopLine;

    // Simulate 20 time periods
    for (int minute = 1; minute <= 20; minute++) {
        cout << "Time step #" << minute << ":" << endl;

        // Initial setup: Add 5 customers
        if (minute == 1) {
            coffeeShopLine.push_back("Jean");
            coffeeShopLine.push_back("Iris");
            coffeeShopLine.push_back("Omar");
            coffeeShopLine.push_back("Andy");
            coffeeShopLine.push_back("Drew");
        } else {
            if (rand() % 100 < 40 && coffeeShopLine.pop_front()) {
                // 40% chance a customer is served
            }
            if (rand() % 100 < 60) {
                coffeeShopLine.push_back("New Customer");  // 60% chance a new customer joins
            }
            if (rand() % 100 < 20) {
                coffeeShopLine.remove_last();  // 20% chance the last customer leaves
            }
            if (rand() % 100 < 10) {
                coffeeShopLine.push_front("VIP Customer");  // 10% chance a VIP cuts in line
            }
            coffeeShopLine.remove_random();  // 10% chance any customer leaves
        }
        coffeeShopLine.print();  // Display the current line
    }
    return 0;
}
