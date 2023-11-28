#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <documentation.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_chooseFile_clicked();

    void on_pushButton_start_clicked();

    void progressChanged(int doneCount, int maxCount);

private:
    Ui::MainWindow *ui;
    Documentation* doc;

    QStringList selectedFiles;

    void outputOnTableView(QStringList list);


};
#endif // MAINWINDOW_H
