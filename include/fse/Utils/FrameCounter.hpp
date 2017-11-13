/**
 * @Author: daniel_b
 * @Date:   2017-07-30T23:16:53+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-05T01:22:39+02:00
 */



#ifndef FRAME_COUNTER_HPP
#define FRAME_COUNTER_HPP

#include <sys/time.h>

#include <iostream>

namespace fse {
    namespace utils {

        class FrameCounter
        {
        public:
            FrameCounter() { gettimeofday(&_last_time, 0); }

            void    update() {
                struct timeval  current;

                _fps_count++;
                gettimeofday(&current, 0);
                timersub(&current, &_last_time, &current);
                if (current.tv_sec > 0)
                {
                    _fps = _fps_count;
                    _fps_count = 0;

                    gettimeofday(&_last_time, 0);
                }
            }

            const unsigned int    &getFrameRate() const { return (_fps); }

        private:
            unsigned int    _fps = 60;
            unsigned int    _fps_count = 0;
            struct timeval  _last_time;

        };

    }
}

#endif
