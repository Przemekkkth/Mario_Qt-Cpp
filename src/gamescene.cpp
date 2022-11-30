#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "entities/mario.h"
#include "entities/questionblock.h"
#include "entities/mushroom.h"
#include "entities/enemy.h"

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
    setSceneRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
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
        for(int i = 0; i < Block::BLOCKS.size(); ++i)
        {
            Block::BLOCKS.at(i)->update(elapsedTime);
        }
        for(int i = 0; i < Mushroom::MUSHROOMS.size(); ++i)
        {
            Mushroom::MUSHROOMS.at(i)->update(elapsedTime);
        }
        for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
        {
            Enemy::ENEMIES.at(i)->update(getCameraX(*m_mario), elapsedTime);
        }
//draw
        clear();
        setBackgroundBrush(QBrush(QColor(0, 219, 255)));
        m_mapManager.drawBackground(getCameraX(*m_mario), *this);
        m_mapManager.drawForeground(getCameraX(*m_mario), *this);
        m_mario->draw(*this);
        for(int i = 0; i < Mushroom::MUSHROOMS.size(); ++i)
        {
            Mushroom::MUSHROOMS.at(i)->draw(*this);
        }
        for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
        {
            Enemy::ENEMIES.at(i)->draw(*this);
        }
        setSceneRect(getCameraX(*m_mario), 0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
//reset key/mouse status, reset frame counter
        resetStatus();
        m_loopTime -= m_loopSpeed;
    }
}

void GameScene::handlePlayerInput()
{
    if(m_keys[GLOBAL::R_KEY]->m_released || m_keys[GLOBAL::ENTER_KEY]->m_released)
    {
        resetGameScene();
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

void GameScene::resetGameScene()
{
    Block::BLOCKS.clear();
    Mushroom::MUSHROOMS.clear();
    Enemy::ENEMIES.clear();
    m_mapManager.updateMapSketch(0);
    m_mapManager.convertFromSketch(0);
    m_mario->resetStatus();
}

float GameScene::getCameraX(const Mario &mario)
{
    if(mario.x() < GLOBAL::SCREEN_SIZE.width()/2){
        return 0.0f;
    }
    else
    {
        //return QPointF(GLOBAL::SCREEN_SIZE.width()/2-GLOBAL::TILE_SIZE.width(), marioPos.y());
        return mario.position().x() - GLOBAL::SCREEN_SIZE.width()/2;
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(GLOBAL::KeysMapper.contains(event->key()))
    {
        m_keys[GLOBAL::KeysMapper[event->key()]]->m_held = true;
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(GLOBAL::KeysMapper.contains(event->key()))
    {
        m_keys[GLOBAL::KeysMapper[event->key()]]->m_held = false;
        m_keys[GLOBAL::KeysMapper[event->key()]]->m_released = true;
    }
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
