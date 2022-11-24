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
private:
    static QList<QuestionBlock*> QUESTION_BLOCKS;
    Animator m_animator;

    // Entity interface
public:
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
};

#endif // QUESTIONBLOCK_H
