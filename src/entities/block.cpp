#include "block.h"
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
    Block* block = new Block();
    //QPoint spritePosition = MapManager::cellToPointOfSpriteMap;
    block->setCellType(cType);
    QPoint spritePosition = MapManager::cellToPointOfSpriteMap.value(cType);
    block->setPixmap(
         QPixmap(":/res/map16x16.png").copy(spritePosition.x() * GLOBAL::TEXTURE_SIZE.width(),
                                            spritePosition.y() * GLOBAL::TEXTURE_SIZE.height(),
                                            GLOBAL::TEXTURE_SIZE.width(),
                                            GLOBAL::TEXTURE_SIZE.height()).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    block->setPosition(mapPosition);
}

void Block::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
}

QPixmap Block::pixmap() const
{
    return m_pixmap;
}

QRectF Block::hitBox()
{
    return QRectF(position().x(), position().y(),
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
    pItem->setPixmap(pixmap());
    pItem->setPos(position());
    scene.addItem(pItem);
}
