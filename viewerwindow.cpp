#include "viewerwindow.h"
#include "ui_viewerwindow.h"



ViewerWindow::ViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerWindow) //se crea el formulario
{

    QSettings  settings;
    //para guardar las variables una vez cerrado el programa
    ui->setupUi(this); // se configura el formulario
    movie = new QMovie();
    indice=settings.value("indice").toInt();
    check=settings.value("check").toInt();
    ui->checkBox->setChecked(check);
    indice=settings.value("indice").toInt();

}

ViewerWindow::~ViewerWindow()
{
    delete ui;
    delete movie;
    delete dialog;
    delete preferencias;
    delete camera;
    delete viewfinder;
}

void ViewerWindow::on_Salir_clicked()
{
  qApp->quit(); //qApp apunta al objeto creado en el main(QAplication)
   //quit no cierra instantaneamente. Cierra primero los mensajes que esten delante del quit y luego cierra.
}

void ViewerWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void ViewerWindow::on_actionAbrirImagen_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,"abrir archivo",  //es un método estático por lo que no hace falta instanciar el objeto de la clase QFileDialog

                                                  QString());

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this,"Abrir archivo","El archivo no puedo ser abierto.");
        }
        else {

          /*QTextStream stream (&file);
            QString texto;
            texto=stream.readAll();
            ui->textEdit->setText(texto);
          */

          QPixmap pixmap(fileName);
          ui->label->setPixmap(pixmap);

          //*****************************************************
          //QImageReader ir(&file);
          //Qpixmap pixmap = QPixmap::fromImageReader(&ir);
          // ui->label->setPixmap(pixmap);
          //*****************************************************

      /*   QWaitCondition wc; //variable de condición par que un hilo espere a un acontecimiento
         QMutex mutex;//semaforo de binario. Para controlar los hilos. Duerme hilos para liberar cpu cuando no tienen nada que hacer
         wc.wait(&mutex,5000); //esperar que un hilo despierte
      */
        }

    }


}

void ViewerWindow::on_actionAbrirVideo_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,"abrir archivo de video",QString(),"video(*.mjpeg)");

    movie->setFileName(fileName);


    if (!movie->isValid()) {
            QMessageBox::critical(this, tr("Error"),tr("No se pudo abrir el archivo o el formato"
                                                                                 " es inválido"));
            return;
    }
    else {
    // ui->label->setMovie(movie);
     if(ui->checkBox->checkState()==2) movie->start();

     //coneccion de señales
     connect(movie, SIGNAL(updated(const QRect&)),this, SLOT(movie_frame(const QRect&)));
     connect(ui->push_Start, SIGNAL(clicked()), movie, SLOT(start()));
     connect(ui->push_Stop, SIGNAL(clicked()), movie, SLOT(stop()));
     connect(ui->Push_Pausa,SIGNAL(clicked()),this,SLOT(on_Push_Pausa_clicked()));

   }
}

void ViewerWindow::on_Push_Pausa_clicked()
{
    movie->setPaused(true);

}

void ViewerWindow::movie_frame(const QRect& rect)
{
    QPixmap pixmap = movie->currentPixmap();
    ui->label->setPixmap(pixmap);

}

void ViewerWindow::on_checkBox_stateChanged(int arg1)
{
    QSettings  settings;
  settings.setValue("check",arg1);
}

void ViewerWindow::on_actionAcercaDe_triggered()
{
    dialog= new Acerca();
    dialog->imagen();
    dialog->exec();

}

void ViewerWindow::on_actionCapturar_triggered()
{

  devices = QCamera::availableDevices();


  camera = new QCamera(devices[indice]); // no permite capturar de la cam
  captureBuffer = new CaptureBuffer();
  camera->setViewfinder(captureBuffer); // selecionamos el visor instanciado anteriormente para nuestra captura

  camera->start();//iniciamos la captura de imagene

  connect(captureBuffer,SIGNAL(s_image(QImage)),this,SLOT(image_s(QImage)));
  /*
  camera = new QCamera(devices[indice]); // no permite capturar de la cam
  viewfinder = new QCameraViewfinder();// nos permite seleccionar un visor para lo que capturamos
  camera->setViewfinder(viewfinder); // selecionamos el visor instanciado anteriormente para nuestra captura
  viewfinder->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);//añadimos las politicas para nuestro visor
  setCentralWidget(viewfinder);//lo ponemos en el widget central
  camera->setCaptureMode(QCamera::CaptureViewfinder);//con esto indicamos que solo se reproducirá la imagen en el visor.
  camera->start();//iniciamos la captura de imagenes
*/
}

void ViewerWindow::on_actionPreferencias_triggered()
{
    devices = QCamera::availableDevices();
    preferencias=new PreferenciaDialog(devices);
    preferencias->show();
    connect(preferencias,SIGNAL(s_camera(int)),this,SLOT(actualizar_s(int)));

}

void ViewerWindow::actualizar_s(int i)
{
    indice=i;
    //on_actionCapturar_triggered();

}
void ViewerWindow::image_s(const QImage &image)
{
  //QPainter paint;
  QTime time = QTime::currentTime();
  QString timeString = time.toString();
  QPixmap pixmap;
  pixmap=pixmap.fromImage(image);
  QPainter paint(&pixmap);
  paint.setPen(Qt::green);
  paint.drawText(550,450,timeString);


  ui->label->setPixmap(pixmap);


}


