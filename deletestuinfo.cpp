#include "deletestuinfo.h"
#include "ui_deletestuinfo.h"
#include "mainwindow.h"

deleteStuInfo::deleteStuInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::deleteStuInfo)
{
    ui->setupUi(this);
}
void deleteStuInfo::on_Return_Button_clicked(){
    emit display(0);
}

void deleteStuInfo::on_Search_Button_clicked(){
    // 先实例化主窗口这个类，需要调用类内的函数
    MainWindow w;
    QStringList header;
    header<<"学号"<<"姓名"<<"性别"<<"年龄"<<"专业"<<"微积分1-1"<<"微积分1-2"<<"C语言程序设计"<<"数据结构"<<"绩点";
    ui->tableWidget->setColumnCount(header.size());                        // 设置表格的列数
    ui->tableWidget->setHorizontalHeaderLabels(header);                    // 设置水平头
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   // 设置表结构默认不可编辑

    stu_id = ui->lineEdit_id->text();
    stu_name = ui->lineEdit_name->text();
    w.getStuInfo(stuInfo);
    int i = -1; // 变量i用于判定是否找到了相关信息的同学，若找到就+1
    for(int j = 0; j < stuInfo.size(); j++){
        if(stu_id == stuInfo[j].getID() && stu_name == stuInfo[j].getName()){
            i++;
            ui->tableWidget->setRowCount(1);           // 设置行数为1
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(stuInfo[j].getID()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(stuInfo[j].getName()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(stuInfo[j].getSex()));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(stuInfo[j].getAge())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(stuInfo[j].getMajor()));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(stuInfo[j].getMath1())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(stuInfo[j].getMath2())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(stuInfo[j].getC())));
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(stuInfo[j].getDS())));
            ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(stuInfo[j].getGpoint())));
        }
        else{
            continue;
        }
    }
    if(i == -1){
        QMessageBox::warning(this, tr("提醒"), tr("未找到符合条件的同学！"), QMessageBox::Ok);
    }
    // 清除输入框的数据
    ui->lineEdit_id->clear();
    ui->lineEdit_name->clear();
}

void deleteStuInfo::on_Delete_Button_clicked(){
    if(ui->tableWidget->rowCount() == 0){
        QMessageBox::warning(this, tr("提醒"), tr("暂无学生信息！"), QMessageBox::Ok);
    }
    else{
        for(QVector<StudentInfo>::iterator it = stuInfo.begin(); it != stuInfo.end(); it++){
            if(it->getName() == stu_name && it->getID() == stu_id){
                stuInfo.erase(it);
                QMessageBox::about(NULL, tr("反馈"), tr("删除成功！"));
            }
        }
        ui->tableWidget->clear();
        QFile file("student.txt");
        // QIODevice::Truncate表示将从头重新写一遍该文件
        file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate);
        if(!file.isOpen()){
            QMessageBox::warning(this, tr("提醒"), tr("学生信息文件无法正常打开！"), QMessageBox::Ok);
            return;
        }
        // 将Vector容器中的学生数据写入文件当中
        QTextStream outp(&file);
        for(int i = 0; i < stuInfo.size(); i++){
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge()
                 << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC()
                 << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
    }
}

deleteStuInfo::~deleteStuInfo()
{
    delete ui;
}
