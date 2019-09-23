#include "fengencode.h"
#include "ui_fengencode.h"
#include <QColorDialog>
#include <QDebug>

FenGenCode::FenGenCode(QTreeWidget *tree, QTreeWidgetItem *item) : ui(new Ui::FenGenCode)
{
    ui->setupUi(this);
    this->tree = tree;
    this->item = item;
    if (item)
    {
        if (item->parent() == NULL)
        {
            if (item->text(0) == "Camera")
            {
                ui->Tab->setCurrentIndex(2);
                ui->camName->setText(item->child(0)->text(1));
                ui->posxCam->setValue(item->child(1)->child(0)->text(1).toInt());
                ui->posyCam->setValue(item->child(1)->child(1)->text(1).toInt());
                ui->poszCam->setValue(item->child(1)->child(2)->text(1).toInt());
                ui->rotxCam->setValue(item->child(2)->child(0)->text(1).toInt());
                ui->rotyCam->setValue(item->child(2)->child(1)->text(1).toInt());
                ui->rotzCam->setValue(item->child(2)->child(2)->text(1).toInt());
            }
            else if (item->text(0) == "Light")
            {
                ui->Tab->setCurrentIndex(1);
                ui->type->setCurrentIndex(item->child(0)->text(1).toInt());
                ui->posx->setValue(item->child(1)->child(0)->text(1).toInt());
                ui->posy->setValue(item->child(1)->child(1)->text(1).toInt());
                ui->posz->setValue(item->child(1)->child(2)->text(1).toInt());
                ui->colorLight->setText(item->child(2)->text(1));
                ui->lightCoef->setValue(item->child(3)->text(1).toDouble());
            }
            else
            {
                ui->Tab->setCurrentIndex(0);
                if (item->text(0).toLower() == "sphere")
                    ui->shapesSelect->setCurrentIndex(0);
                else if (item->text(0).toLower() == "plane")
                    ui->shapesSelect->setCurrentIndex(1);
                else if (item->text(0).toLower() == "cone")
                    ui->shapesSelect->setCurrentIndex(2);
                else if (item->text(0).toLower() == "cylinder")
                    ui->shapesSelect->setCurrentIndex(3);
                else if (item->text(0).toLower() == "hyperboloid")
                    ui->shapesSelect->setCurrentIndex(4);
                ui->shine->setValue(item->child(0)->text(1).toDouble());
                ui->posxShape->setValue(item->child(1)->child(0)->text(1).toInt());
                ui->posyShape->setValue(item->child(1)->child(1)->text(1).toInt());
                ui->poszShape->setValue(item->child(1)->child(2)->text(1).toInt());
                ui->rotx->setValue(item->child(2)->child(0)->text(1).toInt());
                ui->roty->setValue(item->child(2)->child(1)->text(1).toInt());
                ui->rotz->setValue(item->child(2)->child(2)->text(1).toInt());
                ui->rayon1->setValue(item->child(3)->text(1).toInt());
                ui->rayon2->setValue(item->child(4)->text(1).toInt());
                ui->colorShape->setText(item->child(5)->text(1));
                if (item->child(6)->text(1) == "true")
                    ui->checkerplane->setChecked(1);
                if (item->child(7)->text(1) == "true")
                {
                    ui->perlinNoise->setChecked(1);
                    ui->chooseColorPerlin->setEnabled(1);
                    ui->colorPerlin->setEnabled(1);
                    ui->typePerlin->setEnabled(1);
                    ui->typePerlin->setCurrentIndex(item->child(7)->child(0)->text(1).toInt());
                    ui->colorPerlin->setText(item->child(7)->child(1)->text(1));
                }
                else
                {
                    ui->chooseColorPerlin->setDisabled(1);
                    ui->colorPerlin->setDisabled(1);
                    ui->typePerlin->setDisabled(1);
                }
            }

        }
    }
    ui->addLightButton->setIcon(QIcon(":/images/images/add.png"));
    ui->addShapeButton->setIcon(QIcon(":/images/images/add.png"));
    ui->addCamButton->setIcon(QIcon(":/images/images/add.png"));
    if (!item)
    {
        ui->chooseColorPerlin->setDisabled(1);
        ui->colorPerlin->setDisabled(1);
        ui->typePerlin->setDisabled(1);
    }
    getColor = new QColorDialog(this);
    setFixedSize(640, 400);
    connect(ui->chooseColorLight, SIGNAL(clicked()), this, SLOT(getColorLight()));
    connect(ui->chooseColorShape, SIGNAL(clicked()), this, SLOT(getColorShape()));
    connect(ui->addLightButton, SIGNAL(clicked()), this, SLOT(addLightToTree()));
    connect(ui->addShapeButton, SIGNAL(clicked()), this, SLOT(addShapeToTree()));
    connect(ui->addCamButton, SIGNAL(clicked()), this, SLOT(addCamToTree()));
    connect(ui->chooseColorPerlin, SIGNAL(clicked()), this, SLOT(getColorPerlin()));
    connect(ui->perlinNoise, SIGNAL(clicked()), this, SLOT(perlinActived()));
}

FenGenCode::~FenGenCode()
{
    delete ui;
}

void FenGenCode::removeItemChilds()
{
    qDeleteAll(item->takeChildren());
}

void FenGenCode::perlinActived()
{
    if (!ui->perlinNoise->isChecked())
    {
        ui->chooseColorPerlin->setDisabled(1);
        ui->colorPerlin->setDisabled(1);
        ui->typePerlin->setDisabled(1);
    }
    else
    {
        ui->chooseColorPerlin->setDisabled(0);
        ui->colorPerlin->setDisabled(0);
        ui->typePerlin->setDisabled(0);
    }
}

void FenGenCode::getColorLight()
{
    ui->colorLight->setText(getColor->getColor(Qt::white, this, "Choose a color", 0).name().toUpper());
}

void FenGenCode::getColorShape()
{
    ui->colorShape->setText(getColor->getColor(Qt::white, this, "Choose a color", 0).name().toUpper());
}

void FenGenCode::getColorPerlin()
{
    ui->colorPerlin->setText(getColor->getColor(Qt::white, this, "Choose a color", 0).name().toUpper());
}

void FenGenCode::addLightToTree()
{
    if(item && item->childCount() > 0)
        removeItemChilds();
    QTreeWidgetItem *light;
    if (item)
        light = item;
    else
        light = new QTreeWidgetItem(tree);
    light->setText(0, "Light");

    QTreeWidgetItem *type = new QTreeWidgetItem(light);
    type->setText(0, "Type");
    type->setData(1, 0, (QVariant)ui->type->currentText().toInt());

    QTreeWidgetItem *position = new QTreeWidgetItem(light);
    position->setText(0, "Position");

    QTreeWidgetItem *posx = new QTreeWidgetItem(position);
    posx->setText(0, "x");
    posx->setData(1, 0, (QVariant)ui->posx->cleanText());
    QTreeWidgetItem *posy = new QTreeWidgetItem(position);
    posy->setText(0, "y");
    posy->setData(1, 0, (QVariant)ui->posy->cleanText());
    QTreeWidgetItem *posz = new QTreeWidgetItem(position);
    posz->setText(0, "z");
    posz->setData(1, 0, (QVariant)ui->posz->cleanText());

    QTreeWidgetItem *color = new QTreeWidgetItem(light);
    color->setText(0, "Color");
    color->setData(1, 0, (QVariant)ui->colorLight->text());

    QTreeWidgetItem *ratio = new QTreeWidgetItem(light);
    ratio->setText(0, "Ratio");
    ratio->setData(1, 0, (QVariant)ui->lightCoef->text());

    this->close();
}

void FenGenCode::addCamToTree()
{
    if(item && item->childCount() > 0)
        removeItemChilds();
    QTreeWidgetItem *cam;
    if (item)
        cam = item;
    else
        cam = new QTreeWidgetItem(tree);
    cam->setText(0, "Camera");

    QTreeWidgetItem *name = new QTreeWidgetItem(cam);
    name->setText(0, "Name");
    name->setData(1, 0, ui->camName->text());

    QTreeWidgetItem *position = new QTreeWidgetItem(cam);
    position->setText(0, "Position");

    QTreeWidgetItem *posx = new QTreeWidgetItem(position);
    posx->setText(0, "x");
    posx->setData(1, 0, (QVariant)ui->posxCam->cleanText());
    QTreeWidgetItem *posy = new QTreeWidgetItem(position);
    posy->setText(0, "y");
    posy->setData(1, 0, (QVariant)ui->posyCam->cleanText());
    QTreeWidgetItem *posz = new QTreeWidgetItem(position);
    posz->setText(0, "z");
    posz->setData(1, 0, (QVariant)ui->poszCam->cleanText());

    QTreeWidgetItem *rotation = new QTreeWidgetItem(cam);
    rotation->setText(0, "Rotation");

    QTreeWidgetItem *rotx = new QTreeWidgetItem(rotation);
    rotx->setText(0, "x");
    rotx->setData(1, 0, (QVariant)ui->rotxCam->cleanText());
    QTreeWidgetItem *roty = new QTreeWidgetItem(rotation);
    roty->setText(0, "y");
    roty->setData(1, 0, (QVariant)ui->rotyCam->cleanText());
    QTreeWidgetItem *rotz = new QTreeWidgetItem(rotation);
    rotz->setText(0, "z");
    rotz->setData(1, 0, (QVariant)ui->rotzCam->cleanText());

    this->close();
}

void FenGenCode::addShapeToTree()
{
    if(item && item->childCount() > 0)
        removeItemChilds();
    QTreeWidgetItem *shape;
    if (item)
        shape = item;
    else
        shape = new QTreeWidgetItem(tree);
    shape->setText(0, ui->shapesSelect->currentText());

    QTreeWidgetItem *shine = new QTreeWidgetItem(shape);
    shine->setText(0, "Shine");
    shine->setData(1, 0, (QVariant)ui->shine->text());

    QTreeWidgetItem *position = new QTreeWidgetItem(shape);
    position->setText(0, "Position");

    QTreeWidgetItem *posx = new QTreeWidgetItem(position);
    posx->setText(0, "x");
    posx->setData(1, 0, (QVariant)ui->posxShape->cleanText());
    QTreeWidgetItem *posy = new QTreeWidgetItem(position);
    posy->setText(0, "y");
    posy->setData(1, 0, (QVariant)ui->posyShape->cleanText());
    QTreeWidgetItem *posz = new QTreeWidgetItem(position);
    posz->setText(0, "z");
    posz->setData(1, 0, (QVariant)ui->poszShape->cleanText());

    QTreeWidgetItem *rotation = new QTreeWidgetItem(shape);
    rotation->setText(0, "Rotation");

    QTreeWidgetItem *rotx = new QTreeWidgetItem(rotation);
    rotx->setText(0, "x");
    rotx->setData(1, 0, (QVariant)ui->rotx->cleanText());
    QTreeWidgetItem *roty = new QTreeWidgetItem(rotation);
    roty->setText(0, "y");
    roty->setData(1, 0, (QVariant)ui->roty->cleanText());
    QTreeWidgetItem *rotz = new QTreeWidgetItem(rotation);
    rotz->setText(0, "z");
    rotz->setData(1, 0, (QVariant)ui->rotz->cleanText());

    QTreeWidgetItem *rayon1 = new QTreeWidgetItem(shape);
    rayon1->setText(0, "Radius 1");
    rayon1->setData(1, 0, (QVariant)ui->rayon1->text());

    QTreeWidgetItem *rayon2 = new QTreeWidgetItem(shape);
    rayon2->setText(0, "Radius 2");
    rayon2->setData(1, 0, (QVariant)ui->rayon2->text());

    QTreeWidgetItem *color = new QTreeWidgetItem(shape);
    color->setText(0, "Color");
    color->setData(1, 0, (QVariant)ui->colorShape->text());

    QTreeWidgetItem *checkerplane = new QTreeWidgetItem(shape);
    checkerplane->setText(0, "Chess Board");
    if (ui->checkerplane->isChecked())
        checkerplane->setData(1, 0, "true");
    else
        checkerplane->setData(1, 0, "false");

    QTreeWidgetItem *perlin = new QTreeWidgetItem(shape);
    perlin->setText(0, "Perlin noise");
    if (ui->perlinNoise->isChecked())
    {
        perlin->setData(1, 0, "true");
        QTreeWidgetItem *type = new QTreeWidgetItem(perlin);
        type->setText(0, "Type");
        type->setData(1, 0, (QVariant)ui->typePerlin->currentIndex());
        QTreeWidgetItem *color = new QTreeWidgetItem(perlin);
        color->setText(0, "Color");
        color->setData(1, 0, (QVariant)ui->colorPerlin->text());
    }
    else
        perlin->setData(1, 0, "false");

    this->close();
}
