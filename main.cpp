#include <iostream>
#include <string>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat {
private:
    int age;
    string name;
    string color;
    string names[15] = {"Alice", "Benjamin", "Catherine", "David", "Elena",
        "Frank", "Grace", "Henry", "Isabella", "Jack",
        "Karen", "Liam", "Mia", "Nathan", "Olivia"};

    string colors[15] = {"Red", "Blue", "Green", "Yellow", "Orange",
        "Purple", "Pink", "Brown", "Black", "White",
        "Gray", "Cyan", "Magenta", "Teal", "Gold"};

public:
    // default constructor
    Goat () {
        // randomizing between 1 and 20
        age = (rand() % 20) + 1;
        // randomizing an index to choose a random array element
        name = names[rand() % 16];
        color = colors[rand() % 16];

    }
    // parameter constructor
    Goat (int a, string n, string c) {age = a; name = n, color = c;}

    // getters
    int getAge() {return age;}
    string getName() {return name;}
    string getColor() {return color;}
    
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;  
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat g) {
        Node* newNode = new Node(g);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat g) {
        Node* newNode = new Node(g);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat g, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(g);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    // void delete_node(Goat g) {
    //     if (!head) return; // Empty list

    //     Node* temp = head;
    //     while (temp && temp->data != g)
    //         temp = temp->next;

    //     if (!temp) return; // Value not found

    //     if (temp->prev) {
    //         temp->prev->next = temp->next;
    //     } else {
    //         head = temp->next; // Deleting the head
    //     }

    //     if (temp->next) {
    //         temp->next->prev = temp->prev;
    //     } else {
    //         tail = temp->prev; // Deleting the tail
    //     }

    //     delete temp;
    // }

    void print() {
        Node* current = head;
        if (!current) return;
        cout << "Forward: " << endl;
        while (current) {
            cout << "   " << current->data.getName() << " (" << current->data.getColor() << ", " << current->data.getAge() << ")" << endl; 
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        cout << "Backward: " << endl;
        while (current) {
            cout << "   " << current->data.getName() << " (" << current->data.getColor() << ", " << current->data.getAge() << ")" << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(Goat());
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}