
#include "Clock.h"

bool NonStd::Clock::isClockShow () const {

    return this -> show;

};

NonStd::Clock::Clock (

    int_sig radius,
    int_sig min_stick_length,
    int_sig sec_stick_length,
    int_sig hour_stick_length,
    int_sig circle_radius,
    int_sig min_stick_width,
    int_sig sec_stick_width,
    int_sig hour_stick_width

) : radius ( radius ),
    min_stick_length ( min_stick_length ),
    sec_stick_length ( sec_stick_length ),
    hour_stick_length ( hour_stick_length ),
    circle_radius ( circle_radius ),
    min_stick_width ( min_stick_width ),
    sec_stick_width ( sec_stick_width ),
    hour_stick_width ( hour_stick_width ),
    show ( false ),
    date_show ( true ) {};

void NonStd::Clock::clockToggle () {

    this -> show = !this -> show;

};

void NonStd::Clock::drawText (
    
    const char * text,
    const GLint pos_x,
    const GLint pos_y,
    unsign_int size
    
) {

    glRasterPos2i ( pos_x, pos_y );
    unsigned int index = 0;

    for ( ; index < size; ++ index ) {

        glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_18, text[ index ] );

    }

};

void NonStd::Clock::__clockFrame () {

    unsign_int angle = 0;
    unsign_int & r = this -> radius;
    const double to_rad = 3.14 / 180;

    glBegin ( GL_TRIANGLE_FAN );

        glColor3d ( 1.0, 1.0, 1.0 );

        for ( ; angle < 360; ++ angle ) {

            glVertex2d ( r * cos ( angle * to_rad ), r * sin ( angle * to_rad ) );

        }

    glEnd ();

};

void NonStd::Clock::__hourStick () {

    unsigned int & h = this -> hour;
    const double to_rad = 3.14 / 180;

    glLineWidth ( this -> hour_stick_width );

    glBegin ( GL_LINES );

        glColor3d ( .0, .0, 1.0 );

        glVertex2d ( 0, 0 );
        glVertex2d ( this -> hour_stick_length * sin ( h * to_rad ), this -> hour_stick_length * cos ( h * to_rad ) );

    glEnd ();

};

void NonStd::Clock::__minuteStick () {

    unsigned int & min = this -> minutes;
    const double to_rad = 3.14 / 180;

    glLineWidth ( this -> min_stick_width );

    glBegin ( GL_LINES );

        glColor3d ( 1.0, .0, .0 );

        glVertex2d ( 0, 0 );
        glVertex2d ( this -> min_stick_length * sin ( min * to_rad ), this -> min_stick_length * cos ( min * to_rad ) );

    glEnd ();

};

void NonStd::Clock::__secondStick () {

    unsigned int & s = this -> seconds;
    const double to_rad = 3.14 / 180;

    glLineWidth ( this -> sec_stick_width );

    glBegin ( GL_LINES );

        glColor3d ( .0, 1.0, .0 );

        glVertex2d ( 0, 0 );
        glVertex2d ( this -> sec_stick_length * sin ( s * to_rad ), this -> sec_stick_length * cos ( s * to_rad ) );

    glEnd ();

};

void NonStd::Clock::__circle () {

    unsigned int angle = 0;
    unsigned int & r = this -> circle_radius;
    const double to_rad = 3.14 / 180;

    glBegin ( GL_TRIANGLE_FAN );

        glColor3d ( .2, .3, .2 );

        for ( ; angle < 360; ++ angle ) {

            glVertex2d ( r * cos ( angle * to_rad ), r * sin ( angle * to_rad ) );

        }

    glEnd ();

};

void NonStd::Clock::__numberLine () {

    unsigned int angle = 0, number_distance = 360 / 12, time_number = 0;
    unsigned int & r = this -> radius, & stick_length = this -> min_stick_length;

    double length = ( r - stick_length ) * .5, calculation = .0;
    const double to_rad = 3.14 / 180;

    unsigned int label = 1;

    for ( ; angle < 360; angle += number_distance ) {

        calculation =  angle * to_rad;

        glBegin ( GL_LINES );

            glColor3d ( .0, .0, .0 );

            glVertex2d ( ( r - 30 ) * sin ( calculation ), ( r - 30 ) * cos ( calculation ) );
            glVertex2d ( ( stick_length - 20 ) * sin ( calculation ), ( stick_length - 20 ) * cos ( calculation ) );

        glEnd ();

        if ( angle % 30 == 0 ) {

            angle / 30 == 0 ?
                this -> drawText ( "12", stick_length * sin ( calculation ), ( stick_length - 50 ) * cos ( calculation ), 2 )
                :
                this -> drawText ( std::to_string( angle / 30 ).c_str (), ( stick_length - 20 ) * sin ( calculation ), ( stick_length - 50 ) * cos ( calculation ), 2 );

        }

    }

    number_distance = 360 / 60;
    angle = 0;

    for ( ; angle < 360; angle += number_distance ) {

        glBegin ( GL_LINES );

            glColor3d ( .0, .0, .0 );

            glVertex2d ( ( r - 30 ) * sin ( angle * to_rad ), ( r - 30 ) * cos ( angle * to_rad ) );
            glVertex2d ( ( length + stick_length ) * sin ( angle * to_rad ), ( length + stick_length ) * cos ( angle * to_rad ) );

        glEnd ();

    }

    std::time_t current_time = time ( NULL );
    struct std::tm * time_struct = std::localtime ( &current_time );

    // this text drawing is not generic

    if ( this -> date_show )
        this -> drawText ( asctime ( time_struct ), -190, r - 380, sizeof ( asctime ( time_struct ) ) * 3 );

};

void NonStd::Clock::_drawClock () {

    // draw clock frame
    this -> __clockFrame ();

    // draw sticks
    this -> __hourStick ();
    this -> __minuteStick ();
    this -> __secondStick ();
    this -> __circle ();

    // labels
    this -> __numberLine ();

};

void NonStd::Clock::start () {

    if ( this -> show ) this -> _drawClock ();

};

void NonStd::Clock::setRadius ( int_sig radius ) {

    this -> radius = radius;

};

void NonStd::Clock::setSecond ( int_sig second ) {

    this -> seconds = 6 * second;

};

void NonStd::Clock::setMinute ( int_sig minute ) {

    this -> minutes = 6 * minute;

};

void NonStd::Clock::setHour ( int_sig hour ) {

    this -> hour = 30 * hour;

};

void NonStd::Clock::dateToggle () {

    this -> date_show = !this -> date_show;

};

bool NonStd::Clock::isDateShow () const {

    return this -> date_show;

}