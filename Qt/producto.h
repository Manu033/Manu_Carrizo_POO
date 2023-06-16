#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QImage>



namespace Ui {
class Producto;
}

class Producto : public QWidget
{
    Q_OBJECT

public:
    explicit Producto(QWidget *parent = nullptr);
    ~Producto();

    void setDescripcion( QString descripcion );
    void setImagen( QString url );
    void setPrecio(int precio);

private:
    Ui::Producto *ui;

    QNetworkAccessManager *manager;

private slots:
    void slot_descargaFinalizada( QNetworkReply * reply );
};

#endif // PRODUCTO_H
