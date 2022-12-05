#include "block.h"
#include "questionblock.h"
#include "brick.h"
#include "../utils/mapmanager.h"
#include <QMap>
#include <QGraphicsPixmapItem>

QList<Block*> Block::BLOCKS;

Block::Block()
{
    BLOCKS.push_back(this);
}

Block::~Block()
{
    BLOCKS.removeOne(this);
}

void Block::CreateBlock(GLOBAL::CELL_TYPE cType, QPointF mapPosition)
{
    if(cType == GLOBAL::QuestionBlock0 || cType == GLOBAL::QuestionBlock0M)
    {
        if(cType == GLOBAL::QuestionBlock0M)
        {
            QuestionBlock::CreateQuestionBlock(mapPosition, QuestionBlock::Type::PowerSupply);
        }
        else
        {
            QuestionBlock::CreateQuestionBlock(mapPosition);
        }
    }
    else if(cType == GLOBAL::Brick0)
    {
        Brick::createBrick(mapPosition);
    }
    else
    {
        Block* block = new Block();
        block->setCellType(cType);
        QPoint spritePosition = MapManager::cellToPointOfSpriteMap.value(cType);
        block->setPixmap(
                    QPixmap(":/res/map16x16.png").copy(spritePosition.x() * GLOBAL::TEXTURE_SIZE.width(),
                                                       spritePosition.y() * GLOBAL::TEXTURE_SIZE.height(),
                                                       GLOBAL::TEXTURE_SIZE.width(),
                                                       GLOBAL::TEXTURE_SIZE.height()).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
        block->setPosition(mapPosition);
    }
}

void Block::UpdateBlocks(float elapsedTime)
{
    foreach(Block* block, BLOCKS)
    {
        block->update(elapsedTime);
    }
}

void Block::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
}

QPixmap Block::pixmap() const
{
    return m_pixmap;
}

QRect Block::hitBox()
{
    return QRect(position().x(), position().y(),
                  GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height());
}

void Block::setCellType(GLOBAL::CELL_TYPE cellType)
{
    m_cellType = cellType;
}

GLOBAL::CELL_TYPE Block::cellType() const
{
    return m_cellType;
}

void Block::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setZValue(GLOBAL::BLOCK_LAYER);
    pItem->setPixmap(pixmap());
    pItem->setPos(position());
    scene.addItem(pItem);
}

void Block::update(float)
{

}
