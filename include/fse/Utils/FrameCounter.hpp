/**
 * @Author: daniel_b
 * @Date:   2017-07-30T23:16:53+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-09-05T01:22:39+02:00
 */



#ifndef FRAME_COUNTER_HPP
#define FRAME_COUNTER_HPP

#include <chrono>

#include <iostream>

namespace fse {
    namespace utils {

        class FrameCounter
        {
        public:
            FrameCounter() { 
				timer = std::chrono::steady_clock::now();
			}

            void    update() {
				fps = std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 60>>>(std::chrono::steady_clock::now() - timer);
				if (fps.count() >= 1)
				{
					timer = std::chrono::steady_clock::now();
					//std::cout << std::chrono::duration_cast<duration<float, std::chrono::milli>(fps).count() << "ms FPS: " << fps.count() * 60 << endl;
				}
            }

            const unsigned int    getFrameRate() const { return (fps.count() * 60); }

        private:
			std::chrono::time_point<std::chrono::steady_clock>		timer;
			std::chrono::duration<int32_t, std::ratio<1, 60>>		fps;
        };

    }
}

#endif
