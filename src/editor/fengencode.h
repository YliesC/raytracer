#ifndef FENGENCODE_H
#define FENGENCODE_H

#include <QDialog>
#include <QColorDialog>
#include <mainwindow.h>

namespace Ui {
class FenGenCode;
}

class FenGenCode : public QDialog
{
    Q_OBJECT

    public:
        FenGenCode(QTreeWidget *tree, QTreeWidgetItem *item = NULL);
        ~FenGenCode();
        QTreeWidget *tree;
        QTreeWidgetItem *item;
        void removeItemChilds();

    private:
        Ui::FenGenCode *ui;
        QColorDialog   *getColor;

    public slots:
        void getColorLight();
        void getColorShape();
        void getColorPerlin();
        void addLightToTree();
        void addShapeToTree();
        void addCamToTree();
        void perlinActived();
};

#endif // FENGENCODE_H
