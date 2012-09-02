#include "mirroreffect.h"
#include <QPainter>

MirrorGraphicsEffect::MirrorGraphicsEffect(QObject* parent /* = NULL */)
	:QGraphicsEffect(parent), _reflectionOffset(1)
{

}

QRectF MirrorGraphicsEffect::boundingRectFor(const QRectF &rect) const
{
	// Expand bounding box to include reflection
	QRectF r = rect.united(rect.translated(QPoint(0,rect.height() + _reflectionOffset)));;
	return r;
}

void MirrorGraphicsEffect::setReflectionOffset(float value)
{
	if(_reflectionOffset != value){
		_reflectionOffset = value; 
		updateBoundingRect(); // we have to call this function to inform everybody who interested that boundings of control has changed
	}
}

void MirrorGraphicsEffect::draw(QPainter *painter)
{
	PixmapPadMode mode = PadToEffectiveBoundingRect;

	// Draw pixmap in device coordinates to avoid pixmap scaling.
	QPoint offset;
	const QPixmap pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset, mode);
	if (pixmap.isNull())
		return;

	QTransform restoreTransform = painter->worldTransform();
	painter->setWorldTransform(QTransform());

	// We'll draw widget on this image
	QImage tmp(pixmap.size(), QImage::Format_ARGB32_Premultiplied);
	tmp.fill(Qt::transparent);
	// We're going to draw widget on tmp image using this painter object
	QPainter tmpPainter(&tmp);
	tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
	tmpPainter.drawPixmap(QPoint(0,0), pixmap);
	tmpPainter.end(); 

	// Now we need to mirror image and put alpha channel gradient on our image of control
	// First mirror it by Y axis
	QImage mirroredImage(tmp.mirrored(false, true));
	// Create gradient object
	QPoint p1, p2;
	p2.setY(mirroredImage.height());
	QLinearGradient gradient(p1, p2);
	gradient.setColorAt(0.3, QColor(0, 0, 0, 255));
	gradient.setColorAt(0.8, QColor(0, 0, 0, 0));

	// With this painter we'll draw gradient on mirror image
	QPainter mirroredImagePainter(&mirroredImage);
	mirroredImagePainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	mirroredImagePainter.fillRect(0, 0, mirroredImage.width(), mirroredImage.height(), gradient);
	mirroredImagePainter.end();

	// Draw reflection first
	painter->drawImage(offset, mirroredImage);
	// Draw source widget
	painter->drawPixmap(offset, pixmap);
	painter->setWorldTransform(restoreTransform);
}