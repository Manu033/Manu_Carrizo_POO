#ifndef VENTANAMELI_H
#define VENTANAMELI_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QImage>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "producto.h"


namespace Ui {
class VentanaMeli;
}

class VentanaMeli : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaMeli(QWidget *parent = nullptr);
    ~VentanaMeli();

    void setCod_usuario(const QString &newCod_usuario);

    QString getCod_usuario() const;

private:
    Ui::VentanaMeli *ui;
    QNetworkAccessManager * managerBusqueda;
    //QNetworkAccessManager * managerGuardaBusq;

    Producto * producto;
    QString cod_usuario;
private slots:
    void slot_descargar_producto();
    void slot_descargaFinalizada(QNetworkReply * reply);


};

#endif // VENTANAMELI_H
