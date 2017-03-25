#include "utils.hpp"

vector<string> utils::explode(const string &str, const string &delimiter)
{
  vector<string> arr;

  int strleng = str.length();
  int delleng = delimiter.length();
  if (delleng==0)
  return arr;//no change

  int i=0;
  int k=0;
  while( i<strleng )
  {
    int j=0;
    while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
    j++;
    if (j==delleng)//found delimiter
    {
      arr.push_back(  str.substr(k, i-k) );
      i+=delleng;
      k=i;
    }
    else
    {
      i++;
    }
  }
  arr.push_back(  str.substr(k, i-k) );
  return arr;
}

bool utils::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
