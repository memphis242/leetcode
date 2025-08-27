#include <string>
#include <filesystem>
#include <fstream>

bool redact( std::string badwords_path, std::string redactee_path ) {

   std::filesystem::path bad_words_fpath(badwords_path);
   std::filesystem::path redactee_fpath(redactee_path);

   // Trivial cases
   if ( !std::filesystem::exists(redactee_fpath) )
      return false;

   if ( !std::filesystem::exists(badwords_fpath) )
      return true;

   std::ifstream badwords_f(badwords_fpath);
   std::fstream  redactee_f(redactee_fpath, std::ios::in | std::ios::out);

   if ( !redactee_f || !badwords_f )
      return false;

   // Obviously, a set or trie would be used here, but to account for the fact
   // that the files may be very large, we'll likely want to MapReduce, with
   // our distribution on a single machine being across threads.
   // TODO: Set up the map, reduce, and distribution.
}
