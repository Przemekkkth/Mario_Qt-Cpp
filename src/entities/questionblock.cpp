#include "questionblock.h"
#include "mushroom.h"
#include <QGraphicsPixmapItem>
#include <QList>

QList<QuestionBlock*> QuestionBlock::QUESTION_BLOCKS;

QuestionBlock::QuestionBlock()
    : m_activate(true), m_coinParticle(nullptr)
{
    setCellType(GLOBAL::QuestionBlock0);
    createBlinkingAnimation();
    createCoinAnimation();
    QUESTION_BLOCKS.push_back(this);
}

QuestionBlock::~QuestionBlock()
{
    QUESTION_BLOCKS.removeOne(this);
    if(m_coinParticle)
    {
        delete m_coinParticle;
    }
}

void QuestionBlock::CreateQuestionBlock(QPointF position, Type type)
{
    QuestionBlock* questionBlock = new QuestionBlock();
    questionBlock->setType(type);
    questionBlock->setPosition(position);
}

void QuestionBlock::UpdateQuestionBlocks(float elapsedTime)
{
    foreach(QuestionBlock* questionBlock, QUESTION_BLOCKS)
    {
        questionBlock->update(elapsedTime);
    }
}

void QuestionBlock::draw(GameScene &scene)
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    if(m_activate)
    {
        pItem->setPixmap(m_animator.pixmap());
    }
    else
    {
        pItem->setPixmap(m_deactivatePixmap);
    }
    pItem->setPos(position());
    scene.addItem(pItem);
    //draw other element ie coin
    if(!m_activate)
    {
        if(m_type == QuestionBlock::Type::Coin)
        {
            if(m_coinParticle)
            {
                m_coinParticle->draw(scene);
            }
        }
        else if(m_type == QuestionBlock::Type::PowerSupply)
        {

        }

    }
}

void QuestionBlock::update(float elapsedTime)
{
    if(m_activate)
    {
        m_animator.update(elapsedTime);
    }
    else
    {
        //draw other element ie coin
        if(!m_activate)
        {
            if(m_type == QuestionBlock::Type::Coin)
            {
                if(m_coinParticle)
                {
                    m_coinParticle->update(elapsedTime);
                    if(!m_coinParticle->isAlive())
                    {
                        delete m_coinParticle;
                        m_coinParticle = nullptr;
                    }
                }
            }
            else if(m_type == QuestionBlock::Type::PowerSupply)
            {
                Mushroom::CreateMushroom(QPointF(position().x(), position().y()-GLOBAL::TILE_SIZE.height()),
                                         Mushroom::Type::Grow);
                setType(QuestionBlock::Type::None);
            }
        }
    }
}

void QuestionBlock::deactivate()
{
    m_activate = false;
    if(!m_coinParticle)
    {
        float TW = GLOBAL::TILE_SIZE.width();
        m_coinParticle = new Particle(position().x(), position().y()-TW, 0, -COIN_SPEED);
        m_coinParticle->setAnimator(m_coinAnimation);
        m_coinParticle->setMinYValue(m_coinParticle->position().y() - 4*TW);
    }
}

bool QuestionBlock::isActivate()
{
    return m_activate;
}

void QuestionBlock::setType(Type type)
{
    m_type = type;
}

void QuestionBlock::createCoinAnimation()
{
    m_coinTexturePixmap.load(":/res/coin16x16.png");
    //0 0 10frames
    float TW = GLOBAL::TEXTURE_SIZE.width();
    float TH = GLOBAL::TEXTURE_SIZE.height();
    float TSW = GLOBAL::TILE_SIZE.width();
    float TSH = GLOBAL::TILE_SIZE.height();
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(0*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(1*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(2*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(3*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(4*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(5*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(6*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(7*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(8*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_mapStates["coin_spinning"].push_back(m_coinTexturePixmap.copy(9*TW, 0, TW, TH).scaled(TSW, TSH));
    m_coinAnimation.m_timeBetweenFrames = 0.1f;
    m_coinAnimation.changeState("coin_spinning");
}

void QuestionBlock::createBlinkingAnimation()
{
    setPixmap(QPixmap(":/res/map16x16.png"));
    //x = 0, y = 3, 3frames left to right
    const float TW  = GLOBAL::TEXTURE_SIZE.width();
    const float TH  = GLOBAL::TEXTURE_SIZE.height();
    const float TSW = GLOBAL::TILE_SIZE.width();
    const float TSH = GLOBAL::TILE_SIZE.height();

    m_animator.m_mapStates["blinking"].push_back(pixmap().copy(0 * TW,
                                                               3 * TH,
                                                               TW,
                                                               TH).scaled(TSW, TSH));
    m_animator.m_mapStates["blinking"].push_back(pixmap().copy(1 * TW,
                                                               3 * TH,
                                                               TW,
                                                               TH).scaled(TSW, TSH));
    m_animator.m_mapStates["blinking"].push_back(pixmap().copy(2 * TW,
                                                               3 * TH,
                                                               TW,
                                                               TH).scaled(TSW, TSH));

    m_animator.changeState("blinking");
    m_animator.m_timeBetweenFrames = .5f;

    m_deactivatePixmap = pixmap().copy(6 * TW,
                                       1 * TH,
                                       TW,
                                       TH).scaled(TSW, TSH);

}
