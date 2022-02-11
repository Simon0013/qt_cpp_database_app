#include "ratingwindow.h"
#include "ui_ratingwindow.h"
#include <QtSql>

RatingWindow::RatingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RatingWindow)
{
    ui->setupUi(this);
    model->setTable("disc");
    model->setSort(7, Qt::DescendingOrder);
    ui->tableView->setModel(model);
    model->select();
    QString years = "прошлого года,текущего года";
    ui->yearChooseBox->addItems(years.split(","));
    QString places = "1,3,5,7,10";
    ui->countTopBox->addItems(places.split(","));
}

RatingWindow::~RatingWindow()
{
    delete ui;
}

void RatingWindow::on_yearChooseBox_currentIndexChanged(int index)
{
    if (index == 0)
        yearColumnIndex = 7;
    else if (index == 1)
        yearColumnIndex = 8;
    model->setSort(yearColumnIndex, sortOrder);
    model->select();
}


void RatingWindow::on_descOrderBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
        sortOrder = Qt::DescendingOrder;
    else if (arg1 == Qt::Checked)
        sortOrder = Qt::AscendingOrder;
    model->setSort(yearColumnIndex, sortOrder);
    model->select();
}


void RatingWindow::on_countTopBox_currentTextChanged(const QString &arg1)
{
    for (int i = 0; i < model->rowCount(); i++)
        ui->tableView->setRowHidden(i, false);
    int countTop = arg1.toInt();
    if (countTop >= model->rowCount())
        return;
    if (sortOrder == Qt::AscendingOrder)
        model->setSort(yearColumnIndex, Qt::DescendingOrder);
    int places = 0, count = 0;
    for (int i = 1; i < model->rowCount(); i++)
    {
        if (model->index(i, yearColumnIndex).data().toInt() != model->index(i-1, yearColumnIndex).data().toInt())
            ++places;
        ++count;
        if (places == countTop) break;
    }
    for (int i = count; i < model->rowCount(); i++)
        ui->tableView->setRowHidden(i, true);
    if (sortOrder == Qt::AscendingOrder)
        model->setSort(yearColumnIndex, Qt::AscendingOrder);
    model->select();
}

