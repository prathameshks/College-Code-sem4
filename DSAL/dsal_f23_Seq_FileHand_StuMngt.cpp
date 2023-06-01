/*
Department maintains a student information. The file contains roll number, name,
division and address. Allow user to add, delete information of student. Display
information of particular student. If record of student does not exist an
appropriate message is displayed. If it is, then the system displays the student
details. Use sequential file to main the data.
*/

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef struct student {
    int rollNo;
    char name[50];
    char div;
    char address[100];
} student;

class studentDatabase {
    string fileName = "student_data.dat";

   public:
    studentDatabase() {
        fstream fileObj(fileName);
        if (fileObj.fail()) {
            fileObj.open(fileName, ios::out);
            cout << "New File Created" << endl;
        } else {
            cout << "Existing File Found" << endl;
        }
        fileObj.close();
    }

    void addStudent();
    void searchStudent();
    void deleteStudent();
    void displayAll();
};

void studentDatabase::searchStudent() {
    int roll;
    student s;
    bool status = false;

    // take input of roll number to delete
    cout << "Enter roll number to delete:";
    cin >> roll;

    // opening files to delete a record
    ifstream readFile;
    readFile.open(fileName, ios::in | ios::binary);

    // looking for record
    while (readFile.read((char*)&s, sizeof(student))) {
        if (s.rollNo == roll) {
            status = true;
            break;
        }
    }
    readFile.close();

    if (status) {
        cout << "Found record with details" << endl;
        cout << "Roll No:" << s.rollNo << endl;
        cout << "Name:" << s.name << endl;
        cout << "Division:" << s.div << endl;
        cout << "Address:" << s.address << endl;
    } else {
        cout << "No record found" << endl;
    }
}

void studentDatabase::deleteStudent() {
    int roll;
    student s;
    bool status = false;

    // take input of roll number to delete
    cout << "Enter roll number to delete:";
    cin >> roll;

    // opening files to delete a record
    ifstream readFile;
    readFile.open(fileName, ios::in | ios::binary);
    ofstream writeFile;
    writeFile.open("~" + fileName, ios::out | ios::binary);
    writeFile.clear();

    // looking for record
    while (readFile.read((char*)&s, sizeof(student))) {
        if (s.rollNo == roll) {
            status = true;
        } else {
            writeFile.write((char*)&s, sizeof(student)) << flush;
        }
    }
    readFile.close();
    writeFile.close();

    // moving temp file back to original file
    if (status) {
        readFile.open("~" + fileName, ios::in | ios::binary);
        writeFile.open(fileName, ios::out | ios::binary);
        writeFile.clear();

        writeFile << readFile.rdbuf();
        readFile.close();
        writeFile.close();

        // remove("~"+fileName);
        cout << "Deleted record" << endl;
    } else {
        cout << "No record found" << endl;
    }
}

void studentDatabase::addStudent() {
    student s;
    cout << "Enter Roll number of student:";
    cin >> s.rollNo;
    cout << "Enter Name of student:";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter Division of student:";
    // cin.ignore();
    cin >> s.div;
    cout << "Enter Address of student:";
    cin.ignore();
    cin.getline(s.address, 100);
    // cin.ignore();
    ofstream file(fileName, ios::out | ios::binary | ios::app);
    // file.seekp(ios::end);
    file.write((char*)&s, sizeof(student)) << flush;
    if (file.fail()) {
        cout << "Failed to add record" << endl;
    } else {
        cout << "Student record added successfully" << endl;
    }
    file.close();
}

void studentDatabase::displayAll() {
    ifstream file;
    student s;
    int count = 0;
    file.open(fileName, ios::in | ios::binary);
    while (file.read((char*)&s, sizeof(student))) {
        count++;
        cout << count << ") ";
        cout << s.rollNo << "|";
        cout << s.name << "|";
        cout << s.div << "|";
        cout << s.address << endl;
    }
    if (count == 0) {
        cout << "No records Found" << endl;
    }
    file.close();
}
int main() {
    int ch;
    studentDatabase db;

    // loop
    do {
        cout << endl;
        cout << "MENU" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Display All Records" << endl;
        cout << "0. Exit" << endl << endl;
        cout << "Enter Your Choice :";
        cin >> ch;
        switch (ch) {
            case 0:
                cout << "Thank You" << endl;
                break;
            case 1:
                db.addStudent();
                break;
            case 2:
                db.deleteStudent();
                break;
            case 3:
                db.searchStudent();
                break;
            case 4:
                cout << "Records in File are" << endl;
                db.displayAll();
                break;

            default:
                cout << "Enter a valid Choice" << endl;
                break;
        }
    } while (ch != 0);

    return 0;
}