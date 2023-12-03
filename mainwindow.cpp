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
    connect(doc, SIGNAL(changeStatus(int, int, QString)), this, SLOT(slotChangeStatus(int, int, QString)));
    connect(doc->getWriter(), SIGNAL(status(int, int, QString)), this, SLOT(slotChangeStatus(int, int, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_chooseFile_clicked()
{
    qDebug() << "on_pushButton_chooseFile_clicked";
    if(!selectedFiles.isEmpty())
        selectedFiles.clear();

    selectedFiles  = QFileDialog::getOpenFileNames(this, "Выберите файлы", "D:/univer/maga/Managment/Library", "");

    if(selectedFiles.isEmpty())
        return;

    inputOnTableView(selectedFiles);

}

void MainWindow::inputOnTableView(QStringList list){

    qDebug() << "outputOnTableView(QStringList list)";
    ui->label_count->clear();
    ui->label_count->setText("[0/0]");
    ui->progressBar->reset();
    if(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(list.size());

    for(int i = 0; i < list.size(); ++i){
        QTableWidgetItem* item_name = new QTableWidgetItem(QFileInfo(list[i]).fileName());
        ui->tableWidget->setItem(i, 0, item_name);
        slotChangeStatus(i, 1);
    }

    ui->pushButton_start->setDisabled(false);

}

void MainWindow::slotChangeStatus(int row, int status, QString error){
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
        ui->label_status->setText(" Готово");
        makeDocx();
        break;
    }
    case static_cast<int>(Status::Status_fileError) : {
        QMessageBox::warning(this,
                             "Внимание",
                             error);
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

void MainWindow::makeDocx(){
    //pandoc -o output.docx -f markdown -t docx filename.md
//    pandoc documentation.md  --reference-doc=template.docx --output=output.docx --to=docx
//    pandoc -s --reference-doc=template.docx -o out.docx documentation.md
    QString ref = "--reference-doc="+QCoreApplication::applicationDirPath() + "/template.docx";
    QString md = QCoreApplication::applicationDirPath() + "/documentation.md";
    QString out = QCoreApplication::applicationDirPath() + "/documentation.docx";
    QProcess* process = new QProcess(this);
    process->start("pandoc", QStringList() << "-s"<<ref<<"-o"<<out<<md);
//    process->start("pandoc", QStringList() << "-o" << out << "-f" << "markdown"<<"-t"<<"docx"<<md);
//    process->waitForFinished(-1);
    if( !process->waitForStarted() || !process->waitForFinished() ) {
        return;
    }

    QString error = process->readAllStandardError();
    if(error.isEmpty())
        QMessageBox::information(this, "", "Файл с документацией готов");
    else
        QMessageBox::warning(this, "Внимание", "При создание документации возникла ошибка\n"+
                                               error);

//    qDebug() << process->readAllStandardError();
//    qDebug() << process->readAllStandardOutput();

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

