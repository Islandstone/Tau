#include "blob.h"
#include "timer.h"
#include <QtGui>

#include "input.h"
#include "GL/gl.h"
#include "blob.h"

CBlob::CBlob() {
	x = 30;
	y = 30;
	speed_x = 0;
	speed_y = 0;
	m_flLastThinkTime = 0.0f;
	m_bKeyHeld = false;
	m_flKeyStartTime = 0.0f;
}

#define STEP_SIZE 10000
#define DAMPING 100

void CBlob::Think() {
	float dt = Timer()->CurrentTime() - m_flLastThinkTime;

	if (dt < 0.01f) return;

	if (!m_bKeyHeld && Input()->KeyHeld(KEY_SPACE)) {
		m_bKeyHeld = true;
		m_flKeyStartTime = Timer()->CurrentTime();
	} else if (m_bKeyHeld && Input()->KeyReleased(KEY_SPACE)) {
		m_bKeyHeld = false;

		float mod = (Timer()->CurrentTime() - m_flKeyStartTime) * 0.2f;

		if (mod < 0.1f) mod = 0.1f;
		if (mod > 2.0f) mod = 2.0f;

		if (Input()->KeyHeld(KEY_D)) {
			speed_x += dt * mod * STEP_SIZE;
		}  

		if (Input()->KeyHeld(KEY_A)) {
			speed_x -= dt * mod * STEP_SIZE;
		}

		if (Input()->KeyHeld(KEY_W)) {
			speed_y -= dt * mod * STEP_SIZE;
		}

		if (Input()->KeyHeld(KEY_S)) {
			speed_y += dt * mod * STEP_SIZE;
		}
	}
	else 
	{
		speed_x *= 1.0f - (1.0f / DAMPING);
		speed_y *= 1.0f - (1.0f / DAMPING);
	}

	x = x + speed_x * dt;
	y = y + speed_y * dt;

	if (x - 10 < 0)
		speed_x *= -1;

	if ((x + 10) > 185)
		speed_x *= -1;

	if ((y - 10) < 0) 
		speed_y *= -1;

	if ((y + 10) > 100)
		speed_y *= -1;

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

void CBlob::Render() {
	drawCircle(x, y, 10);
}
