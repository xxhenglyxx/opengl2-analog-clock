
#include "Clock.h"

// global vars

NonStd::Clock analogClock ( 600, 480, 560, 520, 60 );

void render ();
void timer ( int val );
void windowOnChange ( int width, int height );
void initMenu ();

void dateShown ( int val );
void hourStickColor ( int val );
void minStickColor ( int val );
void secStickColor ( int val );

int main ( int args_len, char ** args_context ) {

    glutInit ( &args_len, args_context );
    glutInitDisplayMode ( GLUT_SINGLE );
    glutInitWindowSize ( 800, 800 );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow ( "Analog Clock" );

    glClearColor ( .2, .3, .5, .8 );
    glClear ( GL_COLOR_BUFFER_BIT );
    glLoadIdentity ();
    gluOrtho2D ( -800, 800, -800, 800 );

    // toggle to show clock
    analogClock.clockToggle ();

    std::time_t current_time = time ( NULL );
    struct std::tm * time_struct = std::localtime ( &current_time );

    analogClock.setSecond ( time_struct -> tm_sec );
    analogClock.setMinute ( time_struct -> tm_min );
    analogClock.setHour ( time_struct -> tm_hour );

    glutDisplayFunc ( render );
    // glutReshapeFunc ( windowOnChange );

    initMenu ();

    glutTimerFunc ( 1000, timer, NULL );

    glutMainLoop ();

    return 0;

};

void render () {

    analogClock.start ();

    glFlush ();

};

void timer ( int val ) {

    std::time_t current_time = time ( NULL );
    struct std::tm * time_struct = std::localtime ( &current_time );

    analogClock.setSecond ( time_struct -> tm_sec );
    analogClock.setMinute ( time_struct -> tm_min );
    analogClock.setHour ( time_struct -> tm_hour );

    glutTimerFunc ( 1000, timer, NULL );

    glutPostRedisplay ();

};

void dateShown ( int val ) {

    switch ( val ) {

        case 0: {

            if ( !analogClock.isDateShow () )
                analogClock.dateToggle ();
            
            break;

        }

        case 1: {

            if ( analogClock.isDateShow () )
                analogClock.dateToggle ();

            break;

        }

    }

    glutPostRedisplay ();

};

void hourStickColor ( int val ) {

};

void minStickColor ( int val ) {

};

void secStickColor ( int val ) {

};

void mainMenu ( int val ) {

}

void initMenu () {

    int date_show_menu = glutCreateMenu ( dateShown );

    glutAddMenuEntry ( "On", 0 );
    glutAddMenuEntry ( "Off", 1 );

    int h_stick_color_menu = glutCreateMenu ( hourStickColor );

    glutAddMenuEntry ( "Red", 0 );
    glutAddMenuEntry ( "Green", 1 );

    int m_stick_color_menu = glutCreateMenu ( minStickColor );

    glutAddMenuEntry ( "Black", 0 );
    glutAddMenuEntry ( "Yellow", 1 );

    int s_stick_color_menu = glutCreateMenu ( secStickColor );

    glutAddMenuEntry ( "Purple", 0 );
    glutAddMenuEntry ( "Brown", 1 );

    int main_menu = glutCreateMenu ( mainMenu );

    glutAddSubMenu ( "Date", date_show_menu );
    glutAddSubMenu ( "Hour Stick Color", h_stick_color_menu );
    glutAddSubMenu ( "Minute Stick Color", m_stick_color_menu );
    glutAddSubMenu ( "Second Stick Color", s_stick_color_menu );

    glutAttachMenu ( GLUT_RIGHT_BUTTON );

};