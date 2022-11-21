#include "animator.h"
#include <QGraphicsPixmapItem>

Animator::Animator()
{

}

void Animator::changeState(QString state)
{
    if(state != m_currentState)
    {
        m_currentState = state;
        m_timeCounter  = 0.0f;
        m_currentFrame = 0;
    }
}

void Animator::update(float elapsedTime)
{
    m_timeCounter += elapsedTime;
    if (m_timeCounter >= m_timeBetweenFrames)
    {
        m_timeCounter -= m_timeBetweenFrames;
        m_currentFrame++;
        if (m_currentFrame >= m_mapStates[m_currentState].size())
        {
            m_currentFrame = 0;
        }
    }
}

QPixmap Animator::pixmap() const
{
    return m_mapStates[m_currentState][m_currentFrame];
}

void Animator::draw(GameScene &scene, QPointF position)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setPixmap(pixmap());
    pItem->setPos(position);
    scene.addItem(pItem);
}
