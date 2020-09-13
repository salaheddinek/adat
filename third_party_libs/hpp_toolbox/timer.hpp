#pragma once
#include <chrono>
#include <atomic>
#include <string>

namespace hpp_toolbox
{
template <typename Clock = std::chrono::high_resolution_clock>
class stopwatch
{
    const typename Clock::time_point start_point;
    std::string m_clock_name {""};
public:
    stopwatch(const std::string clock_name = "") :
        start_point(Clock::now()),
        m_clock_name(clock_name)
    {}

    // use examplee: stopwatch.elapsed_time<unsigned int, std::chrono::microseconds>()
    template <typename Rep = typename Clock::duration::rep, typename Units = typename Clock::duration>
    Rep elapsed_time() const
    {
        std::atomic_thread_fence(std::memory_order_relaxed);
        auto counted_time = std::chrono::duration_cast<Units>(Clock::now() - start_point).count();
        std::atomic_thread_fence(std::memory_order_relaxed);
        return static_cast<Rep>(counted_time);
    }

    std::string get_simple_time() const{
        unsigned long milli = this->elapsed_time<unsigned long, std::chrono::milliseconds>();

        unsigned long hr = milli / 3600000;
        milli = milli - 3600000 * hr;

        unsigned long min = milli / 60000;
        milli = milli - 60000 * min;

        unsigned long sec = milli / 1000;
        milli = milli - 1000 * sec;

        return   std::to_string(hr) + "h "
                + std::to_string(min) + "m "
                + std::to_string(sec) + "s "
                + std::to_string(milli) + "ms";
    }

    std::string get_formated_time() const
    {
        return "*** Run time for " + m_clock_name + ": " + this->get_simple_time();
    }
};

using precise_stopwatch = stopwatch<>;
using system_stopwatch = stopwatch<std::chrono::system_clock>;
using monotonic_stopwatch = stopwatch<std::chrono::steady_clock>;

}
