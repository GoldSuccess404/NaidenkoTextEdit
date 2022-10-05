#include "dialognewfile.h"

dialogNewFile::dialogNewFile(QWidget *parent)
    : QWidget{parent}
{
  name = new QLabel("Name: ");
  line = new QLineEdit;
  cb = new QComboBox;
  ok = new QPushButton("Ok");
  cancel = new QPushButton("Cancel");

  cb->addItem(".cpp");
  cb->addItem(".h");

  QHBoxLayout *hay1 = new QHBoxLayout;
  QHBoxLayout *hay2 = new QHBoxLayout;
  QVBoxLayout *vay = new QVBoxLayout;

  hay1->addWidget(line);
  hay1->addWidget(cb);

  hay2->addWidget(cancel);
  hay2->addWidget(ok);

  vay->addWidget(name);
  vay->addLayout(hay1);
  vay->addLayout(hay2);

  setLayout(vay);
  /*стили*/
  setWindowIcon(QIcon("://images/main.png"));
  setWindowTitle("NaidenkoTextEdit");
  setFixedSize(250,100);
  QFont font("Georgia", 13);
  name->setFont(font);
  cb->setFont(font);
  line->setFont(font);
  ok->setFont(font);
  cancel->setFont(font);


  QObject::connect(ok, SIGNAL(clicked(bool)), this, SLOT(getFileName()));
  QObject::connect(cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}


void dialogNewFile::getFileName()
{
  if (cb->currentIndex() == 0){
      emit fileReady(line->text() + ".cpp");
      line->clear();
      cb->setCurrentIndex(0);
      this->close();
  }
  else {
      emit fileReady(line->text() + ".h");
      line->clear();
      cb->setCurrentIndex(0);
      this->close();
  }
}



