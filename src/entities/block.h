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
    static void UpdateBlocks(float elapsedTime);
    void setPixmap(const QPixmap& pixmap);
    QPixmap pixmap() const;
    QRect hitBox();
    void setCellType(GLOBAL::CELL_TYPE cellType);
    GLOBAL::CELL_TYPE cellType() const;
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
private:
    GLOBAL::CELL_TYPE m_cellType;
    QPixmap m_pixmap;
};

#endif // BLOCK_H
