
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QNetworkAccessManager>  // Para ejecutar solicitudes GET, POST, etc
#include <QNetworkRequest>  // Contener la info que ira hacia el server
#include <QNetworkReply>  // Contiene la info que viene desde el server
#include <QUrl>
#include <QPainter>

#include "ventana.h"
#include "admindb.h"
#include "ventanameli.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget

{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void setClima( QString contenido );

private:
    Ui::Login * ui;
    QNetworkAccessManager * manager;
    QNetworkAccessManager * managerClima;
    QNetworkAccessManager * managerparaimagen;

    //Para poner imagen de fondo
    QImage imagenBackground;
    bool imagenCargada;

    AdminDB * adminDB;
    VentanaMeli * ventanameli;



private slots:
    void slot_cargar_clima();
    void slot_mostrar_clima( QNetworkReply * reply);
    void slot_validar_con_API();
    void slot_descargaFinalizada( QNetworkReply * reply );
    void slot_recordar();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void slot_descargadeimagenFinalizada( QNetworkReply * reply );
};

#endif // LOGIN_H
