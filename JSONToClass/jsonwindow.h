#ifndef JSONWINDOW_H
#define JSONWINDOW_H

#include <QMainWindow>

namespace Ui {
class JsonWindow;
}

class JsonWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JsonWindow(QWidget *parent = 0);
    ~JsonWindow();

private:
    Ui::JsonWindow *ui;
};

#endif // JSONWINDOW_H
