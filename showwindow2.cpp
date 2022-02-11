#include "showwindow2.h"
#include "ui_showwindow2.h"
#include <QtSql>
#include <QStandardItemModel>

ShowWindow2::ShowWindow2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWindow2)
{
    ui->setupUi(this);
    QString headers = "id, Название, Производитель, Поставщик, Дата_выпуска, Розничная_цена, "
                      "Оптовая_цена, Продано_в_прошлом_году, Продано_в_текущем_году, "
                      "В_наличии";
    model->setHorizontalHeaderLabels(headers.split(","));
    ui->tableView->setModel(model);
}

ShowWindow2::~ShowWindow2()
{
    delete model;
    delete ui;
}

void ShowWindow2::on_comboBox_currentTextChanged(const QString &arg1)
{
    model->removeRows(0, model->rowCount());
    if ((ui->comboBox->currentIndex() != -1) && comboBoxChangedAllowed)
    {
        query = new QSqlQuery(nullptr, QSqlDatabase::database("dbConn"));
        QString queryTxt = "SELECT id FROM %1 WHERE name = '%2'";
        query->exec(queryTxt.arg(chosen).arg(arg1));
        query->next();
        QString performerId = query->value(0).toString();
        queryTxt = "SELECT id FROM perfomance WHERE %1_id = %2";
        query->exec(queryTxt.arg(chosen).arg(performerId));
        QStringList *perfomances = new QStringList();
        while (query->next())
        {
            perfomances->append(query->value(0).toString());
        }
        queryTxt = "SELECT disc.id, disc.name, releaser.name, provider.name, create_date, retail_price, "
                   "wholesale_price, selled_past_year, selled_this_year, stock FROM disc "
                   "INNER JOIN releaser ON releaser.id = creater_id "
                   "INNER JOIN provider ON provider.id = provider_id "
                   "INNER JOIN perfomance_disc ON (disc.id = disc_id AND perfomance_id = %1)";
        QString perfomance;
        foreach (perfomance, *perfomances)
        {
            query->exec(queryTxt.arg(perfomance));
            while (query->next())
            {
                if (insertedIds.contains(query->value(0).toString()))
                    continue;
                QList<QStandardItem *> row;
                for (int i = 0; i < 10; i++)
                    row << new QStandardItem(query->value(i).toString());
                model->appendRow(row);
                insertedIds.append(query->value(0).toString());
            }
        }
        ui->tableView->resizeColumnsToContents();
        QString countLabelTxt = "Итого найдено пластинок: %1";
        ui->countLabel->setText(countLabelTxt.arg(model->rowCount()));
        insertedIds.clear();
        delete query;
    }
}


void ShowWindow2::on_ensembleButton_clicked()
{
    if (ui->ensembleButton->isChecked())
    {
        comboBoxChangedAllowed = false;
        chosen = "ensemble";
        query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec("SELECT name FROM ensemble ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        ui->comboBox->setCurrentIndex(-1);
        ui->label->setText("Выберете интересующий Вас ансамбль: ");
        delete query;
        comboBoxChangedAllowed = true;
    }
}


void ShowWindow2::on_musicianButton_clicked()
{
    if (ui->musicianButton->isChecked())
    {
        comboBoxChangedAllowed = false;
        chosen = "musician";
        query = new QSqlQuery(QSqlDatabase::database("dbConn"));
        query->exec("SELECT name FROM musician ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        ui->comboBox->setCurrentIndex(-1);
        ui->label->setText("Выберете интересующего Вас музыканта: ");
        delete query;
        comboBoxChangedAllowed = true;
    }
}

