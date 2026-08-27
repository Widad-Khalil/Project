#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Course {
    string code;
    string name;
    int credits;
    int value;
    string prereq;
};

struct Student{
    int id;
    string name;
    double gpa;
};

int seed = 0;
int num_courses = 0;
int num_records = 0;
int credit_cap = 0;

vector<Course> courses;
vector<Student> records;

unsigned int lcg_next(unsigned int &x){
    unsigned int next_val = (1103515245ULL * x + 12345ULL) % 2147483648ULL;
    x = next_val;
    return next_val;
}

void generateData(int student_id){
    seed = student_id % 10000;
    num_courses = 12 + (seed % 6);
    num_records = 40 + (seed % 20);
    credit_cap = 15 + (seed % 4);
     unsigned int current_seed = static_cast<unsigned int>(seed);
     string course_prefixes[] = {"ENG" , "CS" , "MATH" , "PHY"};
     string course_names[] = {"Data Struct" , "Discrete" , "Algorithms" , "Digital Logic" ,
                             "Circuits" , "Intro Programming" , "Linear Algebra" , "Signals" ,
                              "OS" , "DB Systems" , "Networks" , "Web Dev" , "AI Intro" , 
                            "Cybersecurity" , "Embeded Sys" , "Software Eng" ,"Microcontrollers" , "VLSI Design" };
    
    courses.clear();

    for (int i = 0; i < num_courses; ++i) {
        Course c;
        c.code = course_prefixes[i % 4] + to_string(101 + i * 10);
        c.name = course_names[i % 18];
        c.credits = 2 + (lcg_next(current_seed) % 3);
        c.value = 5 + (lcg_next(current_seed) % 6);
        
    if (i == 0 || (lcg_next(current_seed) % 3 == 0)) {
        c.prereq = "-";
    } else {
      int prereq_idx = lcg_next(current_seed) % i;
      c.prereq = courses[prereq_idx].code;  
    }
    courses.push_back(c);
    }                        

    string first_names[] = {"Lia" , "Sara" , "Yara" , "Ahmad" , "Samer" , "Adam" , "Lina" , "Tariq" , "Nour" , " Naya"};
    string last_names[] = { "Yousef" , "Saleh" , "Nasser" , "Qasim" , "Fares" , "Masri" , "kareem" , "Hamad" , "Sami" ,"Waseem"};
    records.clear();
    for (int i = 0; i < num_records; ++i) {
        Student s;
        s.id = 2025000 + (lcg_next(current_seed) % 900);
        s.name = first_names[lcg_next(current_seed) % 10] + " " +last_names[lcg_next(current_seed) % 10];
        s.gpa = 2.0 + (lcg_next(current_seed) % 201) / 100.0; // GPA between 2.00 and 4.00
        records.push_back(s);
    }
}
void printHeader() {
    cout << "\n----------------------------------------" << endl;
    cout << "CourseForge - System Data Initialization" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Seed           : " << seed << endl;
    cout << "Courses (n)    : " << num_courses << endl;
    cout << "Records (m)    : " << num_records << endl;
    cout << "Credit Cap (c) : " << credit_cap << endl;
    cout << "------------------------------------------" << endl;
}
void printGeneratedSample() {
    cout << "\n----- Generated Courses Sample -----" << endl;
    for (int i = 0; i < min(5 , (int)courses.size()); ++i) {
        cout << courses[i].code << " " << courses[i].name << " " << courses[i].credits << "cr val " 
              << courses[i].value << "pre:" << courses[i].prereq << endl;
    }
    cout << "\n----- Generated Student Records Sample -----" << endl;
    for (int i = 0; i < min(5 , (int)records.size()); ++i) {
        cout << records[i].id << " " << records[i].name << " GPA " << fixed << setprecision(2) << records[i].gpa << endl;
    }
}
void selectionSort(vector<Student> arr , long long &comparisions, long long &swaps) {
    comparisions = 0;
    swaps = 0;
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        int min_idx = i;
        for (int j = i+1; j < n; ++j) {
            comparisions++;
        if (arr[j].gpa < arr[min_idx].gpa) {
            min_idx = j;
        }
        }
        if (min_idx != i) {
            swap(arr[i] , arr[min_idx]);
            swaps++;
        }
    }
}

