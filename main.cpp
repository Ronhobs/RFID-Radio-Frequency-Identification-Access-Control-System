#include "RFIDSimulation.h"
#include "AccessControl.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <RFID_TAG_ID>" << std::endl;
        return 1;
    }

    std::string simulatedTagID = argv[1];
    
    // Initialize component
    RFIDReader reader;
    AccessControl accessControl;

    // Add users and authorized tags
    User user1("1", "Alice");
    User user2("2", "Bob");
    User user3("3", "Serena");
    User user4("4", "Micah");
    User user5("5", "Jake");

    user1.addRFIDTag("19729");
    user2.addRFIDTag("62190");
    user3.addRFIDTag("90415");
    user4.addRFIDTag("38910");
    user5.addRFIDTag("07280");

    accessControl.addUser(user1);
    accessControl.addUser(user2);
    accessControl.addUser(user3);
    accessControl.addUser(user4);
    accessControl.addUser(user5);

    // Simulate reading the tag
    reader.simulateTag(simulatedTagID);

    // Check access
    std::string userName;
    if (accessControl.checkAccess(reader, userName)) {
        std::cout << "Access Granted to " << userName << std::endl;
    } else {
        std::cout << "Access Denied" << std::endl;
    }

    // Print logs
    const auto& logs = accessControl.getLogs();
    for (const auto& log : logs) {
        std::cout << log << std::endl;
    }

    return 0;
}
