#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Problem {
    string code;
    string notes;
    int tag;
    int miscount;
};

void push_data(vector<Problem> &problems);
void display_data(const vector<Problem> &problems);
void delete_data(vector<Problem> &problems);
void edit_data(vector<Problem> &problems);
void search_data(const vector<Problem> &problems);
void save_data(const vector<Problem> &problems, const string &file1);
void load_data(vector<Problem> &problems, const string &file1);

int main() {
    vector<Problem> problem_list;
    int choice;
    const string file1 = "problems.txt";
    load_data(problem_list, file1);

    do {
        cout << "\n==== Problem Tracker ====\n";
        cout << "1. Add Problem\n";
        cout << "2. Show Problems\n";
        cout << "3. Delete Problem\n";
        cout << "4. Edit Problem\n";
        cout << "5. Search Problems\n";
        cout << "6. Exit\n";
        cout << "Enter choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                push_data(problem_list);
                break;
            case 2:
                display_data(problem_list);
                break;
            case 3:
                delete_data(problem_list);
                break;
            case 4:
                edit_data(problem_list);
                break;
            case 5:
                search_data(problem_list);
                break;
            case 6:
                save_data(problem_list, file1);
                break;
            default:
                cout << "Invalid input!!\n";
        }
    } while (choice != 6);

    return 0;
}

void push_data(vector<Problem> &problems) {
    Problem temp_p;
    string line;
    int c;

    cin.ignore();

    cout << "Enter code (type 'END' on a new line when finished):\n";
    while (getline(cin, line)) {
        if (line == "END") break;
        temp_p.code += line + "\n";
    }

    cout << "Any notes? (1 for YES, 0 for NO): ";
    cin >> c;
    cin.ignore();
    if (c == 1) {
        cout << "Enter notes (type 'END' on a new line when finished):\n";
        while (getline(cin, line)) {
            if (line == "END") break;
            temp_p.notes += line + "\n";
        }
    }

    cout << "Enter tag/problem number: ";
    cin >> temp_p.tag;

    cout << "Enter mistake count: ";
    cin >> temp_p.miscount;
    cin.ignore();

    problems.push_back(temp_p);
}

void display_data(const vector<Problem> &problems) {
    if (problems.empty()) {
        cout << "\nNo problems added yet.\n";
        return;
    }
    for (const Problem &p : problems) {
        cout << "\nTag = " << p.tag << "\n"
             << "Code:\n" << p.code
             << "Notes:\n" << p.notes
             << "Mistakes: " << p.miscount << "\n";
    }
}

void delete_data(vector<Problem> &problems) {
    int target;
    cout << "Enter tag/problem number to delete: ";
    cin >> target;

    auto it = find_if(problems.begin(), problems.end(),
                      [target](const Problem &p) { return p.tag == target; });
    if (it != problems.end()) {
        problems.erase(it);
        cout << "\nProblem deleted.\n";
    } else {
        cout << "\nProblem not found.\n";
    }
}

void edit_data(vector<Problem> &problems) {
    int target;
    cout << "Enter tag/problem number to edit: ";
    cin >> target;
    cin.ignore();

    auto it = find_if(problems.begin(), problems.end(),
                      [target](const Problem &p) { return p.tag == target; });
    if (it == problems.end()) {
        cout << "\nProblem not found.\n";
        return;
    }

    string line;

    cout << "\nCurrent code:\n" << it->code;
    cout << "Enter new code (type 'END' on a new line to finish, or type 'END' right away to keep it):\n";
    string new_code;
    bool changed = false;
    while (getline(cin, line)) {
        if (line == "END") break;
        new_code += line + "\n";
        changed = true;
    }
    if (changed) it->code = new_code;

    cout << "\nCurrent notes:\n" << it->notes;
    cout << "Change notes? (1 for YES, 0 for NO): ";
    int c;
    cin >> c;
    cin.ignore();
    if (c == 1) {
        cout << "Enter new notes (type 'END' on a new line when finished):\n";
        string new_notes;
        while (getline(cin, line)) {
            if (line == "END") break;
            new_notes += line + "\n";
        }
        it->notes = new_notes;
    }

    cout << "\nCurrent mistake count: " << it->miscount << "\n";
    cout << "Enter new mistake count (or the same number to keep it): ";
    cin >> it->miscount;
    cin.ignore();

    cout << "\nProblem updated.\n";
}

void search_data(const vector<Problem> &problems) {
    int target;
    cout << "Enter tag/problem number to search: ";
    cin >> target;

    auto it = find_if(problems.begin(), problems.end(),
                      [target](const Problem &p) { return p.tag == target; });
    if (it != problems.end()) {
        cout << "\nFound\n"
             << "Tag = " << it->tag << "\n"
             << "Code:\n" << it->code
             << "Notes:\n" << it->notes
             << "Mistakes: " << it->miscount << "\n";
    } else {
        cout << "\nEntered number not found!!!\n";
    }
}

void save_data(const vector<Problem> &problems, const string &file1){
    ofstream out(file1);
    if(!out){
        cout << "\nCould not open " << file1 << " for saving.\n";
        return;
    }
    out << problems.size() << "\n";
    for(const Problem &p : problems){
        out << p.tag << " " << p.miscount << "\n";
        out << p.code.size() << "\n" << p.code;
        out << p.notes.size() << "\n" << p.notes;
    }
    cout << "\nSaved " << problems.size() << " problem(s) to " << file1 << ".\n";
}

void load_data(vector<Problem> &problems, const string &file1){
    ifstream in(file1);
    if(!in) return;   // no save file yet, so start empty

    size_t count;
    if(!(in >> count)) return;
    in.ignore();      // skip the newline after the count

    for(size_t i = 0; i < count; i++){
        Problem p;
        in >> p.tag >> p.miscount;
        in.ignore();

        size_t len;
        in >> len;
        in.ignore();
        p.code.resize(len);
        in.read(&p.code[0], len);

        in >> len;
        in.ignore();
        p.notes.resize(len);
        in.read(&p.notes[0], len);

        problems.push_back(p);
    }
    cout << "Loaded " << problems.size() << " problem(s) from " << file1 << ".\n";
}