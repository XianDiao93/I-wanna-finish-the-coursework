#include "header.h"
#include "Scyxd6Object.h"
#include "BaseEngine.h"

void Scyxd6Object::virtDraw()
{
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + 50,
		m_iCurrentScreenY + 50,
		0xcccccc);
}


void Scyxd6Object::virtDoUpdate(int iCurrentTime)
{
	// Change position if player presses a key 
	if (getEngine()->isKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 2;
	if (getEngine()->isKeyPressed(SDLK_s))
		m_iCurrentScreenY += 2;
	if (getEngine()->isKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 2;
	if (getEngine()->isKeyPressed(SDLK_d))
		m_iCurrentScreenX += 2;
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;
	// Ensure that the objects get redrawn on the display 
	this->redrawDisplay();
}
