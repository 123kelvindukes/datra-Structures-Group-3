#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;


struct Book {
    int id;
    string title;
    string author;
    int year;

    Book* prev;
    Book* next;
};


class Library {
private:
    Book* head;
    Book* tail;

    // Find a book using its ID
    Book* findBook(int id) const {
        Book* current = head;

        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }

    // Read a valid integer
    int readInteger(string message, int minValue,
                    int maxValue) const {
        string input;
        int value;
        char extra;

        while (true) {
            cout << message;
            getline(cin, input);

            stringstream ss(input);

            if (ss >> value && !(ss >> extra)) {
                if (value >= minValue &&
                    value <= maxValue) {
                    return value;
                }
            }

            cout << "Invalid input! Enter a number between "
                 << minValue << " and " << maxValue << ".\n";
        }
    }

    // Read non-empty text
    string readText(string message) {
        string value;

        while (true) {
            cout << message;
            getline(cin, value);

            if (!value.empty() &&
                value.find_first_not_of(" \t") != string::npos) {
                return value;
            }

            cout << "Input cannot be empty. Try again.\n";
        }
    }

    // Display one book
    void displayBook(Book* book) const {
        cout << "\n----------------------------------\n";
        cout << "Book ID: " << book->id << endl;
        cout << "Title: " << book->title << endl;
        cout << "Author: " << book->author << endl;
        cout << "Publication Year: " << book->year << endl;
        cout << "----------------------------------\n";
    }

public:

    // Constructor
    Library() {
        head = nullptr;
        tail = nullptr;
    }

    // Destructor: free allocated memory
    ~Library() {
        Book* current = head;

        while (current != nullptr) {
            Book* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
    }



    void addBook() {
        cout << "\n========== ADD NEW BOOK ==========\n";

        int id = readInteger("Enter Book ID: ", 1, 1000000);

        if (findBook(id) != nullptr) {
            cout << "\nError: A book with this ID already exists!\n";
            return;
        }

        string title = readText("Enter Book Title: ");
        string author = readText("Enter Author Name: ");
        int year = readInteger("Enter Publication Year: ",
                               1000, 9999);

        Book* newBook = new Book;

        newBook->id = id;
        newBook->title = title;
        newBook->author = author;
        newBook->year = year;

        newBook->prev = nullptr;
        newBook->next = nullptr;

        // If the list is empty
        if (head == nullptr) {
            head = newBook;
            tail = newBook;
        }

        // If the list already contains books
        else {
            tail->next = newBook;
            newBook->prev = tail;
            tail = newBook;
        }

        cout << "\nBook added successfully!\n";
    }


    void removeBook() {
        cout << "\n========== REMOVE BOOK ==========\n";

        if (head == nullptr) {
            cout << "The library is empty.Nothing to remove.\n";
            return;
        }

        int id = readInteger("Enter Book ID to remove: ",
                             1, 1000000);

        Book* current = findBook(id);

        if (current == nullptr) {
            cout << "\nBook not found!\n";
            return;
        }

        // If the book is the first node
        if (current == head) {
            head = current->next;
        }

        // If the book is the last node
        if (current == tail) {
            tail = current->prev;
        }

        // Connect the previous node to the next node
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }

        // Connect the next node to the previous node
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }

        delete current;

        cout << "\nBook removed successfully!\n";

        if (head == nullptr) {
            tail = nullptr;
        }
    }



    void searchBook() const {
        cout << "\n========== SEARCH BOOK ==========\n";

        if (head == nullptr) {
            cout << "The library is empty.\n";
            return;
        }

        int id = readInteger("Enter Book ID to search: ",
                             1, 1000000);

        Book* result = findBook(id);

        if (result == nullptr) {
            cout << "\nBook not found!\n";
        } else {
            cout << "\nBook found successfully!";
            displayBook(result);
        }
    }


    void displayForward() const {
        cout << "\n========== BOOKS (FORWARD) ==========\n";

        if (head == nullptr) {
            cout << "The library is empty.\n";
            return;
        }

        Book* current = head;

        while (current != nullptr) {
            displayBook(current);
            current = current->next;
        }

        cout << "\nEnd of book collection.\n";
    }



    void displayBackward() const {
        cout << "\n========== BOOKS (BACKWARD) ==========\n";

        if (tail == nullptr) {
            cout << "The library is empty.\n";
            return;
        }

        Book* current = tail;

        while (current != nullptr) {
            displayBook(current);
            current = current->prev;
        }

        cout << "\nBeginning of book collection.\n";
    }


    void updateBook() {
        cout << "\n========== UPDATE BOOK ==========\n";

        if (head == nullptr) {
            cout << "The library is empty. Nothing to update.\n";
            return;
        }

        int id = readInteger("Enter Book ID to update: ",
                             1, 1000000);

        Book* current = findBook(id);

        if (current == nullptr) {
            cout << "\nBook not found!\n";
            return;
        }

        cout << "\nCurrent Book Details:";
        displayBook(current);

        cout << "\nEnter the new details below:\n";

        current->title = readText("Enter New Title: ");
        current->author = readText("Enter New Author: ");
        current->year = readInteger("Enter New Publication Year: ",
                                    1000, 9999);

        cout << "\nBook details updated successfully!\n";
    }

};



int main() {

    Library library;

    int choice;

    do {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "       UNIVERSITY LIBRARY MANAGEMENT\n";cout << "============================================\n";

        cout << "1. Add New Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book\n";
        cout << "4. Display Books Forward\n";
        cout << "5. Display Books Backward\n";
        cout << "6. Update Book Details\n";
        cout << "7. Exit\n";

        cout << "============================================\n";

        // Validate menu choice
        string input;
        stringstream ss;
        char extra;

        while (true) {
            cout << "Enter your choice (1-7): ";
            getline(cin, input);

            ss.clear();
            ss.str(input);

            if (ss >> choice && !(ss >> extra) &&
                choice >= 1 && choice <= 7) {
                break;
            }

            cout << "Invalid choice! Please enter a number from 1 to 7.\n";
        }

        switch (choice) {

            case 1:
                library.addBook();
                break;

            case 2:
                library.removeBook();
                break;

            case 3:
                library.searchBook();
                break;

            case 4:
                library.displayForward();
                break;

            case 5:
                library.displayBackward();
                break;

            case 6:
                library.updateBook();
                break;

            case 7:
                cout << "\nThank you for using the University Library System!\n";
                cout << "Program terminated successfully.\n";
                break;
        }

    } while (choice != 7);

    return 0;
}
