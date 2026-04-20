#pragma once
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Student {
private:
    string STUDENT_NAME;
    string STUDENT_ID;
    string RESIDENCE_LOCATION_ID;
    vector<string> CLASSCODES;
    unordered_map<pair<string,string>, string> GRAPH;
};

class CampusCompass {
private:
    // Think about what member variables you need to initialize
    // perhaps some graph representation?
    unordered_map<string, Student> students;
    // ID, Name, Residence ID, Class Codes
public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);
    bool insert(const string& STUDENT_NAME, const string& STUDENT_ID, const string& RESIDENCE_LOCATION_ID, const vector<string>& CLASSCODES);
    bool remove(const string& STUDENT_ID);
    bool dropClass(const string& STUDENT_ID, const string& CLASSCODE);
    bool replaceClass(const string& STUDENT_ID, const string& CLASSCODE_1, const string& CLASSCODE_2);
    bool removeClass(const string& CLASSCODE);
    bool toggleEdgesClosure(const string& N, const vector<string>& LOCATION_IDS);
    bool checkEdgeStatus(const string& LOCATION_ID_X,const string& LOCATION_ID_Y);
    bool isConnected(const string& LOCATION_ID_1,const string& LOCATION_ID_2);
    void printShortestEdges(const string& STUDENT_ID);
    void printStudentZone(const string& STUDENT_ID);
    bool verifySchedule(const string& STUDENT_ID);
};
