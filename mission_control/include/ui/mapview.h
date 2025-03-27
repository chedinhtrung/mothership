
#include <QWebEngineView>

#ifndef MAPVIEW
#define MAPVIEW

class MapView : public QWebEngineView {
    Q_OBJECT
    public:
    MapView(QWidget* parent=nullptr, QString map_api_key="");
    ~MapView();
    QString loadHtml(QString map_api_key="");
};

#endif