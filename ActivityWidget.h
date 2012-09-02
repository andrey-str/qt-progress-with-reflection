#ifndef __ACTIVITY_WIDGET__
#define __ACTIVITY_WIDGET__

#include <QWidget>
#include <QLabel>

class MirrorGraphicsEffect;
class ActivityProgressBar;


/** \brief Widget shows progress bar and text above it.
 * 
 * Class has several properties which allows to tune widget's look.
 * User of this class can turn on or off reflection, change text above the progress bar and set offset for reflection.
 * 
*/	
class ActivityWidget : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Class contructor
	 * 
	 * Contruct class object. 
	 * @param parent - parent Qt widget.
	 */
	ActivityWidget(QWidget* parent = NULL);
public:
	/**
	 * 
	 * Return true if widget is showing reflection, otherwise return false.
	 */
	inline bool isShowReflection() {return _useReflection;}
	/**
	 * Return current text in label
	 */
	inline void text() {_label->text();}
public slots:	
	/** 
	 * Set label's.
	 * @param value - text to set
	 */
	void setText(const QString& value) {_label->setText(value); }
	/** 
	 * Show or hide reflection
	 * @param showReflection - show reflection if true, hide reflection if false.
	 */
	void showReflection(bool showReflection = true);
	/** 
	 * Set reflection offset. It is distance between control and reflection image. Can be negative.
	 * @param value - offset to set
	 */
	void setReflectionOffset(int value);
private:
	MirrorGraphicsEffect* _reflectionEffect; //! Variable holds reflection effect class instance
	ActivityProgressBar* _activityProgressBar; //! Variable holds custom progress bar widget instance
	QLabel* _label; //! Widget for showing text above the progress bar
	QTimer* _timer;
private:
	bool _useReflection;
	float _reflectionDistance;
	
};

#endif