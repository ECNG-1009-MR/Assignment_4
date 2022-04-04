/*Program by Group MR
Members:
1)Nathan Ragoobar
2)Nyckel St. Louis
3)Matthias Elliot
4)Nikolai Pillai
5)Quinton Aleong
6)Rajiv Sahadeo
7)Chad Moore
8)Matthew Williams
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <algorithm>



//A class for all the functionality of the original Wordle game
class wordle
{
    //Everything here is private, because there's no need to access them from the main() function

    std::vector<std::string> dictionary;


    //A function that checks if the inputted word exists within the provided dictionary
    bool wordExists(std::string word, std::vector<std::string> dictionary)
    {
        if (std::find(dictionary.begin(), dictionary.end(), word) != dictionary.end())
        {
            return true;
        }

        else
        {
            return false;
        }

    }

    //A function that makes sure the word is only five letters long
    bool fiveLetters(std::string word)
    {
        if (word.size() > 5 || word.size() < 5)
        {
            return false;
        }

        else
        {
            return true;
        }

    }

    //A function to convert all letters in a provided string to lower-case
    void convertToLower(std::string& word)
    {
        for (int z = 0; z < word.size(); z++)
        {
            if (isupper(word[z]))
            {
                word[z] = std::tolower(word[z]);
            }
        }
    }


public:

    //Everything here is public, and can be accessed from the main() function  

    std::string wordAnswer;     //word randomly chosen to be the answer
    std::string word;           //user inputted word

    //a function that opens the dictionary text file, and pushes it into the dictionary vector
    void openLibrary(std::string dictionaryFile)
    {
        std::string fiveLetterWord;
        std::ifstream inputfile;
        inputfile.open(dictionaryFile);
        if (!inputfile.is_open())
        {
            std::cout << "Error! Dictionary not found!" << std::endl;
            exit(1);
        }
        else
        {
            while (getline(inputfile, fiveLetterWord))
            {
                dictionary.push_back(fiveLetterWord);
            }
        }
        
    }

    //a function to randomly select a word from the dictionary
    void selectWord()
    {
        int randIndex;
        std::random_device seed;        //generates a seed for the engine
        std::default_random_engine eng(seed());
        std::uniform_int_distribution <int> range(0, dictionary.size()-1);

        randIndex = range(eng);
        wordAnswer = dictionary[randIndex];
        //std::cout << "Answer: " << wordAnswer << std::endl;   //for testing purposes
    }

    //a function used to input the word
    void inputWord()
    {
        std::cout << "Word: ";
        std::cin >> word;

        convertToLower(word);


        while (!wordExists(word, dictionary) || !fiveLetters(word))
        {
            std::cout << "Error! Either input does not exist in our dictionary, or the input is not 5 letters" << std::endl;
            std::cout << "Word: ";            
            std::cin >> word;
            convertToLower(word);
            wordExists(word, dictionary);
        }
    }
        
    //Primary function of the game: checks if the letter is in the correct space or exists in the word
    void check()
    {
        std::vector<bool> usedLetter = { 0,0,0,0,0 };
        std::vector<std::string> WordStat = { "","","","","" };
        std::string CorrectPos = "\x1B[42m";            //green colour
        std::string NotInWord = "\x1B[30m\x1B[47m";     //white colour
        std::string WrongPos = "\x1B[43m";              //yellow colour


        //Checks for words to see if it's in the correct position and then assigns "CorrectPos"
        //If not in the correct position, assigns "WrongPos"
        for (int i = 0; i < word.size(); i++)
        {

            if (word[i] == wordAnswer[i])       //Checks if the word is in the correct place 
            {
                usedLetter[i] = 1;
                WordStat[i] = CorrectPos;
            }
            else
            {

                WordStat[i] = NotInWord;
            }
        }


        //Checks for words that was assigned "WrongPos" compares to each unused letter in the "wordAnswer"
        for (int i = 0; i < word.size(); i++)
        {
            //if (!usedLetter[i]) //Checks to see which letter was used already before so the comparison doesn't repeat it for the input word
            for (int j = 0; j < word.size(); j++)
            {
                if (WordStat[i] == NotInWord)
                {
                    if (!usedLetter[j])  //Checks to make sure the correct letters in the answer word doesn't repeat
                    {

                        if (word[i] == wordAnswer[j])
                        {
                            WordStat[i] = WrongPos;
                            usedLetter[j] = 1;
                        }
                    }
                }
            }
        }

        //Prints Letters
        std::cout << "\033[A" << "\33[2K";
        std::cout << "Word: ";
        for (int i = 0; i < word.size(); i++)
        {
            std::cout << WordStat[i] << word[i] << "\x1B[0m";
        }
    }

    //A function just to print ASCII art for win screen
    void winBanner()
    {
        std::cout << "\x1B[32m\n";
        std::cout <<"             ___________" << std::endl;	
        std::cout <<"            '._==_==_=_.'" << std::endl;	
        std::cout <<"            .-\\:      /-." << std::endl;	
        std::cout <<"           | (|:.     |) |     ##    ##  #######  ##     ##    ##      ## #### ##    ##  ####" << std::endl; 
        std::cout <<"            '-|:.     |-'       ##  ##  ##     ## ##     ##    ##  ##  ##  ##  ###   ##  ####" << std::endl; 
        std::cout <<"              \\::.    /          ####   ##     ## ##     ##    ##  ##  ##  ##  ####  ##  ####" << std::endl; 
        std::cout <<"               '::. .'            ##    ##     ## ##     ##    ##  ##  ##  ##  ## ## ##   ##" << std::endl; 
        std::cout <<"                 ) (              ##    ##     ## ##     ##    ##  ##  ##  ##  ##  ####" << std::endl; 
        std::cout <<"               _.' '._            ##    ##     ## ##     ##    ##  ##  ##  ##  ##   ###  ####" << std::endl; 
        std::cout <<"              `-------`           ##     #######   #######      ###  ###  #### ##    ##  ####" << std::endl; 
        std::cout << "\x1B[0m";
    }

    //A function containing the main sequence of the game
    void gameFunction()
    {
        selectWord();
        int attemptsNum = 6;    //number of attempts at guessing the word
        std::cout << "Please guess the FIVE letter word!";
        for (int i = 1; i <= attemptsNum; i++)
        {
            std::cout << "\n\nAttempt #" << i << ": " << std::endl;
            inputWord();
            check();

            if (word == wordAnswer)
            {
                winBanner();
                i = attemptsNum + 1;      //increment i so that the loop breaks without having to use a break statement
            }
        }

        if (word != wordAnswer)
        {
            std::cout << "\x1B[31m" << "\n\nYOU LOSE :(" << "\x1B[0m" << std::endl;
            std::cout << "Answer: " << wordAnswer << std::endl;
        }
    }

    //A function just used to print the title banner of the wordle version
    void banner()
    {
        std::cout <<" +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ " << std::endl;
        std::cout <<" |O| |r| |i| |g| |i| |n| |a| |l|   |W| |o| |r| |d| |l| |e| " << std::endl;
        std::cout <<" +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ " << std::endl << std::endl << std::endl;
    }

};

//A child class that inherits from the parent wordle class
class modifiedWordle : public wordle
{
public:
    
    //A function used to calculate points based of game difficulty and the attempt at which the answer was found
    void calculatePoints(int attempt, int mode)
    {
        float pointsList[6] = { 100.0, 80.0, 60.0, 40.0, 20.0, 10.0 };
        float multiplierList[3] = { 1, 1.5, 2 };
        float points = 0.0;

        for (int i = 1; i < 7; i++)
        {
            if (attempt == i) { points = pointsList[i - 1]; }
        }

         //100 points for solving in 1 attempt
         //80 points for solving in 2 attempts
         //60 points for solving in 3 attempts
         //40 points for solving in 4 attempts
         //20 points for solving in 5 attempts
         //10 points for solving in 6 attempts


        for (int i = 1; i < 4; i++)                                     //Multiplier is 1 for easy mode
        {                                                               //Multiplier is 1.5 for medium mode
            if (mode == i) { points *= multiplierList[i - 1]; }         //Multiplier is 2 for hard mode
        }

        std::cout << "Score: " << "\x1B[42m" << points << "\x1B[0m" << std::endl;

    }

    //The following printFunctions illustrate 'Compiletime Polymorphism' - 'Function overloading'
    //First printFunction takes 2 indices and prints the 2 revealed letters at their correct spots 
    void printFunction(int index1, int index2)
    {
        if (index1 > index2)
        {
            int tmp = index2;
            index2 = index1;
            index1 = tmp;
        }

        for (int i = 0; i < index1; i++)
        {
            std::cout << "_ ";
        }
        std::cout << "\x1B[42m" << wordAnswer[index1] << "\x1B[0m" << " ";
        for (int i = index1 + 1; i < index2; i++)
        {
            std::cout << "_ ";
        }
        std::cout << "\x1B[42m" << wordAnswer[index2] << "\x1B[0m" << " ";
        for (int i = index2 + 1; i < wordAnswer.size(); i++)
        {
            std::cout << "_ ";
        }
    }

    //Second printFunction takes 1 index and prints the 1 revealed letter at it's correct spots 
    void printFunction(int index)
    {
        for (int i = 0; i < index; i++)
        {
            std::cout << "_ ";
        }

        std::cout << "\x1B[42m" << wordAnswer[index] << "\x1B[0m" << " ";

        for (int i = index + 1; i < wordAnswer.size(); i++)
        {
            std::cout << "_ ";
        }
    }
   
    //Third printFunction takes no arguments, and prints empty spots for all five letters
    void printFunction()
    {
        for (int i = 0; i <  wordAnswer.size(); i++)
        {
            std::cout << "_ ";
        }
    }

    //A function used to allow user to choose between Easy, Medium or Hard difficulty 
    int chooseDifficulty()
    {
        int difficulty;
        std::cout << "Please choose difficulty by typing 1, 2 or 3:" << std::endl;
        std::cout << " \x1B[32m 1. Easy (Reveals 2 letters)" << std::endl; 
        std::cout << " \x1B[33m 2. Medium (Reveals 1 letter)" << std::endl;
        std::cout << " \x1B[31m 3. Hard (Reveals No letters) \x1B[0m" << std::endl;
        std::cout << "\nChoose: ";
        std::cin >> difficulty;
        while (difficulty > 3 || difficulty < 1)
        {
            //ensures choice is 1 or 2 or 3, and an integer
            std::cout << "Please select either 1, 2 or 3 !" << std::endl;
            std::cout << "Choose: ";
            std::cin >> difficulty;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        return difficulty;
    }

    //A function used to pick random letters to reveal depending on the difficulty level
    std::vector<int> randomIndexgenerator(int choice)
    {
        srand(time(NULL));
        std::vector<int> index;
        for (int i = 0; i < choice; i++)
        {
            index.push_back(rand() % 5);
        }
        if (index.size() > 1 && index.front() == index.back())
        {
            while (index.front() == index.back())
            {
                index.front() = rand() % 5;
            }
        }
        return index;
    }

    //Modified version of the banner function. This is 'Runtime Polymorphism' - 'Function overriding'.
    void banner()
    {
        std::cout << " +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ " << std::endl;
        std::cout << " |M| |o| |d| |i| |f| |i| |e| |d|   |W| |o| |r| |d| |l| |e| " << std::endl;
        std::cout << " +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ " << std::endl << std::endl << std::endl;
    }

    //Modified version of gameFunction(). This is 'Runtime Polymorphism' - 'Function overriding'.
    void gameFunction()
    {
        selectWord();
        int attemptsNum = 6;    //number of attempts at guessing the word
        std::vector<int> indices;
        int difficulty; 

        difficulty = chooseDifficulty();         
        
        system("CLS");
        banner();
        std::cout << "Please guess the FIVE letter word!" << std::endl;
        std::cout << "Revealed letters: \n";

        if (difficulty == 1)
        {
            indices = randomIndexgenerator(2);
            printFunction(indices[0], indices[1]);      //printFunction with 2 arguments
        }
        else if (difficulty == 2)
        {
            indices = randomIndexgenerator(1);
            printFunction(indices[0]);                  //printFunction with 1 argument
        }
        else
        {
            printFunction();                            //printFunction with no arguments
        }

        for (int i = 1; i <= attemptsNum; i++)
        {
            std::cout << "\n\nAttempt #" << i << ": " << std::endl;
            inputWord();
            check();

            if (word == wordAnswer)
            {               
                winBanner();
                calculatePoints(i, difficulty);
                i = attemptsNum + 1;      //increment i so that the loop breaks without having to use a break statement
            }
        }

        if (word != wordAnswer)
        {
            std::cout << "\x1B[31m" << "\n\nYOU LOSE :(" << "\x1B[0m" << std::endl;
            std::cout << "Answer: " << wordAnswer << std::endl;
            std::cout << "Score: " << "\x1B[41m" << 0 << "\x1B[0m" << std::endl;
        }

    }
  


};


void mainMenuBanner()
{
    std::cout << "##      ##  #######  ########  ########  ##       ########" << std::endl;
    std::cout << "##  ##  ## ##     ## ##     ## ##     ## ##       ##      " << std::endl;
    std::cout << "##  ##  ## ##     ## ##     ## ##     ## ##       ##      " << std::endl;
    std::cout << "##  ##  ## ##     ## ########  ##     ## ##       ######  " << std::endl;
    std::cout << "##  ##  ## ##     ## ##   ##   ##     ## ##       ##      " << std::endl;
    std::cout << "##  ##  ## ##     ## ##    ##  ##     ## ##       ##      " << std::endl;
    std::cout << " ###  ###   #######  ##     ## ########  ######## ########" << std::endl;

    std::cout << "                                   +-+-+ +-+-+-+-+-+ +-+-+" << std::endl;
    std::cout << "                                   |B|y| |G|r|o|u|p| |M|R|" << std::endl;
    std::cout << "                                   +-+-+ +-+-+-+-+-+ +-+-+" << std::endl << std::endl << std::endl;
}

int main()
{
    int choice;
    wordle baseGame;            //creates the object for the parent wordle class
    modifiedWordle modGame;     //creates the object for the child modifiedWordle class     

    mainMenuBanner();

    std::cout << "Please choose a game mode by typing 1 or 2:" << std::endl;
    std::cout << "1. Original Wordle game \n2. Modified Wordle game" << std::endl;
    std::cout << "\nChoose: ";
    std::cin >> choice;

    while (choice > 2 || choice < 1)
    {
        //ensures choice is 1 or 2, and an integer
        std::cout << "Please type either 1 or 2 !" << std::endl;
        std::cout << "Choose: ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }

    if (choice == 1)
    {
        system("CLS");
        baseGame.banner();
        baseGame.openLibrary("Dictionary.txt");     //pass the filename of the dictionary as an argument
        baseGame.gameFunction();
    }
    else if (choice == 2)
    {
        system("CLS");
        modGame.banner();
        modGame.openLibrary("Dictionary.txt");     //pass the filename of the dictionary as an argument
        modGame.gameFunction();
    }

    std::cout << "\n\nThank you for playing!" << std::endl;

    return 0;
}

