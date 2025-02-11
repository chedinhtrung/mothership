#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "leftbar.h"
#include "topbar.h"
#include "tabbar.h"
#include "maintab.h"

#ifndef MAINUI
#define MAINUI 
class MainUI : public QWidget {
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);
    virtual ~MainUI();
    TopBar* topbar;
    SideBar* sidebar; 
    TabBar* tabbar;
    MainTab* maintab;

public slots:
};
#endif
