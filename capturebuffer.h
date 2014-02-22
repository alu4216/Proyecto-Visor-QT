#ifndef CAPTUREBUFFER_H
#define CAPTUREBUFFER_H
#include <QList>
#include <QDebug>
#include <QAbstractVideoSurface>

class CaptureBuffer : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CaptureBuffer(QObject *parent = 0);
    ~CaptureBuffer();
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType =
                                                            QAbstractVideoBuffer::NoHandle) const
    {
        QList<QVideoFrame::PixelFormat> formats;
               formats << QVideoFrame::Format_ARGB32;
               formats << QVideoFrame::Format_ARGB32_Premultiplied;
               formats << QVideoFrame::Format_RGB32;
               formats << QVideoFrame::Format_RGB24;
               formats << QVideoFrame::Format_RGB565;
               formats << QVideoFrame::Format_RGB555;
               return formats;
               //metodo para devolver los tipos de formatos de video soportados.
    }
    bool present(const QVideoFrame &frame); // A través de este método nos darán el frame para que
                                                            // lo mostremos.

signals:
  void s_image(const QImage&);
public slots:

};

#endif // CAPTUREBUFFER_H
