#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_start->setDisabled(true);
    doc = new Documentation();
    connect(doc, SIGNAL(progress(int)), this, SLOT(slotProgressChanged(int)));
    connect(doc, SIGNAL(changeStatus(int, int)), this, SLOT(slotChangeStatus(int, int)));
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

    inputOnTableView(selectedFiles);

}

void MainWindow::inputOnTableView(QStringList list){

    ui->tableWidget->setRowCount(list.size());
    qDebug() << "outputOnTableView(QStringList list)";
    for(int i = 0; i < list.size(); ++i){
        QTableWidgetItem* item_name = new QTableWidgetItem(QFileInfo(list[i]).fileName());
        ui->tableWidget->setItem(i, 0, item_name);
        slotChangeStatus(i, 1);
    }

    ui->pushButton_start->setDisabled(false);

}

void MainWindow::slotChangeStatus(int row, int status){
    switch(status){
    case static_cast<int>(Status::Status_added) :{
        QTableWidgetItem* item = new QTableWidgetItem("Добавлено");
        ui->tableWidget->setItem(row, 1, item);
        break;
    }
    case static_cast<int>(Status::Status_ready) : {
        QTableWidgetItem* item = ui->tableWidget->item(row, 1);
        item->setText("Готово");
        item->setBackgroundColor(Qt::green);
        break;
    }
    case static_cast<int>(Status::Status_processing) : {
        QTableWidgetItem* item = ui->tableWidget->item(row, 1);
        item->setText("Обработка...");
        item->setBackgroundColor(Qt::yellow);
        break;
    }
    case static_cast<int>(Status::Status_error) : {
        QTableWidgetItem* item = ui->tableWidget->item(row, 1);
        item->setText("Ошибка");
        item->setBackgroundColor(Qt::red);
        item->setTextColor(Qt::white);
        break;
    }
    case static_cast<int>(Status::Status_done) : {
        QMessageBox::information(this,
                                 "Готово",
                                 "Все файлы обработаны");
        break;
    }
    default:{
        QMessageBox::warning(this,
                             "Внимание",
                             "Неизвестная ошибка");
        break;
    }

    }


}

void MainWindow::slotProgressChanged(int doneCount){

    ui->progressBar->setValue(doneCount);
    ui->label_count->setText("["+QString::number(doneCount)+"/"+QString::number(doneCount) + "]");
}

void MainWindow::on_pushButton_start_clicked()
{
    qDebug() << "on_pushButton_start_clicked";
    ui->progressBar->setMaximum(selectedFiles.size());
    doc->setListFiles(selectedFiles);
}

