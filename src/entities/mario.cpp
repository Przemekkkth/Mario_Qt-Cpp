#include "mario.h"
#include <QGraphicsPixmapItem>

Mario::Mario()
    : m_velocityX(0.0f), m_velocityY(0.0f), m_onGround(false), m_runMode(false)
{
    m_pixmap = QPixmap(":/res/mario_items_18x18.png")
            .copy(0,4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
            .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}

void Mario::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setPos(position());
    pItem->setPixmap(m_pixmap);
    scene.addItem(pItem);
}

void Mario::update(float elapsedTime)
{
    //m_velocityY += GLOBAL::GRAVITY;
    // Drag
    if (!m_onGround)
    {
        m_velocityX += -DRAG_VALUE * m_velocityX * elapsedTime;
        if (std::fabs(m_velocityX) < 0.01f)
        {
            m_velocityX = 0.0f;
        }
    }
    clampVelocities(elapsedTime);
    qDebug() << m_velocityX;
    setPosition(position().x() + m_velocityX, position().y() + m_velocityY);
}

void Mario::update(float elapsedTime, GameScene &scene)
{
    if(scene.keys(Qt::Key_A)->m_held)
    {
        //in air mario is less control(0.75) than on ground
        if(m_runMode)
        {
            m_velocityX += (m_onGround ? -RUN_SPEED : -0.75f*RUN_SPEED) * elapsedTime;
        }
        else
        {
            m_velocityX += (m_onGround ? -MOVE_SPEED : -0.75*MOVE_SPEED) * elapsedTime;
        }
    }
    if(scene.keys(Qt::Key_D)->m_held)
    {
        //in air mario is less control(0.75) than on ground
        if(m_runMode)
        {
            m_velocityX += (m_onGround ? +RUN_SPEED : +0.75f*RUN_SPEED) * elapsedTime;
        }
        else
        {
            m_velocityX += (m_onGround ? +MOVE_SPEED : +0.75*MOVE_SPEED) * elapsedTime;
        }
    }
    if(scene.keys(Qt::Key_Z)->m_held)
    {
        if (m_velocityY == 0)
        {
            m_velocityY = -JUMP_SPEED;
            //nDirModX = 1;
        }
    }
    else
    {
        if (m_velocityY != 0)
        {
            if(m_velocityY < 0.0f)
                m_velocityY = 0.0f;
            //nDirModX = 0;
        }
    }
    update(elapsedTime);
}

void Mario::clampVelocities(float elapsedTime)
{
    if(m_runMode && m_velocityX > MAX_RUN_SPEED*elapsedTime)
    {
        m_velocityX = MAX_RUN_SPEED*elapsedTime;
    }
    else if (!m_runMode && m_velocityX > MAX_MOVE_SPEED*elapsedTime )
    {
        m_velocityX = MAX_MOVE_SPEED*elapsedTime;
    }

    if(m_runMode && m_velocityX < -MAX_RUN_SPEED*elapsedTime)
    {
        m_velocityX = -MAX_RUN_SPEED*elapsedTime;
    }
    else if (!m_runMode && m_velocityX < -MAX_MOVE_SPEED*elapsedTime)
    {
        m_velocityX = -MAX_MOVE_SPEED*elapsedTime;
    }

    if (m_velocityY > MAX_FALLDOWN_SPEED*elapsedTime)
    {
        m_velocityY = MAX_FALLDOWN_SPEED*elapsedTime;
    }

//    if (fPlayerVelY < -100.0f)
//    {
//        fPlayerVelY = -100.0f;
//    }
}
