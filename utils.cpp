#include "utils.hpp"
#include <vector>
#include <string>
using namespace std;
vector<string> utils::explode( const string &delimiter, const string &str)
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


// #include <iostream>
// int main(int argc, char const *argv[]) {
//   vector<string> v = utils::explode(" ","yo je suis nul");
//   for (size_t i = 0;  i < v.size(); i++) {
//       cout << v[i] <<endl;
//   }
//   return 0;
// }
