#include <iostream>
#include <vector>
#include <string>


namespace scs {

inline std::vector<size_t> indices(const size_t start,
                                   const int step,
                                   const size_t end,
                                   const bool end_defined = false)
{
    std::vector<size_t> indices;
    if(step == 0 || start == end)
        return indices;
    if(start < end && step < 0)
        return indices;
    if(start > end && step > 0)
        return indices;
    size_t i = start;
    int sign = step < 0? -1: 1;
    while(sign * static_cast<int>(i)  < sign * static_cast<int>(end) + !end_defined ){
        indices.push_back(i);
        i += step;
    }

    return indices;
}

struct Index_info {
    int start {0};
    int step {1};
    int end {-1};
    bool end_defined {false};
    bool start_defined {false};
};

struct End {
    inline End(int in){
        info.end = in;
        info.end_defined = true;
    }

    inline End operator-(){
        info.end = - info.end;
        return *this;
    }
    inline Index_info get_info() const{return info;}

protected:
    Index_info info;

    End();
};

struct Step{
    inline Step(int in){
        info.step = in;
    }

    inline Step operator&(End e){
        auto old_info = e.get_info();
        info.end = old_info.end;
        info.end_defined = old_info.end_defined;
        return *this;
    }

    inline Step operator-(){
        info.step = -info.step;
        return *this;
    }
    inline Index_info get_info() const{return info;}

protected:
    Index_info info;

    Step();
};

struct Start {
    inline Start(int idx){
        info.start = idx;
        info.start_defined = true;
    }

    inline Start operator&(End e){
        auto old_info = e.get_info();
        info.end = old_info.end;
        info.end_defined = old_info.end;
        return *this;
    }

    inline Start operator&(Step s){
        auto old_info = s.get_info();
        info.step = old_info.step;
        if(old_info.end_defined){
            info.end = old_info.end;
            info.end_defined = old_info.end_defined;
        }
        return *this;
    }

    inline Start operator-(){
        info.start = -info.start;
        return *this;
    }
    inline Index_info get_info() const{return info;}

protected:
    Index_info info;

    Start();
};

template<class T>
class slice {
public:
    slice(T& v){m_container = v;}

    T operator[](Start in){
        m_info = in.get_info();
        return get();
    }
    T operator[](Step in){
        m_info = in.get_info();
        return get();
    }

    T operator[](End in){
        m_info = in.get_info();
        return get();
    }

    template <typename R>
    R operator[](int in){
        return static_cast<R>(m_container.at(idx_from_int(in)));
    }

    T get()
    {
        m_info.step = m_info.step == 0 ? 1: m_info.step;
        int size = static_cast<int>(m_container.size());
        if(!m_info.end_defined)
            m_info.end = m_info.step > 0 ? size - 1: 0;

        if(!m_info.start_defined)
            m_info.start = m_info.step > 0 ? 0: size - 1;

        std::vector<size_t> indices = scs::indices(idx_from_int(m_info.start), m_info.step,
                                                      idx_from_int(m_info.end), m_info.end_defined);
        T result;
        for(auto idx : indices)
            result.push_back(m_container.at(idx));

//        print_indices_for_debug();
        return result;
    }

    slice<T> start(int in)
    {
        m_info.start = in; m_info.start_defined = true; return *this;
    }
    slice<T> end(int in)
    {
        m_info.end = in; m_info.end_defined = true; return *this;
    }
    slice<T> step(int in)
    {
        m_info.step = in; return *this;
    }

private:
    inline void print_indices_for_debug() {

        std::cout << "start=" << m_info.start << ", step=" << m_info.step << ", end=" << m_info.end << "\n";

        std::cout << "corrected: start=" <<idx_from_int( m_info.start) << ", step=" << m_info.step
                  << ", end=" << idx_from_int(m_info.end )<< "\n";

        std::string indices_str = "indices=[";
        for(auto idx: scs::indices(idx_from_int(m_info.start), m_info.step, idx_from_int(m_info.end))){
            indices_str += std::to_string(idx) + ", ";
        }
        std::cout << indices_str << "]\n";
    }
    inline size_t idx_from_int(const int n) const {
        int size = static_cast<int>(m_container.size());
        int bounded_n = n;
        bounded_n = n >= size? size - 1: bounded_n;
        bounded_n = n < -size? -size: bounded_n;
        size_t idx = bounded_n >= 0? static_cast<size_t>(bounded_n): static_cast<size_t>(size + bounded_n);
        return idx;
    }
private:
    Index_info m_info;
    T m_container;

private:
    slice();
};
}

scs::Start operator "" _start(unsigned long long in){
    scs::Start s(static_cast<int>(in)); return s;}

scs::Step operator "" _step(unsigned long long in){
    scs::Step s(static_cast<int>(in)); return s;}

scs::End operator "" _end(unsigned long long in){
    scs::End e(static_cast<int>(in)); return e;}
 
