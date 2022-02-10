#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QSqlDatabase>

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_exitButton_clicked()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("dbConn");
    close();
}


void MainMenu::on_chooseButton_clicked()
{
    if (ui->showMusicButton->isChecked()) {

    }
    else if (ui->showDiscButton->isChecked()) {

    }
    else if (ui->showRatingButton->isChecked()) {

    }
    else if (ui->editDiscButton->isChecked()) {

    }
    else if (ui->addEnsembleButton->isChecked()) {

    }
}

