#include <fstream>
#include <iostream>
#include <string>
#include "Pay.h"

void readStoreData(Pay & w, const std::string & f) {
    int days = 5;
    std::string fname;
    std::string lname;
    double ratePerHour;
    double normalHours;
    double extraHours;
    double totalHours;

    std::ifstream inFile;
    inFile.open(f);

    while(inFile >> fname) { // reads 1 record
        extraHours = 0;
        normalHours = 0;
        inFile >> lname >> ratePerHour;
        // create a for loop using # of days to read the rest of the record
        for(int i =0; i < days; i++) { // reads hours for 5 days
            inFile >> totalHours;
            if(totalHours > 8) { // IFF hours included OT
                extraHours += totalHours - 8; // i = 0 ex 9.0: extrahours = 0 + (9 - 8) == 1
                                              // i = 1 ex 10.5: extrahours = 1 + (10.5 - 8) == 3.5
                normalHours += 8;
            }
            else { // worked less than or equal to 8 hours
                normalHours += totalHours;
            }
        }
        // at this time, I have normal hours and OT hours computed and separated
        // have to save record before moving on
        std::string fullName = fname + " " + lname;
        //std::cout << fullName << " " << ratePerHour<< " " << normalHours<< " " << extraHours << std::endl;
        w.addEmployee(fullName, ratePerHour, normalHours, extraHours); // fname = "Stephanie" lname = "Quail" ?
                         // fname + lname -> "StephanieQuail"
                         // fname + " " + lname -> "Stephanie Quail"
    }

}

int main() {
    std::string fname = "input.txt";
    Pay week;
    readStoreData(week, fname); // need to pass the obj and file name
    week.payAndClearEmployees();

	system("pause");
    return 0;
}