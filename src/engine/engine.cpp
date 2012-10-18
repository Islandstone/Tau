#include <QtGui>
#include <iostream>
#include <sstream>

#include "engine.h"
#include "window.h"

#ifndef _WIN32
#include "unistd.h"
#endif

#include "time.h"

#include "input.h"
#include "sound.h"

#include "timer.h"
#include "physics.h"

#include "console.h"
//#include "script.h"

void msleep( float msec )
{
#ifdef _WIN32
	Sleep(msec);
#else
    usleep( msec * 1000 );
#endif
}

CEngine::CEngine()
{
	m_pWindow = NULL;
}

bool CEngine::Init() 
{
    Message("Engine Init\n");

	Timer()->Start();

    CreateSystems();

    if ( !InitSystems() ) 
    {
        return false;
    }

    Message("Engine Init Successful\n");
    return true;
}

void CEngine::CreateSystems()
{
    AddSystem( Input() );
	AddSystem( Physics() );

	/*
    AddSystem( Sound() );
	AddSystem( Script() );	
	*/
}

void CEngine::AddSystem( IGameSystem *pSystem )
{
    m_vecGameSystems.push_back(pSystem);
}

bool CEngine::InitSystems()
{
    for (int i = 0; i < m_vecGameSystems.size(); i++)
    {
        if ( m_vecGameSystems[i]->Init() == false)
        {
            return false;
        }
    }

    return true;
}

void CEngine::Destroy()
{
    Message("Engine Destroy\n");

	/*
	for (int i = 0; i < m_vecObjectList.size(); i++)
    {
        m_vecObjectList[i]->Destroy();
    }
	*/

	for (int i = 0; i < m_vecGameSystems.size(); i++)
    {
        m_vecGameSystems[i]->Destroy();
    }
}

void CEngine::Start()
{   
    Message("Engine Start\n");

    Main();
}

void CEngine::Main()
{
	//InitFormat();

    TauWindow window;

	m_pWindow = &window;
    window.resize(1024, 568);
    window.show();
	window.raise(); // Bring to front

	Console console(&window);

	//Script()->PostInit();

    //while ( !window.shouldClose() )
	while (window.isVisible()) 
    {
        m_pApp->processEvents();
		FrameAdvance();

        if ( Input()->KeyPressed( KEY_ESC ) )
        {
            break;
        }
		else if (Input()->KeyHeld( KEY_ALT ) && ( Input()->KeyReleased( KEY_ENTER ) || Input()->KeyReleased( KEY_RETURN ) ) )
		{
			if ( window.isFullScreen() ) 
			{
				window.showNormal();
			}
			else
			{
				window.showFullScreen();
			}
		}

		if ( Input()->KeyPressed( KEY_PAGEUP )) {
			console.Toggle();
		}
        
		window.Render();

        for (int i = 0; i < m_vecGameSystems.size(); i++)
        {
            m_vecGameSystems[i]->PostRender();
        }

        // We don't really need more than 100 fps, so sleep for 0.01 sec
        msleep(0);
    }

    Message("Engine Main End\n");
}

void CEngine::FrameAdvance()
{
    Update();
}

void CEngine::Update()
{
    for (int i = 0; i < m_vecGameSystems.size(); i++)
    {
        m_vecGameSystems[i]->Update();
    }

	m_pWindow->Think();

	/*
	for (int i = 0; i < m_vecObjectList.size(); i++)
    {
        m_vecObjectList[i]->Think();
    }
	*/
}

void CEngine::Render()
{
	/*
	for (int i = 0; i < m_vecObjectList.size(); i++)
    {
        m_vecObjectList[i]->Render();
    }
	*/

	for (int i = 0; i < m_vecGameSystems.size(); i++)
	{
		m_vecGameSystems[i]->Render();
	}
}

void CEngine::Stop()
{
    Message("Engine Stop\n");
    Destroy();
}

void CEngine::Message( String msg )
{
#ifdef _WIN32
	OutputDebugString( msg.c_str() );
#else
    std::cout << msg << std::endl;
#endif
}

void CEngine::Debug( String msg )
{
#ifdef _WIN32
	OutputDebugStringW( msg.c_str() );
#else
    std::cout << msg << std::endl;
#endif
}

void CEngine::Error( String msg )
{
    std::cout << msg << std::endl;
}
