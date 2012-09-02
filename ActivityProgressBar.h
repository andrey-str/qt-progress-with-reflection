#ifndef __ACTIVITY_PROGRESS_BAR_H__
#define __ACTIVITY_PROGRESS_BAR_H__

#include <QProgressBar>

class QStylePainter;
class QStyleOptionProgressBarV2;
class QTimer;

/** \brief Progress bar with custom painting. 
 *  
 *  Works only in "activity" mood, i.e. doesn't use maximum and minimum properties. Also hides QProgressBar's text label;
 */

class ActivityProgressBar : public QProgressBar
{
	Q_OBJECT
public:
	/** 
	 * Class constructor
	 * @param parent - parent Qt widget. Can be NULL.
	 */
	ActivityProgressBar(QWidget* parent = NULL);
	virtual ~ActivityProgressBar();
protected:
	/** Override QWidget's paint method. Performs custom drawing of progress bar
	 * @param pe - paint event object
	 */
	virtual void paintEvent(QPaintEvent *pe);
private slots:
	/** Internal private slot, used for updating progress bar content.
	 */
	void update_indicator();
private:
	qreal _progressBarImageDelta;
	QImage* _pbIndicator; //! Temp image for drawing on widget update(implemented in update_indicator method)
};
#endif