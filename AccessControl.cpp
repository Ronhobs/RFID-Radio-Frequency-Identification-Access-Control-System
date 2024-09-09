#include "AccessControl.h"
#include <ctime>

AccessControl::AccessControl() {
    // Initialization if needed
}

void AccessControl::addUser(const User& user) {
    users.emplace(user.getID(), user);
}

void AccessControl::addAuthorizedTag(std::string userID, std::string tagID) {
    auto it = users.find(userID);
    if (it != users.end()) {
        it->second.addRFIDTag(tagID);
    }
}

bool AccessControl::checkAccess(RFIDReader& reader, std::string& userName) {
    std::string tagID = reader.readTag();
    for (const auto& [id, user] : users) {
        if (user.getRFIDTags().find(tagID) != user.getRFIDTags().end()) {
            userName = user.getName();
            logAccessAttempt(tagID, true);
            return true;
        }
    }
    logAccessAttempt(tagID, false);
    return false;
}

void AccessControl::logAccessAttempt(std::string tagID, bool accessGranted) {
    std::time_t now = std::time(0);
    char* dt = std::ctime(&now);
    std::string logEntry = std::string(dt) + "-Tag:" + tagID + "-" + (accessGranted ? "Access Granted" : "Access Denied");
    accessLogs.push_back(logEntry);
}

const std::vector<std::string>& AccessControl::getLogs() const {
    return accessLogs;
}
