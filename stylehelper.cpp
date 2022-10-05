#include "stylehelper.h"


QString styleHelper::getStyleTextEdit()
{
  return "QTextEdit{"
         "background-color: #EAEAEA;"
         "}";
}

QString styleHelper::getDarkThemeTextEdit()
{
    return "QTextEdit{"
           "background-color: black;"
           "}";
}

QString styleHelper::getStyleSideBar()
{
  return
         "background-color: #EAEAEA;"
         "border: none;"
          ;
}

QString styleHelper::getDarkThemeSideBar()
{
    return
           "background-color: black;"
           "border: none;"
            ;
}

QString styleHelper::getStyleMenuBar()
{
  return "QMenuBar{"
          "background-color: #3D84A8;"
          "font-family: Georgia;"
          "font-size: 17px;"
          "height: 23px"
         "}"

         "QMenuBar::item:selected{"
         "background: #457992;"
         "}";
}

QString styleHelper::getDarkThemeMenuBar()
{
    return "QMenuBar{"
            "background-color: black;"
            "color: white;"
            "font-family: Georgia;"
            "font-size: 17px;"
            "height: 23px"
           "}"

           "QMenuBar::item:selected{"
           "background: #1F261C;"
           "}";
}

QString styleHelper::getStyleMenu()
{
 return  "QMenu{"
         "background-color: #3D84A8;"
         "font-family: Georgia;"
         "font-size: 17px;"
         "}"
         "QMenu::item:selected{"
         "background-color: #457992;"
         "}";
}

QString styleHelper::getDarkThemeMenu()
{
    return  "QMenu{"
            "background-color: black;"
            "color: white;"
            "font-family: Georgia;"
            "font-size: 17px;"
            "}"
            "QMenu::item:selected{"
            "background-color: #1F261C;"
            "}";
}
