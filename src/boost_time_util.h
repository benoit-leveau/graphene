
#ifndef BOOST_TIME_UTIL_H
#define BOOST_TIME_UTIL_H

#include <boost/thread/condition_variable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

inline boost::xtime delay(int secs, int msecs=0, int nsecs=0)
{
    const int MILLISECONDS_PER_SECOND = 1000;
    const int NANOSECONDS_PER_SECOND = 1000000000;
    const int NANOSECONDS_PER_MILLISECOND = 1000000;
    boost::xtime xt;
    nsecs += xt.nsec;
    msecs += nsecs / NANOSECONDS_PER_MILLISECOND;
    secs += msecs / MILLISECONDS_PER_SECOND;
    nsecs += (msecs % MILLISECONDS_PER_SECOND) * NANOSECONDS_PER_MILLISECOND;
    xt.nsec = nsecs % NANOSECONDS_PER_SECOND;
    xt.sec += secs + (nsecs / NANOSECONDS_PER_SECOND);
    return xt;
} 

#endif //!BOOST_TIME_UTIL_H
