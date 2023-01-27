#include "addstuinfo.h"
#include "mainwindow.h"
#include "ui_addstuinfo.h"

AddStuInfo::AddStuInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddStuInfo)
{
    ui->setupUi(this);
}

// 点击返回按钮返回主菜单
void AddStuInfo::on_Return_Button_clicked(){
    emit display(0);
}

// 点击插入数据按钮保存学生信息，默认为按顺序存储
void AddStuInfo::on_Upload_Button_clicked(){
    // 将输入的数据存储在变量当中
    stu_id = ui->lineEdit_id->text();
    stu_name = ui->lineEdit_name->text();
    stu_age = ui->lineEdit_age->text().toInt();
    stu_sex =  ui->lineEdit_sex->text();
    stu_major = ui->lineEdit_major->text();
    math_1 = ui->lineEdit_math1->text().toInt();
    scores.push_back(math_1);
    math_2 = ui->lineEdit_math2->text().toInt();
    scores.push_back(math_2);
    Cprog = ui->lineEdit_C->text().toInt();
    scores.push_back(Cprog);
    dataStruc = ui->lineEdit_ds->text().toInt();
    scores.push_back(dataStruc);
    // 提醒不能存在数据空项
    if(ui->lineEdit_C->text() == "" || ui->lineEdit_ds->text() == ""
            || ui->lineEdit_id->text() == "" || ui->lineEdit_age->text() == ""
            || ui->lineEdit_sex->text() == "" || ui->lineEdit_name->text() == ""
            || ui->lineEdit_math1->text() == "" || ui->lineEdit_math2->text() == ""){
        //插入的数据都不能为空，否则在读取文件时会出现问题。
        QMessageBox::warning(this, tr("提醒"), tr("输入的数据存在空项！"), QMessageBox::Ok);
    }
    QFile file("student.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
    if(!file.isOpen()){
        QMessageBox::warning(this, tr("提醒"), tr("学生信息文件无法正常打开！"), QMessageBox::Ok);
        return;
    }
    // 计算加权平均绩点
    calculate_Gpoints(scores, gpoint);
    // 写入文件
    QTextStream outp(&file);
    outp << stu_id << " " << stu_name << " " << stu_sex << " " << stu_age << " " << stu_major << " " << math_1 << " " << math_2 << " " << Cprog << " " << dataStruc << " " << gpoint << "\n" << endl;
    file.close();
    QMessageBox::about(NULL, "反馈", "插入成功！");
    // 输入框已输入的数据清空
    scores.clear();
    ui->lineEdit_C->clear();
    ui->lineEdit_ds->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_age->clear();
    ui->lineEdit_sex->clear();
    ui->lineEdit_major->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_math1->clear();
    ui->lineEdit_math2->clear();
}

// 点击指定行插入数据按钮即可在指定行数处插入新输入的数据
void AddStuInfo::on_Specify_Upload_Button_clicked(){
    stu_id = ui->lineEdit_id->text();
    stu_name = ui->lineEdit_name->text();
    stu_age = ui->lineEdit_age->text().toInt();
    stu_sex =  ui->lineEdit_sex->text();
    stu_major = ui->lineEdit_major->text();
    math_1 = ui->lineEdit_math1->text().toInt();
    scores.push_back(math_1);
    math_2 = ui->lineEdit_math2->text().toInt();
    scores.push_back(math_2);
    Cprog = ui->lineEdit_C->text().toInt();
    scores.push_back(Cprog);
    dataStruc = ui->lineEdit_ds->text().toInt();
    scores.push_back(dataStruc);
    int specify = ui->lineEdit_Specify->text().toInt();

    // 计算加权平均绩点
    calculate_Gpoints(scores, gpoint);

    if(ui->lineEdit_C->text() == "" || ui->lineEdit_ds->text() == ""
            || ui->lineEdit_id->text() == "" || ui->lineEdit_age->text() == ""
            || ui->lineEdit_sex->text() == "" || ui->lineEdit_name->text() == ""
            || ui->lineEdit_math1->text() == "" || ui->lineEdit_math2->text() == ""
            || ui->lineEdit_Specify->text() == ""){
        //插入的数据都不能为空，否则在读取文件时会出现问题。
        QMessageBox::warning(this, tr("提醒"), tr("输入的数据存在空项！"), QMessageBox::Ok);
    }
    // 声明Vector容器存储文件中已有的学生信息，然后实例化主窗口，使用主窗口类中的获取学生信息到Vector容器的函数
    // 在Vector容器中将新数据插入在指定位置当中
    QVector<StudentInfo> stuInfo;
    MainWindow w;
    w.getStuInfo(stuInfo);
    stuInfo.insert(stuInfo.begin() + specify - 1,
                   StudentInfo(stu_id, stu_name, stu_sex, stu_major,
                               stu_age, math_1, math_2, Cprog, dataStruc, gpoint));

    QMessageBox::about(NULL, "反馈", "插入成功！");

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
        outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex()
             << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1()
             << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " "
             << stuInfo[i].getGpoint() << "\n" << endl;
    }
    file.close();

    // 输入的数据清空
    scores.clear();
    ui->lineEdit_C->clear();
    ui->lineEdit_ds->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_age->clear();
    ui->lineEdit_sex->clear();
    ui->lineEdit_major->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_math1->clear();
    ui->lineEdit_math2->clear();
    ui->lineEdit_Specify->clear();
}

/*
 * 函数功能：计算加权平均绩点
 * 微积分1-1对应5学分，微积分1-2对应4学分，C语言对应3学分，数据结构对应2学分
 * 单科成绩在60到69分给予1.0绩点，在70到79分给予2.0绩点，80到89给予3.0绩点，90分及以上给予4.0绩点
*/
void AddStuInfo::calculate_Gpoints(QVector<int> s, double &g){
    // 记录单科绩点
    QVector<double> a;
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 60 && s[i] < 70){
            a.push_back(1.0);
        }
        else if(s[i] >= 70 && s[i] < 80){
            a.push_back(2.0);
        }
        else if(s[i] >= 80 && s[i] < 90){
            a.push_back(3.0);
        }
        else if(s[i] >= 90 && s[i] <= 100){
            a.push_back(4.0);
        }
        else{
            a.push_back(0.0);
        }
    }
    g = (a[0]*5 + a[1]*4 + a[2]*3 + a[3]*2) / 14;
}

AddStuInfo::~AddStuInfo()
{
    delete ui;
}
