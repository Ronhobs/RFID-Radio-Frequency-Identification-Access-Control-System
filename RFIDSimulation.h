#ifndef RFIDSIMULATION_H
#define RFIDSIMULATION_H

#include <string>
#include <vector>

class RFIDTag {
public:
    RFIDTag(std::string id);
    std::string getID() const;
private:
    std::string id;
};

class RFIDReader {
public:
    RFIDReader();
    std::string readTag();
    void simulateTag(std::string tagID); // For simulation purposes
private:
    std::string currentTagID;
};

#endif // RFIDSIMULATION_H
