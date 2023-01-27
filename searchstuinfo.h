#ifndef SEARCHSTUINFO_H
#define SEARCHSTUINFO_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include "StudentInfo.h"

namespace Ui {
class searchStuInfo;
}

class searchStuInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchStuInfo(QWidget *parent = nullptr);
    ~searchStuInfo();

signals:
    void display(int num);

public slots:
    void on_Return_Button_clicked();
    void on_Search_Button_clicked();

private:
    Ui::searchStuInfo *ui;
    QString stu_name, stu_id;
    QVector<StudentInfo> stuInfo;
};

#endif // SEARCHSTUINFO_H
