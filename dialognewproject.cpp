#include "dialognewproject.h"

DialogNewProject::DialogNewProject(QWidget *parent)
    : QWidget{parent}
{
  lab = new QLabel("Path: ");
  line = new QLineEdit;
  ok = new QPushButton("Ok");
  cancel = new QPushButton("Cancel");

  QHBoxLayout *hay = new QHBoxLayout;
  QVBoxLayout *vay = new QVBoxLayout;

  hay->addWidget(cancel);
  hay->addWidget(ok);

  vay->addWidget(lab);
  vay->addWidget(line);
  vay->addLayout(hay);

  setLayout(vay);
  /*стили*/
  setWindowIcon(QIcon("://images/main.png"));
  setWindowTitle("NaidenkoTextEdit");
  setFixedSize(250,100);

  QFont font("Georgia", 13);
  lab->setFont(font);
  line->setFont(font);
  ok->setFont(font);
  cancel->setFont(font);

  QObject::connect(ok, SIGNAL(clicked(bool)), this, SLOT(getNameProgect()));
  QObject::connect(cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void DialogNewProject::getNameProgect()
{
  emit nameProgect(line->text());
    line->clear();
    this->close();
}
