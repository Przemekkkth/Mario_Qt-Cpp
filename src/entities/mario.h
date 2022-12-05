#ifndef MARIO_H
#define MARIO_H
#include "../gamescene.h"
#include "entity.h"
#include "../utils/animator.h"
#include <QPixmap>

class Enemy;
class Block;
class GameScene;
class Mushroom;
class Mario : public Entity {
public:
    static constexpr const float MOVE_SPEED         = 20.0f;
    static constexpr const float RUN_SPEED          = 12.0f;
    static constexpr const float JUMP_SPEED         = 450.0f;
    static constexpr const float DRAG_VALUE         = 2.0f;
    static constexpr const float MAX_MOVE_SPEED     = 150.0f;
    static constexpr const float MAX_RUN_SPEED      = 12.0f;
    static constexpr const float MAX_FALLDOWN_SPEED = 350.0f;
    static constexpr const float HURT_TIMER         = 2.f;
    static constexpr const float DEAD_TIMER         = 1.5f;
    Mario();
public:
    virtual void draw(GameScene &scene) override;
    virtual void update(float elapsedTime) override;
    void update(float elapsedTime, GameScene& scene);
    void setBig(bool on);
    bool isBig() const;
    void resetStatus();
    void setMaxX(int maxX);
private:
    void clampVelocities(float elapsedTime);
    void checkCollisionWithBlocks();
    void collideWithBlock(Block *block);
    void checkCollisionWithMushrooms();
    void collideWithMushroom(Mushroom *mushroom);
    void checkCollisionWithEnemies();
    void chooseAnimation();
    void collideWithEnemy(Enemy* enemy);
    void setAnimatationState(QString state);
    void setFliped();
    void createAnimations();
    void jump(float jumpSpeed);
    void handleHurtCounter(float elapsedTime);
    void handleDeadCounter(float elapsedTime);
    bool m_big, m_fliped, m_hurt, m_dead;
    void setHurt();
    QRect hitBox();
    QPixmap m_texture;
    float m_velocityX, m_velocityY;
    float m_elapsedTime;
    float m_hurtTimer;
    float m_deadTimer;
    bool m_onGround, m_runMode;
    bool m_crouchning;
    bool m_collideWithBlock;
    Animator m_animator;
    float m_maxX;

};

#endif // MARIO_H
