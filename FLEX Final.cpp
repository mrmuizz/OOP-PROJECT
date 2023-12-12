#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

// Class representing a Course
class Course
{
public:
    string code;
    string name;
    string instructor;
    int credits;
    int capacity;
    string* students;
    unordered_map<string, int> marks;

    Course() {};

    // Constructor to initialize a course
    Course(const string& code, const string& name, const string& instructor, int credits, int capacity)
        : code(code), name(name), instructor(instructor), credits(credits), capacity(capacity) {
        students = new string[capacity];
    }

    // Destructor to free memory
    ~Course() {
        delete[] students;
    }

    // Save course information to file
    void saveToFile(ofstream& file) {
        file << code << " " << name << " " << instructor << " " << credits << " " << capacity << endl;
        for (int i = 0; i < studentsEnrolled; ++i) {
            file << students[i] << " ";
        }
        file << endl;
    }
    // Function to enroll a student in the course
    void enrollStudent(const string& student) {
        if (studentsEnrolled < capacity) {
            students[studentsEnrolled] = student;
            attendanceStatus[student] = false;  // Initialize attendance status to false
            cout << student << " has been enrolled in " << name << endl;
            ++studentsEnrolled;
        }
        else {
            cout << "Course " << name << " is full. Cannot enroll more students." << endl;
        }
    }
    // Function to remove a student from the course
    void removeStudent(const string& studentName) {
        // Remove the student from the list of enrolled students in the course
        bool found = false;
        for (int i = 0; i < studentsEnrolled; ++i) {
            // Find the index of the student to be removed
            if (students[i] == studentName) {
                found = true;
                // Shift the remaining elements to fill the gap
                for (int j = i; j < studentsEnrolled - 1; ++j) {
                    students[j] = students[j + 1];
                }
                // Update the number of enrolled students
                --studentsEnrolled;
                cout << "Student " << studentName << " removed from the course.\n";
                break;  // Exit the loop once the student is found and removed
            }
        }

        // If the student is not found in the course, print a message
        if (!found) {
            cout << "Student " << studentName << " is not enrolled in the course.\n";
        }
    }
    // Function to assign marks to a student
    void assignMarks(const string& studentName, int marks) {
        auto it = marksRecord.find(studentName);
        if (it != marksRecord.end()) {
            it->second = marks;
        }
        else {
            cerr << "Error: Student " << studentName << " not found in marks record.\n";
        }
    }
    // Function to display enrolled students in the course
    void displayEnrolledStudents() const {
        cout << "Enrolled students in " << name << ":" << endl;
        for (int i = 0; i < studentsEnrolled; ++i) {
            cout << "  " << students[i] << endl;
        }
    }
    // Function to mark attendance for a student
    void markAttendance(const string& studentName) {
        auto it = attendanceStatus.find(studentName);
        if (it != attendanceStatus.end()) {
            it->second = true; // Mark the student as present
        }
        else {
            cerr << "Error: Student " << studentName << " not found in attendance record.\n";
        }
    }
    // Function to display attendance for the course
    void saveToFile(ofstream& file) const 
    {
        file << code << " " << name << " " << instructor << " " << credits << " " << capacity << endl;
        for (int i = 0; i < studentsEnrolled; ++i) {
            file << students[i] << " ";
        }
        file << endl;
    }
    void displayAttendance(){}
private:
    int studentsEnrolled = 0;
    unordered_map<string, bool> attendanceStatus;
    unordered_map<string, int> marksRecord;
};

// Class representing a Student
class Student:public Course
{
public:
    string name;
    string rollNum;
    int age;
    string contact;
    string* courses;
    static const int MAX_COURSES = 5;
    int coursesEnrolled = 0;

    // Constructor to initialize a student
    Student(const string& name, const string& rollNum, int age, const string& contact)
        : name(name), rollNum(rollNum), age(age), contact(contact) {
        courses = new string[MAX_COURSES];
    }
    // Destructor to free memory
    ~Student() {
        delete[] courses;
    }
    // Function to enroll in a course
    void enrollInCourse(const string& course) {
        if (coursesEnrolled < MAX_COURSES) {
            courses[coursesEnrolled] = course;
            cout << name << " has been enrolled in " << course << endl;
            ++coursesEnrolled;
        }
        else {
            cout << "You cannot enroll in more than " << MAX_COURSES << " courses." << endl;
        }
    }
    // Function to display enrolled courses
    void displayEnrolledCourses() const {
        cout << name << "'s enrolled courses:" << endl;
        for (int i = 0; i < coursesEnrolled; ++i) {
            cout << "  " << courses[i] << endl;
        }
    }

    // Save student information to file
    void saveToFile(ofstream& file) {
        file << name << " " << rollNum << " " << age << " " << contact << endl;
        for (int i = 0; i < coursesEnrolled; ++i) {
            file << courses[i] << " ";
        }
        file << endl;
    }
    // Function to drop a course
    void dropCourse(const string& courseCode) {
        bool found = false;
        for (int i = 0; i < coursesEnrolled; ++i) {
            // Find the index of the course to be dropped
            if (courses[i] == courseCode) {
                found = true;
                // Shift the remaining elements to fill the gap
                for (int j = i; j < coursesEnrolled - 1; ++j) {
                    courses[j] = courses[j + 1];
                }
                // Update the number of enrolled courses
                --coursesEnrolled;
                cout << "Course " << courseCode << " dropped successfully.\n";
                break;  // Exit the loop once the course is found and dropped
            }
        }

        // If the course is not found in the enrolled courses, print a message
        if (!found) {
            cout << "Course " << courseCode << " is not enrolled.\n";
        }
    }
  
    void saveToFile(ofstream& file) const 
    {
        file << name << " " << rollNum << " " << age << " " << contact << endl;
        for (int i = 0; i < coursesEnrolled; ++i) {
            file << courses[i] << " ";
        }
        file << endl;
    }
    // Function to display the number of courses enrolled
    int getCoursesEnrolled() {

        return coursesEnrolled;
    }
private:
};

// Class representing the Learning Management System
class System
{
public:

    // Function to display the main menu
    void displayMainMenu() {
        cout << "Main Menu\n";
        cout << "1- Enroll a student\n";
        cout << "2- Course Registration\n";
        cout << "3- Attendance\n";
        cout << "4- Marks\n";
        cout << "5- Course Withdraw\n";
        cout << "6- Exit\n";
        cout << "Press 1 to 6 to select an option: ";
    }
    // Function to handle main menu options
    void handleMainMenuOption(int option) {
        switch (option) {
        case 1:
            handleEnrollStudent();
            break;
        case 2:
            handleCourseRegistration();
            break;
        case 3:
            handleAttendance();
            break;
        case 4:
            handleMarks();
            break;
        case 5:
            handleCourseWithdraw();
            break;
        case 6:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid option. Please enter a number between 1 and 6.\n";
        }
    }

    // Inside the System class

    // Function to handle student enrollment
    void handleEnrollStudent() {
        cout << "Enroll Student\n";
        cout << "1- Display already enrolled students\n";
        cout << "2- Add a student\n";
        cout << "3- Remove a student\n";
        cout << "4- Edit student detail\n";
        cout << "5- Back\n";
        cout << "Press 1 to 5 to select an option: ";

        int option;
        cin >> option;

        switch (option) {
        case 1:
            handleDisplayEnrolledStudents();
            break;
        case 2:
            handleAddStudent();
            break;
        case 3:
            handleRemoveStudent();
            break;
        case 4:
            handleEditStudentDetail();
            break;
        case 5:
            // Back to main menu
            break;
        default:
            cout << "Invalid option. Please enter a number between 1 and 5.\n";
        }
    }

    // Function to display enrolled students
    void handleDisplayEnrolledStudents() {
        string courseCode;
        cout << "Enter the code of the course to display enrolled students: ";
        cin >> courseCode;

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        // Display enrolled students
        course.displayEnrolledStudents();
    }

    // Function to remove a student
    void handleRemoveStudent() {
        string studentName;
        cout << "Enter the name of the student to be removed: ";
        cin >> studentName;

        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        // Remove the student from all enrolled courses
        for (int i = 0; i < student.getCoursesEnrolled(); ++i) {
            string courseCode = student.courses[i];
            Course course = loadCourseFromFile(courseCode);
            course.removeStudent(studentName);
            updateCourseFile(course);
        }


        // Save the updated student information to file
        updateStudentFile(student);

        cout << "Student " << studentName << " removed successfully.\n";
    }

    // Function to edit student details
    void handleEditStudentDetail() {
        string studentName;
        cout << "Enter the name of the student to edit details: ";
        cin >> studentName;

        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        // Display current details
        cout << "Current details for " << studentName << ":\n";
        cout << "Name: " << student.name << "\n";
        cout << "Roll Number: " << student.rollNum << "\n";
        cout << "Age: " << student.age << "\n";
        cout << "Contact: " << student.contact << "\n";

        // Get new details
        string newName, newRollNum, newContact;
        int newAge;

        cout << "Enter new name: ";
        cin >> newName;

        cout << "Enter new roll number: ";
        cin >> newRollNum;

        cout << "Enter new age: ";
        cin >> newAge;

        cout << "Enter new contact: ";
        cin >> newContact;

        // Update student details
        student.name = newName;
        student.rollNum = newRollNum;
        student.age = newAge;
        student.contact = newContact;

        // Save the updated student information to file
        updateStudentFile(student);

        cout << "Student details updated successfully.\n";
    }

    // Function to add a student
    void handleAddStudent() {
        string name, rollNum, contact;
        int age;

        cout << "Enter student name: ";
        cin >> name;

        cout << "Enter student roll number: ";
        cin >> rollNum;

        cout << "Enter student age: ";
        cin >> age;

        cout << "Enter student contact: ";
        cin >> contact;

        Student newStudent(name, rollNum, age, contact);
        newStudent.saveToFile(studentFile);  // Save newStudent data to file

        cout << "Student information successfully saved.\n";
    }
    // Function to remove a student from a course
    void removeStudentFromCourse(const string& studentName, const string& courseCode) {
        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        // Remove the student from the course
        course.removeStudent(studentName);
        student.dropCourse(courseCode);

        // Save updated student and course information to file
        updateStudentFile(student);
        updateCourseFile(course);

        cout << "Student " << studentName << " removed from course " << courseCode << " successfully.\n";
    }

    // Function to display enrolled courses for a student
    void displayEnrolledCoursesForStudent(const string& studentName) {
        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        // Display enrolled courses
        student.displayEnrolledCourses();
    }
    // Function to handle course registration
    void handleCourseRegistration() {
        cout << "Course Registration\n";
        cout << "1- Display available courses\n";
        cout << "2- Register Course\n";
        cout << "3- Back\n";
        cout << "Press 1 to 3 to select an option: ";

        int option;
        cin >> option;

        switch (option) {
        case 1:
            displayAvailableCourses();
            break;
        case 2:
            handleRegisterCourse();
            break;
        case 3:
            // Back to main menu
            break;
        default:
            cout << "Invalid option. Please enter a number between 1 and 3.\n";
        }
    }
    // Function to display available courses
    void displayAvailableCourses() {
        // Load available courses from file or other data source
        ifstream courseFile("courses.txt");
        if (!courseFile.is_open()) {
            cerr << "Error: Unable to open courses file.\n";
            // Handle error (e.g., create a new file or exit)
        }

        string line;
        int courseNumber = 1;

        while (getline(courseFile, line)) {
            istringstream iss(line);

            string code, name, instructor;
            int credits, capacity;

            iss >> code >> name >> instructor >> credits >> capacity;

            // Display course information
            cout << courseNumber << "- Code: " << code << ", Name: " << name << ", Instructor: " << instructor << ", Credits: " << credits << ", Capacity: " << capacity << "\n";
            courseNumber++;
        }

        courseFile.close();
    }
    // Function to handle course registration
    void handleRegisterCourse() {
        string studentName;
        cout << "Enter student name: ";
        cin >> studentName;

        string courseCode;
        cout << "Enter the code of the course you want to register: ";
        cin >> courseCode;

        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        // Enroll the student in the course
        student.enrollInCourse(courseCode);
        course.enrollStudent(studentName);

        // Save updated student and course information to file
        updateStudentFile(student);
        updateCourseFile(course);

        cout << "Registration successful.\n";
    }
    // Function to load student information from file
    Student loadStudentFromFile(const string& studentName) {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cerr << "Error: Unable to open students file.\n";
            // Handle error (e.g., create a new file)
            return Student("", "", 0, "");
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string nameFromFile;
            iss >> nameFromFile;
            if (nameFromFile == studentName) {
                // Found the student
                string rollNum, contact;
                int age;
                iss >> rollNum >> age >> contact;
                Student student(nameFromFile, rollNum, age, contact);
                // Load enrolled courses
                while (iss >> rollNum) {
                    student.enrollInCourse(rollNum);
                }
                return student;
            }
        }

        // Student not found, close the file and return an empty student
        file.close();
        cout << "Student not found: " << studentName << endl;
        return Student("", "", 0, "");
    }
    // Function to load course information from file
    Course loadCourseFromFile(const string& courseCode) {
        ifstream file("courses.txt");
        if (!file.is_open()) {
            cerr << "Error: Unable to open courses file.\n";
            // Handle error (e.g., create a new file)
            return Course("", "", "", 0, 0);
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string codeFromFile;
            iss >> codeFromFile;
            if (codeFromFile == courseCode) {
                // Found the course
                string name, instructor;
                int credits, capacity;
                iss >> name >> instructor >> credits >> capacity;
                Course course(codeFromFile, name, instructor, credits, capacity);
                // Load enrolled students
                while (iss >> name) {
                    course.enrollStudent(name);
                }
                return course;
            }
        }


        // Course not found, close the file and return an empty course
        file.close();
        cout << "Course not found: " << courseCode << endl;
        return Course("", "", "", 0, 0);
    }
    // Function to update student information in file
    void updateStudentFile(const Student& student) {
        ofstream file("students.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Error: Unable to open students file for update.\n";
            // Handle error
            return;
        }

        student.saveToFile(file);
        file.close();
    }
    // Function to update course information in file
    void updateCourseFile(const Course& course) {
        ofstream file("courses.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Error: Unable to open courses file for update.\n";
            // Handle error
            return;
        }

        course.saveToFile(file);
        file.close();
    }

    // Inside the System class

    // Function to display attendance
    void handleDisplayAttendance() {
        string courseCode;
        cout << "Enter the code of the course to display attendance: ";
        cin >> courseCode;

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        // Display attendance
        course.displayAttendance();
    }

    // Function to mark attendance
    void handleMarkAttendance()
    {
        string courseCode;
        cout << "Enter the code of the course for attendance: ";
        cin >> courseCode;

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        string studentName;
        cout << "Enter the name of the student for attendance: ";
        cin >> studentName;

        // Mark attendance for the student in the course
        course.markAttendance(studentName);

        // Save updated course information to file
        updateCourseFile(course);
    }

    // Function to handle marks
    void handleMarks() {
        cout << "Marks\n";
        cout << "1- Display Marks (Subject wise)\n";
        cout << "2- Assign Marks\n";
        cout << "3- Back\n";
        cout << "Press 1 to 3 to select an option: ";

        int option;
        cin >> option;

        switch (option) {
        case 1:
            // Display Marks (Subject wise) (implementation needed)
            break;
        case 2:
            handleAssignMarks();
            break;
        case 3:
            // Back to main menu
            break;
        default:
            cout << "Invalid option. Please enter a number between 1 and 3.\n";
        }
    }

    // Function to handle marks assignment
    void handleAssignMarks() {
        string courseCode;
        cout << "Enter the code of the course for marks assignment: ";
        cin >> courseCode;

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        string studentName;
        cout << "Enter the name of the student for marks assignment: ";
        cin >> studentName;

        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        int marks;
        cout << "Enter marks for " << studentName << " in " << courseCode << ": ";
        cin >> marks;

        // Assign marks
        // Note: In a complete system, you would handle specific assignments, exams, etc.
        cout << "Assigning " << marks << " marks to " << studentName << " in " << courseCode << endl;

        // Save updated course information to file
        updateCourseFile(course);
    }

    // Function to handle course withdrawal

    void handleCourseWithdraw() {
        cout << "Course Withdrawal\n";
        cout << "1- Display Enrolled Courses\n";
        cout << "2- Drop a Course\n";
        cout << "3- Back\n";
        cout << "Press 1 to 3 to select an option: ";

        int option;
        cin >> option;

        switch (option) {
        case 1:
            handleDisplayEnrolledCourses();
            break;
        case 2:
            handleDropCourse();
            break;
        case 3:
            // Back to main menu
            break;
        default:
            cout << "Invalid option. Please enter a number between 1 and 3.\n";
        }
    }

    // Function to display enrolled courses
    void handleDisplayEnrolledCourses() {
        string studentName;
        cout << "Enter the name of the student to display enrolled courses: ";
        cin >> studentName;

        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        // Display enrolled courses
        student.displayEnrolledCourses();
    }

    // Function to drop a course
    void handleDropCourse() {
        string studentName;
        cout << "Enter the name of the student to drop a course: ";
        cin >> studentName;

        // Load student information from file
        Student student = loadStudentFromFile(studentName);

        string courseCode;
        cout << "Enter the code of the course to be dropped: ";
        cin >> courseCode;

        // Load course information from file
        Course course = loadCourseFromFile(courseCode);

        // Drop the course
        student.dropCourse(courseCode);
        course.removeStudent(studentName);

        // Save updated student and course information to file
        updateStudentFile(student);
        updateCourseFile(course);

        cout << "Course dropped successfully.\n";
    }

    // Function to handle attendance
    void handleAttendance() {
        cout << "Attendance\n";
        cout << "1- Display Attendance\n";
        cout << "2- Mark Attendance\n";
        cout << "3- Back\n";
        cout << "Press 1 to 3 to select an option: ";

        int option;
        cin >> option;

        switch (option) {
        case 1:
            handleDisplayAttendance();
            break;
        case 2:
            handleMarkAttendance();
            break;
        case 3:
            // Back to main menu
            break;
        default:
            cout << "Invalid option. Please enter a number between 1 and 3.\n";
        }
    }


private:
    ofstream studentFile{ "students.txt", ios::app };
    ofstream courseFile{ "courses.txt", ios::app };
};

int main() {

    // Create an instance of the Learning Management System
    System learningManagementSystem;
    int option;

    // Main loop to display the menu and handle options
    do {
        learningManagementSystem.displayMainMenu();
        cin >> option;
        learningManagementSystem.handleMainMenuOption(option);
    } while (option != 6);

    return 0;
}
