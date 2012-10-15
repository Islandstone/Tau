#include <QtGui>

#include "window.h"
#include "engine.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	/*
	TauWindow window;
	//window.resize(1024, 768);
	//window.show();
	window.showFullScreen();
	return app.exec();
	*/

	CEngine *e = CEngine::GetInstance();

	if (!e->Init())
		return 0;

	e->Start();
	e->Stop();
}

