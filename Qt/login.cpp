#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>

#include <QFile>


#include <QSqlQuery>
#include <QSqlRecord>

bool usuarioValido = false;

Login::Login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Login),
                                manager( new QNetworkAccessManager( this ) ),
                                managerClima (new QNetworkAccessManager( this )),
                                managerparaimagen(new QNetworkAccessManager(this)),
                                imagenCargada(false),
    adminDB( new AdminDB )

{
    ui->setupUi(this);
    //conecta a la base de datos local
    adminDB->conectar( "C:/Users/carri/OneDrive/Documentos/UBP FACULTAD DOCUMENTOS/semestre 5/POO/Ejercicios Para subir GitHub/sqlite/Base_Poo" );

    //Imagen de fondo
    connect(managerparaimagen, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargadeimagenFinalizada(QNetworkReply*)));
    managerparaimagen->get(QNetworkRequest(QUrl("https://us.123rf.com/450wm/onairjiw/onairjiw1702/onairjiw170200150/72952333-alta-resoluci%C3%B3n-de-la-textura-de-madera-clara.jpg")));

    //Validar credenciales
    connect( ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validar_con_API()));
    connect( ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar_con_API()));
    connect( manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    //API del clima
    connect(managerClima, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_mostrar_clima(QNetworkReply*)));

    // Connect para validar el recordarme
    connect(ui->leUsuario, SIGNAL(editingFinished()), this, SLOT(slot_recordar()));

    //esto es para que cuando abramos el programa, ya este listo para ingresar el usuario
    ui->leUsuario->setFocus();

    //Armo solicitud para el ws que me trae el clima
    QString sUrl = "https://tusrutashoy.com.ar/api_manu/apiclima.php";
    managerClima ->get( QNetworkRequest( QUrl( sUrl ) ) );

    //Creo objeto clase Ventana Meli para permitir la busqueda
    ventanameli = new VentanaMeli;

}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent*)
{
    if (imagenCargada) {
        QPainter painter(this);
        painter.drawImage(0, 0, imagenBackground.scaled(this->width(), this->height()));
    }
}

void Login::slot_descargadeimagenFinalizada(QNetworkReply* reply)
{
    imagenBackground = QImage::fromData(reply->readAll());
    imagenCargada = true;
    this->repaint();
    this->show(); //Esto hace que no se habra el login hasta que la imagen este descargada
}
void Login::slot_cargar_clima(){
    //Armo solicitud para el ws
    QString sUrl = "http://tusrutashoy.com.ar/api_manu/apiclima.php";
    managerClima ->get( QNetworkRequest( QUrl( sUrl ) ) );
}

void Login::slot_mostrar_clima( QNetworkReply * reply){
    QByteArray clima = reply->readAll();//Lee la respuesta y la manda
    this->setClima(clima);

}

void Login::setClima(QString contenido)
{
    ui->lClima->setText(contenido);//Muestra
}

void Login::slot_validar_con_API()  {
    // Aqui armar la solicitud para el webservice

    QString sUrl = "https://tusrutashoy.com.ar/api_manu/apimanu.php?user=";
    sUrl += ui->leUsuario->text();
    sUrl += "&pass=";
    sUrl += ui->leClave->text();

    manager->get( QNetworkRequest( QUrl( sUrl ) ) );//CONSULTA
}

/**
 * @brief Login::slot_descargaFinalizada se ejecuta cuando la respuesta llega aqui
 * @param reply es toda la info que mando el server
 */
void Login::slot_descargaFinalizada( QNetworkReply * reply )  {
    QByteArray ba = reply->readAll(); //Trae la info desde el php

    //qDebug() << ba;


    if ( ba.contains( "::" ) )  { //el usuario es valido
        ba = ba.replace( "::", "" );
        ba = ba.replace( "/", "" );
        ba = ba.replace( "*", "" );
        ba.toInt();
        ventanameli->setCod_usuario(ba);
        qDebug() <<ba;
        this->hide();

//        QFile file("../contenido.html");
//        file.open(QIODevice::ReadOnly | QIODevice::Text);

        if(ui->leRecordarme->isChecked() && !usuarioValido){
            QSqlQuery * query = new QSqlQuery( adminDB->getDB() );
            query->exec( "INSERT INTO usuarios_recordame (usuario, clave) values ('" + ui->leUsuario->text() + "' , '" + ui->leClave->text() + "' )" );
        }


        ventanameli->show();//Muestra la ventana de MELI
//        ventana->setContenido( file.readAll() );
//        ventana->show();

    }else if( ba.contains( "!" )){//Usuario no válido
        ba = ba.replace( "!", " " );
        ba.remove(0, 2);

        qDebug() << ba;
        QMessageBox::critical(this,"Error de validacion", "Ha alcanzado el limite de 3 intentos, puede intentar de vuelta a las " + ba);
    }else{ // usuario o contraseña invalida
        QMessageBox::critical(this,"Error de validacion", "Usuario o contraseña incorrectos");
    }


}



void Login::slot_recordar(){ //extrae la clave de la base

    if ( adminDB->getDB().isOpen() )  {
        QSqlQuery * query = new QSqlQuery( adminDB->getDB() );

        query->exec( "SELECT usuario, clave FROM usuarios_recordame WHERE usuario='" +
                    ui->leUsuario->text() + "'" );
        //query->exec( "SELECT usuario, clave FROM usuarios");
        //qDebug() << query->lastQuery();

        // Si los datos son consistentes, devolverá un único registro.
        while ( query->next() )  {

            //qDebug() << "1";

            QSqlRecord record = query->record();

            // Obtenemos el número de la columna de los datos que necesitamos.
            int columnaClave = record.indexOf( "clave" );


            ui->leClave->setText(query->value( columnaClave ).toString());//convierte el valor en string
            usuarioValido = true;
        }


    }

}


