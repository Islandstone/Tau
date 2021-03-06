#ifndef _ENGINE_INCLUDE
#define _ENGINE_INCLUDE

#include "base.h"
#include "game_systems.h"
#include "sound.h"
#include "window.h"

#include <QApplication>
#include <vector>

//#include "base_object.h"

class CEngine
{
private:
    CEngine();

public:

    static CEngine* GetInstance() 
    {
        static CEngine engine;
        return &engine;
    }

    bool Init();
    void Destroy();

    void Start();
    void Main();
    void Stop();

    void SetFullscreen(bool fullscreen);
    
    //inline void AddObject( IGameObject *pObject) { m_vecObjectList.push_back(pObject); }
    
    void Error( String msg );
    void FatalError( String msg );
    void Message( String msg );
    void Debug( String msg );

    void SetQtApp(QApplication *app) { m_pApp = app; }

	void Render();

	void PushContext();
	void PopContext();

private:

    void CreateSystems();
    bool InitSystems();
    void AddSystem( IGameSystem *pSystem );

    void FrameAdvance();
    void Update();

    QApplication*       m_pApp;
	//QtInterface*		m_pWindow;
	TauWindow*			m_pWindow;
    
    /*
    IGameFactory*       m_pGameFactory;
    IGameInterface*     m_pGame;
    bool                m_bGameStarted;
    */

    bool                m_bFullscreen;
    int                 m_iScreenX;
    int                 m_iScreenY;

    bool                m_bActive;

    /*
    CSprite*            m_pLogoSprite;
    CSprite*            m_pSplashSprite;
    CSample*            m_pStartupSound;
    */

    //std::vector<IGameObject*>   m_vecObjectList;
    std::vector<IGameSystem*>   m_vecGameSystems;
};

extern inline CEngine* Engine()
{
    return CEngine::GetInstance();
}

#endif
