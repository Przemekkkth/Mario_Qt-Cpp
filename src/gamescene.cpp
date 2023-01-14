#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QDir>
#include <QGraphicsRectItem>
#include "entities/mario.h"
#include "entities/questionblock.h"
#include "entities/mushroom.h"
#include "entities/enemy.h"


GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_mostRightX(200000),
      m_loopSpeed(int(1000.0f/GLOBAL::FPS))
{

    m_mapManager.updateMapSketch(0);
    m_mapManager.convertFromSketch(0);
    m_mostRightX = float(m_mapManager.getMapSketchWidth()*GLOBAL::TILE_SIZE.width()-GLOBAL::SCREEN_SIZE.width());
    m_mario = new Mario();
    m_mario->setMaxX(m_mostRightX+GLOBAL::SCREEN_SIZE.width());
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
    while( m_loopTime > m_loopSpeed)
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
        setBackgroundBrush(QBrush(QColor(Qt::black)));
        float cameraPosX = std::clamp(getCameraX(*m_mario), 0.0f, m_mostRightX);
        QGraphicsRectItem* bgRect = new QGraphicsRectItem();
        bgRect->setRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        bgRect->setPos(cameraPosX, 0);
        bgRect->setPen(QColor(0, 219, 255));
        bgRect->setBrush(QColor(0, 219, 255));
        addItem(bgRect);
        m_mapManager.drawBackground(cameraPosX, *this);
        m_mapManager.drawForeground(cameraPosX, *this);
        m_mario->draw(*this);
        for(int i = 0; i < Mushroom::MUSHROOMS.size(); ++i)
        {
            Mushroom::MUSHROOMS.at(i)->draw(*this);
        }
        for(int i = 0; i < Enemy::ENEMIES.size(); ++i)
        {
            Enemy::ENEMIES.at(i)->draw(*this);
        }
        setSceneRect(cameraPosX, 0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        //Add boundary
        QGraphicsRectItem* lRect = new QGraphicsRectItem();
        lRect->setPen(QColor(Qt::black));
        lRect->setBrush(QColor(Qt::black));
        lRect->setRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        lRect->setPos(sceneRect().x()-GLOBAL::SCREEN_SIZE.width(), 0);
        lRect->setZValue(1000);
        addItem(lRect);
        QGraphicsRectItem* rRect = new QGraphicsRectItem();
        rRect->setPen(QColor(Qt::black));
        rRect->setBrush(QColor(Qt::black));
        rRect->setRect(0,0, GLOBAL::SCREEN_SIZE.width(), GLOBAL::SCREEN_SIZE.height());
        rRect->setPos(sceneRect().x()+GLOBAL::SCREEN_SIZE.width(), 0);
        rRect->setZValue(1000);
        addItem(rRect);

        //reset key/mouse status, reset frame counter
        resetKeyStatus();
        m_loopTime -= m_loopSpeed;
    }
}

void GameScene::handlePlayerInput()
{
    if(m_keys[GLOBAL::R_KEY]->m_released || m_keys[GLOBAL::ENTER_KEY]->m_released)
    {
        resetGameScene();
    }
    if(m_keys[GLOBAL::Z_KEY]->m_released)
    {
        //renderGameScene();//uncomment if you want to make screenshots
    }
}

void GameScene::resetKeyStatus()
{
    for(int i = 0; i < GLOBAL::COUNT_OF_KEYS; ++i)
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

void GameScene::renderGameScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

float GameScene::getCameraX(const Mario &mario)
{
    if(mario.x() < GLOBAL::SCREEN_SIZE.width()/2){
        return 0.0f;
    }
    else
    {
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
