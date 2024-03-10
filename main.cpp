// MUSTAFA BATIN EFE - 29272
#include <iostream>
#include "cmake-build-debug/feedback.cpp"
#include <string>

using namespace std;
string get_the_feedback (string guess, int game_id);

struct node
{
    int digit;
    node * next;
};

/*Following function will check every wrong probability of guessInput
 * and will return T(True) or F(False)*/
string ValidGuess (string guessInput){
    int count = 0;
    // Check if its 3 digit
    if(guessInput.size() == 3){
        for(int m = 0; m < guessInput.size(); m++){
            // Check if its between 0-9
            char z = guessInput[m];
            if( z >= 48 && 57 >= z ){
                count++; // increment valid number
            }
        }
        // If 3 of them are passed the check test continue
        if(count == guessInput.size()){
            /*If each number is distinct*/
            if((guessInput[0] != guessInput[1]) &&
               (guessInput[0] != guessInput[2]) &&
               (guessInput[1] != guessInput[2])){
                // if numbers are between 012 -- 987
                if(stoi(guessInput) >= 12 && stoi(guessInput) <= 987){
                    return "T";
                }
            } else{
                return "F";
            }
        } else{
            return "F";
        }
    }
    return "F";
}
/* Following function will ask user again if the input is wrong */
string GuessInputCheck(string guessInput){
    // check the FIRST input in the beginning
    string validCheck = ValidGuess(guessInput);
    // If its write return immediately, else -> ask again till its true
    while(validCheck == "F"){
        cin.clear();
        cout << "Invalid guess. Enter your guess." << endl;
        cin >> guessInput;
        validCheck = ValidGuess(guessInput);
        if(validCheck == "T"){
            break;
        }
    }
    return guessInput;
}

/* Begin: code taken and updated from ptrfunc.cpp*/
node * AddInOrder(node * head, int newkey)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list
{
    node *  ptr = head;   // loop variable
    // if new node should be first, handle this case and return
    // in this case, we return address of new node since it is new head
    if (head == NULL || newkey < head->digit)
    {
        node * temp = new node;  //node to be inserted
        temp->digit = newkey;
        temp->next = head; //connect the rest
        return temp; //new head
    }

    // check node one ahead so we don't pass
    while (ptr->next != NULL && ptr->next->digit < newkey)
    {
        ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node ptr points

    //now insert new node with newkey after where ptr points to
    node * temp = new node;  //node to be inserted
    temp->digit = newkey;
    temp->next = ptr->next; //connect the rest
    ptr->next = temp;

    return head;
}
/* End: code taken and updated from ptrfunc.cpp*/

/* Begin: code taken and updated from  linkedList.cpp*/
/* Following function will try to find search value in given linked list*/
bool SearchList(node * head, int searchValue){
    while(head != nullptr){
        // If current node is equal to value we need, return true
        if(head->digit == searchValue){
            return true;
        }
        // If next one is not nullptr, go ahead
        if(head->next != nullptr) {
            head = head->next;
        } else{
            return false;
        }
    }
    return false;
}
/* End: code taken and updated from  linkedList.cpp*/

/* Begin: code taken and updated from  linkedList.cpp*/
/* Following function will find the size of the given linked lists*/
/* It will be necessary to use in EndGameCheck function*/
int GetSize(node *head)
{
    int counter=0;
    node *ptr = head;
    while (ptr != NULL)
    {
        ptr = ptr->next;
        counter++;
    }
    return counter;
}
/* End: code taken and updated from  linkedList.cpp*/

/* Begin: code taken and updated from  linkedList.cpp*/
/* Following function will remove the int given from linked list given
 * And will connect the rest of linked list back together*/
node * RemovePoss(node *head, int removeInt){
    if(head != nullptr) {
        /* If there is only one node in linked list, just delete and show NULL with head*/
        if (GetSize(head) == 1) {
            node *ptr = head;
            head = nullptr;
            delete ptr;
            return head;
        } else if (head->digit == removeInt && GetSize(head) != 1) {
            // If the node in the beginning but size of linked list is not 1
            node *temp = head;
            if (head->digit == removeInt) {
                head = head->next; // It will push to the next one as head
                delete temp;
                return head;
            }
        } else{
            // If the node going to be deleted is in the middle or in the end
            node *realHead = head; // realHead -> will not change position
            node *temp = head; // It will stay in the back
            node *temp2 = head; // It will stay in forward
            // Head will be in current
            while(head != nullptr){
                head = head->next; // push head
                temp2 = head->next; // push temp2 to head's next
                if(head->digit == removeInt){
                    // If the digit what we wanted, delete and move temp to next one
                    delete head;
                    temp->next = temp2;
                    return realHead;
                } else{
                    // If not what we wanted, then simply move temp to head;
                    // and head will be postponed again next
                    temp = head;
                }
            }

        }
    }
    return head;
}
/* End: code taken and updated from  linkedList.cpp*/

/* Begin: code taken and updated from  linkedList.cpp*/
node * FillPoss(node *possSlot, int num){
    // This function will fill all the nodes from 0 to 9 (excluding possible number)
    // This will be used if the feedback is G
    if(num != 0) {
        /* Condition that number is not zero; so we can start filling with 0 */
        node* head = new node;
        node* temp;
        possSlot = head;
        head->digit = 0; // start with 0
        for(int i = 1; i < 10; i++){
            // we need to filter because we do not know the number
            if(num != i) {
                temp = new node;
                possSlot->next = temp;
                temp->digit = i;
                possSlot = temp;
            }
        }
        temp->next = nullptr;
        possSlot = head;
        return possSlot;
    } else{
        /* Condition that number is 0 so we will start with 1*/
        node* head = new node;
        node* temp;
        possSlot = head;
        head->digit = 1; // start with 1
        for(int i = 2; i < 10; i++){
            // no need to filter number because we already know
                temp = new node;
                possSlot->next = temp;
                temp->digit = i;
                possSlot = temp;
        }
        // at last, show next as null
        possSlot = head;
        temp->next = nullptr;
        return possSlot;
    }
}
/* End: code taken and updated from  linkedList.cpp*/

/* Begin: code taken and updated from  linkedList.cpp*/
void ClearList(node *head){
    // This function will delete all the members of linked list
    node *ptr;
    while(head!= nullptr){
        ptr = head;
        head = head->next;
        delete ptr;
    }
    delete head;
}
/* End: code taken and updated from  linkedList.cpp*/

/* Begin: code taken and updated from  ptrfunc.cpp*/
// Following function will print out the Impossibles and Possibles
void DisplayList (int m, node * imposs, node * poss)
{
    cout << "Slot: " << m << endl;
    cout << "Impossibles: ";
    node * ptr = imposs;
    while (ptr != NULL)
    {
        // Print the number and move to the next node
        cout << ptr ->digit << " ";
        ptr = ptr->next;
    }
    cout << endl;

    cout << "Possibles: ";
    node * ptr2 = poss;
    while (ptr2 != NULL)
    {
        // Print the number and move to the next node
        cout << ptr2 ->digit << " ";
        ptr2 = ptr2->next;
    }
    cout << endl;
}
/* End: code taken and updated from  ptrfunc.cpp*/

/* Following function will check if the game is suitable to end */
bool EndGameCheck(node * impossible){
    // List is ordered that is why if it is not distinct;
    // number going to be either its behind or front
    node * ptr = impossible; // actual head
    node * ptr2 = impossible; // coming from behind
    int count = 0;
    while(ptr2 != nullptr){
        // While the node coming from behind not null
        ptr = ptr->next; // Move actual head
        if(ptr != nullptr){
            // And if it is not nullptr
            if(ptr->digit != ptr2->digit){
                count ++;
                // implement the count
            }
        }
        ptr2 = ptr;
    }
    // If count is 8; this means there will be 8 impossible number
    // It will not count the last element since we know it exists
    // because ptr will break the loop (No Segmentation Fault)
    if(count == 8){
        return true;
    } else {
        return false;
    }

}

/* Following function is similiar to EndGameCheck, however this will also check
 * If there is an also 1 number in possible linked list as well.*/
bool EndGameCheck2(node * impossible, node * possible){
    // List is ordered that is why if it is not distinct;
    // number going to be either its behind or front
    node * ptr = impossible; // actual head
    node * ptr2 = impossible; // coming from behind
    int count = 0;
    while(ptr2 != nullptr){
        // While the node coming from behind not null
        ptr = ptr->next;
        if(ptr != nullptr){
            if(ptr->digit != ptr2->digit){
                count ++;
                // implement the count

            }
        }
        ptr2 = ptr;
    }
    // If count is 8; this means there will be 8 impossible number
    // It will not count the last element since we know it exists
    // because ptr will break the loop (No Segmentation Fault)
    // If size of possible is 1; this means there exist only 1 element in possible
    if(count == 8 && GetSize(possible) == 1){
        return true;
    } else {
        return false;
    }

}
/* Following function will find the missing number in given linked list*/
// Reason: To print out missing element, if there exists 9 elements in impossible linked list
// Because, it will be our TRUE number
void FindMissing(node *imposs, int & missed){
    node * ptr = imposs;
    for(int q = 0; q <9; q++){
        if(ptr->digit == q){
            ptr = ptr->next;
        } else{
            missed = ptr->digit - 1;
            break;
        }
    }
    if(ptr == nullptr){
        missed =9;
    }
}

int main() {
    int gameID;
    /* Get the game ID input*/
    cout << "Please enter a game ID." << endl;
    cin >> gameID;

    /* We will create linked lists */
    /* Begin: code taken and updated from arrayOfIntegers.cpp*/
    const int size = 3;
    node* possibleMain[size];
    node* impossibleMain[size];
    for (int i = 0; i < 3; i++) {
        possibleMain[i] = nullptr;
        impossibleMain[i] = nullptr;
    }
    /* End: code taken and updated from arrayOfInteger.cpp */
    /* Linked lists are created */
    bool gameContinue = true; // we will make this false, when we guess right number
    while(gameContinue) {
        string guessInput;
        cout << "Enter your guess." << endl;
        cin >> guessInput;
        /* Check if its 3 distinct (different) integer, if fails keep asking*/
        guessInput = GuessInputCheck(guessInput);
        /* Now, guess input is valid; we will get feedback*/
        string feedbackString = get_the_feedback(guessInput, gameID);

        for(int a = 0; a < feedbackString.size(); a++){
            // It will travel 3 times basically
            int number = int(guessInput[a] - 48); // we will convert char to int
            if(feedbackString[a] == 'R'){
                // number(n) should be inserted to all of to the impossible list
                if(SearchList(impossibleMain[0] , number) == false){
                    impossibleMain[0] = AddInOrder(impossibleMain[0], number);
                }
                if(SearchList(impossibleMain[1] , number) == false){
                    impossibleMain[1] = AddInOrder(impossibleMain[1], number);
                }
                if(SearchList(impossibleMain[2] , number) == false){
                    impossibleMain[2] = AddInOrder(impossibleMain[2], number);
                }

            } else if (feedbackString[a] == 'Y'){
                // number(n) should be removed from the possible linked list of slot t, if exists
                if(SearchList(possibleMain[a] , number) == true){
                    possibleMain[a] = RemovePoss(possibleMain[a],number);
                }
                // number(n) inserted to the impossible linked list of slot t
                if(SearchList(impossibleMain[a] , number) == false){
                    impossibleMain[a] = AddInOrder(impossibleMain[a], number);
                }
                // inserted to the possible linked lists of the other two slots
                // if it wasn't in the corresponding slot's impossible linked list
                if(a == 0){
                    // The reason that there are lots of element in the if conditions are:::::
                    // 1) Search list for impossibleMain to make sure the number is not in impossible
                    // 2) Search list for possibleMain to make sure the number is not in possible
                    // 3) To make sure game did not end (impossible list is not full)
                    // 4) To make sure impossible list is not full and also there is not only 1 element in possible
                    if(SearchList(impossibleMain[1],number)==false &&SearchList(possibleMain[1],number)==false && EndGameCheck2(impossibleMain[1],possibleMain[1]) == false){
                        possibleMain[1] = AddInOrder(possibleMain[1],number);
                    }
                    if(SearchList(impossibleMain[2],number)==false && SearchList(possibleMain[2],number)==false &&  EndGameCheck2(impossibleMain[2], possibleMain[2]) == false){
                        possibleMain[2] = AddInOrder(possibleMain[2],number);
                    }
                } else if(a == 1){
                    if( SearchList(impossibleMain[0],number)==false && SearchList(possibleMain[0],number)==false && EndGameCheck2(impossibleMain[0], possibleMain[0]) == false ){
                        possibleMain[0] = AddInOrder(possibleMain[0],number);
                    }
                    if(SearchList(impossibleMain[2],number)==false && SearchList(possibleMain[2],number)==false &&  EndGameCheck2(impossibleMain[2], possibleMain[2]) == false){
                        possibleMain[2] = AddInOrder(possibleMain[2],number);
                    }
                } else if(a == 2){
                    if(SearchList(impossibleMain[0],number)==false &&SearchList(possibleMain[0],number)==false &&  EndGameCheck2(impossibleMain[0],possibleMain[0]) == false){
                        possibleMain[0] = AddInOrder(possibleMain[0],number);
                    }
                    if(SearchList(impossibleMain[1],number)==false && SearchList(possibleMain[1],number)==false &&  EndGameCheck2(impossibleMain[1], possibleMain[1]) == false){
                        possibleMain[1] = AddInOrder(possibleMain[1],number);
                    }
                }
            } else if(feedbackString[a] == 'G'){
                // number(n) should be inserted to the possible linked list of slot t
                if(SearchList(possibleMain[a],number)==false){
                    possibleMain[a] = AddInOrder(possibleMain[a],number);
                }

                // number(n) should be inserted to the impossible linked lists of the other two slots (other than t)
                if(a==0){
                    if(SearchList(impossibleMain[1],number)==false){
                        impossibleMain[1] = AddInOrder(impossibleMain[1], number);
                    }
                    if(SearchList(impossibleMain[2],number)==false){
                        impossibleMain[2] = AddInOrder(impossibleMain[2], number);
                    }
                } else if(a==1){
                    if(SearchList(impossibleMain[0],number)==false){
                        impossibleMain[0] = AddInOrder(impossibleMain[0], number);
                    }
                    if(SearchList(impossibleMain[2],number)==false){
                        impossibleMain[2] = AddInOrder(impossibleMain[2], number);
                    }

                } else if(a==2){
                    if(SearchList(impossibleMain[0],number)==false){
                        impossibleMain[0] = AddInOrder(impossibleMain[0], number);
                    }
                    if(SearchList(impossibleMain[1],number)==false){
                        impossibleMain[1] = AddInOrder(impossibleMain[1], number);
                    }
                }
                // number(n) should be removed from the possible lists of other two slot, if any
                if(a==0){
                    if(SearchList(possibleMain[1],number) == true){
                        possibleMain[1] = RemovePoss(possibleMain[1],number);
                    }
                    if(SearchList(possibleMain[2],number) == true){
                        possibleMain[2] = RemovePoss(possibleMain[2],number);
                    }
                } else if(a==1){
                    if(SearchList(possibleMain[0],number) == true){
                        possibleMain[0] = RemovePoss(possibleMain[0],number);
                    }
                    if(SearchList(possibleMain[2],number) == true){
                        possibleMain[2] = RemovePoss(possibleMain[2],number);
                    }
                } else if(a==2){
                    if(SearchList(possibleMain[0],number) == true){
                        possibleMain[0] = RemovePoss(possibleMain[0],number);
                    }
                    if(SearchList(possibleMain[1],number) == true){
                        possibleMain[1] = RemovePoss(possibleMain[1],number);
                    }
                }
                // all digits except n should be inserted to impossible
                ClearList(impossibleMain[a]); // clear the impossible list
                impossibleMain[a] = FillPoss(impossibleMain[a],number); // fill 0 to 9 except number
                // Following will remove any other digits except n from the possible list
                node * temp = possibleMain[a];
                node * temp2 = nullptr;

                while(temp != nullptr){
                    if(temp->digit != number){
                        if(temp2 == nullptr){
                            possibleMain[a] = temp->next;
                        } else{
                            temp2->next = temp->next;
                        }
                        node* temp3 = temp;
                        temp = temp->next;
                        delete temp3;
                    } else{
                        temp2 = temp;
                        temp = temp->next;
                    }
                }

            }
        }
        cout << "Linked lists:" << endl;
        DisplayList(1, impossibleMain[0],possibleMain[0]);
        cout << endl;
        DisplayList(2, impossibleMain[1],possibleMain[1]);
        cout << endl;
        DisplayList(3, impossibleMain[2],possibleMain[2]);
        cout << endl;

        if(EndGameCheck(impossibleMain[0]) &&
                EndGameCheck(impossibleMain[1]) &&
                EndGameCheck(impossibleMain[2])){
            int missed0, missed1, missed2;
            FindMissing(impossibleMain[0],missed0);
            FindMissing(impossibleMain[1],missed1);
            FindMissing(impossibleMain[2],missed2);
            cout<< "The secret number is: "<< missed0 << missed1 <<missed2 << endl;
            cout << "Congrats! Now, deleting the lists...";
            ClearList(impossibleMain[0]);
            ClearList(impossibleMain[1]);
            ClearList(impossibleMain[2]);
            impossibleMain[0] = nullptr;
            impossibleMain[1] = nullptr;
            impossibleMain[2] = nullptr;
            ClearList(possibleMain[0]);
            ClearList(possibleMain[1]);
            ClearList(possibleMain[2]);
            possibleMain[0] = nullptr;
            possibleMain[1] = nullptr;
            possibleMain[2] = nullptr;
            gameContinue = false;
        }
    }
    return 0;
}
