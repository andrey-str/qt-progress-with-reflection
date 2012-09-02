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
	 * Class contructor
	 * @param parent - parent Qt widget. Can be NULL.
	 */
	ActivityProgressBar(QWidget* parent = NULL);
protected:
	/** Overrided QWidget's paint method. Performs custom drawing of progress bar
	 * @param pe - paint event object
	 */
	virtual void paintEvent(QPaintEvent *pe);
signals:
	/** Signal to send after each repaint operation
	 */
	void repaint_owner();
private slots:
	/** Internal private slot, used for updating progress bar content. Connected to private timer object
	 */
	void updatePBContent();
private:
	/** Internal private method performs custom drawing of progress bar's content(animated progress line)
	 */
	void draw_custom_pb_contents(QStylePainter* painter, QStyleOptionProgressBarV2* opt);
private:
	float _progressBarImageDelta;
	QTimer* _timer;
};
#endif