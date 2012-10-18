#include "base.h"
#include "input.h"
#include "engine.h"

#include <sstream>
#include <QtGui>

//#include "script.h"

/*
#define MAKE_KEY( name ) Sqrat::ConstTable().Const(#name, name);

void BindInput()
{
	Sqrat::Class<CInput, Sqrat::NoConstructor> def;

	def.Func("KeyUp", &CInput::KeyUp);
	def.Func("KeyPressed", &CInput::KeyPressed);
	def.Func("KeyHeld", &CInput::KeyHeld);
	def.Func("KeyReleased", &CInput::KeyReleased);

	Sqrat::RootTable().Bind("InputSystem", def);

	//Sqrat::ConstTable().Const("KEY_LEFT", KEY_LEFT);
	MAKE_KEY( KEY_LEFT );
	MAKE_KEY( KEY_RIGHT );
	MAKE_KEY( KEY_UP );
	MAKE_KEY( KEY_DOWN );
	MAKE_KEY( KEY_Q );
	MAKE_KEY( KEY_W );
	MAKE_KEY( KEY_PAGEUP );
	MAKE_KEY( KEY_PAGEDOWN );
	MAKE_KEY( KEY_HOME );

	// Push the singleton to squirrel
	sq_pushroottable( Sqrat::DefaultVM::Get() );
	sq_pushstring( Sqrat::DefaultVM::Get(), "InputSystem", -1 );
	sq_get(  Sqrat::DefaultVM::Get(), -2 );
	sq_pushstring(  Sqrat::DefaultVM::Get(), "Input", -1 );
	sq_createinstance(  Sqrat::DefaultVM::Get(), -2 );
	sq_setinstanceup(  Sqrat::DefaultVM::Get(), -1, (SQUserPointer)Input() );
	sq_newslot(  Sqrat::DefaultVM::Get(), -4, SQFalse );
	sq_pop(  Sqrat::DefaultVM::Get(), 2 );
}

ClassBinder inputBinder(&BindInput);
*/


CInput::CInput()
{
}

void CInput::PostRender()
{
	m_pPreviousState.clear();
	for (QSet<int>::const_iterator i = m_pCurrentState.begin(); i != m_pCurrentState.end(); ++i) {
		m_pPreviousState.insert(*i);
	}
}

void CInput::SetKeyUp(int keycode)
{
	m_pCurrentState.remove(keycode);
}

void CInput::SetKeyDown(int keycode)
{
	m_pCurrentState.insert(keycode);
}

bool CInput::KeyUp(int keycode)
{
	return (!m_pCurrentState.contains(keycode));
}

bool CInput::KeyPressed(int keycode) {
	return (m_pCurrentState.contains(keycode));
}


bool CInput::KeyReleased(int keycode)
{
	return (!m_pCurrentState.contains(keycode) && m_pPreviousState.contains(keycode));
}
