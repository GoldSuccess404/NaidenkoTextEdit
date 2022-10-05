#ifndef FILE_H
#define FILE_H
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QWidget>
#include <QList>
#include <QTextEdit>
#include "highlighting.h"
#include "darkhighlighting.h"
#include "stylehelper.h"


class file : public QWidget
{
    Q_OBJECT
private:
    QList<QString> filePath;
    QString dirPath;
public:
    QString getFilePath(int index);
    file(QWidget *parent);
    QList<QString> listFilesPath(QString pathDirectory);
    QList<QString> getFilesPath();
    QString getDirPath();
    void setDirPath(QString path);
    void clearFilesPath();
    void deleteCurrentFilePath(int index);
    void setFilePath(QString path);
public slots:
    void openFile(bool ok);
    void openDark();
    void openLight();
signals:
    void fileName(QString name, QTextEdit *tEdit, QString projectName);
};

#endif // FILE_H
