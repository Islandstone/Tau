#include "console.h"

ConsoleInput::ConsoleInput(QWidget* parent) : QTextEdit(parent) {

}

void ConsoleInput::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		Console()->SendCommand(toPlainText().trimmed());
		setText("");
		event->ignore();
	}
	else if (event->key() == Qt::Key_PageUp) {
		event->ignore();
	}
	else if (event->key() == Qt::Key_Up) {
		qDebug() << "Key up";
	}
	else if (event->key() == Qt::Key_Down) {
		qDebug() << "Key down";
	}
	else if (event->key() == Qt::Key_Tab) {
		return;
	}
	else {
		QTextEdit::keyPressEvent(event);
	}
}

ConsoleText::ConsoleText(QWidget* parent) : QTextEdit(parent) {
	setReadOnly(true);
}

void ConsoleText::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		event->ignore();
	}
	else if (event->key() == Qt::Key_PageUp) {
		event->ignore();
	}
	else {
		QTextEdit::keyPressEvent(event);
	}
}

ConsoleWidget::ConsoleWidget() {
	
}

void ConsoleWidget::InitWidgets(QWidget* parent) {
	m_pWidget = new QWidget();
	m_pWidget->setParent(parent);

	m_pText = new ConsoleText();
	m_pInput = new ConsoleInput();
	m_pInput->setFixedHeight(25); // HACKHACK

	m_pLayout = new QVBoxLayout(m_pWidget);
	m_pLayout->addWidget(m_pText);
	m_pLayout->addWidget(m_pInput);

	// Set scrollbar policy
	m_pText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pWidget->hide();
	/*
	m_pWidget->show();
	m_pText->show();
	m_pInput->show();
	*/

	int width = 0.7f * parent->width();
	int height = 0.7f * parent->height();

	m_pWidget->resize(width, height);
	m_pText->resize(100, 100);
	m_pInput->resize(100, 10);
	m_pInput->move(0, 100);

	m_pWidget->move((0.5f * parent->width()) - (0.5f * width), (0.5f * parent->height()) - (0.5f * height) );

	m_bVisible = false;
}

void ConsoleWidget::Toggle() {
	if (m_bVisible) {
		Hide();
	} else {
		Show();
	}
}

void ConsoleWidget::Show() {
	m_pWidget->show();
	m_pInput->setFocus();
	m_bVisible = true;
}

void ConsoleWidget::Hide() {
	m_pWidget->hide();
	m_bVisible = false;
}

void ConsoleWidget::SendCommand(QString str) {
	m_pText->setText(m_pText->toPlainText() + "\n" + str);
}
