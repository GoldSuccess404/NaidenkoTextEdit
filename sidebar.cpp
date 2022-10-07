#include "sidebar.h"

sideBar::sideBar(QWidget *parent) : QWidget(parent)
{
 f = new file(this);
 lab1 = new QLabel("Opened project: ");
 lab = new QLabel("");
 listWid = new QListWidget(this);
 stackWid = new QStackedWidget(this);
 setInterface();

 QHBoxLayout *hay = new QHBoxLayout;
 QVBoxLayout *vay = new QVBoxLayout;

 //компановка
 vay->addWidget(lab1);
 vay->addWidget(lab);
 vay->addWidget(listWid);

 hay->addLayout(vay);
 hay->addWidget(stackWid);
 hay->setContentsMargins(0,0,0,0);
 setLayout(hay);


 /*добавление в лист*/
 QObject::connect(this, SIGNAL(addElemnt(QString,QTextEdit*,QString)), this, SLOT(addElementToList(QString,QTextEdit*,QString)));
 /*перемещение по двойному щелчку*/
 QObject::connect(listWid, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(changeCurrentElement(QModelIndex)));
 /*добавление нового файла в проект*/
 QObject::connect(this, SIGNAL(newFileName(QString)), this, SLOT(addNewElementToList(QString)));
 /*добавление имени проекта при создании нового проекта*/
 QObject::connect(this, SIGNAL(projectName(QString)), this, SLOT(setProjectName(QString)));
 /*при сохранении удаление звездочки из файла*/
 QObject::connect(this, SIGNAL(saveToFile()), this, SLOT(fileSaved()));
 /*при сохранении удаление звездочек из проекта*/
 QObject::connect(this, SIGNAL(saveToProject()), this, SLOT(projectSaved()));
 /*темная тема*/
 QObject::connect(this, SIGNAL(darkTheme()), this, SLOT(setDarkTheme()));
 /*светлая тема*/
 QObject::connect(this, SIGNAL(lightTheme()), this, SLOT(setLightTheme()));
}


/*добавление элемента в лист и установка имени проекта*/
void sideBar::addElementToList(QString name,  QTextEdit *tEdit, QString projectName)
{
 lab->setText(projectName);
 QListWidgetItem *item = new QListWidgetItem(listWid);
 QSize size(0, 25);

 if (name.contains(".cpp")){
     item->setIcon(QIcon("://images/cppFile.png"));
 }
 else {
     item->setIcon(QIcon("://images/headerFile.png"));
 }
 item->setText(name);
 item->setSizeHint(size);

 listWid->addItem(item);
 stackWid->addWidget(tEdit);
 stackWid->setCurrentIndex(count1);
 listWid->setCurrentRow(count1);
 count1++;


 //при изменении текста добавление звездочки на несохраненный файл
 QTextEdit *teEdit = qobject_cast<QTextEdit *>(stackWid->widget(listWid->currentRow()));
 QObject::connect(teEdit, SIGNAL(textChanged()), this, SLOT(notFileSaved()));

}


/*перемещение между элементами листа*/
void sideBar::changeCurrentElement(QModelIndex index)
{
    stackWid->setCurrentIndex(index.row());
}



/*геттеры*/

//возвращает текущий индекс листа
int sideBar::getCurrentIndexList()
{
    return listWid->currentRow();
}

//возвращает название проекта
QString sideBar::getNameProject()
{
    return lab->text();
}

//возвращает виджет по текущей позиции листа
QWidget* sideBar::getCurrentIndexWidget()
{
    return stackWid->widget(listWid->currentRow());
}

//возвращает виджет по индексу
QWidget* sideBar::getIndexWidget(int index)
{
    return stackWid->widget(index);
}




/*закрытие проекта*/
void sideBar::closeProject()
{
    //обнуление счетчика
    count1 =0;

    //удаление виджетов из QStackedWidget
    for(int i = stackWid->count(); i>=0 ; i--)
    {
        stackWid->removeWidget(stackWid->widget(i));
    }

    //удаление виджетов из QListWidget
    for(int i= listWid->count(); i >= 0; i--){
        listWid->removeItemWidget(listWid->takeItem(i));
    }

    //очистка QLabel - название проекта
    lab->clear();
}


/*удаления файла по текущему индексу*/
void sideBar::deleteCurrentFile()
{
  //удаление виджета из QStackedWidget
  stackWid->removeWidget(stackWid->widget(listWid->currentRow()));
  //удаление виджета из QListWidget
  listWid->removeItemWidget(listWid->takeItem(listWid->currentRow()));
  count1--;
}


/*добавление нового файла в лист*/
void sideBar::addNewElementToList(QString name)
{
 QListWidgetItem *item = new QListWidgetItem(listWid);
 QSize size(0, 25);

 if (name.contains(".cpp")){
     item->setIcon(QIcon("://images/cppFile.png"));
 }
 else {
     item->setIcon(QIcon("://images/headerFile.png"));
 }

 item->setText(name);
 item->setSizeHint(size);

 listWid->addItem(item);

 QTextEdit *textEdit = new QTextEdit(this);
 if (theme){
 new darkHighlighting(textEdit->document());
 }
 else {
     new highlighting(textEdit->document());
 }


 textEdit->setFontPointSize(16);
 stackWid->addWidget(textEdit);
 listWid->setCurrentRow(count1);
 stackWid->setCurrentIndex(count1);
 count1++;


 //при изменении текста добавление звездочки на несохраненный файл
 QTextEdit *teEdit = qobject_cast<QTextEdit *>(stackWid->widget(listWid->currentRow()));
 teEdit->setFontPointSize(16);
 QObject::connect(teEdit, SIGNAL(textChanged()), this, SLOT(notFileSaved()));
}

/*добавление имени проекта*/
void sideBar::setProjectName(QString projectName)
{
    lab->setText(projectName);
}

/*темная тема*/
void sideBar::setDarkTheme()
{
  for (int i=0; i<count1; i++){
      QTextEdit *text = qobject_cast<QTextEdit *>( stackWid->widget(i));
      text->setStyleSheet(styleHelper::getDarkThemeTextEdit());
  }
      this->setStyleSheet(styleHelper::getDarkThemeSideBar());
      lab1->setStyleSheet("color: white");
      lab->setStyleSheet("color: white");
      listWid->setStyleSheet("color: white");
      theme=true;
}

/*светлая тема*/
void sideBar::setLightTheme()
{
    for (int i=0; i<count1; i++){
        QTextEdit *text = qobject_cast<QTextEdit *>( stackWid->widget(i));
        text->setStyleSheet(styleHelper::getStyleTextEdit());
    }
        this->setStyleSheet(styleHelper::getStyleSideBar());
        lab1->setStyleSheet("color: black");
        lab->setStyleSheet("color: black");
        listWid->setStyleSheet("color: black");

        theme=false;
}

/*добавление звездочки*/
void sideBar::notFileSaved()
{
   if (!listWid->currentItem()->text().contains("*"))
  listWid->currentItem()->setText(listWid->currentItem()->text()+"*");
}

/*удаление звездочки в файле*/
void sideBar::fileSaved()
{
  if (listWid->currentItem()->text().contains("*"))
      listWid->currentItem()->setText(listWid->currentItem()->text().remove("*"));
}

/*удаление звездочек во всем проекте*/
void sideBar::projectSaved()
{
  for (int i=0; i<listWid->count(); i++){
    if (listWid->item(i)->text().contains("*"))
        listWid->item(i)->setText(listWid->item(i)->text().remove("*"));
  }
}

/*проверка сохранен ли проект для обработки событий*/
bool sideBar::isSavedProject()
{
    for (int i=0; i<listWid->count(); i++){
      if (listWid->item(i)->text().contains("*"))
          return false;
    }
    return true;
}

/*стили*/
void sideBar::setInterface()
{
   listWid->setFixedWidth(300);

   lab1->setFixedHeight(50);
   QFont font("Verdana", 17, QFont::Bold);
   lab1->setStyleSheet("padding-left: 15px");
   lab1->setFont(font);

   lab->setFixedHeight(50);
   lab->setStyleSheet("padding-left: 15px");
   lab->setFont(font);

}



















