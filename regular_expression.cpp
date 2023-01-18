/*
Matching an Input String with Given Regular Expression
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string inexpr;
    string input;
    // regex expr("(\\+|-)?[[:alpha:]]+[[:digit:]]*");
    cout << "Enter an Expression: ";
    cin >> inexpr;
    cout << "Enter an Input: ";
    cin >> input;
    regex expr(inexpr);
    if (regex_match(input, expr))
        cout << "Input Matched" << endl;
    else
    {
        cout << "Invalid input" << endl;
    }
    return 0;
}
