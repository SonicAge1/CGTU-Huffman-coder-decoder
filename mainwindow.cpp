#pragma execution_character_set("utf-8")
#include <iostream>
#include <stdio.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qdatetime.h"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <sys/time.h>

int* weightArr;
char CharArr[999] = {'\0'};
QString treedir;
QString filedir;
char* charArr;
QString CharList;

//MainWindow *MainWindow::mutualUi = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //mutualUi = this;
    on_textBrowser_append("欢迎使用哈夫曼编码译码器\n使用步骤：\n1.选择charSet构建哈夫曼树\n2.选择需要编码/译码的文件\n3."
                          "按键选择开始编码译码\n管理员将拥有管理哈夫曼树的限权,如果您是管理员请输入令牌登录...\n本编/译码器输出结果将保存在源文件"
                          "目录下的文件夹中...\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_code_clicked()
{
    void create_code(bool var);
    bool discover_Mistake_char(QString dir);

    QFile file(filedir);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        MainWindow::on_textBrowser_append("打开文件失败...\n");
    }
    QByteArray all = file.readAll();
    file.close();
    charArr = all.data();

    if(filedir == ""){
        MainWindow::on_textBrowser_append("您还没有选择任何文件...\n");
    }else{
        if(discover_Mistake_char(treedir) == false){//对比查重
            MainWindow::on_textBrowser_append("文件内容不符合编码规则，请重新选择...\n");
        }else{
            MainWindow::on_textBrowser_append("文件选择成功，开始编码...\n");
            create_code(true);
        }
        MainWindow::on_textBrowser_append("编码完毕，请移步codefile查看...\n");
    }
}


void MainWindow::on_choseFile_clicked()
{
    char* get_All_Char(char* Str);
    int* get_Node_Weight(char* allCharArr, char* Str);
    void create_tree(char*  charArr,int* weightArr);
    treedir.clear();

    FILE *fp;
    char con[9999];
    int i = 0;
    QString filter = "Text Files (*.txt)";
    treedir = QFileDialog::getOpenFileName(this,"请选择需要编译的文件","D:\\",filter);
    if(treedir == ""){
        MainWindow::on_textBrowser_append("打开文件失败\n");
    }else{
        QFile file(treedir);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            MainWindow::on_textBrowser_append("打开文件失败\n");
        }
        QByteArray all = file.readAll();
        file.close();
        QString allStr = QString(all);
        char* allstr = all.data();
        MainWindow::on_textBrowser_append("文件路径为:"+treedir+"\n");
        MainWindow::on_textBrowser_append("文件内容为:"+allStr+"\n");

        charArr = get_All_Char(allstr);//获取qstring全部字符
        weightArr = get_Node_Weight(charArr, allstr);//获取全部字符权重

        create_tree(charArr,weightArr);//建立hfm树


        charArr = NULL;
        weightArr = NULL;
        MainWindow::on_textBrowser_append("已成功建立哈夫曼哈夫曼树，请选择需要编/译码文件\n");
    }
}


void MainWindow::on_OK_clicked()
{
    QString edVal = ui->lineEdit->text();
    if(edVal != "123456"){
        MainWindow::on_textBrowser_append("令牌错误,请联系作者wx:liu1966488323\n");
    }else{
        MainWindow::on_textBrowser_append("热烈欢迎管理员,您可以管理哈夫曼树...\n");
        QString runPath = QCoreApplication::applicationDirPath();       //获取exe路径。
        QString filePath = "file:///" + runPath + "/hfmtree";
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
}


void MainWindow::on_decod_clicked()
{
    void create_code(bool var);
    bool discover_Mistake_code(QString treedir);

    QFile file(filedir);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        MainWindow::on_textBrowser_append("打开文件失败...\n");
    }
    QByteArray all = file.readAll();
    file.close();
    charArr = all.data();

    void create_tree(char*  charArr,int* weightArr);
    if(filedir == ""){
        MainWindow::on_textBrowser_append("您还没有选择任何文件...\n");
    }else{
        if(discover_Mistake_code(treedir) == false){//对比查重
            MainWindow::on_textBrowser_append("文件内容不符合编码规则，请重新选择...\n");
        }else{
            MainWindow::on_textBrowser_append("文件选择成功，开始译码...\n");
            create_code(false);
        }
        MainWindow::on_textBrowser_append("编码完毕，请移步textfile查看...\n");
    }
}


void MainWindow::on_textBrowser_append(QString content)
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");        //当前的小时   //当前的秒
    ui->textBrowser->insertPlainText(time+"----"+content);
}


void MainWindow::on_pushButton_clicked()
{
    char* get_All_Char(char* Str);
    int* get_Node_Weight(char* allCharArr, char* Str);

    filedir.clear();
    if(treedir == ""){
        MainWindow::on_textBrowser_append("您还没有建立hfmtree,请先建立hfmtree...\n");
    }else{
        FILE *fp;
        char con[9999];
        int i = 0;
        QString filter = "Text Files (*.txt)";
        filedir = QFileDialog::getOpenFileName(this,"请选择需要编/译码文件...","D:\\",filter);
        QFile file(filedir);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            MainWindow::on_textBrowser_append("打开文件失败...\n");
        }
        QByteArray all = file.readAll();
        file.close();
        QString allStr = QString(all);
        char* allstr = all.data();
        MainWindow::on_textBrowser_append("文件路径为:"+filedir+"\n");
        MainWindow::on_textBrowser_append("文件内容为:"+allStr+"\n");

        charArr = get_All_Char(allstr);//获取需要编译的文件的全部字符
        CharList = QString::fromUtf8(charArr);
    }
}

