#include <iostream>
#include <string>
using namespace std;

// Задание 1
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    size_t list_size;
    
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    
public:
    SinglyLinkedList() : head(nullptr), list_size(0) {}
    
    ~SinglyLinkedList() {
        clear();
    }
    
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        list_size++;
    }
    
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        list_size++;
    }
    
    void pop_front() {
        if (empty()) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        list_size--;
    }
    
    void pop_back() {
        if (empty()) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next && current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        list_size--;
    }
    
    T& front() {
        return head->data;
    }
    
    T& back() {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->data;
    }
    
    bool empty() const {
        return head == nullptr;
    }
    
    size_t size() const {
        return list_size;
    }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        list_size = 0;
    }
};

// Задание 2
template <typename T>
class Stack {
private:
    T* arr;
    size_t capacity;
    size_t stack_top;  // индекс вершины (количество элементов)
    
    void resize() {
        capacity *= 2;
        T* new_arr = new T[capacity];
        for (size_t i = 0; i < stack_top; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }
    
public:
    Stack(size_t initial_capacity = 10) : capacity(initial_capacity), stack_top(0) {
        arr = new T[capacity];
    }
    
    ~Stack() {
        delete[] arr;
    }
    
    Stack(const Stack& other) : capacity(other.capacity), stack_top(other.stack_top) {
        arr = new T[capacity];
        for (size_t i = 0; i < stack_top; i++) {
            arr[i] = other.arr[i];
        }
    }
    
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] arr;
            capacity = other.capacity;
            stack_top = other.stack_top;
            arr = new T[capacity];
            for (size_t i = 0; i < stack_top; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    
    void push(const T& value) {
        if (stack_top >= capacity) {
            resize();
        }
        arr[stack_top++] = value;
    }
    
    void pop() {
        if (!empty()) {
            stack_top--;
        }
    }
    
    T& top() {
        return arr[stack_top - 1];
    }
    
    bool empty() const {
        return stack_top == 0;
    }
    
    size_t size() const {
        return stack_top;
    }
};

int main() {
    cout << "Задание 1:" << endl;
    
    SinglyLinkedList<int> list;
    
    cout << "Пустой? " << (list.empty() ? "да" : "нет") << endl;
    
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.push_front(1);
    
    cout << "Размер: " << list.size() << endl;
    cout << "Первый: " << list.front() << endl;
    cout << "Последний: " << list.back() << endl;
    
    list.pop_front();
    cout << "После pop_front, первый: " << list.front() << endl;
    
    list.pop_back();
    cout << "После pop_back, последний: " << list.back() << endl;
    
    list.clear();
    cout << "После clear, размер: " << list.size() << endl;
    
    // Список со строками
    SinglyLinkedList<string> str_list;
    str_list.push_back("Привет");
    str_list.push_back("Мир");
    cout << "Строковый список: " << str_list.front() << " " << str_list.back() << endl;
    
    cout << "\nЗадание 2:" << endl;
    
    string test_strings[] = {"radar", "hello", "madam", "world"};
    
    for (const string& s : test_strings) {
        Stack<char> st;
        
        for (char c : s) {
            st.push(c);
        }
        
        bool is_palindrome = true;
        for (char c : s) {
            if (c != st.top()) {
                is_palindrome = false;
                break;
            }
            st.pop();
        }
        
        cout << "\"" << s << "\" - " << (is_palindrome ? "палиндром" : "не палиндром") << endl;
    }
    
    cout << "\nДемонстрация стека:" << endl;
    Stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);
    
    cout << "Вершина: " << st.top() << endl;
    cout << "Размер: " << st.size() << endl;
    
    st.pop();
    cout << "После pop, вершина: " << st.top() << endl;
    cout << "Размер: " << st.size() << endl;
    
    return 0;
}