#include "RFIDSimulation.h"

// RFIDTag implementation
RFIDTag::RFIDTag(std::string id) : id(id) {}

std::string RFIDTag::getID() const {
    return id;
}

// RFIDReader implementation
RFIDReader::RFIDReader() : currentTagID("") {}

std::string RFIDReader::readTag() {
    return currentTagID;
}

void RFIDReader::simulateTag(std::string tagID) {
    currentTagID = tagID;
}
