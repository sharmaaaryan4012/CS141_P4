/*
Aaryan Sharma
CS 141 - Project 4 Part 2
Spring 2023
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Contact.h"
#include "ContactList.h"

using namespace std;

void main_menu(){                                                                                  // Used to display the main menu, on which the program is based.
  cout << "********************************************" << endl
         << "Main Menu" << endl << endl
         << "Enter the letter for the desired menu option:" << endl
         << "C - Get count" << endl
         << "L - Load contacts from file" << endl
         << "S - Search contacts" << endl
         << "P - Print contacts" << endl
         << "X - Exit" << endl << endl;
}

int main() {                                                                                       // Main function of the program.
  
    ContactList CList;                                                                             // CList is an object of the ContactList type, which is used to perform actions using the member functions of the class.
    
    char usr_inp, edit_opt, phChoice, phTypeChoice;
    string file_name, target_word, print_str, s_submenu, edit_sub, email, consent, phType, phnoInput, phnoONLY;
    int index;
    vector<string>phno_vec;
    vector<int> positions_vec;
    
    main_menu();
    cin >> usr_inp;                                                                                // Takes input from the user, which is used to run the menu driven program.

    while (tolower(usr_inp) != 'x'){                                                               // While loop runs till the user input 'X'.

        switch(usr_inp){                                  
            case 'C':                                                                              // Case where the program displays the number of contacts present in the vector.                              
                cout << "There are " << CList.getCount() << " contacts" << endl;
                break;

            case 'L':                                                                              // Case where the program loads contact info from user inputted file.
                cout << "Enter a filename";
                cin >> file_name;

                print_str = CList.loadContactsFromFile(file_name);
                cout  << print_str << endl;
                break;

            case 'S':                                                                              // Case where the program searches for a target word and diaplays the matches.
                cout << "Enter a search term" << endl;
                cin >> target_word;

                positions_vec = CList.findContactsByName(target_word);                             // This particular case employs the findContactByName function of the 

                if (positions_vec.size() > 1){
                    cout << endl << "Found " << to_string(positions_vec.size()) << " results" << endl;
                }

                else{
                    cout << endl << "Found " << to_string(positions_vec.size()) << " result" << endl;
                }

                for (int i=0; i<positions_vec.size(); i++) {
                    cout << (i + 1) << ". " << (CList.getContact(positions_vec.at(i)))->getName() << endl;
                }

                cout << "Enter an option:" << endl
                     <<   "   P - Print contacts"<< endl
                     <<   "   or a Contact number to view/edit"<< endl
                     <<   "   R - Return to main menu" << endl;

                cin >> s_submenu;
                if (!isdigit(s_submenu.at(0))){                                                    // If user's input is not of the digit type, this branch runs.
                    switch (s_submenu.at(0)){
                        case 'R':
                            break;
                        case 'P':
                            CList.printContacts(positions_vec);
                            break;
                    }
                }

                else{                                                                              // In case the input is a number.
                    cout << CList.getContact(positions_vec.at((stoi(s_submenu)) - 1))->getAsString() << endl
                         << "Enter an option for contact:" << endl
                         << "A - Edit address" << endl
                         << "B - Edit date of birth" << endl
                         << "E - Edit email address" << endl
                         << "N - Edit name" << endl
                         << "P - Edit phone numbers" << endl
                         << "R - Return to main menu" << endl
                         << "D - Delete" << endl;

                    cin >> edit_opt;
                    edit_opt = toupper(edit_opt);

                    switch(edit_opt){                                                              // Switch case is used for sub menu.
                        case 'A':
                            break;

                        case 'B':
                            break;

                        case 'E':
                            index = positions_vec.at((stoi(s_submenu)) - 1);                       // This variable is used throughout the code, and is used to hold the index of the contact that needs to be edited.

                            email = (CList.getContact(index))->getEmail();
                            cout << "Current email:" << email << endl
                                 << "Enter new email or C to cancel:"<< endl;
                            cin >> edit_sub;

                            if(edit_sub != "C") {
                                (CList.getContact(index))->setEmail(edit_sub);
                                cout << "Email updated:" << endl
                                     << edit_sub << endl;
                            }
                            break;

                        case 'N':
                            break;

                        case 'R':                                                                  // Case - return to the main menu.
                            break;

                        case 'P':                                                                  // This case displays contacts that were found during the search, and provides the user with another set of features.

                            index = positions_vec.at((stoi(s_submenu)) - 1);
                            phno_vec = (CList.getContact(index))->getPhoneNumbers();              


                            if (phno_vec.size() > 1){
                                cout << endl << "Found " << to_string(phno_vec.size()) << " phone numbers" << endl;
                            }

                            else{
                                cout << endl << "Found " << to_string(phno_vec.size()) << " phone number" << endl;
                            }

                            for (int i=0; i<phno_vec.size(); i++) {
                                cout << (i + 1) << ". " << phno_vec.at(i) << endl;
                            }

                            cout << "Enter an option:" << endl                                     // Another set of features for the user.
                                 << "A - Add a phone number" << endl
                                 << "R - Return to main menu" << endl
                                 << "or list number to delete" << endl;
                            cin >> phChoice;

                            switch(toupper(phChoice)){
                                case 'A':                                                          // Case - add phone number.
                                    cout << "Enter the letter for the phone number type:" << endl
                                         << "C(ell), W(ork) or H(ome)" << endl;
                                    cin >> phTypeChoice;

                                    switch(phTypeChoice){
                                        case 'C':
                                            phType = "Cell";
                                            break;
                                        case 'W':
                                            phType = "Work";
                                            break;
                                        case 'H':
                                            phType = "Home";
                                            break;
                                    }

                                    cout << "Enter the phone number:" << endl;
                                    cin >> phnoInput;

                                    CList.getContact(index)->addPhone(phTypeChoice,phnoInput);     // Adds a phone number and its respective type to the vector.

                                    cout << "success: added number " << phnoInput << " " << phType << endl;
                                    break;

                                case 'R':                                                          // Case - return to main menu.
                                    break;


                                default:                                                           // Case - Delete specified contact.
                                    index = positions_vec.at((stoi(s_submenu)) - 1);
                                    cout << "Are you sure you want to delete phone:" << phno_vec.at( (phChoice-'0')-1) << "?" << endl
                                         << "Enter 'Y' to confirm." << endl;

                                    cin >> consent;

                                    if (toupper(consent.at(0)) == 'Y') {
                                        cout << CList.getContact(index)->deletePhone((phChoice-'0')-1) << endl;
                                    }
                                    break;
                            }

                            break;

                        case 'D':                                              
                            index = positions_vec.at((stoi(s_submenu)) - 1);
                            cout << "Are you sure you want to delete contact " << (CList.getContact(index))->getName() << "?" << endl
                                 << "Enter 'Y' to confirm." << endl;

                            cin >> consent;

                            if (toupper(consent.at(0)) == 'Y'){
                                cout << CList.deleteContact(index) << endl;
                            }
                            break;
                    }
                }



                break;

            case 'P':
                break;

            default:
                break;
        }

        main_menu();

        cin >> usr_inp;
    }

    return 0;
}