#include "mushroom.h"
#include <QList>
#include <QGraphicsPixmapItem>

QList<Mushroom*> Mushroom::MUSHROOMS;

void Mushroom::CreateMushroom(QPointF pos, Type type)
{
    Mushroom* mushroom = new Mushroom(pos.x(), pos.y());
    mushroom->setType(type);
}

Mushroom::Mushroom(float x, float y)
{
    setPosition(x, y);
    createAnimation();
    MUSHROOMS.push_back(this);
}

Mushroom::~Mushroom()
{
    MUSHROOMS.removeOne(this);
}

void Mushroom::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    //pItem->setZValue(GLOBAL::PARTICLE_LAYER);
    pItem->setPos(int(position().x()), int(position().y()));
    pItem->setPixmap(m_animator.pixmap());
    scene.addItem(pItem);
}

void Mushroom::update(float elapsedTime)
{
    m_animator.update(elapsedTime);
    setPosition(position().x(), position().y());
    //qDebug() << m_animator.m_currentFrame;
}

Mushroom::Type Mushroom::type() const
{
    return m_type;
}

void Mushroom::setType(Type type)
{
    m_type = type;
}

void Mushroom::createAnimation()
{
    m_texturePixmap.load(":/res/mario_items_18x18.png");

    //x = 0, y = 5, 2frames left to right
    const float TW  = GLOBAL::MARIO_TEXTURE_SIZE.width();
    const float TH  = GLOBAL::MARIO_TEXTURE_SIZE.height();
    const float TSW = GLOBAL::TILE_SIZE.width();
    const float TSH = GLOBAL::TILE_SIZE.height();

    m_animator.m_mapStates["idle"].push_back(m_texturePixmap.copy(0 * TW,
                                                               5 * TW,
                                                               TW,
                                                               TH).scaled(TSW, TSH));
    m_animator.m_mapStates["idle"].push_back(m_texturePixmap.copy(1 * TW,
                                                               5 * TH,
                                                               TW,
                                                               TH).scaled(TSW, TSH));
    m_animator.changeState("idle");
    m_animator.m_timeBetweenFrames = 0.5f;
}
