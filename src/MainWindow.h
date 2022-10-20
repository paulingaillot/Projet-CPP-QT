#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QTimer>

#include "MyScene.h"
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class MainWindow : public QMainWindow {
Q_OBJECT

private :
    // Timer pour le slot
    QTimer* timer;
    // Affichage actif
    MyScene* mainscene;
    // Fenetre
    QGraphicsView* mainView;
    // ToolsBar
    QMenu* helpMenu;
    // Boutons play & exit
    QPushButton* but;
    QPushButton* but2;
    // Qlineedit pour le pseudo du joueur
    QLineEdit* bib;
    //Varaible bool pour savoir si le jeu est actuelement demarré
    bool test = false;
    // RadioBouton pour savoir si on joue avec 1 ou 2 voiture
    QRadioButton* v1;
    QRadioButton* v2;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    //Slot de la toolsbar
    void slot_aboutMenu();
    //slot pour savoir si l'utilisateur a cliqué sur un bouton
    void update();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
