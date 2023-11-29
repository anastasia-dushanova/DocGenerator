#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

#include <QObject>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

class Documentation : public QObject
{
    Q_OBJECT
public:
    Documentation();
    ~Documentation() {}

    void setListFiles(QStringList list);

private:
    enum class Status : int{
        Status_added = 1,
        Status_processing,
        Status_ready,
        Status_error,
        Status_done
    };

    QStringList listFiles;

    void generateDocumentation();

    QString getPartOfComment(QByteArray array, QString separator);

signals:
    void progress(int doneCount);
    void changeStatus(int row, int status);
};

#endif // DOCUMENTATION_H
