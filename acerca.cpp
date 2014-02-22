#include "acerca.h"
#include "ui_acerca.h"

Acerca::Acerca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acerca)
{
    ui->setupUi(this);
}

Acerca::~Acerca()
{
    delete ui;
}
void Acerca::imagen()
{

   QPixmap pixmap("/home/josue/QTproyectos/build-visor-Desktop_Qt_5_2_0_GCC_64bit-Debug/qt_logo.png");

   ui->label_texto->setText(tr("Estado del visor\n"
                      "Based on Qt 5.2.0 (GCC 4.6.1, 64 bit)"));

   ui->label->setPixmap(pixmap);
}
