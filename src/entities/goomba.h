#ifndef GOOMBA_H
#define GOOMBA_H
#include "enemy.h"
#include "../utils/animator.h"

class Block;
class Enemy;
class Goomba : public Enemy
{
public:
    static constexpr const float GOOMBA_SPEED = 80.f;
    static constexpr const float GOOMBA_DEAD_TIMER = 1.5f;
    Goomba(float x, float y);
    virtual ~Goomba();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    virtual void update(int cameraX, float elapsedTime) override;
    void checkCollisionWithBlocks();
    void collideWithBlock(Block* block);
    void checkCollisonWithEnemies();
    void collideWithEnemy(Enemy* enemy);
private:
    void createAnimation();
    void setAnimation(QString state);
    virtual QRect hitBox() override;
    void setDirection(bool isRight);
    int direction() const;

    float m_velocityX, m_velocityY;
    QPixmap m_texturePixmap;
    Animator m_animator;
    bool m_isRight;
    float m_deathCounter;
    float m_speed;
};

#endif // GOOMBA_H
