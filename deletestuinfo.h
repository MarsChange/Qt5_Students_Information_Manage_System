#ifndef DELETESTUINFO_H
#define DELETESTUINFO_H

#include <QMainWindow>
#include <QMessageBox>
#include "StudentInfo.h"

namespace Ui {
class deleteStuInfo;
}

class deleteStuInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit deleteStuInfo(QWidget *parent = nullptr);
    ~deleteStuInfo();

signals:
    void display(int num);

public slots:
    void on_Return_Button_clicked();
    void on_Search_Button_clicked();
    void on_Delete_Button_clicked();

private:
    Ui::deleteStuInfo *ui;
    QString stu_name, stu_id;
    QVector<StudentInfo> stuInfo;
};

#endif // DELETESTUINFO_H
