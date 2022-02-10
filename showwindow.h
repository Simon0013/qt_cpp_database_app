#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class ShowWindow;
}

class ShowWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWindow(QWidget *parent = nullptr);
    ~ShowWindow();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_ensembleButton_clicked();

    void on_musicianButton_clicked();

private:
    Ui::ShowWindow *ui;
    QSqlTableModel *model = new QSqlTableModel(Q_NULLPTR, QSqlDatabase::database("dbConn"));
    bool modelInitialized = false;
    void modelInitialize();
};

#endif // SHOWWINDOW_H
