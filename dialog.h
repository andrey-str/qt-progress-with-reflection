#ifndef __TEST_DIALOG_H__

#include <QDialog>
#include "ui_dialog.h"

/** \brief Dialog which contains ActivityWidget and test controls. 
 *  
 *  Allows to change ActivityWidget label's text, setup reflection offset and turn on/off reflection.
 */
class ProgressBarDialog : public QDialog, public Ui::ProgressBarDialog
{
	Q_OBJECT
public:
	/** Class contructor
	 * @param parent - parent Qt widget.
	 */
    ProgressBarDialog(QWidget* parent = NULL);

};

#endif