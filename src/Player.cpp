#include "header.h"
#include "Player.h"

void Player::virtDraw()
{
    if (isVisible())
    {
        // Draw to foreground surface instead of background
        kid.renderImageWithMask(
            getEngine()->getForegroundSurface(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            kid.getWidth(), kid.getHeight(),
            0x000000
        );
    }
}


void Player::virtDoUpdate(int iCurrent)
{
    if (lockTimer > 10)
    {
        lockKeyIn = false;
    }
    else
    {
        lockTimer++;
    }
    if (!dead && !lockKeyIn)
    {
        storePreviousPosition();
        handleAnimation(iCurrent);
        handleMovement(iCurrent);
        handleJump(iCurrent);
        applyGravity();
        applyVerticalMovement();
        checkTopCollision();
        checkBottomCollision();
        checkSpecialPlatformEffects();
        updateScreenPosition();
        if (dead)
        {
            kid = ImageManager::loadImage("resources/img/Kid/death.png", true);
        }
        getEngine()->redrawDisplay();

    }
}

int Player::getState() const
{
    return state;
}

Utilities::coordinate Player::getPos()
{
    return pos;
}

void Player::setPos(Utilities::coordinate position)
{
    pos.x = position.x;
    pos.y = position.y;
}

bool Player::isDead() const
{
    return dead;
}

void Player::reTry()
{
    dead = false;
}



void Player::storePreviousPosition()
{
    prevPos.x = m_iCurrentScreenX;
    prevPos.y = m_iCurrentScreenY;
}

void Player::handleAnimation(int iCurrent)
{
    currentFrame = (iCurrent / 100) % 4;
    std::string direction = (state == 0) ? "rightKid" : "leftKid";
    kid = ImageManager::loadImage("resources/img/Kid/" + direction + std::to_string(currentFrame + 1) + ".png", true);
}

void Player::handleMovement(int iCurrent)
{
    if (lockTimer < 20)
    {
        lockTimer++;
        return;
    }
    if (getEngine()->isKeyPressed(keys[0])) // Right
    {
        state = 0;
        currentFrame = (iCurrent / 50) % 6;
        int mapX = tm->getMapXForScreenX(rightX);
        int mapYT = tm->getMapYForScreenY(topY);
        int mapYB = tm->getMapYForScreenY(bottomY);

        if (tm->getMapValue(mapX, mapYT) >= 9 && tm->getMapValue(mapX, mapYB) >= 9)
        {
            pos.x += 2;
        }

        kid = ImageManager::loadImage("resources/img/Kid/rightRun" + std::to_string(currentFrame + 1) + ".png", true);
    }
    else if (getEngine()->isKeyPressed(keys[1])) // Left
    {
        state = 1;
        currentFrame = (iCurrent / 50) % 6;
        int mapX = tm->getMapXForScreenX(leftX);
        int mapYT = tm->getMapYForScreenY(topY);
        int mapYB = tm->getMapYForScreenY(bottomY);

        if (tm->getMapValue(mapX, mapYT) >= 9 && tm->getMapValue(mapX, mapYB) >= 9)
        {
            pos.x -= 2;
        }

        kid = ImageManager::loadImage("resources/img/Kid/leftRun" + std::to_string(currentFrame + 1) + ".png", true);
    }
}

void Player::handleJump(int iCurrent)
{
    bool jumpKeyPressed = getEngine()->isKeyPressed(keys[2]);

    if (jumpKeyPressed && !jumpHandled)
    {
        if (!isJumping && !isFalling)
        {
            isJumping = true;
            canDoubleJump = true;
            jumpStartTime = iCurrent;
            jumpDuration = 0;
            velocityY = -8.0f;
            jumpHandled = true;
        }
        else if (!isDoubleJumping && canDoubleJump && !jumpKeyPreviouslyPressed)
        {
            isDoubleJumping = true;
            isJumping = true;
            canDoubleJump = false;
            jumpStartTime = iCurrent;
            jumpDuration = 0;
            velocityY = -6.0f;
            jumpHandled = true;
        }
    }

    if (jumpKeyPressed && isJumping)
    {
        jumpDuration = iCurrent - jumpStartTime;
        if (jumpDuration < maxJumpDuration)
            velocityY = -6.0f * (1.0f - static_cast<float>(jumpDuration) / maxJumpDuration);
        else
            isJumping = false;
    }
    else if (!jumpKeyPressed)
    {
        if (isJumping) isJumping = false;
        jumpHandled = false;
    }

    jumpKeyPreviouslyPressed = jumpKeyPressed;
}

void Player::applyGravity()
{
    if (velocityY < maxVel)
        velocityY += gravity;
    else
        velocityY = maxVel;
}

void Player::applyVerticalMovement()
{
    pos.y += static_cast<int>(velocityY);
}

void Player::checkTopCollision()
{
    int mapX_L = tm->getMapXForScreenX(pos.x + 4);
    int mapX_R = tm->getMapXForScreenX(pos.x + 21);
    int mapY_Top = tm->getMapYForScreenY(pos.y - 1);

    if (tm->getMapValue(mapX_L, mapY_Top) < 9 || tm->getMapValue(mapX_R, mapY_Top) < 9)
    {
        velocityY = 0;
        isJumping = false;
        isDoubleJumping = false;
        isFalling = true;
        pos.y = 32 * (mapY_Top + 1) + 1;
    }
    if (tm->getMapValue(mapX_L, mapY_Top) >= 9 && tm->getMapValue(mapX_L, mapY_Top) <= 12)
    {
        checkSpikeCollision(0, tm->getMapValue(mapX_L, mapY_Top), mapX_L, mapY_Top);
    }
    if (tm->getMapValue(mapX_R, mapY_Top) >= 9 && tm->getMapValue(mapX_R, mapY_Top) <= 12)
    {
        checkSpikeCollision(1, tm->getMapValue(mapX_R, mapY_Top), mapX_R, mapY_Top);
    }
}

void Player::checkBottomCollision()
{
    int mapX_L = tm->getMapXForScreenX(pos.x + 4);
    int mapX_R = tm->getMapXForScreenX(pos.x + 21);
    int mapY_Bottom = tm->getMapYForScreenY(pos.y + 23);

    if (tm->getMapValue(mapX_L, mapY_Bottom) < 9 || tm->getMapValue(mapX_R, mapY_Bottom) < 9)
    {
        velocityY = 0;
        isJumping = false;
        isDoubleJumping = false;
        canDoubleJump = true;
        isFalling = false;
        pos.y = 32 * (mapY_Bottom - 1) + 11;
    }
    else
    {
        isFalling = true;
    }
    if (tm->getMapValue(mapX_L, mapY_Bottom) >= 9 && tm->getMapValue(mapX_L, mapY_Bottom) <= 12)
    {
        checkSpikeCollision(2, tm->getMapValue(mapX_L, mapY_Bottom), mapX_L, mapY_Bottom);
    }
    if (tm->getMapValue(mapX_R, mapY_Bottom) >= 9 && tm->getMapValue(mapX_R, mapY_Bottom) <= 12)
    {
        checkSpikeCollision(3, tm->getMapValue(mapX_R, mapY_Bottom), mapX_R, mapY_Bottom);
    }

}

void Player::checkSpecialPlatformEffects()
{
    int mapX_L = tm->getMapXForScreenX(pos.x + 4);
    int mapX_R = tm->getMapXForScreenX(pos.x + 21);
    int mapY_Top = tm->getMapYForScreenY(pos.y - 1);
    int mapY_Bottom = tm->getMapYForScreenY(pos.y + 23);

    if (tm->getMapValue(mapX_L, mapY_Top) == 13 || tm->getMapValue(mapX_R, mapY_Top) == 13 ||
        tm->getMapValue(mapX_L, mapY_Bottom) == 13 || tm->getMapValue(mapX_R, mapY_Bottom) == 13)
    {
        maxVel = 3;
        canDoubleJump = true;
        isDoubleJumping = false;
    }
    else
    {
        maxVel = 8;
    }
}

void Player::updateScreenPosition()
{
    m_iCurrentScreenX = pos.x;
    m_iCurrentScreenY = pos.y;
    leftX = pos.x + 3;
    rightX = pos.x + 22;
    topY = pos.y - 1;
    bottomY = pos.y + 19;

    int frame = currentFrame % 2;

    if (isJumping)
    {
        kid = ImageManager::loadImage("resources/img/Kid/" + std::string(state == 0 ? "rightJump" : "leftJump") + std::to_string(frame + 1) + ".png", true);
    }
    else if (isFalling)
    {
        kid = ImageManager::loadImage("resources/img/Kid/" + std::string(state == 0 ? "rightDrop" : "leftDrop") + std::to_string(frame + 1) + ".png", true);
    }
}

void Player::checkSpikeCollision(int position, int value, int mapX, int mapY)
{

    Utilities::coordinate point{0};
    switch (position)
    {
    case 0:
        point.x = pos.x;
        point.y = pos.y;
        break;
    case 1:
        point.x = pos.x;
        point.y = pos.y + 23;
        break;
    case 2:
        point.x = pos.x + 21;
        point.y = pos.y;
        break;
    case 3:
        point.x = pos.x + 21;
        point.y = pos.y + 23;
        break;
    }

    bool hit = false;
    bool a, b, c, d;
    switch (value)
    {
    case 9: // down
        a = virtIsPositionWithinObject(mapX * 32, mapY * 32);
        b = virtIsPositionWithinObject(mapX * 32 + 31, mapY * 32);
        c = virtIsPositionWithinObject(mapX * 32 + 15, mapY * 32 + 31);
        d = Utilities::isPointInTriangleInt(mapX*32, mapY*32, mapX*32+31, mapY*32, mapX*32+15, mapY*32+31, point.x, point.y);
        hit = a || b || c || d;
        break;
    case 10: // left
        a = virtIsPositionWithinObject(mapX * 32 + 31, mapY * 32);
        b = virtIsPositionWithinObject(mapX * 32 + 31, mapY * 32 + 31);
        c = virtIsPositionWithinObject(mapX * 32, mapY * 32 + 15);
        d = Utilities::isPointInTriangleInt(mapX * 32+31, mapY * 32, mapX * 32 + 31, mapY * 32 + 31, mapX * 32, mapY * 32 + 15, point.x, point.y);
        hit = a || b || c || d;
        break;
    case 11: // right
        a = virtIsPositionWithinObject(mapX * 32, mapY * 32);
        b = virtIsPositionWithinObject(mapX * 32, mapY * 32 + 31);
        c = virtIsPositionWithinObject(mapX * 32 + 31, mapY * 32 + 15);
        d = Utilities::isPointInTriangleInt(mapX * 32, mapY * 32, mapX * 32, mapY * 32 + 31, mapX * 32 + 31, mapY * 32 + 15, point.x, point.y);
        hit = a || b || c || d;
        break;
    case 12: // up
        a = virtIsPositionWithinObject(mapX * 32, mapY * 32 + 31);
        b = virtIsPositionWithinObject(mapX * 32 + 31, mapY * 32 + 31);
        c = virtIsPositionWithinObject(mapX * 32 + 15, mapY * 32);
        d = Utilities::isPointInTriangleInt(mapX * 32, mapY * 32 + 31, mapX * 32 + 31, mapY * 32 + 31, mapX * 32 + 15, mapY * 32, point.x, point.y);
        hit = a || b || c || d;
        break;
    }

    if (hit)
    {
        triggerDeath();
        return;
    }

}

void Player::triggerDeath()
{
    dead = true;
}
