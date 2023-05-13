#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>

#include <QFile>


Login::Login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Login),
                                manager( new QNetworkAccessManager( this ) )

{
    ui->setupUi(this);


    connect( ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validar_con_API()));
    connect( ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar_con_API()));
    connect( manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    ui->leUsuario->setFocus();

    ventana = new Ventana;
}

Login::~Login()
{
    delete ui;
}

void Login::slot_validar_con_API()  {
    // Aqui armar la solicitud para el webservice

    QString sUrl = "https://tusrutashoy.com.ar/api_manu/apimanu.php?user=";
    sUrl += ui->leUsuario->text();
    sUrl += "&pass=";
    sUrl += ui->leClave->text();

    manager->get( QNetworkRequest( QUrl( sUrl ) ) );
}

/**
 * @brief Login::slot_descargaFinalizada se ejecuta cuando la respuesta llega aqui
 * @param reply es toda la info que mando el server
 */
void Login::slot_descargaFinalizada( QNetworkReply * reply )  {
    QByteArray ba = reply->readAll();
    qDebug() << ba;


    if ( ba.contains( "::" ) )  { //el usuario es valido
        ba = ba.replace( "::", " " );
        this->hide();

        QFile file("../contenido.html");
        file.open(QIODevice::ReadOnly | QIODevice::Text);




        //ventana->setContenido( file.readAll() );
        ventana->show();

    }else if( ba.contains( "!" ) ){
        ba = ba.replace( "!", " " );
        ba.remove(0, 2);

        qDebug() << ba;
        QMessageBox::critical(this,"Error de validacion", "Ha alcanzado el limite de 3 intentos, puede intentar de vuelta a las " + ba);
    }else{ // usuario o contraseña invalida
        QMessageBox::critical(this,"Error de validacion", "Usuario o contraseña incorrectos");
    }


}


