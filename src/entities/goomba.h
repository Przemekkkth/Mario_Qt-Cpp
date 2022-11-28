#ifndef GOOMBA_H
#define GOOMBA_H
#include "enemy.h"
#include "../utils/animator.h"

class Block;
class Goomba : public Enemy
{
public:
    static constexpr const float GOOMBA_SPEED = 80.f;
    Goomba(float x, float y);
    virtual ~Goomba();
    // Entity interface
public:
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    void checkCollisionWithBlocks();
    void collideWithBlock(Block* block);
private:
    void createAnimation();
    QRectF hitBox();
    void setDirection(bool isRight);
    int direction() const;
    float m_velocityX, m_velocityY;
    QPixmap m_texturePixmap;
    Animator m_animator;
    bool m_isRight;

};

#endif // GOOMBA_H
