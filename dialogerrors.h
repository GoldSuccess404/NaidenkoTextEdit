#ifndef DIALOGERRORS_H
#define DIALOGERRORS_H

#include <QDialog>
#include <QString>
#include <QTextEdit>
#include <QHBoxLayout>
class dialogErrors : public QDialog
{
    Q_OBJECT
public:
    dialogErrors(QWidget *parent, QString text);
private:
    QTextEdit *textError;
};

#endif // DIALOGERRORS_H
