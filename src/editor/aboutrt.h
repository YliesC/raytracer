#ifndef ABOUTRT_H
#define ABOUTRT_H

#include <QDialog>

namespace Ui {
class aboutrt;
}

class aboutrt : public QDialog
{
    Q_OBJECT

    public:
        explicit aboutrt(QWidget *parent = 0);
        ~aboutrt();

    public slots:
        void closeAbout();
    private:
        Ui::aboutrt *ui;
};

#endif // ABOUTRT_H
