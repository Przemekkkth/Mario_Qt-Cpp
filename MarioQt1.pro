greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    src/gamescene.h \
    src/utils/global.h \
    src/view.h

SOURCES += \
    src/gamescene.cpp \
    src/main.cpp \
    src/view.cpp

RESOURCES += \
    resources.qrc
