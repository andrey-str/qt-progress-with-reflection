#include "ActivityProgressBar.h"
#include <QStylePainter>
#include <QStyleOptionDockWidgetV2>
#include <QTimer>


ActivityProgressBar::ActivityProgressBar(QWidget* parent /* = NULL */):
QProgressBar(parent), _progressBarImageDelta(0.f), _pbIndicator(NULL)
{
	QString stylesheet = "QProgressBar { border: 2px solid black; border-radius: 5px; }";

	setStyleSheet(stylesheet);

	update_indicator();
}

ActivityProgressBar::~ActivityProgressBar()
{
	// safe delete _pbInidicato
	if(_pbIndicator)
		delete _pbIndicator;

}
void ActivityProgressBar::update_indicator()
{
	_progressBarImageDelta+=0.5;

	float chunkLength = 2;

	if(_progressBarImageDelta >= chunkLength*2)
		_progressBarImageDelta = 0.f;

	// draw on _pbIndicator
	QRect bounds = contentsRect();
	bounds = bounds.adjusted(2, 8, -2, -8);

	// safe delete _pbInidicato
	if(_pbIndicator)
		delete _pbIndicator;

	QRect rc = bounds.adjusted(0, 0, 0, 0);

	_pbIndicator = new QImage(rc.size(), QImage::Format_ARGB8565_Premultiplied);
	_pbIndicator->fill(Qt::transparent);
	QPainter p(_pbIndicator);

	p.setCompositionMode(QPainter::CompositionMode_Source);
	p.setRenderHint(QPainter::SmoothPixmapTransform, true);
	p.setRenderHint(QPainter::HighQualityAntialiasing, true);

	QColor chunkColor = QColor::fromRgb(255,150,100),
		backgroundColor = Qt::darkGray;

	QBrush brush0(Qt::SolidPattern);
	brush0.setColor(backgroundColor);
	p.fillRect(0,0,_pbIndicator->width(), _pbIndicator->height(), brush0);

	QBrush brush(Qt::SolidPattern);
	brush.setColor(chunkColor);
	p.setBrush(brush);

	QPen pen(chunkColor);
	p.setPen(pen);
	for (qreal iX = -chunkLength*3 + _progressBarImageDelta; iX < _pbIndicator->width(); iX++)
	{
		//p.drawEllipse(iX, (_pbIndicator->height()-chunkLength)/2, chunkLength, chunkLength);
		p.drawRoundedRect(iX, 0, chunkLength, _pbIndicator->height()-1, 2, 2);
		iX += (chunkLength*2 + 1);
	}

	p.end();
}

void ActivityProgressBar::paintEvent(QPaintEvent *pe)
{	
	// Basically this function draws progress bar frame using standard style
	// and then draws progress bar content in "draw_custom_pb_contents" method.
	QStylePainter painter(this);
	QStyleOptionProgressBarV2 opt;
	initStyleOption(&opt);

	QRect bounds = contentsRect();
	opt.rect = bounds;
	opt.minimum = 0;
	opt.maximum = 0;

	opt.rect = bounds.adjusted(0, 6, 0, -6);
	painter.drawControl(QStyle::CE_ProgressBarGroove, opt);
	opt.rect = bounds.adjusted(2, 8, -2, -8);
	painter.drawImage(opt.rect, *_pbIndicator);
	painter.end();
}