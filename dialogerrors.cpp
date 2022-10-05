#include "dialogerrors.h"

dialogErrors::dialogErrors(QWidget *parent, QString text)
    :QDialog(parent)
{
  this->setMinimumSize(350, 175);
  textError = new QTextEdit(this);
  textError->setText(text);
  QHBoxLayout *hay = new QHBoxLayout;
  hay->addWidget(textError);
  setLayout(hay);
  setWindowTitle("Errors");
}
