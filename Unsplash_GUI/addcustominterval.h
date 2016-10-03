#ifndef ADDCUSTOMINTERVAL_H
#define ADDCUSTOMINTERVAL_H

#include <QDialog>
#include "ui_addcustominterval.h"

class addCustomInterval : public QDialog, public Ui::addCustomInterval
{
	Q_OBJECT

public:
	addCustomInterval(QWidget *parent = 0);
	~addCustomInterval();
};

#endif // ADDCUSTOMINTERVAL_H
