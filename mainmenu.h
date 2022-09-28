#ifndef MAINMENU_H
#define MAINMENU_H

#include "ui_mainmenu.h"
#include "wordle.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class MainMenu : public QMainWindow
{
    Q_OBJECT

    Ui::MainMenu *ui;

    bool isSimulating;
    bool showLocalStats;
    int guesses[7]{ 0 };

    //Stat Data Variables
    int gamesPlayed;
    int gameResults[7]{ 0 };

    QString style_blank = "QLabel { border: 2px solid gray; }";
    QString style_typing = "QLabel { border: 2px solid DarkGray; }";
    QString style_green = "QLabel { border: 2px solid DarkGray; background: ForestGreen ;}";
    QString style_yellow = "QLabel { border: 2px solid DarkGray; background: Gold; }";
    QString style_grey = "QLabel { border: 2px solid DarkGray; background: Gray; }";
    bool backspacePressed;

    void keyPressEvent(QKeyEvent *event);
    void setLabelText(QString letter);
    QString getStyle();
    void getColorHints();
    void resetColorHints();
    void simulateGame(int numSimulations);
    void getStatData();
    void writeStatData();

public:
    Wordle wordleBot;
    QChar word[5];
    QString wordle;

    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
//    void on_pushButton_released();
//    void on_pushButton_2_released();
//    void on_pushButton_3_released();
//    void on_pushButton_4_released();
//    void on_lineEdit_returnPressed();
//    void on_pushButton_5_released();
    void on_playButton_released();
    void on_viewStats_released();
    void on_pushButton_released();
    void on_pushButton_2_released();
    void on_pushButton_6_released();
    void on_pushButton_3_released();
};
#endif // MAINWINDOW_H
