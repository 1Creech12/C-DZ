#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool is_borrowed;
    
public:
    Book(const string& t, const string& a, const string& i) 
        : title(t), author(a), isbn(i), is_borrowed(false) {
        cout << "Книга \"" << title << "\" создана" << endl;
    }
    
    ~Book() {
        cout << "Книга \"" << title << "\" уничтожена" << endl;
    }
    
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    bool isBorrowed() const { return is_borrowed; }
    
    void borrow() {
        if (!is_borrowed) {
            is_borrowed = true;
            cout << "Книга \"" << title << "\" выдана" << endl;
        } else {
            cout << "Книга \"" << title << "\" уже выдана" << endl;
        }
    }
    
    void returnBook() {
        if (is_borrowed) {
            is_borrowed = false;
            cout << "Книга \"" << title << "\" возвращена" << endl;
        } else {
            cout << "Книга \"" << title << "\" не была выдана" << endl;
        }
    }
    
    void display() const {
        cout << "  \"" << title << "\" - " << author 
             << " (ISBN: " << isbn << ")" 
             << (is_borrowed ? " [ВЫДАНА]" : " [В НАЛИЧИИ]") << endl;
    }
};

class Library {
private:
    string name;
    Book** books;
    int count;
    int capacity;
    
    void resize() {
        capacity *= 2;
        Book** new_books = new Book*[capacity];
        for (int i = 0; i < count; i++) {
            new_books[i] = books[i];
        }
        delete[] books;
        books = new_books;
    }
    
public:
    Library(const string& n) : name(n), count(0), capacity(10) {
        books = new Book*[capacity];
        cout << "Библиотека \"" << name << "\" открыта" << endl;
    }
    
    ~Library() {
        cout << "Библиотека \"" << name << "\" закрыта" << endl;
        delete[] books;
    }
    
    void addBook(Book* book) {
        if (book) {
            if (count >= capacity) {
                resize();
            }
            books[count++] = book;
            cout << "В библиотеку добавлена книга \"" << book->getTitle() << "\"" << endl;
        }
    }
    
    void borrowBook(const string& title) {
        for (int i = 0; i < count; i++) {
            if (books[i]->getTitle() == title && !books[i]->isBorrowed()) {
                books[i]->borrow();
                return;
            }
        }
        cout << "Книга \"" << title << "\" не найдена или уже выдана" << endl;
    }
    
    void returnBook(const string& title) {
        for (int i = 0; i < count; i++) {
            if (books[i]->getTitle() == title && books[i]->isBorrowed()) {
                books[i]->returnBook();
                return;
            }
        }
        cout << "Книга \"" << title << "\" не найдена или не была выдана" << endl;
    }
    
    void displayBooks() const {
        cout << "\nКаталог библиотеки \"" << name << "\":" << endl;
        if (count == 0) {
            cout << "  Библиотека пуста" << endl;
        } else {
            for (int i = 0; i < count; i++) {
                books[i]->display();
            }
        }
        cout << endl;
    }
    
    int getBookCount() const {
        return count;
    }
};

int main() {
    
    Book* book1 = new Book("Война и мир", "Лев Толстой", "6564");
    Book* book2 = new Book("Преступление и наказание", "Федор Достоевский", "7375");
    Book* book3 = new Book("Мастер и Маргарита", "Михаил Булгаков", "2736");
    
    cout << endl;
    
    Library lib("Центральная библиотека");
    
    lib.addBook(book1);
    lib.addBook(book2);
    lib.addBook(book3);
    
    cout << endl;
    lib.displayBooks();
    
    cout << "Выдача книг" << endl;
    lib.borrowBook("Война и мир");
    lib.borrowBook("Мастер и Маргарита");
    
    cout << endl;
    lib.displayBooks();
    
    cout << "Возврат книги" << endl;
    lib.returnBook("Война и мир");
    
    cout << endl;
    lib.displayBooks();
    
    cout << "Попытка выдать выданную книгу" << endl;
    lib.borrowBook("Мастер и Маргарита");
    
    cout << "\nИтоговый каталог" << endl;
    lib.displayBooks();
    
    cout << "\nУничтожение книг" << endl;
    delete book1;
    delete book2;
    delete book3;
    
    cout << endl;
    
    return 0;
}