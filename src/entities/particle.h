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
    Animator animator() const;
    void setMinYValue(float y);
    void setMaxYValue(float y);
    void setVerticalSpeed(float newVerticalSpeed);
    float verticalSpeed() const;
    bool isAlive();
private:
    float m_horizontalSpeed;
    float m_verticalSpeed;
    float m_minYValue, m_maxYValue;
    bool m_alive;
    Animator m_animator;
};

#endif // PARTICLE_H
