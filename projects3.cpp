#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib> // for exit(), system()

using namespace std;

class student {
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;

    void calculate() {
        per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
        if (per >= 60) grade = 'A';
        else if (per >= 50 && per < 60) grade = 'B';
        else if (per >= 33 && per < 50) grade = 'C';
        else grade = 'F';
    }

public:
    void getdata() {
        cout << "\nEnter The roll number of student: ";
        cin >> rollno;
        cin.ignore(); // to ignore newline character left in buffer
        cout << "\nEnter The Name of student: ";
        cin.getline(name, 50);
    
        do {
            cout << "\nEnter The marks in physics out of 100: ";
            cin >> p_marks;
            if (p_marks < 0 || p_marks > 100) {
                cout << "Invalid input! Marks should be between 0 and 100.\n";
            }
        } while (p_marks < 0 || p_marks > 100);
    
        do {
            cout << "\nEnter The marks in chemistry out of 100: ";
            cin >> c_marks;
            if (c_marks < 0 || c_marks > 100) {
                cout << "Invalid input! Marks should be between 0 and 100.\n";
            }
        } while (c_marks < 0 || c_marks > 100);
    
        do {
            cout << "\nEnter The marks in maths out of 100: ";
            cin >> m_marks;
            if (m_marks < 0 || m_marks > 100) {
                cout << "Invalid input! Marks should be between 0 and 100.\n";
            }
        } while (m_marks < 0 || m_marks > 100);
    
        do {
            cout << "\nEnter The marks in english out of 100: ";
            cin >> e_marks;
            if (e_marks < 0 || e_marks > 100) {
                cout << "Invalid input! Marks should be between 0 and 100.\n";
            }
        } while (e_marks < 0 || e_marks > 100);
    
        do {
            cout << "\nEnter The marks in computer science out of 100: ";
            cin >> cs_marks;
            if (cs_marks < 0 || cs_marks > 100) {
                cout << "Invalid input! Marks should be between 0 and 100.\n";
            }
        } while (cs_marks < 0 || cs_marks > 100);
    
        calculate();
    }


    void showdata() const {
        cout << "\nRoll number of student: " << rollno;
        cout << "\nName of student: " << name;
        cout << "\nMarks in Physics: " << p_marks;
        cout << "\nMarks in Chemistry: " << c_marks;
        cout << "\nMarks in Maths: " << m_marks;
        cout << "\nMarks in English: " << e_marks;
        cout << "\nMarks in Computer Science: " << cs_marks;
        cout << "\nPercentage of student is: " << setprecision(2) << per;
        cout << "\nGrade of student is: " << grade;
    }

    void show_tabular() const {
        cout << rollno << setw(12) << name << setw(10) << p_marks << setw(3) << c_marks << setw(3)
             << m_marks << setw(3) << e_marks << setw(3) << cs_marks << setw(6) << setprecision(3) << per
             << " " << grade << endl;
    }

    int retrollno() const { return rollno; }
};

// Global declaration for stream object, object
fstream fp;
student st;

// Function to write in file
void write_student()
{
    ofstream file("student.dat", ios::binary | ios::app);
    if (!file) {
        cerr << "Error: Could not open file for writing\n";
        return;
    }

    st.getdata();  // Collect data from the user
    file.write(reinterpret_cast<char*>(&st), sizeof(student));  // Write to file in binary format
    file.close();
    
    cout << "\n\nStudent record has been created.\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();  // Wait for Enter key
}


// Function to read all records from file
void display_all()
{
    ifstream file("student.dat", ios::binary);
    if (!file) {
        cerr << "Error: Could not open file for reading\n";
        return;
    }
    
    cout << "\n\nDISPLAYING ALL STUDENTS RECORD!!!\n";
    while (file.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        st.showdata();  // Display individual student data
        cout << "\n\n====================================\n";
    }
    file.close();
    
    cout << "\nPress Enter to continue...";
    cin.ignore();  // Ignore any leftover newline character
    cin.get();    // Wait for Enter key
}


// Function to read specific record from file
// Function to read specific record from file
void display_sp(int n) {
    int flag = 0;
    fp.open("student.dat", ios::in | ios::binary);
    if (!fp) {
        cout << "Error: Could not open file\n";
        return;
    }
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        if (st.retrollno() == n) {
            system("clear || cls");  // clear the screen
            st.showdata();  // display student data
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\n\nRecord not found\n";
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();  // Clear the input buffer (if there are any newline characters left)
    cin.get();  // Wait for Enter key
}


// Function to modify record in the file
void modify_student() {
    int no, found = 0;
    system("clear || cls");
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The roll number of student: ";
    cin >> no;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student)) && found == 0) {
        if (st.retrollno() == no) {
            st.showdata();
            cout << "\nPlease Enter The New Details of student:\n";
            st.getdata();
            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&st), sizeof(student));
            cout << "\n\n\tRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) cout << "\n\nRecord Not Found ";
    cin.get();
}

// Function to delete record from the file
void delete_student() {
    int no;
    system("clear || cls");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The roll number of student You Want To Delete: ";
    cin >> no;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        if (st.retrollno() != no) {
            fp2.write(reinterpret_cast<char*>(&st), sizeof(student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.get();
}

// Function to display all students' grade report
void class_result()
{
    ifstream file("student.dat", ios::binary);
    if (!file) {
        cerr << "Error: Could not open file\n";
        return;
    }

    cout << "\n\n\tALL STUDENTS RESULT \n\n";
    cout << "====================================================\n";
    cout << "Roll No. Name       P C M E CS %age Grade\n";
    cout << "====================================================\n";
    
    while (file.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        st.show_tabular();  // Display student data in tabular form
    }
    file.close();
    
    cout << "\nPress Enter to continue...";
    cin.ignore();  // Clear any leftover newline character
    cin.get();    // Wait for Enter key
}


// Function to display result menu
void result() {
    int ans, rno;
    system("clear || cls");
    cout << "\n\n\nRESULT MENU";
    cout << "\n\n\n1. Class Result\n\n2. Student Report Card\n\n3. Back to Main Menu";
    cout << "\n\n\nEnter Choice (1/2)? ";
    cin >> ans;
    switch (ans) {
        case 1: 
            class_result(); 
            break;
        case 2:
            char moreResults;
            do {
                system("clear || cls");
                cout << "\n\nEnter Roll Number Of Student: ";
                cin >> rno;
                display_sp(rno);
                cout << "\n\nDo you want to see more results (y/n)? ";
                cin >> moreResults;
                cin.ignore();  // Ignore leftover newline character after the input
            } while (moreResults == 'y' || moreResults == 'Y');
            break;
        case 3: 
            break;
        default: 
            cout << "\a";  // Beep for invalid choice
    }
}


// Introduction function
void intro() {
    system("clear || cls");
    cout << "STUDENT REPORT CARD PROJECT\n\nMADE BY : RAHUL SHARMA\nSCHOOL : CAMBRIDGE SCHOOL\n";
    cin.get();
}

// Entry / Edit Menu function
void entry_menu()
{
    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1. CREATE STUDENT RECORD";
    cout << "\n\n\t2. DISPLAY ALL STUDENTS RECORDS";
    cout << "\n\n\t3. SEARCH STUDENT RECORD";
    cout << "\n\n\t4. MODIFY STUDENT RECORD";
    cout << "\n\n\t5. DELETE STUDENT RECORD";
    cout << "\n\n\t6. BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6): ";
    
    char choice;
    cin >> choice;
    cin.ignore();  // Clear newline from the input buffer

    switch(choice)
    {
        case '1': 
            write_student();
            break;
        case '2': 
            display_all();
            break;
        case '3':
            int num;
            cout << "\n\n\tPlease Enter The roll number: ";
            cin >> num;
            cin.ignore();
            display_sp(num);
            break;
        case '4': 
            modify_student();
            break;
        case '5': 
            delete_student();
            break;
        case '6': 
            return; // Go back to the main menu
        default:
            cout << "\a"; // Beep sound
            entry_menu();
    }
}


// Main function of the program
int main() {
    char ch;
    intro();
    do {
        system("clear || cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. RESULT MENU";
        cout << "\n\n\t2. ENTRY/EDIT MENU";
        cout << "\n\n\t3. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3): ";
        cin >> ch;
        switch (ch) {
            case '1': system("clear || cls"); result(); break;
            case '2': entry_menu(); break;
            case '3': exit(0);
            default: cout << "\a";
        }
    } while (ch != '3');
    return 0;
}
