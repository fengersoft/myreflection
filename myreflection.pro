QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/api/dialogs/setvaluedialog.cpp \
    src/api/sql/sqldef.cpp \
    src/api/sql/sqlitedao.cpp \
    src/api/sql/sqlitewrapper.cpp \
    src/dialogs/setsubjectdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/widgets/recordwidget.cpp \
    src/widgets/subjectwidget.cpp

HEADERS += \
    src/api/dialogs/setvaluedialog.h \
    src/api/sql/sqldef.h \
    src/api/sql/sqlitedao.h \
    src/api/sql/sqlitewrapper.h \
    src/dialogs/setsubjectdialog.h \
    src/mainwindow.h \
    src/widgets/recordwidget.h \
    src/widgets/subjectwidget.h

FORMS += \
    src/api/dialogs/setvaluedialog.ui \
    src/dialogs/setsubjectdialog.ui \
    src/mainwindow.ui \
    src/widgets/recordwidget.ui \
    src/widgets/subjectwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DESTDIR=$$PWD/bin
RC_ICONS=app.ico

RESOURCES += \
    app.qrc
