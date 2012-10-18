#ifndef _BLOB_PHYSICS_INCLUDE
#define _BLOB_PHYSICS_INCLUDE

//#include "blob.h"
#include "vector.h"

class CBlob;

class CBlobPhysics // TODO: Interface?
{
public:
	CBlobPhysics(CBlob* object);

	void ApplyForceDir(Vector dir);
	void SetForceScale(float scale) {}

	void Think();

private:
	Vector m_vDelta;
	CBlob* m_pObject;
};

#endif
