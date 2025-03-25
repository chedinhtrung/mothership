#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QPainter>

#ifndef FLIGHTDISP
#define FLIGHTDISP

struct coord {
    float x;
    float y;
};

void draw_arc(float x, float y, float r, float start, float end, int n_seg=100);

struct opengl_color {
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
};

class FlightDisplay : public QOpenGLWidget, protected QOpenGLFunctions{
    Q_OBJECT

    public:
    FlightDisplay(QWidget* parent=nullptr);
    ~FlightDisplay();

    float roll = 7.0;
    float pitch = 0;
    float heading = 0;
    float bat = 0;
    float vspeed = 0;
    float airspeed = 0;
    float alt = 0;

    protected:

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void draw_pitch(float pitch, float roll);
    void draw_pitch();
    void draw_pitchmarker(float pitch, float roll, float len=0.5, QString text="", float alpha=1.0, bool zero=0);

    void draw_heading(float heading);
    void draw_heading();
    void draw_heading_markers(float heading, float r=0.5);
    void draw_heading_arrow(float r=0.5);

    void draw_viewpoint(float len=0.8);
    void draw_text(QString txt, float x, float y, float r, 
                    float x_offset=0, float y_offset=0, QColor color=QColor(0, 204, 127, 255));

    void draw_roll(float roll, float r=0.85, float start=M_PI/4, float end=3*M_PI/4, int n_seg=50);
    void draw_roll();

    void draw_alt(float alt);
    void draw_alt();
    void draw_ruler_alt(float alt, float x=0.5, float y=0, float h=1, int range=40, int step_s=1, int step_m=5, int step_l=10);
    void draw_indicator_alt(float x=0.5, float w=0.21, float h=0.12);

    void draw_vspeed(float vspeed);
    void draw_vspeed();
    void draw_ruler_vspeed(float x, float y, float h);

    void draw_airspeed(float airspeed);
    void draw_airspeed();
    void draw_ruler_airspeed(float alt, float x=-0.6, float y=0, float h=1, int range=64, int step_s=4, int step_l=8);
    void draw_indicator_airspeed(float x=-0.63, float w=0.21, float h=0.12);

    void draw_textbox(QString txt, float x, float y, float w, float h);


    coord relative_to_pix(coord c);
    


    private slots:
        void onTestUpdate(); // Test funct
    
};

#endif 