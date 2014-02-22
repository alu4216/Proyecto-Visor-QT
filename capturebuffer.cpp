#include "capturebuffer.h"

CaptureBuffer::CaptureBuffer(QObject *parent) :
    QAbstractVideoSurface(parent)
{
}

CaptureBuffer::~CaptureBuffer()
{

}

bool CaptureBuffer:: present(const QVideoFrame &frame)
{

   QVideoFrame frame2(frame);

   frame2.map(QAbstractVideoBuffer::ReadOnly);

   QImage frameAsImage = QImage(frame2.bits(), frame2.width(),frame2.height(), frame2.bytesPerLine(),
                                  QVideoFrame::imageFormatFromPixelFormat(frame2.pixelFormat()));

   frameAsImage.copy();
   emit s_image(frameAsImage);

   frame2.unmap();



 return true;
}
