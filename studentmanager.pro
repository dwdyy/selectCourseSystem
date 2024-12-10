QT       += core gui
win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    StuManage.cpp \
    filelist.cpp \
    main.cpp \
    mainwindow.cpp \
    mannager.cpp \
    page_login.cpp

HEADERS += \
    StuManage.h \
    fielist.h \
    mainwindow.h \
    mannager.h \
    page_login.h

FORMS += \
    mainwindow.ui \
    mannager.ui \
    page_login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    CourseData.txt \
    ManagerData.txt \
    StudentCourseData.txt \
    StudentData.txt
