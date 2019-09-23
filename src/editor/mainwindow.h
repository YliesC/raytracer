#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(char *map);
        ~MainWindow();
        void clearMap();
        void generateCode(QString action, QString folder, int winx, int winy, bool preview);
        void addCamera(QString nameCam,  QJsonArray posCam, QJsonArray rotCam);
        void addLight(QString typeLight, QJsonArray posLight, QString colorLight, QString ratioLight);
        void addShape(QString typeShape, QString shineShape, QString colorShape, QString rayon1Shape, QString rayon2Shape, QJsonArray positionShape, QJsonArray rotationShape, QJsonArray modsShape);


    protected:
        QJsonObject parseLights(QTreeWidgetItem *item);
        QJsonObject parseShapes(QTreeWidgetItem *item);
        QJsonObject parseCameras(QTreeWidgetItem *item);

    public slots:
        void addObject();
        void newMap();
        void saveMap();
        void loadMap();
        void removeItem();
        void modifiedItem(QTreeWidgetItem *item, int column);
        void startPreview();
        void generateMap();
        void aboutRt();
        void aboutEpitech();

    private:
        Ui::MainWindow *ui;
        QString fileNameLoaded;
        void fillInput(char *fileMap);
};

#endif // MAINWINDOW_H
