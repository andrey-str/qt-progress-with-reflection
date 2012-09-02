#include "dialog.h"

#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include "mirroreffect.h"
#include "ActivityWidget.h"

ProgressBarDialog::ProgressBarDialog(QWidget* parent):
QDialog(parent)
{
    setupUi(this);
   
	reflectionsCheckBox->setChecked(true);

	connect(lineEdit, SIGNAL(textChanged(const QString&)), activityWidget, SLOT(setText(const QString&)));
	connect(reflectionsCheckBox, SIGNAL(toggled(bool)), activityWidget, SLOT(showReflection(bool)));
	connect(slider, SIGNAL(valueChanged(int)), activityWidget, SLOT(setReflectionOffset(int)));
}
