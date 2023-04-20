// Assignment #6
// Name: Rohaan Kamaraj
// ASU Email Address: rkamara1@asu.edu
// Description: This program displays a menu of choices to a user
//        and performs the chosen task. It will keep asking a user to
//        enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream> //to use cin and cout
#include <string> //to use strings
#include <cstdlib> //to use string functions
#include "BinarySearchTree.h"

using namespace std;

void printMenu();

int main()
{
    // instantiate a Binary Tree object
    BinarySearchTree * tree1 = new BinarySearchTree();

    char input1;
    bool success = false;
    string line, inputStr, courseName, numberOfCreditsStr;
    int numberOfCredits;
    Course * temp; //it will be used to hold a returned the input info

    printMenu();

    do  // will ask for user input
    {
        cout << "What action would you like to perform?\n";
        cin.get(input1);
        input1 = toupper(input1);
        cin.ignore(20, '\n'); //flush the buffer
        // matches one of the case
        switch (input1)
        {
            case 'A':   //Inorder Print
                tree1->inOrderTreePrint();
                break;
            case 'B':   //Preorder Print
                tree1->preOrderTreePrint();
                break;
            case 'C':   //Postorder Print
                tree1->postOrderTreePrint();
                break;
            case 'D':   //Tree Minimum
                temp = tree1->treeMinimum();
                if (temp == NULL)
                    cout << "tree is empty" << endl;
                else
                {
                    cout << "The first course is\n";
                    temp->print();
                    cout  << endl;
                }
                break;
            case 'E':   //Tree Maximum
                temp = tree1->treeMaximum();
                if (temp == NULL)
                    cout << "tree is empty" << endl;
                else
                {
                    cout << "The last course is\n";
                    temp->print();
                    cout << endl;
                }
                break;
            case 'F':   //Tree Predecessor
                cout << "Please enter a course name to find its predecessor:\n";
                getline(cin,courseName);

                cout << "Please enter a number of credits to find its predecessor:\n";
                getline(cin,numberOfCreditsStr);
                numberOfCredits = atoi(numberOfCreditsStr.c_str());

                temp = tree1->treePredecessor(courseName, numberOfCredits);
                if (temp == NULL)
                    cout << courseName << " with " << numberOfCredits << " credit(s) does not have any predecessor\n";
                else
                {
                    cout << "The predecessor of "
                         << courseName << " with " << numberOfCredits << " credit(s) is\n";
                    temp->print();
                    cout << endl;
                }
                break;
            case 'G':   //Tree Successor
                cout << "Please enter a course name to find its successor:\n";
                getline(cin,courseName);

                cout << "Please enter a number of credits to find its successor:\n";
                getline(cin,numberOfCreditsStr);
                numberOfCredits = atoi(numberOfCreditsStr.c_str());

                temp = tree1->treeSuccessor(courseName, numberOfCredits);
                if (temp == NULL)
                    cout << courseName << " with " << numberOfCredits << " credit(s) does not have any successor\n";
                else
                {
                    cout << "The successor of "
                         << courseName << " with " << numberOfCredits << " credit(s) is\n";
                    temp->print();
                    cout << endl;
                }
                break;
            case 'H':   //Tree Search
                cout << "Please enter a course name to search:\n";
                getline(cin,courseName);

                cout << "Please enter a number of credits to search:\n";
                getline(cin,numberOfCreditsStr);
                numberOfCredits = atoi(numberOfCreditsStr.c_str());

                temp = tree1->treeSearch(courseName, numberOfCredits);
                if (temp != NULL)
                    cout << courseName << " with " << numberOfCredits << " credit(s) found\n";
                else
                    cout << courseName << " with " << numberOfCredits << " credit(s) not found\n";
                break;
            case 'I':   //Tree Insert
                cout << "Please enter a courseName/numberOfCredits to insert:\n";
                cout << "Enter a course name\n";
                getline(cin,courseName);
                cout << "Enter its number of credits\n";
                getline(cin,numberOfCreditsStr);
                numberOfCredits = atoi(numberOfCreditsStr.c_str());

                success = tree1->treeInsert(courseName,numberOfCredits);

                if (success == true)
                {
                    cout << courseName << " with " << numberOfCredits;
                    cout << " credit(s) inserted\n";
                }
                else
                {
                    cout << courseName << " with " << numberOfCredits;
                    cout << " credit(s) not inserted\n";
                }
                break;
            case 'J':  //Right Rotation
                cout << "Please enter a courseName to right-rotate:\n";
                getline(cin,courseName);

                cout << "Please enter a numberOfCredits to right-rotate:\n";
                getline(cin,numberOfCreditsStr);
                numberOfCredits = atoi(numberOfCreditsStr.c_str());

                success = tree1->rightRotate(courseName, numberOfCredits);
                if (success == true)
                    cout << "Right Rotation around " << courseName << " with " << numberOfCredits << " credit(s) is successful\n";
                else
                {
                    cout << "Right Rotation cannot be performed around ";
                    cout << courseName << " with " << numberOfCredits << " credit(s) " << endl;
                }
                break;
            case 'K':  //Left Rotation
                cout << "Please enter a courseName to left-rotate:\n";
                getline(cin,courseName);

                cout << "Please enter a numberOfCredits to left-rotate:\n";
                getline(cin,numberOfCreditsStr);
                numberOfCredits = atoi(numberOfCreditsStr.c_str());

                success = tree1->leftRotate(courseName, numberOfCredits);
                if (success == true)
                {
                    cout << "Left Rotation around " << courseName << " with " << numberOfCredits << " credit(s) is successful\n";
                }
                else
                {
                    cout << "Left Rotation cannot be performed around ";
                    cout << courseName << " with " << numberOfCredits << " credit(s) " << endl;
                }
                break;
            case 'Q':   //Quit
                delete tree1;
                break;
            case '?':   //Display Menu
                printMenu();
                break;
            default:
                cout << "Unknown action\n";
                break;
        }
    } while (input1 != 'Q');

    return 0;
}

/** The method printMenu displays the menu to a user**/
void printMenu()
{
    cout << "Choice\t\tAction\n";
    cout << "------\t\t------\n";
    cout << "A\t\tInorder Print\n";
    cout << "B\t\tPreorder Print\n";
    cout << "C\t\tPostorder Print\n";
    cout << "D\t\tTree Minimum\n";
    cout << "E\t\tTree Maximum\n";
    cout << "F\t\tTree Predecessor\n";
    cout << "G\t\tTree Successor\n";
    cout << "H\t\tTree Search\n";
    cout << "I\t\tTree Insert\n";
    cout << "J\t\tRight Rotation\n";
    cout << "K\t\tLeft Rotation\n";
    cout << "Q\t\tQuit\n";
    cout << "?\t\tDisplay Help\n\n";
}


