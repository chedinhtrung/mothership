#ifndef SIDEBAR
#define SIDEBAR
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SideBar : public QWidget { 
    Q_OBJECT

    public:
        SideBar(QWidget* parent=nullptr);
        ~SideBar();

        QVBoxLayout* layout;
        QPushButton* account;
        QPushButton* nav;
        QPushButton* log;
        QPushButton* power;
        QPushButton* sos;
};

#endif