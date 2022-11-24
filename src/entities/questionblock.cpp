#include "questionblock.h"
#include <QGraphicsPixmapItem>
#include <QList>

QList<QuestionBlock*> QuestionBlock::QUESTION_BLOCKS;

QuestionBlock::QuestionBlock()
{
    setCellType(GLOBAL::ActivatedQuestionBlock);
    setPixmap(QPixmap(":/res/map16x16.png"));
    //x = 0, y = 3, 3frames left to right
    m_animator.m_mapStates["blinking"].push_back(pixmap().copy(0 * GLOBAL::TEXTURE_SIZE.width(),
                                                               3 * GLOBAL::TEXTURE_SIZE.height(),
                                                               GLOBAL::TEXTURE_SIZE.width(),
                                                               GLOBAL::TEXTURE_SIZE.height()).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    m_animator.m_mapStates["blinking"].push_back(pixmap().copy(1 * GLOBAL::TEXTURE_SIZE.width(),
                                                               3 * GLOBAL::TEXTURE_SIZE.height(),
                                                               GLOBAL::TEXTURE_SIZE.width(),
                                                               GLOBAL::TEXTURE_SIZE.height()).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
    m_animator.m_mapStates["blinking"].push_back(pixmap().copy(2 * GLOBAL::TEXTURE_SIZE.width(),
                                                               3 * GLOBAL::TEXTURE_SIZE.height(),
                                                               GLOBAL::TEXTURE_SIZE.width(),
                                                               GLOBAL::TEXTURE_SIZE.height()).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));

    m_animator.changeState("blinking");
    m_animator.m_timeBetweenFrames = 1.f;

    QUESTION_BLOCKS.push_back(this);
}

QuestionBlock::~QuestionBlock()
{
    QUESTION_BLOCKS.removeOne(this);
}

void QuestionBlock::CreateQuestionBlock(QPointF position)
{
    QuestionBlock* questionBlock = new QuestionBlock();
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
    pItem->setPixmap(m_animator.pixmap());
    pItem->setPos(position());
    scene.addItem(pItem);
}

void QuestionBlock::update(float elapsedTime)
{
    m_animator.update(elapsedTime);
}
