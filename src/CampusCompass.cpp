#include "CampusCompass.h"

#include <string>

using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // return boolean based on whether parsing was successful or not
    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
// Insert a new student
bool CampusCompass::insert(const std::string& STUDENT_NAME,
                           const std::string& STUDENT_ID,
                           const std::string& RESIDENCE_LOCATION_ID,
                           const std::vector<std::string>& CLASSCODES) {
    // TODO

    return false;
}

// Remove a student
bool CampusCompass::remove(const std::string& STUDENT_ID) {
    // TODO
    return false;
}

// Drop a specific class for a student
bool CampusCompass::dropClass(const std::string& STUDENT_ID,
                             const std::string& CLASSCODE) {
    // TODO
    return false;
}

// Replace one class with another
bool CampusCompass::replaceClass(const std::string& STUDENT_ID,
                                const std::string& CLASSCODE_1,
                                const std::string& CLASSCODE_2) {
    // TODO
    return false;
}

// Remove a class entirely from the system
bool CampusCompass::removeClass(const std::string& CLASSCODE) {
    // TODO
    return false;
}

// Toggle edge closures for a location
bool CampusCompass::toggleEdgesClosure(const std::string& N,
                                       const std::vector<std::string>& LOCATION_IDS) {
    // TODO
    return false;
}

// Check if an edge is open/closed
bool CampusCompass::checkEdgeStatus(const std::string& LOCATION_ID_X,
                                    const std::string& LOCATION_ID_Y) {
    // TODO
    return false;
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

