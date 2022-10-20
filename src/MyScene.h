#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QPushButton>
#include <fstream>
#include <QInputDialog>
#include <QTextEdit>
#include <QAction>

class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    // Timer
    QTimer* timer;
    // Nom de l'utilisateur
    QString username;
    // Voitures pouvants spawn
    QGraphicsPixmapItem* voiture;
    QGraphicsPixmapItem* voiture2;
    // Bool pour savoir si l'on joue avec 1 ou 2 voiture max
    bool voit2 = false;
    // Tortue utilisateur
    QGraphicsPixmapItem* user;
    // Afficheur Score utilisateur
    QGraphicsTextItem* qgti;
    // Score user
    double points;
    // Nb de collision
    int collision;
    // Bool de fin de game pour revenir au menu
    bool end;
    // Nom du meilleur joueur
    QGraphicsTextItem* bestu;
    // Score du meilleur joueur
    QGraphicsTextItem* bests;

    //Coeurs de vie (rouge ou noir)
    QGraphicsPixmapItem* H1;
    QGraphicsPixmapItem* H2;
    QGraphicsPixmapItem* H3;
    QGraphicsPixmapItem* H4;

protected:
    //Event en cas d'appui sur touche du clavier
    void keyPressEvent(QKeyEvent* event);
public:
    //Fonction pour redemarrer le jeu
    void reset();
    //Ceci est un constructeur
    MyScene(QString username, int voit2, QObject* parent = nullptr);
    // Ceci est un desctructeur (vide pour un proejt QT)
    virtual ~MyScene();
    // GetEnd() pour recuperer de maniere public si le jeu est fini ou non
    bool isEnd();
public slots:
    // Fonction slot d'update du jeu
    void update();


};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
