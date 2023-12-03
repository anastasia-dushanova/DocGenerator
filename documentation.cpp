#include "documentation.h"

Documentation::Documentation() {
    writer = new Writer();
}

void Documentation::setListFiles(QStringList list){
    listFiles = list;
    generateDocumentation();
}

Documentation::~Documentation(){
    delete writer;
}

void Documentation::generateDocumentation(){
    qDebug() << "Documentation::generateDocumentation()";

    writer->clearDoc();

    for(int i = 0; i < listFiles.size(); ++i){

        QFile file(listFiles[i]);
        writer->writeFilename(QFileInfo(listFiles[i]).fileName());

        if(!file.open(QIODevice::ReadOnly))
            emit changeStatus(-1, 6,
                              "Не удалось открыть файл " + QFileInfo(listFiles[i]).fileName() + " для чтения");

        while(!file.atEnd()){
            QByteArray currentLine = file.readLine();
            QString nameSpace{""};

            if(currentLine.contains("\\namespace")){
                nameSpace = getPartOfComment(currentLine, "\\namespace");
//                if(!nameSpace.isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Пространство имен ")<<nameSpace ;
            }

//            qDebug() << currentLine;
            if(currentLine.contains("\\brief")){
                Command command;

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

                    QList<QPair<QString, QString>> params;
                    QString par = getPartOfComment(nextLine, "\\param");
                    QStringList parList = par.split("] ");
                    params.append(qMakePair(parList[0].remove("["), parList[1]));
                    nextLine = file.readLine();
                    while(nextLine.contains("\\param")){
                        QString str = getPartOfComment(nextLine, "\\param");
                        QStringList strList = str.split("] ");
                        params.append(qMakePair(strList[0].remove("["), strList[1]));
                        nextLine = file.readLine();

                    }

                    command.setParams(params);

                    QByteArray method_byte = file.readLine();
                    if(method_byte.contains("*/")){
//                    if(method_byte.contains("\r\n")){
                        method_byte = file.readLine();
//                        while(method_byte == "\r\n")
//                            method_byte = file.readLine();
                    }
                    command.setMethod(QString(method_byte).simplified().remove(";"));
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\return")){
//                    command.setReturnValue(getPartOfComment(nextLine, "\\return"));
                    QString str = getPartOfComment(nextLine, "\\return");
                    QStringList strList = str.simplified().split("] ");
                    command.setReturnValue(qMakePair(strList[0].remove("["), strList[1]));
                    nextLine = file.readLine();
                }

                if(nextLine.contains("*/")){
                    nextLine = file.readLine();

//                    while(nextLine == "\r\n")
//                        nextLine = file.readLine();

                    if(nextLine.contains("()")){
                        command.setMethod(QString(nextLine).simplified().remove(";"));
                    }else if(nextLine.contains("class")){

                        QString name = QString(nextLine).simplified();
                        QStringList list = name.split(":");
                        QString className = list[0].split(" ")[1];

                        if(list.size() > 1){
                            QString parent = list[1];
                            QStringList parentList = parent.split(",");

                            QStringList finalList;
                            finalList << className << parentList;
                            command.setClassName(finalList);
                        }else
                            command.setClassName(QStringList() << className);
                    }else{
                        QString str = QString(nextLine).simplified();
                        QStringList strList = str.split(" ");
                        command.setMember(qMakePair(strList[0], strList[1].simplified().remove(";")));
                    }
                }

//                if(!command.getDescription().isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Описание ")<<command.getDescription() ;
//                if(!command.getVersion().isEmpty()) qDebug() <<QString::fromUtf8("Версия ")<<command.getVersion() ;
//                if(!command.getDate().isEmpty()) qDebug() <<QString::fromUtf8("Дата ")<<command.getDate() ;
//                if(!command.getClassName().isEmpty()) qDebug() <<QString::fromUtf8("Имя класса ")<<command.getClassName() ;
//                if(!command.getParams().isEmpty()) qDebug() <<QString::fromUtf8("Аргументы метода ")<<command.getParams() ;
//                if(!command.getReturnValue().first.isEmpty()) qDebug() <<QString::fromUtf8("возращаемый тип ")<<command.getReturnValue() ;
//                if(!command.getMethod().isEmpty()) qDebug() <<QString::fromUtf8("Имя метода ")<<command.getMethod() ;
//                if(!command.getMember().first.isEmpty()) qDebug() <<QString::fromUtf8("Имя поля ")<<command.getMember() ;
                writer->writeCommand(command);
            }



            if(currentLine.contains("public:")){
//                qDebug() << QString(currentLine).remove("\r\n");
                writer->writeMark("public:");
            }
            if(currentLine.contains("private slots:")){
//                qDebug() << QString(currentLine).remove("\r\n");
                writer->writeMark("private slots:");
            }
            if(currentLine.contains("signals:")){
//                qDebug() << QString(currentLine).remove("\r\n");
                writer->writeMark("signals:");
            }
            if(currentLine.contains("private:")){
//                qDebug() << QString(currentLine).remove("\r\n");
                writer->writeMark("private:");
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
    QStringList list = array_str.simplified().split(separator);
    return list[1];
}
