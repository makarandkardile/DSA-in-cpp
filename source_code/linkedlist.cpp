#include <iostream>
#include <string>
using namespace std;

struct Student
{
    int studentID;
    string name;
    int rollNo;
    int age;
    string department;

    Student* prev;
    Student* next;
};

Student* head = NULL;

// Add a new student
void addStudent()
{
    Student* newNode = new Student;

    cout << "\nEnter Student ID: ";
    cin >> newNode->studentID;

    cout << "Enter Name: ";
    cin >> ws;
    getline(cin, newNode->name);

    cout << "Enter Roll Number: ";
    cin >> newNode->rollNo;

    cout << "Enter Age: ";
    cin >> newNode->age;

    cout << "Enter Department: ";
    cin >> ws;
    getline(cin, newNode->department);

    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Student* temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    cout << "\nStudent added successfully!\n";
}

// Display all students
void displayStudents()
{
    if (head == NULL)
    {
        cout << "\nNo student records found.\n";
        return;
    }

    Student* temp = head;

    cout << "\n--- Student Records ---\n";

    while (temp != NULL)
    {
        cout << "\nStudent ID: " << temp->studentID;
        cout << "\nName: " << temp->name;
        cout << "\nRoll Number: " << temp->rollNo;
        cout << "\nAge: " << temp->age;
        cout << "\nDepartment: " << temp->department;
        cout << "\n-----------------------\n";

        temp = temp->next;
    }
}

// Search for a student
void searchStudent()
{
    int id;
    cout << "\nEnter Student ID to search: ";
    cin >> id;

    Student* temp = head;

    while (temp != NULL)
    {
        if (temp->studentID == id)
        {
            cout << "\nStudent Found!\n";
            cout << "Name: " << temp->name << endl;
            cout << "Roll Number: " << temp->rollNo << endl;
            cout << "Age: " << temp->age << endl;
            cout << "Department: " << temp->department << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "\nStudent not found.\n";
}

// Delete a student
void deleteStudent()
{
    int id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;

    Student* temp = head;

    while (temp != NULL && temp->studentID != id)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "\nStudent not found.\n";
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    delete temp;

    cout << "\nStudent deleted successfully!\n";
}

// Free allocated memory
void freeMemory()
{
    while (head != NULL)
    {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== STUDENT DATABASE MANAGEMENT =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                freeMemory();
                cout << "\nProgram terminated.\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
