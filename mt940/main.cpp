#include "mt940.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MT940 w;
    w.show();
    return a.exec();
}
