#include "mushroom.h"
#include <QList>
#include <QGraphicsPixmapItem>
#include "block.h"

QList<Mushroom*> Mushroom::MUSHROOMS;

void Mushroom::CreateMushroom(QPointF pos, Type type)
{
    Mushroom* mushroom = new Mushroom(pos.x(), pos.y());
    mushroom->setDirection(true);
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
    m_velocityY += GLOBAL::GRAVITY;
    m_velocityX = direction()*MUSHROOM_SPEED*elapsedTime;
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

Mushroom::Type Mushroom::type() const
{
    return m_type;
}

void Mushroom::setType(Type type)
{
    m_type = type;
}

void Mushroom::setDirection(bool isRight)
{
    m_isRight = isRight;
}

int Mushroom::direction() const
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

QRect Mushroom::hitBox()
{
    return QRect(position().x(), position().y(), GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}

void Mushroom::hit()
{
    delete this;
}

void Mushroom::checkCollisionWithBlocks()
{
    for(int i = 0; i < Block::BLOCKS.size(); ++i)
    {

        collideWithBlock(Block::BLOCKS.at(i));
    }
}

void Mushroom::collideWithBlock(Block* block)
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
