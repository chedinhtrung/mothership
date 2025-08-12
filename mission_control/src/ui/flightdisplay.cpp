#include "ui/flightdisplay.h"
#include <QScreen>
#include <QApplication>
#include <QOpenGLPaintDevice>

FlightDisplay::FlightDisplay(QWidget* parent) : QOpenGLWidget(parent){
    QScreen *screen = QApplication::primaryScreen();
    int screenHeight = screen->geometry().height();
    int screenWidth = screen->geometry().width();

    int width = static_cast<int>(screenHeight/2.5);
    int height = static_cast<int>(screenHeight/2.5);
    setFixedSize(QSize(width, height));
    //setAttribute(Qt::WA_AlwaysStackOnTop, true);

    // test function
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlightDisplay::onTestUpdate);
    timer->start(100);
    /* 
    roll = 30;
    pitch = 10;
    heading = 10;
    alt = 115.7;
    update();
    */
}

void FlightDisplay::onTestUpdate(){
    pitch += 0.2;
    roll += 0.5;
    heading += 1;
    alt += 0.4;
    airspeed += 0.4;
    update();
}

FlightDisplay::~FlightDisplay(){}

void FlightDisplay::initializeGL(){
    initializeOpenGLFunctions(); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void FlightDisplay::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void FlightDisplay::paintGL(){
    //qDebug() << "Repaint";
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0);
    draw_heading(heading);
    draw_pitch(pitch, roll);
    draw_viewpoint();
    draw_roll();
    draw_alt();
    draw_airspeed();
}

void FlightDisplay::draw_pitch(float pitch, float roll){
    for (int i=-36; i<=36; i++){
        if (abs(i*5 + pitch) > 15){continue;}   // Limit to current pitch +- 15
        float dev = abs(i + pitch/5);
        float alpha;
        if (dev <= 1){alpha = 1.0f;} 
        else {alpha = 0.1 + 1/dev;}
        if (i%2){
            draw_pitchmarker((pitch + i*5), roll, 0.2, QString::number(-i*5), alpha, i==0);
        } else {
            draw_pitchmarker((pitch + i*5), roll, 0.55, QString::number(-i*5), alpha, i==0);
        }
    }
}

void FlightDisplay::draw_pitchmarker(float pitch, float roll, 
                                    float len, QString text, float alpha, bool zero){
    float roll_rad = 3.14159*roll/180;
    float x1 = -len/2;
    float y1 = -pitch/40;
    float y2 = -pitch/40;
    float x2 = len/2;

    float x1t = x1 * cos(roll_rad) - y1 * sin(roll_rad);
    float y1t = x1 * sin(roll_rad) + y1 * cos(roll_rad);

    float x2t = x2 * cos(roll_rad) - y2 * sin(roll_rad);
    float y2t = x2 * sin(roll_rad) + y2 * cos(roll_rad);
    
    
    draw_text(text,x2t, y2t, roll_rad+M_PI/2, 15, 0, QColor(0, 204, 127, alpha*254));
    glLineWidth(3.0);
    if (zero){
        glColor4f(1.0f, 0.0f, 0.0f, alpha);
    } else {
        glColor4f(0.0f, 0.8f, 0.5f, alpha);
    }
    glBegin(GL_LINES);
        glVertex2f(x1t, y1t); 
        glVertex2f(x2t, y2t); 
    glEnd();
}

void FlightDisplay::draw_viewpoint(float len){
    glColor3f(1.0f, 0.0f, 0.0f); 
    glLineWidth(4.0);
    glBegin(GL_LINE_STRIP); 
        glVertex2f(-len/2, 0); 
        glVertex2f(-len/6, 0);
        glVertex2f(0, -len/6);
        glVertex2f(len/6, 0);
        glVertex2f(len/2, 0);
    glEnd();

    glPointSize(15.0f);
    glBegin(GL_POINTS);
        glVertex2f(0.0,0.0); 
    glEnd();
}

void FlightDisplay::draw_pitch(){
    draw_pitch(pitch, roll);
}

void FlightDisplay::draw_heading(){
    draw_heading(heading);
}

void FlightDisplay::draw_heading(float heading){
    float r = 0.6;
    draw_arc(0, -1.2, r, 0, M_PI, 50);
    draw_heading_markers(heading, r);
    draw_heading_arrow(r);
}

void FlightDisplay::draw_heading_arrow(float r){
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(0, -1.2);
        glVertex2f(0, -1.2+r);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(0, -1.2+r);
        glVertex2f(-r/14, -1.2 + r + r/9);
        glVertex2f(r/14, -1.2 + r + r/9);
    glEnd();
}

void draw_arc(float x, float y, float r, float start, float end, int n_seg){
    float total_angle = end - start;
    glBegin(GL_LINE_STRIP); 
    glColor3f(0.0f, 0.8f, 0.5f);
    for (int i=0; i<=n_seg; i++){
        float angle = i*total_angle/n_seg + start;
        glVertex2f((r*cos(angle) + x), (r*sin(angle) + y));
    }
    glEnd();
}

void FlightDisplay::draw_heading_markers(float heading, float r){
    float large_marker = 0.06;
    float small_marker = 0.1;
    float marker_len;

    glColor3f(0.0f, 0.8f, 0.5f);
    glLineWidth(3.0f);
    for (int i=-36; i<=36; i++){
        glColor3f(0.0f, 0.8f, 0.5f);
        float angle = (90 - i*5 + heading)*3.14159/180;
        // Markers
        glBegin(GL_LINES);
        if (i%2){marker_len = large_marker;}
        else {marker_len = small_marker;}
        float marker_lower_x = r*(1-marker_len)*cos(angle);
        float marker_lower_y = r*(1-marker_len)*sin(angle)-1.2;
        glVertex2f(r*cos(angle), r*sin(angle)-1.2);
        glVertex2f(marker_lower_x, marker_lower_y);
        glEnd();
        // Marker text
        if (abs(i*5) % 30 == 0){
            int num;
            if (i < 0){ num=i*5+360; } else { num=i*5; }
            QColor color = QColor(0, 204, 127, 255);
            QString txt = QString::number(static_cast<int>(num/10));
            if (i*5 == 0){txt="N"; color = QColor(255, 0, 0, 255);}
            if (i*5 == 90){txt="E"; color = QColor(255, 0, 0, 255);}
            if (i*5 == 180 || i*5 == -180){txt="S"; color = QColor(255, 0, 0, 255);}
            if (i*5 == -90){txt="W"; color = QColor(255, 0, 0, 255);}
            
            draw_text(txt, marker_lower_x, marker_lower_y, angle, 0, 8, color);
        }
    }
}


coord FlightDisplay::relative_to_pix(coord c){
    // convert x, y from [-1.0,1.0] coords used by OpenGL 
    // to x, y relative to top left of widget
    coord result;
    result.x = static_cast<int>((c.x + 1)*width()/2.0);
    result.y = static_cast<int>((-c.y + 1)*height()/2.0);
    return result;
}

void FlightDisplay::draw_text(QString txt, float x, float y, float r, 
                                float x_offset, float y_offset, QColor color){
    /*
    x, y, r in relative coords [-1, 1]. Offset in pixel
    */ 
   
    // convert to pixel coords
    // QOpenGLPaintDevice device = QOpenGLPaintDevice(size());
    QPainter painter(this);
    //int alp = static_cast<int>(254*alpha);
    painter.setPen(color);
    painter.setFont(QFont("Arial", 8));
    
    coord txt_c; 
    txt_c.x = x;
    txt_c.y = y;
    coord txt_pc = relative_to_pix(txt_c);
    // Get txt width and height
    QFontMetrics metrics(painter.font());
    int txt_w = metrics.horizontalAdvance(txt);
    int txt_h = metrics.height();
    // Translate to desired pos

    painter.translate(txt_pc.x, txt_pc.y);
    painter.rotate(-r*180/M_PI + 90);
    painter.drawText(QRect(-txt_w/2 + x_offset, -txt_h/2 + y_offset, txt_w, txt_h), Qt::AlignCenter, txt);
    painter.end();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FlightDisplay::draw_roll(){
    draw_roll(roll);
}

void FlightDisplay::draw_roll(float roll, float r, float start, float end, int n_seg){
    // The arc
    float total_angle = end - start;
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP); 
    glColor3f(0.0f, 0.8f, 0.5f);
    for (int i=0; i<=n_seg; i++){
        float angle = i*total_angle/n_seg + start;
        glVertex2f(r*cos(angle), r*sin(angle));
    }
    glEnd();

    glPointSize(12.0f);
    glBegin(GL_POINTS);

    // The marker
    for (int j=0; j<=6; j++){
        float angle = start + j*M_PI*15.0/180.0;
        float mark_x = r*cos(angle);
        float mark_y = r*sin(angle);
        glVertex2f(mark_x, mark_y);
    }
    glEnd();

    // Marker text
    for (int j=0; j<=6; j++){
        float angle = start + j*M_PI*15.0/180.0;
        float mark_x = r*cos(angle);
        float mark_y = r*sin(angle);
        draw_text(QString::number(abs(j-3)*15), mark_x, mark_y, angle, 0.0f, -10.0f);
    }

    // the Roll
    float roll_rad = M_PI*roll/180 + M_PI/2;
    float cos_roll = cos(roll_rad);
    float sin_roll = sin(roll_rad);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(r*cos_roll, r*sin_roll); 
        glVertex2f(
            (r-0.05)*cos_roll - 0.025*sin_roll,
            (r-0.05)*sin_roll + 0.025*cos_roll
        );
        glVertex2f(
            (r-0.05)*cos_roll + 0.025*sin_roll,
            (r-0.05)*sin_roll - 0.025*cos_roll
        );
    glEnd();

}

void FlightDisplay::draw_alt(){
    draw_alt(alt);
}

void FlightDisplay::draw_alt(float alt){
    draw_indicator_alt(0.52);
    draw_ruler_alt(alt);
}

float get_circular_offset(float x, int step){
    return x - static_cast<int>(x/step)*step;
}

void FlightDisplay::draw_ruler_alt(float alt, float x, float y, float h, int range, int step_s, int step_m, int step_l){
    glColor3f(0.0f, 0.8f, 0.5f);
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glVertex2f(x, -h/2+y);
        glVertex2f(x, h/2+y);
    glEnd();

    float offset = get_circular_offset(alt, step_l);

    float steplen = h*step_s/range;
    glLineWidth(1.0);

    float len_marker_base = 0.03;
    
    for (int i=-range/2/step_s-step_l; i<=range/2/step_s+step_l; i++){
        glColor3f(0.0f, 0.8f, 0.5f);
        float len_marker = len_marker_base;
        float coord_y = (i-offset/step_s)*steplen;
        if (coord_y < -h/2 || coord_y > h/2){continue;}
        
        if (i*step_s%step_l == 0){
            len_marker*=2.9;
            int mark_num = static_cast<int>(alt/step_l)*step_l + i*step_s;
            draw_text(QString::number(mark_num), x+len_marker, coord_y, M_PI/2, 12);
        } 
        else if (i*step_s%step_m == 0){len_marker*=1.7;}
        glColor3f(0.0f, 0.8f, 0.5f);
        glBegin(GL_LINES);
        glVertex2f(x, coord_y);
        glVertex2f(x+len_marker, coord_y);
        glEnd();
    }

    draw_text(QString::number(static_cast<int>(alt)), x+len_marker_base*2.9, y, M_PI/2, 12);
}

void FlightDisplay::draw_indicator_alt(float x, float w, float h){
    glColor4f(0.8, 0.0, 0.0, 0.5);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, 0.0f);
        glVertex2f(x+w/3, h/2);
        glVertex2f(x+w, h/2);
        glVertex2f(x+w, -h/2);
        glVertex2f(x+w/3, -h/2);
    glEnd();
    glColor4f(0.0, 0.8, 0.5, 1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, 0.0f);
        glVertex2f(x+w/3, h/2);
        glVertex2f(x+w, h/2);
        glVertex2f(x+w, -h/2);
        glVertex2f(x+w/3, -h/2);
    glEnd();
}

void FlightDisplay::draw_indicator_airspeed(float x, float w, float h){
    glColor4f(0.8, 0.0, 0.0, 0.5);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, 0.0f);
        glVertex2f(x-w/3, h/2);
        glVertex2f(x-w, h/2);
        glVertex2f(x-w, -h/2);
        glVertex2f(x-w/3, -h/2);
    glEnd();
    glColor4f(0.0, 0.8, 0.5, 1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, 0.0f);
        glVertex2f(x-w/3, h/2);
        glVertex2f(x-w, h/2);
        glVertex2f(x-w, -h/2);
        glVertex2f(x-w/3, -h/2);
    glEnd();
}

void FlightDisplay::draw_ruler_airspeed(float airspeed, float x, float y, float h, int range, int step_s, int step_l){
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glVertex2f(x, -h/2+y);
        glVertex2f(x, h/2+y);
    glEnd();

    float offset = get_circular_offset(airspeed, step_l);

    float steplen = h*step_s/range;
    glLineWidth(1.0);

    float len_marker_base = 0.03;
    
    for (int i=-range/2/step_s-step_l; i<=range/2/step_s+step_l; i++){
        glColor3f(0.0f, 0.8f, 0.5f);
        float len_marker = len_marker_base;
        float coord_y = (i-offset/step_s)*steplen;
        if (coord_y < -h/2 || coord_y > h/2){continue;}
        
        if (i*step_s%step_l == 0){
            len_marker*=2.2;
            int mark_num = static_cast<int>(airspeed/step_l)*step_l + i*step_s;
            draw_text(QString::number(mark_num), x-len_marker, coord_y, M_PI/2, -12);
        } 
        glColor3f(0.0f, 0.8f, 0.5f);
        glBegin(GL_LINES);
        glVertex2f(x, coord_y);
        glVertex2f(x-len_marker, coord_y);
        glEnd();
    }
    draw_text(QString::number(static_cast<int>(airspeed)), x-len_marker_base*2.2,y, M_PI/2, -12);
}

void FlightDisplay::draw_airspeed(){
    draw_airspeed(airspeed);
}

void FlightDisplay::draw_airspeed(float airspeed){
    draw_indicator_airspeed();
    draw_ruler_airspeed(airspeed);
}

