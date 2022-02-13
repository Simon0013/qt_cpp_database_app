#include "perfomancewindow.h"
#include "ui_perfomancewindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

PerfomanceWindow::PerfomanceWindow(QWidget *parent, int elemId, int mode) :
    QWidget(parent),
    ui(new Ui::PerfomanceWindow)
{
    ui->setupUi(this);
    this->elemId = elemId;
    this->mode = mode;
    model->setQuery("SELECT id, Произведение, Ансамбль AS Исполнитель FROM perfomance_view_ensemble INNER JOIN perfomance_disc ON "
                    "perfomance_id = id UNION "
                    "SELECT id, Произведение, Исполнитель FROM perfomance_view_musician INNER JOIN perfomance_disc ON "
                    "perfomance_id = id", QSqlDatabase::database("dbConn"));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

PerfomanceWindow::~PerfomanceWindow()
{
    delete model;
    delete ui;
}

void PerfomanceWindow::on_okButton_clicked()
{
    QModelIndexList indexes =ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())
    {
        QMessageBox::information(this, "Ничего не выбрано", "Вы не выбрали ни одного экземпляра, поэтому изменения не произошли");
        return;
    }
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
    foreach (index, indexes)
    {
        int id = ui->tableView->model()->index(index.row(), 0).data().toInt();
        query->prepare("SELECT * FROM perfomance_disc WHERE perfomance_id = ? AND disc_id = ?");
        query->addBindValue(id);
        query->addBindValue(elemId);
        query->exec();
        bool hasValues = query->next();
        if (hasValues && (mode == 0))
        {
            QMessageBox::information(this, "Дубликация данных", "Эта композиция уже записана на пластинку!");
            return;
        }
        else if (!hasValues && (mode != 0))
        {
            QMessageBox::information(this, "Попытка удалить несуществующее", "Этой композиции и так нет на пластинке!");
            return;
        }
        QString queryTxt;
        if (mode == 0)
            queryTxt = "INSERT INTO perfomance_disc VALUES (?, ?)";
        else
            queryTxt = "DELETE FROM perfomance_disc WHERE perfomance_id = ? AND disc_id = ?";
        query->prepare(queryTxt);
        query->addBindValue(id);
        query->addBindValue(elemId);
        if (!query->exec())
            QMessageBox::critical(this, "Ошибка редактирования данных в БД", query->lastError().text());
        else
            QMessageBox::information(this, "Изменения сохранены", "Изменения успешно сохранены в БД");
    }
    delete query;
}


void PerfomanceWindow::on_cancelButton_clicked()
{
    close();
}

