#ifndef MUSHROOM_H
#define MUSHROOM_H
#include "entity.h"
#include "../utils/animator.h"
#include <QPixmap>

class Mushroom : public Entity
{
public:
    static constexpr const float MUSHROOM_SPEED = 40.f;
    Mushroom(float x, float y);
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
private:
    void createAnimation();
    float m_velocityX, m_velocityY;
    Animator m_animator;
    QPixmap m_texturePixmap;
};

#endif // MUSHROOM_H
