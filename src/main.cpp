
#include "Clock.h"

// global vars

NonStd::Clock analogClock ( 600, 480, 560, 520, 60 );

void render ();
void timer ( int val );

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