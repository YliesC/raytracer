#include "aboutrt.h"
#include "ui_aboutrt.h"

aboutrt::aboutrt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutrt)
{
    setFixedSize(550, 300);
    ui->setupUi(this);
    connect(ui->closeAbout, SIGNAL(clicked()), this, SLOT(closeAbout()));
}

void aboutrt::closeAbout()
{
    this->close();
}

aboutrt::~aboutrt()
{
    delete ui;
}
