#include "brick.h"
#include <QGraphicsPixmapItem>
#include "../utils/animator.h"

void Brick::createBrick(QPointF position)
{
    Brick *brick = new Brick(position.x(), position.y());
}

Brick::Brick(float x, float y)
    : m_isDestroyed(false)
{
    setPosition(x, y);
    const float TW  = GLOBAL::TEXTURE_SIZE.width();
    const float TH  = GLOBAL::TEXTURE_SIZE.height();
    const float TSW = GLOBAL::TILE_SIZE.width();
    const float TSH = GLOBAL::TILE_SIZE.height();

    setPixmap(QPixmap(":/res/map16x16.png"));
    m_brickPixmap = pixmap().copy(0,0,TW, TH).scaled(TSW, TSH);

    //00
    QPixmap pixmap00 = m_brickPixmap.copy(0,0, TSW/2, TSH/2);
    m_particle[0] = new Particle(position().x(), position().y(), -BRICK_PARTICLE_SPEED/4, -BRICK_PARTICLE_SPEED);
    Animator animator00;
    animator00.m_mapStates["idle"].push_back(pixmap00);
    animator00.changeState("idle");
    animator00.m_timeBetweenFrames = 1.f;
    m_particle[0]->setAnimator(animator00);
    //10
    QPixmap pixmap10 = m_brickPixmap.copy(TSW/2,0, TSW/2, TSH/2);
    m_particle[1] = new Particle(position().x()+TSW/2, position().y(), +BRICK_PARTICLE_SPEED/4, -BRICK_PARTICLE_SPEED);
    Animator animator10;
    animator10.m_mapStates["idle"].push_back(pixmap10);
    animator10.changeState("idle");
    animator10.m_timeBetweenFrames = 1.f;
    m_particle[1]->setAnimator(animator10);
    //01
    QPixmap pixmap01 = m_brickPixmap.copy(0, TSH/2, TSW/2, TSH/2);
    m_particle[2] = new Particle(position().x(), position().y()+TSW/2, -BRICK_PARTICLE_SPEED/3, -BRICK_PARTICLE_SPEED/2);
    Animator animator01;
    animator01.m_mapStates["idle"].push_back(pixmap01);
    animator01.changeState("idle");
    animator01.m_timeBetweenFrames = 1.f;
    m_particle[2]->setAnimator(animator01);
    //11
    QPixmap pixmap11 = m_brickPixmap.copy(TSW/2, TSH/2, TSW/2, TSH/2);
    m_particle[3] = new Particle(position().x()+TSW/2, position().y()+TSH/2, +BRICK_PARTICLE_SPEED/3, -BRICK_PARTICLE_SPEED/2);
    Animator animator11;
    animator11.m_mapStates["idle"].push_back(pixmap11);
    animator11.changeState("idle");
    animator11.m_timeBetweenFrames = 1.f;
    m_particle[3]->setAnimator(animator11);

}

Brick::~Brick()
{
    for(int i = 0; i < 4; i++)
    {
        if(m_particle[i])
        {
            delete m_particle[i];
        }
    }
}

void Brick::draw(GameScene &scene)
{
    if(!m_isDestroyed)
    {
        QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
        pItem->setZValue(GLOBAL::BLOCK_LAYER);
        pItem->setPos(int(position().x()), int(position().y()));
        pItem->setPixmap(m_brickPixmap);
        scene.addItem(pItem);
    }
    else
    {
        for(int i = 0; i < 4; ++i)
        {
            if(m_particle[i])
            {
                QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
                pItem->setZValue(GLOBAL::PARTICLE_LAYER);
                pItem->setPos(int(m_particle[i]->position().x()), int(m_particle[i]->position().y()));
                pItem->setPixmap(m_particle[i]->animator().pixmap());
                scene.addItem(pItem);
            }
        }
    }
}

void Brick::update(float elapsedTime)
{
    if(m_isDestroyed)
    {
        for(int i = 0; i < 4; ++i)
        {
            if(m_particle[i])
            {
                m_particle[i]->update(elapsedTime);
                m_particle[i]->setVerticalSpeed(m_particle[i]->verticalSpeed() + BRICK_PARTICLE_FALLDOWN);
            }
        }
        if(!m_particle[0]->isAlive() && !m_particle[1]->isAlive() && !m_particle[2]->isAlive()
                && !m_particle[3]->isAlive())
        {
           delete this;
        }
    }
}

void Brick::destroy()
{
    m_isDestroyed = true;
}

bool Brick::isDestroyed() const
{
    return m_isDestroyed;
}
