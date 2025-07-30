#include <iostream>
#include <string>
#include <map>

std::map<int, std::string> FZMap =
{
   { 3, "Fizz" },
   { 5, "Buzz" }
};

int main(void)
{
   std::string outstr = "";
   for ( int i = 1; i <= 100; i++ )
   {
      std::string itrstr = "";
      for ( auto& [div,fzstr] : FZMap )
      {
         if ( i % div == 0 ) itrstr += fzstr;
      }

      if ( itrstr.empty() ) itrstr += std::to_string(i);

      outstr += itrstr + " ";
   }

   std::cout << outstr << std::endl;
}
