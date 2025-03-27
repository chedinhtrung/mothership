#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>

#include "leftbar.h"
#include "topbar.h"
#include "tabbar.h"
#include "maintab.h"
#include "flightdisplay.h"
#include "mapview.h"

#ifndef MAINUI
#define MAINUI 
class MainUI : public QWidget {
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);
    virtual ~MainUI();

    QJsonObject config;
    TopBar* topbar;
    SideBar* sidebar; 
    TabBar* tabbar;
    MainTab* maintab;
    FlightDisplay* flightdisp;
    MapView* map;
    

public slots:
};
#endif
