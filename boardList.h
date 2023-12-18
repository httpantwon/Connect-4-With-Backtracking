//
// Created by Antwon Walls on 11/29/23.
//

#ifndef PROGRAM6_BOARDLIST_H
#define PROGRAM6_BOARDLIST_H

using namespace std;

/**creates a Node consisting of data and a reference
 * to the next node in the linked list chain**/
struct Node {
private:
    /**because the board is a 2D array, it's best to create
     * a double pointer. The first pointer helps to access each of
     * the individual arrays (6 rows). The second pointer helps to
     * access each element (Xs, Os, empty spaces) within the 7 columns**/
    char** data;

    ///a reference (or address) to the next node in the list
    Node* link;
public:
    Node(char board[6][7]);
    char** getData();
    Node* getLink();
    void setLink(Node* head);
};

/**Defines the parameterized constructor of a Node struct.
 * copies the board's contents to the node's data**/
Node::Node(char board[6][7]) {
    /**creates an array of character pointers for each row**/
    data = new char*[6];
    for (int row = 0; row < 6; row++) {
        /**creates an array of the character elements (Xs, Os, -s)
         * for the array of character pointers**/
        data[row] = new char[7];
    }

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            data[row][col] = board[row][col];
        }
    }
    /**sets link to nullptr to make sure the program
     * doesn't cause an error. By default, the should be empty unless
     * it's NOT the last item in the list**/
     link = nullptr;
}

/**Gets the information at each node, which is
 * the contents of the latest updated board
 * (Xs, Os, empty spaces)**/
char** Node::getData() {
    return data;
}

/**A way of accessing the reference (or address) to
 * the next node in the list because link is a
 * private data member**/
Node* Node::getLink() {
    return link;
}

/**After each new move, updates the head to point to the
 * most recent link (reference) containing that move**/
void Node::setLink(Node* head) {
    link = head;
}

/**Creates a class for the chain of boards in the linked list
 * with functions to keep track of, modify, and output them.**/
class boardList {
private:
    Node* head;

public:
    boardList();
    Node* getHead();
    void add(char board[6][7]);
    void undo(char board[6][7]);
    void print(Node* node);
};

/**Default constructor for the chain of board versions in the links
 * of the linked list. Head of the linked list is initially
 * empty until new links are added to it
 * (hence the add function later on)**/
boardList::boardList() {
    head = nullptr;
}

///gets the starting point (first node) of the linked list
Node* boardList::getHead() {
    return head;
}

/**function that adds a new node for each new move a player makes
 * to internally keep track of the plays made**/
void boardList::add(char board[6][7]) {
    Node* newNode = new Node(board);
    newNode->setLink(head);

    /**Head will always update to point to the most recently added node
     * (aka most recently played move)**/
    head = newNode;
}

/**removes the node containing the most recent played move
 * (last node) from the linked list**/
void boardList::undo(char board[6][7]) {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            board[row][col] = head->getData()[row][col];
        }
    }
    head = head->getLink();
}

/**recursive function that prints all of the boards
 * that occurred after each of the moves have been made
 * (up until the end of the linked list)**/
void boardList::print(Node* node) {
    if (node->getLink() != nullptr) {
        print(node->getLink());
    }

    /**This for loop just prints out each column index (0 1 2 3 4 5 6)**/
    for (int i = 0; i < 7; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            cout << node->getData()[row][col] << " ";
        }
        cout << endl;
    }
}

#endif //PROGRAM6_BOARDLIST_H