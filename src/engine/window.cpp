#include "window.h"
#include <GL/glu.h>
#include <QtGui>

#include "input.h"
#include "physics.h"

TauWindow::TauWindow(QWidget* parent) : QGLWidget(parent) {
}

void TauWindow::initializeGL() {
	qDebug("GL Init");


	// Enable alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DOUBLE);
	glAlphaFunc(GL_GREATER,0.1);
	glDisable(GL_ALPHA_TEST);

	glDisable( GL_DEPTH_TEST );

	//TODO: Engine()->Precache();

	glClearColor(0,0,0,0);
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	setFocusPolicy(Qt::StrongFocus);
	/*
    m_flFPS = 0.0f;
    m_flLastTime = 0.0f;
	*/
	glDisable(GL_CULL_FACE);
}

void TauWindow::Think() {
}

void TauWindow::Render() {
	update();
}

void TauWindow::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	/*glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	blob1->Render();
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	blob2->Render();*/
	QVector<IGameObject *> tmp = Physics()->m_vObjects;
	for (int i = 0; i < tmp.size(); i++) {
		tmp[i]->Render();
	}
	glFlush();
	glFinish();
	swapBuffers();
}

void TauWindow::resizeGL(int width, int height) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,width,height);

	float viewwidth = 0.0f;
	float viewheight = 0.0f;

	if ( width >= height )
	{
		viewwidth = 100 * (float)width/(float)height;
		viewheight = 100;
	}
	else
	{
		// Unusual case, but left in anyways
		viewwidth = 100;
		viewheight = 100 * (float)height/(float)width;
	}

	gluOrtho2D(0, viewwidth, viewheight, 0);

}

void TauWindow::keyPressEvent(QKeyEvent *event) 
{
	/*if ( event->isAutoRepeat() )
    {
	return;
    }*/

	int keycode = event->key();
	Input()->SetKeyDown( keycode );
}

void TauWindow::keyReleaseEvent(QKeyEvent *event)
{
	/*if (event->isAutoRepeat() )
    {
	return;
    }*/

	qDebug() << event;
	int keycode = event->key();

	Input()->SetKeyUp( keycode );
}

void TauWindow::RenderText(int x, int y, QString str)
{
	/*
	QFont font = QFont("Source Code Pro");
	font.setPointSize(18);
	renderText(x, y, str, font);
	*/
	renderText(x, y, str);
}
