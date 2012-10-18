#include "console.h"

Console::Console(QWidget* parent) {
	m_pWidget = new QWidget();
	m_pWidget->setParent(parent);

	m_pText = new QTextEdit();
	m_pInput = new QTextEdit();
	m_pInput->setFixedHeight(20); // HACKHACK

	m_pLayout = new QVBoxLayout(m_pWidget);
	m_pLayout->addWidget(m_pText);
	m_pLayout->addWidget(m_pInput);
	m_pText->setText("Text");
	m_pInput->setText("Input");

	m_pWidget->show();
	m_pText->show();
	m_pInput->show();

	int width = 0.7f * parent->width();
	int height = 0.7f * parent->height();

	m_pWidget->resize(width, height);
	m_pText->resize(100, 100);
	m_pInput->resize(100, 10);
	m_pInput->move(0, 100);
}


