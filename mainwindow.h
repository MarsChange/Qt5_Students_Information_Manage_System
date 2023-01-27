#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QTableWidget>
#include <QAxObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStackedLayout>
#include "StudentInfo.h"
#include "addstuinfo.h"
#include "searchstuinfo.h"
#include "deletestuinfo.h"

#define MAXNUM 100

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool getStuInfo(QVector<StudentInfo> &allStuInfo);
    void quick_sort_string(QVector<QString> &a, QVector<int> &index, int low, int high);
    void quick_sort_int(QVector<int> &a, QVector<int> &index, int low, int high);
    void quick_sort_double(QVector<double> &a, QVector<int> &index, int low, int high);
    void display_table(QVector<StudentInfo> stuInfo);
    ~MainWindow();

public slots:
    void on_Create_StuInfo_Button_clicked();  // 创建学生信息列表按钮
    void on_Add_StuInfo_Button_clicked();     // 添加学生信息按钮
    void on_Delete_StuInfo_Button_clicked();  // 删除学生信息按钮
    void on_Search_StuInfo_Button_clicked();  // 搜索学生信息按钮
    void on_Sort_Button_clicked();            // 排序按钮

signals:
    void display(int num);

private:
    QVector<StudentInfo> allStuInfo;
    QStackedLayout *stackLayout; // QStackedLayout布局，用于点击按钮后的页面切换

    AddStuInfo *addstuInfo; // 添加学生信息页面
    deleteStuInfo *delStuInfo; // 删除学生信息页面
    searchStuInfo *searchInfo; // 搜索学生信息页面
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
