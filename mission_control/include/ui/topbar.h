#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "ui/menubar.h"

#ifndef TOPBAR
#define TOPBAR

class TopBar : public QWidget{
    Q_OBJECT
    public: 
        QHBoxLayout* layout;
        TopBar(QWidget* parent = nullptr, QWidget* rootui = nullptr);
        ~TopBar();

        QPushButton* close_button;
        QPushButton* minimize_button;
        MenuBar* menubar;
};


#endif