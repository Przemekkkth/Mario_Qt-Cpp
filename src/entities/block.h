#ifndef BLOCK_H
#define BLOCK_H
#include "entity.h"

class Block : public Entity
{
public:
    Block();
    ~Block();
    static QList<Block*> BLOCKS;
    static void CreateBlock(GLOBAL::CELL_TYPE cType, QPointF mapPosition);
    void setPixmap(const QPixmap& pixmap);
    QPixmap pixmap() const;
    QRectF hitBox();

    void setCellType(GLOBAL::CELL_TYPE cellType);
    GLOBAL::CELL_TYPE cellType() const;
private:
    GLOBAL::CELL_TYPE m_cellType;
    QPixmap m_pixmap;

    // Entity interface
public:
    virtual void draw(GameScene &scene) override;
};

#endif // BLOCK_H
