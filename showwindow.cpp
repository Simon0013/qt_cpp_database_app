#include "showwindow.h"
#include "ui_showwindow.h"
#include "compositionwindow.h"
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
    ui->comboBox->setCurrentIndex(-1);
    modelInitialized = true;
}

void ShowWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (!modelInitialized)
        modelInitialize();
    if (ui->comboBox->currentIndex() != -1)
    {
        QString filter;
        if (ui->ensembleButton->isChecked())
            filter = "Ансамбль = '%1'";
        else
            filter = "Исполнитель = '%1'";
        model->setFilter(filter.arg(arg1));
        model->select();
    }
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    QString countLabelTxt = "Итого найдено исполнений: %1";
    ui->countLabel->setText(countLabelTxt.arg(ui->tableView->model()->rowCount()));
}

void ShowWindow::on_ensembleButton_clicked()
{
    if (ui->ensembleButton->isChecked())
    {
        query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec("SELECT name FROM ensemble ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        modelInitialize();
        ui->label->setText("Выберете интересующий Вас ансамбль: ");
        delete query;
    }
}


void ShowWindow::on_musicianButton_clicked()
{
    if (ui->musicianButton->isChecked())
    {
        query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec("SELECT name FROM musician ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        modelInitialize();
        ui->label->setText("Выберете интересующего Вас музыканта: ");
        delete query;
    }
}


void ShowWindow::on_showCompButton_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index;
    foreach (index, indexes)
    {
        QString comp = ui->tableView->model()->index(index.row(), 0).data().toString();
        query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec(QString("SELECT composition_id FROM perfomance WHERE id = %1").arg(comp));
        query->next();
        comp = query->value(0).toString();
        CompositionWindow *cw = new CompositionWindow(nullptr, comp.toInt());
        cw->show();
    }
}

