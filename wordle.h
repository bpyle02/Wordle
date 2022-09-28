#ifndef WORDLE_H
#define WORDLE_H

#include <random>
#include <vector>
#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

using namespace std;

class Wordle
{
public:
    int guessNum;
    int letterNum;

    vector<QString> possibleAnswers;
    vector<QString> possibleGuesses;
    vector<QString> remainingPossibleGuesses;

    vector<pair<QString, int>> words;
    vector<vector<int>> QCharFreq;

    vector<QChar> grey;
    QChar greyLetters[5];
    vector<pair<QChar, int>> yellow;
    QChar yellowLetters[5];
    QChar green[5];

    QString wordle;
    QString guess;
    QChar guessResults[5];
    bool isGameOver = false;
    bool gameWon = false;

    Wordle();

    void getWordList();
    void getWordScore();
    bool isValidWord(QString word);
    QString getBestGuess();
    QString getRandomWordle();
    void setWordle(QString w = "");
    void makeGuess(QString g = "");
    void getGuessResults();
    void eliminateWords();
    void resetVals();
    void gameOver();
};

#endif // WORDLE_H
