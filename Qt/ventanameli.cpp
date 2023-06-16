#include <QSqlDatabase>
#include <QSqlQuery>

#include "ventanameli.h"
#include "ui_ventanameli.h"

VentanaMeli::VentanaMeli(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VentanaMeli),
    managerBusqueda( new QNetworkAccessManager( this ))
  //  managerGuardaBusq(new QNetworkAccessManager(this))


{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("https://w7.pngwing.com/pngs/633/292/png-transparent-mercadolibre-hd-logo.png"));
//    ui->producto1->setDescripcion( "Producto 1" );
//    ui->producto1->setImagen( "https:///" );

    connect(ui->pbBuscar, SIGNAL(pressed()), this, SLOT(slot_descargar_producto()));
    connect( managerBusqueda, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_descargaFinalizada(QNetworkReply*)));


}

VentanaMeli::~VentanaMeli()
{
    delete ui;
}

void VentanaMeli::setCod_usuario(const QString &newCod_usuario)
{
    cod_usuario = newCod_usuario;
}

QString VentanaMeli::getCod_usuario() const
{
    return cod_usuario;
}

void VentanaMeli::slot_descargar_producto()
{ //una vez que el usuario ya ingreso lo que desea buscar y apreta el boton
    managerBusqueda->get(QNetworkRequest (QUrl("https://api.mercadolibre.com//sites/MLA/search?limit=5&sort=price_asc&q="+ ui->leBuscar->text())));



}

void VentanaMeli::slot_descargaFinalizada( QNetworkReply * reply)
{
    //Guardar en la base la ultima búsqueda

    /*QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName("C:/Users/carri/OneDrive/Documentos/UBP FACULTAD DOCUMENTOS/semestre 5/POO/Ejercicios Para subir GitHub/sqlite/Base_Poo");
    QString valor = ui->leBuscar->text();
    QSqlQuery query;
    query.prepare("INSERT INTO usuarios_recordame (ultima_busqueda) VALUES (:valor)");
    query.bindValue(":valor", valor);
    db1.close();*/

   // analizar json con QJsonDocument QJsonArray QJsonObject
    QByteArray ba = reply->readAll();
    //qDebug() << ba;
    QString json_string = ba; //reply->readAll();  //Lee el JSON
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8()); //Accede a los datos del JSON utilizando métodos y propiedades de QJsonDocument, QJsonObject y QJsonArray:

    if (json_doc.isObject()) {
       // qDebug() << "es objeto";

        QJsonObject jsonObject = json_doc.object();

        if (jsonObject.contains("results")) {
            QJsonValue resultsValue = jsonObject.value("results");
            if (resultsValue.isArray()) {
                QJsonArray resultsArray = resultsValue.toArray();
                // Recorrer el array de resultados
                int cantResultados=0;

                for (const QJsonValue& result : resultsArray) {
                    if (cantResultados>4){
                        break;
                    }
                    // Acceder a los campos de cada resultado
                    if(cantResultados == 0){
                        if (result.isObject()) {
                            QJsonObject resultObject = result.toObject();
                            if (resultObject.contains("thumbnail")) {
                                QString foto = resultObject.value("thumbnail").toString();
                                qDebug() << "Foto: " << foto;
                                ui->producto1->setImagen(foto);
                            }
                            if (resultObject.contains("title")) {
                                QString descripcion = resultObject.value("title").toString();
                                qDebug() << "Descripcion: " << descripcion;
                                ui->producto1->setDescripcion(descripcion);
                            }
                            if (resultObject.contains("price")) {
                                int precio = resultObject.value("price").toInt();
                                qDebug() << "Precio: " << precio;
                                ui->producto1->setPrecio(precio);

                            }
                        }
                    }
                        if(cantResultados == 1){
                        if (result.isObject()) {
                            QJsonObject resultObject = result.toObject();
                            if (resultObject.contains("thumbnail")) {
                                QString foto = resultObject.value("thumbnail").toString();
                                qDebug() << "Foto: " << foto;
                                ui->producto2->setImagen(foto);
                            }
                            if (resultObject.contains("title")) {
                                QString descripcion = resultObject.value("title").toString();
                                qDebug() << "Descripcion: " << descripcion;
                                ui->producto2->setDescripcion(descripcion);
                            }
                            if (resultObject.contains("price")) {
                                int precio = resultObject.value("price").toInt();
                                qDebug() << "Precio: " << precio;
                                ui->producto2->setPrecio(precio);
                            }
                        }
                    }
                    if(cantResultados == 2){
                        if (result.isObject()) {
                            QJsonObject resultObject = result.toObject();
                            if (resultObject.contains("thumbnail")) {
                                QString foto = resultObject.value("thumbnail").toString();
                                qDebug() << "Foto: " << foto;
                                ui->producto3->setImagen(foto);
                            }
                            if (resultObject.contains("title")) {
                                QString descripcion = resultObject.value("title").toString();
                                qDebug() << "Descripcion: " << descripcion;
                                ui->producto3->setDescripcion(descripcion);
                            }
                            if (resultObject.contains("price")) {
                                int precio = resultObject.value("price").toInt();
                                qDebug() << "Precio: " << precio;
                                ui->producto3->setPrecio(precio);

                            }
                        }
                    }
                    if(cantResultados == 3){
                        if (result.isObject()) {
                            QJsonObject resultObject = result.toObject();
                            if (resultObject.contains("thumbnail")) {
                                QString foto = resultObject.value("thumbnail").toString();
                                qDebug() << "Foto: " << foto;
                                ui->producto4->setImagen(foto);
                            }
                            if (resultObject.contains("title")) {
                                QString descripcion = resultObject.value("title").toString();
                                qDebug() << "Descripcion: " << descripcion;
                                ui->producto4->setDescripcion(descripcion);
                            }
                            if (resultObject.contains("price")) {
                                int precio = resultObject.value("price").toInt();
                                qDebug() << "Precio: " << precio;
                                ui->producto4->setPrecio(precio);

                            }
                        }
                    }
                    if(cantResultados == 4){
                        if (result.isObject()) {
                            QJsonObject resultObject = result.toObject();
                            if (resultObject.contains("thumbnail")) {
                                QString foto = resultObject.value("thumbnail").toString();
                                qDebug() << "Foto: " << foto;
                                ui->producto5->setImagen(foto);
                            }
                            if (resultObject.contains("title")) {
                                QString descripcion = resultObject.value("title").toString();
                                qDebug() << "Descripcion: " << descripcion;
                                ui->producto5->setDescripcion(descripcion);
                            }
                            if (resultObject.contains("price")) {
                                int precio = resultObject.value("price").toInt();
                                qDebug() << "Precio: " << precio;
                                ui->producto5->setPrecio(precio);

                            }
                        }
                    }
                    cantResultados++;
                }
            }
        }
    }

    //QString sUrl = "https://tusrutashoy.com.ar/api_manu/GuardarBusqueda.php?busqueda=";
    // sUrl += ui->leBuscar->text();
    //sUrl += "&cod_usuario=";
    //sUrl += getCod_usuario();
    //qDebug() << getCod_usuario().toInt();


    //managerGuardaBusq->get( QNetworkRequest( QUrl( sUrl ) ) );




}


