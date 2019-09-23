#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fengencode.h"
#include "aboutrt.h"

MainWindow::MainWindow(char *map) : QMainWindow(), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->fileNameLoaded = QString();
    if (map != NULL)
        fillInput(map);
    QRegExp rx("^[A-Za-z0-9-]*");
    ui->exportPath->setValidator(new QRegExpValidator(rx, this));
    /* --------------------- Shorcut --------------------- */
    ui->newMapButton->setShortcut(QKeySequence("Ctrl+N"));
    ui->LoadMapButton->setShortcut(QKeySequence("Ctrl+L"));
    ui->saveMapButton->setShortcut(QKeySequence("Ctrl+S"));
    ui->saveAsButton->setShortcut(QKeySequence("Ctrl+X"));
    ui->exportButton->setShortcut(QKeySequence("Ctrl+E"));
    ui->filterButton->setShortcut(QKeySequence("Ctrl+F"));
    ui->exitButton->setShortcut(QKeySequence::Quit);
    ui->addItemButton->setShortcut(QKeySequence("A"));
    ui->delItemButton->setShortcut(QKeySequence("R"));
    /* ----------------------------------------------------*/
    ui->addItemButton->setIcon(QIcon(":/images/images/add.png"));
    ui->delItemButton->setIcon(QIcon(":/images/images/remove.png"));
    ui->generateButton->setIcon(QIcon(":/images/images/ok.png"));
    ui->previewButton->setIcon(QIcon(":/images/images/preview.png"));
    /* ----------------------------------------------------*/
    connect(ui->newMapButton, SIGNAL(triggered()), this, SLOT(newMap()));
    connect(ui->LoadMapButton, SIGNAL(triggered()), this, SLOT(loadMap()));
    connect(ui->exitButton, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->addItemButton, SIGNAL(clicked()), this, SLOT(addObject()));
    connect(ui->delItemButton, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generateMap()));
    connect(ui->previewButton, SIGNAL(clicked()), this, SLOT(startPreview()));
    connect(ui->saveMapButton, SIGNAL(triggered()), this, SLOT(saveMap()));
    connect(ui->treeObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(modifiedItem(QTreeWidgetItem*, int)));
    connect(ui->aboutRtButton, SIGNAL(triggered()), this, SLOT(aboutRt()));
    connect(ui->aboutEpitech, SIGNAL(triggered()), this, SLOT(aboutEpitech()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutRt()
{
    aboutrt *about = new aboutrt();
    about->exec();
    delete about;
}

void MainWindow::aboutEpitech()
{
    QDesktopServices::openUrl(QUrl("http://www.epitech.eu/"));
}

void MainWindow::removeItem()
{
    if (ui->treeObjects->currentItem())
    {
        if (ui->treeObjects->currentItem()->parent() == NULL)
        {
            qDeleteAll(ui->treeObjects->currentItem()->takeChildren());
            delete ui->treeObjects->currentItem();
        }
    }
}

void MainWindow::modifiedItem(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if (item->parent() == NULL)
    {
        FenGenCode *modify = new FenGenCode(ui->treeObjects, item);
        modify->exec();
        delete modify;
    }
}

void MainWindow::addObject()
{
    FenGenCode *generator = new FenGenCode(ui->treeObjects);
    generator->exec();
    delete generator;
}

void MainWindow::fillInput(char *fileMap)
{
    QFile file(fileMap);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray jsonCode = file.readAll();
    QString error;
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonCode, &jsonError);
    switch (jsonError.error) {
    case 1:
        error = "An object is not correctly terminated with a closing curly bracket";
        break;
    case 2:
        error = "A comma separating different items is missing";
        break;
    case 3:
        error = "The array is not correctly terminated with a closing square bracket";
        break;
    case 4:
        error = "A colon separating keys from values inside objects is missing";
        break;
    case 5:
        error = "The value is illegal";
        break;
    case 6:
        error = "The input stream ended while parsing a number";
        break;
    case 7:
        error = "The number is not well formed";
        break;
    case 8:
        error = "An illegal escape sequence occurred in the input";
        break;
    case 9:
        error = "An illegal UTF8 sequence occurred in the input";
        break;
    case 10:
        error = "A string wasn't terminated with a quote";
        break;
    case 11:
        error = "An object was expected but couldn't be found";
        break;
    case 12:
        error = "The JSON document is too deeply nested for the parser to parse it";
        break;
    case 13:
        error = "The JSON document is too large for the parser to parse it";
        break;
    default:
        break;
    }
    if (jsonError.error != QJsonParseError::NoError)
    {
        QMessageBox::warning(this, "Parsing error", "Error : " + error + "<br> Offset : " + QString::number(jsonError.offset));
        return ;
    }
    clearMap();
    this->fileNameLoaded = QString::fromLatin1(fileMap);
    QJsonObject root;
    root = jsonDoc.object();

    /* --- Parsing main config --- */

    QJsonObject config;
    config = root["config"].toObject();
    QJsonObject screen;

    screen = config["screen"].toObject();
    ui->sceneName->setText(screen["name"].toString());
    QJsonArray size;

    size = screen["size"].toArray();
    ui->winSizeX->setValue(size[0].toInt());
    ui->winSizeY->setValue(size[1].toInt());
    ui->antiAliasing->setValue(config["antialiasing"].toInt());
    ui->exportPath->setText(config["export"].toString());

    /* --- Parsing mods --- */

    QJsonArray mods;
    mods = config["mods"].toArray();

    foreach(const QJsonValue &value, mods)
    {
        QJsonObject mod;
        mod = value.toObject();
        if (mod["name"].toString() == "refraction")
        {
            if (mod["enabled"] == true)
                ui->refraction->setChecked(1);
        }
        else if (mod["name"].toString() == "reflexion")
        {
            if (mod["enabled"] == true)
            {
                ui->reflexion->setChecked(1);
                ui->reflexionCoef->setValue(mod["ratio"].toDouble());
            }
        }
        else if (mod["name"].toString() == "shadow")
        {
            if (mod["enabled"] == true)
            {
                ui->shadow->setChecked(1);
                ui->shadowCoef->setValue(mod["ratio"].toDouble());
            }
        }
        else if (mod["name"].toString() == "cell_shading")
        {
            if (mod["enabled"] == true)
                ui->cellshading->setChecked(1);
        }
        else if (mod["name"].toString() == "filter_negative")
        {
            if (mod["enabled"] == true)
                ui->negative->setChecked(1);
        }
        else if (mod["name"].toString() == "filter_greyscale")
        {
            if (mod["enabled"] == true)
                ui->grey->setChecked(1);
        }
    }
    /* --- Parsing cameras --- */

    QJsonArray cameras;
    cameras = config["cams"].toArray();

    foreach(const QJsonValue &value, cameras)
    {
        QJsonObject obj;
        obj = value.toObject();
        QJsonArray position;
        QJsonArray rotation;
        position = obj["position"].toArray();
        rotation = obj["rotation"].toArray();
        addCamera(obj["name"].toString(), position, rotation);
    }

    /* --- Parsing lights --- */

    QJsonArray lights;
    lights = root["lights"].toArray();

    foreach(const QJsonValue &value, lights)
    {
        QJsonObject obj;
        obj = value.toObject();
        QJsonArray position;
        position = obj["position"].toArray();
        addLight(obj["type"].toString(), position, obj["color"].toString(), obj["ratio"].toString());
    }

    /* --- Parsing shapes --- */

    QJsonArray shapes;
    shapes = root["objects"].toArray();

    foreach(const QJsonValue &value, shapes)
    {
        QJsonObject obj;
        obj = value.toObject();
        QJsonArray position;
        QJsonArray rotation;
        QJsonArray mods;
        mods = obj["mods"].toArray();
        position = obj["position"].toArray();
        rotation = obj["rotation"].toArray();
        addShape(obj["type"].toString(), QString::number(obj["shine"].toDouble()), obj["color"].toString(), QString::number(obj["radius1"].toInt()),
                QString::number(obj["radius2"].toInt()), position, rotation, mods);
    }
}

void MainWindow::loadMap()
{
    QString s_file = QFileDialog::getOpenFileName(this, "Select one file to open", QString(), "JSON File (*.json)");
    QByteArray tmp = s_file.toLatin1();
    char *map = tmp.data();
    fillInput(map);
}

void MainWindow::clearMap()
{
    ui->antiAliasing->setValue(0);
    ui->sceneName->clear();
    ui->winSizeX->setValue(0);
    ui->winSizeY->setValue(0);
    ui->exportEx->setCurrentIndex(0);
    ui->exportPath->clear();
    ui->treeObjects->clear();
    ui->reflexion->setChecked(0);
    ui->refraction->setChecked(0);
    ui->reflexionCoef->setValue(0.00);
    ui->shadow->setChecked(0);
    ui->shadowCoef->setValue(0.0);
    ui->cellshading->setChecked(0);
    ui->negative->setChecked(0);
    ui->grey->setChecked(0);
    ui->antiAliasing->setValue(1);
}

void MainWindow::newMap()
{
    clearMap();
}

QJsonObject MainWindow::parseLights(QTreeWidgetItem *item)
{
    QJsonObject light;

    light["type"] = item->child(0)->text(1).toInt();
    light["color"] = item->child(2)->text(1);

    QJsonArray position;
    position.append(item->child(1)->child(0)->text(1).toInt());
    position.append(item->child(1)->child(1)->text(1).toInt());
    position.append(item->child(1)->child(2)->text(1).toInt());
    light["position"] = position;
    light["ratio"] = item->child(3)->text(1).toDouble();
    return (light);
}

QJsonObject MainWindow::parseCameras(QTreeWidgetItem *item)
{
    QJsonObject camera;

    camera["name"] = item->child(0)->text(1);

    QJsonArray position;
    position.append(item->child(1)->child(0)->text(1).toInt());
    position.append(item->child(1)->child(1)->text(1).toInt());
    position.append(item->child(1)->child(2)->text(1).toInt());
    camera["position"] = position;

    QJsonArray rotation;
    rotation.append(item->child(2)->child(0)->text(1).toInt());
    rotation.append(item->child(2)->child(1)->text(1).toInt());
    rotation.append(item->child(2)->child(2)->text(1).toInt());
    camera["rotation"] = rotation;
    return (camera);
}

QJsonObject MainWindow::parseShapes(QTreeWidgetItem *item)
{
    QJsonObject shape;

    shape["type"] = item->text(0).toLower();
    shape["shine"] = item->child(0)->text(1).toDouble();
    shape["color"] = item->child(5)->text(1);

    QJsonArray position;
    position.append(item->child(1)->child(0)->text(1).toInt());
    position.append(item->child(1)->child(1)->text(1).toInt());
    position.append(item->child(1)->child(2)->text(1).toInt());
    shape["position"] = position;

    QJsonArray rotation;
    rotation.append(item->child(2)->child(0)->text(1).toInt());
    rotation.append(item->child(2)->child(1)->text(1).toInt());
    rotation.append(item->child(2)->child(2)->text(1).toInt());
    shape["rotation"] = rotation;
    shape["radius1"] = item->child(3)->text(1).toInt();
    shape["radius2"] = item->child(4)->text(1).toInt();

    QJsonArray mods;
    QJsonObject mod;

    mod["name"] = QJsonValue(QString("chess"));
    if (item->child(6)->text(1) == "true")
        mod["enabled"] = true;
    else
        mod["enabled"] = false;
    mods.append(mod);

    mod["name"] = QJsonValue(QString("perlin"));
    if (item->child(7)->text(1) == "true")
    {
        mod["enabled"] = true;
        mod["type"] = item->child(7)->child(0)->text(1);
        mod["color"] = item->child(7)->child(1)->text(1);
    }
    else
        mod["enabled"] = false;

    if (item->child(0)->text(1).toDouble() != 0.00)
    {
        mod["name"] = QJsonValue(QString("shining"));
        mod["enabled"] = true;
    }
    mods.append(mod);
    shape["mods"] = mods;

    return (shape);
}

void MainWindow::generateMap()
{
    generateCode("generated", "maps", ui->winSizeX->value(), ui->winSizeY->value(), false);
}

void MainWindow::saveMap()
{
    generateCode("saved", "saves", ui->winSizeX->value(), ui->winSizeY->value(), false);
}

void MainWindow::generateCode(QString action, QString folder, int winx, int winy, bool preview)
{
    if (!preview)
    {
        if (ui->sceneName->text().trimmed().isEmpty())
        {
            QMessageBox::warning(this, "Scene name empty", "A scene name is required, please set it and retry");
            return ;
        }
    }
    if (!QDir(folder).exists())
        QDir().mkdir(folder);
    QString fileName;
    if (!preview)
    {
        if (fileNameLoaded.isNull())
            fileName = folder + "/" + ui->sceneName->text().trimmed() + ".json";
        else
            fileName = fileNameLoaded;
    }
    else
        fileName = "/tmp/preview.json";
    QFile file(fileName);
    if (file.open(QIODevice::Truncate | QIODevice::ReadWrite))
    {
        QJsonObject obj;
        QJsonObject config;
        QJsonArray lights;
        QJsonArray shapes;
        QJsonArray cameras;

        /* Config */
        QJsonObject screen;
        QJsonArray size;

        size.append(QJsonValue(winx));
        size.append(winy);
        screen["size"] = size;
        screen["name"] = ui->sceneName->text();

        QJsonArray mods;
        QJsonObject mod;

        mod["name"] = QJsonValue(QString("refraction"));
        if (ui->refraction->isChecked())
            mod["enabled"] = true;
        else
            mod["enabled"] = false;
        mods.append(mod);

        mod["name"] = QJsonValue(QString("cell_shading"));
        if (ui->cellshading->isChecked()/* && !preview*/)
            mod["enabled"] = true;
        else
            mod["enabled"] = false;
        mods.append(mod);

        mod["name"] = QJsonValue(QString("reflexion"));
        if (ui->reflexion->isChecked())
        {
            mod["enabled"] = true;
            mod["ratio"] = ui->reflexionCoef->text().toDouble();
        }
        else
            mod["enabled"] = false;
        mods.append(mod);

        mod["name"] = QJsonValue(QString("shadow"));
        if (ui->shadow->isChecked())
        {
            mod["enabled"] = true;
            mod["ratio"] = ui->shadowCoef->text().toDouble();
        }
        else
            mod["enabled"] = false;
        mods.append(mod);

        mod.remove("ratio");

        mod["name"] = QJsonValue(QString("filter_negative"));
        if (ui->negative->isChecked())
            mod["enabled"] = true;
        else
            mod["enabled"] = false;
        mods.append(mod);

        mod["name"] = QJsonValue(QString("filter_greyscale"));
        if (ui->grey->isChecked())
            mod["enabled"] = true;
        else
            mod["enabled"] = false;
        mods.append(mod);

        mod["name"] = QJsonValue(QString("light"));
        if (preview)
            config["preview"] = true;
        if (!preview)
        config["antialiasing"] = ui->antiAliasing->cleanText().toInt();
        if (!ui->exportPath->text().trimmed().isEmpty())
            config["export"] = ui->exportPath->text() + ui->exportEx->currentText();
        config["screen"] = screen;

        QTreeWidgetItemIterator ite(ui->treeObjects, QTreeWidgetItemIterator::All);
        while (*ite)
        {
            QVariant data;

            data = (*ite)->data(0, 0);
            if (data.toString() == "Light")
                lights.append(parseLights((*ite)->clone()));
            else if (data.toString() == "Sphere" || data.toString() == "Plane" || data.toString() == "Cone" ||
                     data.toString() == "Cylinder" || data.toString() == "Hyperboloid")
                shapes.append(parseShapes((*ite)->clone()));
            else if (data.toString() == "Camera")
                cameras.append(parseCameras((*ite)->clone()));
            ite++;
        }
        if (lights.count() > 0)
            mod["enabled"] = true;
        else
            mod["enabled"] = false;
        mods.append(mod);
        config["mods"] = mods;
        config["cams"] = cameras;
        obj["config"] = config;
        obj["lights"] = lights;
        obj["objects"] = shapes;

        QTextStream stream (&file);
        stream << QJsonDocument(obj).toJson(QJsonDocument::Indented);
        if (!preview)
            QMessageBox::information(this, "Success!", "Your file was succefully " + action + ".<br />"
                                                                                               + " It's locate in the <i>" + folder + "</i> folder!");
    }
    else
        if (!preview)
            QMessageBox::warning(this, "Creating JSON file failed", "An error occured while filling JSON file ...<br />Please check that a <i>" + folder + "</i> folder exist and retry.");
}

void MainWindow::startPreview()
{
    generateCode("", "", 540, 350, true);
    QProcess rt;
    QStringList args;

    args << "-t 64" << "/tmp/preview.json";
    rt.start("./rt", args);
    rt.waitForFinished();
    rt.close();
    ui->preview->setPixmap(QPixmap("/tmp/preview.bmp"));
    system("rm -f /tmp/preview.bmp");
    //system("rm -f /tmp/preview.json");
}

void MainWindow::addCamera(QString nameCam, QJsonArray posCam, QJsonArray rotCam)
{
    QTreeWidgetItem *cam = new QTreeWidgetItem(ui->treeObjects);
    cam->setText(0, "Camera");

    QTreeWidgetItem *name = new QTreeWidgetItem(cam);
    name->setText(0, "Name");
    name->setData(1, 0, nameCam);

    QTreeWidgetItem *position = new QTreeWidgetItem(cam);
    position->setText(0, "Position");

    QTreeWidgetItem *posx = new QTreeWidgetItem(position);
    posx->setText(0, "x");
    posx->setData(1, 0, (QVariant)QString::number(posCam[0].toInt()));
    QTreeWidgetItem *posy = new QTreeWidgetItem(position);
    posy->setText(0, "y");
    posy->setData(1, 0, (QVariant)QString::number(posCam[1].toInt()));
    QTreeWidgetItem *posz = new QTreeWidgetItem(position);
    posz->setText(0, "z");
    posz->setData(1, 0, (QVariant)QString::number(posCam[2].toInt()));

    QTreeWidgetItem *rotation = new QTreeWidgetItem(cam);
    rotation->setText(0, "Rotation");

    QTreeWidgetItem *rotx = new QTreeWidgetItem(rotation);
    rotx->setText(0, "x");
    rotx->setData(1, 0, (QVariant)QString::number(rotCam[0].toInt()));
    QTreeWidgetItem *roty = new QTreeWidgetItem(rotation);
    roty->setText(0, "y");
    roty->setData(1, 0, (QVariant)QString::number(rotCam[1].toInt()));
    QTreeWidgetItem *rotz = new QTreeWidgetItem(rotation);
    rotz->setText(0, "z");
    rotz->setData(1, 0, (QVariant)QString::number(rotCam[2].toInt()));
}

void MainWindow::addLight(QString typeLight, QJsonArray posLight, QString colorLight, QString ratioLight)
{
    QTreeWidgetItem *light = new QTreeWidgetItem(ui->treeObjects);
    light->setText(0, "Light");

    QTreeWidgetItem *type = new QTreeWidgetItem(light);
    type->setText(0, "Type");
    type->setData(1, 0, (QVariant)typeLight);

    QTreeWidgetItem *position = new QTreeWidgetItem(light);
    position->setText(0, "Position");

    QTreeWidgetItem *posx = new QTreeWidgetItem(position);
    posx->setText(0, "x");
    posx->setData(1, 0, (QVariant)QString::number(posLight[0].toInt()));
    QTreeWidgetItem *posy = new QTreeWidgetItem(position);
    posy->setText(0, "y");
    posy->setData(1, 0, (QVariant)QString::number(posLight[1].toInt()));
    QTreeWidgetItem *posz = new QTreeWidgetItem(position);
    posz->setText(0, "z");
    posz->setData(1, 0, (QVariant)QString::number(posLight[2].toInt()));

    QTreeWidgetItem *color = new QTreeWidgetItem(light);
    color->setText(0, "Color");
    color->setData(1, 0, (QVariant)colorLight);

    QTreeWidgetItem *ratio = new QTreeWidgetItem(light);
    ratio->setText(0, "Ratio");
    ratio->setData(1, 0, (QVariant)ratioLight);
}

void MainWindow::addShape(QString typeShape, QString shineShape, QString colorShape, QString rayon1Shape, QString rayon2Shape, QJsonArray positionShape, QJsonArray rotationShape, QJsonArray modsShape)
{
    QTreeWidgetItem *shape = new QTreeWidgetItem(ui->treeObjects);
    typeShape.replace(0, 1, typeShape[0].toUpper());
    shape->setText(0, typeShape);

    QTreeWidgetItem *shine = new QTreeWidgetItem(shape);
    shine->setText(0, "Shine");
    shine->setData(1, 0, (QVariant)shineShape);

    QTreeWidgetItem *position = new QTreeWidgetItem(shape);
    position->setText(0, "Position");

    QTreeWidgetItem *posx = new QTreeWidgetItem(position);
    posx->setText(0, "x");
    posx->setData(1, 0, (QVariant)QString::number(positionShape[0].toInt()));
    QTreeWidgetItem *posy = new QTreeWidgetItem(position);
    posy->setText(0, "y");
    posy->setData(1, 0, (QVariant)QString::number(positionShape[1].toInt()));
    QTreeWidgetItem *posz = new QTreeWidgetItem(position);
    posz->setText(0, "z");
    posz->setData(1, 0, (QVariant)QString::number(positionShape[2].toInt()));

    QTreeWidgetItem *rotation = new QTreeWidgetItem(shape);
    rotation->setText(0, "Rotation");

    QTreeWidgetItem *rotx = new QTreeWidgetItem(rotation);
    rotx->setText(0, "x");
    rotx->setData(1, 0, (QVariant)QString::number(rotationShape[0].toInt()));
    QTreeWidgetItem *roty = new QTreeWidgetItem(rotation);
    roty->setText(0, "y");
    roty->setData(1, 0, (QVariant)QString::number(rotationShape[1].toInt()));
    QTreeWidgetItem *rotz = new QTreeWidgetItem(rotation);
    rotz->setText(0, "z");
    rotz->setData(1, 0, (QVariant)QString::number(rotationShape[2].toInt()));

    QTreeWidgetItem *rayon1 = new QTreeWidgetItem(shape);
    rayon1->setText(0, "Rayon 1");
    rayon1->setData(1, 0, (QVariant)rayon1Shape);

    QTreeWidgetItem *rayon2 = new QTreeWidgetItem(shape);
    rayon2->setText(0, "Rayon 2");
    rayon2->setData(1, 0, (QVariant)rayon2Shape);

    QTreeWidgetItem *color = new QTreeWidgetItem(shape);
    color->setText(0, "Color");
    color->setData(1, 0, (QVariant)colorShape);

    /* --- Mods --- */

    QJsonObject mod;
    QTreeWidgetItem *checkerplane = new QTreeWidgetItem(shape);
    checkerplane->setText(0, "Chess Board");
    QTreeWidgetItem *perlin = new QTreeWidgetItem(shape);
    perlin->setText(0, "Perlin noise");

    foreach(const QJsonValue &value, modsShape)
    {
        mod = value.toObject();
        if (mod["name"].toString() == "chess")
        {
            if (mod["enabled"] == true)
                checkerplane->setData(1, 0, "true");
            else
                checkerplane->setData(1, 0, "false");
        }
        else if (mod["name"].toString() == "perlin")
        {
            if (mod["enabled"] == true)
            {
                perlin->setData(1, 0, "true");
                QTreeWidgetItem *type = new QTreeWidgetItem(perlin);
                type->setText(0, "Type");
                type->setData(1, 0, (QVariant)QString::number(mod["type"].toInt()));
                QTreeWidgetItem *color = new QTreeWidgetItem(perlin);
                color->setText(0, "Color");
                color->setData(1, 0, (QVariant)mod["color"].toString());
            }
            else
                perlin->setData(1, 0, "false");
        }
    }
}
