#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H
#include "block.h"
#include "../utils/animator.h"
#include "particle.h"

class QuestionBlock : public Block
{
public:
    enum class Type{
        None, Coin, PowerSupply, LifeMushroom
    };
    QuestionBlock();
    ~QuestionBlock();
    static void CreateQuestionBlock(QPointF position,
                                    QuestionBlock::Type type=QuestionBlock::Type::Coin);
    static void UpdateQuestionBlocks(float elapsedTime);
    static constexpr const float COIN_SPEED         = 160.0f;
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    void deactivate();
    bool isActivate();
    void setType(Type type);

private:
    static QList<QuestionBlock*> QUESTION_BLOCKS;
    void createCoinAnimation();
    void createBlinkingAnimation();
    Animator m_animator;
    bool m_activate;
    QPixmap m_deactivatePixmap, m_coinTexturePixmap;
    Particle* m_coinParticle;
    Animator m_coinAnimation;

    Type m_type;
};

#endif // QUESTIONBLOCK_H
