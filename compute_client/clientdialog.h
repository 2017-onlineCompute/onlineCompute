#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>
#include <QString>
#include <QDialog>
#include "ui_clientdialog.h"

namespace Ui {
class Dialog;
}

class ClientDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = 0);
    ~ClientDialog();


    void okClicked();
    void enableOkButton(const QString &text);

private:
    Ui::Dialog *ui;
};

#endif // FINDDIALOG
