#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*! \class utils
   * \brief class tools
   *
   *  Class with usefull tools like a splitter
   */
class utils{
public:
  static vector<string> explode(const string &str, const string &delimiter);
  static bool is_number(const std::string& s);
};

#endif // UTILS_HPP_INCLUDED
