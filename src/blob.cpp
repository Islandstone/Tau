#include "blob.h"
#include "timer.h"
#include <QtGui>

#include "input.h"
#include "GL/gl.h"
#include "blob.h"

CBlob::CBlob() {
	m_flLastThinkTime = 0.0f;
	m_bKeyHeld = false;
	m_flKeyStartTime = 0.0f;
	m_kUp = -1;
	m_kDown = -1;
	m_kRight = -1;
	m_kLeft = -1;
	m_kFire = -1;
}

#define STEP_SIZE 10000
#define DAMPING 100

void CBlob::Think() {
	float dt = Timer()->CurrentTime() - m_flLastThinkTime;

	if (dt < 0.01f) return;

	if (!m_bKeyHeld && Input()->KeyHeld(m_kFire)) {
		m_bKeyHeld = true;
		m_flKeyStartTime = Timer()->CurrentTime();
	} else if (m_bKeyHeld && Input()->KeyReleased(m_kFire)) {
		m_bKeyHeld = false;

		float mod = (Timer()->CurrentTime() - m_flKeyStartTime) * 1.5f;

		if (mod < 0.1f) mod = 0.1f;
		if (mod > 5.0f) mod = 5.0f;

		if (Input()->KeyHeld(m_kRight)) {
			//speed_x += dt * mod * STEP_SIZE;
			m_vSpeed.x += dt * mod * STEP_SIZE;
		}  

		if (Input()->KeyHeld(m_kLeft)) {
			//speed_x -= dt * mod * STEP_SIZE;
			m_vSpeed.x -= dt * mod * STEP_SIZE;
		}

		if (Input()->KeyHeld(m_kUp)) {
			m_vSpeed.y -= dt * mod * STEP_SIZE;
		}

		if (Input()->KeyHeld(m_kDown)) {
			m_vSpeed.y += dt * mod * STEP_SIZE;
		}
	}
	else 
	{
		m_vSpeed *= 1.0 - (1.0 / DAMPING);
	}

	//m_vPos = m_vPos + (dt * m_vSpeed);
	Vector delta = m_vSpeed;
	delta *= dt;
	m_vPos += delta;

	if (m_vPos.x - 10 < 0) {
		m_vSpeed.x *= -1;
		m_vPos.x = 10;
	}

	if ((m_vPos.x + 10) > 150) {
		m_vSpeed.x *= -1;
		m_vPos.x = 140;
	}

	if ((m_vPos.y - 10) < 0) {
		m_vSpeed.y *= -1;
		m_vPos.y = 10;
	}

	if ((m_vPos.y + 10) > 100) {
		m_vSpeed.y *= -1;
		m_vPos.y = 90;
	}

	m_flLastThinkTime = Timer()->CurrentTime();
}

#define CIRCLE_SEGMENTS 30

void drawCircle(float x, float y, float radius) {
	glBegin(GL_POLYGON);

	for (int i = 0; i < CIRCLE_SEGMENTS; i++) {
		float _x = x + (radius * cos(2 * M_PI * (float)i / CIRCLE_SEGMENTS));
		float _y = y + (radius * sin(2 * M_PI * (float)i / CIRCLE_SEGMENTS));
		glVertex3f(_x, _y, 1.0f);
	}

	glEnd();
}

void CBlob::SetInputKeys(int up, int left, int down, int right, int fire) {
	m_kUp = up;
	m_kLeft = left;
	m_kDown = down;
	m_kRight = right;
	m_kFire = fire;
}

void CBlob::SetPos(float x, float y) {
	/*
	this->x = x; this->y = y;
	*/
	m_vPos.x = x; m_vPos.y = y;
}

void CBlob::Render() {
	drawCircle(m_vPos.x, m_vPos.y, 10);
}
