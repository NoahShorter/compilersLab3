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
using std::cout;

static unordered_set<int> FirstEXAMPLE_1 = {NUM, 'x', 'y'};
static unordered_set<int> FirstEXAMPLE_2 = {'q', END, 'b'};

bool goodFail;

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
 //   cout << "FOUND PROG\n";
    return true;
}
//*******************************************
bool FindSTMTS()
{
    bool loop = true;
    while(FindSTMT())
    {
        //cout << "Found a statement\n";
    }

 //   cout << "FOUND STMTS\n";
    return true;
}
//*******************************************
bool FindSTMT()
{
 //   cout << "IN STMT\n";
    if(PeekToken() == VAR)
    {
     //   cout << "FOUND STMT.VAR\n";
        AdvanceToken();
        if(PeekToken() != '=') { Error("="); return false; }
        AdvanceToken();
        if(!FindEXPR()) return false;
        if(PeekToken() != ';') { Error(";"); return false; }
        AdvanceToken();
        cout << "Found a statement\n";
        return true;
    }
    else if(PeekToken() == WHILE)
    {
   //     cout << "FOUND STMT.WHILE\n";
        AdvanceToken();
        if(PeekToken() != '(') { Error("("); return false; }
        AdvanceToken();
        if(!FindEXPR()) return false;
        if(PeekToken() != ')') { Error(")"); return false; }
        AdvanceToken();
        if(!FindSTMT()) return false;
        cout << "Found a statement\n";
        return true;
    }
    else if(PeekToken() == '[')
    {
        AdvanceToken();
 //       cout << "FOUND STMT.[\n";
        if(!FindSTMTS()) return false;
        if(PeekToken() != ']') { Error("]"); return false; }
        AdvanceToken();
        cout << "Found a statement\n";
        return true;
    }
    //Error("STMT");
    return false;
}
//*******************************************
bool FindEXPR()
{
    //cout << "IN EXPR\n";
    if(FindOP())
    {
     //   cout << "FOUND EXPR.OP\n";
        if(!FindEXPR()) return false;
        if(!FindEXPR()) return false;
        return true;
    }
    else if(PeekToken() == NUM)
    {
   //     cout << "FOUND EXPR.NUM\n";
        AdvanceToken();
        return true;
    }
    else if(PeekToken() == VAR)
    {
        AdvanceToken();
 //       cout << "FOUND EXPR.VAR\n";
        return true;
    }
    Error("EXPR");
    return false;
}
//*******************************************
bool FindOP()
{
    //cout << "IN OP\n";
    int token = PeekToken();
    if(token ==  '+' || 
            token == '-' || 
            token == '*' || 
            token == '/' )
    {
        AdvanceToken();
        //cout << "FOUND OP\n";
        return true;
    }
    return false;
}
//*******************************************
void ErrorResume()
{
    while(PeekToken() != ';' && PeekToken() != END)
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

