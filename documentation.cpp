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
            if(currentLine.contains("\\namespace")){
//                QByteArray next = file.readLine();
//                qDebug() << QString::fromUtf8(line);

            }

            if(currentLine.contains("\\brief")){
//                qDebug() << QString::fromUtf8(line);

                QString description{""};
                QString version{""};
                QString date{""};
                QString param{""};
                QString method{""};
                QString member{""};

                QString str(currentLine);
                QStringList brief = str.split("\\brief ");

                description = brief[1].remove("\r\n");
                QByteArray nextLine = file.readLine();

                if(nextLine.contains("\\version")){
                    QString ver(nextLine);
                    QStringList v = ver.split("\\version ");
                    version = v[1].remove("\r\n");
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\date")){
                    QString date_str(nextLine);
                    QStringList d = date_str.split("\\date ");
                    date = d[1].remove("\r\n");
                    nextLine = file.readLine();
                }

                if(nextLine.contains("\\param")){

                    QString param_str(nextLine);
                    QStringList param_list = param_str.split("\\param ");
                    param = param_list[1].remove("\r\n");
                    QByteArray method_byte = file.readLine();
                    if(method_byte.contains("*/"))
                        method_byte = file.readLine();
//                    qDebug() << method;
                    method = QString(method_byte).remove("\r\n");
                }

                if(nextLine.contains("*/")){
                    nextLine = file.readLine();
//                    QRegExp reg("\\([a-zA-Z]*\\)");
                    if(/*reg.exactMatch(nextLine) ||*/ nextLine.contains("()")){
//                        QByteArray method_byte = file.readLine();
//                        method = QString(method_byte).remove("\r\n");
                        method = QString(nextLine).remove("\r\n");
                    }else{
//                        QByteArray member_byte = file.readLine();
//                        member = QString(member_byte).remove("\r\n");
                        member = QString(nextLine).remove("\r\n");
                    }
                }


                if(!description.isEmpty()) qDebug() <<"\n"<<QString::fromUtf8("Описание ")<<description ;
                if(!version.isEmpty()) qDebug() <<QString::fromUtf8("Версия ")<<version ;
                if(!date.isEmpty()) qDebug() <<QString::fromUtf8("Дата ")<<date ;
                if(!param.isEmpty()) qDebug() <<QString::fromUtf8("Аргументы метода ")<<param ;
                if(!method.isEmpty()) qDebug() <<QString::fromUtf8("Имя метода ")<<method ;
                if(!member.isEmpty()) qDebug() <<QString::fromUtf8("Имя поля ")<<member ;
            }




            if(currentLine.contains("class")){
                qDebug() << QString::fromUtf8(currentLine);
            }
            if(currentLine.contains("public:")){
                qDebug() << QString::fromUtf8(currentLine);
            }
            if(currentLine.contains("private slots:")){
                qDebug() << QString::fromUtf8(currentLine);
            }
            if(currentLine.contains("signals:")){
                qDebug() << QString::fromUtf8(currentLine);
            }
            if(currentLine.contains("private:")){
                qDebug() << QString::fromUtf8(currentLine);
            }

        }
        emit progress(i+1, listFiles.size());
//        qDebug() << count;
    }

}
