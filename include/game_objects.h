#ifndef _GAME_OBJECT_INCLUDE
#define _GAME_OBJECT_INCLUDE

class IGameRenderable {
public:
	virtual void Render() = 0;
};

class IGameThinker {
public:
	virtual void Think() = 0;
};

class IGameObject : public IGameRenderable, public IGameThinker {
};

#endif
