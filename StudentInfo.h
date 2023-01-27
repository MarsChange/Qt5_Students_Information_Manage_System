#ifndef STUDENTINFO_H
#define STUDENTINFO_H
#include <QString>

class StudentInfo{
public:
    QString stu_name, stu_id, stu_sex, stu_major;
    int stu_age, math_1, math_2, Cprog, dataStruc;
    double gpoint;
    StudentInfo();
    StudentInfo(QString tid, QString tname, QString tsex, QString tmaj, int tage, int tmath1, int tmath2, int tCprog, int tDS, double tG){
        stu_name = tname;
        stu_id = tid;
        stu_sex = tsex;
        stu_major = tmaj;
        stu_age = tage;
        math_1 = tmath1;
        math_2 = tmath2;
        Cprog = tCprog;
        dataStruc = tDS;
        gpoint = tG;
    }
    // 返回学号
    QString getID(){
        return stu_id;
    }
    // 返回学生名字
    QString getName(){
        return stu_name;
    }
    // 返回学生性别
    QString getSex(){
        return stu_sex;
    }
    // 返回专业
    QString getMajor(){
        return stu_major;
    }
    // 返回年龄
    int getAge(){
        return stu_age;
    }
    // 返回微积分1-1成绩
    int getMath1(){
        return math_1;
    }
    // 返回微积分1-2成绩
    int getMath2(){
        return math_2;
    }
    // 返回C语言成绩
    int getC(){
        return Cprog;
    }
    // 返回数据结构成绩
    int getDS(){
        return dataStruc;
    }
    // 返回绩点
    double getGpoint(){
        return gpoint;
    }
};

#endif // STUDENTINFO_H
