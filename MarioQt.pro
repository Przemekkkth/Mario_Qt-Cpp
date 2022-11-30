greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    src/entities/block.h \
    src/entities/brick.h \
    src/entities/enemy.h \
    src/entities/entity.h \
    src/entities/goomba.h \
    src/entities/mario.h \
    src/entities/mushroom.h \
    src/entities/particle.h \
    src/entities/questionblock.h \
    src/gamescene.h \
    src/utils/animator.h \
    src/utils/global.h \
    src/utils/mapmanager.h \
    src/view.h

SOURCES += \
    src/entities/block.cpp \
    src/entities/brick.cpp \
    src/entities/enemy.cpp \
    src/entities/entity.cpp \
    src/entities/goomba.cpp \
    src/entities/mario.cpp \
    src/entities/mushroom.cpp \
    src/entities/particle.cpp \
    src/entities/questionblock.cpp \
    src/gamescene.cpp \
    src/main.cpp \
    src/utils/animator.cpp \
    src/utils/mapmanager.cpp \
    src/view.cpp

RESOURCES += \
    resources.qrc
