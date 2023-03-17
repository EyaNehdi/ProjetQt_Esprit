#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("ProjetA2");
db.setUserName("Touta");//inserer nom de l'utilisateur
db.setPassword("Touta");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
