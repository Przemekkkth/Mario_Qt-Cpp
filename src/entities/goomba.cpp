#include "goomba.h"
#include <QGraphicsPixmapItem>
#include "block.h"

Goomba::Goomba(float x, float y)
    : Enemy(x, y), m_isRight(false)
{
    createAnimation();
}

Goomba::~Goomba()
{
    qDebug() << "~Goomba";
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
    m_velocityY += GLOBAL::GRAVITY;
    m_velocityX = direction()*GOOMBA_SPEED*elapsedTime;
    m_animator.update(elapsedTime);
    checkCollisionWithBlocks();
    setPosition(position().x() + m_velocityX, position().y() + m_velocityY);
    if(position().x() < 0.0f - GLOBAL::TILE_SIZE.width())
    {
        delete this;
    }
    if(position().y() > GLOBAL::SCREEN_SIZE.height()+GLOBAL::TILE_SIZE.height())
    {
        delete this;
    }
}

void Goomba::checkCollisionWithBlocks()
{
    for(int i = 0; i < Block::BLOCKS.size(); ++i)
    {

        collideWithBlock(Block::BLOCKS.at(i));
    }
}

void Goomba::collideWithBlock(Block *block)
{
    // Calculate potential new position
    float CollideX;
    float CollideY;
    float shrinkPixel = 5.f, shrinkFactor = 0.9f;//For one tile row, column to avoid block

    //X-axis
    if (m_velocityX <= 0.0f) // Moving Left
    {
        CollideX = position().x() + m_velocityX;
        if(block->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
        }
    }
    else // Moving Right
    {
        CollideX = position().x() + hitBox().width() + m_velocityX;
        if(block->hitBox().contains(int(CollideX), position().y()+hitBox().height()/2))
        {
            setDirection(!m_isRight);
        }
    }
    //Y-axis
    if(m_velocityY > 0.0f) // Moving Down
    {
        CollideY = position().y() + hitBox().height() + m_velocityY;
        if(block->hitBox().contains(position().x()+shrinkPixel, CollideY)
                ||
                block->hitBox().contains(position().x()+shrinkFactor*hitBox().width() , CollideY))
        {
            m_velocityY = 0.0f;
        }
    }
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

QRectF Goomba::hitBox()
{
    return QRectF(position().x(), position().y(), GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}

void Goomba::setDirection(bool isRight)
{
    m_isRight = isRight;
}

int Goomba::direction() const
{
    if(m_isRight)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
