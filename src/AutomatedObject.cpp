#include "header.h"
#include "AutomatedObject.h"
#include "BaseEngine.h"

void AutomatedObject::virtDraw()
{
	if (isVisible())
	{
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + 50,
			m_iCurrentScreenY + 50,
			0xcccccc);
	}
}

void AutomatedObject::virtDoUpdate(int iCurrentTime)
{

	m_iCurrentScreenX += velocity * hDirection;
	if (m_iCurrentScreenX > 700)
	{
		hDirection = -1;
	}
	else if (m_iCurrentScreenX < 50)
	{
		hDirection = 1;
	}

}
