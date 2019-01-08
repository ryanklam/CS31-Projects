//
//  main.cpp
//  Project 5
//
//  Created by Ryan Lam on 11/9/18.
//  Copyright © 2018 Ryan Lam. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;


const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 250;

void rotate2DArray(char str[][MAX_WORD_LENGTH+1], int size, int index)
{
    char temp[MAX_WORD_LENGTH];
    strcpy(temp, str[index]);
    for(int i = index; i < size - 1; i++)
        strcpy(str[i], str[i+1]);
    strcpy(str[size - 1], temp);
}

void rotate1DArray(int num[], int size, int index)
{
    int temp = num[index];
    for(int i = index; i < size - 1; i++)
        num[i] = num[i+1];
    num[size-1] = temp;
}

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns)
{
    if(nPatterns < 0)
        return 0;
    
    for(int i = 0; i < nPatterns; i++)
    {
        if(strlen(word1[i]) == 0 or strlen(word2[i]) == 0 or separation[i] < 0) // REMOVES PATTERNS WITH EMPTY WORDS, NEGATIVE SEPARATIONS
        {
            // REMOVE PATTERN FROM ARRAY
            rotate2DArray(word1, nPatterns, i);
            rotate2DArray(word2, nPatterns, i);
            rotate1DArray(separation, nPatterns, i);
            nPatterns--;
            i--; 
        }
        else
        {
            for(int j = 0; j < strlen(word1[i]); j++)  // WORD 1 LOOP
            {
                if(isalpha(word1[i][j])) // CHECKS IF CHARACTER IS A LETTER
                    if(isupper(word1[i][j]))
                        word1[i][j] = tolower(word1[i][j]); // CHANGES FROM UPPER TO LOWER
                if(!isalpha(word1[i][j]))
                {
                    
                     // REMOVE PATTERN FROM ARRAY
                     rotate2DArray(word1, nPatterns, i);
                     rotate2DArray(word2, nPatterns, i);
                     rotate1DArray(separation, nPatterns, i);
                     nPatterns--;
                     i--;
                }
            }
            
            for(int k = 0; k < strlen(word2[i]); k++) // WORD 2 LOOP
            {
                if(isalpha(word2[i][k])) // CHECKS IF CHARACTER IS A LETTER
                    if(isupper(word2[i][k]))
                        word2[i][k] = tolower(word2[i][k]); // CHANGES FROM UPPER TO LOWER
                if(!isalpha(word2[i][k]))
                {
                     // REMOVE PATTERN FROM ARRAY
                     rotate2DArray(word1, nPatterns, i);
                     rotate2DArray(word2, nPatterns, i);
                     rotate1DArray(separation, nPatterns, i);
                     nPatterns--;
                     i--;
                }
            }
        }
    }

    for(int ii = 0; ii < nPatterns-1; ii++)
    {
        for(int jj = ii+1; jj < nPatterns; jj++)
        {
            if(strcmp(word1[ii], word1[jj]) == 0 and strcmp(word2[ii], word2[jj]) == 0) // CHECKS FOR REPEATED PATTERNS
            {
                if(separation[ii] > separation[jj])
                {
                    // REMOVE PATTERN FROM ARRAY
                    rotate2DArray(word1, nPatterns, jj);
                    rotate2DArray(word2, nPatterns, jj);
                    rotate1DArray(separation, nPatterns, jj);
                    nPatterns--; 
                    ii--;
                }
                else if(separation[ii] < separation[jj])
                {
                    // REMOVE PATTERN FROM ARRAY
                    rotate2DArray(word1, nPatterns, ii);
                    rotate2DArray(word2, nPatterns, ii);
                    rotate1DArray(separation, nPatterns, ii);
                    nPatterns--;
                    ii--;
                }
                else 
                {
                    rotate2DArray(word1, nPatterns, jj);
                    rotate2DArray(word2, nPatterns, jj);
                    rotate1DArray(separation, nPatterns, jj);
                    nPatterns--;
                    ii--;
                }
            }
            if(strcmp(word1[ii], word2[jj]) == 0 and strcmp(word2[ii], word1[jj]) == 0)
            {
                if(separation[ii] > separation[jj])
                {
                    // REMOVE PATTERN FROM ARRAY
                    rotate2DArray(word1, nPatterns, jj);
                    rotate2DArray(word2, nPatterns, jj);
                    rotate1DArray(separation, nPatterns, jj);
                    nPatterns--;
                    ii--;
                }
                else if(separation[ii] < separation[jj])
                {
                    // REMOVE PATTERN FROM ARRAY
                    rotate2DArray(word1, nPatterns, ii);
                    rotate2DArray(word2, nPatterns, ii);
                    rotate1DArray(separation, nPatterns, ii);
                    nPatterns--;
                    ii--;
                }
                else 
                {
                    rotate2DArray(word1, nPatterns, jj);
                    rotate2DArray(word2, nPatterns, jj);
                    rotate1DArray(separation, nPatterns, jj);
                    nPatterns--;
                    ii--;
                }
            }
        }
    }
    return nPatterns;
}


int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns)
{
    if(nPatterns < 0)
        return 0;

    if(document[0] == '\0') // IF DOCUMENT IS EMPTY
        return 0;
    
    char docCopy[MAX_DOC_LENGTH+1];
    int docK = 0;
    for(int i = 0; document[i] != '\0'; i++) // CONVERTS DOCUMENT INTO ONLY LETTERS
        if(isalpha(document[i]) or isspace(document[i]))
        {
            docCopy[docK] = tolower(document[i]);
            docK++;  
        }
    docCopy[docK] = '\0';

    char docWords[MAX_DOC_LENGTH+1][MAX_DOC_LENGTH+1];
    int docWordsIndex = 0;

    for(int k = 0; docCopy[k] != '\0'; k++) // SPLIT DOC INTO INDIVIDUAL WORDS, CREATE ARRAY OF WORDS
    {
        if(isalpha(docCopy[k]))
        {
            // ADD SUBSTRING TO ARRAY
            int count = 0;
            while(!isspace(docCopy[k]) and docCopy[k] != '\0')
            {
                docWords[docWordsIndex][count] = docCopy[k];
                k++;
                count++;
            }
            docWords[docWordsIndex][count] = '\0';
            docWordsIndex++;
            if(docCopy[k] == '\0')
                break;
        }   
    }

    int result = 0;
    for(int c = 0; c < nPatterns; c++) // CHECKS FOR MATCHING PATTERNS IN DOCUMENT
    {
        for(int b = 0; b < docWordsIndex; b++)
        {
            if(strcmp(word1[c], docWords[b]) == 0)
            {
                for(int d = b+1; d <= b + separation[c] + 1; d++)
                {
                    if(d >= docWordsIndex) // MAKE SURE D DOES NOT GO OUT OF INDEX BOUNDS
                        break;
                    if(strcmp(word2[c], docWords[d]) == 0)
                    {
                        result += 1;
                        break;
                    }
                }
                break;
            }

            else if(strcmp(word2[c], docWords[b]) == 0)
            {
                for(int d = b+1; d <= b + separation[c] + 1; d++)
                {
                    if(d >= docWordsIndex) // MAKE SURE D DOES NOT GO OUT OF INDEX BOUNDS
                        break;
                    if(strcmp(word1[c], docWords[d]) == 0)
                    {
                        result += 1;
                        break;
                    }
                }
                break;
            }
        }
    }
    return result;
}

/*
int main() {
    
    const int nPatternsTest1 = 4;
char word1Test1[nPatternsTest1][MAX_WORD_LENGTH+1] = {
"mad", "deranged", "nefarious", "have"
};
char word2Test1[nPatternsTest1][MAX_WORD_LENGTH+1] = {
"scientist", "robot", "plot", "mad"
};
int separationTest1[nPatternsTest1] = {
1, 3, 0 ,12
};

assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 2);
//Rate works correctly

/*
assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 2);
//Document with multiple consecutive spaces

assert(rate("**** 2018 ****",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 0);
//Document with characters and numbers but no letters

assert(rate("  That plot: NEFARIOUS!",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 1);
//Document with mix of characters and letters, and uppercase letters

assert(rate("deranged deranged robot deranged robot robot",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 1);
//Repeated occurrence of patterns

assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 0);
//Document with no matching patterns

assert(rate("The nomadic unscientistics eat pie every Thursday.",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 0);
//Document with patterns embedded in words
assert(rate("deranged deranged deranged deranged deranged",
word1Test1, word2Test1, separationTest1, nPatternsTest1) == 0);
//Document with repeated word






const int nPatternsTest2 = 8;
char word1Test2[nPatternsTest2][MAX_WORD_LENGTH+1] = {
"mad", "deranged", "nEfArIoUs", "bl%ue42", "plot", "have", "mad", "mad"
};
char word2Test2[nPatternsTest2][MAX_WORD_LENGTH+1] = {
"sciENTIst", "robot", "plot", "UCLA", "nefarious", "mad", "scientist", "scientist"
};
int separationTest2[nPatternsTest2] = {
1, -2, 3, 4, 5, 6, 7, 7
};

assert(makeProper(word1Test2, word2Test2, separationTest2, nPatternsTest2) == 3);
//MakeProper works correctly
//makes all letters lowercase
//removes patterns with non-letters
//removes repeated patterns in either order
//removes one of multiple identical patterns

const int nPatternsTest3 = -4;
char word1Test3[4][MAX_WORD_LENGTH+1] = {
"mad", "deranged", "nefarious", "have"
};
char word2Test3[4][MAX_WORD_LENGTH+1] = {
"scientist", "robot", "plot", "mad"
};
int separationTest3[4] = {
1, 2, 3 ,4
};

assert(makeProper(word1Test3, word2Test3, separationTest3, nPatternsTest3) == 0);
//Negative number of patterns

/*
const int nPatternsTest4 = 4;
char word1Test4[nPatternsTest4][MAX_WORD_LENGTH+1] = {
    "mad", "", "nefarious", "have"
};
char word2Test4[nPatternsTest4][MAX_WORD_LENGTH+1] = {
"scientist", "robot", "plot", ""
};
int separationTest4[nPatternsTest4] = {
1, 2, 3 ,4
};

assert(makeProper(word1Test4, word2Test4, separationTest4, nPatternsTest4) == 2);
//empty words are removed from patterns
const int nPatternsTest5 = 4;
char word1Test5[nPatternsTest5][MAX_WORD_LENGTH+1] = {
"have", "have", "have", "have"
};
char word2Test5[nPatternsTest5][MAX_WORD_LENGTH+1] = {
"mad", "mad", "mad", "mad"
};
int separationTest5[nPatternsTest5] = {
1, 2, 3 ,4
};

assert(makeProper(word1Test5, word2Test5, separationTest5, nPatternsTest4) == 1);
//only keeps highest separation value of repeated patterns


cout << "all tests succeeded";

}
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cassert>

using namespace std;

int d[3] =                      {    1,    0,    2 };
char w1[3][MAX_WORD_LENGTH+1] = { "aa", "bb", "cc" };
char w2[3][MAX_WORD_LENGTH+1] = { "dd", "ee", "ff" };

int e[2] =                      {    3,    3 };
char x1[2][MAX_WORD_LENGTH+1] = { "aa", "cc" };
char x2[2][MAX_WORD_LENGTH+1] = { "bb", "dd" };

const int THREE_LETTERS = 26*26*26;
int dd[THREE_LETTERS];
char ww1[THREE_LETTERS][MAX_WORD_LENGTH+1];
char ww2[THREE_LETTERS][MAX_WORD_LENGTH+1];

bool eq(int c, int dist, const char wd1[], const char wd2[])
{
	return d[c] == dist  &&  strcmp(w1[c], wd1) == 0  &&
						strcmp(w2[c], wd2) == 0;
}

void testone(int n)
{
	switch (n)
	{
			         case  1: {
		assert(makeProper(w1, w2, d, 0) == 0);
			} break; case  2: {
		assert(makeProper(w1, w2, d, 1) == 1  &&
					eq(0, 1, "aa", "dd"));
			} break; case  3: {
		d[0] = -1;
		assert(makeProper(w1, w2, d, 1) == 0);
			} break; case  4: {
		d[0] = -1;
		assert(makeProper(w1, w2, d, 2) == 1  &&
					eq(0, 0, "bb", "ee"));
			} break; case  5: {
		d[1] = -1;
		assert(makeProper(w1, w2, d, 2) == 1  &&
					eq(0, 1, "aa", "dd"));
			} break; case  6: {
		d[1] = -1;
		d[2] = -1;
		assert(makeProper(w1, w2, d, 3) == 1  &&
					eq(0, 1, "aa", "dd"));
			} break; case  7: {
		d[0] = -1;
		d[1] = -1;
		assert(makeProper(w1, w2, d, 3) == 1  &&
					eq(0, 2, "cc", "ff"));
			} break; case  8: {
		d[0] = -1;
		d[1] = -1;
		d[2] = -1;
		assert(makeProper(w1, w2, d, 3) == 0);
			} break; case  9: {
		strcpy(w1[1], "");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 10: {
		strcpy(w2[1], "");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 11: {
		strcpy(w1[1], "bb@");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 12: {
		strcpy(w1[1], "bb ");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 13: {
		strcpy(w1[1], "bBBb");
		assert(makeProper(w1, w2, d, 2) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bbbb", "ee"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bbbb", "ee"))
		       )
		      );
			} break; case 14: {
		strcpy(w1[1], "bBBb");
		strcpy(w2[1], "EeEeE");
		assert(makeProper(w1, w2, d, 2) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bbbb", "eeeee"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bbbb", "eeeee"))
		       )
		      );
			} break; case 15: {
		strcpy(w2[1], "bb");
		assert(makeProper(w1, w2, d, 2) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bb", "bb"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bb", "bb"))
		       )
		      );
			} break; case 16: {
		strcpy(w2[0], "aa");
		strcpy(w1[1], "aa");
		strcpy(w2[1], "aa");
		assert(makeProper(w1, w2, d, 2) == 1  &&
					eq(0, 1, "aa", "aa")
		      );
			} break; case 17: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 18: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 1;
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 19: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 4;
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 4, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 4, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 20: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		assert(makeProper(w1, w2, d, 3) == 1  &&
					eq(0, 2, "aa", "dd")
		      );
			} break; case 21: {
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		d[1] = -1;
		assert(makeProper(w1, w2, d, 3) == 1  &&
					eq(0, 2, "aa", "dd")
		      );
			} break; case 22: {
		strcpy(w1[1], "abcdefghijklmnopqrst");
		strcpy(w2[1], "abcdefghijklmnopqrsu");
		d[0] = -1;
		assert(makeProper(w1, w2, d, 2) == 1  &&
				eq(0, 0, "abcdefghijklmnopqrst",
						"abcdefghijklmnopqrsu")
		      );
			} break; case 23: {
		strcpy(w2[0], "DD");
		strcpy(w1[1], "AA");
		strcpy(w2[1], "dD");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 24: {
		strcpy(w1[1], "dd");
		strcpy(w2[1], "aa");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 25: {
		strcpy(w1[1], "dd");
		strcpy(w2[1], "aa");
		d[1] = 1;
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       (((eq(0, 1, "aa", "dd")  ||  eq(0, 1, "dd", "aa")
			 )  &&  eq(1, 2, "cc", "ff")
			)  ||
			((eq(1, 1, "aa", "dd")  ||  eq(1, 1, "dd", "aa")
			 )  &&  eq(0, 2, "cc", "ff")
			)
		       )
		      );
			} break; case 26: {
		strcpy(w1[1], "Dd");
		strcpy(w2[1], "aA");
		assert(makeProper(w1, w2, d, 3) == 2  &&
		       ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
			(eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
		       )
		      );
			} break; case 27: {
		int dx[7] = { 1, 3, 0, 2, 1, 0, 12 };
		char w1x[7][MAX_WORD_LENGTH+1] = { "mad", "deranged",
			"NEFARIOUS", "half-witted", "robot", "plot", "have" };
		char w2x[7][MAX_WORD_LENGTH+1] = { "scientist", "robot",
			"PLOT", "assistant", "deranged", "Nefarious", "mad" };
		assert(makeProper(w1x, w2x, dx, 7) == 4);
			} break; case 28: {
		assert(rate("", x1, x2, e, 2) == 0);
			} break; case 29: {
		assert(rate(" ", x1, x2, e, 2) == 0);
			} break; case 30: {
		assert(rate("aa bb", x1, x2, e, 2) == 1);
			} break; case 31: {
		e[0] = 0;
		assert(rate("aa bb", x1, x2, e, 2) == 1);
			} break; case 32: {
		e[0] = 0;
		assert(rate("aa     bb", x1, x2, e, 2) == 1);
			} break; case 33: {
		assert(rate(" aa bb", x1, x2, e, 2) == 1);
			} break; case 34: {
		assert(rate("aa bb ", x1, x2, e, 2) == 1);
			} break; case 35: {
		assert(rate("aa bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 36: {
		assert(rate("aa bb cc dd xx", x1, x2, e, 1) == 1);
			} break; case 37: {
		assert(rate("aa xx cc bb xx dd xx", x1, x2, e, 2) == 2);
			} break; case 38: {
		assert(rate("xx dd bb cc aa xx", x1, x2, e, 2) == 2);
			} break; case 39: {
		assert(rate("aa xx xx xx bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 40: {
		assert(rate("aa xx xx xx xx bb cc dd xx", x1, x2, e, 2) == 1);
			} break; case 41: {
		e[0] = 0;
		e[1] = 0;
		assert(rate("aa xx bb cc dd xx", x1, x2, e, 2) == 1);
			} break; case 42: {
		e[0] = 1;
		e[1] = 1;
		assert(rate("aa cc bb dd xx", x1, x2, e, 2) == 2);
			} break; case 43: {
		assert(rate("aa bb aa bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 44: {
		assert(rate("aa aa bb bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 45: {
		strcpy(x2[0], "aa");
		assert(rate("aa xx xx aa", x1, x2, e, 2) == 1);
			} break; case 46: {
		strcpy(x2[0], "aa");
		assert(rate("xx aa xx", x1, x2, e, 2) == 0);
			} break; case 47: {
		assert(rate("aA bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 48: {
		assert(rate("aa @@ ## $$ %% ^^ bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 49: {
		assert(rate("aa b@@b cc dd xx", x1, x2, e, 2) == 2);
			} break; case 50: {
		assert(rate("aa b123456789012345678901234567890b cc dd xx", x1, x2, e, 2) == 2);
			} break; case 51: {
		e[0] = 0;
		assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 1);
			} break; case 52: {
		e[0] = 1;
		assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 53: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(rate("abcdefghijklmnopqrst bb cc dd xx", x1, x2, e, 2) == 2);
			} break; case 54: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(rate("abcdefghijklmnopqrstu bb cc dd xx", x1, x2, e, 2) == 1);
			} break; case 55: {
		assert(rate("aaa bb cc dd xx", x1, x2, e, 2) == 1);
			} break; case 56: {
		assert(rate("aa@bb cc dd xx", x1, x2, e, 2) == 1);
			} break; case 57: {
		assert(rate("aa bb@cc dd xx", x1, x2, e, 2) == 0);
			} break; case 58: {
		e[0] = 1000;
		assert(rate("xx aa xx", x1, x2, e, 2) == 0);
			} break; case 59: {
		strcpy(x1[0], "a");
		strcpy(x2[0], "b");
		e[0] = 123;
		char doc[250+1];
		strcpy(doc, "a ");
		for (int k = 0; k < 123; k++)
			strcpy(doc+2+2*k, "x ");
		strcpy(doc+248, "b ");
		assert(rate(doc, x1, x2, e, 2) == 1);
			} break; case 60: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = (k % 2) - 1;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(makeProper(ww1, ww2, dd, THREE_LETTERS) == THREE_LETTERS / 2);
		for (int k = 0; k < THREE_LETTERS / 2; k++)
			assert(dd[k] == 0 && strcmp(ww1[k], "a") == 0 &&
				islower(ww2[k][2]) &&
				(ww2[k][2] - 'a') % 2 == 1);
			} break; case 61: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = 0;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(rate("a aaa a iaa a pzz a zzz", ww1, ww2, dd, THREE_LETTERS) == 4);
		assert(rate("a aaaa a iaaa a pzzz a zzzz", ww1, ww2, dd, THREE_LETTERS) == 0);
			} break;
	}
}

int main()
{
    cout << "Enter a test number (1 to 61): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 61)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}