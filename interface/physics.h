#ifndef _PHYSICS_INCLUDE
#define _PHYSICS_INCLUDE

#include "game_systems.h"
#include "game_objects.h"
#include <QVector>

class CPhysics : public CGameSystem {
	CPhysics();
public:
	static CPhysics* GetInstance() {
		static CPhysics physics;
		return &physics;
	}

	bool Init();
	void Destroy();

	void Update();
	//void Render();
	//void PostRender();
	
	const String GetName() { return String("Physics"); }
	QVector<IGameObject*> m_vObjects;
private:
	float m_flLastThinkTime;
};

inline extern CPhysics* Physics() {
	return CPhysics::GetInstance();
}

#endif
