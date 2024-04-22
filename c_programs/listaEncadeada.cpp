#include <iostream>
using namespace std;

// Definição da estrutura do nó da lista
class Node 
{
    public:
        int data;
        Node* next;

        // Construtor
        Node(int data) : data(data), next(nullptr) {}
};

// Definição da classe da lista encadeada
class LinkedList 
{
    private:
        Node* head;

    public:
        // Construtor
        LinkedList() : head(nullptr) {}

        // Método para inserir um elemento no início da lista
        void insert(int data) 
        {
            Node* newNode = new Node(data);
            newNode -> next = head;
            head = newNode;
        }

        // Método para exibir os elementos da lista
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

        // Método para buscar um elemento na lista
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

        // Método para excluir um elemento da lista
        void remove(int key) 
        {
            Node* current = head;
            Node* prev = nullptr;

            // Procurar o elemento a ser excluído
            while (current != nullptr && current -> data != key) 
            {
                prev = current;
                current = current -> next;
            }

            // Se o elemento não foi encontrado
            if (current == nullptr)
                return;

            // Remover o elemento
            if (prev == nullptr)
                head = current -> next; // Se o elemento a ser excluído for o primeiro
            else
                prev -> next = current -> next; // Se o elemento a ser excluído estiver no meio ou no final

            delete current;
        }
};

// =====================================================================================================================

int main() 
{
    // Criar uma lista encadeada
    LinkedList list;

    // Inserir elementos
    list.insert(5);
    list.insert(10);
    list.insert(15);
    list.insert(20);

    // Exibir os elementos
    cout << "Lista: ";
    list.display();

    // Buscar um elemento
    int key = 10;
    if (list.search(key))
        cout << key << " encontrado na lista.\n";
    else
        cout << key << " nao encontrado na lista.\n";

    // Remover um elemento
    key = 15;
    list.remove(key);
    cout << "Removendo " << key << " da lista.\n";

    // Exibir os elementos após a remoção
    cout << "Lista: ";
    list.display();

    return 0;
}
