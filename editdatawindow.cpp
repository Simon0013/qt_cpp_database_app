#include "editdatawindow.h"
#include "ui_editdatawindow.h"

EditDataWindow::EditDataWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditDataWindow)
{
    ui->setupUi(this);
}

EditDataWindow::~EditDataWindow()
{
    delete ui;
}
