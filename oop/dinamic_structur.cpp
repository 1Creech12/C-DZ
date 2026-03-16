
#include <iostream>
using namespace std;
/*
Динамичские структуры - 
new delete, умный указатель

Принцип FIFO - первый вошел - первый ушел!

Односвязоного списка
#include <iostream>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t count;

public:
    LinkedList() : head(nullptr), count(0) {}

    // Деструктор - освобождает память всех узлов
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Запрет копирования для простоты (можно реализовать, но это отдельная задача)
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++count;
    }

    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
            --count;
        }
    }

    bool empty() const { return head == nullptr; }
    size_t size() const { return count; }

    // Класс-итератор для обхода списка (упрощённо)!!!
    class Iterator {
        Node* ptr;
    public:
        Iterator(Node* p) : ptr(p) {}
        T& operator*() const { return ptr->data; }
        Iterator& operator++() { ptr = ptr->next; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};


стек памяти<T> - структура данных, работает по принципу последний вошел первый вышел 

include <stack>


template <typename T>
class Stack {
private:
    T* arr;
    size_t capacity;
    size_t topIndex;

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (size_t i = 0; i < topIndex; ++i)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Stack(size_t initCap = 10) : capacity(initCap), topIndex(0) {
        arr = new T[capacity];
    }

    ~Stack() {
        delete[] arr;
    }

    // Копирование (правило трёх) – для простоты опущено

    void push(const T& value) {
        if (topIndex == capacity)
            resize();
        arr[topIndex++] = value;
    }

    void pop() {
        if (topIndex > 0)
            --topIndex;
    }

    T& top() {
        return arr[topIndex - 1];
    }

    bool empty() const { return topIndex == 0; }
    size_t size() const { return topIndex; }
};

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}// !
    };

    Node* root;

    void insert(Node*& node, const T& value) {
        if (!node)
            node = new Node(value);
        else if (value < node->data)
            insert(node->left, value);
        else if (value > node->data)
            insert(node->right, value);
        // если равно – ничего не делаем (или можно обработать)
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        insert(root, value);
    }

    void printInorder() const {
        inorder(root);
        std::cout << std::endl;
    }

    // Поиск, удаление и т.д. – аналогично
};
*/
#include <iostream>
#include <memory> // для std::unique_ptr

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::unique_ptr<Node> head; // указатель на начало
    Node* tail;                 // сырой указатель на конец (для быстрой вставки)
    size_t count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    // Запрещаем копирование для простоты (можно реализовать при необходимости)
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    ~Queue() {
        // unique_ptr автоматически удалит всю цепочку
    }

    void enqueue(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        Node* newTail = newNode.get();
        if (tail) {
            tail->next = std::move(newNode);
        }
        else {
            head = std::move(newNode);
        }
        tail = newTail;
        ++count;
    }

    void dequeue() {
        if (head) {
            head = std::move(head->next);
            if (!head) tail = nullptr;
            --count;
        }
    }

    T& front() const {
        return head->data;
    }

    bool empty() const { return head == nullptr; }
    size_t size() const { return count; }
};

// Пример использования
int main() {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Front: " << q.front() << std::endl; // 10
    q.dequeue();
    std::cout << "Front after dequeue: " << q.front() << std::endl; // 20
    std::cout << "Size: " << q.size() << std::endl; // 2

    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.dequeue();
    } // 20 30
    std::cout << std::endl;
    return 0;
}


#include <iostream>
#include <string>

template <typename T>
class Stack {
private:
    T* arr;
    size_t capacity;
    size_t topIndex;

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (size_t i = 0; i < topIndex; ++i)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Stack(size_t initCap = 10) : capacity(initCap), topIndex(0) {
        arr = new T[capacity];
    }

    ~Stack() {
        delete[] arr;
    }

    // Копирование опустим

    void push(const T& value) {
        if (topIndex == capacity)
            resize();
        arr[topIndex++] = value;
    }

    void pop() {
        if (topIndex > 0)
            --topIndex;
    }

    T& top() {
        return arr[topIndex - 1];
    }

    bool empty() const { return topIndex == 0; }
    size_t size() const { return topIndex; }
};

bool checkBrackets(const std::string& expr) {
    Stack<char> st;
    for (char ch : expr) {
        if (ch == '('  ch == '['  ch == '{') {
            st.push(ch);
        }
        else if (ch == ')'  ch == ']'  ch == '}') {
            if (st.empty()) return false;
            char top = st.top();
            if ((ch == ')' && top != '(')
                (ch == ']' && top != '[')
                (ch == '}' && top != '{')) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    std::string test1 = "((a+b)*[c-d])";
    std::string test2 = "([)]";
    std::string test3 = "{[]}";

    std::cout << test1 << " -> " << (checkBrackets(test1) ? "OK" : "ERROR") << std::endl;
    std::cout << test2 << " -> " << (checkBrackets(test2) ? "OK" : "ERROR") << std::endl;
    std::cout << test3 << " -> " << (checkBrackets(test3) ? "OK" : "ERROR") << std::endl;
    return 0;
}
#include <iostream>
#include <algorithm>

class BST {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, int value) {
        if (!node)
            node = new Node(value);
        else if (value < node->data)
            insert(node->left, value);
        else if (value > node->data)
            insert(node->right, value);
        // равные игнорируем
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    bool search(Node* node, int value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        else return search(node->right, value);
    }

    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

    // Для демонстрации: подсчёт высоты
    int height(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(int value) { insert(root, value); }
    bool search(int value) const { return search(root, value); }
    void printInorder() const { inorder(root); std::cout << std::endl; }
    int height() const { return height(root); }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    std::cout << "Inorder traversal: ";
    tree.printInorder(); // 20 30 40 50 60 70 80

    std::cout << "Search 40: " << (tree.search(40) ? "found" : "not found") << std::endl;
    std::cout << "Search 100: " << (tree.search(100) ? "found" : "not found") << std::endl;
    std::cout << "Height: " << tree.height() << std::endl; // 3 (если считать корень за 1)

    return 0;
}

// -------------------------------------------------------------------------------

// Композиция - часть-целое
class Engine
{
    string type;
public:
    Engine(const string& t) : type(t) {}
    ~Engine() {}

    void start() const {}
};

//Контейнер по отношению  к Engine
class Car
{
    Engine str1, str2; // Композиция
public:
    void drive() { // Пепеопределения
    }
};

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Department {
    std::string name;
public:
    Department(const std::string& n) : name(n) {}
    void print() const {
        std::cout << "Department: " << name << "\n";
    }
};

class University {
    std::string name;
    std::vector<std::reference_wrapper<Department>> departments; // слабые ссылки
public:
    University(const std::string& n) : name(n) {}
    void addDepartment(Department& dept) {
        departments.push_back(dept);
    }
    void showDepartments() const {
        std::cout << "University " << name << " has departments:\n";
        for (const auto& deptRef : departments) {
            deptRef.get().print();
        }
    }
};

int main() {
    Department cs("Computer Science");
    Department math("Mathematics");
    {
        University uni("Oxford");
        uni.addDepartment(cs);
        uni.addDepartment(math);
        uni.showDepartments();
    } // University уничтожается, но Department продолжают существовать
    cs.print(); // отдел всё ещё жив
    return 0;
}