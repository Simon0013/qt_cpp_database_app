#include "bookwindow.h"
#include "initdb.h"
#include "mainmenu.h"

#include <QtSql>

BookWindow::BookWindow()
{
    ui.setupUi(this);
}

void BookWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Невозможно подключиться к БД",
                "Ошибка подключения к БД: " + err.text());
}

QSqlDatabase BookWindow::getDbConn()
{
    return db;
}


void BookWindow::on_cancelButton_clicked()
{
    close();
}


void BookWindow::on_okButton_clicked()
{
    if (!QSqlDatabase::drivers().contains("QODBC"))
        QMessageBox::critical(this, "Невозможно подключиться к БД",
                              "Для этого проекта необходим ODBC драйвер");

    // Подключение к базе данных
    QString server = ui.serverName->text();
    QString uid = ui.userName->text();
    QString pwd = ui.password->text();
    QString database = ui.dbName->text();
    QSqlError err = initDb(server, uid, pwd, database);
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }
    hide();
    MainMenu *menuWin = new MainMenu();
    menuWin->show();
}


void BookWindow::on_defaultFullButton_clicked()
{
    ui.serverName->setText("127.0.0.1");
    ui.userName->setText("postgres");
    ui.dbName->setText("music_store");
}

