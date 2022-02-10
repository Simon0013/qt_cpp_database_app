#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "showwindow.h"
#include "editdatawindow.h"
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
        ShowWindow *sw = new ShowWindow();
        sw->show();
    }
    else if (ui->showDiscButton->isChecked()) {
        ShowWindow *sw = new ShowWindow();
        sw->show();
    }
    else if (ui->showRatingButton->isChecked()) {
        ShowWindow *sw = new ShowWindow();
        sw->show();
    }
    else if (ui->editDiscButton->isChecked()) {
        EditDataWindow *edw = new EditDataWindow();
        edw->show();
    }
    else if (ui->addEnsembleButton->isChecked()) {
        EditDataWindow *edw = new EditDataWindow();
        edw->show();
    }
}

