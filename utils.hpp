#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED
#include <vector>
#include <string>
using namespace std;

class utils{
public:
  static vector<string> explode( const string &delimiter, const string &str);
};

#endif // UTILS_HPP_INCLUDED