#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    getStatData();

    backspacePressed = false;
    isSimulating = false;

    wordleBot.setWordle();
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::keyPressEvent(QKeyEvent *event)
{
    if (!wordleBot.gameWon && wordleBot.guessNum < 6)
    {
        if (event->key() == Qt::Key_Q)
        {
            setLabelText("Q");
            word[wordleBot.letterNum] = 'Q';
        }

        if (event->key() == Qt::Key_W)
        {
            setLabelText("W");
            word[wordleBot.letterNum] = 'W';
        }

        if (event->key() == Qt::Key_E)
        {
            setLabelText("E");
            word[wordleBot.letterNum] = 'E';
        }

        if (event->key() == Qt::Key_R)
        {
            setLabelText("R");
            word[wordleBot.letterNum] = 'R';
        }

        if (event->key() == Qt::Key_T)
        {
            setLabelText("T");
            word[wordleBot.letterNum] = 'T';
        }

        if (event->key() == Qt::Key_Y)
        {
            setLabelText("Y");
            word[wordleBot.letterNum] = 'Y';
        }

        if (event->key() == Qt::Key_U)
        {
            setLabelText("U");
            word[wordleBot.letterNum] = 'U';
        }

        if (event->key() == Qt::Key_I)
        {
            setLabelText("I");
            word[wordleBot.letterNum] = 'I';
        }

        if (event->key() == Qt::Key_O)
        {
            setLabelText("O");
            word[wordleBot.letterNum] = 'O';
        }

        if (event->key() == Qt::Key_P)
        {
            setLabelText("P");
            word[wordleBot.letterNum] = 'P';
        }

        if (event->key() == Qt::Key_A)
        {
            setLabelText("A");
            word[wordleBot.letterNum] = 'A';
        }

        if (event->key() == Qt::Key_S)
        {
            setLabelText("S");
            word[wordleBot.letterNum] = 'S';
        }

        if (event->key() == Qt::Key_D)
        {
            setLabelText("D");
            word[wordleBot.letterNum] = 'D';
        }

        if (event->key() == Qt::Key_F)
        {
            setLabelText("F");
            word[wordleBot.letterNum] = 'F';
        }

        if (event->key() == Qt::Key_G)
        {
            setLabelText("G");
            word[wordleBot.letterNum] = 'G';
        }

        if (event->key() == Qt::Key_H)
        {
            setLabelText("H");
            word[wordleBot.letterNum] = 'H';
        }

        if (event->key() == Qt::Key_J)
        {
            setLabelText("J");
            word[wordleBot.letterNum] = 'J';
        }

        if (event->key() == Qt::Key_K)
        {
            setLabelText("K");
            word[wordleBot.letterNum] = 'K';
        }

        if (event->key() == Qt::Key_L)
        {
            setLabelText("L");
            word[wordleBot.letterNum] = 'L';
        }

        if (event->key() == Qt::Key_Z)
        {
            setLabelText("Z");
            word[wordleBot.letterNum] = 'Z';
        }

        if (event->key() == Qt::Key_X)
        {
            setLabelText("X");
            word[wordleBot.letterNum] = 'X';
        }

        if (event->key() == Qt::Key_C)
        {
            setLabelText("C");
            word[wordleBot.letterNum] = 'C';
        }

        if (event->key() == Qt::Key_V)
        {
            setLabelText("V");
            word[wordleBot.letterNum] = 'V';
        }

        if (event->key() == Qt::Key_B)
        {
            setLabelText("B");
            word[wordleBot.letterNum] = 'B';
        }

        if (event->key() == Qt::Key_N)
        {
            setLabelText("N");
            word[wordleBot.letterNum] = 'N';
        }

        if (event->key() == Qt::Key_M)
        {
            setLabelText("M");
            word[wordleBot.letterNum] = 'M';
        }

        if (event->key() == Qt::Key_Backspace && wordleBot.letterNum > 0)
        {
            backspacePressed = true;

            wordleBot.letterNum--;
            setLabelText(" ");

            backspacePressed = false;
        }

        if (event->key() == Qt::Key_Return && wordleBot.letterNum == 5)
        {
            QString w = QString::fromRawData(word, 5).toLower();

            qDebug() << w;

            if (wordleBot.isValidWord(w))
            {
                wordleBot.letterNum = 0;

                wordleBot.makeGuess(w);
                wordleBot.getGuessResults();
                getColorHints();
                wordleBot.gameOver();

                wordleBot.guessNum++;
                qDebug() << "guessNum: " << wordleBot.guessNum;

                if (wordleBot.gameWon)
                {
                    QString gameWonMsg = "Congratulations, you guessed the Wordle!";

                    QMessageBox::information(this, tr("Game Over"), gameWonMsg);

                    gamesPlayed++;
                    gameResults[wordleBot.guessNum]++;
                    writeStatData();
                }
                else if (wordleBot.guessNum == 6 && !wordleBot.gameWon)
                {
                    QString gameLostMsg = "Better luck next time!";

                    QMessageBox::information(this, tr("Game Over"), gameLostMsg);

                    gamesPlayed++;
                    gameResults[wordleBot.guessNum]++;
                    writeStatData();
                }
            }
            else
            {
                QString errorMsg = QString::fromRawData(word, 5) + " is not a valid word";

                QMessageBox::information(this, tr("Error"), errorMsg);
            }
        }

        if (wordleBot.letterNum < 5 && event->key() != Qt::Key_Return && event->key() != Qt::Key_Backspace)
        {
            wordleBot.letterNum++;
            //qDebug() << "letterNum: " << wordleBot.letterNum;
        }
    }
}

void MainMenu::setLabelText(QString letter)
{
    QLabel *letterBoxes[30] = { ui->label_0_0, ui->label_0_1, ui->label_0_2, ui->label_0_3, ui->label_0_4, ui->label_1_0, ui->label_1_1, ui->label_1_2, ui->label_1_3, ui->label_1_4, ui->label_2_0, ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_3_0, ui->label_3_1, ui->label_3_2, ui->label_3_3, ui->label_3_4, ui->label_4_0, ui->label_4_1, ui->label_4_2, ui->label_4_3, ui->label_4_4, ui->label_5_0, ui->label_5_1, ui->label_5_2, ui->label_5_3, ui->label_5_4 };

    letterBoxes[(5 * wordleBot.guessNum) + wordleBot.letterNum]->setText(letter);

    if (backspacePressed)
        letterBoxes[(5 * wordleBot.guessNum) + wordleBot.letterNum]->setStyleSheet(style_blank);
    else
        letterBoxes[(5 * wordleBot.guessNum) + wordleBot.letterNum]->setStyleSheet(style_typing);
}

void MainMenu::getColorHints()
{
    QLabel *letterBoxes[30] = { ui->label_0_0, ui->label_0_1, ui->label_0_2, ui->label_0_3, ui->label_0_4, ui->label_1_0, ui->label_1_1, ui->label_1_2, ui->label_1_3, ui->label_1_4, ui->label_2_0, ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_3_0, ui->label_3_1, ui->label_3_2, ui->label_3_3, ui->label_3_4, ui->label_4_0, ui->label_4_1, ui->label_4_2, ui->label_4_3, ui->label_4_4, ui->label_5_0, ui->label_5_1, ui->label_5_2, ui->label_5_3, ui->label_5_4 };

    for (int i = 0; i < 5; i++)
    {
        if (wordleBot.green[i] == '1')
            letterBoxes[(5 * wordleBot.guessNum) + i]->setStyleSheet(style_green);
        else if (wordleBot.yellowLetters[i] == '1')
            letterBoxes[(5 * wordleBot.guessNum) + i]->setStyleSheet(style_yellow);
        else if (wordleBot.greyLetters[i] == '1')
            letterBoxes[(5 * wordleBot.guessNum) + i]->setStyleSheet(style_grey);
        else
            letterBoxes[(5 * wordleBot.guessNum) + i]->setStyleSheet(style_typing);
    }
}

void MainMenu::resetColorHints()
{
    QLabel *letterBoxes[30] = { ui->label_0_0, ui->label_0_1, ui->label_0_2, ui->label_0_3, ui->label_0_4, ui->label_1_0, ui->label_1_1, ui->label_1_2, ui->label_1_3, ui->label_1_4, ui->label_2_0, ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_3_0, ui->label_3_1, ui->label_3_2, ui->label_3_3, ui->label_3_4, ui->label_4_0, ui->label_4_1, ui->label_4_2, ui->label_4_3, ui->label_4_4, ui->label_5_0, ui->label_5_1, ui->label_5_2, ui->label_5_3, ui->label_5_4 };

    for (int i = 0; i < 30; i++)
    {
        letterBoxes[i]->setStyleSheet(style_blank);
        letterBoxes[i]->setText("");
    }
}

void MainMenu::simulateGame(int numSimulations)
{
    int totalSimulations = numSimulations;
    double avg = 0.0;
    int guessTotal = 0;
    bool multipleSims = false;
    showLocalStats = false;

    if (numSimulations > 1)
    {
        multipleSims = true;
    }

    while (numSimulations > 0)
    {        
        if (ui->selectWordle->isModified())
        {
            wordleBot.setWordle(wordle.toLower());
        }
        else
        {
            wordleBot.setWordle();
        }

        qDebug() << wordleBot.wordle;

        while (!wordleBot.gameWon && wordleBot.guessNum < 6)
        {
            wordleBot.makeGuess();

            wordleBot.getGuessResults();

//            ui->stackedWidget->setCurrentIndex(2);

//            for (int i = 0; i < 5; i++)
//            {
//                QChar guessLetter = wordleBot.guess[i].toUpper().unicode();
//                int letter = guessLetter.unicode();

//                QKeyEvent *key_press = new QKeyEvent(QKeyEvent::KeyPress, letter, Qt::NoModifier, wordleBot.guess[i].toUpper());

//                QApplication::sendEvent(ui->centralwidget, key_press);

//                setLabelText(wordleBot.guess[i].toUpper());
//                wordleBot.letterNum++;
//            }

//            QKeyEvent *enter_press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Return, Qt::NoModifier, "");

//            QApplication::sendEvent(ui->centralwidget, enter_press);

            getColorHints();

            wordleBot.eliminateWords();
            wordleBot.gameOver();

            wordleBot.guessNum++;
            wordleBot.letterNum = 0;
        }

        if (multipleSims)
        {
            if (wordleBot.gameWon)
            {
                guesses[wordleBot.guessNum - 1] += 1;
            }
            else
            {
                guesses[6] += 1;
            }

            guessTotal += wordleBot.guessNum;

            wordleBot.resetVals();
        }

        resetColorHints();
        numSimulations--;
    }

    if (multipleSims)
    {
        avg = ((1.0 * guesses[0]) + (2.0 * guesses[1]) + (3.0 * guesses[2]) + (4.0 * guesses[3]) + (5.0 * guesses[4]) + (6.0 * guesses[5])) / (totalSimulations - guesses[6]);

        qDebug() << "Wordle Solver guessed the wordle in " << avg << " guesses on average (excluding failed attempts)";
        qDebug() << "Guess Spread:";
        qDebug() << "1: " << guesses[0];
        qDebug() << "2: " << guesses[1];
        qDebug() << "3: " << guesses[2];
        qDebug() << "4: " << guesses[3];
        qDebug() << "5: " << guesses[4];
        qDebug() << "6: " << guesses[5];
        qDebug() << "X: " << guesses[6];
    }

    resetColorHints();
}

void MainMenu::getStatData()
{
    QFile file("stats.txt");

    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Cannot open file";
    }

    QTextStream stream(&file);

    gamesPlayed = stream.readLine().toInt();

    for (int i = 0; i < 7; i++)
    {
        gameResults[i] = stream.readLine().toInt();
    }

    file.close();
}

void MainMenu::writeStatData()
{
    QFile file("stats.txt");

    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Cannot open file";
    }

    QTextStream stream(&file);

    stream << gamesPlayed << "\n";

    for (int i = 0; i < 7; i++)
    {
        stream << gameResults[i] << "\n";
    }

    file.close();
}

void MainMenu::on_playButton_released()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainMenu::on_viewStats_released()
{
    QBarSet *set0 = new QBarSet("1");

    *set0 << gameResults[6] << gameResults[5] << gameResults[4] << gameResults[3] << gameResults[2] << gameResults[1] << gameResults[0];

    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simulation Statistics");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "X" << "6" << "5" << "4" << "3" << "2" << "1";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->legend()->setVisible(false);
    series->setLabelsVisible(true);

    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->verticalFrame);
    chartView->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainMenu::on_pushButton_released()
{
    if (ui->selectWordle->text() != "")
    {
        qDebug() << "In first if statement";

        if (wordleBot.isValidWord(ui->selectWordle->text().toLower()))
        {
            qDebug() << "Wordle is valid!";

            wordleBot.setWordle(ui->selectWordle->text().toLower());
            wordle = ui->selectWordle->text().toUpper();
        }
    }
    else
    {
        wordleBot.setWordle();
    }

    if(ui->numSimulations->value() > 1)
    {
        isSimulating = true;
        simulateGame(ui->numSimulations->value());
        ui->stackedWidget->setCurrentIndex(2);
    }

    ui->stackedWidget->setCurrentIndex(2);
}

void MainMenu::on_pushButton_2_released()
{
    QBarSet *set0 = new QBarSet("1");

    if (ui->numSimulations->value() > 1)
        *set0 << guesses[6] << guesses[5] << guesses[4] << guesses[3] << guesses[2] << guesses[1] << guesses[0];
    else
        *set0 << gameResults[6] << gameResults[5] << gameResults[4] << gameResults[3] << gameResults[2] << gameResults[1] << gameResults[0];

    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simulation Statistics");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "X" << "6" << "5" << "4" << "3" << "2" << "1";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->legend()->setVisible(false);
    series->setLabelsVisible(true);

    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->verticalFrame);
    chartView->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);

    ui->stackedWidget->setCurrentIndex(1);
}


void MainMenu::on_pushButton_6_released()
{
    resetColorHints();
    wordleBot.resetVals();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainMenu::on_pushButton_3_released()
{
    ui->stackedWidget->setCurrentIndex(0);
}

