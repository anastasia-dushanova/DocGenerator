#include "documentation.h"

Documentation::Documentation() { }

void Documentation::setListFiles(QStringList list){
    listFiles = list;
    generateDocumentation();
}

void Documentation::generateDocumentation(){
    qDebug() << "Documentation::generateDocumentation()";
    QFile fileDoc(QCoreApplication::applicationDirPath() + "/documentation.md");
    if(!fileDoc.open(QIODevice::ReadWrite | QIODevice::Append))
        qDebug() << "error";

    for(int i = 0; i < listFiles.size(); ++i){
        QFile file(listFiles[i]);
        if(!file.open(QIODevice::ReadOnly))
            qDebug() << "error";
//        int count = 0;
        while(!file.atEnd()){
            QByteArray currentLine = file.readLine();
//            qDebug() << QString::fromUtf8(line);
            QString nameSpace{""};
            if(currentLine.contains("\\namespace")){
//                QByteArray next = file.readLine();
//                qDebug() << QString::fromUtf8(line);
                QString str(currentLine);
                QStringList list = str.split("\\namespace ");
                nameSpace = list[1].remove("\r\n");

                if(!nameSpace.isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Пространство имен ")<<nameSpace ;
            }

            if(currentLine.contains("\\brief")){
//                qDebug() << QString::fromUtf8(line);

                QString description{""};
                QString version{""};
                QString date{""};
                QStringList params;
                QString method{""};
                QString member{""};
                QString className{""};
                QString returnValue{""};

                QString str(currentLine);
                QStringList brief = str.split("\\brief ");

                description = brief[1].remove("\r\n");
                QByteArray nextLine = file.readLine();

                if(nextLine.contains("\\version")){
                    version = getPartOfComment(nextLine, "\\version");
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\date")){
                    date = getPartOfComment(nextLine, "\\date");
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\param")){

                    params.append(getPartOfComment(nextLine, "\\param"));
                    nextLine = file.readLine();
                    while(nextLine.contains("\\param")){
                        params.append(getPartOfComment(nextLine, "\\param"));
                        nextLine = file.readLine();
                    }

                    QByteArray method_byte = file.readLine();
                    if(method_byte.contains("*/"))
                        method_byte = file.readLine();

                    method = QString(method_byte).remove("\r\n");
                }

                if(nextLine.contains("\\return")){
                    returnValue = getPartOfComment(nextLine, "\\return");
                    nextLine = file.readLine();
                }

                if(nextLine.contains("*/")){
                    nextLine = file.readLine();
                    if(nextLine.contains("()")){
                        method = QString(nextLine).remove("\r\n");
                    }else if(nextLine.contains("class")){
                        className = QString(nextLine).remove("\r\n");
                    }else {
                        member = QString(nextLine).remove("\r\n");
                    }
                }

                if(!description.isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Описание ")<<description ;
                if(!version.isEmpty()) qDebug() <<QString::fromUtf8("Версия ")<<version ;
                if(!date.isEmpty()) qDebug() <<QString::fromUtf8("Дата ")<<date ;
                if(!date.isEmpty()) qDebug() <<QString::fromUtf8("Имя класса ")<<className ;
                if(!params.isEmpty()) qDebug() <<QString::fromUtf8("Аргументы метода ")<<params ;
                if(!returnValue.isEmpty()) qDebug() <<QString::fromUtf8("возращаемый тип ")<<returnValue ;
                if(!method.isEmpty()) qDebug() <<QString::fromUtf8("Имя метода ")<<method ;
                if(!member.isEmpty()) qDebug() <<QString::fromUtf8("Имя поля ")<<member ;
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
    }

    emit changeStatus(0, int(Status::Status_done));

}

QString Documentation::getPartOfComment(QByteArray array, QString separator){
    QString array_str(array);
    QStringList list = array_str.split(separator);
    return list[1].remove("\r\n");
}
