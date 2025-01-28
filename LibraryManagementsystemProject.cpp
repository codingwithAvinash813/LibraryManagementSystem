#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& t, const string& a) : title(t), author(a) {}
};

class Library {
private:
    vector<Book> books;
    const string password = "newtonharamihai";  // Password to remove books (Secret Agent Stuff)

    // Helper function to display books
    void displayBooks(const vector<Book>& booksList) const {
        if (booksList.empty()) {
            cout << "\nOops! Looks like we are out of books!\n";
        } else {
            for (const auto& book : booksList) {
                cout << left << setw(30) << book.title << " | " << book.author << endl;
            }
        }
    }

    // Helper function to trim whitespace from strings
    string trim(const string& str) const {
        size_t first = str.find_first_not_of(" \t\n\r\f\v");
        size_t last = str.find_last_not_of(" \t\n\r\f\v");
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    // Convert string to lowercase for case-insensitive comparison
    string toLower(const string& str) const {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:
    Library() {
        // Predefined books from various famous authors and genres (because who doesn't love a classic?)
        books.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald"));
        books.push_back(Book("1984", "George Orwell"));
        books.push_back(Book("To Kill a Mockingbird", "Harper Lee"));
        books.push_back(Book("Moby Dick", "Herman Melville"));
        books.push_back(Book("Pride and Prejudice", "Jane Austen"));
        books.push_back(Book("Batman: The Killing Joke", "Alan Moore"));
        books.push_back(Book("Superman: Red Son", "Mark Millar"));
        books.push_back(Book("Marvel's The Avengers", "Stan Lee"));
        books.push_back(Book("Spider-Man: Birth of Venom", "David Michelinie"));
        books.push_back(Book("Watchmen", "Alan Moore"));
        books.push_back(Book("X-Men: Days of Future Past", "Chris Claremont"));
        books.push_back(Book("Hamlet", "William Shakespeare"));
        books.push_back(Book("Romeo and Juliet", "William Shakespeare"));
        books.push_back(Book("Macbeth", "William Shakespeare"));
        books.push_back(Book("Sapiens: A Brief History of Humankind", "Yuval Noah Harari"));
        books.push_back(Book("Principles of Economics", "Alfred Marshall"));
    }

    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        cout << "\nYay! You just added \"" << title << "\" by " << author << " to the library!\n";
    }

    void viewBooks() const {
        cout << "\nHere are the books currently in our humble library (drumroll please)...\n";
        displayBooks(books);
    }

    void viewBooksByAuthor(const string& author) const {
        vector<Book> authorBooks;
        string lowerAuthor = toLower(trim(author));

        for (const auto& book : books) {
            if (toLower(trim(book.author)) == lowerAuthor) {
                authorBooks.push_back(book);
            }
        }

        if (authorBooks.empty()) {
            cout << "\nNo books found by the mysterious author: " << author << " (They must be in another dimension!)\n";
        } else {
            cout << "\nBooks by the legendary " << author << ":\n";
            displayBooks(authorBooks);
        }
    }

    void viewAuthors() const {
        set<string> authors;
        for (const auto& book : books) {
            authors.insert(book.author);
        }

        cout << "\nAuthors in our library (the famous, the infamous, and the underrated):\n";
        for (const auto& author : authors) {
            cout << author << endl;
        }
    }

    void removeBook(const string& title) {
        string enteredPassword;
        cout << "\nOnly the true book ninja can remove books. Enter password: ";
        cin >> enteredPassword;

        if (enteredPassword != password) {
            cout << "Nope! Nice try though. You need the secret password to delete books.\n";
            return;
        }

        auto it = remove_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "\nBOOM! You've successfully deleted \"" << title << "\" from the library. It's like magic.\n";
        } else {
            cout << "\nUh-oh! \"" << title << "\" wasn't found in our collection. Maybe it's hiding?\n";
        }
    }

    void showMenu() {
        int choice;
        string title, author;

        while (true) {
            cout << "\nWelcome to the Quirky Library Management System\n";
            cout << "==============================================\n";
            cout << "1. Add a Book (Feel free to be the book wizard)\n";
            cout << "2. View All Books (Like a boss)\n";
            cout << "3. View Books by Author (Find the genius behind the words)\n";
            cout << "4. View List of Authors (The People Behind the Magic)\n";
            cout << "5. Remove Book (Delete like a secret agent!)\n";
            cout << "6. Exit (Escape the library... for now)\n";
            cout << "Enter your choice (1-6): ";
            cin >> choice;
            cin.ignore();  // To clear the input buffer

            switch (choice) {
                case 1:
                    cout << "\nEnter Book Title: ";
                    getline(cin, title);
                    cout << "Enter Author Name: ";
                    getline(cin, author);
                    addBook(title, author);
                    break;
                case 2:
                    viewBooks();
                    break;
                case 3:
                    cout << "\nEnter Author's Name: ";
                    getline(cin, author);
                    viewBooksByAuthor(author);
                    break;
                case 4:
                    viewAuthors();
                    break;
                case 5:
                    cout << "\nEnter Book Title to Remove: ";
                    getline(cin, title);
                    removeBook(title);
                    break;
                case 6:
                    cout << "\nGoodbye, book lover! May your shelves never be empty.\n";
                    return;
                default:
                    cout << "\nOops, I think you pressed the wrong button. Try again!\n";
            }
        }
    }
};

int main() {
    Library library;
    library.showMenu();
    return 0;
}


