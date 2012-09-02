#include "ActivityProgressBar.h"
#include <QStylePainter>
#include <QStyleOptionDockWidgetV2>
#include <QTimer>


ActivityProgressBar::ActivityProgressBar(QWidget* parent /* = NULL */):
QProgressBar(parent), _progressBarImageDelta(0.f)
{
	_timer = new QTimer(this);
	connect(_timer, SIGNAL(timeout()), this, SLOT(updatePBContent()));
	_timer->start(15);

	QString stylesheet = "QProgressBar { border: 2px solid black; border-radius: 5px; }";

	setStyleSheet(stylesheet);
}

void ActivityProgressBar::updatePBContent()
{
	_progressBarImageDelta+=1;
}

void ActivityProgressBar::draw_custom_pb_contents(QStylePainter* painter, QStyleOptionProgressBarV2* opt)
{
	// Function creates an image, then draw many elipses on it with some delta to imitate moving of these elpises from left to right
	float chunkLength = 6;

	QRect rc = opt->rect.adjusted(chunkLength*3, 0, 0, 0);
	QImage image(rc.size(), QImage::Format_ARGB8565_Premultiplied);
	image.fill(Qt::transparent);
	QPainter p(&image);
	p.setCompositionMode(QPainter::CompositionMode_Source);
	p.setRenderHint(QPainter::SmoothPixmapTransform, true);
	p.setRenderHint(QPainter::HighQualityAntialiasing, true);
	
	QColor chunkColor = QColor::fromRgb(255,150,100),
			backgroundColor = Qt::darkGray;

	QBrush brush0(Qt::SolidPattern);
	brush0.setColor(backgroundColor);
	p.fillRect(0,0,image.width(), image.height(), brush0);

	QBrush brush(Qt::SolidPattern);
	brush.setColor(chunkColor);
	p.setBrush(brush);

	QPen pen(chunkColor);
	p.setPen(pen);
	for (int iX = -chunkLength*3 + _progressBarImageDelta; iX < image.width(); iX++)
	{
		p.drawEllipse(iX, (image.height()-chunkLength)/2, chunkLength, chunkLength);
		iX += chunkLength * 2;
	}

	p.end();
	
	painter->drawImage(opt->rect, image);

	
	if(_progressBarImageDelta >= chunkLength*2)
		_progressBarImageDelta = 0.f;

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
	draw_custom_pb_contents(&painter, &opt);
	painter.end();

	// since progress bar content is always changing, we 
	// informs everybody who interested so they have chance to update themselves
	// useful for updating reflection effect
	emit repaint_owner();
}