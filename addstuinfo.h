#ifndef ADDSTUINFO_H
#define ADDSTUINFO_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>

namespace Ui {
class AddStuInfo;
}

class AddStuInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddStuInfo(QWidget *parent = nullptr);
    void calculate_Gpoints(QVector<int> s, double &g);
    ~AddStuInfo();

signals:
    void display(int num);

public slots:
    void on_Return_Button_clicked();
    void on_Upload_Button_clicked();
    void on_Specify_Upload_Button_clicked();

private:
    Ui::AddStuInfo *ui;
    QString stu_name, stu_id, stu_sex, stu_major;
    int stu_age, math_1, math_2, Cprog, dataStruc;
    double gpoint = 0.0;
    QVector<int> scores;
};

#endif // ADDSTUINFO_H
