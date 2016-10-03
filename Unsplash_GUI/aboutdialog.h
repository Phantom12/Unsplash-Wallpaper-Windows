#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "ui_aboutdialog.h"

class aboutDialog : public QDialog, public Ui::aboutDialog
{
	Q_OBJECT

public:
	aboutDialog(QWidget *parent = 0);
	~aboutDialog();
};

#endif // ABOUTDIALOG_H
