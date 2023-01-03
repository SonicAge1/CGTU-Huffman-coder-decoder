#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QString treedir;
extern QString filedir;
extern char* charArr;
extern QString CharList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*char* charArr;
    int* weightArr;*/
    //static MainWindow *mutualUi;

public slots:

    void on_choseFile_clicked();

    void on_code_clicked();

    void on_decod_clicked();

    void on_OK_clicked();

    void on_textBrowser_append(QString content);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
