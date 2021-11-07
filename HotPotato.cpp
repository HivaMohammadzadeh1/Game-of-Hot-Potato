// Lab 4 Mohammadzadeh,Hiva Thursday
// Hot Potato Game

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

class Players
{
private:
    string playerName;
    Players *next;
    int playerNumber;
    
public:
    Players();
    ~Players();
    
    void SetName(string input);
    void SetNext(Players *temp);
    void setPlayerNum(int num);
    
    string GetName() const{
        return playerName;
    }
    
    Players *GetNext() const {
        return next;
    }
    
    int getPlayerNum() {
           return playerNumber;
       }
};

void Players :: setPlayerNum(int num){
    playerNumber = num;
}

Players::Players() {

    playerName = "";
    next = nullptr;
}

Players::~Players() {
   
    playerName = "";
    next = nullptr;
    delete next;
}

void Players::SetName(string input) {
   
    playerName = input;
}

void Players::SetNext(Players *temp) {
 
    next = temp;
}


class LinkedList
{
    
private:
    Players *head;
    Players *last;
    int numberOfPlayers;
    
public:
    LinkedList();
    ~LinkedList();
    void openDataFile(int players);
    int DeletePlayer(int numberOfPasses, int numberOfPlayers);
    Players* SearchPlayer(int numberOfPasses);
    void DisplayWinner();
   
};

LinkedList::LinkedList() {
  
    head = nullptr;
    last = nullptr;
    numberOfPlayers = 0;
}

LinkedList::~LinkedList() {


    head = nullptr;
    last = nullptr;
    delete head;
    delete last;
    numberOfPlayers = 0;
}


void LinkedList::openDataFile(int length)
{
    ifstream fin;
    Players *temp = nullptr;
    string tempName = "";

    fin.open("/Users/hivamoh/Desktop/CS 136/Labs/CS 136 Lab 4 FINALL/136 lab4 file.txt");

    if (!fin)
        cout << "ERROR: Data file not found.";
    
    else {
        int num = 1;
        
        while (!fin.eof() && numberOfPlayers < length) {
            
            temp = new (nothrow) Players;
            
            if (temp == nullptr) {
                
                cout << "ERROR: No memory allocated.\n" << endl;
                delete temp;
                exit(1);
            }
            
            fin >> tempName;
            temp->SetName(tempName);
            temp->setPlayerNum(num++);
            
            if (head == nullptr) {
                
                head = temp;
                last = temp;
            }
            
            else {
                
                last->SetNext(temp);
                last = temp;
            }
            
            ++numberOfPlayers;
        }
    }
    
    last->SetNext(head);
    fin.close();
}


int LinkedList::DeletePlayer(int numberOfPasses, int numberOfPlayers) {
   
    Players *temp = nullptr;
    Players *current = nullptr;
    temp = SearchPlayer(numberOfPasses);
    current = head;

    if (temp == head)
    {
        head = head->GetNext();
        last->SetNext(head);
    }
    
    else if (temp == last)
    {
    
        while (current->GetNext() != temp)
            current = current->GetNext();
        
        last = current;
        last->SetNext(head);
    }
    
    else
    {
    
        while (current->GetNext() != temp)
            current = current->GetNext();
        
        current->SetNext((current->GetNext())->GetNext());
    }

    cout << "Player " << temp->getPlayerNum() << ": " << temp->GetName()<< " has been eliminated." << endl;
    
    --numberOfPlayers;
    delete temp;
    return numberOfPlayers;
}


Players* LinkedList::SearchPlayer(int numberOfPasses)
{
    
    Players *temp = nullptr;
    temp = head;

    int i = 0;

    while (i < numberOfPasses) {
        
        temp = temp->GetNext();
        head = head->GetNext();
        last = last->GetNext();
        i++;
    }
    
    return temp;
}

void LinkedList::DisplayWinner()
{
    cout << "\nAnd the winner is... Player " << head->getPlayerNum() << ": "<< head->GetName() << "!\n" << endl;
    
}

int main()
{
    int playAgain;
    int numberOfPlayers = 0, numberOfPasses = 0;

    cout << "Welcome to the game of Hot Potato!" << endl;

    do
    {
        LinkedList list;

        cout << "\nPlease enter the number of players: ";
        cin >> numberOfPlayers;
        cout << "Please enter the number of passes: ";
        cin >> numberOfPasses;

        if (!cin){
            cin.clear();
            cin.ignore(255, '\n');
            cout<< "\n\nERROR: Please enter the proper numbers and not letters."<< endl;
            playAgain = 1;
        }

        else if (numberOfPlayers > 10 || numberOfPlayers<2 || numberOfPasses<0) {
            cout << "\nERROR: There must be a minimum of 2 and maximum of 10 players, and there can't be less than 0 passes. Try again." << endl;
            playAgain = 1;
        }

        else {

            list.openDataFile(numberOfPlayers);

            cout << endl;
            while (numberOfPlayers > 1) {
                numberOfPlayers = list.DeletePlayer(numberOfPasses, numberOfPlayers);
            }

            list.DisplayWinner();
            cout << "\nEnter 1 to play again." << endl;
            cout << "\nPress any other key to end the game and exit." << endl;
            cin >> playAgain;
        }

    } while (playAgain == 1);
    
    system("pause");
    return 0;
}



/*
TEST DATA
Mario
Luigi
Peach
Daisy
Yoshi
Toad
Rosalina
Bowser
Wario
Waluigi
*/

/*
 Welcome to the game of Hot Potato!

 Please enter the number of players: ghgfhj
 Please enter the number of passes:

 ERROR: Please enter the proper numbers and not letters.

 Please enter the number of players: -5
 Please enter the number of passes: 0

 ERROR: There must be a minimum of 2 and maximum of 10 players, and there can't be less than 0 passes. Try again.

 Please enter the number of players: 20
 Please enter the number of passes: 0

 ERROR: There must be a minimum of 2 and maximum of 10 players, and there can't be less than 0 passes. Try again.

 Please enter the number of players: 20
 Please enter the number of passes: 3

 ERROR: There must be a minimum of 2 and maximum of 10 players, and there can't be less than 0 passes. Try again.

 Please enter the number of players: 3
 Please enter the number of passes: -6

 ERROR: There must be a minimum of 2 and maximum of 10 players, and there can't be less than 0 passes. Try again.

 Please enter the number of players: 8
 Please enter the number of passes: 3

 Player 4: Daisy has been eliminated.
 Player 8: Bowser has been eliminated.
 Player 5: Yoshi has been eliminated.
 Player 2: Luigi has been eliminated.
 Player 1: Mario has been eliminated.
 Player 3: Peach has been eliminated.
 Player 7: Rosalina has been eliminated.

 And the winner is... Player 6: Toad!


 Enter 1 to play again.

 Press any other key to end the game and exit.
 1

 Please enter the number of players: 3
 Please enter the number of passes: 6

 Player 1: Mario has been eliminated.
 Player 2: Luigi has been eliminated.

 And the winner is... Player 3: Peach!


 Enter 1 to play again.

 Press any other key to end the game and exit.
 1

 Please enter the number of players: 8
 Please enter the number of passes: 2

 Player 3: Peach has been eliminated.
 Player 6: Toad has been eliminated.
 Player 1: Mario has been eliminated.
 Player 5: Yoshi has been eliminated.
 Player 2: Luigi has been eliminated.
 Player 8: Bowser has been eliminated.
 Player 4: Daisy has been eliminated.

 And the winner is... Player 7: Rosalina!


 Enter 1 to play again.

 Press any other key to end the game and exit.
 das
 sh: pause: command not found
 Program ended with exit code: 0
 */

