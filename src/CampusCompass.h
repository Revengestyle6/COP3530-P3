#pragma once
#include <map>
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
    unordered_map<string, vector<string>> GRAPH; // id points to classcodes

public:
    Student(string STUDENT_NAME,
            string STUDENT_ID,
            string RESIDENCE_LOCATION_ID,
            vector<string> CLASSCODES)
        : STUDENT_NAME(std::move(STUDENT_NAME)),
          STUDENT_ID(std::move(STUDENT_ID)),
          RESIDENCE_LOCATION_ID(std::move(RESIDENCE_LOCATION_ID)),
          CLASSCODES(std::move(CLASSCODES)),
          GRAPH() {}
    Student() = default;
    string getName() const { return STUDENT_NAME; }
    string getID() const { return STUDENT_ID; }
    string getResidence() const { return RESIDENCE_LOCATION_ID; }
    vector<string> getClasses() const { return CLASSCODES; }
    unordered_map<string, vector<string>> getGraph() const { return GRAPH; }

    // setters
    void setName(const string& name) { STUDENT_NAME = name; }
    void setID(const string& id) { STUDENT_ID = id; }
    void setResidence(const string& residence) { RESIDENCE_LOCATION_ID = residence; }
    void setClasses(const vector<string>& classes) { CLASSCODES = classes; }
    void setGraph(const unordered_map<string, vector<string>>& graph) { GRAPH = graph; }
};

class CampusCompass {
    // TODO
    // create map that links classcode to location
    // create edgelist/adj matrix of each edge (WITH TOGGLE FOR On/Off)
private:
    // Think about what member variables you need to initialize
    // perhaps some graph representation?
    map<string, Student> students;
    map<pair<string,string>, pair<int,bool>> edges; // id1, id2, distance
    map<string, pair<int, pair<string,string>>> classes; // classcode, id, start, end
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
    bool checkEdgeStatus(const string& LOCATION_ID_X, const string& LOCATION_ID_Y);
    bool isConnected(const string& LOCATION_ID_1, const string& LOCATION_ID_2);
    void printShortestEdges(const string& STUDENT_ID);
    void printStudentZone(const string& STUDENT_ID);
    bool verifySchedule(const string& STUDENT_ID);
};
