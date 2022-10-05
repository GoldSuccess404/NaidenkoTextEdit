QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    darkhighlighting.cpp \
    dialogerrors.cpp \
    dialognewfile.cpp \
    dialognewproject.cpp \
    file.cpp \
    highlighting.cpp \
    main.cpp \
    menuwind.cpp \
    sidebar.cpp \
    stylehelper.cpp

HEADERS += \
    darkhighlighting.h \
    dialogerrors.h \
    dialognewfile.h \
    dialognewproject.h \
    file.h \
    highlighting.h \
    menuwind.h \
    sidebar.h \
    stylehelper.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    helloWorld.qrc \
    images.qrc
