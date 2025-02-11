#include <QTabWidget>
#include <QWidget>

#ifndef TABBAR
#define TABBAR

class TabBar : public QTabWidget{
    Q_OBJECT

    public: 
    TabBar(QWidget* parent=nullptr);
    ~TabBar();
    
};

#endif