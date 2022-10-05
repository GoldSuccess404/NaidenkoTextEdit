#ifndef DIALOGNEWFILE_H
#define DIALOGNEWFILE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class dialogNewFile : public QWidget
{
    Q_OBJECT
public:
    explicit dialogNewFile(QWidget *parent = nullptr);
private:
    QLabel *name;
    QLineEdit *line;
    QComboBox *cb;
    QPushButton *ok;
    QPushButton *cancel;
public slots:
    void getFileName();
signals:
    void fileReady(QString str);

};

#endif // DIALOGNEWFILE_H
