#ifndef ENTITY_H
#define ENTITY_H
#include "../gamescene.h"
#include "../utils/global.h"
class Entity
{
public:
    Entity();
    ~Entity();
    static QPointF convertMapPointToScreenPoint(int x, int y);
    virtual void draw(GameScene& scene);
    virtual void update(float elapsedTime);

    void setBodyType(GLOBAL::BODY_TYPE bodyType);
    GLOBAL::BODY_TYPE bodyType() const;

    QPointF position() const;
    void setPosition(QPointF position);
    void setPosition(float x, float y);
    void setY(float y);
    void setX(float x);
    float y() const;
    float x() const;
private:
    GLOBAL::BODY_TYPE m_bodyType;
    QPointF m_position;
};

#endif // ENTITY_H
