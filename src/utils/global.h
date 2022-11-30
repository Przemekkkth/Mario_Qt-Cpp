#ifndef GLOBAL_H
#define GLOBAL_H
#include <QSize>
#include <QMap>
#include <QtGlobal>

namespace GLOBAL
{

static constexpr int FPS = 60;
static constexpr float FRAME_TIME = (1000.0f/60);
static constexpr int FRAME_TIME_INT = int(FRAME_TIME);

enum CELL_TYPE{
    Empty,
    Brick0,
    Coin,
    TopLeftPipe0,
    LeftPipe0,
    TopRightPipe0,
    RightPipe0,
    Wall0,
    Wall1,
    QuestionBlock0,
    QuestionBlock0M
};

static QString cellTypeToString(CELL_TYPE t)
{
    if(t == Empty)
    {
        return QString("Empty");
    }
    else if(t == Brick0)
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
static constexpr const QSize ENEMY_TEXTURE_SIZE = QSize(18,18);
static constexpr const QSize TILE_SIZE = QSize(TEXTURE_SIZE.width() * RESOLUTION_FACTOR.width(), TEXTURE_SIZE.height() * RESOLUTION_FACTOR.height());

static constexpr const float GRAVITY = 0.2f;

using Map = QVector<std::array<CELL_TYPE, SCREEN_SIZE.height() / TILE_SIZE.height()>>;

static constexpr const int ENTITY_UPDATE_AREA = 64;

//////////Layer z-value
static constexpr const int BG_LAYER       = 0;
static constexpr const int BLOCK_LAYER    = 10;
static constexpr const int ENEMY_LAYER    = 15;
static constexpr const int MARIO_LAYER    = 20;
static constexpr const int PARTICLE_LAYER = 30;
//////////Keys
static constexpr const int LEFT_ARROW_KEY  = 0;
static constexpr const int RIGHT_ARROW_KEY = 1;
static constexpr const int UP_ARROW_KEY    = 2;
static constexpr const int DOWN_ARROW_KEY  = 3;

static constexpr const int A_KEY           = 4;
static constexpr const int D_KEY           = 5;
static constexpr const int W_KEY           = 6;
static constexpr const int S_KEY           = 7;
static constexpr const int SPACE_KEY       = 8;

static constexpr const int ENTER_KEY       = 9;
static constexpr const int R_KEY           = 10;
static constexpr const int Z_KEY           = 11;


static constexpr const int COUNT_OF_KEYS   = 12;

static const QMap<int, int> KeysMapper =
{
    {static_cast<int>(Qt::Key_Left),  LEFT_ARROW_KEY},
    {static_cast<int>(Qt::Key_Right), RIGHT_ARROW_KEY},
    {static_cast<int>(Qt::Key_Up),    UP_ARROW_KEY},
    {static_cast<int>(Qt::Key_Down),  DOWN_ARROW_KEY},
    {static_cast<int>(Qt::Key_A),     A_KEY},
    {static_cast<int>(Qt::Key_D),     D_KEY},
    {static_cast<int>(Qt::Key_W),     W_KEY},
    {static_cast<int>(Qt::Key_S),     S_KEY},
    {static_cast<int>(Qt::Key_Space), SPACE_KEY},
    {static_cast<int>(Qt::Key_Enter), ENTER_KEY},
    {static_cast<int>(Qt::Key_Return),ENTER_KEY},
    {static_cast<int>(Qt::Key_R),     R_KEY},
    {static_cast<int>(Qt::Key_Z),     Z_KEY}
};
}

#endif // GLOBAL_H
