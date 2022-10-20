#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    // On isntancie une View par default gerer la fenetre

    this->mainView = new QGraphicsView;

    // On set test a false pour dire que le jeu n'a encore jamais été lancé

    this->test = false;

    // on créé un Scene par defaut pour y generer l'affichage du menu

    QGraphicsScene* scene = new QGraphicsScene();

    // On met un fond a notre scene

    QGraphicsRectItem* qgri2 = new QGraphicsRectItem(0, 0, 525, 700);
    qgri2->setBrush(QPixmap("./../resources/fondd.png"));
    scene->addItem(qgri2);

    // On met un design pour le titre de notre menu

    QGraphicsPixmapItem* titre = new QGraphicsPixmapItem(QPixmap("./../resources/title.png"));
    titre->setPos(50, 50);
    scene->addItem(titre);

    // On créé 2 bouttons play / exit qui sont des elements privés de notre classe
    // On créé 1 QlineEdit afin de recuperer le pseudo du joueur

    but = new QPushButton("Play");
    but2 = new QPushButton("Exit");
    bib = new QLineEdit("username");
    bib->setTextMargins(60,0,0,0);

    // En on créé un Qradiobutton afin de pouvoir selectiionner si l'on veut jouer avec 1 ou 2 voiture

     v1 = new QRadioButton("1 Voiture");
     v2 = new QRadioButton("2 Voiture");

     // On ajoute les widget a notre affichage et on set leur position
    QGraphicsProxyWidget *qr1 = scene->addWidget(v1);
    QGraphicsProxyWidget *qrr = scene->addWidget(v2);
    qr1->setPos(190, 300);
    qrr->setPos(280, 300);
    QGraphicsProxyWidget *qr = scene->addWidget(bib);
    qr->setPos(170, 275);
    QGraphicsProxyWidget *qp1 = scene->addWidget(but);
    qp1->setPos(180,325);
    QGraphicsProxyWidget *qp2 = scene->addWidget(but2);
    qp2->setPos(275,325);


    // Enfin on affichage l'affichage créé
    this->mainView->setScene(scene);
    this->setCentralWidget(mainView);

    // On choisit l'icone voulu pour notre application

    this->setWindowIcon(QIcon("./../resources/icon.png"));

    // On choisit le curseur voulu pour notre applciation

    this->setCursor(QCursor(QPixmap("./../resources/steering_wheel_icon.png")));

    // Enfin on set la taille et le titre de notre fenetre

    this->setWindowTitle("Ninja Dodge");
    this->resize(530, 725);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* actionHelp = new QAction(tr("&About"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

    // On créé une fonction slot qui va permette de savoir quand l'utilisateur a cliqué sur le bouton

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30); //toutes les 30 millisecondes


}

void MainWindow::update() {

    // On emepeche l'utilisateur de cliquer sur les deux bouton (1 et 2 voiture) en meme temps.
    if(v1->isChecked()) v2->setCheckable(false);
    if(v2->isChecked()) v1->setCheckable(false);

    if(but->isDown()) {

        QGraphicsScene* scene = new QGraphicsScene();

        // On recupere le pseudo

        QString text = bib->text();

        //On recupere le nombre de voiture

        if(v1->isChecked()) this->mainscene = new MyScene(text,1);
        else if(v2->isChecked()) this->mainscene = new MyScene(text,2);
        else this->mainscene = new MyScene(text,1);

        // On demarre le jeu

        this->mainView->setScene(mainscene);
        this->test = true;

        // On change la taille de notre fenetre

        this->resize(780, 900);

    }
    if(but2->isDown()) {
        // On arrete notre progamme
        timer->stop();
        exit(0);
    }
    if(test == true && mainscene->isEnd()) {

        /*
         * On cherche ici a revenir a l'ecran de menu lorsque l'utilisateur a fini sa partie et qu'il clique sur menu
         * On va donc recharger entierement notre menu sauf le slot qui lui est deja chargé et deja actif
         */

        test =false;
        QGraphicsScene* scene = new QGraphicsScene();

        QGraphicsRectItem* qgri2 = new QGraphicsRectItem(0, 0, 525, 700);
        qgri2->setBrush(QPixmap("./../resources/fondd.png"));
        scene->addItem(qgri2);

        QGraphicsPixmapItem* titre = new QGraphicsPixmapItem(QPixmap("./../resources/title.png"));
        titre->setPos(50, 50);
        scene->addItem(titre);

        but = new QPushButton("Play");
        but2 = new QPushButton("Exit");
        bib = new QLineEdit("username");
        bib->setTextMargins(60,0,0,0);

        v1 = new QRadioButton("1 Voiture");
        v2 = new QRadioButton("2 Voiture");


        QGraphicsProxyWidget *qr = scene->addWidget(bib);
        qr->setPos(160, 275);
        QGraphicsProxyWidget *qp1 = scene->addWidget(but);
        qp1->setPos(160,325);
        QGraphicsProxyWidget *qp2 = scene->addWidget(but2);
        qp2->setPos(285,325);
        QGraphicsProxyWidget *qr1 = scene->addWidget(v1);
        QGraphicsProxyWidget *qrr = scene->addWidget(v2);
        qr1->setPos(190, 300);
        qrr->setPos(280, 300);

        this->resize(530, 725);
        this->mainView->setScene(scene);
    }

}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu() {
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleur
    msgBox.exec();
}
