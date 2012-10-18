#ifndef _BLOB_INCLUDE
#define _BLOB_INCLUDE

#include "vector.h"
#include "game_object.h"

class CBlob : public IGameObject
{
public:
	CBlob();

	void Act();
	void Think();
	void SetInputKeys(int up, int left, int down, int right, int fire);
	void SetPos(float x, float y);
	void Render();
	void SetColor(float r, float g, float b, float a);

private:
	Vector m_vPos;
	Vector m_vSpeed;

	float m_flKeyStartTime;
	bool m_bKeyHeld;
	float m_flRed, m_flGreen, m_flBlue, m_flAlpha;

	int m_kUp, m_kLeft, m_kDown, m_kRight, m_kFire;
};

#endif
