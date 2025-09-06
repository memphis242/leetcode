#include <concepts>
#include <ranges>

namespace sorts
{

   template<typename T>
   concept GTComparable = requires(T a, T b) {
      { a > b } -> std::convertible_to<bool>;
   };

   template<typename R>
   concept GTComparableRange = std::ranges::random_access_range<R>
                               && GTComparable<std::ranges::range_value_t<R>>;

   template<GTComparableRange R>
   void insertion(R& range)
   {
      auto size = std::ranges::size(range);
      for ( std::ptrdiff_t i=1; i < static_cast<std::ptrdiff_t>(size); ++i )
      {
         // Place the key into its correct relative position within the left half
         // of the vector (i.e., the indices 0 ... i-1)
         auto key = range[i];
         std::ptrdiff_t j = i - 1;
         // Keep shifting elements in the range 1 up as long as they are > key
         while ( j >= 0 && range[j] > key )
         {
            range[j+1] = range[j];
            j--;
         }
         // Place the key
         range[j+1] = key;
      }
   }

   template<GTComparableRange R>
   void merge(R& range)
   {
      
   }

};
