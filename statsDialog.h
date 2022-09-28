#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include "ui_mainmenu.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *m_ui;
};

#endif // STATSDIALOG_H
