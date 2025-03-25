#ifndef MAPVIEW
#include <QWebEngineView>

class MapView : public QWebEngineView {
    Q_OBJECT
    public:
    MapView(QWidget* parent=nullptr);
    ~MapView();
};

#endif