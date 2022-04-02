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

    void covenverToLower(std::string &word)
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
        wordAnswer = "plate";//dictionary[randIndex];
        std::cout << "Answer: " << wordAnswer << std::endl;
    }

    //a function used to input the word
    void inputWord()
    {
        std::cout << "Input: ";
        std::cin >> word;

        covenverToLower(word);

        
        while (!wordExists(word, dictionary) || !fiveLetters(word))
        {
            std::cout << "Error! Either input does not exist in our dictionary, or the input is not 5 letters" << std::endl;
            std::cout << "Input: ";
            std::cin >> word;
            covenverToLower(word);
            wordExists(word, dictionary);
        }
    }

    //Primary function of the game: checks if the letter is in the correct space or exists in the word
    void check()
    {  
        std::vector<bool> usedLetter = { 0,0,0,0,0};
        std::vector<std::string> WordStat = {"","","","",""};
        std::string CorrectPos = "\x1B[42m";  //green colour
        std::string NotInWord = "\x1B[30m\x1B[47m";      //white colour
        std::string WrongPos = "\x1B[43m";      //yellow colour

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

        
        for (int i = 0; i < word.size(); i++)
        {
            std::cout << WordStat[i] << word[i] << "\x1B[0m";

        }
    }

    void gameFunction()
    {
        int attemptsNum = 6;    //number of attempts at guessing the word
        for (int i = 1; i <= attemptsNum; i++)
        {
            std::cout << "\n\nAttempt #" << i << ": " << std::endl;
            inputWord();
            check();

            if (word == wordAnswer)
            {
                std::cout << "\x1B[32m" << "\nYOU WIN!" << "\x1B[0m";
                i = attemptsNum+1;      //increment i so that the loop breaks without having to use a break statement
            }
        }

        if (word != wordAnswer)
        {
            std::cout << "\x1B[31m" << "\nYOU LOSE :(" << "\x1B[0m" << std::endl;
            std::cout << "Answer: " << wordAnswer << std::endl;
        }
    }


};

class modifiedWordle : public wordle
{

    //choose difficulty
    //random index generator
    //print functions

    //gameFunction() with points

};



int main()
{
    wordle game;            //creates the object for the wordle class

    game.openLibrary("TestDictionary.txt");     //pass the filename of the dictionary as an argument
    game.selectWord();
    game.gameFunction();


    

    return 0;
}

