#include <iostream>
#include <string>
#include <map>

#include "fizbuz.hpp"

static const std::map<int, std::string> FZMap =
{
   { 3, "Fizz" },
   { 5, "Buzz" }
};

std::string fizbuz_map(void)
{
   std::string outstr = "";

   for ( int i = 1; i <= 100; i++ )
   {
      std::string itrstr = "";
      for ( const auto& [div,fzstr] : FZMap )
      {
         if ( i % div == 0 ) itrstr += fzstr;
      }

      if ( itrstr.empty() ) itrstr += std::to_string(i);

      outstr += itrstr + " ";
   }

   // Let NRVO do its thing!
   return outstr;
}

std::string fizbuz_naive(void)
{
   std::string outstr = "";

   for ( int i = 1; i <= 100; i++ )
   {
      std::string itrstr = "";
      if ( i % 3 == 0 ) itrstr += "Fizz";
      if ( i % 5 == 0 ) itrstr += "Buzz";
      if ( itrstr.empty() ) itrstr += std::to_string(i);

      outstr += itrstr + " ";
   }

   // Let NRVO do its thing!
   return outstr;
}
