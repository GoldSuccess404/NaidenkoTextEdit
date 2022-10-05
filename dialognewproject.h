#ifndef DIALOGNEWPROJECT_H
#define DIALOGNEWPROJECT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class DialogNewProject : public QWidget
{
    Q_OBJECT
public:
    explicit DialogNewProject(QWidget *parent = nullptr);
private:
    QLabel *lab;
    QLineEdit *line;
    QPushButton *ok;
    QPushButton *cancel;
private slots:
    void getNameProgect();
signals:
    void nameProgect(QString name);
};

#endif // DIALOGNEWPROJECT_H
