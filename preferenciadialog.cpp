#include "preferenciadialog.h"
#include "ui_preferenciadialog.h"

PreferenciaDialog::PreferenciaDialog(const QList<QByteArray> &devices,QWidget * parent) :
    QDialog(parent),
    ui(new Ui::PreferenciaDialog)
{
    ui->setupUi(this);
   // QList<QByteArray> devices = QCamera::availableDevices();
    qDebug() << "Capturando de... "
             << QCamera::deviceDescription(devices[0]);
     qDebug()<< "Tamaño de...."
                <<devices.size();
     QSettings settings;
     int i=0;
     do {
     ui->comboBox->addItem(QCamera::deviceDescription(devices[i]));
     i++;
     }while(i<devices.size());

     ui->comboBox->setCurrentIndex(settings.value("indice").toInt());




}

PreferenciaDialog::~PreferenciaDialog()
{
    delete ui;
}

void PreferenciaDialog::on_pushOk_clicked()
{
    indice=ui->comboBox->currentIndex();
    QSettings settings;
    settings.value("indice",indice);
    emit s_camera(indice);
    close();
}

void PreferenciaDialog::on_pushCerrar_clicked()
{
    close();
}
