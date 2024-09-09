#include "User.h"

User::User() : id(""), name("") {}

User::User(std::string id, std::string name) : id(id), name(name) {}

std::string User::getID() const {
    return id;
}

std::string User::getName() const {
    return name;
}

void User::addRFIDTag(std::string tagID) {
    rfidTags.insert(tagID);
}

const std::unordered_set<std::string>& User::getRFIDTags() const {
    return rfidTags;
}
