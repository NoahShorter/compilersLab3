//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab3
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

#include <unordered_set>
using std::unordered_set;

static unordered_set<int> FirstEXAMPLE_1 = {NUM, 'x', 'y'};
static unordered_set<int> FirstEXAMPLE_2 = {'q', END, 'b'};

//*******************************************
static bool IsIn(unordered_set<int>& set, int value)
{
    auto found = set.find(value);
    if (found != set.end()) return true;
    return false;
}

//*******************************************
// Find a PROG non-terminal
bool FindPROG()
{
    Error("Program");
    return false;
}
/*******************************************
bool FindExample()
{
    int token = PeekToken();
    if (IsIn(FirstEXAMPLE_1, token))
    {
        if (!FindPART1()) return false;
    
        token = PeekToken();
        if (token != '+') 
        {
            Error("'+'");
            return false;
        }
        AdvanceToken();         // past '+'

        if (!FindPART2()) return false;

        return true;
    }
    else if (IsIn(FirstEXAMPLE_2, token))
    {
        if (!FindPART2()) return false;
        return true;
    }

    return false;
}
*/

