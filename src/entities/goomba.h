#ifndef GOOMBA_H
#define GOOMBA_H
#include "enemy.h"
#include "../utils/animator.h"

class Goomba : public Enemy
{
public:
    Goomba(float x, float y);
    virtual ~Goomba();
    // Entity interface
public:
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
private:
    void createAnimation();
    QPixmap m_texturePixmap;
    Animator m_animator;
};

#endif // GOOMBA_H
