#include "window.h"
#include <GL/glu.h>
#include <QtGui>

#include "input.h"

TauWindow::TauWindow(QWidget* parent) : QGLWidget(parent) {
	blob = new CBlob(); // TODO: Cleanup
}

void TauWindow::initializeGL() {
    qDebug("GL Init");

	/*
	if ( ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		 iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		 ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) {
			printf("DevIL version is different...exiting!\n");
			Engine()->Stop();
	} 

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer( ILUT_OPENGL );
	*/

	// Enable alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glEnable(GL_BLEND);		
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
	blob->Think();
}

void TauWindow::Render() {
	update();
}

void TauWindow::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 1.0);

		glVertex3f(30, 0, 1.0);

		glVertex3f(30, 30.0, 1.0);

		glVertex3f(0.0, 30.0, 1.0);
	glEnd();

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	blob->Render();
}

void TauWindow::resizeGL(int width, int height) {
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
void TauWindow::resizeGL(int width, int height) {
    glViewport(0,0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	float viewwidth = 0.0f;
	float viewheight = 0.0f;

	// delta's from the center of the screen
	float dx = 0.0f;
	float dy = 0.0f;

	if ( width >= height )
	{
		viewwidth = 100 * (float)width/(float)height;
		viewheight = 100;	
		dx = 0.5f * viewwidth - 50.0f;
	}
	else
	{
		viewwidth = 100;
		viewheight = 100 * (float)height/(float)width;
		dy = 0.5f * viewheight - 50.0f;
	}
	
	gluOrtho2D(0, viewwidth, viewheight, 0);

	glTranslatef(dx, dy, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
*/

void TauWindow::keyPressEvent(QKeyEvent *event) 
{
    if ( event->isAutoRepeat() )
    {
        return;
    }

	int keycode = event->key();

    Input()->SetKeyDown( keycode );
}

void TauWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() )
    {
        return;
    }

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
