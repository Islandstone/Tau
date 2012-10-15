#ifndef _BLOB_INCLUDE
#define _BLOB_INCLUDE

#include "vector.h"

class CBlob 
{
public:
	CBlob();

	void Think();
	void SetInputKeys(int up, int left, int down, int right, int fire);
	void SetPos(float x, float y);
	void Render();

private:
	Vector m_vPos;
	Vector m_vSpeed;

	float m_flLastThinkTime;
	float m_flKeyStartTime;
	bool m_bKeyHeld;

	int m_kUp, m_kLeft, m_kDown, m_kRight, m_kFire;
};

#endif
