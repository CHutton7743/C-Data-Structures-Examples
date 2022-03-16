/////////////////////////////////////////
//// Name: Codey Hutton              ////
//// Class: CS 300 Data Structures   ////
//// Professor: Z Li                 ////
//// Assignment: SLLString           ////
//// Date: 10/17/2021                ////
/////////////////////////////////////////

// Task: 
// • create SLLString class and provide implementations for all functions given in the assignment description.  IN PROGRESS:

// • use singly linked list to implement string as a linked list of characters.

// • overload << operator so that cout<< works with SLLString objects.

// • apply big three rule by implementing copy constructor, assignment operator and destructor.
 
#ifndef SLLSTRING_

#include <iostream>
#include <list>
#include <string>

using namespace std;

class SLLString {
    private:
        struct Node {
            char data;
            Node* next;
        };
        // iterator pointer
        Node* lead;
        // points to the head node and rarely if ever moves
        Node* head;
        // trailes behind the iterator. Used in functions that modify nodes.
        Node* previousNode;

    public:
        // this method is the default constructor for SLLString class.
        SLLString(){ 
            // assign a head node, assign all pointers to point to the head node.
            head = new Node();
            head->next = NULL;
            lead = head;
            previousNode = head; 
        }

        // this method is the destructor for the SLLString class.
        ~SLLString(){
            // reset pointers to the head node
            lead = head;
            previousNode = lead;
            
            // lead moves forward. Previous node gets deleted. previous points to lead. Repeat until at the last node.
            while (lead-> next != NULL){
                lead = lead->next;
                delete previousNode;
                previousNode = lead;
            }
            // the last node remains, delete it.
            delete lead;
            head = NULL;
            previousNode = NULL;
            lead = NULL;
        }

        // this method copies the constructor taking another SLLString.
        SLLString(const string& other){
            head = new Node();
            head->data = other[0];
            head->next = NULL;
            lead = head;
            previousNode = head;

            for (int i = 1; i < other.size(); i++){
                lead = new Node();
                lead->data = (other[i]);
                lead->next = NULL;
                previousNode->next = lead;
                previousNode = lead;    
            }
        }

        //copy constructor taking another SLLString 
        SLLString(const SLLString& other) {
            head = new Node();
            Node* temp = other.head;
            head->data = temp->data;
            head->next = NULL;
            temp = temp->next;
            lead = head;
            previousNode = head;

            while(temp != NULL) {
                lead = new Node;
                lead->data = temp->data;
                lead->next = NULL;
                previousNode->next = lead;
                previousNode = lead;
                temp = temp->next;
            }  
        }
        
        // this method overloads the << operator 
        friend ostream& operator<<(ostream& os, const SLLString& input) {
            Node* lead = input.head;

            while (lead != NULL) {
                os << lead->data;
                lead = lead->next;
            }
            return os;
        }

        // this method finds the length of a string.
        int length() {
            lead = head;
            int count = 0;
            while (lead->next != NULL) {
                count++;
                lead = lead->next;
            }
           if (lead->next == NULL) {
               count++;
           }
           lead = head;
           previousNode = head;
           return count;
         }
 
        // this method will find the char at the index of n.
        char& operator[](const int n){
            lead = head;
            for (int i = 0; i < n; i++){
                lead = lead->next;
            }
            return lead->data;
        }

        void print() {
            lead = head;
            while(lead->next != NULL)
            {
                cout << lead->data << "->";
                lead = lead->next;
            }
            cout << lead->data << "-> NULL" << endl;
    }

        // concatenation of 2 strings.
        void operator+= (const SLLString& rightHand){
            lead = head;
            previousNode = head;
            Node* temp = rightHand.head;

            while (lead->next != NULL){
                lead = lead->next;
            }
            previousNode = lead;

            while(temp->next != NULL){
                lead = new Node;
                lead->data = temp->data;
                lead->next = NULL;
                previousNode->next = lead;
                previousNode = lead;
                temp = temp->next;  
            }
            previousNode = lead;
            lead = new Node;
            lead->data = temp->data;
            previousNode->next = lead;
            lead->next = NULL;
        }
        // this method overloads the = operator.
        void operator=(const SLLString& rightHand) {
            lead = head;
            previousNode = head;
            Node* temp = rightHand.head;
            head->data = temp->data;
            head->next = NULL;
            temp = temp->next;

            while(temp != NULL) {
                lead = new Node;
                lead->data = temp->data;
                lead->next = NULL;
                previousNode->next = lead;
                previousNode = lead;
                temp = temp->next;
            }
        }

        // this method finds the index of the first occurrence of substring in the current string. Returns -1 if not found.
        int findSubstring(const string& substring){
            int substringStart;
            int count = 0;
            int length = this->length();

            // reset the pointers to the head node.
            lead = head;
            previousNode = head;
            // iterate through the list until a match between substring and this object is found.
            for (int i = 0; i < length - substring.size(); i++) {
                if (substring[0] == lead->data) {
                    previousNode = lead->next;
                    int count = 1;
                    substringStart = i;
                    lead = lead->next;

                    // once a match is found iterate through the rest of the SLLString checking that it matches. If it fails count == 0 
                    // reset and fall back to the previous for loop. Continue looking for matches until the end of the string.
                    while (substring[count] == lead->data){
                       lead = lead->next;
                       count++;
                       if(count == substring.size()) {
                           return substringStart;
                       }
                    }
                    count = 0;
                }
                lead = lead->next;
            }
            // if no matching substrings are found return -1.
            return -1;
        }
  
        // this method will erase all occurrences of char c from the current string.
        void erase(char c){
            lead = head;
            previousNode = head;
            Node* temp;
            // if the char c == the head node perform the following to delete the head node and move it over while keeping track.
            if (lead->data == c) {
                temp = lead;
                lead = lead->next;
                previousNode = head;
                previousNode->next = lead;
                delete temp;
            }

            // for anything after the head node the following while loops and if else statements will erase nodes whose data == c.
            while (lead->next != NULL) {
                if (lead->data == c) {
                    temp = lead;
                    lead = lead->next;
                    previousNode->next = lead;
                    delete temp;
                } else {
                    previousNode = lead;
                    lead = lead->next;
                }
            }
            if (lead->data == c) {
                previousNode->next = NULL;
            }
        }
};
#endif