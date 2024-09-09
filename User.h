#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_set>

class User {
public:
    User();
    User(std::string id, std::string name);

    std::string getID() const;
    std::string getName() const;
    void addRFIDTag(std::string tagID);
    const std::unordered_set<std::string>& getRFIDTags() const;

private:
    std::string id;
    std::string name;
    std::unordered_set<std::string> rfidTags;
};

#endif // USER_H
