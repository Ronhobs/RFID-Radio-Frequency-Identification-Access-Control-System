#ifndef ACCESS_CONTROL_H
#define ACCESS_CONTROL_H

#include <unordered_map>
#include <vector>
#include <string>
#include "User.h"
#include "RFIDSimulation.h"

class AccessControl {
private:
    std::unordered_map<std::string, User> users;
    std::vector<std::string> accessLogs;

    void logAccessAttempt(std::string tagID, bool accessGranted);

public:
    AccessControl();
    void addUser(const User& user);
    void addAuthorizedTag(std::string userID, std::string tagID);
    bool checkAccess(RFIDReader& reader, std::string& userName);
    const std::vector<std::string>& getLogs() const;
};

#endif // ACCESS_CONTROL_H
