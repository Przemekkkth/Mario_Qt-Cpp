#include "particle.h"
#include <QGraphicsPixmapItem>

Particle::Particle(float x, float y, float hSpeed, float vSpeed)
    : m_horizontalSpeed(hSpeed), m_verticalSpeed(vSpeed), m_alive(true)
{
    setPosition(x, y);
    setMinYValue(-100);
    setMaxYValue(2000);
}

Particle::~Particle()
{

}

void Particle::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setZValue(GLOBAL::PARTICLE_LAYER);
    pItem->setPixmap(m_animator.pixmap());
    pItem->setPos(position());
    scene.addItem(pItem);

}

void Particle::update(float elapsedTime)
{
    if(position().y() < m_minYValue)
    {
        m_alive = false;
    }
    if(position().y() > m_maxYValue)
    {
        m_alive = false;
    }
    m_animator.update(elapsedTime);
    setPosition(position().x()+m_horizontalSpeed*elapsedTime,
                position().y()+m_verticalSpeed*elapsedTime);

}

void Particle::setAnimator(Animator animator)
{
    m_animator = animator;
}

Animator Particle::animator() const
{
    return m_animator;
}

void Particle::setMinYValue(float y)
{
    m_minYValue = y;
}

void Particle::setMaxYValue(float y)
{
    m_maxYValue = y;
}

void Particle::setVerticalSpeed(float newVerticalSpeed)
{
    m_verticalSpeed = newVerticalSpeed;
}

float Particle::verticalSpeed() const
{
    return m_verticalSpeed;
}

bool Particle::isAlive()
{
    return m_alive;
}
