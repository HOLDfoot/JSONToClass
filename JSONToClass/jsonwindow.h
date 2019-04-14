#ifndef JSONWINDOW_H
#define JSONWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

namespace Ui {
class JsonWindow;
}

class JsonWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JsonWindow(QWidget *parent = 0);
    ~JsonWindow();
    std::string ValueToString(const rapidjson::Value &value);
    void analyseString(const std::string &textJson, const std::string &beanName);
    void printDefineSentence(std::string variable, int index, const rapidjson::Value &value, std::string &sb);

public slots:
    void BtnPushSlot(void);
    void OnItemDoubleClicked(QListWidgetItem *item);

private:
    Ui::JsonWindow *ui;
};

#endif // JSONWINDOW_H
