#include "wordle.h"

Wordle::Wordle()
{
    guessNum = 0;
    letterNum = 0;

    getWordList();
    getWordScore();
}

void Wordle::getWordList()
{
    QString word;
    QFile file1(":/Resources/officialWords.txt");

    if (file1.open(QIODevice::ReadOnly))
    {
        file1.seek(0);

        while(!file1.atEnd())
        {
            word = file1.readLine();
            word.chop(2);

            possibleAnswers.push_back(word);
            remainingPossibleGuesses.push_back(word);
        }

        file1.close();
    }
    else
    {
        qCritical() << "Could not open file1!";
        qCritical() << file1.errorString();
        return;
    }

    QFile file2(":/Resources/allWords.txt");

    if (file2.open(QIODevice::ReadOnly))
    {
        file2.seek(0);

        while(!file2.atEnd())
        {
            word = file2.readLine();
            word.chop(2);

            possibleGuesses.push_back(word);
        }

        file2.close();
    }
    else
    {
        qCritical() << "Could not open file2!";
        qCritical() << file2.errorString();
        return;
    }
}

void Wordle::getWordScore()
{
    QFile file(":/Resources/possibleWordleAnswersWithFrequencies.txt");

    if (file.open(QIODevice::ReadOnly))
    {
        while (!file.atEnd())
        {
            QString l;
            QStringList pair;
            QString wordWithFrequency[2];
            QString w;

            l = file.readLine();
            pair = l.split(" ");

            foreach(QString w, pair)
            {
                wordWithFrequency->push_back(w);
            }

            words.push_back({ wordWithFrequency[0], wordWithFrequency[1].toInt() });
        }
    }
}

QString Wordle::getBestGuess()
{
    return words[0].first;
}

QString Wordle::getRandomWordle()
{
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, possibleAnswers.size());

    return possibleAnswers[dist(mt)];
}

void Wordle::setWordle(QString w)
{
    if (w == "")
        wordle = getRandomWordle();
    else
        wordle = w;
}

void Wordle::makeGuess(QString g)
{
    if (g == "")
        guess = getBestGuess();
    else
        guess = g;
}

void Wordle::getGuessResults()
{
    for (int i = 0; i < 5; i++)
    {
        greyLetters[i] = '0';
        yellowLetters[i] = '0';
        green[i] = '0';
    }

    //Check for letters in correct position
    for (int i = 0; i < 5; i++)
    {
        if (guess[i] == wordle[i])
        {
            green[i] = '1';
        }
    }

    //Check for correct letters in wrong position
    for (int i = 0; i < 5; i++)
    {
        bool addYellowLetter = false;
        pair<QChar, int> val;

        for (int j = 0; j < 5; j++)
        {
            if (guess[i] == wordle[j] && i != j && green[i] != '1')
            {
                val.first = guess[i];
                val.second = i;

                addYellowLetter = true;
            }
        }

        if (addYellowLetter)
        {
            yellow.push_back(val);
            yellowLetters[val.second] = '1';
        }
    }

    for (int i = 0; i < 5; i++)
    {
        bool isYellowOrGreen = false;

        for (int j = 0; j < 5; j++)
        {
            if (guess[i] == green[j])
                isYellowOrGreen = true;
        }

        for (int j = 0; j < yellow.size(); j++)
        {
            if (guess[i] == yellow[j].first)
                isYellowOrGreen = true;
        }

        if (!isYellowOrGreen && guess[i] != wordle[i])
        {
            grey.push_back(guess[i]);
            greyLetters[i] = '1';
        }
    }
}

void Wordle::eliminateWords()
{
    int numWordsRemoved = 0;
    auto i = words.begin();

    while (i != words.end())
    {
        QString word = i->first;
        bool wordRemoved = false;

        if (!wordRemoved)
        {
            //Eliminate word if greens aren't in it
            for (int j = 0; j < 5; j++)
            {
                    if (green[j] == '1' && word[j] != wordle[j])
                    {
                        wordRemoved = true;
                    }
            }

            //Eliminate word if yellows aren't in it
            for (int j = 0; j < 5; j++)
            {
                for (int t = 0; t < yellow.size(); t++)
                {
                    if (word[j] == yellow[t].first && j == yellow[t].second)
                    {
                        wordRemoved = true;
                    }
                }
            }

            for (int j = 0; j < yellow.size(); j++)
            {
                bool letterIncluded = false;

                for (int t = 0; t < 5; t++)
                {

                    if (yellow[j].first == word[t])
                    {
                        letterIncluded = true;
                    }
                }

                if (!letterIncluded)
                    wordRemoved = true;
            }

            //Eliminate word if it has one of the greys
            for (int j = 0; j < grey.size(); j++)
            {
                bool greyLetterIncluded = false;

                for (int t = 0; t < 5; t++)
                {
                    if (grey[j] == word[t])
                    {
                        greyLetterIncluded = true;
                    }
                }

                if (greyLetterIncluded)
                    wordRemoved = true;
            }
        }

        if (wordRemoved)
        {
            i = words.erase(i);
            numWordsRemoved++;
        }
        else
        {
            ++i;
        }
    }
}

void Wordle::resetVals()
{
    words.clear();
    guessNum = 0;
    grey.clear();
    yellow.clear();
    isGameOver = false;
    gameWon = false;

    getWordScore();

    for (int i = 0; i < 5; i++)
        green[i] = '0';
}

void Wordle::gameOver()
{
    if (guess != "")
    {
        bool isCorrectGuess = true;

        for (int i = 0; i < 5; i++)
            if (guess[i] != wordle[i])
                isCorrectGuess = false;

        if (isCorrectGuess)
            gameWon = true;
    }

    if (gameWon)
        isGameOver = true;
}

bool Wordle::isValidWord(QString word)
{
    bool isFound = false;

    for (const auto &i : remainingPossibleGuesses)
    {
        if (i == word)
            isFound = true;
    }

    return isFound;
}
