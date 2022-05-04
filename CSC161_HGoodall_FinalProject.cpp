/*CSC161_HGoodall_FinalProject
* Author: Hannah Goodall
* Date: 5/4/2022
* Program: Word search game that reads the puzzles from text files. Give the coordinates of the word you find and two asterisks will appear next to the word if you found it and entered the correct coordinates. 
*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int GetPuzzle(vector<vector<char>> &puzzle, vector<string> &words, int ROWS, int COLS);
void PlayGame(vector<vector<char>> &puzzle, vector<string> &words, int& numWords, int ROWS, int COLS, int &choice);
void Instructions();
void Print(vector<vector<char>>& puzzle, vector<string>& words);
void MarkWord(vector<string>& words, string& word);


int main()
{
    const int ROWS = 10;
    const int COLS = 10;
    int choice, numWords;
    vector<vector<char>> puzzle;
    vector<string> words;

    cout << "Welcome!!" << endl;
    cout << "\n";
    cout << "1. New game" << endl;
    cout << "2. Exit" << endl;
    cin >> choice;

    if (choice == 1) {
        cout << "\n";
        Instructions();
        numWords = GetPuzzle(puzzle, words, ROWS, COLS);
        PlayGame(puzzle, words, numWords, ROWS, COLS, choice);
    }


}
void Instructions() {
    cout << "\nINSTRUCTIONS" << endl <<
        "------------------------------------------------------------------------" << endl <<
        "| Find all the words in the word bank.                                 |" << endl <<
        "| Words can be vertical, horizontal, diagonal, backwards and forwards. |\n" <<
        "| Words do not share letters.                                          |\n" <<
        "| Type -999 -999 if you give up.                                       |" << endl <<
        "------------------------------------------------------------------------" << endl;
}

//read random text file when user clicks new game. displays puzzle and words to search for
int GetPuzzle(vector<vector<char>> &puzzle, vector<string> &words, int ROWS, int COLS) {

    
    char letter;
    int numWords;
    string word;
    ifstream infile;

    srand(time(0));
    int n = 1 + (rand() % 5);
    string filename = "WordSearch" + to_string(n) + ".txt";

    infile.open(filename);

    //input text file and save it into vector
    for (int i = 0; i < ROWS; i++) {
        vector<char> v1;
        for (int j = 0; j < COLS; j++) {
            infile >> letter;
            v1.push_back(letter);
        }
        puzzle.push_back(v1);
    }
    //get words to search for
    infile >> numWords;
    for (int i = 0; i < numWords; i++) {
        infile >> word;
        words.push_back(word);
    }

    //print puzzle
    cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < puzzle.size(); i++) {
        cout << i << " ";
        for (int j = 0; j < COLS; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }

    
    //print word bank
    cout << "\nWork Bank" << endl;
    cout << "------------" << endl;
    for (int i = 0; i < numWords; i++) {
        cout << i+1 << ". " << words[i] << endl;
    }

    return numWords;
}
void Print(vector<vector<char>>& puzzle, vector<string>& words) {
    //print updated puzzle
    cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < puzzle.size(); i++) {
        cout << i << " ";
        for (int j = 0; j < puzzle[0].size(); j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }

    //print updated word bank
    cout << "\nWork Bank" << endl;
    cout << "------------" << endl;
    for (int i = 0; i < words.size(); i++) {
        cout << i + 1 << ". " << words[i] << endl;
    }
}

//user enters coordinates and program finds word they are referring to and changes letters to lowercase (adds an asterisk by word in word bank to indicate it is found.
void PlayGame(vector<vector<char>>& puzzle, vector<string>& words, int& numWords, int ROWS, int COLS, int& choice) {
    pair<int, int> c1;
    pair<int, int> c2;
    vector<char> wordvec;
    string word;
    int count = 0;


    while (count != numWords && choice != 2) {
        cout << "\nEnter the starting coordinates of word (two numbers, row then column, separated by a space, ex: 0 3): ";
        cin >> c1.first >> c1.second;
        if (c1.first == -999 || (c1.first == -999 && c1.second == -999))
            break;
        cout << "Enter the ending coordinates of the word (two numbers, row then column, separated by a space, ex: 0 3): ";
        cin >> c2.first >> c2.second;
        if (c2.first == -999 || (c2.first == -999 && c2.second == -999))
            break;
        cout << endl;
        if (c1.first > 9 || c1.second > 9 || c2.first > 9 || c2.second > 9) {
            cout << "Invalid option" << endl;
            continue;
        }



        //if found make found letters lowercase
        if (puzzle[c1.first][c1.second] < 91) {


            //word is horizontal forwards
            if (c1.first == c2.first && c1.second < c2.second) {
                for (int i = c1.second; i <= c2.second; i++) {
                    wordvec.push_back(puzzle[c1.first][i]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end())
                {
                    MarkWord(words, word);
                    for (int i = c1.second; i <= c2.second; i++) {
                        puzzle[c1.first][i] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }

            }
            //word is horizontal backwards
            else if (c1.first == c2.first && c1.second > c2.second) {
                for (int i = c1.second; i >= c2.second; i--) {
                    wordvec.push_back(puzzle[c1.first][i]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.second; i >= c2.second; i--) {
                        puzzle[c1.first][i] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else {

                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }

            }
            //word is vertical forwards
            else if (c1.first < c2.first && c1.second == c2.second) {
                for (int i = c1.first; i <= c2.first; i++) {
                    wordvec.push_back(puzzle[i][c1.second]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.first; i <= c2.first; i++) {
                        puzzle[i][c1.second] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }

            }
            //word is vertical backwards
            else if (c1.first > c2.first && c1.second == c2.second) {
                for (int i = c1.first; i >= c2.first; i--) {
                    wordvec.push_back(puzzle[i][c1.second]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.first; i >= c2.first; i--) {
                        puzzle[i][c1.second] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }

            }
            //word is diagonal forwards to the bottom right
            else if (c1.first < c2.first && c1.second < c2.second) {
                for (int i = c1.first, j = c1.second; i <= c2.first; i++, j++) {
                    wordvec.push_back(puzzle[i][j]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.first, j = c1.second; i <= c2.first; i++, j++) {
                        puzzle[i][j] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;

                }
                else {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }


            }
            //word is diagonal backwards to the top left
            else if (c1.first > c2.first && c1.second > c2.second) {
                for (int i = c1.first, j = c1.second; i >= c2.first; i--, j--) {
                    wordvec.push_back(puzzle[i][j]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.first, j = c1.second; i >= c2.first; i--, j--) {
                        puzzle[i][j] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else
                {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }

            }
            //word is diagonal forwards to the top right
            else if (c1.first > c2.first && c1.second < c2.second) {
                for (int i = c1.first, j = c1.second; i >= c2.first; i--, j++) {
                    wordvec.push_back(puzzle[i][j]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.first, j = c1.second; i >= c2.first; i--, j++) {
                        puzzle[i][j] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }


            }
            //word is diagonal backwards to the bottom left
            else if (c1.first < c2.first && c1.second > c2.second) {
                for (int i = c1.first, j = c1.second; i <= c2.first; i++, j--) {
                    wordvec.push_back(puzzle[i][j]);
                }
                string word(wordvec.begin(), wordvec.end());
                if (find(words.begin(), words.end(), word) != words.end()) {
                    MarkWord(words, word);
                    for (int i = c1.first, j = c1.second; i <= c2.first; i++, j--) {
                        puzzle[i][j] += 32;
                    }
                    Print(puzzle, words);
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    count += 1;
                }
                else
                {
                    cout << "Not a word!";
                    wordvec.erase(wordvec.begin(), wordvec.end());
                    continue;
                }

            }

            if (count == numWords) {
                cout << "\n\nYOU WON!!!" << endl;
                cout << "Congratulations!" << endl;
                cout << endl;
                cout << "Play Again?" << endl;
                cout << "1. Yes OR 2. No" << endl;
                cin >> choice;

                if (choice == 1) {
                    puzzle.erase(puzzle.begin(), puzzle.end());
                    words.erase(words.begin(), words.end());
                    Instructions();
                    numWords = GetPuzzle(puzzle, words, ROWS, COLS);
                    PlayGame(puzzle, words, numWords, ROWS, COLS, choice);
                }
                else {
                    cout << "Thank you for playing!" << endl;
                    cout << "Have a great day! :) <3";
                    break;
                }
            }
        }
    }
}

void MarkWord(vector<string>& words, string &word) {
    for (int i = 0; i < words.size(); i++) {
        if (word == words[i]) {
            words[i] += "**";
        }
    }
}



