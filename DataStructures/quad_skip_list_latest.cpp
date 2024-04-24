#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;


// Define the Employee class to store employee information
class Employee {
    private:
        int id{};
        int salary{};
        int department{};
    public:
        Employee() = default;
        ~Employee() = default;
        Employee(int id, int salary, int department) {
            this->salary = salary;
            this->department = department;
            this->id = id;
        }
        void setSalary(int salary_) {this->salary = salary_;}
        void setDepartment(int dep_) {this->department = dep_;}
        int getId() const {return this->id;}
        int getSalary() const {return this->salary;}
        int getDepartment() const {return this->department;}
};

// Node structure for the Skip List
struct Node {
    Employee* employee;
    Node *next;
    Node *prev;
    Node *below;
    Node *above;

    Node(Employee* emp) : employee(emp), next(nullptr), prev(nullptr), below(nullptr), above(nullptr) {}
};


class SkipList {
private:
    Node *head;
    int maxLevel;
    int currentLevel;
    int highestId = INT16_MIN;

public:
    explicit SkipList(const std::string& filename) {
        Employee* emp = nullptr;
        head = new Node(emp); // Head node with the minimum integer value
        maxLevel = 1;
        currentLevel = 1;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open the file" << std::endl;
            exit(1);
        }
        std::string line;
        bool is_first_line = true;
        while (std::getline(file, line)) {
            // Skip first line
            if (is_first_line){
                is_first_line = false;
                continue;
            }
            std::istringstream ss(line);
            std::string token;
            std::getline(ss, token, ';');
            int id = std::stoi(token);
            std::getline(ss, token, ';');
            int salary = std::stoi(token);
            std::getline(ss, token, ';');
            int department = std::stoi(token);
            Employee* employee = new Employee(id, salary, department);
            insert(employee);
            if (id > highestId) {
                highestId = id;
            }
        }
        file.close();
    }

    // Adjust the height based on coin toss probability
    int determineNodeLevel() {
        int level = 1;
        while ((rand() & 1) && level < maxLevel + 1) { // Coin toss: 0 or 1 (0.5 probability)
            level++;
        }
        return level;
    }

    // Insert a new element into the Skip List
    void insert(Employee* emp) {
        Node *curr = head;
        Node *insertedNode = nullptr;
        Node *prevLevelNode = nullptr;

        /*
        * Step-1: Start by top-left node and this line to find where value is suitable
        * Step-2: If top line is not suitable look for the lower line, continue this 
        * until finding the right place. 
        * Step-3: If right place is found, create new node for given value and 
        * re-arrange nodes accordingly.
        * Step-4:
        */
       int key = emp->getId();
        while (curr) {
            // Find the node where the value is fitted
            while (curr->next && curr->next->employee->getId() < key) {
                curr = curr->next;
            }
            // Update node level (line)
            if (curr->below) {
                prevLevelNode = curr;
                curr = curr->below;
            }

            // Reached most bottom line.
            else {
                insertedNode = new Node(emp);
                insertedNode->next = curr->next;
                insertedNode->prev = curr;
                if (curr->next) {
                    curr->next->prev = insertedNode;
                }
                curr->next = insertedNode;

                if (prevLevelNode && insertedNode) {
                    insertedNode->above = insertedNode;
                    insertedNode->above->below = insertedNode;
                }

                break;
            }
        }
    }

    // Remove a node from the Skip List
    bool remove(int key) {
        Node *curr = head;
        while (curr) {
            while (curr->next && curr->next->employee->getId() < key) {
                curr = curr->next;
            }

            if (curr->next && curr->next->employee->getId() == key) {
                Node *toRemove = curr->next;
                curr->next = toRemove->next;
                if (toRemove->next) {
                    toRemove->next->prev = curr;
                }

                while (curr->above) {
                    curr = curr->above;
                    Node *temp = curr;
                    while (temp->next && temp->next != toRemove) {
                        temp = temp->next;
                    }
                    temp->next = toRemove->next;
                    if (toRemove->next) {
                        toRemove->next->prev = temp;
                    }
                    toRemove = toRemove->above;
                }

                delete toRemove; // Free memory
                return true;
            }

            if (curr->below) {
                curr = curr->below;
            } else {
                break;
            }
        }

        return false; // Node with given value not found
    }


    // Update employee information based on ID
    bool update(const Employee &emp) {
        Node *curr = head;

        while (curr) {
            while (curr->next && curr->next->employee->getId() < emp.getId()) {
                curr = curr->next;
            }

            if (curr->next && curr->next->employee->getId() == emp.getId()) {
                curr->next->employee->setSalary(emp.getSalary());
                curr->next->employee->setDepartment(emp.getDepartment());
                return true; // Employee information updated
            }

            if (curr->below) {
                curr = curr->below;
            } else {
                break;
            }
        }

        return false; // Employee ID not found
    }

    // Print the Skip List structure
    void print() {
        Node *curr = head;
        while (curr->below) {
            curr = curr->below;
        }

        while (curr) {
            Node *temp = curr;
            while (temp) {
                cout << temp->employee->getId() << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
            curr = curr->below;
        }
    }

    // Write employees to a CSV file
    void writeToFile(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            exit(1);
        }

        file << "Employee_ID;Salary;Department" << std::endl; // Writing the header

        Node *curr = head->next; // Start from the bottom-most level

        while (curr) {
            Node *temp = curr;
            while (temp) {
                Employee* emp = temp->employee;
                file << emp->getId() << ";" << emp->getSalary() << ";" << emp->getDepartment() << std::endl;
                temp = temp->next;
            }
            curr = curr->below;
        }
        file.close();
    }

    int getHighestId() const {
        return highestId;
    }

    void incrementHighestId() {
        highestId++;
    }

};

// Function to parse a line from operations.txt and execute the corresponding operation
void executeOperation(const std::string& operationLine,
                      SkipList& db) {
    std::istringstream iss(operationLine);
    std::string operation;
    if (std::getline(iss, operation, ';')) {
        if (operation == "ADD") {
            int salary;
            int department;
            iss >> salary;  // Parse salary
            iss.ignore(1, ';'); // Skip the delimiter
            iss >> department; // Parse department
//            clock_t start = clock();
            db.incrementHighestId();
            int id = db.getHighestId();
            Employee* emp = new Employee(id,salary,department);
            db.insert(emp); // took 0-1 ms.
//            clock_t end = clock();
//            double execution_time = (double) (end-start)*1000 / CLOCKS_PER_SEC;
//            std::cout << "Operation:ADD took" << execution_time << " seconds." << std::endl;

        }

        else if (operation == "UPDATE") {
            int id;
            int salary;
            int department;
            iss >> id;iss.ignore(1, ';'); // Skip the delimiter
            iss >> salary;iss.ignore(1, ';'); // Skip the delimiter
            iss >> department;
            // Search for the employee with the given ID and update their information
//            clock_t start = clock();
            Employee* emp = new Employee(id, salary, department);
            bool found = db.update(*emp); // took  0ms
            if (!found){
                std::cout << "ERROR: An invalid ID to update\n";
                return;
            }
//            clock_t end = clock();
//            double execution_time = (double) (end-start)*1000 / CLOCKS_PER_SEC;
//            std::cout << "Operation:Update took" << execution_time << " seconds." << std::endl;
        }

        else if (operation == "DELETE") {
            int id;
            iss >> id;
//            clock_t start = clock();
            bool is_found = db.remove(id); // took 0 ms
            if(!is_found){
                std::cout << "ERROR: An invalid ID to delete\n";
            }
//            clock_t end = clock();
//            double execution_time = (double) (end-start)*1000 / CLOCKS_PER_SEC;
//            std::cout << "Operation:Delete took" << execution_time << " seconds." << std::endl;
        }
    }
}


int main(int argc, char* argv[]) {
    // Create a copy of the original employee file
//    const std::string originalEmployeeFile = argv[1];
//    std::fstream operationsFile(argv[2], std::ios::in);

    const std::string originalEmployeeFile = "hw4/dataset/500k_employees.csv";
    std::fstream operationsFile("hw4/dataset/operations_for_500k_1.csv", std::ios::in);
    // Read operations line by line, and execute on employees db object.
    SkipList db(originalEmployeeFile);
    // Execute each operation line by line
    std::string line;
    while (getline(operationsFile, line)) {
        executeOperation(line, db);
    }
    // Write solutions to CSV file
    db.writeToFile("output.csv");

return 0;
}
