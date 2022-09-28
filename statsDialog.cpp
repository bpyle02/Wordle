#include "statsDialog.h"
#include "ui_dialog.h"
#include "ui_mainmenu.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete m_ui;
}

void Dialog::on_buttonBox_accepted()
{
    ui->stackedWidget->setCurrentIndex(1);
}
