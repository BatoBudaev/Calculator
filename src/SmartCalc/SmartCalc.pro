QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_bank.c \
    ../s21_postfix.c \
    ../s21_stack.c \
    credit.cpp \
    deposit.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../s21_bank.h \
    ../s21_postfix.h \
    ../s21_stack.h \
    credit.h \
    deposit.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    deposit.ui \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
