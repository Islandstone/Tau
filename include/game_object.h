#ifndef _GAME_OBJECT_INCLUDE
#define _GAME_OBJECT_INCLUDE

class IGameObject {
public:
	virtual void Think() = 0;
	virtual void Act() = 0;
	virtual void Render() = 0;
};

#endif
