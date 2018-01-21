#ifndef REGISTEINTERFACE_H
#define REGISTEINTERFACE_H

#include <QDialog>
#include "clientinterface.h"

namespace Ui {
class registeinterface;
}

class registeinterface : public QDialog
{
    Q_OBJECT

public:
    explicit registeinterface(QWidget *parent = 0);
    ~registeinterface();
signals:
    void reshowsignal();
private slots:
    void on_okButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::registeinterface *ui;
};

#endif // REGISTEINTERFACE_H
