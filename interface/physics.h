#ifndef _PHYSICS_INCLUDE
#define _PHYSICS_INCLUDE

#include "game_systems.h"

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
private:
};

inline extern CPhysics* Physics() {
	return CPhysics::GetInstance();
}

#endif
