//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab3
//
// Author: Phil Howard 
// phil.howard@oit.edu
// Edited by: Noah Shorter
// noah.shorter@oit.edu
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

#include <unordered_set>
using std::unordered_set;
using std::cout;

static unordered_set<int> FirstEXAMPLE_1 = {NUM, 'x', 'y'};
static unordered_set<int> FirstEXAMPLE_2 = {'q', END, 'b'};


//*******************************************
//static bool IsIn(unordered_set<int>& set, int value)
//{
//    auto found = set.find(value);
//    if (found != set.end()) return true;
//    return false;
//}

//*******************************************
// Find a PROG non-terminal
//*******************************************
bool FindPROG()
{
    if(!FindSTMTS()) return false;
    if(PeekToken() != END) { Error("end"); return false; }
    AdvanceToken();
    return true;
}
//*******************************************
// Find a series of statements
//*******************************************
bool FindSTMTS()
{
    bool cont = true;
    while(cont)
    {
        bool found = FindSTMT();

        // If there was a statement, continue
        if(found);

        // Is the file point to the END variable? if so, stop looking.
        else if(PeekToken() == END)
            cont = false;

        // Are you at the end of a [STMTS] If so, stop looking.
        else if(PeekToken() == ']')
            cont = false;

        // Are you at the EOF, if so stop looking.
        else if(PeekToken() == 0)
            cont = false;

        // If your not at the end of the program or [STMTS] then error occured.
        else
            ErrorResume();
    }

    return true;
}
//*******************************************
bool FindSTMT()
{
    // Look for a VAR = EXPR;
    if(PeekToken() == VAR)
    {
        AdvanceToken();
        if(PeekToken() != '=') { Error("'='"); return false; }
        AdvanceToken();
        if(!FindEXPR()) return false;
        if(PeekToken() != ';') { Error("';'"); return false; }
        AdvanceToken();
        cout << "Found a statement\n";
        return true;
    }
    // Look for a while (EXPR) STMT
    else if(PeekToken() == WHILE)
    {
        AdvanceToken();
        if(PeekToken() != '(') { Error("'('"); return false; }
        AdvanceToken();
        if(!FindEXPR()) return false;
        if(PeekToken() != ')') { Error("')'"); return false; }
        AdvanceToken();
        if(!FindSTMT()) return false;
        cout << "Found a statement\n";
        return true;
    }
    // Look for a [STMTS]
    else if(PeekToken() == '[')
    {
        AdvanceToken();
        if(!FindSTMTS()) return false;
        if(PeekToken() != ']') { Error("']'"); return false; }
        AdvanceToken();
        cout << "Found a statement\n";
        return true;
    }
    // If your not at the function END, EOF, or end of [STMTS] then show error.
    if(PeekToken() != END && PeekToken() != 0 && PeekToken() != ']')
        Error("STMT");

    return false;
}
//*******************************************
// Find an EXPR
//*******************************************
bool FindEXPR()
{
    // Check for NUM
    if(PeekToken() == NUM)
    {
        AdvanceToken();
        return true;
    }

    // Check for VAR
    else if(PeekToken() == VAR)
    {
        AdvanceToken();
        return true;
    }

    //Check for OP EXPR EXPR
    else if(FindOP())
    {
        if(!FindEXPR()) return false;
        if(!FindEXPR()) return false;
        return true;
    }

    // If EXPR not found, show error.
    Error("EXPR");
    return false;
}
//*******************************************
// Look for a +, -, *, /
//*******************************************
bool FindOP()
{
    int token = PeekToken();
    if(token ==  '+' || 
            token == '-' || 
            token == '*' || 
            token == '/' )
    {
        AdvanceToken();
        return true;
    }
    return false;
}
//*******************************************
// If error found, continue until you find,
// ; or ] or END token
//*******************************************
void ErrorResume()
{
    while(PeekToken() != ';' && PeekToken() != END && PeekToken() != ']')
        AdvanceToken();
    if(PeekToken() == ';')
        AdvanceToken();
}
/********************************************
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
*******************************************/

