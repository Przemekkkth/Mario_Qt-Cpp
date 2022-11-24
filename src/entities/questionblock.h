#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H
#include "block.h"
#include "../utils/animator.h"

class QuestionBlock : public Block
{
public:
    QuestionBlock();
    ~QuestionBlock();
    static void CreateQuestionBlock(QPointF position);
    static void UpdateQuestionBlocks(float elapsedTime);
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    void deactivate();
private:
    static QList<QuestionBlock*> QUESTION_BLOCKS;
    Animator m_animator;
    bool m_activate;
    QPixmap m_deactivatePixmap;
    // Entity interface
};

#endif // QUESTIONBLOCK_H
