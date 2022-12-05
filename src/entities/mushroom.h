#ifndef MUSHROOM_H
#define MUSHROOM_H
#include "entity.h"
#include "../utils/animator.h"
#include <QPixmap>

class Block;
class Mushroom : public Entity
{
public:
    enum class Type{
      Grow, Life
    };
    static constexpr const float MUSHROOM_SPEED = 80.f;
    static void CreateMushroom(QPointF pos, Type type);
    static QList<Mushroom*> MUSHROOMS;
    Mushroom(float x, float y);
    virtual ~Mushroom();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    Type type() const;
    void setType(Type type);
    void setDirection(bool isRight);
    int direction() const;
    QRect hitBox();
    void hit();
private:
    void createAnimation();
    void checkCollisionWithBlocks();
    void collideWithBlock(Block* block);
    float m_velocityX, m_velocityY;
    Animator m_animator;
    QPixmap m_texturePixmap;
    Type m_type;
    bool m_isRight;
};

#endif // MUSHROOM_H
