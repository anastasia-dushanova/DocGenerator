

# Файл: **adduser.h** <br>



## Имя класса AddUser

**Классы-родители:**  public QWidget

**Дата**  01.01.2022

**Версия**  1.0

 Класс для добавления пользователей

<br>



### Открытые поля

<br>



<div custom-style='method_command'>explicit AddUser(QWidget *parent = nullptr)</div>



 Конструктор

**Аргументы метода** <br>

| Номер агрумента | Тип | Описание |
| :---: | --- | --- |
| 1 |  QWidget | родитель | 

<br>



<div custom-style='method_command'>~AddUser()</div>



 Деструктор

<br>



<br>

### Закрытые слоты

<br>



<div custom-style='method_command'>void on_pushButton_save_clicked()</div>



 Слот-обработчик нажатия на кнопку "Сохранить"

<br>



<div custom-style='method_command'>void on_pushButton_cancel_clicked()</div>



 Слот-обработчик нажатия на кнопку "Отменить"

<br>



<br>

### Сигналы

<br>



<div custom-style='method_command'>void saveUser(QStringList list)</div>



 Сигнал, сообщающий о том, что можно сохранить список пользователей в файл

**Аргументы метода** <br>

| Номер агрумента | Тип | Описание |
| :---: | --- | --- |
| 1 |  QStringList | Список книг | 

<br>



<br>

### Закрытые поля

<br>



<div custom-style='member_command'>Ui::AddUser *ui</div>


 Виджет для добавления пользователя

<br>



<div custom-style='method_command'>void clearContents()</div>



 Метод для очистки полей

<br>

