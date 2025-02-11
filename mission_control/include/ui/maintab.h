#include <QWidget>

#ifndef MAINTAB
#define MAINTAB

class MainTab : public QWidget{
    Q_OBJECT
    
    public:
    MainTab(QWidget* parent=nullptr);
    ~MainTab();

};

#endif