#include "physics.h"
#include "engine.h"
#include "input.h"
#include "timer.h"
#include "base.h"
#include <QDebug>

CPhysics::CPhysics() {

}

bool CPhysics::Init() {
	m_flLastThinkTime = 0.0f;
	CBlob *tmp = new CBlob();
	tmp->SetPos(30, 50);
	tmp->SetInputKeys(KEY_W, KEY_A, KEY_S, KEY_D, KEY_C);
	tmp->SetColor(1, 0, 0, 1);
	m_vObjects.append(tmp);
	tmp = new CBlob();
	tmp->SetPos(100, 50);
	tmp->SetInputKeys(KEY_I, KEY_J, KEY_K, KEY_L, KEY_N);
	tmp->SetColor(0, 1, 0, 1);
	m_vObjects.append(tmp);
	return true;
}

void CPhysics::Destroy() {

}

void CPhysics::Update() {
	float cTime = Timer()->CurrentTime();
	for (int i = 0; i < m_vObjects.size(); i++) {
		m_vObjects.at(i)->Think();
	}
	while ((m_flLastThinkTime + STEPSIZE) < cTime) {
		for (int i = 0; i < m_vObjects.size(); i++) {
			m_vObjects.at(i)->Act();
		}
		m_flLastThinkTime += STEPSIZE;
	}

}

/*
void CPhysics::Render() {

}

void CPhysics::PostRender() {

}
*/
