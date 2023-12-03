#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

#include <QObject>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <command.h>
#include <writer.h>

class Documentation : public QObject
{
    Q_OBJECT
public:
    Documentation();
    ~Documentation();

    void setListFiles(QStringList list);

    Writer* getWriter() { return writer;}

private:
    enum class Status : int{
        Status_added = 1,
        Status_processing,
        Status_ready,
        Status_error,
        Status_done
    };

    QStringList listFiles;

    Writer* writer;

    void generateDocumentation();

    QString getPartOfComment(QByteArray array, QString separator);

    void wirteDoc();

signals:
    void progress(int doneCount);
    void changeStatus(int row, int status, QString error = QString());
};

#endif // DOCUMENTATION_H
