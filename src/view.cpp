#include "view.h"
#include <QKeyEvent>
#include <QApplication>

View::View()
    : m_gameScene(new GameScene(this))
{
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width()+2, m_gameScene->sceneRect().height()+2);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    QGraphicsView::keyReleaseEvent(event);
}
