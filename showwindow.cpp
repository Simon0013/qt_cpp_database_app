#include "showwindow.h"
#include "ui_showwindow.h"
#include <QtSql>

ShowWindow::ShowWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWindow)
{
    ui->setupUi(this);
}

ShowWindow::~ShowWindow()
{
    delete ui;
}

void ShowWindow::modelInitialize()
{
    if (ui->musicianButton->isChecked())
        model->setTable("perfomance_view_musician");
    else if (ui->ensembleButton->isChecked())
        model->setTable("perfomance_view_ensemble");
    ui->tableView->setModel(model);
    modelInitialized = true;
}

void ShowWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (!modelInitialized)
        modelInitialize();
    model->select();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void ShowWindow::on_ensembleButton_clicked()
{
    if (ui->ensembleButton->isChecked())
    {
        QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec("SELECT name FROM ensemble ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        modelInitialize();
    }
}


void ShowWindow::on_musicianButton_clicked()
{
    if (ui->musicianButton->isChecked())
    {
        QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec("SELECT name FROM musician ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        modelInitialize();
    }
}

