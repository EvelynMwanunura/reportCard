#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath> // For std::round

using namespace std;

//***************************************************************
// 1. STUDENT CLASS (DATA STRUCTURE: STORES INDIVIDUAL RECORD)
//***************************************************************
class Student {
private:
    int studentNumber;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    double per;
    char grade;

    void calculate() {
        // Calculate total marks and percentage
        int total = p_marks + c_marks + m_marks + e_marks + cs_marks;
        per = total / 5.0;

        // Assign grade based on percentage
        if (per >= 75) grade = 'A';
        else if (per >= 60) grade = 'B';
        else if (per >= 40) grade = 'C';
        else grade = 'F';
    }

public:
    // Function to get data from user
    void getdata() {
        cout << "\n\tEnter The Student Number of student: ";
        cin >> studentNumber;
        cin.ignore();
        cout << "\tEnter The Name of student: ";
        cin.getline(name, 50);
        cout << "\tEnter Marks in Statistics (out of 100): "; cin >> p_marks;
        cout << "\tEnter Marks in Data Structures and Algorythims (out of 100): "; cin >> c_marks;
        cout << "\tEnter Marks in Database Implementation (out of 100): "; cin >> m_marks;
        cout << "\tEnter Marks in Software Engineering (out of 100): "; cin >> e_marks;
        cout << "\tEnter Marks in Computer Science (out of 100): "; cin >> cs_marks;
        calculate();
    }

    // Function to show individual student data on screen
    void showdata() const {
        cout << "\n\tStudent number of student: " << studentNumber;
        cout << "\n\tName of student: " << name;
        cout << "\n\tMarks in Statistics: " << p_marks;
        cout << "\n\tMarks in Data Structures and Algorythims: " << c_marks;
        cout << "\n\tMarks in Database Implementation: " << m_marks;
        cout << "\n\tMarks in Software Engineering: " << e_marks;
        cout << "\n\tMarks in Computer Science: " << cs_marks;
        cout << setprecision(2) << fixed;
        cout << "\n\tPercentage of student is: " << per;
        cout << "\n\tGrade of student is: " << grade;
    }

    // Function to show data in tabular format for all students
    void show_tabular() const {
        cout << setprecision(2) << fixed;
        cout << studentNumber << setw(10) << name << setw(5) << p_marks << setw(5) << c_marks << setw(5) << m_marks
             << setw(5) << e_marks << setw(5) << cs_marks << setw(10) << per << setw(6) << grade << endl;
    }

    // Accessor function for student number (crucial for searching/sorting)
    int retStudentNo() const {
        return studentNumber;
    }
};

//***************************************************************
// 2. DATA STRUCTURES & ALGORITHMS IMPLEMENTATION
//***************************************************************

// The core data structure is a dynamic array (std::vector) of Student objects.


// --- Sorting Algorithm (e.g., Bubble Sort for simplicity, or Merge/Quick Sort for complexity) ---
bool compareStudents(const Student& a, const Student& b) {
    return a.retStudentNo() < b.retStudentNo();
}

void sort_records(vector<Student>& students) {
    // ALGORITHM: Using std::sort (which implements a variant of Quick Sort/Intro Sort)
    sort(students.begin(), students.end(), compareStudents);
}

// --- Searching Algorithm: Binary Search ---
// Binary Search is efficient but requires the data to be sorted first.
int binary_search_student(const vector<Student>& students, int studentNumber) {

    int low = 0;
    int high = students.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (students[mid].retStudentNo() == studentNumber) {
            return mid; // Found at index mid
        }
        if (students[mid].retStudentNo() < studentNumber) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Not found
}


//***************************************************************
// 3. FILE I/O FUNCTIONS (FOR PERSISTENCE)
//***************************************************************
const string FILENAME = "student.dat";

void load_records(vector<Student>& students) {
    ifstream inFile(FILENAME, ios::binary);
    if (!inFile) return; // File doesn't exist or cannot be opened

    Student st;
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        students.push_back(st); // Store records from file into the Vector (Dynamic Array)
    }
    inFile.close();
}

void save_records(const vector<Student>& students) {
    ofstream outFile(FILENAME, ios::binary | ios::trunc); // Overwrite file
    for (const auto& st : students) {
        outFile.write(reinterpret_cast<const char*>(&st), sizeof(Student));
    }
    outFile.close();
}


//***************************************************************
// 4. MAIN MENU & CORE FUNCTIONS (CRUD OPERATIONS)
//***************************************************************
vector<Student> student_records;

void write_student() {
    Student st;
    st.getdata();
    student_records.push_back(st);
    save_records(student_records);
    cout << "\n\tStudent record Has Been Created and Saved!";
    cin.ignore(); cin.get();
}

void display_all() {
    if (student_records.empty()) {
        cout << "\n\tNo records to display. Press any key...";
        cin.ignore(); cin.get();
        return;
    }
    cout << "\n\n\t\t\tDISPLAY ALL RECORDS\n\n";
    cout << "================================================================" << endl;
    cout << "R.No" << setw(10) << "Name" << setw(5) << "P" << setw(5) << "C" << setw(5) << "M"
         << setw(5) << "E" << setw(5) << "CS" << setw(10) << "Per(%)" << setw(6) << "Grade" << endl;
    cout << "================================================================" << endl;

    // Sorting the records by Student Number before display
    sort_records(student_records);
    
    for (const auto& st : student_records) {
        st.show_tabular();
    }
    cin.ignore(); cin.get();
}

void display_sp(int n) {
    // Sort the list before performing Binary Search
    sort_records(student_records);

    // ALGORITHM: Search for the student using Binary Search
    int index = binary_search_student(student_records, n);
    
    if (index != -1) {
        cout << "\n\tRecord Found:";
        student_records[index].showdata();
    } else {
        cout << "\n\tRecord not found for Student Number " << n;
    }
    cin.ignore(); cin.get();
}

void modify_student(int n) {
    // Sort the list before performing Binary Search
    sort_records(student_records);

    // ALGORITHM: Search for the student using Binary Search
    int index = binary_search_student(student_records, n);

    if (index != -1) {
        cout << "\n\tRecord Found. Enter New Details:";
        student_records[index].getdata();
        save_records(student_records);
        cout << "\n\n\tRecord Updated!";
    } else {
        cout << "\n\n\tRecord Not Found for Student Number " << n;
    }
    cin.ignore(); cin.get();
}

void delete_student(int n) {
    // Sort the list before performing Binary Search
    sort_records(student_records);

    // ALGORITHM: Search for the student using Binary Search
    int index = binary_search_student(student_records, n);

    if (index != -1) {
        // DATA STRUCTURE OPERATION: Delete element from the Vector (Array)
        student_records.erase(student_records.begin() + index);
        save_records(student_records);
        cout << "\n\n\tRecord Deleted ..";
    } else {
        cout << "\n\n\tRecord Not Found for Student Number " << n;
    }
    cin.ignore(); cin.get();
}

void entry_menu() {
    char ch;
    int num;
    do {
        system("cls"); // Clears the screen (Windows/CMD only)
        cout << "\n\n\n\tENTRY/EDIT MENU";
        cout << "\n\n\t1. CREATE STUDENT RECORD";
        cout << "\n\n\t2. DISPLAY ALL STUDENTS REPORT";
        cout << "\n\n\t3. SEARCH STUDENT RECORD (Student No)";
        cout << "\n\n\t4. MODIFY STUDENT RECORD";
        cout << "\n\n\t5. DELETE STUDENT RECORD";
        cout << "\n\n\t6. BACK TO MAIN MENU";
        cout << "\n\n\tPlease Enter Your Option (1-6): ";
        cin >> ch;
        system("cls");
        switch (ch) {
            case '1':
                write_student();
                break;
            case '2':
                display_all();
                break;
            case '3':
                cout << "\n\n\tPlease Enter The Student Number: "; cin >> num;
                display_sp(num);
                break;
            case '4':
                cout << "\n\n\tPlease Enter The Student Number: "; cin >> num;
                modify_student(num);
                break;
            case '5':
                cout << "\n\n\tPlease Enter The Student Number: "; cin >> num;
                delete_student(num);
                break;
            case '6':
                break;
            default:
                cout << "\a";
        }
    } while (ch != '6');
}

//***************************************************************
// 5. MAIN FUNCTION
//***************************************************************
int main() {
    // 1. Load data from file into the vector (dynamic array) on startup
    load_records(student_records);
    
    char ch;
    // Set fixed and precision for output
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);

    do {
        system("cls");
        cout << "\n\n\n\tSTUDENT REPORT CARD SYSTEM (C++)";
        cout << "\n\n\t==============================";
        cout << "\n\n\t1. ENTRY/EDIT MENU";
        cout << "\n\n\t2. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-2) ";
        cin >> ch;

        switch (ch) {
            case '1':
                entry_menu();
                break;
            case '2':
                break; // Exit loop
            default:
                cout << "\a";
        }
    } while (ch != '2');

    return 0;
}