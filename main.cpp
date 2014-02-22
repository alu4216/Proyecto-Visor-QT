#include "viewerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Josue");
    QCoreApplication::setApplicationName("check");
    ViewerWindow w;
    w.show();

    return a.exec();//no se sale hasta que el usuario no cierre.Bucle infinito esperando que ocurra algo.
                    //Espera señales. Manda señales a partir de lo ocurrido.
}
