#include "ActivityWidget.h"
#include "mirroreffect.h"
#include "ActivityProgressBar.h"
#include <cassert>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsBlurEffect>
#include <QTimer>

ActivityWidget::ActivityWidget(QWidget* parent /* = NULL */):
QWidget(parent), _useReflection(false), _label(NULL), _activityProgressBar(NULL), _reflectionEffect(NULL),
	_reflectionDistance(8.f)
{
	_label = new QLabel(this);
	_label->setStyleSheet("color: white;");
	_activityProgressBar = new ActivityProgressBar(this);
	_reflectionEffect = new MirrorGraphicsEffect();
	_reflectionEffect->setEnabled(_useReflection);	
	this->setGraphicsEffect(_reflectionEffect);
	
	_timer = new QTimer(this);

	connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(_timer, SIGNAL(timeout()), _activityProgressBar, SLOT(update()));

	_timer->start(1000/25);

	setText("Activity description");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(_label);
	layout->addWidget(_activityProgressBar);
	setLayout(layout);

	_label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	_activityProgressBar->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

	QString stylesheet = "QWidget { background: gray; border-radius: 5px; }";

	setStyleSheet(stylesheet);

	showReflection(true);
}

void ActivityWidget::showReflection(bool showReflection /* = true */)
{
	assert(_reflectionEffect);
	_reflectionEffect->setEnabled(showReflection);
}

void ActivityWidget::setReflectionOffset(int value)
{
	_reflectionEffect->setReflectionOffset(value); 
}