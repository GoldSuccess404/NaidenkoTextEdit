#include "menuwind.h"

MenuWind::MenuWind(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(900, 400);
    setStyleSheet("background-color: white");
    file1 = new file(this);
    side = new sideBar(this);
    side->setStyleSheet(styleHelper::getStyleSideBar());

    QHBoxLayout *h = new QHBoxLayout;
    QWidget * wid = new QWidget(this);

    /*menu project*/
    menu = menuBar()->addMenu("Project");

    QAction *open = new QAction(QIcon("://images/OpenProject.png"),"Open Project");
    open->setShortcut(QKeySequence::Open);

    QAction *newProject = new QAction(QIcon("://images/NewProject.png"),"New Project");
    newProject->setShortcut(QKeySequence::New);

    saveFile1 = new QAction("Save File");
    saveFile1->setEnabled(false);
    saveFile1->setShortcut(QKeySequence::Save);

    saveProject1 = new QAction("Save Project");
    saveProject1->setEnabled(false);

    closeProject1 = new QAction(QIcon("://images/CloseProject.png"),"Close Project");
    closeProject1->setEnabled(false);

    deleteFile = new QAction("Delete File");
    deleteFile->setEnabled(false);

    newFile1 = new QAction(QIcon("://images/NewFile.png"),"New File");
    newFile1->setEnabled(false);

    QAction *exit = new QAction("Exit");


    menu->addAction(newProject);
    menu->addAction(open);
    menu->addAction(closeProject1);
    menu->addAction(newFile1);
    menu->addAction(deleteFile);
    menu->addAction(saveProject1);
    menu->addAction(saveFile1);
    menu->addSeparator();
    menu->addAction(exit);

    /*компиляция*/
    menu2 = menuBar()->addMenu("Run");
    run = new QAction("Run Now");
    run->setEnabled(false);

    menu2->addAction(run);

    /*тема*/
    menu3 = menuBar()->addMenu("View");
    subMenu = new QMenu("Theme");
    light = new QAction(QIcon("://images/mark.png"),"Light");
    light->setEnabled(false);

    dark = new QAction("Dark");
    dark->setEnabled(false);

    subMenu->addAction(light);
    subMenu->addAction(dark);

    menu3->addMenu(subMenu);

    /*компановка*/
    h->addWidget(side);
    wid->setLayout(h);
    setCentralWidget(wid);

    /*стили*/
    menuBar()->setStyleSheet(styleHelper::getStyleMenuBar());
    menu->setStyleSheet(styleHelper::getStyleMenu());
    menu2->setStyleSheet(styleHelper::getStyleMenu());
    menu3->setStyleSheet(styleHelper::getStyleMenu());
    subMenu->setStyleSheet(styleHelper::getStyleMenu());
    menuBar()->setFixedHeight(30);
    setWindowIcon(QIcon("://images/main.png"));
    setWindowTitle("NaidenkoTextEdit");

    /*открытие проекта*/
    QObject::connect(open, SIGNAL(triggered(bool)), this, SLOT(checkProject()));
    QObject::connect(this, SIGNAL(openSignal(bool)), file1, SLOT(openFile(bool)));
    /*сохранение файла и проекта*/
    QObject::connect(saveProject1, SIGNAL(triggered(bool)), this, SLOT(saveProject()));
    QObject::connect(saveFile1, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    /*удаление проекта*/
    QObject::connect(closeProject1, SIGNAL(triggered(bool)), this, SLOT(closeProject()));
    /*удаление файла*/
    QObject::connect(deleteFile, SIGNAL(triggered(bool)), this, SLOT(deleteToFile()));
    /*создание нового файла*/
    QObject::connect(newFile1, SIGNAL(triggered(bool)), this, SLOT(newFile()));
    QObject::connect(&DiNewFile, SIGNAL(fileReady(QString)), this, SLOT(addNewFile(QString)));
    /*создание проекта*/
    QObject::connect(newProject, SIGNAL(triggered(bool)), this, SLOT(newProject()));
    QObject::connect(&DiProject, SIGNAL(nameProgect(QString)), this, SLOT(createNewProgect(QString)));
    /*закрытие программы*/
    QObject::connect(exit, SIGNAL(triggered(bool)), this, SLOT(close()));
    /*компиляция программы*/
    QObject::connect(run, SIGNAL(triggered(bool)), this, SLOT(compile()));
    /*темная тема*/
    QObject::connect(dark, SIGNAL(triggered(bool)), this, SLOT(setDarkTheme()));
    /*светлая тема*/
    QObject::connect(light, SIGNAL(triggered(bool)), this, SLOT(setLightTheme()));
    /*добавление элементов*/
    QObject::connect(file1, SIGNAL(fileName(QString,QTextEdit*,QString)), this, SLOT(fileAddSidebar(QString,QTextEdit*,QString)));

}

/*обработка события закрытия*/
void MenuWind::closeEvent(QCloseEvent *event)
{
    if(!side->isSavedProject()){
        event->ignore();
        QMessageBox ms;

        QAbstractButton *yes = ms.addButton("Yes",QMessageBox::NoRole);
        QAbstractButton *no = ms.addButton("No",QMessageBox::NoRole);
        QAbstractButton *saveAll = ms.addButton("Save All", QMessageBox::NoRole);
        ms.setText("There are unsaved files. Do you really want to close?");
        ms.setWindowIcon(QIcon("://images/main.png"));
        ms.exec();

        if(ms.clickedButton() == yes) event->accept();
        if(ms.clickedButton() == no) ms.close();
        if(ms.clickedButton() == saveAll){
            saveProject();
            event->accept();
        }
    }
}


/*отправка сигнала в SIDEBAR для добавления элемента*/
void MenuWind::fileAddSidebar(QString name, QTextEdit *tEdit, QString projectName)
{
  emit side->addElemnt(name, tEdit, projectName);

}


/*сохранение файлов*/
void MenuWind::saveFile()
{
    QFile file(file1->getFilePath(side->getCurrentIndexList()));
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QTextStream stream(&file);
    QTextEdit *tEdit = qobject_cast<QTextEdit *>(side->getCurrentIndexWidget());
    stream << tEdit->toPlainText();
    file.close();
    emit side->saveToFile();

}

/*сохранение всего проекта*/
void MenuWind::saveProject()
{
  QList<QString> list;
  list << file1->getFilesPath();

  for (int i=0; i<list.size(); i++){
      QFile file(list.at(i));
      if (!file.open(QFile::WriteOnly | QFile::Text)){
          return;
      }
      QTextStream stream(&file);
      QTextEdit *tEdit = qobject_cast<QTextEdit *>(side->getIndexWidget(i));
      stream << tEdit->toPlainText();
      file.close();
  }
  emit side->saveToProject();
}



/*проверка был ли уже открыт проект*/
void MenuWind::checkProject()
{
    /*если проект не сохранен*/
    if(!side->isSavedProject()){
        QMessageBox ms;

        QAbstractButton *yes = ms.addButton("Yes",QMessageBox::NoRole);
        QAbstractButton *no = ms.addButton("No",QMessageBox::NoRole);
        QAbstractButton *saveAll = ms.addButton("Save All", QMessageBox::NoRole);
        ms.setText("There are unsaved files. Do you really want to close?");
        ms.setWindowIcon(QIcon("://images/main.png"));
        ms.exec();
        /***************************************/
        if (ms.clickedButton() == yes){
            if(check){
                emit openSignal(check);
                check=false;
            }
            else {
                side->closeProject();
                emit openSignal(check);
            }
        }
        /****************************************/
        if (ms.clickedButton() == no) ms.close();
        /****************************************/
        if (ms.clickedButton() == saveAll){
            saveProject();
            if(check){
                emit openSignal(check);
                check=false;
            }
            else {
                side->closeProject();
                emit openSignal(check);
            }
        }
        /***************************************/
    }

/*если проект сохранен*/
 else{
 if(check){
     emit openSignal(check);
     check=false;
     saveFile1->setEnabled(true);
     saveProject1->setEnabled(true);
     closeProject1->setEnabled(true);
     deleteFile->setEnabled(true);
     newFile1->setEnabled(true);
     run->setEnabled(true);
     dark->setEnabled(true);
     light->setEnabled(true);
 }
 else {
     side->closeProject();
     emit openSignal(check);
     saveFile1->setEnabled(true);
     saveProject1->setEnabled(true);
     closeProject1->setEnabled(true);
     deleteFile->setEnabled(true);
     newFile1->setEnabled(true);
     run->setEnabled(true);
     dark->setEnabled(true);
     light->setEnabled(true);
      }
    }
}



/*закрытие проекта*/
void MenuWind::closeProject()
{
  if(!side->isSavedProject()){
      QMessageBox ms;

      QAbstractButton *yes = ms.addButton("Yes",QMessageBox::NoRole);
      QAbstractButton *no = ms.addButton("No",QMessageBox::NoRole);
      QAbstractButton *saveAll = ms.addButton("Save All", QMessageBox::NoRole);
      ms.setText("There are unsaved files. Do you really want to close?");
      ms.setWindowIcon(QIcon("://images/main.png"));
      ms.exec();

      if (ms.clickedButton() == yes){
          file1->clearFilesPath();
          side->closeProject();
          saveFile1->setEnabled(false);
          saveProject1->setEnabled(false);
          closeProject1->setEnabled(false);
          deleteFile->setEnabled(false);
          newFile1->setEnabled(false);
          run->setEnabled(false);
          dark->setEnabled(false);
          light->setEnabled(false);
      }
      if (ms.clickedButton() == no) ms.close();
      if (ms.clickedButton() == saveAll){
          saveProject();
          file1->clearFilesPath();
          side->closeProject();
          saveFile1->setEnabled(false);
          saveProject1->setEnabled(false);
          closeProject1->setEnabled(false);
          deleteFile->setEnabled(false);
          newFile1->setEnabled(false);
          run->setEnabled(false);
          dark->setEnabled(false);
          light->setEnabled(false);
      }
  }

  else {
  file1->clearFilesPath();
  side->closeProject();

  saveFile1->setEnabled(false);
  saveProject1->setEnabled(false);
  closeProject1->setEnabled(false);
  deleteFile->setEnabled(false);
  newFile1->setEnabled(false);
  run->setEnabled(false);
  dark->setEnabled(false);
  light->setEnabled(false);

       /*тема*/
  emit side->lightTheme();
    this->setStyleSheet("background: white");
    menuBar()->setStyleSheet(styleHelper::getStyleMenuBar());
    menu->setStyleSheet(styleHelper::getStyleMenu());
    menu2->setStyleSheet(styleHelper::getStyleMenu());
    menu3->setStyleSheet(styleHelper::getStyleMenu());
    subMenu->setStyleSheet(styleHelper::getStyleMenu());
    dark->setIconVisibleInMenu(false);
    light->setIconVisibleInMenu(true);
  }
}


/*удаление файла*/
void MenuWind::deleteToFile()
{
 QFile(file1->getFilePath(side->getCurrentIndexList())).remove();
 file1->deleteCurrentFilePath(side->getCurrentIndexList());
 side->deleteCurrentFile();
}


/*создание нового файла*/
void MenuWind::newFile()
{
    DiNewFile.show();
}

void MenuWind::addNewFile(QString str)
{
        QDir dir(file1->getDirPath());
        bool ok = dir.exists();

        if(ok){
            QFile file(file1->getDirPath() + "/" + str);
            if(!file.open(QFile::WriteOnly)){
                return;
            }
            file.close();
        }
        //добавление пути к файлу
        file1->setFilePath(file1->getDirPath() + "/" + str);
        //добавление в лист
        emit side->newFileName(str);
}



/*создание проекта*/
void MenuWind::newProject()
{   /*если проект не сохранен*/
    if(!side->isSavedProject()){
        QMessageBox ms;

        QAbstractButton *yes = ms.addButton("Yes",QMessageBox::NoRole);
        QAbstractButton *no = ms.addButton("No",QMessageBox::NoRole);
        QAbstractButton *saveAll = ms.addButton("Save All", QMessageBox::NoRole);
        ms.setText("There are unsaved files. Do you really want to close?");
        ms.setWindowIcon(QIcon("://images/main.png"));
        ms.exec();
        /*закрытие без сохранения*/
        if (ms.clickedButton() == yes){
            file1->clearFilesPath();
            side->closeProject();
            DiProject.show();
        }
        /*просто закрытие*/
        if (ms.clickedButton() == no) ms.close();
        /*закрытие с сохранением*/
        if (ms.clickedButton() == saveAll){
            saveProject();
            file1->clearFilesPath();
            side->closeProject();
            DiProject.show();
        }
    }

   /*если проект сохранен*/
    else {
    file1->clearFilesPath();
    side->closeProject();
    DiProject.show();

    saveFile1->setEnabled(true);
    saveProject1->setEnabled(true);
    closeProject1->setEnabled(true);
    deleteFile->setEnabled(true);
    newFile1->setEnabled(true);
    run->setEnabled(true);
    dark->setEnabled(true);
    light->setEnabled(true);
    }
}

void MenuWind::createNewProgect(QString name)
{
    QDir().mkdir(name);
    //создали проект
    check=false;
    createProject=true;
    file1->setDirPath(name);

    QFile file(":/hello/hello World/helloWorld.cpp");
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);

    /*создание файла*/
     QDir dir(file1->getDirPath());

     if(dir.exists()){
         QFile fil(file1->getDirPath() + "/main.cpp");
         if(!fil.open(QFile::WriteOnly)) return;
         QTextStream s(&fil);
         s << stream.readAll();

         //добавление пути к файлу
         file1->setFilePath(file1->getDirPath() + "/main.cpp");
         fil.close();
     }
    file.close();

    QFile fileMain(file1->getDirPath() + "/main.cpp");
    if (!fileMain.open(QFile::ReadOnly)) return;
    QTextStream mainStream(&fileMain);
    QTextEdit *textEdit = new QTextEdit(this);

    /*стили*/
    if (side->theme){
       textEdit->setStyleSheet(styleHelper::getDarkThemeTextEdit());
       new darkHighlighting(textEdit->document());
    }
    else {
       textEdit->setStyleSheet(styleHelper::getStyleTextEdit());
       new highlighting(textEdit->document());
    }
    QFont font("Lucida Console", 14);
    textEdit->setFont(font);


    textEdit->setText(mainStream.readAll());
    fileMain.close();



    //добавление в лист
    emit side->addElemnt("main.cpp", textEdit, QFileInfo(name).fileName());
}



/*компиляция программы*/
void MenuWind::compile()
{
    if(!side->isSavedProject())
    {
        QMessageBox ms;

        QAbstractButton *saveAll = ms.addButton("Save All", QMessageBox::AcceptRole);
        ms.setText("There are unsaved files!");
        ms.setWindowIcon(QIcon("://images/main.png"));
        ms.exec();

        if (ms.clickedButton() == saveAll){
            saveProject();
        }
    }

    QString debugDirPath = file1->getDirPath() + "/Debug";
    QDir debugDir(debugDirPath);
    if(!debugDir.exists()) debugDir.mkdir(debugDirPath);

    QStringList args;
  for (int i=0; i<side->count1; i++){
      args << file1->getFilePath(i);
  }
  args << "-o";
  args << debugDirPath + "/" + side->getNameProject() + ".exe";
  process.start("g++", args);
  process.waitForFinished();

   //если присутсвуют синтаксический ошибки
  QString errors = process.readAllStandardError();
  if(!errors.isEmpty()){
      dialogErrors *diEr = new dialogErrors(this, errors);
      diEr->exec();
  }
  else {
      system(QString(debugDirPath + "/" + side->getNameProject() + ".exe").toStdString().c_str());
  }
}

/*темная тема*/
void MenuWind::setDarkTheme()
{
  saveFile();
  side->closeProject();
  file1->openDark();
  emit side->darkTheme();
    this->setStyleSheet("background: #11150F");
    menuBar()->setStyleSheet(styleHelper::getDarkThemeMenuBar());
    menu->setStyleSheet(styleHelper::getDarkThemeMenu());
    menu2->setStyleSheet(styleHelper::getDarkThemeMenu());
    menu3->setStyleSheet(styleHelper::getDarkThemeMenu());
    subMenu->setStyleSheet(styleHelper::getDarkThemeMenu());

    light->setIconVisibleInMenu(false);
    if (theme){
    dark->setIcon(QIcon("://images/markLight.png"));
    }
    else {
        dark->setIconVisibleInMenu(true);
    }
    theme=false;
}

/*светлая тема*/
void MenuWind::setLightTheme()
{
   saveFile();
   side->closeProject();
   file1->openLight();
  emit side->lightTheme();
    this->setStyleSheet("background: white");
    menuBar()->setStyleSheet(styleHelper::getStyleMenuBar());
    menu->setStyleSheet(styleHelper::getStyleMenu());
    menu2->setStyleSheet(styleHelper::getStyleMenu());
    menu3->setStyleSheet(styleHelper::getStyleMenu());
    subMenu->setStyleSheet(styleHelper::getStyleMenu());

    dark->setIconVisibleInMenu(false);
    light->setIconVisibleInMenu(true);
}









