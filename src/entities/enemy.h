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
    static QList<Enemy*> ENEMIES;
    static void CreateEnemy(Type type, QPointF position);
};

#endif // ENEMY_H
