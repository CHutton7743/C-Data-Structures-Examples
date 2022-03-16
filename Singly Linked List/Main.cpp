/////////////////////////////////////////
//// Name: Codey Hutton              ////
//// Class: CS 300 Data Structures   ////
//// Professor: Z Li                 ////
//// Assignment: SLLString           ////
//// Date: 10/17/2021                ////
/////////////////////////////////////////

#include "SLLString.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {
    SLLString str("Hello World!");
    
    SLLString newStr;

    newStr = str;
    newStr += SLLString(" CS@BC");
    newStr[6] = 'W';

    cout << newStr << endl; // Hello World! CS@BC
    cout << newStr.length() << endl; // 18

    int loc = newStr.findSubstring("World");    

    cout << loc << endl; // 6

    newStr.erase('l'); // erase  the letter l.

    cout << newStr << endl; // Heo Word! CS@BC

    newStr.erase('C');
    
    cout << newStr << endl; // Heo word! S@B 
   
}