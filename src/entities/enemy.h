#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"

class Enemy : public Entity
{
public:
    enum class Type{
        None, Goomba
    };
    Enemy(float x, float y);
    virtual ~Enemy();
    virtual QRect hitBox() = 0;
    virtual void update(int cameraX, float elapsedTime) = 0;
    static QList<Enemy*> ENEMIES;
    static void CreateEnemy(Type type, QPointF position);
    void setAlive(bool on);
    bool isAlive() const;
private:
    bool m_isAlive;
};

#endif // ENEMY_H
