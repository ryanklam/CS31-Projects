//
//  main.cpp
//  Project 1 Logic error
//
//  Created by Ryan Lam on 10/3/18.
//  Copyright © 2018 Ryan Lam. All rights reserved.
//

// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;   // pp. 38-39 in Savitch 6/e explains this line

int main()
{
    int numberSurveyed;
    int forNewsom;
    int forCox;
    
    cout << "How many registered voters were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them say they will vote for Newsom? ";
    cin >> forNewsom;
    cout << "How many of them say they will vote for Cox? ";
    cin >> forCox;
    
    double pctNewsom = 10.0 * forNewsom / numberSurveyed; //ERROR: changed multiplier from 100 to 10
    double pctCox = 100.0 * forCox / numberSurveyed;
    
    cout.setf(ios::fixed);       // see pp. 32-33 in Savitch 6/e
    cout.precision(1);
    
    cout << endl;
    cout << pctNewsom << "% say they will vote for Newsom." << endl;
    cout << pctCox << "% say they will vote for Cox." << endl;
    
    if (forNewsom < forCox) //ERROR: changed > to <
        cout << "Newsom is predicted to win the election." << endl;
    else
        cout << "Cox is predicted to win the election." << endl;
}
