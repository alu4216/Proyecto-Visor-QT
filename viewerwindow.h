#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QFile>
#include <QLabel>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <QWaitCondition>
#include <QMutex>
#include <QMovie>
#include <QSettings>
#include <QCamera>
#include <QCameraViewfinder>
#include <QPainter>
#include <QDateTime>
#include "acerca.h"
#include "preferenciadialog.h"
#include "capturebuffer.h"
#include "QVideoFrame"


namespace Ui {
class ViewerWindow;
}

class ViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewerWindow(QWidget *parent = 0);
    ~ViewerWindow();

private slots:
    void on_Salir_clicked();

    void on_actionSalir_triggered();

    void on_actionAbrirImagen_triggered();

    void on_actionAbrirVideo_triggered();

    void movie_frame(const QRect& rect);

    void on_checkBox_stateChanged(int arg1);

    void on_actionAcercaDe_triggered();

    void on_Push_Pausa_clicked();

    void on_actionCapturar_triggered();

    void on_actionPreferencias_triggered();

    void actualizar_s(int);

    void image_s(const QImage&);


private:
    Ui::ViewerWindow * ui;//puntero al formulario
    QMovie * movie;
    Acerca * dialog;
    PreferenciaDialog * preferencias;
    QList<QByteArray> devices;
    QCamera * camera;
    QCameraViewfinder * viewfinder;
    CaptureBuffer * captureBuffer;
    int check;
    int indice;


};

#endif // VIEWERWINDOW_H
