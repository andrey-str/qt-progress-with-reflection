#ifndef __MIRROREFFECT_H__
#define __MIRROREFFECT_H__

#include <QGraphicsEffect>

/** \brief Reflection effect. 
 *  
 *  Draw "reflection" of the source widget. Source widget is the widget who use this effect by widget->setGraphicsEffect(effect);
 */
class MirrorGraphicsEffect : public QGraphicsEffect
{
	Q_OBJECT
public:
	/** Class contructor
	 * @param parent - parent object
	 */
	MirrorGraphicsEffect(QObject* parent = NULL);
protected:
	/** Performs effect drawing
	 * @param painter - painter for drawing
	 */
	virtual void draw(QPainter *painter);
	/** Returns updated rectangle for widget, including bounds of the effect
	 * Changes after changing of reflection offset property
	 */
	virtual QRectF boundingRectFor(const QRectF &rect) const;
	/** Returns current reflection offset
	 */
	inline float reflectionOffset() { return _reflectionOffset;}
public slots:
	/** Set reflection offset
	 * @param value - reflection offset
	 */
	void setReflectionOffset(float value);

private:
	float _reflectionOffset; //! Reflection offset. Can be negative. This value is distance between reflection and widget. 
							 //! If it is negative, reflection may going to the widget itself.
};
#endif