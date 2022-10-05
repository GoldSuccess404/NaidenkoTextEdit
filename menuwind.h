#ifndef MENUWIND_H
#define MENUWIND_H
#include "sidebar.h"
#include "dialognewproject.h"
#include "dialogerrors.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include <QProcess>

class MenuWind : public QMainWindow
{
    Q_OBJECT

public:
    MenuWind(QWidget *parent = nullptr);
private:
    sideBar *side;
    file *file1;

    dialogNewFile DiNewFile;
    DialogNewProject DiProject;

    QAction *saveFile1;
    QAction *saveProject1;
    QAction *closeProject1;
    QAction *deleteFile;
    QAction *newFile1;
    QAction *run;
    QAction *light;
    QAction *dark;
    QMenu *menu;
    QMenu *menu2;
    QMenu *menu3;
    QMenu *subMenu;

    QString nameFile;
    QProcess process;
    void closeEvent(QCloseEvent *event);
    bool check=true;
    bool createProject=false;
    bool theme=true;
public slots:
    void saveFile();
    void saveProject();
    void checkProject();
    void closeProject();
    void deleteToFile();
    void newFile();
    void addNewFile(QString str);
    void newProject();
    void createNewProgect(QString name);
    void compile();
    void setDarkTheme();
    void setLightTheme();
    void fileAddSidebar(QString name, QTextEdit *tEdit, QString projectName);
signals:
    void openSignal(bool ok);
};
#endif // MENUWIND_H
