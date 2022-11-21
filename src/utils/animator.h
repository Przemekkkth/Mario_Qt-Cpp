#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <QMap>
#include <QString>
#include <QVector>
#include <QPixmap>
#include "../gamescene.h"

class Animator
{
public:
    Animator();
    QMap<QString, QVector<QPixmap> > m_mapStates;
    QString m_currentState;
    int m_currentFrame = 0;
    float m_timeBetweenFrames = 0.1f;
    float m_timeCounter       = 0.0f;

    void changeState(QString state);
    void update(float elapsedTime);

    QPixmap pixmap() const;
    void draw(GameScene& scene, QPointF position);
};

#endif // ANIMATOR_H
