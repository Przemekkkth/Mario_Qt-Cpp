#include "mushroom.h"

Mushroom::Mushroom(float x, float y)
{
    setPosition(x, y);
    createAnimation();
}

void Mushroom::draw(GameScene &scene)
{

}

void Mushroom::update(float elapsedTime)
{

}

void Mushroom::createAnimation()
{
    m_texturePixmap.load(":/res/mario_items_18x18.png");

    //x = 0, y = 5, 2frames left to right
    const float TW  = GLOBAL::TEXTURE_SIZE.width();
    const float TH  = GLOBAL::TEXTURE_SIZE.height();
    const float TSW = GLOBAL::TILE_SIZE.width();
    const float TSH = GLOBAL::TILE_SIZE.height();

    m_animator.m_mapStates["idle"].push_back(m_texturePixmap.copy(0 * TW,
                                                               5 * TH,
                                                               TW,
                                                               TH).scaled(TSW, TSH));
    m_animator.m_mapStates["idle"].push_back(m_texturePixmap.copy(1 * TW,
                                                               5 * TH,
                                                               TW,
                                                               TH).scaled(TSW, TSH));
}
