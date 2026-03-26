#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class User
{
public:
    string name;
    User() {}
    User(string name) : name(name) {} // Add this constructor
    virtual void display() = 0; // Pure virtual function makes User an abstract base class
};

class Book
{
public:
    string name;
    string author;
};

class Student : public User
{
public:
    string id;
    string voucher;
    void display() override
    {
        cout << "Student Name: " << name << ", ID: " << id << ", Voucher: " << voucher << '\n';
    }
};

class Admin : public User
{
public:
    string password;
    Admin(string name, string password) : User(name), password(password) {} // Call User's constructor here
    void display() override
    {
        cout << "Admin Name: " << name << ", Password: " << password << '\n';
    }
};

int main()
{
    Book books[100] = {
        {"Discrete Mathematics and its Applications, 7th Edition","K. Rosen, McGraw Hill"},
        {"Teach Yourself C++","Herbert Schildt"},
        {"Introductory Methods of Numerical Analysis","S. S. Sastry"},
        {"Electronic Device and Circuit Theory","Robert L. Boylestad"},
        {"Ordinary and Partial Differential Equations","M.D. Raisinghania"}
        };
    Student students[100];
    Admin admin = {"admin", "password"};
    int n = 5;

    int choice;
    int studentCount = 0;

    while (true)
    {
        cout << "\n\t\t\tWelcome to Library\n";
        cout << "Main Menu:\n\n";
        cout << "1. Book Catalogue\n";
        cout << "2. Book Return\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";
        cout << "\nPlease Choose an Option: ";
        cin >> choice;

        if (choice == 1)
        {
            while (true)
            {
                cout << "\nAvailable Books:\n\n";
                int sl = 1;
                for (int i = 0; i < n; ++i)
                {
                    cout << sl++ << ". " << books[i].name << " by " << books[i].author << '\n';
                }
                cout << sl << ". Back to Main Menu\n";
                cout << "\nPlease Choose an Option: ";
                cin >> choice;

                if (choice > n + 1 || choice < 1)
                {
                    cout << "\nInvalid choice\n";
                    continue;
                }
                else if (choice == n + 1)
                {
                    break; // Back to main menu
                }

                // Process book borrowing
                cout << "\nDo you want to borrow it? (y/n): ";
                char borrow;
                cin >> borrow;
                if (borrow == 'y' || borrow == 'Y')
                {
                    cout << "Enter your name: ";
                    cin >> students[studentCount].name;
                    cout << "Enter your id: ";
                    cin >> students[studentCount].id;
                    students[studentCount].voucher = students[studentCount].name + to_string(studentCount); // Generate a unique voucher for each student
                    studentCount++;
                    cout << "Book borrowed successfully! Your voucher is: " << students[studentCount - 1].voucher << '\n';
                    // Write the voucher to a file
                    ofstream outFile("vouchers.txt", ios_base::app);
                    outFile << students[studentCount - 1].name << ", " << students[studentCount - 1].id << ", " << students[studentCount - 1].voucher << '\n';
                    outFile.close();
                }
            }
        }
        else if (choice == 2)
        {
            // Process book return
            cout << "\nEnter your voucher number to return the book: ";
            string returnVoucher;
            cin >> returnVoucher;
            bool validVoucher = false;
            for (int i = 0; i < studentCount; ++i)
            {
                if (students[i].voucher == returnVoucher)
                {
                    validVoucher = true;
                    // Erase the voucher from the file
                    ifstream inFile("vouchers.txt");
                    ofstream tempFile("temp.txt");
                    string line;
                    while (getline(inFile, line))
                    {
                        string name, id, voucher;
                        istringstream iss(line);
                        getline(iss, name, ',');
                        getline(iss, id, ',');
                        getline(iss, voucher, ',');
                        if (voucher != returnVoucher)
                        {
                            tempFile << line << '\n';
                        }
                    }
                    inFile.close();
                    tempFile.close();
                    remove("vouchers.txt");
                    rename("temp.txt", "vouchers.txt");
                    break;
                }
            }
            if (validVoucher)
            {
                cout << "\nBook returned successfully!\n";
            }
            else
            {
                cout << "\nInvalid voucher!\n";
            }
        }
        else if (choice == 3)
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (username == admin.name && password == admin.password)
            {
                cout << "\nAdmin logged in successfully!\n\n";
                // Admin functionalities
                while (true)
                {
                    cout << "\nAdmin Menu:\n\n";
                    cout << "1. Add Book\n";
                    cout << "2. Remove Book\n";
                    cout << "3. Back to Main Menu\n";
                    cout << "\nPlease Choose an Option: ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        // Add Book
                        cout << "Enter book name: ";
                        string newBookName;
                        cin.ignore(); // Ignore any previous newline character in the input buffer
                        getline(cin, newBookName); // Allowing for spaces in book name
                        cout << "Enter author name: ";
                        string newBookAuthor;
                        getline(cin, newBookAuthor); // Allow for spaces in author name
                        // Add the book to the array
                        books[n].name = newBookName;
                        books[n].author = newBookAuthor;
                        n++;
                        cout << "\nBook added successfully!\n";
                    }
                    else if (choice == 2)
                    {
                        // Remove Book
                        cout << "\nAvailable Books:\n";
                        for (int i = 0; i < n; ++i)
                        {
                            cout << i + 1 << ". " << books[i].name << " by " << books[i].author << '\n';
                        }
                        cout << "\nEnter book number to remove: ";
                        int bookNumber;
                        cin >> bookNumber;
                        if (bookNumber >= 1 && bookNumber <= n)
                        {
                            for (int i = bookNumber - 1; i < n - 1; i++)
                            {
                                books[i] = books[i + 1];
                            }
                            n--;
                            cout << "\nBook removed successfully!\n";
                        }
                        else
                        {
                            cout << "\nInvalid book number!\n";
                        }
                    }
                    else if (choice == 3)
                    {
                        break; // Back to main menu
                    }
                    else
                    {
                        cout << "\nInvalid choice\n";
                    }
                }
            }
            else
            {
                cout << "\nInvalid admin credentials!\n";
            }
        }
        else if (choice == 4)
        {
            cout << "\n\t\t\tThank You for visiting our library.\n";
            break; // Exit the program
        }
        else
        {
            cout << "\nInvalid choice\n";
        }
    }

    return 0;
}
