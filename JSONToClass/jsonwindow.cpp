#include "jsonwindow.h"
#include "ui_jsonwindow.h"
#include <QString>
#include <qDebug>
#include <QClipboard>

#include <iostream>
#include <String>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

static const char* kTypeNames[] =
    { "Null", "False", "True", "Object", "Array", "String", "Number" };
static const char* kTypes[] =
    { "Object", "bool", "bool", "Object", "Array", "String", "int" };

int nextIndex = 0;

JsonWindow::JsonWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JsonWindow)
{
    ui->setupUi(this);

    ui->textEdit_2->setText("请在上方输入框中输入标准json字符串");


    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(BtnPushSlot()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(OnItemDoubleClicked(QListWidgetItem *)));

    std::string textJson = "{\"code\":200,\"message\":\"success\",\"time\":{\"start\":11,\"end\":22},\"user\":[\"zhangsan\",\"lisi\"]}";
    textJson = "{\"code\":200,\"score\":10.123,\"message\":\"success\"}";
}

JsonWindow::~JsonWindow()
{
    delete ui;
}

std::string JsonWindow::ValueToString(const rapidjson::Value &value) {
    rapidjson::StringBuffer sbBuf;
    rapidjson::Writer<rapidjson::StringBuffer> jWriter(sbBuf);
    value.Accept(jWriter);
    return std::string(sbBuf.GetString());
}

void JsonWindow::analyseString(const std::string &textJson, const std::string &beanName)
{
    QString text = QString::fromStdString(textJson);

    Document document;
    document.Parse(textJson.data());
    if (document.HasParseError()) {
        ui->textEdit_2->setText("HasParseError:\n" + text);
        ui->textEdit_2->append("\n");
        this->repaint();
        return;
    } else {
        ui->textEdit_2->setText("Json格式正确");
        this->repaint();
    }


    std::string sb;
    char buff[100];
    snprintf(buff, sizeof(buff), "public class %s {\n\n", beanName.c_str());
    sb.append(buff);

    for (Value::ConstMemberIterator itr = document.MemberBegin();
        itr != document.MemberEnd(); ++itr)
    {
        printDefineSentence(itr->name.GetString(), itr->value.GetType(), itr->value, sb); //itr->value.GetObject()
    }

    sb.append("\n}\n");
    qDebug()<<sb.c_str();
    //ui->textEdit_2->append(sb.c_str());
    //ui->textEdit_2->append("\n");

    QListWidgetItem* item = new QListWidgetItem(sb.c_str());
    ui->listWidget->addItem(item);
    ui->listWidget->repaint();
    this->repaint();
}

void JsonWindow::printDefineSentence(std::string variable, int index, const Value &value, std::string &sb)
{
    const char* kType = kTypes[index];
    // Null 不处理
    // Object和Array特殊处理
    if (index == 0) return; // Null
    if (index == 3) { // Object
        std::string firstUpper = variable;
        firstUpper[0] = toupper(firstUpper[0]);
        std::string objBeanName = firstUpper + "Bean";

        char buff[100];
        snprintf(buff, sizeof(buff), "    public %s %s;", objBeanName.c_str(), variable.c_str());
        sb.append(buff);
        sb.append("\n");

        // 根据value取出来字符串, 再次创建一个Bean类
        std::string valueStr = ValueToString(value);

        analyseString(valueStr, objBeanName);
    } else if (index == 4) { // Array

        if (value.Size() == 0) {
            // 什么都不做, 就当没这个Array, 因为没法判断类型
        } else {
            const Value &v0 = value[0];
            int type = v0.GetType();
            if (type !=3 && type != 4) { // int/string/bool的情况(3/4为Object或者Array的情况), 不可能为空
                const char* itemType = kTypes[type];

                char buff[100];
                snprintf(buff, sizeof(buff), "    public List<%s> %s;", itemType, variable.c_str());
                sb.append(buff);
                sb.append("\n");
            } else {
                std::string firstUpper = variable;
                firstUpper[0] = toupper(firstUpper[0]);
                std::string objBeanName = firstUpper + "Model";

                std::string valueStr = ValueToString(v0);
                analyseString(valueStr, objBeanName);

                char buff[100];
                snprintf(buff, sizeof(buff), "    public List<%s> %s;", objBeanName.c_str(), variable.c_str());
                sb.append(buff);
                sb.append("\n");
            }

        }
        // 需要判断是不是自定义对象还是JAVA基本对象, String int bool float, 方法参数应该继续传递父json
        // 应该弄一个StringBuilder, 当拼装完成后才打印到终端
    } else { // bool int String
        char javaType[10];
        if (value.IsFloat()) {
            snprintf(javaType, sizeof(javaType), "float");
        } else if (value.IsNumber() && !value.IsInt()) {
            snprintf(javaType, sizeof(javaType), "long");
        } else {
            snprintf(javaType, sizeof(javaType), "%s", kType);
        }

        char buff[100];
        snprintf(buff, sizeof(buff), "    public %s %s;", javaType, variable.c_str());
        sb.append(buff);
        sb.append("\n");
    }
}

void JsonWindow::OnItemDoubleClicked(QListWidgetItem *item) {
    QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
    QString originalText = item->text();	         //获取item上文本信息
    clipboard->setText(originalText);		             //设置剪贴板内容

    ui->textEdit_2->append("已复制");
    this->repaint();
}

void JsonWindow::BtnPushSlot(void)
{
    //重新初始化
    ui->textEdit_2->setText("请在上方输入框中输入标准json字符串");
    ui->listWidget->clear();
    nextIndex = 0;

    const QString strText = ui->textEdit->toPlainText();
    const std::string inputStr = strText.toStdString();
    analyseString(inputStr, "Bean");
    ui->textEdit_2->append("已解析完成, 请双击复制\n");
    this->repaint();
}
