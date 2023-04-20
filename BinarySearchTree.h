// Assignment #6
// Name: Rohaan Kamaraj
// ASU Email Address: rkamara1@asu.edu
// Description: This file contains a Binary Search Tree implementations with methods to populate
// and manipulate it's data. It also contains a class for the BST nodes, which are called courses.

#include <iostream> //to use cout
#include <string> //to use strings
#include <cstdlib> //to use atoi

using namespace std;

//Course represents some course information
class Course
{
private:
    string courseName;
    int numberOfCredits;
    Course * left, * right, * parent;


public:
    //The following two functions are constructors
    Course()
    {
        courseName = "?";
        numberOfCredits = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }


    Course(string courseName1, int numberOfCredits1)
    {
        courseName = courseName1;
        numberOfCredits = numberOfCredits1;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    //The following functions are accessor functions
    Course * getLeft()
    {
        return left;
    }

    Course * getRight()
    {
        return right;
    }

    Course * getParent()
    {
        return parent;
    }

    string getCourseName()
    {
        return courseName;
    }
    int getNumberOfCredits()
    {
        return numberOfCredits;
    }


    //The following functions are mutator functions
    void setLeft(Course * other)
    {
        left = other;
    }

    void setRight(Course * other)
    {
        right = other;
    }

    void setParent(Course * other)
    {
        parent = other;
    }

    //The print method prints the courseName and numberOfCredits
    void print()
    {
        cout << "Course Name: " << courseName;
        cout << ", Credits: " << numberOfCredits << endl;
    }


};

//class BinarySearchTree will contains courses
class BinarySearchTree
{
private:
    Course * root;
    int size;

public:
    BinarySearchTree();
    ~BinarySearchTree();
    bool isEmpty();
    void inOrderTreePrint();
    void preOrderTreePrint();
    void postOrderTreePrint();
    void inOrderTreeWalk(Course *);
    void preOrderTreeWalk(Course *);
    void postOrderTreeWalk(Course *);
    Course * treeSearch(string, int);
    Course * treeMinimum();
    Course * treeMaximum();
    Course * treeSuccessor(string,int);
    Course * treePredecessor(string,int);
    bool treeInsert(string,int);
    bool rightRotate(string, int);
    bool leftRotate(string, int);
    void deleteTree(Course*, int&); // method I created to assist in deleting all nodes of the tree
};

//The constructor initialize the root to be NULL
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

//The destructor should delete all nodes in the tree
//and perform garbage collections starting from leaves (bottom-up order).
//The destructor should also print “The number of nodes deleted: X”
//where X is the number of nodes deleted
BinarySearchTree::~BinarySearchTree()
{
    if (root == NULL) {
        // nothing happens as there is nothing to be deleted
        cout << "The number of nodes deleted: 0" << endl;
    } else {
        int count = 1;
        deleteTree(root, count);
        cout << "The number of nodes deleted: " + to_string(count) << endl;
    }
}

//Checks if the tree is empty
bool BinarySearchTree::isEmpty()
{
    if (root == NULL)
        return true;
    else
        return false;
}

//prints all nodes using in-order
void BinarySearchTree::inOrderTreePrint()
{
    if (isEmpty())
        cout << "tree is empty" << endl;
    else
    {
        cout << "\n";
        inOrderTreeWalk(root);
        cout << "\n";
    }
}

//prints all nodes using pre-order
void BinarySearchTree::preOrderTreePrint()
{
    if (isEmpty())
        cout << "tree is empty" << endl;
    else
    {
        cout << "\n";
        preOrderTreeWalk(root);
        cout << "\n";
    }
}

//prints all nodes using post-order
void BinarySearchTree::postOrderTreePrint()
{
    if (isEmpty())
        cout << "tree is empty" << endl;
    else
    {
        cout << "\n";
        postOrderTreeWalk(root);
        cout << "\n";
    }
}

// treeInsert method inserts a course created with the data passed in, into the tree.
// the courses in the tree are organized in decreasing order of their number of credits
// and by alphabetical order if need be.
bool BinarySearchTree::treeInsert(string userData, int userCredits) {
    Course* newCourse = new Course(userData, userCredits);
    bool inserted = false;

    if (isEmpty()) {
        root = newCourse;
        inserted = true;
        return inserted;
    }

    Course* course = root;

    Course* course2 = root; // this will be used to track the exact location of where the node will be placed

    //this while loop will run through the tree and find the location where the node will be placed
    while (course != NULL) {
        course2 = course;
        if (userCredits < course->getNumberOfCredits()) {
            course = course->getRight();
        } else if (userCredits > course->getNumberOfCredits()) {
            course = course->getLeft();
        } else if (userCredits == course->getNumberOfCredits()) {
            if (userData < course->getCourseName()) {
                course = course->getLeft();
            } else if (userData > course->getCourseName()) {
                course = course->getRight();
            } else {
                return inserted;
            }
        }
    }

    // Actually places the course in the tree at the right location
    Course* course3 = course2; // used to specify the parent
    if (userCredits < course2->getNumberOfCredits()) {
        course2->setRight(newCourse);
        course2 = course2->getRight(); // course2 is now newCourse
        course2->setParent(course3);
    } else if (userCredits > course2->getNumberOfCredits()) {
        course2->setLeft(newCourse);
        course2 = course2->getLeft();
        course2->setParent(course3);
    } else if (userCredits == course2->getNumberOfCredits()) {
        if (userData < course2->getCourseName()) {
            course2->setLeft(newCourse);
            course2 = course2->getLeft(); // course2 is now newCourse
            course2->setParent(course3);
        } else {
            course2->setRight(newCourse);
            course2 = course2->getRight();
            course2->setParent(course3);
        }
    }
    inserted = true;
    return inserted;

}

//treeSearch takes the data passed in and tries to find the course inside the tree,
//if the course isn't there, then return NULL.
Course* BinarySearchTree::treeSearch(string userData, int userCredits) {
    // if tree is empty then return NULL
    if (isEmpty()) {
        return NULL;
    }

    Course *course = root;
    while (course != NULL) {
        // check whether current course is the one being searched for
        if (course->getCourseName() == userData && course->getNumberOfCredits() == userCredits) {
            return course;
        }
        // traverses the tree
        if (userCredits < course->getNumberOfCredits()) {
            course = course->getRight();
        } else if (userCredits > course->getNumberOfCredits()) {
            course = course->getLeft();
        } else if (userCredits == course->getNumberOfCredits()) {
            if (userData < course->getCourseName()) {
                course = course->getLeft();
            } else if (userData > course->getCourseName()) {
                course = course->getRight();
            }
        }
    }
    // if no such course is found, then NULL is returned
    return NULL;
}

//treeMinimum finds and prints the minimum value of the tree.
Course* BinarySearchTree::treeMinimum() {
    if (root == NULL) {
        return NULL;
    }
    Course* course = root;
    while (course->getLeft() != NULL) {
        course = course->getLeft(); //gets the left most node in the tree
    }

    return course;
}

//treeMaximum finds and prints the maximum value of the tree.
Course* BinarySearchTree::treeMaximum() {

    if (root == NULL) {
        return NULL;
    }
    Course* course = root;
    while (course->getRight() != NULL) {
        course = course->getRight(); //gets the right most node in the tree
    }

    return course;

}

//inOrderTreeWalk takes in the root and prints out the courses in the "inOrder" way.
void BinarySearchTree::inOrderTreeWalk(Course* course) {
    if (course == NULL) {
        // nothing will happen if the root is null
    } else {
        inOrderTreeWalk(course->getLeft()); // goes through the left part of the bst
        course->print();
        inOrderTreeWalk(course->getRight()); // goes through right part of bst
    }
}

//preOrderTreeWalk takes in the root and prints out the courses in the "preOrder" way.
void BinarySearchTree::preOrderTreeWalk(Course* course) {
    if (course == NULL) {
        // nothing will happen if the root is null
    } else {
        course->print();
        preOrderTreeWalk(course->getLeft()); // goes through left part of bst
        preOrderTreeWalk(course->getRight()); // goes through right part of bst
    }
}

//postOrderTreeWalk takes in the root and prints out the courses in the "postOrder" way.
void BinarySearchTree::postOrderTreeWalk(Course* course) {
    if (course == NULL) {
        // noting will happen if the root is null
    } else {
        postOrderTreeWalk(course->getLeft()); // goes through left part of bst
        postOrderTreeWalk(course->getRight()); // goes through right part of bst
        course->print();
    }
}

//treePredecessor takes in data for a course, finds the course in the tree,
//then finds that course's predecessor and returns it
Course* BinarySearchTree::treePredecessor(string userData, int userCredits) {

    if (root == NULL) {
        return NULL;
    }

    Course* course = treeSearch(userData, userCredits);
    // if left subtree of course is non-empty
    if (course->getLeft() != NULL) {
        course = course->getLeft();
        while (course->getRight() != NULL) {
            course = course->getRight();
        }
        return course;
    } else { // if left subtree of course is empty
        Course* course2 = course->getParent();
        while (course2 != NULL && course == course2->getLeft()) {
            course = course2;
            course2 = course2->getParent();
        }

        return course2;
    }

}

//treeSuccessor takes in data for a course, finds the course in the tree,
//then finds that course's successor and returns it
Course* BinarySearchTree::treeSuccessor(string userData, int userCredits) {

    if (root == NULL) {
        return NULL;
    }

    Course* course = treeSearch(userData, userCredits);
    // if right subtree of course is non-empty
    if (course->getRight() != NULL) {
        course = course->getRight();
        while (course->getLeft() != NULL) {
            course = course->getLeft();
        }
        return course;
    } else { // if right subtree of course is empty
        Course* course2 = course->getParent();

        while (course2 != NULL && course == course2->getRight()) {
            course = course2;
            course2 = course2->getParent();
        }
        return course2;
    }
}

//deleteTree is a helper method for the destructor that helps delete all the courses
// in the tree.
void BinarySearchTree:: deleteTree(Course* course, int& count) {
    //performs garbage collection, tracks the number of nodes deleted
    if (course->getLeft() != NULL) {
        count++;
        deleteTree(course->getLeft(), count);
    }
    if (course->getRight() != NULL) {
        count++;
        deleteTree(course->getRight(), count);
    }
    delete course;
}

//leftRotate takes in data for a course, finds the course in the tree, and then
//performs a left rotation around that course. If a left rotation is not possible,
//then false is returned.
bool BinarySearchTree::leftRotate(string userData, int userCredits) {
    Course* course = treeSearch(userData, userCredits);
    if (course == NULL) {
        return false;
    }

    Course* course2 = course->getRight();
    if (course2 == NULL) {
        return false;
    }

    course->setRight(course2->getLeft()); //course2's left subtree into course's right subtree
    if (course2->getLeft() != NULL) {
        course2->getLeft()->setParent(course);
    }
    course2->setParent(course->getParent()); //connects course2's parent to course
    if (course->getParent() == NULL) {
        root = course2;
    } else if (course == course->getParent()->getLeft()) {
        course->getParent()->setLeft(course2);
    } else {
        course->getParent()->setRight(course2);
    }

    course2->setLeft(course); //puts course on course2's left
    course->setParent(course2);
    return true;
}

//rightRotate takes in data for a course, finds the course in the tree, and then
//performs a right rotation around that course. If a right rotation is not possible,
//then false is returned.
bool BinarySearchTree::rightRotate(string userData, int userCredits) {
    Course* course = treeSearch(userData, userCredits);
    if (course == NULL) {
        return false;
    }

    Course* course2 = course->getLeft();
    if (course2 == NULL) {
        return false;
    }

    course->setLeft(course2->getRight()); //course2's right subtree into course's left subtree
    if (course2->getRight() != NULL) {
        course2->getRight()->setParent(course);
    }
    course2->setParent(course->getParent()); //connects course2's parent to course
    if (course->getParent() == NULL) {
        root = course2;
    } else if (course == course->getParent()->getRight()) {
        course->getParent()->setRight(course2);
    } else {
        course->getParent()->setLeft(course2);
    }

    course2->setRight(course); //puts course on course2's right
    course->setParent(course2);
    return true;
}