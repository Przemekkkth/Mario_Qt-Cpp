#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H
#include "block.h"
#include "../utils/animator.h"
#include "particle.h"

class QuestionBlock : public Block
{
public:
    QuestionBlock();
    ~QuestionBlock();
    static void CreateQuestionBlock(QPointF position);
    static void UpdateQuestionBlocks(float elapsedTime);
    static constexpr const float COIN_SPEED         = 160.0f;
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    void deactivate();
private:
    static QList<QuestionBlock*> QUESTION_BLOCKS;
    void createCoinAnimation();
    Animator m_animator;
    bool m_activate;
    QPixmap m_deactivatePixmap, m_coinTexturePixmap;
    Particle* m_coinParticle;
    Animator m_coinAnimation;
    // Entity interface
};

#endif // QUESTIONBLOCK_H
