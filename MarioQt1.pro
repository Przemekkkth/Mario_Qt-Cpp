greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    src/entities/block.h \
    src/entities/entity.h \
    src/entities/mario.h \
    src/gamescene.h \
    src/utils/animator.h \
    src/utils/global.h \
    src/utils/mapmanager.h \
    src/view.h

SOURCES += \
    src/entities/block.cpp \
    src/entities/entity.cpp \
    src/entities/mario.cpp \
    src/gamescene.cpp \
    src/main.cpp \
    src/utils/animator.cpp \
    src/utils/mapmanager.cpp \
    src/view.cpp

RESOURCES += \
    resources.qrc
