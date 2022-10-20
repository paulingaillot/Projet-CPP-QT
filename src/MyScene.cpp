#include "MyScene.h"


using namespace std;

MyScene::MyScene(QString username, int voit2, QObject* parent) : QGraphicsScene(parent) {
    // On recupere les variables en parametre et on les set comme varaible de la classe
    this->username = username;
    this->end = false;
    if(voit2 == 1) this->voit2 = false;
    else this->voit2 = true;

    // On insere un fond different pour le haut de notre fenetre


    QGraphicsRectItem* qgri2 = new QGraphicsRectItem(0, 0, 792, 65);
    qgri2->setBrush(QPixmap("./../resources/fond2.jpg"));
    this->addItem(qgri2);

    // On genere l'affichage du score de notre jeu

    qgti = new QGraphicsTextItem(" 0");
    qgti->setPos(80, 20);
    qgti->setParentItem(qgri2);
    this->addItem(qgti);

    /*
     * On genere les 4 coeurs rouge qui corresponde aux vide
     * Ces 4 coeurs deviendront noir au fur et a mesure que le joueur se prend des voiture
     */

     H1 = new QGraphicsPixmapItem(QPixmap("./../resources/red_heart.png"));
    H1->setPos(650, 20);
    this->addItem(H1);

     H2 = new QGraphicsPixmapItem(QPixmap("./../resources/red_heart.png"));
    H2->setPos(675, 20);
    this->addItem(H2);

     H3 = new QGraphicsPixmapItem(QPixmap("./../resources/red_heart.png"));
    H3->setPos(700, 20);
    this->addItem(H3);

     H4 =new QGraphicsPixmapItem(QPixmap("./../resources/red_heart.png"));
    H4->setPos(725, 20);
    this->addItem(H4);

    // Meilleur Score
    // Lecture du fichier pour recuperer le meilleur score

    ifstream fichier("./../resources/best.txt", ios::in);  // on ouvre en lecture

    if(fichier)  // si l'ouverture a fonctionné
    {
        string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
        getline(fichier, contenu);  // on met dans "contenu" la ligne
        QString fi = contenu.c_str();
        bestu = new QGraphicsTextItem(" te");
        bestu->setPlainText(fi);
        bestu->setPos(300, 40);
        bestu->setParentItem(qgri2);
        this->addItem(bestu);
        getline(fichier, contenu);
        QString fi2 = contenu.c_str();
        bests = new QGraphicsTextItem(" ter");
        bests->setPlainText(fi2);
        bests->setPos(400, 40);
        bests->setParentItem(qgri2);
        this->addItem(qgti);

        fichier.close();
    }
    else
        // Message d'erreur si probleme dans la lecture du ficiher
        cerr << "Impossible d'ouvrir le fichier !" << endl;


    QGraphicsPixmapItem* top = new QGraphicsPixmapItem(QPixmap("./../resources/top.png"));
    top->setPos(270, 36);
    this->addItem(top);

    // On genere le fond de notre fentre


    QGraphicsRectItem* qgri = new QGraphicsRectItem(0, 65, 792, 800);
    qgri->setBrush(QPixmap("./../resources/fond.jpg"));
    this->addItem(qgri);

    // On affiche notre premiere voiture

    QGraphicsPixmapItem* voiture = new QGraphicsPixmapItem(QPixmap("./../resources/voiture.png"));
    voiture->setPos(510, 65);
    this->addItem(voiture);
    this->voiture = voiture;

    // On affiche l'icone de vitesse a coté de notre compteur de vitesse

    QGraphicsPixmapItem* speedometer = new QGraphicsPixmapItem(QPixmap("./../resources/speedometer.png"));
    speedometer->setPos(50, 20);
    this->addItem(speedometer);

    // On genere une 2e voiture qui ne bougera qui si le bool voit2 vaut true

        QGraphicsPixmapItem *voiture2 = new QGraphicsPixmapItem(QPixmap("./../resources/voiture.png"));
        voiture2->setPos(340, 65);
        this->addItem(voiture2);
        this->voiture2 = voiture2;

        // Si voit2 == true alors on rend invisible l'item pour ne pas voir la 2e voiture

    if(this->voit2 == true) {
    }else {
        this->voiture2->setVisible(false);
    }

    // On affiche l'utilisateur dans notre fenetre

    QGraphicsPixmapItem* user = new QGraphicsPixmapItem(QPixmap("./../resources/user.png"));
    user->setPos(360, 750);
    this->addItem(user);
    this->user = user;

    // Points et collisions par defaut a 60 et 0 pts

    points = 60;
    collision = 0;

    // On demarre le timer et le slot update()

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30); //toutes les 30 millisecondes

}

void MyScene::update() {
    // si il y a collision
    if (voiture->collidesWithItem(user) || (voiture2->collidesWithItem(user) && voiture2->isVisible())) {
        collision ++; // On augmente la valeur de collision

        if(collision == 1) H4->setPixmap(QPixmap("./../resources/black_heart.png")); // 1 coeur noir
        if(collision == 2) H3->setPixmap(QPixmap("./../resources/black_heart.png")); // 2 coeur noir
        if(collision == 3) H2->setPixmap(QPixmap("./../resources/black_heart.png")); // 3 coeur noir
        if(collision == 4) H1->setPixmap(QPixmap("./../resources/black_heart.png")); // 4 coeur noir -> fin du jeu

        if(collision != 4) { // si le jeu n'est pas fini

            // On tp la voiture en haut pour ne pas avoir d'autre collision, la voiture est donc regeneré sur un empalcement aleatoire
            int posx;
            int alea = rand() % 3 + 1;
            if (alea == 1) posx = 340;
            else if (alea == 2) posx = 340 - 170;
            else posx = 340 + 170;
            voiture->setPos(posx, 50); //incrémentation de la coordonnée y*

            //Si on joue avec 2 voitures alors on va generer (avec une proba de 0.5) une seconde voiture sur un emplacement aleatoire
            // Si la 2e voiture n'est pas généré alors on va la rendre invisible et la palcé en 0 0
            if(voit2 == true) {

                int alea = rand() % 2 + 1;

                if(alea == 2) {
                    int posx;
                    int alea = rand() % 3 + 1;
                    if (alea == 1) posx = 340;
                    else if (alea == 2) posx = 340 - 170;
                    else posx = 340 + 170;
                    voiture2->setPos(posx, 50); //incrémentation de la coordonnée y*
                    voiture2->setVisible(true);
                } else {
                    voiture2->setVisible(false);
                }
            }

        }else { // fin du jeu

            // On recup le meilleur score

            ifstream fichier("./../resources/best.txt", ios::in);  // on ouvre en lecture
            int val =0;

            if(fichier)  // si l'ouverture a fonctionné
            {
                string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
                getline(fichier, contenu);  // on met dans "contenu" la ligne
                getline(fichier, contenu);
                val = stoi(contenu);

                fichier.close();
            }
            else
                cerr << "Impossible d'ouvrir le fichier !" << endl;

            if(val < points) {

                // On ecrit le nouveau meilleur score

                ofstream monFlux("./../resources/best.txt");

                if (monFlux) {
                    monFlux << username.toStdString() << endl;
                    monFlux << (points) << endl;
                } else {
                    cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
                }

            }

            // On créé un fenetre flottante pour prevenir que le jeu est fini et que l'utilisateur doit quitter / recevnir au menu / relancer une partie
            QMessageBox msgBox;
            msgBox.setText("Game Over !!");
            msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
            QPushButton* connectButton = msgBox.addButton("Retry",  QMessageBox::ActionRole); // trelance une partie
            QPushButton* menuButton = msgBox.addButton("Menu",  QMessageBox::ActionRole); // retourne au menu
            QPushButton* abortButton = msgBox.addButton("Leave",  QMessageBox::DestructiveRole); // quitte le jeu

            msgBox.exec();

            if (msgBox.clickedButton() == connectButton) {
                this->reset(); // relance le jeu
            } else if (msgBox.clickedButton() == abortButton) {
                timer->stop();
                exit(0); // arrete le programme
            } else if (msgBox.clickedButton() == menuButton) {
                timer->stop();
                end = true; // cet varaible va enelcher la fonction update dans mainwindows ce qui va reafficher le menu
            }

        }
    }

    QPointF pos = voiture->pos(); //récupération de la position de l'objet qgti

    if((int)(pos.ry()) > 750) {//La voiture a  atteind le points le plus bas de la fenetre
        // on tp la premiere voiture en haut
        int posx;
        int alea = rand()%3 + 1;
        if(alea == 1) posx = 340;
        else if(alea == 2) posx=340-170;
        else posx= 340+170;
        voiture->setPos(posx, 50); //incrémentation de la coordonnée y
        // on tp la deuxieme voiture en haut
        if(voit2 == true) {

            int alea = rand() % 2 + 1;

            if(alea == 2) {
                int posx;
                int alea = rand() % 3 + 1;
                if (alea == 1) posx = 340;
                else if (alea == 2) posx = 340 - 170;
                else posx = 340 + 170;
                voiture2->setPos(posx, 50); //incrémentation de la coordonnée y*
                voiture2->setVisible(true);
            }else voiture2->setVisible(false);
        }

    }else {
        // On fait avancer la premiere voiture
        voiture->setPos(pos.rx(), pos.ry()+5); //incrémentation de la coordonnée y
        // on fait avancer la 2e voiture si elle est visible
        if(voit2 == true) {
            QPointF pos2 = voiture2->pos();
            voiture2->setPos(pos2.rx(), pos2.ry()+5); //incrémentation de la coordonnée y
        }
    }
    // on augmente les pts
    points+= 0.05;
    // On met a jour l'affichage du score
    qgti->setPlainText(QString(" %1 km/h").arg(points-10));
    // on change la vitesse de deplacement des voiture (et donc de la fonction elle meme) en fonction du score (vitesse) du joueur.
    timer->setInterval(1.5*1000/(points));

}

void MyScene::keyPressEvent(QKeyEvent* event){
    if(timer->isActive() && (event->key() == Qt::Key_Right && user->pos().rx() != 530)) { // appui sur la touche right_arrow du clavier
        this->user->setPos(user->pos().rx() +170, user->pos().ry());
    }
    if(timer->isActive() && (event->key() == Qt::Key_Left && user->pos().rx() != 190)) { // appui sur la touche left_arrow du clavier
        this->user->setPos(user->pos().rx() -170, user->pos().ry());
    }
    if(event->key() == Qt::Key_Escape) { // appui sur la touche escape du clavier
        if(timer->isActive()) timer->stop(); // on met en pause le jeu si il est demarré
        else timer->start(); // on relance le jeu si il etait en pâuse
    }
}

bool MyScene::isEnd() {
    return end; // fonction pour recuperer la varaible privé en dehors de la classe
}

void MyScene::reset(){

    /*
     * Fonction de reset permettant de relancer le jeu a zero apres une defaite.
     */

    // On reset les pts / collision

    points = 60;
    collision = 0;

    // On repositionne les voitures

    int posx;
    int alea = rand()%3 + 1;
    if(alea == 1) posx = 340;
    else if(alea == 2) posx=340-170;
    else posx= 340+170;

    if(voit2 == true) {
        int posx2;
        int alea = rand() % 3 + 1;
        if (alea == 1) posx2 = 340;
        else if (alea == 2) posx2 = 340 - 170;
        else posx2 = 340 + 170;
        voiture2->setPos(posx2, 50);
    }

    voiture->setPos(posx, 50); //incrémentation de la coordonnée y

    // On remet tout les coeurs en rouge

    H1->setPixmap(QPixmap("./../resources/red_heart.png"));
    H2->setPixmap(QPixmap("./../resources/red_heart.png"));
    H3->setPixmap(QPixmap("./../resources/red_heart.png"));
    H4->setPixmap(QPixmap("./../resources/red_heart.png"));

    // On recupere le score du meilleur joueur a nouveau

    ifstream fichier("./../resources/best.txt", ios::in);  // on ouvre en lecture

    string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
    getline(fichier, contenu);  // on met dans "contenu" la ligne
    QString fi = contenu.c_str();

    bestu->setPlainText(fi);
    bestu->setPos(300, 40);
    getline(fichier, contenu);
    QString fi2 = contenu.c_str();
    bests->setPlainText(fi2);
    bests->setPos(400, 40);

    //On redemarre le timer avec la vitesse de base

    timer->setInterval(30); //toutes les 30 millisecondes
}

MyScene::~MyScene() {
// Destructeur vide
}
