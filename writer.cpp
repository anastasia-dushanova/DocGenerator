#include "writer.h"

Writer::Writer(){ }

void Writer::clearDoc(){
    QFile fileDoc(QCoreApplication::applicationDirPath() + "/documentation.md");
    fileDoc.resize(0);  //очищаем перед записью
}

void Writer::writeCommand(Command command){
    QFile fileDoc(QCoreApplication::applicationDirPath() + "/documentation.md");

    if(!fileDoc.open(QIODevice::ReadWrite | QIODevice::Append))
        emit status(-1, 6, "Не удалось открыть файл documentation.md для записи");

    QTextStream in(&fileDoc);
    if(!command.getClassName().isEmpty())   //записываем имя класса
        in << tr("\n\n## Имя класса ")<< command.getClassName()[0];

    if(command.getClassName().size() > 1){
        in << tr("\n\n**Классы-родители:** ");
        QString parents{""};
        for(int i = 1; i<command.getClassName().size(); ++i)
            parents += command.getClassName()[i] + ", ";

        parents.chop(2);
        in << parents;

    }
    if(!command.getDate().isEmpty())    //записываем дату
        in << tr("\n\n**Дата** ")<<command.getDate();

    if(!command.getVersion().isEmpty()) //записываем версию
        in << tr("\n\n**Версия** ")<<command.getVersion();

//        in << tr("\n\n```cpp\n")<<command.getMethod() <<"\n```\n\n";
    if(!command.getMethod().isEmpty())  //записываем метод
        in << "\n\n<div custom-style='method_command'>"<<command.getMethod()<<"</div>\n\n";


    if(!command.getMember().first.isEmpty())    //записываем поле
        in << tr("\n\n<div custom-style='member_command'>")<<command.getMember().first<<" "<<command.getMember().second
           <<"</div>\n";

    if(!command.getDescription().isEmpty())     //записываем краткое описание
        in << tr("\n\n")<<command.getDescription();

    if(!command.getParams().isEmpty()){     //записываем параметры
        in << tr("\n\n**Аргументы метода** <br>");
        in << tr("\n\n| Номер агрумента | Тип | Описание |");
        in << "\n| :---: | --- | --- |";
        for(int i = 0; i < command.getParams().size(); ++i){
            in<<"\n| "<<QString::number(i+1)
              <<" | "<<command.getParams()[i].first
              <<" | "<<command.getParams()[i].second<<" | ";
        }
    }

    if(!command.getReturnValue().first.isEmpty()){  //записываем возвращаемое значение
        in << tr("\n\n**Возращаемое значение** ");
        in << tr("\n\n| Тип | Описание |");
        in << "\n| --- | --- |";
        in <<"\n| "<<command.getReturnValue().first
           <<" | "<<command.getReturnValue().second<<" | ";
    }

    in << "\n\n<br>\n\n";
    fileDoc.flush();
    fileDoc.close();
}

void Writer::writeMark(QString mark){
    QFile fileDoc(QCoreApplication::applicationDirPath() + "/documentation.md");
    if(!fileDoc.open(QIODevice::WriteOnly | QIODevice::Append))
        emit status(-1, 6, "Не удалось открыть файл documentation.md для записи");

    QTextStream in(&fileDoc);
    if(mark.contains("public:"))
        in << tr("\n\n### Открытые поля")<< "\n\n<br>\n\n";

    if(mark.contains("private slots:"))
        in << tr("\n\n<br>\n\n### Закрытые слоты")<< "\n\n<br>\n\n";

    if(mark.contains("signals:"))
        in << tr("\n\n<br>\n\n### Сигналы")<< "\n\n<br>\n\n";

    if(mark.contains("private:"))
        in << tr("\n\n<br>\n\n### Закрытые поля")<< "\n\n<br>\n\n";

    fileDoc.flush();
    fileDoc.close();
}

void Writer::writeFilename(QString filename){
    QFile fileDoc(QCoreApplication::applicationDirPath() + "/documentation.md");
    if(!fileDoc.open(QIODevice::WriteOnly | QIODevice::Append))
        emit status(-1, 6, "Не удалось открыть файл documentation.md для записи");

    QTextStream in(&fileDoc);
    in <<tr("\n\n# Файл: **")<< filename << "** <br>\n\n";
    fileDoc.flush();
    fileDoc.close();
}
