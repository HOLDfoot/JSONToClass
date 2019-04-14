#include "jsonwindow.h"
#include "ui_jsonwindow.h"

JsonWindow::JsonWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JsonWindow)
{
    ui->setupUi(this);
}

JsonWindow::~JsonWindow()
{
    delete ui;
}
