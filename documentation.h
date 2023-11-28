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
    QStringList listFiles;

    void generateDocumentation();

signals:
    void progress(int doneCount, int maxCount);
};

#endif // DOCUMENTATION_H
