#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

// Base class for all library items
class LibraryItem {
protected:
    std::string title;
    int id;

public:
    LibraryItem(const std::string& title, int id) : title(title), id(id) {}
    virtual ~LibraryItem() {}

    virtual void display() const = 0; // Pure virtual function for abstraction

    int getId() const { return id; }
};

// Derived class for books
class Book : public LibraryItem {
private:
    std::string author;

public:
    Book(const std::string& title, int id, const std::string& author)
        : LibraryItem(title, id), author(author) {}

    void display() const override {
        std::cout << "enter book id: " << id << ", enter title: " << title << ",author: " << author << std::endl;
    }
};

// Derived class for magazines
class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(const std::string& title, int id, int issueNumber)
        :LibraryItem(title, id), issueNumber(issueNumber) {}

    void display() const override {
        std::cout << "enter magazine id: " << id << ", enter title: " << title << ", enter issue number: " << issueNumber << std::endl;
    }
};

// Class for managing the library
class Library {
private:
    std::vector<LibraryItem*> items;

public:
    ~Library() {
        for (auto item : items) {
            delete item;
        }
    }

    void addItem(LibraryItem* item) {
        items.push_back(item);
    }

    void displayItems() const {
        for (const auto& item : items) {
            item->display();
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Could not open file for writing");
        }
        for (const auto& item : items) {
            outFile << item->getId() << "," << typeid(*item).name() << "," << "\n";
        }
    }
};

// Command line interface for interacting with the library
void commandLineInterface() {
    Library library;
    bool running = true;

    while (running) {
        std::cout << "Library System\n1. Add Book\n2. Add Magazine\n3. Display Items\n4. Save to File\n5. Exit\nChoose an option: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::string title, author;
                    int id;
                    std::cout << "Enter Book ID, Title, and Author: ";
                    std::cin >> id >> title >> author;
                    library.addItem(new Book(title, id, author));
                    break;
                }
                case 2: {
                    std::string title;
                    int id, issueNumber;
                    std::cout << "Enter Magazine ID, Title, and Issue Number: ";
                    std::cin >> id >> title >> issueNumber;
                    library.addItem(new Magazine(title, id, issueNumber));
                    break;
                }
                case 3:
                    library.displayItems();
                    break;
                case 4: {
                    std::string filename;
                    std::cout << "Enter filename to save: ";
                    std::cin >> filename;
                    library.saveToFile(filename);
                    break;
                }
                case 5:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    commandLineInterface();
    return 0;
}
