#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<limits>
using namespace std;
void displayhangman(string fName){
        cout<<"You Failed to save "<<fName<<" now he is being hanged "<<endl;
    	cout << "  _____  " << endl;
		cout << " |     |  " << endl;
		cout << " |     O " << endl;
		cout << " |     |  " << endl;
		cout << " |    / \\ " << endl;
		cout << " |_______   " << endl;
		cout << endl;
}
void resetGame(vector<string> &usedWords, string & sectretLetter)
{
    usedWords.clear();
    sectretLetter.clear();
}
class player
{
private:
   string name;
   string friendName;
public:
    string showFriendName();
    void setName();
    int wins = 0,lost = 0 , played = 0;
};
string player::showFriendName(){
    return friendName;
}
void player::setName(){
    cout<<"Enter Your Name "<<endl;
    getline(cin, name);
    cout<<"Enter Your Friend's Name you want to save "<<endl;
    getline(cin, friendName);
}
void greeting(){
    cout<<"----------Welcome to Hangman Game---------- "<<endl;
    cout<<"Instructions: Save your friend from being hanged by guessing the letters in the secret word.\n";
}

int main()
{
    vector<string> usedWords;
    char playAgain;
    player p1;
    const int MAX_WORDS = 50 ;
    bool guessed = false, characterGuess,completeGuess, wordAlreadyUsed = true;
    p1.setName();
    string friendName = p1.showFriendName();
    greeting();
while(true)
{
    string words[MAX_WORDS] = {"intelligence", "computer", "programming", "blockchain", "language","algorithm", "array", "function", "variable", "filehandling", "conditional", "pointer", "class", "object", "inheritance", "polymorphism", "encapsulation", "abstraction", "template", "vector", "string", "integer", "floating", "boolean","character", "optimization", "input", "output", "stream", "library", "interface", "implementation", "datatypes", "compile", "execute", "error", "exception","memory", "allocation", "deallocation", "recursion", "security", "javascript", "linked", "database", "sorting", "searching", "binary", "concatenation", "graph"
    };
    string randomLetter, secretLetter, hint1, hint2, hint3, hint4;
    int guessRemainings, h1Index, h2Index, h3Index, h4Index;
    srand(time(0));
    do
    {
        int randomIndex = rand() % 50;
        cout<<randomIndex<<endl;
        randomLetter = words[randomIndex];
    } while (find(usedWords.begin(), usedWords.end(), randomLetter) != usedWords.end());
    usedWords.push_back(randomLetter);    
    cout<<randomLetter<<endl;
    cout<<randomLetter.length()<<endl;
    if (usedWords.size() >= 50)
    {
        usedWords.clear();
    }
    
    h1Index = rand() % randomLetter.length();
    h2Index = rand() % randomLetter.length();
    while (h1Index == h2Index)
    {
        h2Index = rand() % randomLetter.length();
    }
    if(randomLetter.length() > 8 && randomLetter.length() < 11)
    {
        do
        {
            h3Index = rand() % randomLetter.length(); 
        } while (h1Index == h3Index || h2Index == h3Index);
    }
    else if (randomLetter.length() >= 11 )
    {
        do
        {
            h4Index = rand() % randomLetter.length();
        } while (h1Index == h4Index || h2Index == h4Index || h3Index == h4Index);
        
    }   
        hint1 = randomLetter[h1Index];
        hint2 = randomLetter[h2Index];
        hint3 = randomLetter[h3Index];
        hint4 = randomLetter[h4Index];
        // cout<<h1Index<<" "<<h2Index<<" "<<h3Index <<" "<<h4Index<<endl;
        // cout <<hint1<<" "<<hint2<<" "<< hint3<<" "<<hint4<<endl;
        
        cout<<"Random Letter Form string words: " << randomLetter<<endl;
        guessRemainings = randomLetter.length() - 1 ;
        for (int  i = 0; i <randomLetter.length(); i++)
        {
            secretLetter += "_";    
        } 
        secretLetter[h1Index] = randomLetter[h1Index];
        secretLetter[h2Index] = randomLetter[h2Index];
        secretLetter[h3Index] = randomLetter[h3Index];
        cout<<"The letter contains "<<secretLetter<<" alphabets"<<endl;
        while(guessRemainings > 0)
        {
            cout<<"Remaining Guesses: "<<guessRemainings<<endl;
            char userGuess;
            cout<<"Guess an alphabet "<<endl;
            cin>>userGuess;
        //   guessedLetters += userGuess;
            userGuess = tolower(userGuess);
            if(cin.fail() || cin.get() != '\n')
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Warning: Single character input only "<<endl;
                if (guessRemainings < randomLetter.length())
                {
                    guessRemainings += 1 ;
                }
            }
            else if (!isalpha(userGuess))
            {
                cout<<"Warning: Character Input Only "<<endl;
                if (guessRemainings < randomLetter.length())
                {
                    guessRemainings += 1 ;
                }
            }
            else if (isalpha(userGuess))
            {
                characterGuess = false;
                for (int i = 0; i < randomLetter.length(); i++)
                {
                    if (userGuess == randomLetter[i])
                    {
                        secretLetter.replace(i, 1, 1, userGuess);
                        characterGuess = true;                    
                        
                    }
                }
                if (!characterGuess)
                {
                    cout<<"Alphabet Not Found in letter "<<endl;               
                }
                if (randomLetter == secretLetter )
                {
                    if (guessRemainings > 0)
                    {
                        cout<<"You have guessed Letter with spare guesses"<<endl;
                    }
                    cout<<"Congratulations you have saved  "<<friendName<<" from being hanged "<<endl; 
                    p1.wins++;
                    break;
                }
            }
            guessRemainings--;
            userGuess = '\0';
            cout<<"letter Guessed so far: "<<secretLetter<<endl;
        // cout<<"Alphabets Guessed: ";
            //cout<<"\t"<<guessedLetters<<endl;
        }
        if(guessRemainings == 0)
        {
            cout<<endl<<"Your are out of Guesses "<<endl;
            cout<<"You Guessed: "<<secretLetter<<endl;
            cout<<"The Secret word is: "<<randomLetter<<endl;
            p1.lost++;
        }
        if (randomLetter != secretLetter)
            {
                guessed = false;
            }
        else
            { 
                guessed = true;
            }
        if (!guessed)
        {
            displayhangman(friendName);
        }
        cout<<endl<<"Do you Want to play again (y/n) "<<endl;
        cin>>playAgain;
        if (playAgain != 'y')
        {
            break;
        }
        else
        {
            resetGame(usedWords, secretLetter);
        }        
    } 
    cout<<"-----------Result-----------"<<endl;
    cout<<"Games Played: "<<p1.lost + p1.wins <<endl;
    cout<<"Won: "<<p1.wins<<endl;
    cout<<"Lost: "<<p1.lost<<endl;
    return 0;
}
