#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "entities/mario.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_loopSpeed(int(1000.0f/GLOBAL::FPS)),
      m_x(0)
{

    m_mapManager.updateMapSketch(0);
    m_mapManager.convertFromSketch(0);
    //m_mapManager.drawForeground(0, *this);
    //exit(0);
    //m_mapManager.printMap();
    m_mario = new Mario();
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i] = new KeyStatus();
    }
    m_mouse = new MouseStatus();
    setSceneRect(0,0, 640, 480);
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();

}

KeyStatus *GameScene::keys(int keyCode)
{
    return m_keys[keyCode];
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed)
    {
        const float elapsedTime = 1.0f/FPS;
//input
        handlePlayerInput();
        m_mario->update(elapsedTime, *this);
//update
//draw
        clear();
//qDebug() << "m_x " << m_x;
        m_mapManager.drawBackground(0,*this);
        m_mapManager.drawForeground(0, *this);
        m_mario->draw(*this);
        setSceneRect(0, 0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
//reset key/mouse status, reset frame counter
        resetStatus();
        m_loopTime -= m_loopSpeed;
    }
}

void GameScene::handlePlayerInput()
{
    if(m_mouse->m_released)
    {
        qDebug() << "m_mouse->m_released " << m_mouse->m_released;
    }
    if(m_keys[Qt::Key_A]->m_held)
    {
        m_x -= 10;
    }
    if(m_keys[Qt::Key_D]->m_held)
    {
        m_x += 10;
    }
}

void GameScene::resetStatus()
{
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_released = false;
    }
    m_mouse->m_released = false;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    m_keys[event->key()]->m_held = true;
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    m_keys[event->key()]->m_held = false;
    m_keys[event->key()]->m_released = true;
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = true;
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = false;
    m_mouse->m_released = true;
    QGraphicsScene::mouseReleaseEvent(event);
}
