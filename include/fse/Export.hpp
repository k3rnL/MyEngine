/**
 * @Date:   2018-02-05T02:28:23+01:00
 * @Last modified time: 2018-02-05T02:33:07+01:00
 */

#ifndef FSE_EXPORT_HPP
#define FSE_EXPORT_HPP

#if defined(_WIN32)
    #define FSE_API_EXPORT __declspec(dllexport)
#endif

#endif /* end of include guard: FSE_EXPORT_HPP */
