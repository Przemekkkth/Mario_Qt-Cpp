#include "entity.h"

Entity::Entity()
    : m_bodyType(GLOBAL::BODY_TYPE::STATIC),
      m_position(0.0f, 0.0f)
{

}

void Entity::draw(GameScene &scene)
{

}

void Entity::update(float elapsedTime)
{

}

void Entity::setBodyType(GLOBAL::BODY_TYPE bodyType)
{
    m_bodyType = bodyType;
}

GLOBAL::BODY_TYPE Entity::bodyType() const
{
    return m_bodyType;
}

QPointF Entity::position() const
{
    return m_position;
}

void Entity::setPosition(QPointF position)
{
    m_position = position;
}

void Entity::setPosition(float x, float y)
{
    m_position.setX(x);
    m_position.setY(y);
}

void Entity::setY(float y)
{
    m_position.setY(y);
}

void Entity::setX(float x)
{
    m_position.setX(x);
}

float Entity::y() const
{
    return m_position.y();
}

float Entity::x() const
{
    return m_position.x();
}
