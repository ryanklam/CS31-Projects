//
//  main.cpp
//  Project 4
//
//  Created by Ryan Lam on 11/1/18.
//  Copyright © 2018 Ryan Lam. All rights reserved.
//

#include <iostream>
#include <string>
#include <array>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
    if( n < 0)
    {
        return -1;
    }
    for(int i = 0; i < n; i++)
    {
        if(!a[i].empty()) // MAKES SURE THAT STRING IS NOT EMPTY
        {
            a[i].append(value);
        }
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    if(n < 0)
    {
        return -1;
    }
    int index = -1;
    int i = 0;
    while(i < n)
    {
        if(a[i] == target) // FUNCTION FINDS TARGET IN ARRAY
        {
            index = i;
            break;
        }
        i++;
    }
    return index;
}

int positionOfMax(const string a[], int n)
{
    if(n <= 0)
    {
        return -1;
    }
    if(a[0] == "\0") // IF ARRAY IS EMPTY
    {
        return -1;
    }
    int index = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(a[i] < a[j])
            {
                if(a[j] != a[index] and a[j] > a[index]) // CHECKS IF THE FOUND STRING IS THE SAME AS THE CURRENT MAX STRING
                {
                    index = j;
                    i = j;
                    break;
                }
            }
        }
    }
    return index;
}

int rotateLeft(string a[], int n, int pos)
{
    if(n <= 0)
    {
        return -1;
    }
    string temp = a[pos];
    for(int i = pos; i < n - 1; i++)
    {
        a[i] = a[i+1]; // SHIFTS ARRAY LEFT
    }
    a[n-1] = temp; // MOVES STRING AT POS TO THE END OF ARRAY
    return pos;
}

int countRuns(const string a[], int n)
{
    if( n < 0)
    {
        return -1;
    }
    if(n == 0)
    {
        return 0;
    }
    if(a[0] == "\0")
    {
        return 0;
    }
    int count = 1;
    string current = a[0];
    for(int i = 0; i < n; i++)
    {
        if(a[i] != current)  // CHECKS IF STRING HAS CHANGED
        {
            count++;
            current = a[i];
        }
    }
    return count;
}

int flip(string a[], int n)
{
    if(n < 0)
    {
        return -1;
    }
    int start = 0;
    int end = n - 1;
    while(start < end) // MAKES SURE IT DOESN'T GO PAST THE MIDDLE OF THE STRING
    {
        string temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++; // INDEXES OF ARRAY
        end--;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 or n2 < 0)
    {
        return -1;
    }
    if(a1[0] == "\0" or a2[0] == "\0") // IF EITHER ARRAY IS EMPTY
    {
        return 0;
    }
    int pos = 0;
    while(a1[pos] == a2[pos]) // CHECKS IF STRINGS DIFFER
    {
        if(pos == n1 or pos == n2) // REACHES END OF AN ARRAY
        {
            if(n1<n2 or n1==n2)
            {
                return n1;
            }
            else
            {
                return n2;
            }
        }
        pos++;
    }
    return pos;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(a2[0] == "\0")
    {
        return 0;
    }
    if(n1 < 0 or n2 < 0)
    {
        return -1;
    }
    for(int i = 0; i < n1; i++)
    {
        if(a1[i] == a2[0])
        {
            int index = i;
            int index2 = 0;
            while(a1[index] == a2[index2])
            {
                if(index2 == n2 - 1)  // IF END OF N2 IS REACHED AND BOTH STRINGS ARE IDENTICAL SO FAR
                {
                    return i;
                }
                index++;
                index2++;
            }
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 or n2 < 0)
    {
        return -1;
    }
    if(a1[0] == "\0" or a2[0] == "\0")
    {
        return -1;
    }
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            if(a1[i] == a2[j])
            {
                return i; // RETURNS THE FIRST ELEMENT THAT IS THE SAME
            }
        }
    }
    return -1;
}

int divide(string a[], int n, string divider)
{
    if( n < 0)
    {
        return -1;
    }
    if(a[0] == "\0")
    {
        return n;
    }
    int larger = 0; // USED TO RECORD HOW MANY LARGER STRINGS THERE ARE
    for(int i = 0; i < n; i++)
    {
        if(a[i] > divider or a[i] == divider)
        {
            larger++;
        }
    }
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(count == larger) // ONLY NEED TO LOOP AS MANY TIMES AS THERE ARE LARGER ELEMENTS TO MOVE
        {
            break;
        }
        if(a[i] > divider or a[i] == divider)
        {
            string temp = a[i];
            for(int j = i; j < n - 1; j++)
            {
                a[j] = a[j+1];
            }
            a[n - 1] = temp;
            count++;
            i--;
        }
    }
    for(int b = 0; b < n; b++)  // MOVES IDENTICAL STRING TO MIDDLE BETWEEN SMALLER AND LARGER
    {
        if(a[b] == divider)
        {
            while(a[b-1] > a[b])
            {
                string temp = a[b-1];
                a[b-1] = a[b];
                a[b] = temp;
                b--;
            }
        }
    }
    int index = n;
    for(int k = 0; k < n; k++)
    {
        if(a[k] > divider or a[k] == divider) // FINDS INDEX OF FIRST LARGER OR EQUAL STRING
        {
            index = k;
            break;
        }
    }
    return index;
}

int main()
{

    
    /*
    // APPEND TO ALL
    string a1[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    cout << appendToAll(a1, 5, "%") << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << a1[i] << " ";
    }
    cout << endl;
    */
    
    /*
    // LOOKUP
    string a2[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    cout << lookup(a2, 5, "dianne") << endl;
    */
    
    /*
    // POSITION OF MAX
    string a3[20] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
    cout << positionOfMax(a3, 0) << endl;
    */
    
    /*
    // ROTATE LEFT
    string a7[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    cout<< rotateLeft(a7, 4, 0) << endl;  // returns 1
    for (int i = 0; i < 5; i++)
    {
        cout << a7[i] << " ";
    }
    cout << endl;
    */
    
    /*
    // COUNT RUNS
    string a4[9] = {"xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john"};
    cout << "result " << countRuns(a4, 9) << endl;
    */
    
    
    /*
    // FLIP
    string a5[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    cout << flip(a5, 5) << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << a5[i] << " ";
        
    }
    */
    
    /*
    // DIFFER
    string a6[6] = {"betty", "john", "", "xavier", "kevin", "dianne" };
    string group[2] = { "betty", "john" };
    cout << differ(a6, 2, group, 2) << endl;  //  returns 2
    cout << differ(a6, 2, group, 1) << endl;
    */
    
    /*
    // SUBSEQUENCE
    string names[10] = { "eleni", "ga", "ke", "g", "gavin", "kevin", "greg" };
    string names1[10] = { "gavin", "kevin", "greg" };
    cout << subsequence(names, 7, names1, 3) << endl;  // returns 1
    string names2[10] = {"eleni", "greg"};
    cout << subsequence(names, 5, names2, 2) << endl;  // returns -1
    */
    
    /*
    //LOOK UP ANY
    string names[10] = { "eleni", "greg", "kevin", "gavin", "betty", "fiona" };
    string set1[10] = {"dianne", "betty", "pooch", "gavin" };
    cout << lookupAny(names, 6, set1, 4) << endl;  // returns 1 (a1 has "gavin" there)
    string set2[10] = { "xavier", "ed"};
    cout << lookupAny(names, 6, set2, 2) << endl;  // returns -1 (a1 has none)
    */
    
    /*
    // DIVIDE
    string eat[7] = {"greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    cout << divide(eat, 4, "fiona") << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << eat[i] << " ";
        
    }
    cout << endl;
    */
    
    ///*
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
    
    string e[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "fiona", "ed", "john" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");
    
    assert(divide(h, 7, "fiona") == 3);
    
    cout << "All tests succeeded" << endl;
    //*/
    
    
    
    /*
    //int appendToAll(string a[], int n, string value):
    string a[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    assert(appendToAll(a, 5, "!!!") == 5 && a[2] == "ed!!!"); // appendToAll works correctly
    assert(appendToAll(a, -1, "!!!") == -1); //n is negative
    assert(appendToAll(a, 0, "!!!") == 0); //n is 0
    a[4] = "greg"; a[0] = "dianne"; //reset a[4] and a[0] back to the original array
    assert(appendToAll(a, 5, "") == 5 && a[4] == "greg");//string to append is empty
    assert(appendToAll(a, 1, "!!!") == 1 && a[0] == "dianne!!!");//n is less than the size of the array
    
    //int lookup(const string a[], int n, string target):
    string b[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    assert (lookup(b, 5,"dianne") == 0); //lookup works properly
    assert (lookup(b, 5,"edlol") == -1);//target not in array
    assert (lookup(b, -1,"dianne") == -1);//n is negative
    assert (lookup(b, 0,"dianne") == -1);//n is equal to 0
    string c[5] = { "dianne", "ed", "ed", "ed", "greg" };
    assert (lookup(c, 5,"ed") == 1);//multiple instances of target
    
    //int positionOfMax(const string a[], int n):
    string d[6] = { "dianne", "fiona", "ed", "xavier", "greg" ,"betty" };
    assert(positionOfMax(d, 6) == 3); //positionOfMax works correctly
    assert(positionOfMax(d, 0) == -1); //n is 0, no interesting elements
    assert(positionOfMax(d, 4) == 3);//n  is less than length of array
    string e2[6] = { "dianne", "xavier", "ed", "xavier", "greg" ,"betty" };
    assert(positionOfMax(e2, 6) == 1); //more than one max string
    assert(positionOfMax(d, -10) == -1); //n is negative
    
    //int rotateLeft(string a[], int n, int pos):
    string politician[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    assert(rotateLeft(politician, 5, 1) == 1 && politician[2] == "kevin"); //rotateLeft works correctly
    string anotheronebitesthedust[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    assert(rotateLeft(anotheronebitesthedust, 4, 2) == 2 && anotheronebitesthedust[3] == "fiona"); //n is less than array size
    assert(rotateLeft(politician, -10, 1) == -1); //n is negative
    assert(rotateLeft(politician, 0, 1) == -1); //n is 0
    assert(rotateLeft(politician, 5, -1) == -1); //pos is 0
    
    //int countRuns(const string a[], int n):
    string lll[9] = {"xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john"};
    assert(countRuns(lll,9) == 5); //countRuns works as intended
    assert(countRuns(lll,-4) == -1);//n is negative
    assert(countRuns(lll,0) == 0);//n is 0
    assert(countRuns(lll,4) == 3);//n is less than array size
    
    //int flip(string a[], int n):
    string folks[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    assert(flip(folks, 6) == 6 && folks[1] == "kevin"); //flip works as expected
    string thesecondfolks[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    assert(flip(thesecondfolks, 4) == 4 && thesecondfolks[1] == "");//n is less than array size
    assert(flip(folks, 0) == 0); //n is 0
    assert(flip(folks, -10) == -1);//n is negative
    
    //int differ(const string a1[], int n1, const string a2[], int n2):
    string hello[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string group[5] = { "betty", "john", "dianne", "", "xavier" };
    assert (differ(hello, 6, group, 5) == 2); //differ works correctly
    assert (differ(hello, 2, group, 1) == 1); //n1 contains all of n2
    //n1 or n2 is negative
    //n1 is zero
    //n2 is zero
    //arrays are equal until they run out
    
    
    
    
    string f[3] = { "fiona", "ed", "john" };
    string e[4] = { "ed", "xavier", "", "eleni" };
    string f3[3] = {};
    
    string h1[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(subsequence(h1, 7, e, 4) == 2); // subsequence works correctly
    string h2[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(subsequence(h2, -7, e, -4) == -1); // n is negative
    string h3[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(subsequence(h3, 0, e, 4) == -1); // n is zero
    string h4[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(subsequence(h4, 4, e, 2) == 2); // n is less than array size
    assert(subsequence(f3, 7, f, 4) == -1); // empty array
    string k2[3] ={"ed", "eleni", "xavier"};
    string h5[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(subsequence(h5, 7, k2, 3) == -1); // no contiguous subsequence
    assert(subsequence(h5, 7, f3, 0) == 0); // subsequence is empty array
    string h6[7] = {"greg", "gavin", "ed", "xavier", "", "ed", "xavier"};
    string h7[2] = {"ed", "xavier"};
    assert(subsequence(h6, 7, h7, 2) == 2); // subsequence appears more than once
    
    
    string h8[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookupAny(h8, 7, f, 3) == 2); // lookupAny works correctly
    string h9[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookupAny(h9, -7, f, -3) == -1); // n is negative
    string h10[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookupAny(h10, 0, f, 3) == -1); // n is zero
    string f2[3] ={"fred", "brian", "john"};
    string h11[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookupAny(h11, 7, f2, 3) == -1); // no equal elements
    string h12[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookupAny(h12, 4, f, 1) == -1); // n is less than array size
    
    assert(lookupAny(f3, 7, f, 3) == -1); // empty array
    
    
    string h21[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(divide(h21, 7, "fiona") == 3); // divide works correctly
    string h22[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(divide(h22, -7, "fiona") == -1); // n is negative
    string h23[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(divide(h23, 0, "fiona") == 0); // n is zero
    assert(divide(f3, 3, "fiona") == 3); // empty array
    string h24[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(divide(h24, 7, "fred") == 4); // divider is not in array
    string h25[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(divide(h25, 4, "fiona") == 1); // n is less than array size
    string h100[4] = {"ed", "", "eleni", "fiona"};
    assert(divide(h100, 4, "fred") == 4); // no elements greater than or equal to divider
    
    cout << "passed" << endl;
    */
    
}


