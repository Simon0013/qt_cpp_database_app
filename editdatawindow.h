#ifndef EDITDATAWINDOW_H
#define EDITDATAWINDOW_H

#include <QWidget>

namespace Ui {
class EditDataWindow;
}

class EditDataWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditDataWindow(QWidget *parent = nullptr);
    ~EditDataWindow();

private:
    Ui::EditDataWindow *ui;
};

#endif // EDITDATAWINDOW_H
