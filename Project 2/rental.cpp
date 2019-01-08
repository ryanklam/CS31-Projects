//
//  main.cpp
//  Project 2
//
//  Created by Ryan Lam on 10/10/18.
//  Copyright © 2018 Ryan Lam. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    // Prompts user to input values
    cout << "Odometer at start: ";
    int startMileage;
    cin >> startMileage;
    
    cout << "Odometer at end: ";
    int endMileage;
    cin >> endMileage;
    
    cout << "Rental days: ";
    int rentalDays;
    cin >> rentalDays;
    cin.ignore(10000, '\n'); // Ignore function passes over leftover nextline character
    
    cout << "Customer name: ";
    string name;
    getline(cin, name);
    
    cout << "Luxury car? (y/n): ";
    string luxury;
    getline(cin, luxury);
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    
    cout << "---" << endl;
    
    // Checks for errors in user input
    if (startMileage < 0)
    {
        cout << "The starting odometer reading must be nonnegative.";
    }
    else if (endMileage < startMileage)
    {
        cout << "The final odometer reading must be at least as large as the starting reading.";
    }
    else if (rentalDays < 0)
    {
        cout << "The number of rental days must be positive.";
    }
    else if (name.empty())
    {
        cout << "You must enter a customer name.";
    }
    else if (luxury != "y" and luxury != "n")
    {
        cout << "You must enter y or n.";
    }
    else if (month < 1 or month > 12)
    {
        cout << "The month number must be in the range 1 through 12.";
    }
    else // Successful output, runs if no user errors are detected
    {
        double totalPrice = 0;
        int milesDriven = endMileage - startMileage;
        if (milesDriven <= 100)
        {
            totalPrice += 0.27 * milesDriven;
        }
        else if (milesDriven <= 400)
        {
            totalPrice += 0.27 * 100;
            if (month == 12 or month == 1 or month == 2 or month == 3)
            {
                totalPrice += 0.27 * (milesDriven - 100);
            }
            else
            {
                totalPrice += 0.21 * (milesDriven - 100);
            }
        }
        else
        {
            totalPrice += 0.27 * 100;
            if (month == 12 or month == 1 or month == 2 or month == 3)
            {
                totalPrice += 0.27 * 300;
            }
            else
            {
                totalPrice += 0.21 * 300;
            }
            totalPrice += 0.19 * (milesDriven - 400);
        }
        
        if (luxury == "y")
        {
            totalPrice += (61 * rentalDays);
        }
        else
        {
            totalPrice += (33 * rentalDays);
        }
        cout.setf(ios::fixed); // Sets the totalPrice double to two decimal points
        cout.precision(2);
        cout << "The rental charge for " << name << " is $" << totalPrice;
    }
    
}

