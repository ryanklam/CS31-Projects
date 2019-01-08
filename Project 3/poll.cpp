//
//  main.cpp
//  Project 3
//
//  Created by Ryan Lam on 10/22/18.
//  Copyright © 2018 Ryan Lam. All rights reserved.
//

#include <iostream>
#include<fstream>
#include<vector>
#include<cassert>
#include<algorithm>

#include <string>

using namespace std;

bool isValidStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool processStateCode(string codeSection) // CHECKS IF STATE CODE IS VALID
{
    string stateCode = "";
    stateCode += toupper(codeSection[0]);
    stateCode += toupper(codeSection[1]);
    if(!isValidStateCode(stateCode))
    {
        return false;
    }
    return true;
}

bool processPartyResults(string codeSection) // CHECKS IF PARTY RESULT IS VALID
{
    bool hasLetter = false;
    string partyResult = codeSection.substr(2);
    if(partyResult.size() == 0)
    {
        return true;
    }
    if(partyResult.size() == 1)
    {
        return false;
    }
    if(isdigit(partyResult[partyResult.size()-1])) // IF PARTY RESULTS END WITH NUMBER, RETURN FALSE
    {
        return false;
    }
    for(int i = 0; i < partyResult.size(); i++)
    {
        if (!isdigit(partyResult[i]))
        {
            hasLetter = true;
            if(i > 2) // THIS MEANS THAT THERE ARE MORE THAN 2 NUMBERS BEFORE
            {
                return false;
            }
            else if (i == 0) // LETTER BEFORE ANY NUMBERS
            {
                return false;
            }
            else if (i == 2)
            {
                if(!isdigit(partyResult[i-1]) or !isdigit(partyResult[i-2]))
                {
                    return false;
                }
            }
            else if (i == 1)
            {
                if(!isdigit(partyResult[i-1]))
                {
                    return false;
                }
            }
            
            partyResult = partyResult.substr(i); // THIS TAKES OUT THE PARTY VOTES
            if(!isalpha(partyResult[0])) // THIS CHECKS FOR PARTY CODE
            {
                return false;
            }
            partyResult = partyResult.substr(1); // THIS TAKES OUT THE WHOLE PARTY RESULT
            i = -1;
        }
    }
    return hasLetter;
}

bool hasProperSyntax(string pollData)
{
    if(pollData.size() == 0)
    {
        return true;
    }
    string codeSection = "";
    for (int i = 0; i < pollData.size(); i++)
    {
        if(pollData[i] != ',')
        {
            codeSection += pollData[i];
        }
        else
        {
            if(!processStateCode(codeSection)) // CHECKS STATE CODES
            {
                return false;
            }
            if(!processPartyResults(codeSection)) // CHECKS PARTY RESULTS
            {
                return false;
            }
            codeSection = "";
        }
    }
    if(!processStateCode(codeSection)) // CODE WITHIN FOR LOOP RUNS ONCE MORE FOR LAST STATE FORECASTPr
    {
        return false;
    }
    if(!processPartyResults(codeSection)) // CHECKS PARTY RESULTS
    {
        return false;
    }
    codeSection = "";
    return true;
}

int tallySeats(string pollData, char party, int& seatTally)
{
    if(pollData.size() == 0) // IF POLL DATA IS EMPTY, DO NOT RUN CODE
    {
        seatTally = 0;
        return 0;
    }
    if (hasProperSyntax(pollData) == false) // IF SYNTAX IS INCORRECT, RETURN 1
    {
        return 1;
    }
    if (isalpha(party) == false) // IF PARTY IS NOT A CHAR, RETURN 2
    {
        return 2;
    }
    
    seatTally = 0; // ENSURE THAT POLL DATA SYNTAX IS CORRECT BEFORE SETTING SEAT TALLY TO 0
    string codeSection = "";
    for (int i = 0; i < pollData.size(); i++)
    {
        if(pollData[i] != ',')
        {
            codeSection += pollData[i];
        }
        else
        {
            
            codeSection = codeSection.substr(2);
            for(int j = 0; j < codeSection.size(); j++)
            {
                if(isalpha(codeSection[j]))
                {
                    if(codeSection[j] == toupper(party) or codeSection[j] == tolower(party))
                    {
                        if(isdigit(codeSection[j-1]))
                        {
                            int ones = codeSection[j-1] - '0';
                            seatTally += ones;
                        }
                        if(j > 1)
                        {
                            if(isdigit(codeSection[j-2]))
                            {
                                int tens = codeSection[j-2] - '0';
                                seatTally += (tens * 10);
                            }
                        }
                    }
                }
            }
            codeSection = "";
        }
    }
    codeSection = codeSection.substr(2); // SECTION WITHIN FOR LOOP RUNS ONCE MORE FOR THE LAST FORECAST
    for(int j = 0; j < codeSection.size(); j++)
    {
        if(isalpha(codeSection[j]))
        {
            if(codeSection[j] == toupper(party) or codeSection[j] == tolower(party))
            {
                if(isdigit(codeSection[j-1]))
                {
                    int ones = codeSection[j-1] - '0';
                    seatTally += ones;
                }
                if(j > 1)
                {
                    if(isdigit(codeSection[j-2]))
                    {
                        int tens = codeSection[j-2] - '0';
                        seatTally += (tens * 10);
                    }
                }
            }
        }
    }
    codeSection = "";
    return 0;
}

int main()
{
    int seats = -999;
    cout << tallySeats("CA4D,NY5R", 'D', seats) << endl;
    cout << seats << endl;
    return 0;
}



 
 

