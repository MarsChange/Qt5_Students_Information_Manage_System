#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

void Dialog::on_Enter_Button_clicked(){
    QString usr_name = ui->lineEdit_usr->text();
    QString usr_pwd = ui->lineEdit_pwd->text();
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    if(usr_name == "admin" && usr_pwd == "123"){
        accept();
    }
    else{
        QMessageBox::warning(this, tr("提醒"), tr("账号或密码输入不正确，请重新输入！"), QMessageBox::Ok);
    }
}

Dialog::~Dialog()
{
    delete ui;
}
