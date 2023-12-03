#ifndef WRITER_H
#define WRITER_H

#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <command.h>

class Writer : public QObject
{
    Q_OBJECT
public:
    Writer();
    ~Writer() {}

    void writeCommand(Command command);
    void writeFilename(QString filename);
    void writeMark(QString mark);
    void clearDoc();

private:
    QString filePath;

signals:
    void status(int row, int status, QString error);
};

#endif // WRITER_H
