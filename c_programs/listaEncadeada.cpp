#include <iostream>
using namespace std;

class Node 
{
    public:
        int data;
        Node* next;
        Node(int data) : data(data), next(nullptr) {}
};

class LinkedList 
{
    private:
        Node* head;

    public:
        LinkedList() : head(nullptr) {}
        void insert(int data) 
        {
            Node* newNode = new Node(data);
            newNode -> next = head;
            head = newNode;
        }

        void display() 
        {
            Node* current = head;
            while (current != nullptr) 
            {
                cout << current -> data << " ";
                current = current -> next;
            }
            cout << endl;
        }

        bool search(int key) 
        {
            Node* current = head;
            while (current != nullptr) 
            {
                if (current -> data == key)
                    return true;
                current = current -> next;
            }
            return false;
        }

        void remove(int key) 
        {
            Node* current = head;
            Node* prev = nullptr;

            while (current != nullptr && current -> data != key) 
            {
                prev = current;
                current = current -> next;
            }

            if (current == nullptr)
                return;

            if (prev == nullptr)
                head = current -> next;
            else
                prev -> next = current -> next;

            delete current;
        }
};

int main() 
{
    LinkedList list;

    list.insert(5);
    list.insert(10);
    list.insert(15);
    list.insert(20);

    cout << "Lista: ";
    list.display();

    int key = 10;
    if (list.search(key))
        cout << key << " encontrado na lista.\n";
    else
        cout << key << " nao encontrado na lista.\n";

    key = 15;
    list.remove(key);
    cout << "Removendo " << key << " da lista.\n";

    cout << "Lista: ";
    list.display();

    return 0;
}
