#ifndef PREFERENCIADIALOG_H
#define PREFERENCIADIALOG_H

#include <QDialog>
#include <QCamera>
#include <QSettings>

namespace Ui {
class PreferenciaDialog;
}

class PreferenciaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenciaDialog(const QList<QByteArray> &devices,QWidget * parent=0);
    ~PreferenciaDialog();

signals:
    void s_camera(int);

private slots:

    void on_pushOk_clicked();

    void on_pushCerrar_clicked();

private:
    Ui::PreferenciaDialog *ui;
    int indice;
};

#endif // PREFERENCIADIALOG_H
