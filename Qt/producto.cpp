#include "producto.h"
#include "ui_producto.h"
#include <QImage>
#include <QPixmap>

Producto::Producto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Producto),
    manager( new QNetworkAccessManager( this ) )
{
    ui->setupUi(this);

    // Conectar network con slot_descargaFinalizada
    connect( manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

}

Producto::~Producto()
{
    delete ui;
}

void Producto::setDescripcion(QString descripcion)
{
    ui->lDescripcion->setText( descripcion );
}

void Producto::setImagen(QString url)
{
    manager->get( QNetworkRequest( QUrl( url ) ) );
}

void Producto::setPrecio(int precio)
{
    ui->lPrecio->setNum(precio);
}

void Producto::slot_descargaFinalizada(QNetworkReply *reply)
{
    QImage image = QImage::fromData(reply->readAll());
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->imagen->setPixmap(pixmap);
    ui->imagen->setFixedSize(100,100);

}
