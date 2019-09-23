#include "mainwindow.h"

int main(int argc, char *argv[])
{
    char *str;

    if (argc > 1)
        str = argv[1];
    else
        str = NULL;
    QApplication a(argc, argv);
    MainWindow w(str);
    w.show();
    return a.exec();
}
