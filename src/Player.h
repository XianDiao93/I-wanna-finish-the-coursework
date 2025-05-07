#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "SimpleImage.h"
#include "ImageManager.h"
#include "Utilities.h"
#include "BaseEngine.h"
#include "MapTileManager.h"
#include "GameState.h"

class Player :
    public DisplayableObject
{
private:
    bool lockKeyIn = true;
    int lockTimer = 0;
protected:
    SimpleImage kid;
    int state = 1;
    MapTileManager *tm;
    int leftX;
    int rightX;
    int topY;
    int bottomY;

    bool dead = false;
    
    bool jumpHandled = false;
    bool jumpKeyPreviouslyPressed = false;
    bool isJumping = false;
    bool isDoubleJumping = false;
    bool canDoubleJump = true;
    bool isFalling = false;
    int jumpStartTime = 0;
    int jumpDuration = 0;
    int maxJumpDuration = 350;
    float jumpVelocity = 0;
    float gravity = 0.3f;
    float velocityY = 0;
    int maxVel = 8;

public:
    Utilities::coordinate pos;
    int keys[4] = {0};
    int currentFrame;
    Utilities::coordinate prevPos;

    bool canJump = true;

public:
    Player(BaseEngine* pEngine, int iX, int iY, MapTileManager *tile, GameState *currentState) : DisplayableObject(pEngine)
    {
        kid = ImageManager::loadImage("resources/img/Kid/rightKid1.png", true);
        pos.x = iX;
        pos.y = iY;
        m_iCurrentScreenX = pos.x;
        m_iCurrentScreenY = pos.y;
        m_iDrawWidth = 23;
        m_iDrawHeight = 21;

        tm = tile;

    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrent) override;
    int getState() const;
    Utilities::coordinate getPos();
    void setPos(Utilities::coordinate position);
    // void drawImage(SimpleImage image);
    bool isDead() const;
    void reTry();

    void storePreviousPosition();
    void handleAnimation(int iCurrent);
    void handleMovement(int iCurrent);
    void handleJump(int iCurrent);
    void applyGravity();
    void applyVerticalMovement();
    void checkTopCollision();
    void checkBottomCollision();
    void checkSpecialPlatformEffects();
    void updateScreenPosition();
    void checkSpikeCollision(int position, int value, int mapX, int mapY);
    void triggerDeath();
};

