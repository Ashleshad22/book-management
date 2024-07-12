#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;

    Book(string t, string a, string i) : title(t), author(a), isbn(i) {}

    void display() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn << endl;
    }
};

class Node {
public:
    Book book;
    Node* next;

    Node(Book b) : book(b), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void addBook(const Book& book) {
        Node* newNode = new Node(book);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void displayBooks() const {
        Node* current = head;
        while (current) {
            current->book.display();
            current = current->next;
        }
    }
};

class BSTNode {
public:
    Book book;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Book b) : book(b), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BSTNode* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(const Book& book) {
        if (!root) {
            root = new BSTNode(book);
        } else {
            insertHelper(root, book);
        }
    }

    void insertHelper(BSTNode* node, const Book& book) {
        if (book.title < node->book.title) {
            if (!node->left) {
                node->left = new BSTNode(book);
            } else {
                insertHelper(node->left, book);
            }
        } else {
            if (!node->right) {
                node->right = new BSTNode(book);
            } else {
                insertHelper(node->right, book);
            }
        }
    }

    BSTNode* search(const string& title) const {
        return searchHelper(root, title);
    }

    BSTNode* searchHelper(BSTNode* node, const string& title) const {
        if (!node || node->book.title == title) {
            return node;
        }
        if (title < node->book.title) {
            return searchHelper(node->left, title);
        }
        return searchHelper(node->right, title);
    }

    void inOrderTraversal(BSTNode* node) const {
        if (node) {
            inOrderTraversal(node->left);
            node->book.display();
            inOrderTraversal(node->right);
        }
    }
};

class HashTable {
private:
    vector<vector<Book>> table;
    int size;

    int hashFunction(const string& isbn) const {
        int hash = 0;
        for (char c : isbn) {
            hash = (hash * 31 + c) % size;
        }
        return hash;
    }

public:
    HashTable(int s = 100) : size(s) {
        table.resize(size);
    }

    void insert(const Book& book) {
        int index = hashFunction(book.isbn);
        table[index].push_back(book);
    }

    bool deleteBook(const string& isbn) {
        int index = hashFunction(isbn);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->isbn == isbn) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    Book* search(const string& isbn) {
        int index = hashFunction(isbn);
        for (auto& book : table[index]) {
            if (book.isbn == isbn) {
                return &book;
            }
        }
        return nullptr;
    }
};

int main() {
    LinkedList linkedList;
    BinarySearchTree bst;
    HashTable hashTable;

    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Display All Books" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline character left in the buffer

        if (choice == 1) {
            string title, author, isbn;
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, isbn);

            Book book(title, author, isbn);
            linkedList.addBook(book);
            bst.insert(book);
            hashTable.insert(book);
            cout << "Book added successfully!" << endl;

        } else if (choice == 2) {
            string isbn;
            cout << "Enter book ISBN to delete: ";
            getline(cin, isbn);
            if (hashTable.deleteBook(isbn)) {
                cout << "Book deleted successfully!" << endl;
            } else {
                cout << "Book not found!" << endl;
            }

        } else if (choice == 3) {
            int searchType;
            cout << "Search by (1) Title or (2) ISBN: ";
            cin >> searchType;
            cin.ignore();  // Ignore the newline character left in the buffer

            if (searchType == 1) {
                string title;
                cout << "Enter book title: ";
                getline(cin, title);
                BSTNode* node = bst.search(title);
                if (node) {
                    cout << "Book found: ";
                    node->book.display();
                } else {
                    cout << "Book not found!" << endl;
                }
            } else if (searchType == 2) {
                string isbn;
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                Book* book = hashTable.search(isbn);
                if (book) {
                    cout << "Book found: ";
                    book->display();
                } else {
                    cout << "Book not found!" << endl;
                }
            }

        } else if (choice == 4) {
            cout << "Books in collection:" << endl;
            linkedList.displayBooks();

        } else if (choice == 5) {
            break;

        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
