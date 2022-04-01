#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <algorithm>
#include <map>


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

    //A function that makes sure the word is only three letters long
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

    //A function that checks how many times a letter occurs in a word
    int multipleLetters(std::string word, char letter)
    {
        int letterFreq = std::count(word.begin(), word.end(), letter);
        return letterFreq;
    }


    //A function that checks if the letter exists in the file
    bool letterExists(std::string word, char letter)
    {
        if (word.find(letter) != std::string::npos)
            return true;
        else
            return false;
    }

public:

    //Everything here is public, and can be accessed from the main() function  

    std::string wordAnswer;     //word randomly chosen to be the answer
    std::string word;           //user inputted word
    int currectCount = 0;       //used to check if all letters are correct (when currectCount=5)

    //a function that opens the dictionary text file, and pushes it into the dictionary vector
    void openLibrary(std::string dictionaryFile)
    {
        std::string fiveLetterWord;
        std::ifstream inputfile;
        inputfile.open(dictionaryFile);
        while (getline(inputfile, fiveLetterWord))
        {
            dictionary.push_back(fiveLetterWord);
        }
    }

    //a function to randomly select a word from the dictionary
    void selectWord()
    {
        int randIndex;
        std::random_device seed;        //generates a seed for the engine
        std::default_random_engine eng(seed());
        std::uniform_int_distribution <int> range(0, dictionary.size());

        randIndex = range(eng);
        wordAnswer = "tools";//dictionary[randIndex];
        std::cout << "Answer: " << wordAnswer << std::endl;
    }

    //a function used to input the word
    void inputWord()
    {
        std::cout << "Input: ";
        std::cin >> word;

        //Loop coverts all capital letters to common
        for (int z = 0; z < word.size(); z++)
        {
            if (isupper(word[z]))
            {
                word[z] = std::tolower(word[z]);
            }
        }

        
        while (!wordExists(word, dictionary) || !fiveLetters(word))
        {
            std::cout << "Error! Either input does not exist in our dictionary, or the input is not 5 letters" << std::endl;
            std::cout << "Input: ";
            std::cin >> word;         
            wordExists(word, dictionary);
        }
    }

    //Primary function of the game: checks if the letter is in the correct space or exists in the word
    void check()
    {  
        std::vector<bool> usedLetter = { 0,0,0,0,0};
        std::vector<std::string> WordStat = {"","","","",""};
        std::string CorrectPos = "\x1B[42m";  //green colour
        std::string NotInWord = "\x1B[0m";      //white colour
        std::string WrongPos = "\x1B[43m";      //yellow colour

        for (int i = 0; i < word.size(); i++)
        {

            if (word[i] == wordAnswer[i])
            {
               // std::cout << "\x1B[42m" << word[i] << "\x1B[0m";                //green: correct letter and correct position
                usedLetter[i] = 1;
                WordStat[i] = CorrectPos;
            }
            else
            {
                //std::cout << "\x1B[47m" << "\x1B[30m" << word[i] << "\x1B[0m";  //grey: letter does not exist in word 
                WordStat[i] = NotInWord;
            }
        }


        //--------------- MAP -------------- // Map could be deleted


        //std::map<char, int> ansLetters;
        std::map<char, int> inputLetters;

       /* for (int i = 0; i < wordAnswer.size(); i++)
        {
            ansLetters.insert(std::pair<char, int>(wordAnswer[i], multipleLetters(wordAnswer, wordAnswer[i])));
        }*/

        for (int i = 0; i < word.size(); i++)
        {
            if (!usedLetter[i]) {
                inputLetters.insert(std::pair<char, int>(word[i], multipleLetters(word, word[i])));
            }            
        }

        // ---------------------------------------------------------

        for (int i = 0; i < word.size(); i++)
        {
            //if (!usedLetter[i]) //Checks to see which letter was used already before so the comparsion doesn't repeat it for the input word
            for (int j = 0; j < word.size(); j++)
            {
                if (WordStat[i] == NotInWord)
                {
                    if (!usedLetter[j])  //Checks to make sure the correct letters in the answer word doesn't repeat
                    {
                        
                        /*if (word[i] == wordAnswer[j] && multipleLetters(word, word[i])  > inputLetters[word[i]])
                        {
                            WordStat[i] = WrongPos;
                            usedLetter[j] = 1;
                        }*/
                        /*if (word[i] == wordAnswer[j] && multipleLetters(word, word[i]) > 1)
                        {
                            WordStat[i] = WrongPos;
                            usedLetter[j] = 1;
                        }*/
                      
                        if (word[i] == wordAnswer[j])
                        {
                            WordStat[i] = WrongPos;
                            usedLetter[j] = 1;
                        }
                    }                    
                }             

            }

        }

        /*for (int i = 0; i < word.size(); i++) {

           if (usedLetter[i] = 0 && multipleLetters(wordAnswer, word[i]) > 1)
           {
                WordStat[i] = WrongPos;

           }
        
        }*/

        for (int i = 0; i < word.size(); i++)
        {
            std::cout << WordStat[i] << word[i] << "\x1B[0m";

        }
    }


};



int main()
{
    wordle game;            //creates the object for the wordle class
    int attemptsNum = 5;    //number of attempts at guessing the word

    game.openLibrary("TestDictionary.txt");     //pass the filename of the dictionary as an argument
    game.selectWord();

    for (int i = 1; i <= attemptsNum; i++)
    {
        std::cout << "\n\nAttempt #" << i << ": " << std::endl;
        game.inputWord();
        game.check();

        if (game.word == game.wordAnswer)
        {
            std::cout << "\x1B[32m" << "\nYOU WIN!" << "\x1B[0m";
            i = 6;      //increment i so that the loop breaks without having to use a break statement
        }
        game.currectCount = 0;
    }

    if (game.word != game.wordAnswer)
    {
        std::cout << "\x1B[31m" << "\nYOU LOSE :(" << "\x1B[0m" << std::endl;
        std::cout << "Answer: " << game.wordAnswer << std::endl;
    }

    return 0;
}

/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>


int main()
{
    std::ifstream input;
    input.open("TestDictionary.txt");
    std::vector<std::string>  possiblewords;
    std::string wordoa;
    while (input >> wordoa)
    {
        possiblewords.push_back(wordoa);
    }
    srand((unsigned)time(0));
    int randomnumber;
    randomnumber = (rand() % possiblewords.size()) ;

    std::string currentword;
    currentword = possiblewords[randomnumber];
    //std::cout << currentword << std::endl;
    std::string guess;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "enter guess" << std::endl;
        std::cin >> guess;
        if (std::count(possiblewords.begin(), possiblewords.end(), guess))
        {
            for (int j = 0; j < 5; j++)
            {
                bool found = 0;
                bool correctplace = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (guess[j]==currentword[k])
                    {
                        found++;
                    }
                    else if (guess[j] == currentword[j])
                    {
                        correctplace = 1;
                    }

                }
                HANDLE  hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                if (correctplace == 1)
                {
                    SetConsoleTextAttribute(hConsole, 10);
                    std::cout << guess[j];
                }
                else if (found == 1)
                {
                    SetConsoleTextAttribute(hConsole, 12); // 14 is yellow 12 is red
                    std::cout << guess[j];
                }
                else if(found == 0)
                {
                    std::cout << guess[j];
                }
                SetConsoleTextAttribute(hConsole, 15);
            }
            std::cout << " " << std::endl;
        }
        else
        {
            std::cout << "invalid word" << std::endl;
            i--;
        }
        if (guess == currentword)
        {
            std::cout << "winner" << std::endl;
            break;
        }
    }
    if (guess != currentword)
    {
        std::cout << "loser" << std::endl << "the word was " << currentword;
    }
    return 0;
}


*/