#include "goomba.h"
#include <QGraphicsPixmapItem>

Goomba::Goomba(float x, float y)
    : Enemy(x, y)
{
    createAnimation();
}

Goomba::~Goomba()
{

}

void Goomba::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setZValue(GLOBAL::ENEMY_LAYER);
    pItem->setPos(int(position().x()), int(position().y()));
    pItem->setPixmap(m_animator.pixmap());
    scene.addItem(pItem);
}

void Goomba::update(float elapsedTime)
{
    m_animator.update(elapsedTime);
}

void Goomba::createAnimation()
{
    if(!m_texturePixmap.load(":/res/enemies_18x18.png"))
    {
        qDebug() << "Not loaded => :/res/enemies_18x18.png";
    }
    float TSW = GLOBAL::ENEMY_TEXTURE_SIZE.width();
    float TSH = GLOBAL::ENEMY_TEXTURE_SIZE.height();
    float TW  = GLOBAL::TILE_SIZE.width();
    float TH  = GLOBAL::TILE_SIZE.height();

    //0 1 2frames
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(0, TSH, TSW, TSH).scaled(TW, TH));
    m_animator.m_mapStates["running"].push_back(m_texturePixmap.copy(TSW, TSH, TSW, TSH).scaled(TW, TH));

    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(0, TSH, TSW, TSH).scaled(TW, TH).transformed(QTransform().scale(-1,1)));
    m_animator.m_mapStates["running_f_"].push_back(m_texturePixmap.copy(TSW, TSH, TSW, TSH).scaled(TW, TH).transformed(QTransform().scale(-1,1)));


    m_animator.m_mapStates["die"].push_back(m_texturePixmap.copy(0, TSH, TSW, TSH).scaled(TW, TH));
    m_animator.m_mapStates["die_f_"].push_back(m_texturePixmap.copy(0, TSH, TSW, TSH).scaled(TW, TH).transformed(QTransform().scale(-1,1)));

    m_animator.changeState("running");
    m_animator.m_timeBetweenFrames = 0.5f;
}
