
#ifndef CLOCK_H
#define CLOCK_H

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <time.h>
#include <iostream>
#include <math.h>

namespace NonStd {

    class Clock {

        typedef const unsigned int int_sig;
        typedef unsigned int unsign_int;

        private:

            unsign_int
                minutes, seconds, hour, radius,
                min_stick_length, sec_stick_length, hour_stick_length, circle_radius,
                min_stick_width, sec_stick_width, hour_stick_width;
            bool show;

            void _drawClock ();
            void __clockFrame ();
            void __hourStick ();
            void __minuteStick ();
            void __secondStick ();
            void __circle ();
            void __numberLine ();

            void drawText (

                const char * text,
                const GLint pos_x,
                const GLint pos_y,
                unsign_int size

            );

        public:

            Clock (

                int_sig radius = 10,
                int_sig min_stick_length = 5,
                int_sig sec_stick_length = 8,
                int_sig hour_stick_length = 9,
                int_sig circle_radius = 10,
                int_sig min_stick_width = 3,
                int_sig sec_stick_width = 2,
                int_sig hour_stick_width = 5

            );

            void clockToggle ();
            void setRadius ( int_sig radius );
            bool isClockShow () const;

            void setMinute ( int_sig minutes );
            void setSecond ( int_sig seconds );
            void setHour ( int_sig hour );

            void start ();

    };

}

#endif