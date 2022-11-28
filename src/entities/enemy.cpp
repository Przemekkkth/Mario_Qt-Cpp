#include "enemy.h"
#include "goomba.h"

QList<Enemy*> Enemy::ENEMIES;

Enemy::Enemy(float x, float y)
{
    setPosition(x, y);
    ENEMIES.push_back(this);
}

Enemy::~Enemy()
{
    ENEMIES.removeOne(this);
}

void Enemy::CreateEnemy(Type type, QPointF position)
{
    if(type == Type::Goomba)
    {
        Goomba* goomba = new Goomba(position.x(), position.y());
    }
}
