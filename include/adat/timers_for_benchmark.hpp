#pragma once
#include <chrono>
#include <atomic>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


namespace tfb
{

// =====+=====+=====+=====+  miscellaneous =====+=====+=====+=====+
inline std::string format_time(const std::chrono::milliseconds& time,
                               const bool justify = false);

struct Timer_result{
    std::string name {""};
    std::chrono::milliseconds elapsed_time {0};
    int percentage {-1};

    std::string get_formatted_elapse(const bool justify = false)
    {return tfb::format_time(elapsed_time, justify);}
};

// =====+=====+=====+=====+ Timer class =====+=====+=====+=====+
class Timer {
public:

    using clock_t = std::chrono::high_resolution_clock;
    using milli_sec = std::chrono::milliseconds;

    friend class Multi_timer;
public:
    inline Timer(const std::string clock_name = "", const bool start_now = true):
        m_start_time(clock_t::now()),
        m_clock_name(clock_name),
        m_is_ticking(start_now)
    {}

    inline void start();

    inline void pause();

    inline std::string get_clock_name() const;

    inline std::chrono::milliseconds get_elapsed_time() const;

    inline std::string get_elapsed_time_as_string() const;

    inline Timer_result get_timer_result() const;

    inline std::string get_formated_elapsed_time() const;


private:
    clock_t::time_point m_start_time;
    std::string m_clock_name {""};
    bool m_is_ticking {false};
    long m_elapsed_time {0};


};


// =====+=====+=====+=====+ Multi_timer class =====+=====+=====+=====+

class Multi_timer{
public:
    inline Multi_timer();


    inline void activate_timer(const std::string timer_name);


    inline std::vector<std::string> get_clocks_names() const;

    inline void pause_current_timer();

    inline std::vector<Timer_result> get_timers_elapsed_time() const;

    inline std::string get_timers_formatted_elapsed_time() const;

private:
    int m_current_clock_idx {-1};
    std::vector<Timer> m_clocks;

private:
    inline std::string center(const std::string& str, size_t& length) const;
    inline std::string rjust(const std::string& str, size_t& length) const;
    inline std::string ljust(const std::string& str, size_t& length) const;


};



// =====+=====+=====+=====+ Multi_timer_singleton class =====+=====+=====+=====+
template<class Dummy>
class Multi_timer_singleton
{
protected:
    inline Multi_timer_singleton()
    { }

     static Multi_timer* m_multi_timer;
public:
    inline Multi_timer_singleton(Multi_timer_singleton &other) = delete;

    inline void operator=(const Multi_timer_singleton &) = delete;

    inline static Multi_timer *get_instance()
    {
        if(m_multi_timer == nullptr){
            m_multi_timer = new tfb::Multi_timer();
        }
        return m_multi_timer;
    }

};

}
template<class Dummy>
tfb::Multi_timer* tfb::Multi_timer_singleton<Dummy>::m_multi_timer = nullptr;

using Multi_timer_singleton = tfb::Multi_timer_singleton<void>;
// =====+=====+=====+=====+  =====+=====+  =====+=====+=====+=====+
// =====+=====+=====+=====+   Timer Impl   =====+=====+=====+=====+
// =====+=====+=====+=====+  =====+=====+  =====+=====+=====+=====+

void tfb::Timer::start()
{
    if(m_is_ticking)
        return;
    m_start_time = clock_t::now();
    m_is_ticking = true;
}

void tfb::Timer::pause()
{
    if(!m_is_ticking)
        return;

    std::atomic_thread_fence(std::memory_order_relaxed);
    auto counted_time = std::chrono::duration_cast<milli_sec>(clock_t::now() - m_start_time).count();

    m_elapsed_time += counted_time;
    m_is_ticking = false;
}

std::string tfb::Timer::get_clock_name() const
{
    return m_clock_name;
}


std::chrono::milliseconds tfb::Timer::get_elapsed_time() const
{
    std::atomic_thread_fence(std::memory_order_relaxed);
    auto counted_time = std::chrono::duration_cast<milli_sec>(clock_t::now() - m_start_time).count();

    if(!m_is_ticking){
        std::atomic_thread_fence(std::memory_order_relaxed);
        return static_cast<std::chrono::milliseconds>(m_elapsed_time);
    }
    std::atomic_thread_fence(std::memory_order_relaxed);
    return static_cast<std::chrono::milliseconds>(counted_time + m_elapsed_time);
}

std::string tfb::Timer::get_elapsed_time_as_string() const{
    return tfb::format_time(this->get_elapsed_time());
}


tfb::Timer_result tfb::Timer::get_timer_result() const
{
    Timer_result result;
    result.elapsed_time = this->get_elapsed_time();
    result.name = m_clock_name;
    result.percentage = -1;
    return result;
}

std::string tfb::Timer::get_formated_elapsed_time() const
{
    return "*** Run time for " + m_clock_name + ": " + this->get_elapsed_time_as_string();
}

// =====+=====+=====+=====+  =====+=====+  =====+=====+=====+=====+
// =====+=====+=====+=====+   Multi_timer  =====+=====+=====+=====+
// =====+=====+=====+=====+  =====+=====+  =====+=====+=====+=====+

tfb::Multi_timer::Multi_timer()
{
    m_clocks.reserve(20);
}



void tfb::Multi_timer::activate_timer(const std::string timer_name)

{
    if(m_current_clock_idx >= 0)
        m_clocks.at(m_current_clock_idx).pause();
    size_t i;
    for(i = 0; i < m_clocks.size(); i++){
        if(m_clocks[i].m_clock_name == timer_name){
            m_clocks.at(i).start();
            m_current_clock_idx = static_cast<int>(i);
            return;
        }
    }
    tfb::Timer stopwatch(timer_name, true);
    m_clocks.push_back(stopwatch);
    m_current_clock_idx = static_cast<int>(i);
//    m_clocks.at(m_current_clock_idx).start();
    return;
}

std::vector<std::string> tfb::Multi_timer::get_clocks_names() const
{
    std::vector<std::string> clocks_names;
    for(auto& clock: m_clocks)
        clocks_names.push_back(clock.m_clock_name);
    return clocks_names;
}

void tfb::Multi_timer::pause_current_timer()
{
    if(m_current_clock_idx >= 0)
        m_clocks.at(m_current_clock_idx).pause();
    m_current_clock_idx = -1;
}


std::vector<tfb::Timer_result>
tfb::Multi_timer::get_timers_elapsed_time() const
{
    std::vector<Timer_result> results;

    std::chrono::milliseconds total {0};
    for(auto& clock: m_clocks){
        Timer_result result;
        result.elapsed_time = clock.get_elapsed_time();
        total += result.elapsed_time;
        results.push_back(result);
    }
    for(size_t i = 0; i < results.size(); i++){
        results.at(i).name = m_clocks.at(i).get_clock_name();
        results.at(i).percentage = static_cast<int>(
                    results.at(i).elapsed_time.count()  * 100 / total.count());
    }

    return results;

}

#include <iostream>
std::string tfb::Multi_timer::get_timers_formatted_elapsed_time() const
{
    std::vector<Timer_result> results = this->get_timers_elapsed_time();
    std::string message = "";
    size_t print_name_s = 10;
    size_t print_time_s = 30;
    size_t print_percent_s = 12;
    std::chrono::milliseconds total{0};
    for(auto& r :results){
        std::string t = r.get_formatted_elapse(true);
        print_name_s = print_name_s < r.name.size() + 2 ? r.name.size() + 2: print_name_s;
        print_time_s = print_time_s < t.size() + 2 ? t.size() + 2: print_time_s;
        total += r.elapsed_time;
    }

    std::string seperator;

    seperator += "#" + std::string(print_name_s, '-');
    seperator += "#" + std::string(print_time_s, '-');
    seperator += "#" + std::string(print_percent_s, '-') + "#\n";

    message += seperator;

    message += "|" + this->center("Clock name", print_name_s);
    message += "|" + this->center("Run time", print_time_s);
    message += "|" + this->center("Percentage", print_percent_s) + "|\n";

    message += seperator;


    for(auto& r :results){
        message += "|" + this->ljust(" " + r.name, print_name_s);
        message += "|" + this->rjust(r.get_formatted_elapse(true) + " ", print_time_s);
        message += "|" + this->rjust(std::to_string(r.percentage) + "% ", print_percent_s) + "|\n";

    }

    message += seperator;

    message += "|" + this->center("Total", print_name_s);
    message += "|" + this->rjust(tfb::format_time(total, true) + " ", print_time_s);
    message += "|" + this->rjust("100% ", print_percent_s) + "|\n";

    message += seperator;


    return message;
}


std::string tfb::Multi_timer::center(const std::string& str, size_t& length) const
{
    if(length <= str.size())
        return str;
    std::string space = std::string((length - str.size()) / 2, ' ');
    std::string result = space + str + space;
    return result.size() < length ? result + " ": result;
}

std::string tfb::Multi_timer::rjust(const std::string& str, size_t& length) const
{
    size_t str_size = str.size();
    if(str_size > length)
        return str;
    return std::string( length - str_size, ' ' ) + str;
}

std::string tfb::Multi_timer::ljust(const std::string& str, size_t& length) const
{
    size_t str_size = str.size();
    if(str_size > static_cast<size_t>(length))
        return str;
    return str + std::string( length - str_size, ' ' );
}

std::string tfb::format_time(const std::chrono::milliseconds& time,
                             const bool justify)
{
    auto milli(time.count());

    int normal_fill = justify ? 2: 0;
    int milli_sec_fill = justify ? 3: 0;

    std::ostringstream oss;
    oss << std::setfill(' ')
        << std::setw(normal_fill) << (milli % 216000000) / 3600000 << "h "
        << std::setw(normal_fill) << (milli % 3600000) / 60000 << "m "
        << std::setw(normal_fill) << (milli % 60000) / 1000 << "s "
        << std::setw(milli_sec_fill) << milli % 1000 << "ms";


    return oss.str();
}

