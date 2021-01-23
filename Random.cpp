#include <random>

#include "Random.hpp"


std::size_t RandomSizeT( std::size_t lowerBound, std::size_t upperBound )
{
   if( lowerBound > upperBound )
      std::swap( lowerBound, upperBound );

   std::random_device rd;
   std::mt19937 rng( rd() );
   std::uniform_int_distribution< std::mt19937::result_type > dist( lowerBound, upperBound ); 

   return dist( rng );
}

int RandomInt( int lowerBound, int upperBound )
{
   if( lowerBound > upperBound )
      std::swap( lowerBound, upperBound );

   if( lowerBound >= 0 )
   {
      RandomSizeT( lowerBound, upperBound );
   }

   if( upperBound <= 0 )
   {
      return 0 - static_cast< int >( RandomSizeT( abs( upperBound ), abs( lowerBound ) ) );
   }

   // lowerBound < 0 && upperBound > 0
   int const diff = upperBound - lowerBound;
   return static_cast< int >( RandomSizeT( 0, diff ) ) - abs( lowerBound );
}