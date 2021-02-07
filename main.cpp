#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <algorithm>

// Author: Rasool Abbas
// Dr. Alkanali

class Date {
public:
    int month, day, year;

    Date(int month, int day, int year) {
        this->month = month;
        this->year = year;
        this->day = day;
    }

    Date() { this->month = this->day = this->year = NULL; }
};

class Assignment {
private:
    Date dueDate;
    std::string assignmentName;
public:
    Assignment(Date dueDate, std::string assignmentName) {
        this->dueDate = dueDate;
        this->assignmentName = assignmentName;
    }

    Date getDueTime() {
        return this->dueDate;
    }

    void setDueDate(Date newDueDate) {
        this->dueDate = newDueDate;
    }

    std::string getAssignmentName() {
        return this->assignmentName;
    }

    void setAssignmentName(std::string newName) {
        this->assignmentName = newName;
    }

    // Less than and greater than 
    // operator overloads for the 
    // handy sort() method
    // to take care of sorting for 
    // us
    bool operator<(const Assignment& d) {
        if (this->dueDate.year < d.dueDate.year) {
            return true;   
        } else {
            if (this->dueDate.year > d.dueDate.year) {
                return false;   
            }
            
            // year is the same
            if (this->dueDate.month < d.dueDate.month) {
                return true;   
            } else {
                if (this->dueDate.month > d.dueDate.month) {
                    return false;   
                }
                
                // Year and month is the same
                if (this->dueDate.day < d.dueDate.day) {
                    return true;   
                } else {
                    return false;   
                }
            }
        }
        
        return false;
    }

    bool operator>(const Assignment& d) {
        return !(*this < d);
    }

    bool operator==(const Assignment& d) {
        return ((this->dueDate.year == d.dueDate.year) && 
                (this->dueDate.month == d.dueDate.month) && 
                (this->dueDate.day == d.dueDate.day) && 
                (this->assignmentName == d.assignmentName));
    }

    bool hasSameDueDate(const Assignment d) {
        return ((this->dueDate.year == d.dueDate.year) && 
                (this->dueDate.month == d.dueDate.month) && 
                (this->dueDate.day == d.dueDate.day));
    }
};

class Assignments {
private:
    std::list<Assignment> assignmentsToDo;
public:
    Assignments() { }

    std::list<Assignment> getAssignmentList() {
        return this->assignmentsToDo;
    }

    void setAssignmentList(std::list<Assignment> newAssignmentList) {
        this->assignmentsToDo = newAssignmentList;
    }

    void addNewAssignment(Assignment newAssignment) {
        this->assignmentsToDo.push_back(newAssignment);
    }

    bool removeAssignment(std::string assignmentToRemove) {
        if (this->assignmentsToDo.size() == 0) {
            return false;
        }
        
        std::list<Assignment>::iterator it = this->assignmentsToDo.begin();        

        while (it != assignmentsToDo.end()) {
            if (assignmentToRemove == it->getAssignmentName()) {
                this->assignmentsToDo.remove(*it);
                return true;
            } else {
                it++;
            }
        }

        return false;
    }

    std::vector<Assignment> getEarliestDueDateAssignments() {
        // Returning a vector of assignments in case we 
        // have multiple with the same due date
        std::vector<Assignment> assignmentVector;

        if (this->assignmentsToDo.size() == 0) {
            return assignmentVector;
        }

        std::list<Assignment> assignmentsCopy = this->assignmentsToDo;

        assignmentsCopy.sort();

        std::list<Assignment>::iterator it;
        
        it = assignmentsCopy.begin();
        while (it != assignmentsCopy.end()) {
            if (it->hasSameDueDate(*assignmentsCopy.begin())) {
                assignmentVector.push_back(*it);
            }

            it++;
        }
        
        return assignmentVector;
    }

    std::vector<Assignment> getAssignmentsInOrder() {
        std::vector<Assignment> assignmentVector;

        if (this->assignmentsToDo.size() == 0) {
            return assignmentVector;
        }

        std::list<Assignment>::iterator it;

        it = this->assignmentsToDo.begin();
        while (it != this->assignmentsToDo.end()) {
            assignmentVector.push_back(*it);

            it++;
        }
        
        sort(assignmentVector.begin(), assignmentVector.end());

        return assignmentVector;
    }
    
    void clearAssignmentList() {
        this->assignmentsToDo.clear();   
    }
};

int main()
{   
    Assignments myAssignments;

    // Below is for showing the earliest due date(s) feature
    myAssignments.addNewAssignment(Assignment(Date(1, 12, 2021), "Data Structures Homework # 1"));
    myAssignments.addNewAssignment(Assignment(Date(1, 12, 2021), "Data Structures Homework # 1.5"));
    myAssignments.addNewAssignment(Assignment(Date(3, 22, 2021), "Data Structures Homework # 2"));
    myAssignments.addNewAssignment(Assignment(Date(1, 30, 2021), "Data Structures Homework # 3"));
    myAssignments.addNewAssignment(Assignment(Date(5, 9, 2021), "Data Structures Homework # 4"));

    std::vector<Assignment> curAssignment = myAssignments.getEarliestDueDateAssignments();

    for (size_t i = 0; i < curAssignment.size(); ++i) {
        std::cout << curAssignment.at(i).getAssignmentName() << std::endl;
    }
        
    std::cout << "==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==" << std::endl;
    
    // Below is for showing ordering
    // of the assignments by their due date
    myAssignments.addNewAssignment(Assignment(Date(7, 17, 2021), "Psychology Homework"));
    myAssignments.addNewAssignment(Assignment(Date(5, 26, 2020), "Random other homework Due Last Year"));
    myAssignments.addNewAssignment(Assignment(Date(8, 20, 2021), "Math homework"));
    myAssignments.addNewAssignment(Assignment(Date(6, 31, 2021), "Biology"));
    myAssignments.addNewAssignment(Assignment(Date(5, 25, 2021), "Engineering"));
    
    std::vector<Assignment> orderedListOfAssignments = myAssignments.getAssignmentsInOrder();

    for (size_t i = 0; i < orderedListOfAssignments.size(); ++i) {
        std::cout << orderedListOfAssignments.at(i).getAssignmentName() << std::endl;
    }
    
    std::cout << "==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==" << std::endl;

    // Below is the demo for removing homework
    if (myAssignments.removeAssignment("Engineering")) {
        std::vector<Assignment> newAssignments = myAssignments.getAssignmentsInOrder();
        
        for (size_t i = 0; i < newAssignments.size(); ++i) {
            std::cout << newAssignments.at(i).getAssignmentName() << std::endl;
        }
    } else {
        std::cout << "Couldn't find assignment" << std::endl;
    }
    
    std::cout << "==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==" << std::endl;
    
    // Below is the demo for removing homework that doesnt exist 
    if (myAssignments.removeAssignment("Some random assignment that doesnt exist")) {
        std::vector<Assignment> newAssignments = myAssignments.getAssignmentsInOrder();
        
        for (size_t i = 0; i < newAssignments.size(); ++i) {
            std::cout << newAssignments.at(i).getAssignmentName() << std::endl;
        }
    } else {
        std::cout << "Couldn't find assignment" << std::endl;
    }

    return 1;
}

// OUTPUT IS BELOW // 
/*
Data Structures Homework # 1
Data Structures Homework # 1.5
==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==
Random other homework Due Last Year
Data Structures Homework # 1
Data Structures Homework # 1.5
Data Structures Homework # 3
Data Structures Homework # 2
Data Structures Homework # 4
Engineering
Biology
Psychology Homework
Math homework
==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==
Random other homework Due Last Year
Data Structures Homework # 1
Data Structures Homework # 1.5
Data Structures Homework # 3
Data Structures Homework # 2
Data Structures Homework # 4
Biology
Psychology Homework
Math homework
==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==
Couldn't find assignment
*/
