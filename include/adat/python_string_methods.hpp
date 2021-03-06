#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <unordered_map>


// c++ 11 minimum
namespace psm {

/// Converts the first character to upper case
inline std::string capitalize(const std::string& str);

/// Converts string into lower case
inline std::string casefold(const std::string& str);

/// Returns a centered string
inline std::string center(const std::string& str, const int length, const char filler = ' ');

/// Returns the number of times a specified value occurs in a string
inline int count(const std::string& str, const std::string& sub_str,
                 const int start = 0, const int end = -1);

/// Delete cells with empty strings: ""
inline std::vector<std::string> delempty(const std::vector<std::string>& str_v);

/// Returns true if the string ends with the specified value
inline bool endswith(const std::string& str, const std::string& sub_str);

/// Sets the tab '\\t' size of the string
inline std::string expandtabs(const std::string& str, const int tabsize = 8);

/// Searches the string for a specified value and returns the position of where it was found (-1 if not found)
inline int find(const std::string& str, const std::string& sub_str,
                const int start = 0, const int end = -1);

/// Searches the string for a specified value and returns the position of where it was found
inline int index(const std::string& str, const std::string& sub_str,
                 const int start = 0, const int end = -1);

/// Returns True if all characters in the string are alphanumeric
inline bool isalnum(const std::string& str);

/// Returns True if all characters in the string are in the alphabet
inline bool isalpha(const std::string& str);

/// Returns True if all characters in the string are digits
inline bool isdigit(const std::string& str);

/// Returns True if the string is an identifier ( (a-z) or (A-Z) or (0-9) or  (_) )
inline bool isidentifier(const std::string& str);

/// Returns True if all characters in the string are lower case
inline bool islower(const std::string& str);

/// Returns True if all characters in the string are printable
inline bool isprintable(const std::string& str);

/// Returns True if all characters in the string are whitespaces
inline bool isspace(const std::string& str);

/// Returns True if the string follows the rules of a title
inline bool istitle(const std::string& str);

/// Returns True if all characters in the string are upper case
inline bool isupper(const std::string& str);

/// Joins the elements of an iterable to the end of the string
template<typename T>
std::string join(const T& stl_container, const std::string& seperator);

/// Returns a left justified version of the string
inline std::string ljust(const std::string& str, const int length,
                         const char character = ' ');

/// Converts a string into lower case
inline std::string lower(const std::string& str);


/// Returns a left trim version of the string
inline std::string lstrip(const std::string& str, const std::string characters = " ");

/// Returns a translation table to be used in translations
inline std::function<std::string(std::string)>
maketrans(const std::string& from, const std::string& to);

/// Returns a array where the string is parted into three parts
inline std::array<std::string, 3> partition(const std::string& str,
                                            const std::string& seperator);

/// Returns a string where a specified value is replaced with a specified value
inline std::string replace(const std::string& str, const std::string& old_value,
                           const std::string& new_value, const int count = -1);

/// Searches the string for a specified value and returns the last position of where it was found
inline int rfind(const std::string& str, const std::string& sub_str,
                 const int start = 0, const int end = -1);

/// Searches the string for a specified value and returns the last position of where it was found
inline int rindex(const std::string& str, const std::string& sub_str,
                  const int start = 0, const int end = -1);

/// Returns a right justified version of the string
inline std::string rjust(const std::string& str, const int length,
                         const char character = ' ');

/// Returns a array where the string is parted into three parts
inline std::array<std::string, 3> rpartition(const std::string& str,
                                             const std::string& seperator);

/// Splits the string at the specified separator, and returns a list
inline std::vector<std::string> rsplit(const std::string& str,
                                       const char delim,
                                       const int max_split = -1);

/// Returns a right trim version of the string
inline std::string rstrip(const std::string& str, const std::string characters = " ");

/// Splits the string at the specified separator, and returns a list
inline std::vector<std::string> split(const std::string& str,
                                      const char delim,
                                      const int max_split = -1);

/// Splits the string at line breaks and returns a list
inline std::vector<std::string> splitlines(const std::string& str,
                                           const bool keep_line_breaks = false);

/// Returns true if the string starts with the specified value
inline bool startswith(const std::string& str, const std::string& sub_str);

/// Returns a trimmed version of the string
inline std::string strip(const std::string& str, const std::string characters = " ");

/// Swaps cases, lower case becomes upper case and vice versa
inline std::string swapcase(const std::string& str);

/// Converts the first character of each word to upper case
inline std::string title(const std::string& str);

/// Converts a string into upper case
inline std::string upper(const std::string& str);

/// Fills the string with a specified number of 0 values at the beginning
inline std::string zfill(const std::string& str, const int length);
}


// =====+=====+=====+=====+  =====+=====+  =====+=====+=====+=====+
// =====+=====+=====+=====+ Implementation =====+=====+=====+=====+
// =====+=====+=====+=====+  =====+=====+  =====+=====+=====+=====+


std::string psm::capitalize(const std::string& str)
{
    if(str.empty())
        return str;
    std::string result = str;
    std::transform(result.begin(), result.begin() + 1,result.begin(), ::toupper);
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::casefold(const std::string& str)
{
    if(str.empty())
        return str;
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::center(const std::string& str, const int length, const char filler)
{
    if(static_cast<size_t>(length) <= str.size())
        return str;
    std::string space = std::string((length - str.size()) / 2, filler);
    std::string result = space + str + space;
    return result.size() < static_cast<size_t>(length) ? result + filler: result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
int psm::count(const std::string& str,
               const std::string& sub_str,
               const int start,
               const int end)
{
    int str_size = static_cast<int>(str.size());
    int start_ = start < 0 ? 0: start;
    int end_ = (end < 0 || end > str_size) ? str_size: end;

    if(end_ <= start_ || start_ >= str_size)
        return 0;

    int num_matches = 0;
    int cursor = start;

    while ( true )
    {
        cursor = psm::find(str, sub_str, cursor, end);

        if ( cursor < 0 ) break;

        cursor += static_cast<int>(sub_str.size());
        num_matches += 1;
    }

    return num_matches;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::vector<std::string> psm::delempty(const std::vector<std::string>& str_v)
{
    if(str_v.empty())
        return str_v;
    std::vector<std::string> result;
    for(auto str: str_v)
        if(!str.empty())
            result.push_back(str);
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::endswith(const std::string& str, const std::string& sub_str)
{
    if (str.length() >= sub_str.length()) {
        return (0 == str.compare (str.length() - sub_str.length(), sub_str.length(), sub_str));
    }
    return false;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::expandtabs(const std::string& str, const int tabsize)
{
    if(str.empty())
        return str;
    std::string result;
    int tabsize_ = tabsize < 1 ? 1: tabsize;
    std::string fill = std::string(tabsize_, ' ');
    for(size_t i = 0; i < str.size(); i++){
        if(str.at(i) == '\t'){
            result += fill;
            continue;
        }
        result += str.at(i);
    }
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
int psm::find(const std::string& str,
              const std::string& sub_str,
              const int start,
              const int end)
{
    int str_size = static_cast<int>(str.size());
    int start_ = start < 0 ? 0: start;
    int end_ = (end < 0 || end > str_size) ? str_size: end;

    if(end_ <= start_ || start_ >= str_size)
        return -1;

    std::size_t found = str.find(sub_str, start);
    if (found == std::string::npos)
        return -1;

    if(found > (end_ - sub_str.size()))
        return -1;

    int result =  found;
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
int psm::index(const std::string& str, const std::string& sub_str,
               const int start, const int end)
{
    return psm::find(str, sub_str, start, end);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isalnum(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isalnum);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isalpha(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isalpha);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isdigit(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isidentifier(const std::string& str)
{
    if(str.empty())
        return false;
    if(std::isdigit(str.at(0)))
        return false;
    for(char c: str)
        if(!std::isalnum(c) && c != '_')
            return false;

    return true;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::islower(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::islower);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isprintable(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isprint);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isspace(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isspace);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::istitle(const std::string& str)
{
    if(str.empty())
        return false;
    if(std::isalpha(str.at(0)))
        if(psm::islower(std::string(1, str.at(0))))
            return false;

    for(size_t i = 1; i < str.size(); i++)
        if(std::isalpha(str.at(i)))
            if(psm::islower(std::string(1, str.at(i - 1))))
                return false;

    return true;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::isupper(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isupper);
}


// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
template<typename T>
std::string psm::join(const T& stl_container, const std::string& seperator)
{

    std::string result;
    typename T::const_iterator itr = stl_container.begin();
    typename T::const_iterator end = stl_container.end();
    for (; itr != end; ++itr)
        result += *itr + seperator;

    for(uint i = 0 ; i < seperator.size(); i++)
        result.pop_back();
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::ljust(const std::string& str, const int length,
                       const char character)
{
    size_t str_size = str.size();
    if(str_size > static_cast<size_t>(length))
        return str;
    return str + std::string( length - str_size, character );
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
inline std::string psm::lower(const std::string& str)
{
    if(str.empty())
        return str;
    std::string result = str;
    std::transform(result.begin(), result.end(),result.begin(), ::tolower);
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::lstrip(const std::string& str, const std::string characters)
{
    if(str.empty() || characters.empty())
        return str;
    size_t index = 0;

    for(size_t i = 0; i < str.size(); i++){
        bool break_loop = true;
        for(auto character: characters)
            if(str.at(i) == character)
                break_loop = false;
        if(break_loop)
            break;
        index++;
    }
    return str.substr(index, str.size() - index);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::function<std::string(std::string)>
psm::maketrans(const std::string& from, const std::string& to) {
    std::unordered_map<char, char> map;
    for (std::string::size_type i = 0;
         i != std::min(from.size(), to.size()); ++i) {
        map[from[i]] = to[i];
    }
    return [=](std::string s) {
        for (auto& c : s) {
            const auto mapped_c = map.find(c);
            if (mapped_c != map.end()) {
                c = mapped_c->second;
            }
        }
        return s;
    };
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::array<std::string, 3> psm::partition(const std::string& str,
                                          const std::string& seperator)
{
    std::array<std::string, 3> result;
    int index = psm::find(str, seperator);
    if(index == - 1){
        result.at(0) = str;
        return result;
    }
    result.at(0) = str.substr( 0, index );
    result.at(1) = seperator;
    result.at(2) = str.substr(index + seperator.size(), str.size());
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::replace(const std::string& str, const std::string& old_value,
                         const std::string& new_value, const int count)
{
    std::string result = str;
    if(old_value.empty())
        return result;
    size_t start_pos = 0;
    int num_replaced = 0;
    while((start_pos = result.find(old_value, start_pos)) != std::string::npos) {
        if(num_replaced == count)
            break;
        result.replace(start_pos, old_value.length(), new_value);
        start_pos += new_value.length();
        num_replaced++;
    }
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
int psm::rfind(const std::string& str, const std::string& sub_str,
               const int start, const int end)
{
    int str_size = static_cast<int>(str.size());
    int start_ = start < 0 ? 0: start;
    int end_ = (end < 0 || end > str_size) ? str_size: end;

    if(end_ <= start_ || start_ >= str_size)
        return -1;

    std::size_t found = str.rfind(sub_str, end_);
    if (found == std::string::npos)
        return -1;

    if(found < static_cast<size_t>(start_))
        return -1;

    int result =  found;
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
int psm::rindex(const std::string& str, const std::string& sub_str,
                const int start, const int end)
{
    return psm::rfind(str, sub_str, start, end);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::rjust(const std::string& str, const int length,
                       const char character)
{
    size_t str_size = str.size();
    if(str_size > static_cast<size_t>(length))
        return str;
    return std::string( length - str_size, character ) + str;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::array<std::string, 3> psm::rpartition(const std::string& str,
                                           const std::string& seperator)
{
    std::array<std::string, 3> result;
    int index = psm::rfind(str, seperator);
    if(index == - 1){
        result.at(2) = str;
        return result;
    }
    result.at(0) = str.substr( 0, index );
    result.at(1) = seperator;
    result.at(2) = str.substr(index + seperator.size(), str.size());
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::vector<std::string> psm::rsplit(const std::string& str,
                                     const char delim,
                                     const int max_split)
{
    if(max_split == 0 || delim == '\0' || str.empty())
        return {str};
    if(max_split < 0)
        return psm::split(str, delim);

    std::vector<std::string> chunks;
    std::stringstream ss(str);
    std::string chunk;

    while (std::getline(ss, chunk, delim))
        chunks.push_back(chunk);

    if(chunks.size() <= static_cast<size_t>(max_split))
        return chunks;

    size_t first_chunks_size = 0;
    for(size_t j = 0; j < chunks.size() - max_split; j++)
        first_chunks_size += chunks.at(j).size() + 1;

    std::vector<std::string> new_chunks;
    new_chunks.push_back(str.substr(0, first_chunks_size - 1));
    for(int j = chunks.size() - max_split; j < static_cast<int>(chunks.size()); j++)
        new_chunks.push_back(chunks.at(j));

    return new_chunks;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::rstrip(const std::string& str, const std::string characters)
{
    if(str.empty() || characters.empty())
        return str;
    int index = str.size() - 1;

    for(int i = str.size() - 1; i >= 0; i--){
        bool break_loop = true;
        for(auto character: characters)
            if(str.at(i) == character)
                break_loop = false;
        if(break_loop)
            break;
        index--;
    }
    return str.substr(0, index + 1);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::vector<std::string> psm::split(const std::string& str,
                                    const char delim,
                                    const int max_split)
{
    if(max_split == 0 || delim == '\0')
        return {str};
    std::vector<std::string> chunks;
    std::stringstream ss(str);
    std::string chunk;
    int i = 0;
    while (std::getline(ss, chunk, delim)){
        chunks.push_back(chunk);
        i++;
        if(i == max_split)
            break;
    }

    // get the rest of str
    size_t chunks_size = 0;
    for(auto& chunk: chunks){
        chunks_size += chunk.size() + 1;
    }
    if(chunks_size >= str.size())
        return chunks;
    chunks.push_back(str.substr(chunks_size, str.size() - chunks_size));

    return chunks;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::vector<std::string> psm::splitlines(const std::string& str,
                                         const bool keep_line_breaks)
{
    std::vector<std::string> n_lines = psm::split(str, '\n');
    std::vector<std::string> result;
    std::string r_linebreak = keep_line_breaks? "\r": "";
    std::string n_linebreak = keep_line_breaks? "\n": "";

    for(auto& n_line: n_lines){
        if(n_line.empty()){
            result.push_back(n_linebreak);
            continue;
        }
        std::vector<std::string> r_lines = psm::split(n_line, '\r');
        for(auto& r_line: r_lines){
            result.push_back(r_line + r_linebreak);
        }
        if(psm::endswith(n_line, "\r") && keep_line_breaks)
            result.back().pop_back();
        result.back() += n_linebreak;
    }
    if(psm::endswith(result.back(), "\n") && keep_line_breaks)
        result.back().pop_back();
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
bool psm::startswith(const std::string& str, const std::string& sub_str)
{
    if (str.length() >= sub_str.length()) {
        return (0 == str.compare (0, sub_str.length(), sub_str));
    }
    return false;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::strip(const std::string& str, const std::string characters)
{
    return psm::rstrip(psm::lstrip(str, characters), characters);
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::swapcase(const std::string& str)
{
    std::string result;
    for(auto c: str){
        if (std::isupper(c))
            result += std::tolower(c);
        else
            result += std::toupper(c);
    }
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::title(const std::string& str)
{
    if(str.empty())
        return str;
    std::string result;


    std::string first_c (1, str.at(0));
    if(std::isalpha(str.at(0)))
        if(psm::islower(first_c))
            first_c = psm::upper(first_c);
    result.push_back(first_c.at(0));

    for(size_t i = 1; i < str.size(); i++){
        if(!std::isalpha(str.at(i))){
            result.push_back(str.at(i));
            continue;
        }
        std::string c (1, str.at(i));
        if(std::isalpha(str.at(i - 1))){
            c = psm::lower(c);
        } else {
            c = psm::upper(c);
        }
        result.push_back(c.at(0));
    }

    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::upper(const std::string& str)
{
    if(str.empty())
        return str;
    std::string result = str;
    std::transform(result.begin(), result.end(),result.begin(), ::toupper);
    return result;
}

// =====+=====+=====+=====+/=====+=====+=====+=====+/=====+=====+=====+=====+
std::string psm::zfill(const std::string& str, const int length)
{
    int size = static_cast<int>(str.size());
    if (size >= length)
        return str;


    std::string result = str;
    int fill = length - size;
    result = std::string( fill, '0' ) + result;

    if (result[fill] == '+' || result[fill] == '-'){
        result[0] = result[fill];
        result[fill] = '0';
    }

    return result;
}
