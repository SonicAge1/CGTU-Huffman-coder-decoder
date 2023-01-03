#include <iostream>
#include <stdio.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"
#include "QDir"
#include "QStringList"

typedef struct Node{
    char value;
    int weight;
    int parent;
    int Lchild,Rchild;
}*Tree;

typedef char **Code;

bool discover_Mistake_char(QString treedir){
    char* get_All_Char(char* Str);

    QFile file(treedir);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line = in.readLine();      //整行读取树中字符


    bool re = false;
    for(int i = 0;i<line.length();i++){
        for(int j = 0;j<CharList.length();j++){
            if(line[i] == CharList[j]){
                re = true;
                break;
            }
        }
        if(re == false){
            return false;
        }else{
            re = false;
            break;
        }
    }
    return true;
}

bool discover_Mistake_code(QString treedir){
    Tree HT;
    int len;
    QByteArray ba;
    char*  ch;
    QFile file(treedir);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList treeValu;
    QStringList Valu,weight,par,lc,rc;

    //从文件读入数据构建hfmtree
    while(!file.atEnd()){
        treeValu.append(file.readLine());
    }
    Valu = treeValu[0].split("/");
    weight = treeValu[1].split("/");
    par = treeValu[2].split("/");
    lc = treeValu[3].split("/");
    rc = treeValu[4].split("/");
    len = Valu.length();//总结点数
    HT = (Tree)calloc(len, sizeof(Node)); //建立Node
    for (int i = 1; i < len; i++)
    {
        ba = Valu[i-1].toLatin1();
        ch=ba.data();

        HT[i].weight = weight[i - 1].toInt(); //赋权值给n个叶子结点
        HT[i].value = ch[0];
        HT[i].parent = par[i-1].toInt();
        HT[i].Lchild = lc[i-1].toInt();
        HT[i].Rchild = rc[i-1].toInt();
        printf("HT[%d] %c %d %d %d %d\n",i,HT[i].value,HT[i].weight,HT[i].parent,HT[i].Lchild,HT[i].Rchild);
    }

    //构建完毕开始编码
    Code HC;
    len = len - 1;
    HC = (Code)malloc(sizeof(char*)*(len + 1));
    char* code = (char*)malloc(sizeof(char)*len);
    code[len - 1] = '\0';
    for (int i = 1; i <= len; i++){
        int pointer = len - 1;//指针指向最后
        int c = i;
        int par = HT[c].parent;
        while (par){ //父节点不为空就循环
            if (HT[par].Lchild == c){ //左0右1
                pointer--;
                code[pointer] = '0';
            }else{
                pointer--;
                code[pointer] = '1';
            }
            c = par;
            par = HT[c].parent;
        }
        HC[i] = (char*)malloc(sizeof(char)*(len - pointer));
        qstrcpy(HC[i], &code[pointer]);
    }
    free(code);


    QFile file2(filedir);
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inn(&file2);
    QString fc = inn.readLine();
    QByteArray ba1 = fc.toLatin1();
    char* filecode = ba1.data();//file编码
    QStringList standercode;//标准编码
    for(int i = 0;i<len;i++){
        standercode.append(HC[i+1]);
    }
    QString com;
    int i = 0;
    bool last = false;;
    int fclen = strlen(filecode);
    int hclen = (standercode.length()+1)/2;
    while(i<fclen){
        for(int j = 0;j<hclen;j++){
            int sclen = standercode[j].length();
            com.clear();
            for(int k = i;k<sclen+i;k++){
                com.append(filecode[k]);
            }
            if(standercode[j].compare(com)==0){
                i = i + standercode[j].length();
                j = -1;
                com.clear();
                last = true;
            }
            if(last == false && j == hclen-1){
                free(HC);
                free(HT);
                return false;
            }
        }
    }
    free(HC);
    free(HT);
    return true;
}

int* get_Node_Weight(char* allCharArr, char* Str) {
    static int weightList[99] = {'\0'};
    int allCharArrLen = 0;int StrLen = 0;
    int i = 0;int j = 0;
    while(allCharArr[i] !=  '\0'){
        i++;
        allCharArrLen++;
    }
    while(Str[j] !=  '\0'){
        j++;
        StrLen++;
    }

    for (int i = 0; i < allCharArrLen; i++) {
        weightList[i] = 0;
        for (int j = 0; j < StrLen; j++) {
            if (Str[j] == allCharArr[i]) {
                weightList[i]++;
            }
        }
    }
    return weightList;
}

char* get_All_Char(char* Str) {
    char AllCharList[99] = { '\0' };
    char* allCharList = AllCharList;
    int strLen = 0, allCharLen = 0,utfCode = 0,counter = 0,trueLen = 0;
    char aChar;
    bool var = false;

    while (Str[trueLen] != '\0') {//原字符串长度
        utfCode = int (Str[trueLen]);
        if(utfCode < 0  && counter != 2){
            counter ++;
        }else if(utfCode >=0){
            strLen++;
        }else if(utfCode < 0  && counter == 2){
            strLen++;
            counter = 0;
        }
        trueLen++;
    }

    /*while (allCharList[allCharLen] != '\0') {
        allCharLen++;//charset长度
    }*/

    for (int i = 0; i < trueLen; i++) {
        aChar = Str[i];

        for (int j = 0; j < allCharLen; j++) {
            if (aChar == allCharList[j]) {
                var = true;
            }
        }

        if (!var) {
            allCharList[allCharLen] = aChar;
            allCharLen++;
        }
        else {
            var = false;
        }
    }
    return allCharList;
}

void twoMin(Tree& HT, int n, int& min1, int& min2){
    int minNum;

    for(int i = 1;i<=n;i++){
        if(HT[i].parent == 0){
            minNum = i;
            break;
        }
    }
    for(int i = minNum+1;i<=n;i++){
        if(HT[i].parent == 0 && HT[i].weight < HT[minNum].weight){
            minNum = i;
        }
    }
    min1 = minNum;

    for(int i = 1;i<=n;i++){
        if(HT[i].parent == 0 && i != min1){
            minNum = i;
            break;
        }
    }
    for(int i = minNum+1; i<=n; i++){
        if(HT[i].parent == 0 && i != min1 && HT[i].weight < HT[minNum].weight){
            minNum = i;
        }
    }
    min2 = minNum;
    //printf("min1:%d,min2:%d\n",min1,min2);
}

void BuildTree(Tree& HT, int* w, int n, char*  charArr)
{
    //double time_Start = (double)clock();
    QString str(charArr);
    int m = 2 * n - 1; //总结点数
    HT = (Tree)calloc(m + 1, sizeof(Node)); //建立Node
    QByteArray ba = str.toLatin1();
    charArr=ba.data();
    //qDebug()<<charArr;
    for (int i = 1; i <= n; i++)
    {
        HT[i].weight = w[i - 1]; //赋权值给n个叶子结点
        HT[i].value = charArr[i-1];
        printf("HT[%d] %d %c\n",i,HT[i].weight,HT[i].value);
    }
    for (int i = n + 1; i <= m; i++) //构建哈夫曼树
    {
        int min1, min2;
        twoMin(HT, i - 1, min1, min2); //找最小
        //printf("min1=%d\nmin2=%d\n",min1,min2);
        //////////////////////////////
        HT[i].weight = HT[min1].weight + HT[min2].weight;//组成新节点
        //printf("HT[%d].weight:%d=HT[%d].weight:%d+HT[%d].weight:%d\n",i,HT[i].weight,min1,HT[min1].weight,min2,HT[min2].weight);
        HT[min1].parent = i;
        HT[min2].parent = i;
        HT[i].Lchild = min1;
        HT[i].Rchild = min2;
    }
    /*double time_End = (double)clock();
    qDebug()<<(time_End - time_Start)/1000.0<<"s";
    printf("value   weight   par  lc  rc\n");*/
    for (int i = 1; i <= m; i++)
    {
        printf("%c   %d   %d   %d   %d\n", HT[i].value, HT[i].weight, HT[i].parent, HT[i].Lchild, HT[i].Rchild);
    }
    printf("\n");

    //创建文件储存hfm树
    QString path = QCoreApplication::applicationDirPath();
    QString createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
    QString fileName;// = path + "/hfmtree/" + createTime + ".txt";
    QStringList list = path.split('/');
    for(int i = 0;i<list.length()-1;i++){
        fileName = fileName + list[i] + "/";
    }
    fileName = fileName + "untitled/hfmtree/" + createTime + ".txt";
    qDebug()<<fileName;


    /*QByteArray ba(fileName.toLatin1());
    std::cout << ba.data();*/

    QFile file(fileName);
    QString in;
    if(file.exists())
    {
        printf("创建失败");
    }else{
        file.open(QFile::WriteOnly|QFile::Text);
        printf("创建成功");//按照一定格式写入哈夫曼树
        for (int i = 1; i <= m; i++)
        {
            if(HT[i].value == NULL){
                in.append(" ");
                in.append("/");
            }else{
                in.append(HT[i].value);
                in.append("/");
            }
        }
        in.append("\n");
        file.write(in.toUtf8().data());
        in.clear();

        for(int i = 1;i<=m;i++){
            in.append(QString::number(HT[i].weight));
            in.append("/");
        }
        in.append("\n");
        file.write(in.toUtf8().data());
        in.clear();

        for(int i = 1;i<=m;i++){
            in.append(QString::number(HT[i].parent));
            in.append("/");
        }
        in.append("\n");
        file.write(in.toUtf8().data());
        in.clear();

        for(int i = 1;i<=m;i++){
            in.append(QString::number(HT[i].Lchild));
            in.append("/");
        }
        in.append("\n");
        file.write(in.toUtf8().data());
        in.clear();

        for(int i = 1;i<=m;i++){
            in.append(QString::number(HT[i].Rchild));
            in.append("/");
        }
        in.append("\n");
        file.write(in.toUtf8().data());
        in.clear();
        file.close();
    }
    treedir = fileName;
    free(HT);

}

void create_tree(char*  charArr,int* weightArr){
    int n = strlen(charArr);
    int* w = weightArr;
    Tree HT;
    BuildTree(HT, w, n, charArr);//构建哈夫曼树
}

void create_code(bool var){
    Tree HT;
    int len;
    QByteArray ba;
    char*  ch;
    QFile file(treedir);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList treeValu;
    QStringList Valu,weight,par,lc,rc;

    //从文件读入数据构建hfmtree
    while(!file.atEnd()){
        treeValu.append(file.readLine());
    }
    Valu = treeValu[0].split("/");
    weight = treeValu[1].split("/");
    par = treeValu[2].split("/");
    lc = treeValu[3].split("/");
    rc = treeValu[4].split("/");
    len = Valu.length();//总结点数
    HT = (Tree)calloc(len, sizeof(Node)); //建立Node
    for (int i = 1; i < len; i++)
    {
        ba = Valu[i-1].toLatin1();
        ch=ba.data();

        HT[i].weight = weight[i - 1].toInt(); //赋权值给n个叶子结点
        HT[i].value = ch[0];
        HT[i].parent = par[i-1].toInt();
        HT[i].Lchild = lc[i-1].toInt();
        HT[i].Rchild = rc[i-1].toInt();
        printf("HT[%d] %c %d %d %d %d\n",i,HT[i].value,HT[i].weight,HT[i].parent,HT[i].Lchild,HT[i].Rchild);
    }

    //构建完毕开始编码
    Code HC;
    len = len - 1;
    HC = (Code)malloc(sizeof(char*)*(len + 1));
    char* code = (char*)malloc(sizeof(char)*len);
    code[len - 1] = '\0';
    for (int i = 1; i <= len; i++){
        int pointer = len - 1;//指针指向最后
        int c = i;
        int par = HT[c].parent;
        while (par){ //父节点不为空就循环
            if (HT[par].Lchild == c){ //左0右1
                pointer--;
                code[pointer] = '0';
            }else{
                pointer--;
                code[pointer] = '1';
            }
            c = par;
            par = HT[c].parent;//确定父节点
        }
        HC[i] = (char*)malloc(sizeof(char)*(len - pointer));
        qstrcpy(HC[i], &code[pointer]);
    }
    free(code);

    for (int i = 1; i < len; i++){
        int l = HT[i].value;
        if(l == 32){
            break;
        }
        ch[0] = HT[i].value;
        QString str = QString::fromUtf8(ch);
        //MainWindow::mutualUi->on_textBrowser_append("数据" + str + "的编码为:"+ HC[i] +"\n" );
    }

    if(var){//用户选择编码,以文件形式储存
        QString iii;
        QString path = QCoreApplication::applicationDirPath();
        QString createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
        QString fileName = path + "/codefile/" + createTime + ".txt";
        /*QStringList list = path.split('/');
        for(int i = 0;i<list.length()-1;i++){
            fileName = fileName + list[i] + "/";
        }
        fileName = fileName + "untitled/codefile/" + createTime + ".txt";*/


        QFile file1(fileName);
        if(file1.exists()){
            printf("创建失败\n");
        }else{//读取文件并写入编码
            file1.open(QFile::WriteOnly|QFile::Text);
            for(int i = 0;i<strlen(charArr);i++){
                for(int j = 0;j<len+1;j++){
                   if(HT[j].value == charArr[i]){
                        printf("%s",HC[j]);
                        iii.append(HC[j]);
                        file1.write(iii.toUtf8().data());
                        iii.clear();
                        break;
                    }
                }
            }
        }
        file1.close();
    }else{//用户选择译码,以文件形式储存
        QFile file2(filedir);
        file2.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream inn(&file2);
        QString fc = inn.readLine();
        QByteArray ba1 = fc.toLatin1();
        char* filecode = ba1.data();//file编码
        QStringList standercode;//标准编码
        for(int i = 0;i<len;i++){
            standercode.append(HC[i+1]);
        }file2.close();
        //获取路径
        QString path = QCoreApplication::applicationDirPath();
        QString createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
        QString fileName = path + "/textfile/" + createTime + ".txt";
        /*QStringList list = path.split('/');
        for(int i = 0;i<list.length()-1;i++){
            fileName = fileName + list[i] + "/";
        }
        fileName = fileName + "untitled/textfile/" + createTime + ".txt";*/
        //创建文件
        QFile file1(fileName);

        if(file1.exists()){
            printf("创建失败\n");
        }else{//译码
            file1.open(QFile::WriteOnly|QFile::Text);
            for(int i = 0;i<len;i++){
                standercode.append(HC[i+1]);
            }
            QString com;
            QString iii;
            int i = 0;
            int fclen = strlen(filecode);//文件编码长度
            int hclen = (standercode.length()+1)/2;//树编码个数
            while(i<fclen){
                for(int j = 0;j<hclen;j++){//遍历每个编码
                    int sclen = standercode[j].length();//标准编码长度,用于决定如对次数
                    com.clear();
                    for(int k = i;k<sclen+i;k++){//入队
                        com.append(filecode[k]);
                    }
                    if(standercode[j].compare(com)==0){//判断队中编码是否等于标准编码
                        i = i + standercode[j].length();

                        printf("%c",HT[j+1].value);
                        iii.append(HT[j+1].value);//写入编码
                        file1.write(iii.toUtf8());
                        iii.clear();

                        j = -1;
                        com.clear();
                        if(i == fclen){//到达末尾跳出
                            break;
                        }
                    }
                }
            }
        }
        file1.close();
    }
    free(HC);
    free(HT);
}



