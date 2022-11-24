#ifndef GLOBAL_H
#define GLOBAL_H
#include <QSize>

namespace GLOBAL
{

static constexpr int FPS = 60;
static constexpr float FRAME_TIME = (1000.0f/60);
static constexpr int FRAME_TIME_INT = int(FRAME_TIME);

enum CELL_TYPE{
    Empty,
    Brick,
    Coin,
    TopLeftPipe0,
    LeftPipe0,
    TopRightPipe0,
    RightPipe0,
    Wall0,
    Wall1,
    QuestionBlock
};

static QString cellTypeToString(CELL_TYPE t)
{
    if(t == Empty)
    {
        return QString("Empty");
    }
    else if(t == Brick)
    {
        return QString("Brick");
    }
    else if(t == Wall0)
    {
        return QString("Wall0");
    }
    else if(t == Wall1)
    {
        return QString("Wall1");
    }
    else
    {
        return QString("Invalid");
    }
}

enum BODY_TYPE
{
    NONE, STATIC, DYNAMIC
};

static constexpr const QSize WINDOW_SIZE = QSize(320, 240);
static constexpr const QSize SCREEN_SIZE = QSize(640, 480);
static constexpr const QSize RESOLUTION_FACTOR = QSize(SCREEN_SIZE.width()/WINDOW_SIZE.width(), SCREEN_SIZE.height()/WINDOW_SIZE.height());

static constexpr const QSize TEXTURE_SIZE = QSize(16,16);
static constexpr const QSize MARIO_TEXTURE_SIZE = QSize(18,18);
static constexpr const QSize TILE_SIZE = QSize(TEXTURE_SIZE.width() * RESOLUTION_FACTOR.width(), TEXTURE_SIZE.height() * RESOLUTION_FACTOR.height());

static constexpr const float GRAVITY = 0.2f;

using Map = QVector<std::array<CELL_TYPE, SCREEN_SIZE.height() / TILE_SIZE.height()>>;

}

#endif // GLOBAL_H
