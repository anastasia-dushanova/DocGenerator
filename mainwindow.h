#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
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

    void slotProgressChanged(int doneCount);

    void slotChangeStatus(int row, int status);

private:
    Ui::MainWindow *ui;
    Documentation* doc;

    enum class Status : int{
        Status_added = 1,
        Status_processing,
        Status_ready,
        Status_error,
        Status_done
    };

    QStringList selectedFiles;

    void inputOnTableView(QStringList list);


};
#endif // MAINWINDOW_H
