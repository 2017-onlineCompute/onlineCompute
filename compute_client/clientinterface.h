#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H
#include <QDialog>
#include "registeinterface.h"

namespace Ui {
class Clientinterface;
}

class Clientinterface : public QDialog
{
    Q_OBJECT

public:
    explicit Clientinterface(QWidget *parent = 0);
    ~Clientinterface();

private slots:
    void on_registerButton_clicked();
    void on_clicked_reshow();
    void on_okButton_clicked();

private:
    Ui::Clientinterface *ui;
};

#endif // CLIENTINTERFACE_H
