#ifndef BRICK_H
#define BRICK_H
#include "block.h"
#include "particle.h"

class Brick : public Block
{
public:
    static constexpr const float BRICK_PARTICLE_SPEED = 250.f;
    static constexpr const float BRICK_PARTICLE_FALLDOWN = 10.f;
    static void createBrick(QPointF position);
    Brick(float x, float y);
    virtual ~Brick();
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    void destroy();
    bool isDestroyed() const;
private:
    QPixmap m_brickPixmap;
    Particle *m_particle[4];
    bool m_isDestroyed;
};

#endif // BRICK_H
