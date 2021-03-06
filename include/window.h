#ifndef WINDOW_INCLUDE_H
#define WINDOW_INCLUDE_H

#include <QGLWidget>
#include "blob.h"

class TauWindow : public QGLWidget {
public:

	TauWindow(QWidget* parent = NULL);

	void RenderText(int x, int y, QString str);

	void Think();
	void Render();

	void RenderFps();
private:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int width, int height);

	void keyPressEvent(QKeyEvent *event); 
	void keyReleaseEvent(QKeyEvent *event); 

	float m_flLastThinkTime;
	float m_flLastTime;
	int m_iFrameCount;
	float m_flFPS;
};

#endif
