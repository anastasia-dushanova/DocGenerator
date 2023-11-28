#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_start->setDisabled(true);
    doc = new Documentation();
    connect(doc, SIGNAL(progress(int, int)), this, SLOT(progressChanged(int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_chooseFile_clicked()
{
    qDebug() << "on_pushButton_chooseFile_clicked";
    selectedFiles  = QFileDialog::getOpenFileNames(this, "Выберите файлы", "D:/univer/maga/Managment/Library", "");

    if(selectedFiles.isEmpty())
        return;

    outputOnTableView(selectedFiles);

}

void MainWindow::outputOnTableView(QStringList list){

    ui->tableWidget->setRowCount(list.size());
    qDebug() << "outputOnTableView(QStringList list)";
    for(int i = 0; i < list.size(); ++i){
        QTableWidgetItem* item_name = new QTableWidgetItem(QFileInfo(list[i]).fileName());
        QTableWidgetItem* item_status = new QTableWidgetItem("Добавлено");
        ui->tableWidget->setItem(i, 0, item_name);
        ui->tableWidget->setItem(i, 1, item_status);
    }

    ui->pushButton_start->setDisabled(false);

}

void MainWindow::progressChanged(int doneCount, int maxCount){
//    qDebug() << "changed";
    ui->progressBar->setMaximum(maxCount);
    ui->progressBar->setValue(doneCount);
    ui->label_count->setText("["+QString::number(doneCount)+"/"+QString::number(doneCount) + "]");
}

void MainWindow::on_pushButton_start_clicked()
{
    qDebug() << "on_pushButton_start_clicked";
    doc->setListFiles(selectedFiles);
}

