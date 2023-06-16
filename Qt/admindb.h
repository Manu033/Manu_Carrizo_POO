#include <QSqlDatabase>
#include <QString>
#include <QObject>

class AdminDB : public QObject  {
    Q_OBJECT

public:
    AdminDB();
    bool conectar( QString archivoSqlite );
    QSqlDatabase getDB();

private:
    QSqlDatabase db;
};
