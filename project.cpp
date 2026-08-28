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

//module 1:selection sort & insertion sort
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
void insertionSortTrace(vector<int> arr) {
    cout << "\n----- Insertion Sort Trace Mode -----" << endl;
    cout << "in: ";
    for (int val : arr) cout << val << " ";
    cout << endl;

    long long comparisions = 0;
    long long shifts = 0;
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisions++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        
        for (int k = 0; k < n; ++k) {
            cout << arr[k] << (k == i ? " | " : " ");
        }
        cout << endl;
    }
    cout << " key comparisions : " << comparisions << " shifts : " << shifts <<endl;
}
void insertionSort(vector<Student> &arr, long long &comparisons, long long &shifts) {
    comparisons = 0;
    shifts = 0;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j].gpa > key.gpa) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else  {
                break;
            }
        }
        arr[j + 1] = key;
    }
}
void runModule1() {
    cout << "\n----- Module 1: Selection Sort & Insertion Sort -----" << endl;
    //Trace Mode for one 10-element array
    vector<int> trace_arr = {89 ,45 ,68 ,90 ,29 ,75 ,12 ,56 ,17 ,34};
    insertionSortTrace(trace_arr);
    //Sorting Student records
    long long sel_cmp = 0, sel_swaps = 0;
    long long  ins_cmp = 0, ins_shifts = 0;

    vector<Student> sel_records = records;
    vector<Student> ins_records = records;

    selectionSort(sel_records, sel_cmp, sel_swaps);
    insertionSort(ins_records, ins_cmp, ins_shifts);

    records = ins_records; //save it to use it in Binary Search
    cout << "\n------ Sorting Result -----" << endl;
    cout << "Selection Sort -> Comparisons: " << sel_cmp << " | Swaps: " << sel_swaps << endl;
    cout << "Insertion Sort -> Comparisons: " << ins_cmp << " | Shifts: " << ins_shifts << endl;

    bool match = true;
    for (size_t i = 0; i < sel_records.size(); ++i) {
        if (abs(sel_records[i].gpa - ins_records[i].gpa) > 1e-6) {
            match = false;
            break;
        }
    }
    cout << "Verification: Both sorted lists match? : " << (match ? "Yes" : "NO") << endl;
}

//module 2: Topological Sort
void runModule2() {
    cout << "\n----- Module 2: Topological Sort -----" << endl;
    int n = courses.size();
    vector<int> in_degree(n, 0);
    for (int i = 0; i < n; ++i) {
        if (courses[i].prereq != "-") {
            for (int j = 0; j < n; ++j) {
                if (courses[j].code == courses[i].prereq) {
                    in_degree[i]++;
                    break;
                }
            }
        }
    }
    vector<int> order;
    vector<bool> removed(n, false);
    for (int step = 0; step < n; ++step) {
        int zero_source = -1;
        for (int i = 0; i < n; ++i) {
            if (!removed[i] && in_degree[i] == 0) {
                zero_source = i;
                break;
            }
        }
        if (zero_source == -1) {
            cout << "Cycle Detected: No legal course order possible! " << endl;
            return;
        }
        removed[zero_source] = true;
        order.push_back(zero_source);

        for (int i = 0; i < n; ++i) {
            if (!removed[i] && courses[i].prereq == courses[zero_source].code) {
                in_degree[i]--;
            }
        }
    }
    if (order.size() == static_cast<size_t>(n)) {
        cout << "Valid Prerequisite Ordering Found: " << endl;
        for (size_t i = 0; i < order.size(); ++i) {
            cout << courses[order[i]].code << ( i + 1 == order.size() ? "" : " -> ");
        }
        cout << endl;
    } else {
        cout << "Cycle Detected: Unable to schedule all courses" << endl;
    }
}

//module 3: Best Course Load (Exhaustive Search)
void runModule3() {
    cout << "\n----- Module 3: Best Course Load (Exhaustive Search) -----" << endl;
    int k = min(10, (int)courses.size());
    int total_subsets = 1 << k; //=2^k
    int best_value = -1;
    int best_credits = 0;
    int best_mask = 0; // best mask(the winning combination)
    int legal_subsets = 0;
     
    for(int mask = 0; mask < total_subsets; ++mask) {
        int current_credits = 0;
        int current_value = 0;
        for (int j = 0; j < k; ++j) {
            if (mask & (1 << j)) {
                current_credits += courses[j].credits;
                current_value += courses[j].value;
            }
        }
        if (current_credits <= credit_cap) {
            legal_subsets++;
            if (current_value > best_value) {
                best_value = current_value;
                best_credits = current_credits;
                best_mask = mask ;
            }
        }
    }
    cout << "Evaluated Courses (k) : " << k << endl;
    cout<< "Credit Cap (C)         : " << credit_cap << endl;
    cout << "Total Subsets Checked : " << total_subsets << endl;
    cout << "Legal Subsets         : " << legal_subsets << endl;
    cout << "/n----- Winning Course Selection -----" << endl;
    cout << "Best Subset Value     : " << best_value << endl;
    cout << "Total Credits Used    : " << best_credits << endl;
    cout << "Selected Courses      : " ;
    for (int j = 0; j < k; ++j) {
        if (best_mask & (1 << j)) {
            cout << courses[j].code << " ";
        }
    }
    cout << endl;
}
