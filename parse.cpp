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
bool FindSTMTS()
{
    bool cont = true;
    while(cont)
    {
        bool found = FindSTMT();
        if(found);
        else if(PeekToken() == END)
            cont = false;
        else if(PeekToken() == ']')
        {
            cont = false;
        }
        else
        {
            ErrorResume();
            cont = true;
        }
    }

    return true;
}
//*******************************************
bool FindSTMT()
{
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
    else if(PeekToken() == '[')
    {
        AdvanceToken();
        if(!FindSTMTS()) return false;
        if(PeekToken() != ']') { Error("']'"); return false; }
        AdvanceToken();
        cout << "Found a statement\n";
        return true;
    }
    if(PeekToken() != END && PeekToken() != 0 && PeekToken() != ']')
        Error("STMT");
    return false;
}
//*******************************************
bool FindEXPR()
{
    if(PeekToken() == NUM)
    {
        AdvanceToken();
        return true;
    }
    else if(PeekToken() == VAR)
    {
        AdvanceToken();
        return true;
    }
    else if(FindOP())
    {
        if(!FindEXPR()) return false;
        if(!FindEXPR()) return false;
        return true;
    }
    Error("EXPR");
    return false;
}
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

