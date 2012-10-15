#ifndef _BLOB_INCLUDE
#define _BLOB_INCLUDE

class CBlob 
{
public:
	CBlob();

	void Think();

	void Render();

private:
	float x, y, speed_x, speed_y;

	float m_flLastThinkTime;
	float m_flKeyStartTime;
	bool m_bKeyHeld;
};

#endif
