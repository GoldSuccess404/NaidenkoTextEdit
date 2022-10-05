#include "file.h"

file::file(QWidget *parent) : QWidget(parent)
{
}

/*открытие проекта*/
void file::openFile(bool ok)
{
    if (ok==false){
        filePath.clear();
    }
 QString str = "";
 str = QFileDialog::getExistingDirectory(this, "Open a project", "c://");
 filePath << listFilesPath(str);

 for (int i=0; i<filePath.size(); i++){
 QFile file(filePath.at(i));

 if(!file.open(QFile::ReadOnly | QFile::Text)){
     qDebug() << file.errorString();
     return;
 }
 dirPath = str;
 QTextStream stream(&file);
 QTextEdit *textEdit = new QTextEdit(this);
 textEdit->setStyleSheet(styleHelper::getStyleTextEdit());
 new highlighting(textEdit->document());
 QFont font("Lucida Console", 14);
 textEdit->setFont(font);
 textEdit->setText(stream.readAll());

 emit fileName(QFileInfo(filePath.at(i)).fileName(), textEdit, QFileInfo(str).fileName());
 file.close();
 }
}

/*открытие файлов в темной теме*/
void file::openDark()
{
    QString str= getDirPath();
    for (int i=0; i<filePath.size(); i++){
    QFile file(filePath.at(i));

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << file.errorString();
        return;
    }
    QTextStream stream(&file);
    QTextEdit *textEdit = new QTextEdit(this);
    new darkHighlighting(textEdit->document());
    QFont font("Lucida Console", 14);
    textEdit->setFont(font);
    textEdit->setText(stream.readAll());

    emit fileName(QFileInfo(filePath.at(i)).fileName(), textEdit, QFileInfo(str).fileName());
    file.close();
    }
}

/*открытие файлов с светлой теме*/
void file::openLight()
{
    QString str= getDirPath();
    for (int i=0; i<filePath.size(); i++){
    QFile file(filePath.at(i));

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << file.errorString();
        return;
    }
    QTextStream stream(&file);
    QTextEdit *textEdit = new QTextEdit(this);
    new highlighting(textEdit->document());
    QFont font("Lucida Console", 14);
    textEdit->setFont(font);
    textEdit->setText(stream.readAll());

    emit fileName(QFileInfo(filePath.at(i)).fileName(), textEdit, QFileInfo(str).fileName());
    file.close();
    }
}


/*возвращает лист путей к файлам из каталога*/
QList<QString> file::listFilesPath(QString pathDirectory)
{
 QList<QString> list;
 QDir dir(pathDirectory);
 bool ok = dir.exists();

 if(ok){
     dir.setFilter(QDir::Files);
     dir.setSorting(QDir::Name);
     QFileInfoList info = dir.entryInfoList();

  for (int i=0; i<info.size(); i++){
      QFileInfo fileInfo = info.at(i);
      list << fileInfo.filePath();
  }
 }
 return list;
}

/*геттеры и сеттеры*/
QList<QString> file::getFilesPath()
{
    return filePath;
}


/*путь файла по индексу*/
QString file::getFilePath(int index)
{
  return filePath[index];
}

QString file::getDirPath()
{
    return dirPath;
}

void file::setDirPath(QString path)
{
    dirPath = path;
}

void file::setFilePath(QString path)
{
    filePath << path;
}


/*очистка листа с путями к файлам*/
void file::clearFilesPath()
{
    filePath.clear();
}

/*удаление пути файла по индексу*/
void file::deleteCurrentFilePath(int index)
{
    filePath.removeAt(index);
}











