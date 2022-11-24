#include "mario.h"
#include "block.h"
#include <QGraphicsPixmapItem>

Mario::Mario()
    : m_brake(false), m_big(false), m_fliped(false), m_velocityX(0.0f), m_velocityY(0.0f), m_onGround(false), m_runMode(false)
{
    m_texture = QPixmap(":/res/mario_items_18x18.png");
    m_pixmap = QPixmap(":/res/mario_items_18x18.png")
            .copy(0,4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
            .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());

    //0 4 1frame
    m_animator.m_mapStates["small_idle"].push_back(m_texture.copy(0,4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
                                                   .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    //2 4 1frame
    m_animator.m_mapStates["small_jump"].push_back(m_texture.copy(2*GLOBAL::MARIO_TEXTURE_SIZE.width(),4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
                                                   .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    //4 4 3frames
    m_animator.m_mapStates["small_run"].push_back(m_texture.copy(4*GLOBAL::MARIO_TEXTURE_SIZE.width(),4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
                                                  .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    m_animator.m_mapStates["small_run"].push_back(m_texture.copy(5*GLOBAL::MARIO_TEXTURE_SIZE.width(),4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
                                                  .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    m_animator.m_mapStates["small_run"].push_back(m_texture.copy(6*GLOBAL::MARIO_TEXTURE_SIZE.width(),4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
                                                  .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    //1 4 1frame
    m_animator.m_mapStates["small_brake"].push_back(m_texture.copy(1*GLOBAL::MARIO_TEXTURE_SIZE.width(),4*GLOBAL::MARIO_TEXTURE_SIZE.width(), GLOBAL::MARIO_TEXTURE_SIZE.width(),GLOBAL::MARIO_TEXTURE_SIZE.width())
                                                    .scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));

    m_animator.changeState("small_brake");
    m_animator.m_timeBetweenFrames = 0.25f;
}

void Mario::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setPos(int(position().x()), int(position().y()));
    pItem->setPixmap(m_animator.pixmap());
    scene.addItem(pItem);
}

void Mario::update(float elapsedTime)
{
    m_velocityY += GLOBAL::GRAVITY;
    // Drag
    if (m_onGround)
    {
        m_velocityX += -DRAG_VALUE * m_velocityX * elapsedTime;
        if (std::fabs(m_velocityX) < 0.01f)
        {
            m_velocityX = 0.0f;
        }
    }
    clampVelocities(elapsedTime);
    checkCollisionWithBlocks();
    setPosition(int(position().x() + m_velocityX), int(position().y() + m_velocityY));

    // Set Animation
    if(m_onGround && std::fabs(m_velocityX) > 1.f)
    {
        setAnimatationState("small_run");
        if(std::fabs(m_velocityX) > 0.95*MAX_MOVE_SPEED)
        {
            m_brake = false;
        }
    }
    if(m_onGround && std::fabs(m_velocityX) < 0.5f)
    {
        if(m_brake)
        {
            setAnimatationState("small_brake");
        }
        else
        {
            setAnimatationState("small_idle");
        }
    }
    if(!m_onGround){
        setAnimatationState("small_jump");
    }
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
            if(m_velocityX == +MAX_MOVE_SPEED * elapsedTime)
            {
                m_brake = true;
            }
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
            if(m_velocityX == -MAX_MOVE_SPEED * elapsedTime)
            {
                m_brake = true;
            }
            m_velocityX += (m_onGround ? +MOVE_SPEED : +0.75*MOVE_SPEED) * elapsedTime;
        }
    }
    if(scene.keys(Qt::Key_Z)->m_released)
    {
        if (m_onGround)
        {
            m_velocityY = -JUMP_SPEED * elapsedTime;
            //nDirModX = 1;
        }
    }
    else
    {
        //        if (m_velocityY != 0)
        //        {
        //            if(m_velocityY < 0.0f)
        //                m_velocityY = 0.0f;
        //            //nDirModX = 0;
        //        }
    }
    update(elapsedTime);
    m_animator.update(elapsedTime);
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

void Mario::collideWithBlock(Block* block)
{
    // Calculate potential new position
    float CollideX;
    float CollideY;
    float shrinkPixel = 5.f, shrinkFactor = 0.9f;//For one tile row, column to avoid block

    //X-axis
    if (m_velocityX <= 0.0f) // Moving Left
    {
        CollideX = position().x() + m_velocityX;
        if(block->hitBox().contains(CollideX, position().y())
                ||
                block->hitBox().contains(CollideX, position().y()+hitBox().height()))
        {
            m_velocityX = 0.0f;
        }
    }
    else // Moving Right
    {
        CollideX = position().x() + hitBox().width() + m_velocityX;
        if(block->hitBox().contains(CollideX, position().y())
                ||
                block->hitBox().contains(CollideX, position().y()+hitBox().height()))
        {
            m_velocityX = 0.0f;
        }
    }
    //Y-axis
    if (m_velocityY < 0.0f) // Moving Up
    {
        m_onGround = false;
        CollideY = position().y() + m_velocityY;
        if(block->hitBox().contains(position().x()+shrinkPixel, CollideY)
                ||
                block->hitBox().contains(position().x()+shrinkFactor*hitBox().width() , CollideY))
        {
            m_velocityY = 0.1f;
        }
    }
    else // Moving Down
    {
        CollideY = position().y() + hitBox().height() + m_velocityY;
        if(block->hitBox().contains(position().x()+shrinkPixel, CollideY)
                ||
                block->hitBox().contains(position().x()+shrinkFactor*hitBox().width() , CollideY))
        {
            m_velocityY = 0.0f;
            m_onGround = true;
        }
    }
}

void Mario::setAnimatationState(QString state)
{
    //if big, add to state '_b_'
    if(m_big)
    {
        state += "_b_";
    }
    //if fliped, add to state '_f_'
    if(m_fliped)
    {
        state += "_f_";
    }
    m_animator.changeState(state);
}

void Mario::checkCollisionWithBlocks()
{

    for(int i = 0; i < Block::BLOCKS.size(); ++i)
    {

        collideWithBlock(Block::BLOCKS.at(i));
    }
}

QRectF Mario::hitBox()
{
    return QRectF(position().x(), position().y(), GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}
