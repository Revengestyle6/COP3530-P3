#include "CampusCompass.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

/**
 *
 */
CampusCompass::CampusCompass() {
    // initialize your object
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    ifstream edgesFile(edges_filepath);
    ifstream classesFile(classes_filepath);

    if (!edgesFile.is_open() || !classesFile.is_open()) return false;

    string command;

    // skip header
    getline(edgesFile, command);

    // parse edges.csv
    while (getline(edgesFile, command)) {
        stringstream ss(command);
        string a, b, name1, name2, timeStr;

        getline(ss, a, ',');
        getline(ss, b, ',');
        getline(ss, name1, ',');
        getline(ss, name2, ',');
        getline(ss, timeStr, ',');


        int hour = stoi(timeStr.substr(0, 2));
        int minute = stoi(timeStr.substr(3, 2));
        int time = hour * 60 + minute;

        edges[{a, b}] = make_pair(time,true);
    }

    // skip header
    getline(classesFile, command);

    // parse classes.csv
    while (getline(classesFile, command)) {
        stringstream ss(command);
        string code, loc, start, end;

        getline(ss, code, ',');
        getline(ss, loc, ',');
        getline(ss, start, ',');
        getline(ss, end, ',');

        int locationID = stoi(loc);

        classes[code] = {locationID, {start, end}};
    }

    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    if (command.substr(0, 6) == "insert") {
            size_t p1 = command.find('"');
            size_t p2 = command.find('"', p1 + 1);
            string name = command.substr(p1 + 1, p2 - p1 - 1);

            size_t p3 = command.find('"', p2 + 1);
            size_t p4 = command.find('"', p3 + 1);
            string id = command.substr(p3 + 1, p4 - p3 - 1);

            size_t p5 = command.find('"', p4 + 1);
            size_t p6 = command.find('"', p5 + 1);
            string residence = command.substr(p5 + 1, p6 - p5 - 1);

            vector<string> classesList;
            size_t pos = p6;
            while ((pos = command.find('"', pos)) != string::npos) {
                size_t end = command.find('"', pos + 1);
                if (end == string::npos) break;
                classesList.push_back(command.substr(pos + 1, end - pos - 1));
                pos = end + 1;
            }

            bool ok = insert(name, id, residence, classesList);
            cout << (ok ? "successful" : "unsuccessful") << endl;
        }

        else if (command.substr(0, 6) == "remove") {
            size_t p = command.find_first_of("0123456789");
            string id = command.substr(p);

            bool ok = remove(id);
            cout << (ok ? "successful" : "unsuccessful") << endl;
        }

        else if (command.substr(0, 9) == "dropClass") {
            size_t p1 = command.find('"');
            size_t p2 = command.find('"', p1 + 1);
            string id = command.substr(p1 + 1, p2 - p1 - 1);

            size_t p3 = command.find('"', p2 + 1);
            size_t p4 = command.find('"', p3 + 1);
            string classcode = command.substr(p3 + 1, p4 - p3 - 1);

            bool ok = dropClass(id, classcode);
            cout << (ok ? "successful" : "unsuccessful") << endl;
        }

        else if (command.substr(0, 12) == "replaceClass") {
            size_t p1 = command.find('"');
            size_t p2 = command.find('"', p1 + 1);
            string id = command.substr(p1 + 1, p2 - p1 - 1);

            size_t p3 = command.find('"', p2 + 1);
            size_t p4 = command.find('"', p3 + 1);
            string c1 = command.substr(p3 + 1, p4 - p3 - 1);

            size_t p5 = command.find('"', p4 + 1);
            size_t p6 = command.find('"', p5 + 1);
            string c2 = command.substr(p5 + 1, p6 - p5 - 1);

            bool ok = replaceClass(id, c1, c2);
            cout << (ok ? "successful" : "unsuccessful") << endl;
        }

        else if (command.substr(0, 11) == "removeClass") {
            size_t p = command.find('"');
            string classcode = command.substr(p + 1, command.find('"', p + 1) - p - 1);

            bool ok = removeClass(classcode);
            cout << (ok ? "successful" : "unsuccessful") << endl;
        }

        else if (command.substr(0, 18) == "toggleEdgesClosure") {
            // implementation placeholder
        }

        else if (command.substr(0, 17) == "checkEdgeStatus") {
            // implementation placeholder
        }

        else if (command.substr(0, 12) == "isConnected") {
            // implementation placeholder
        }

        else if (command.substr(0, 20) == "printShortestEdges") {
            size_t p = command.find('"');
            string id = command.substr(p + 1, command.find('"', p + 1) - p - 1);

            printShortestEdges(id);
        }

        else if (command.substr(0, 16) == "printStudentZone") {
            size_t p = command.find('"');
            string id = command.substr(p + 1, command.find('"', p + 1) - p - 1);

            printStudentZone(id);
        }

        else if (command.substr(0, 15) == "verifySchedule") {
            size_t p = command.find('"');
            string id = command.substr(p + 1, command.find('"', p + 1) - p - 1);

            bool ok = verifySchedule(id);
            cout << (ok ? "successful" : "unsuccessful") << endl;
        } else {
            return false;
        }
    return true;
}
// Insert a new student
bool CampusCompass::insert(const std::string& STUDENT_NAME,
                           const std::string& STUDENT_ID,
                           const std::string& RESIDENCE_LOCATION_ID,
                           const std::vector<std::string>& CLASSCODES) {
    // TODO
    std::regex idCheck = std::regex("^[0-9]{8}$");
    std::regex nameCheck = std::regex("^[A-Za-z]+( [A-Za-z]+)* ?$");
    std::regex classcodeCheck = std::regex("^[A-Z]{3}+[0-9]{4}$");

    if (!std::regex_match(STUDENT_NAME, nameCheck) || !std::regex_match(STUDENT_ID, idCheck)) {
        return false;
    }

    if (CLASSCODES.empty() || CLASSCODES.size() > 6) {
        return false;
    }

    for (const auto& c : CLASSCODES) {
        if (!std::regex_match(c, classcodeCheck)) {
            return false;
        }
    }

    int curSize = students.size();
    Student s = Student(STUDENT_NAME,STUDENT_ID,RESIDENCE_LOCATION_ID,CLASSCODES);
    students.insert({STUDENT_ID,s});
    return curSize + 1 == students.size();
}

// Remove a student
bool CampusCompass::remove(const std::string& STUDENT_ID) {
    // TODO
    int curSize = students.size();
    students.erase(STUDENT_ID);
    return curSize - 1 == students.size();
    return false;
}

// Drop a specific class for a student
bool CampusCompass::dropClass(const std::string& STUDENT_ID,
                             const std::string& CLASSCODE) {
    // TODO
    if (students.find(STUDENT_ID) != students.end()) {
        vector<string> classesList = students[STUDENT_ID].getClasses();
        for (int i = 0; i < classesList.size(); i++) {
            if (classesList[i] == CLASSCODE) {
                classesList.erase(classesList.begin()+i);
                students[STUDENT_ID].setClasses(classesList);
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

// Replace one class with another
bool CampusCompass::replaceClass(const std::string& STUDENT_ID,
                                const std::string& CLASSCODE_1,
                                const std::string& CLASSCODE_2) {
    // TODO
    if (students.find(STUDENT_ID) != students.end()) {
        vector<string> classesList = students[STUDENT_ID].getClasses();
        for (int i = 0; i < classesList.size(); i++) {
            if (classesList[i] == CLASSCODE_1) {
                classesList.erase(classesList.begin()+i);
                students[STUDENT_ID].setClasses(classesList);
                if (classesList.empty()) {
                    students.erase(students.find(STUDENT_ID));
                }
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

// Remove a class entirely from the system
bool CampusCompass::removeClass(const std::string& CLASSCODE) {
    // TODO
    int enrolledCount = 0;
    for (auto s : students) {
        enrolledCount += dropClass(s.second.getID(),CLASSCODE) ? 1 : 0;
    }
    cout << enrolledCount << endl;

    return enrolledCount != 0; // checks condition "no students have a given CLASSCODE"
    //unknown if it works for all other conditions
}

// Toggle edge closures for a location
bool CampusCompass::toggleEdgesClosure(const std::string& N,
                                       const std::vector<std::string>& LOCATION_IDS) {
    // TODO
    for (int i = 0; i < stoi(N); i++) {
        edges[{LOCATION_IDS[i*2],LOCATION_IDS[(i*2)+1]}].second = !(edges[{LOCATION_IDS[i * 2], LOCATION_IDS[(i * 2) + 1]}].second);
    }
    return false;
}

// Check if an edge is open/closed
bool CampusCompass::checkEdgeStatus(const std::string& LOCATION_ID_X,
                                    const std::string& LOCATION_ID_Y) {
    // TODO
    if (edges.find({LOCATION_ID_X,LOCATION_ID_Y}) == edges.end()) {
        cout << "DNE" << endl;
        return false;
    } else {
        string output = edges[{LOCATION_ID_X,LOCATION_ID_Y}].second ? "open" : "closed";
        cout << output << endl;
        return edges[{LOCATION_ID_X,LOCATION_ID_Y}].second;
    }
}

// Check connectivity between two locations
bool CampusCompass::isConnected(const std::string& LOCATION_ID_1,
                                const std::string& LOCATION_ID_2) {
    // TODO
    return false;
}

// Print shortest path edges for a student
void CampusCompass::printShortestEdges(const std::string& STUDENT_ID) {
    // TODO
}

// Print student’s zone
void CampusCompass::printStudentZone(const std::string& STUDENT_ID) {
    // TODO
}

// Verify if student's schedule is valid
bool CampusCompass::verifySchedule(const std::string& STUDENT_ID) {
    // TODO
    return false;
}

