#include <QtGui/QApplication>
#include "FMetro.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    FMetro fmetro;
    fmetro.show();
    return app.exec();
}
