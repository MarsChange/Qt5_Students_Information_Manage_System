#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 新建窗口并命名窗口
    addstuInfo = new AddStuInfo;
    addstuInfo->setWindowTitle("添加学生信息");
    delStuInfo = new deleteStuInfo;
    delStuInfo->setWindowTitle("删除学生信息");
    searchInfo = new searchStuInfo;
    searchInfo->setWindowTitle("搜索学生信息");
    stackLayout = new QStackedLayout;

    // 将页面添加进stackLayout中
    stackLayout->addWidget(this);
    stackLayout->addWidget(addstuInfo);
    stackLayout->addWidget(searchInfo);
    stackLayout->addWidget(delStuInfo);

    setLayout(stackLayout);

    // 连接槽信号并接收按钮点击信号
    connect(this, &MainWindow::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(addstuInfo, &AddStuInfo::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(delStuInfo, &deleteStuInfo::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(searchInfo, &searchStuInfo::display, stackLayout, &QStackedLayout::setCurrentIndex);
}

// 读取txt文件中存储的学生信息
bool MainWindow::getStuInfo(QVector<StudentInfo> &allStuInfo){
    QFile file("student.txt");
    // 每次刷新列表时都清空容器一边避免重复添加学生信息
    allStuInfo.clear();
    file.open(QIODevice::ReadOnly|QIODevice::Text);         //以只读方式打开student.txt文件
    QTextStream inp(&file);
    if(!file.isOpen()){ //文件打开失败
        QMessageBox::warning(this, tr("提醒"), tr("学生信息文件无法正常打开！"), QMessageBox::Ok);
        return false;
    }
    while(!inp.atEnd()){    //读到文件结尾
        QString st_name, st_id, st_sex, st_major;
        int st_age, st_math1, st_math2, st_Cprog, st_ds;
        double st_gpoint;
        inp >> st_id >> st_name >> st_sex >> st_age >> st_major >> st_math1 >> st_math2 >> st_Cprog >> st_ds >> st_gpoint;
        allStuInfo.push_back(StudentInfo(st_id, st_name, st_sex, st_major, st_age, st_math1, st_math2, st_Cprog, st_ds, st_gpoint));
        //调用之前声明的构造函数实例化一个StudentInfo对象并将其加入allStudentInfo
    }
    // 清除最后的空行数据
    allStuInfo.pop_back();
    file.close();
    return true;
}

// 快速排序（String类型）
void MainWindow::quick_sort_string(QVector<QString> &a, QVector<int> &index, int low, int high){
    if(low >= high) return;
    int i = low, temp_int;
    int j = high;
    QString key = a[low];
    QString temp;
    while(i < j){
        while(a[j] >= key && i < j){
            j--;
        }
        while(a[i] <= key && i < j){
            i++;
        }
        if(i < j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            // 记录下标变换
            temp_int = index[i];
            index[i] = index[j];
            index[j] = temp_int;
        }
    }
    a[low] = a[i];
    a[i] = key;
    temp_int = index[low];
    index[low] = index[i];
    index[i] = temp_int;
    quick_sort_string(a, index, low, i - 1);
    quick_sort_string(a, index, i + 1, high);
}

// 快速排序（int类型）
void MainWindow::quick_sort_int(QVector<int> &a, QVector<int> &index, int low, int high){
    if(low >= high) return;
    int i = low, temp_int;
    int j = high;
    int key = a[low];
    int temp;
    while(i < j){
        while(a[j] >= key && i < j){
            j--;
        }
        while(a[i] <= key && i < j){
            i++;
        }
        if(i < j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            // 记录下标变换
            temp_int = index[i];
            index[i] = index[j];
            index[j] = temp_int;
        }
    }
    a[low] = a[i];
    a[i] = key;
    temp_int = index[low];
    index[low] = index[i];
    index[i] = temp_int;
    quick_sort_int(a, index, low, i - 1);
    quick_sort_int(a, index, i + 1, high);
}

// 快速排序（double类型）
void MainWindow::quick_sort_double(QVector<double> &a, QVector<int> &index, int low, int high){
    if(low >= high) return;
    int i = low, temp_int;
    int j = high;
    double key = a[low];
    double temp;
    while(i < j){
        while(a[j] >= key && i < j){
            j--;
        }
        while(a[i] <= key && i < j){
            i++;
        }
        if(i < j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            // 记录下标变换
            temp_int = index[i];
            index[i] = index[j];
            index[j] = temp_int;
        }
    }
    a[low] = a[i];
    a[i] = key;
    temp_int = index[low];
    index[low] = index[i];
    index[i] = temp_int;
    quick_sort_double(a, index, low, i - 1);
    quick_sort_double(a, index, i + 1, high);
}

void MainWindow::on_Create_StuInfo_Button_clicked(){
    bool isOpenFile = getStuInfo(allStuInfo);
    if(isOpenFile){
        ui->isCreate_label->setText("已成功打开学生信息列表，可正常使用系统！");
        ui->Create_StuInfo_Button->setText("刷新学生信息列表");
    }
    // 初始化表头
    QStringList header;
    header<<"学号"<<"姓名"<<"性别"<<"年龄"<<"专业"<<"微积分1-1"<<"微积分1-2"<<"C语言程序设计"<<"数据结构"<<"绩点";
    ui->tableWidget->setColumnCount(header.size());                        // 设置表格的列数
    ui->tableWidget->setHorizontalHeaderLabels(header);                    // 设置水平头
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   // 设置表结构默认不可编辑

    // 将文件中已有的数据初始化到列表当中，若无任何学生信息，则保留表头初始化状态
    if(allStuInfo.empty()){
        ui->tableWidget->setRowCount(1);                                   // 设置初始化行数
        QMessageBox::warning(this, tr("提醒"), tr("暂无学生信息！"), QMessageBox::Ok);
    }
    else{
        ui->tableWidget->setRowCount(allStuInfo.size());
        for(int i = 0; i < allStuInfo.size(); i++){
            // 显示列表
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(allStuInfo[i].getID()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(allStuInfo[i].getName()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(allStuInfo[i].getSex()));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(allStuInfo[i].getAge())));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(allStuInfo[i].getMajor()));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(allStuInfo[i].getMath1())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(allStuInfo[i].getMath2())));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(allStuInfo[i].getC())));
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(allStuInfo[i].getDS())));
            ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(allStuInfo[i].getGpoint())));
        }
    }
}

// 打开添加学生信息页面
void MainWindow::on_Add_StuInfo_Button_clicked(){
    emit display(1);
}
// 打开查询学生信息页面
void MainWindow::on_Search_StuInfo_Button_clicked(){
    emit display(2);
}
// 打开删除学生信息页面
void MainWindow::on_Delete_StuInfo_Button_clicked(){
    emit display(3);
}

void MainWindow::on_Sort_Button_clicked(){
    getStuInfo(allStuInfo);
    QVector<QString> a_string;
    QVector<int> a_int;
    QVector<double> a_double;
    QVector<int> index;
    QVector<StudentInfo> stuInfo;
    a_string.clear();
    a_int.clear();
    a_double.clear();
    index.clear();
    // 按学号排序
    if(ui->comboBox->currentIndex() == 0){
        for (int i = 0; i < allStuInfo.size(); i++) {
            a_string.push_back(allStuInfo[i].getID());
            index.push_back(i);
        }
        quick_sort_string(a_string, index, 0, a_string.size()-1);  // 快速排序
        for(int i = 0; i < allStuInfo.size(); i++){
            stuInfo.push_back(allStuInfo[index[i]]);  // 将排序好的学生信息按照排序好的对应的下标顺序存储入新的Vector容器中
        }
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
            // 将排序好的学生信息写入文件
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
        display_table(stuInfo);  // 将排序好的学生信息显示在tableWidget上
    }
    // 按微积分1-1成绩排序
    else if(ui->comboBox->currentIndex() == 1){
        for (int i = 0; i < allStuInfo.size(); i++) {
            a_int.push_back(allStuInfo[i].getMath1());
            index.push_back(i);
        }
        quick_sort_int(a_int, index, 0, a_int.size()-1);
        for(int i = 0; i < allStuInfo.size(); i++){
            stuInfo.push_back(allStuInfo[index[i]]);
        }
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
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
        display_table(stuInfo);
    }
    // 按微积分1-2成绩排序
    else if(ui->comboBox->currentIndex() == 2){
        for (int i = 0; i < allStuInfo.size(); i++) {
            a_int.push_back(allStuInfo[i].getMath2());
            index.push_back(i);
        }
        quick_sort_int(a_int, index, 0, a_int.size()-1);
        for(int i = 0; i < allStuInfo.size(); i++){
            stuInfo.push_back(allStuInfo[index[i]]);
        }
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
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
        display_table(stuInfo);
    }
    // 按C语言成绩排序
    else if(ui->comboBox->currentIndex() == 3){
        for (int i = 0; i < allStuInfo.size(); i++) {
            a_int.push_back(allStuInfo[i].getC());
            index.push_back(i);
        }
        quick_sort_int(a_int, index, 0, a_int.size()-1);
        for(int i = 0; i < allStuInfo.size(); i++){
            stuInfo.push_back(allStuInfo[index[i]]);
        }
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
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
        display_table(stuInfo);
    }
    // 按数据结构成绩排序
    else if(ui->comboBox->currentIndex() == 4){
        for (int i = 0; i < allStuInfo.size(); i++) {
            a_int.push_back(allStuInfo[i].getDS());
            index.push_back(i);
        }
        quick_sort_int(a_int, index, 0, a_int.size()-1);
        for(int i = 0; i < allStuInfo.size(); i++){
            stuInfo.push_back(allStuInfo[index[i]]);
        }
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
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
        display_table(stuInfo);
    }
    // 按绩点排序
    else if(ui->comboBox->currentIndex() == 5){
        for (int i = 0; i < allStuInfo.size(); i++) {
            a_double.push_back(allStuInfo[i].getGpoint());
            index.push_back(i);
        }
        quick_sort_double(a_double, index, 0, a_double.size()-1);
        for(int i = 0; i < allStuInfo.size(); i++){
            stuInfo.push_back(allStuInfo[index[i]]);
        }
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
            outp << stuInfo[i].getID() << " " << stuInfo[i].getName() << " " << stuInfo[i].getSex() << " " << stuInfo[i].getAge() << " " << stuInfo[i].getMajor() << " " << stuInfo[i].getMath1() << " " << stuInfo[i].getMath2() << " " << stuInfo[i].getC() << " " << stuInfo[i].getDS() << " " << stuInfo[i].getGpoint() << "\n" << endl;
        }
        file.close();
        display_table(stuInfo);
    }
}

// 将学生信息放入列表中显示出来
void MainWindow::display_table(QVector<StudentInfo> stuInfo){
    // 初始化表头
    QStringList header;
    header<<"学号"<<"姓名"<<"性别"<<"年龄"<<"专业"<<"微积分1-1"<<"微积分1-2"<<"C语言程序设计"<<"数据结构"<<"绩点";
    ui->tableWidget->setColumnCount(header.size());                        // 设置表格的列数
    ui->tableWidget->setHorizontalHeaderLabels(header);                    // 设置水平头
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   // 设置表结构默认不可编辑
    ui->tableWidget->setRowCount(allStuInfo.size());
    for(int i = 0; i < stuInfo.size(); i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(stuInfo[i].getID()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(stuInfo[i].getName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(stuInfo[i].getSex()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(stuInfo[i].getAge())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(stuInfo[i].getMajor()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(stuInfo[i].getMath1())));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(stuInfo[i].getMath2())));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(stuInfo[i].getC())));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(stuInfo[i].getDS())));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(stuInfo[i].getGpoint())));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

