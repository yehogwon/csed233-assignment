#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <unistd.h>

const char *SYMBOLS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int SYMBOLS_LEN = 62;

template <typename T>
using function_of_str = std::function<T(const std::string&)>;

std::string time_stamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string ts = std::to_string(ltm->tm_year + 1900) + std::to_string(ltm->tm_mon + 1) + std::to_string(ltm->tm_mday) + std::to_string(ltm->tm_hour) + std::to_string(ltm->tm_min) + std::to_string(ltm->tm_sec);
    return ts;
}

std::string random_string(const int len) {
    std::string rstr;
    rstr.reserve(len);
    for (int i = 0; i < len; i++) rstr += SYMBOLS[std::rand() % SYMBOLS_LEN];
    return rstr;
}

inline void lstrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != '\n';
    }));
}

inline void rstrip(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void strip(std::string &s) {
    lstrip(s);
    rstrip(s);
}

template <typename... Types, typename V>
void apply_vector(std::vector<V> &v, function_of_str<Types>... parsers) {
    // v[i] = parser[i](v[i])
    // assert(sizeof...(Types) == v.size());
    std::vector<std::function<std::variant<Types...>(V)>> parsers_vec = {parsers...};
    for (int i = 0; i < v.size(); i++) v[i] = parsers_vec[i](v[i]);
}

// code below is from: 
//  - https://stackoverflow.com/questions/10929202/initialize-stdarray-with-a-range-pair-of-iterators/10930078#10930078
//  - https://stackoverflow.com/questions/11044504/any-solution-to-unpack-a-vector-to-function-arguments-in-c
template <std::size_t... Indices>
struct indices {
    using next = indices<Indices..., sizeof...(Indices)>;
};

template <std::size_t N>
struct build_indices {
    using type = typename build_indices<N - 1>::type::next;
};

template <>
struct build_indices<0> {
    using type = indices<>;
};

template <std::size_t N>
using BuildIndices = typename build_indices<N>::type;

template <size_t num_args, typename F, typename T>
struct unpack_caller {
private:
    template <size_t... i>
    void call(F &f, std::vector<T> &args, indices<i...>){
        f(args[i]...);
    }

public:
    void operator()(std::vector<T> &args){
        assert(args.size() == num_args);
        call(f, args, BuildIndices<num_args>{});
    }
};

#endif // __UTILS_H__