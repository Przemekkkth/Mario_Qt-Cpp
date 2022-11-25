#ifndef PARTICLE_H
#define PARTICLE_H
#include "entity.h"
#include "../utils/animator.h"

class Particle : public Entity
{
public:
    Particle(float x, float y, float hSpeed, float vSpeed);
    virtual ~Particle();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;

    void setAnimator(Animator animator);
    void setMinYValue(float y);
    bool isAlive();
private:
    float m_horizontalSpeed;
    float m_verticalSpeed;
    float m_minYValue;
    bool m_alive;
    Animator m_animator;
};

#endif // PARTICLE_H
