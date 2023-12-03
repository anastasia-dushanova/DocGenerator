#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>

class Command
{
public:
    Command();
    ~Command(){}

    void setDescription(QString desc) { this->description = desc; }
    void setVersion(QString ver) { this->version = ver; }
    void setDate(QString date) { this->date = date; }
    void setMethod(QString method) { this->method = method; }
    void setMember(QPair<QString, QString> member) { this->member = member; }
    void setClassName(QStringList className) { this->className = className; }
    void setReturnValue(QPair<QString, QString> returnValue) { this->returnValue = returnValue; }
    void setParams(QList<QPair<QString, QString>> params) { this->params = params; }

    QString getDescription() { return description;}
    QString getVersion() { return version;}
    QString getDate() { return date;}
    QString getMethod() { return method;}
    QPair<QString, QString> getMember() { return member;}
    QStringList getClassName() { return className;}
    QPair<QString, QString> getReturnValue() { return returnValue;}
    QList<QPair<QString, QString>> getParams() { return params;}

private:
    QString description;
    QString version;
    QString date;
    QString method;
    QPair<QString, QString> member;
    QStringList className;
    QPair<QString, QString> returnValue;
    QList<QPair<QString, QString>> params;
};

#endif // COMMAND_H
