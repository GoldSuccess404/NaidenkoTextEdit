#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include "file.h"
#include "dialognewfile.h"

class sideBar : public QWidget
{
    Q_OBJECT
public:
    sideBar(QWidget *parent =nullptr);
    QString getNameProject();
    int getCurrentIndexList();
    QWidget* getCurrentIndexWidget();
    QWidget* getIndexWidget(int index);
    void closeProject();
    void deleteCurrentFile();
    bool isSavedProject();
    void setInterface();
    int count1 =0;
    bool theme=false;
    bool mainSaved=false;
private:
    QLabel *lab;
    QLabel *lab1;
    QListWidget *listWid;
    QStackedWidget *stackWid;
    file *f;
signals:
    void addElemnt(QString name, QTextEdit *tEdit, QString projectName=nullptr);
    void newFileName(QString name);
    void projectName(QString projectName);
    void saveToFile();
    void saveToProject();
    void darkTheme();
    void lightTheme();
public slots:
    void notFileSaved();
    void fileSaved();
    void projectSaved();
    void addElementToList(QString name,  QTextEdit *tEdit, QString projectName=nullptr);
    void changeCurrentElement(QModelIndex index);
    void addNewElementToList(QString name);
    void setProjectName(QString projectName);
    void setDarkTheme();
    void setLightTheme();
};

#endif // SIDEBAR_H
