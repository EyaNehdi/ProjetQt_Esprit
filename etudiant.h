#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QSqlQueryModel>
#include<QString>
#include<QTableView>
class Etudiant
{
public:
    Etudiant();
    Etudiant (int,QString,QString,int);
    int getid();
    int getnum_voy();

    QString getnom();
    QString getprenom();
    void setid(int);
    void setnum_voy(int);

    void setnom(QString);
    void setprenom(QString);
bool ajouter();
QSqlQueryModel *afficher();
QSqlQueryModel * tri_prenom();
QSqlQueryModel *tri_nom();
QSqlQueryModel * tri_id();
bool supprimer(int);
void chercheID(QTableView *table, int ID);
void clearTable(QTableView *table);
bool modifier(int);
private:
    int ID,NUM_VOY;
    QString NOM,PRENOM;
};

#endif // ETUDIANT_H
