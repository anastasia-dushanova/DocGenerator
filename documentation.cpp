#include "documentation.h"

Documentation::Documentation() { }

void Documentation::setListFiles(QStringList list){
    listFiles = list;
    writer = new Writer();
    generateDocumentation();
}

Documentation::~Documentation(){
    delete writer;
}

void Documentation::generateDocumentation(){
    qDebug() << "Documentation::generateDocumentation()";


    for(int i = 0; i < listFiles.size(); ++i){

        QFile file(listFiles[i]);
        writer->writeFilename(QFileInfo(listFiles[i]).fileName());

        if(!file.open(QIODevice::ReadOnly))
            qDebug() << "error";

        while(!file.atEnd()){
            QByteArray currentLine = file.readLine();
            QString nameSpace{""};

            if(currentLine.contains("\\namespace")){
                nameSpace = getPartOfComment(currentLine, "\\namespace");
                if(!nameSpace.isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Пространство имен ")<<nameSpace ;
            }

            if(currentLine.contains("\\brief")){
                Command command;

//                QString description{""};
//                QString version{""};
//                QString date{""};
//                QStringList params;
//                QString method{""};
//                QString member{""};
//                QString className{""};
//                QString returnValue{""};

//                description = getPartOfComment(currentLine, "\\brief");
                command.setDescription(getPartOfComment(currentLine, "\\brief"));

                QByteArray nextLine = file.readLine();

                if(nextLine.contains("\\version")){
                    command.setVersion(getPartOfComment(nextLine, "\\version"));
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\date")){
                    command.setDate(getPartOfComment(nextLine, "\\date"));
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\param")){

                    QStringList params;
                    params.append(getPartOfComment(nextLine, "\\param"));
                    nextLine = file.readLine();
                    while(nextLine.contains("\\param")){
                        params.append(getPartOfComment(nextLine, "\\param"));
                        nextLine = file.readLine();

                    }

                    command.setParams(params);
                    QByteArray method_byte = file.readLine();
                    if(method_byte.contains("*/"))
                        method_byte = file.readLine();

//                    method = QString(method_byte).remove("\r\n");
                    command.setMethod(QString(method_byte).remove("\r\n"));
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\return")){
                    command.setReturnValue(getPartOfComment(nextLine, "\\return"));
                    nextLine = file.readLine();
                }

                if(nextLine.contains("*/")){
                    nextLine = file.readLine();
                    if(nextLine.contains("()")){
                        command.setMethod(QString(nextLine).remove("\r\n"));
                    }else if(nextLine.contains("class")){

                        QString name = QString(nextLine).remove("\r\n");
                        QStringList list = name.split(":");
                        QString className = list[0].split(" ")[1];

                        if(list.size() == 1) break;
                        QString parent = list[1];
                        QStringList parentList = parent.split(",");

                        QStringList finalList;
                        finalList.append(className);
                        finalList.append(parentList);
                        command.setClassName(finalList);

                    }else {

                        command.setMember(QString(nextLine).remove("\r\n"));
                    }
                }

                if(!command.getDescription().isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Описание ")<<command.getDescription() ;
                if(!command.getVersion().isEmpty()) qDebug() <<QString::fromUtf8("Версия ")<<command.getVersion() ;
                if(!command.getDate().isEmpty()) qDebug() <<QString::fromUtf8("Дата ")<<command.getDate() ;
                if(!command.getClassName().isEmpty()) qDebug() <<QString::fromUtf8("Имя класса ")<<command.getClassName() ;
                if(!command.getParams().isEmpty()) qDebug() <<QString::fromUtf8("Аргументы метода ")<<command.getParams() ;
                if(!command.getReturnValue().isEmpty()) qDebug() <<QString::fromUtf8("возращаемый тип ")<<command.getReturnValue() ;
                if(!command.getMethod().isEmpty()) qDebug() <<QString::fromUtf8("Имя метода ")<<command.getMethod() ;
                if(!command.getMember().isEmpty()) qDebug() <<QString::fromUtf8("Имя поля ")<<command.getMember() ;
            }



            if(currentLine.contains("public:")){
                qDebug() << QString(currentLine).remove("\r\n");
            }
            if(currentLine.contains("private slots:")){
                qDebug() << QString(currentLine).remove("\r\n");
            }
            if(currentLine.contains("signals:")){
                qDebug() << QString(currentLine).remove("\r\n");
            }
            if(currentLine.contains("private:")){
                qDebug() << QString(currentLine).remove("\r\n");
            }

        }
        emit progress(i+1);
        emit changeStatus(i, int(Status::Status_ready));
        file.close();
    }

    emit changeStatus(0, int(Status::Status_done));

}

QString Documentation::getPartOfComment(QByteArray array, QString separator){
    QString array_str(array);
    QStringList list = array_str.split(separator);
    return list[1].remove("\r\n");
}
