#include <iostream>
#include <fstream>
#include <iomanip>

#include <cmath>

#include <vector>
#include <queue>

#include <set>

#include <unordered_map>
#include <unordered_set>

#include <string>

#include <type_traits>

#include <limits>

#include <functional>
#include <utility>
#include <numeric>
#include <algorithm>

#include <chrono>

#include <bitset>

#include <random>

#include <any>
#include <typeindex>

#include "Random.hpp"
#include "Util.hpp"

#include "List.hpp"
#include "Stack.hpp"
#include "Tree.hpp"

#include "Patterns.hpp"

#include "DBDI_Factory.hpp"



/// sums of cubes
std::size_t const G_lowerBound = 1;
std::size_t const G_upperBound = 1000;
std::size_t const G_power = 3;

struct ABCD
{
   ABCD( std::size_t a, std::size_t b, std::size_t c, std::size_t d )
      : _a( a )
      , _b( b )
      , _c( c )
      , _d( d )
   {}

   std::size_t _a;
   std::size_t _b;
   std::size_t _c;
   std::size_t _d;
};
std::vector< ABCD > SumsOfCubes()
{
   std::vector< ABCD > solutions;
   for( auto a = G_lowerBound; a < G_upperBound; ++a )
   {
      for( auto b = G_lowerBound; b < G_upperBound; ++b )
      {
         for( auto c = G_lowerBound; c < G_upperBound; ++c )
         {
            for( auto d = G_lowerBound; d < G_upperBound; ++d )
            {
               std::cout << a << " " << b << " " << c << " " << d << std::endl;


               if( a == b == c == d )
               {
                  solutions.emplace_back( a, b, c, d );
                  continue;
               }

               if( ( ( a == c ) && ( b == d ) ) || ( ( a == d ) && ( b == c ) ) )
               {
                  solutions.emplace_back( a, b, c, d );
                  continue;
               }

               if( std::pow( a, G_power ) + std::pow( b, G_power ) == std::pow( c, G_power ) + std::pow( d, G_power ) )
               {
                  solutions.emplace_back( a, b, c, d );
               }
            }
         }
      }
   }

   return solutions;
}

/// PERMUTATION
void Permutation( std::string str, std::string oldPrefix )
{
   if( str.empty() )
   {
      std::cout << oldPrefix << std::endl;
   }
   else
   {
      for( std::size_t index = 0; index < str.size(); ++index )
      {
         auto reminder1stPart = str.substr( 0, index );
         auto reminder2ndPart = str.substr( index + 1 );
         auto reminder = reminder1stPart + reminder2ndPart;
         auto newPrefix = oldPrefix + str[ index ];
         Permutation( reminder, newPrefix );
      }
   }
}
void Permutation( std::string str )
{
   Permutation( str, "" );
}

/// powers of 2
int powersOf2( int n )
{
   if( n < 1 )
   {
      return 0;
   }

   if( n == 1 )
   {
      std::cout << n << std::endl;
      return 1;
   }

   int prev = powersOf2( n / 2 );
   int curr = prev * 2;
   std::cout << curr << std::endl;

   return curr;
}

/// Endless array median
std::vector< int > const sourceNumbers = { 12, 31, 25, 12, 43, 64, 47, 56, 75, 68, 62, 74, 57, 80, 89, 98, 99, 15, 10, 11 };
template< class HeapType1, class HeapType2 >
void BalanceHeapsFree( HeapType1& from, HeapType2& to )
{
   if( from.size() < to.size() )
   {
      return;
   }

   while( from.size() - to.size() > 1 )
   {
      auto fromTop = from.top();
      to.push( fromTop );
      from.pop();
   }
}
template< class ElementType >
double ArrayMedian( std::vector< ElementType > const& sourceNumbers )
{
   if( sourceNumbers.empty() )
   {
      return std::numeric_limits< double >::max();
   }
   if( sourceNumbers.size() == 1 )
   {
      return sourceNumbers.front();
   }

   std::priority_queue< int > smallerHalf_MaxHeap;
   std::priority_queue< int, std::vector< int >, std::greater< int > > biggerHalf_MinHeap;
   if( sourceNumbers[ 0 ] < sourceNumbers[ 1 ] )
   {
      smallerHalf_MaxHeap.push( sourceNumbers[ 0 ] );
      biggerHalf_MinHeap.push( sourceNumbers[ 1 ] );
   }
   else
   {
      smallerHalf_MaxHeap.push( sourceNumbers[ 1 ] );
      biggerHalf_MinHeap.push( sourceNumbers[ 0 ] );
   }
   std::size_t index = 2; // start from 3rd value
   for( ; index < sourceNumbers.size(); ++index )
   {
      auto const number = sourceNumbers[ index ];
      if( number <= smallerHalf_MaxHeap.top() )
      {
         smallerHalf_MaxHeap.push( number );
         BalanceHeapsFree( smallerHalf_MaxHeap, biggerHalf_MinHeap );
      }
      else
      {
         biggerHalf_MinHeap.push( number );
         BalanceHeapsFree( biggerHalf_MinHeap, smallerHalf_MaxHeap );
      }
   }

   if( smallerHalf_MaxHeap.size() == biggerHalf_MinHeap.size() )
   {
      return ( smallerHalf_MaxHeap.top() + biggerHalf_MinHeap.top() ) / static_cast< double >( 2 );
   }

   if( smallerHalf_MaxHeap.size() < biggerHalf_MinHeap.size() )
   {
      return biggerHalf_MinHeap.top();
   }
   else
   {
      return smallerHalf_MaxHeap.top();
   }
}
class Median
{
public:
   explicit Median( int number1, int number2 )
   {
      if( number2 < number1 )
      {
         std::swap( number1, number2 );
      }

      smallerHalf_MaxHeap.push( number1 );
      biggerHalf_MinHeap.push( number2 );
   }

public:
   double Push( int number )
   {
      if( number <= smallerHalf_MaxHeap.top() )
      {
         smallerHalf_MaxHeap.push( number );
      }
      else
      {
         biggerHalf_MinHeap.push( number );
      }

      BalanceHeaps( biggerHalf_MinHeap, smallerHalf_MaxHeap );
      return GetMedian();
   }

   double GetMedian() const
   {
      if( smallerHalf_MaxHeap.size() == biggerHalf_MinHeap.size() )
      {
         return static_cast< double >( smallerHalf_MaxHeap.top() + biggerHalf_MinHeap.top() ) / 2.0;
      }

      if( smallerHalf_MaxHeap.size() < biggerHalf_MinHeap.size() )
      {
         return biggerHalf_MinHeap.top();
      }
      else
      {
         return smallerHalf_MaxHeap.top();
      }
   }


private:
   template< class HeapType1, class HeapType2 >
   void BalanceHeaps( HeapType1& big, HeapType2& small )
   {
      if( big.size() < small.size() )
      {
         return BalanceHeaps( small, big );
      }

      while( big.size() - small.size() > 1 )
      {
         auto fromTop = big.top();
         small.push( fromTop );
         big.pop();
      }
   }

private:
   std::priority_queue< int > smallerHalf_MaxHeap;
   std::priority_queue< int, std::vector< int >, std::greater< int > > biggerHalf_MinHeap;
};
//int const lowBound = -200;
//int const highBound = 200;
//std::vector< int > numbers{ lowBound, highBound };
//int const amount = 18;
//Median m( numbers.front(), numbers.back() );
//
//auto printNumbersAndMedian = [&]()
//{
//   std::cout << "Numbers: ";
//   for( std::size_t i = 0u; i < numbers.size() - 1; ++i )
//   {
//      std::cout << numbers[ i ] << ", ";
//   }
//   std::cout << numbers.back() << std::endl;
//   std::cout << "Median: " << m.GetMedian() << std::endl;
//   std::cout << "----------------------------------" << std::endl;
//};
//
//printNumbersAndMedian();
//for( int i = 0; i < amount; ++i )
//{
//   numbers.push_back( RandomInt( lowBound, highBound ) );
//   m.Push( numbers.back() );
//   printNumbersAndMedian();
//}

/// string builder
std::vector< std::string > words
{
    "NYIoCQN28T7CLD871fNw",
    "NrU9e90M7mPu8GJdLxvw",
    "hL5WQwRzpW3SqC9RTVkK",
    "cecAZ3O5Ly53idGIrbFD",
    "09DDcGWQ7YElfAok1vgH",
    "ccTBfsVu65cmnLYHpr3X",
    "GULigXSwNwHcQXv0zbrn",
    "1TDxFoxKyfOn7JHXul6x",
    "fNpUx7QYahBUsXGd1ZSb",
    "pkCrMfvE8fDQ46RiDnZd",
    "4KZaUovHY7l9Fiii3JSS",
    "Uu32o2J28N0sTOIzu7BO",
    "dwT13RZ0ydZ48Il5zaQm",
    "FVrQZpy2BvmifiUTxSqe",
    "2enQrZ0qEhTQHk3gopaj",
    "Geh2ooNvCRg9keW2Micm",
    "k3D7y7p5j2Vlfm2HgSiR",
    "AVGXuAfjaR7oPhY2ND7H",
    "Bi2YL5ywgQfreQ3HAZ6I",
    "FZKAnAskP0NYQhxgobzI",
    "NYIoCQN28T7CLD871fNw",
    "NrU9190M7mPu8GJdLxvw",
    "hL5W1wRzpW3SqC9RTVkK",
    "cecA13O5Ly53idGIrbFD",
    "09DD1GWQ7YElfAok1vgH",
    "ccTB1sVu65cmnLYHpr3X",
    "GULi1XSwNwHcQXv0zbrn",
    "1TDx1oxKyfOn7JHXul6x",
    "fNpU17QYahBUsXGd1ZSb",
    "pkCr1fvE8fDQ46RiDnZd",
    "4KZa1ovHY7l9Fiii3JSS",
    "Uu3212J28N0sTOIzu7BO",
    "dwT11RZ0ydZ48Il5zaQm",
    "FVrQ1py2BvmifiUTxSqe",
    "2enQ1Z0qEhTQH23gopaj",
    "Geh21oNvCRg9k2W2Micm",
    "k3D717p5j2Vlf22HgSiR",
    "AVGX1AfjaR7oP2Y2ND7H",
    "Bi2Y15ywgQfre23HAZ6I",
    "FZKA1AskP0NYQ2xgobzI",
    "NYIo1QN28T7CL2871fNw",
    "NrU9190M7mPu82JdLxvw",
    "hL5W1wRzpW3Sq29RTVkK",
    "cecA13O5Ly53i2GIrbFD",
    "09DD1GWQ7YElf2ok1vgH",
    "ccTBfsVu65cmn2YHpr3X",
    "GULigXSwNwHcQ2v0zbrn",
    "1TDxFoxKyfOn72HXul6x",
    "fNdUx7QYahBUs2Gd1ZSb",
    "pkdrMfvE8fDQ42RiDnZd",
    "4KdaUovHY7l9F2ii3JSS",
    "Uud2o2J28N0sT2Izu7BO",
    "dwd13RZ0ydZ482l5zaQm",
    "FVdQZpy2Bvmif2UTxSqe",
    "2edQrZ0qEhTQH23gopaj",
    "Ged2ooNvCRg9k2W2Micm",
    "k3d7y7p5j2Vlf22HgSiR",
    "AVdXuAfjaR7oP2Y2ND7H",
    "BidYL5ywgQfre23HAZ6I",
    "FZdAnAskP0NYQ2xgobzI",
    "NYdoCQN28T7CL2871fNw",
    "Nrd9e90M7mPu82JdLxvw",
    "hLdWQwRzpW3Sq29RTVkK",
    "cedAZ3O5Ly53i2GIrbFD",
    "09dDcGWQ7YElf2ok1vgH",
    "ccdBfsVu65cmn2YHpr3X",
    "GUdigXSwNwHcQ2v0zbrn",
    "1TdxFoxKyfOn72HXul6x",
    "fNdUx7QYahBUs2Gd1ZSb",
    "pkdrMfvE8fDQ42RiDnZd",
    "4KdaUovHY7l9F2ii3JSS",
    "Uud2o2J28N0sT2Izu7BO",
    "dwd13RZ0ydZ482l5zaQm",
    "FVdQZpy2BvmisdUTxSqe",
    "2edQrZ0qEhTQsd3gopaj",
    "Ged2ooNvCRg9sdW2Micm",
    "k3d7y7p5j2Vlsd2HgSiR",
    "AVdXuAfjaR7osdY2ND7H",
    "BidYL5ywgQfrsd3HAZ6I",
    "FZdAnAskP0NYsdxgobzI",
    "NYdoCQN28T7Csd871fNw",
    "Nrd9e90M7mPusdJdLxvw",
    "hLdWQwRzpW3Ssd9RTVkK",
    "cedAZ3O5Ly53sdGIrbFD",
    "09dDcGWQ7YElsdok1vgH",
    "ccdBfsVu65cmsdYHpr3X",
    "GUdigXSwNwHcsdv0zbrn",
    "1TdxFoxKyfOnsdHXul6x",
    "fNdUx7QYahBUsdGd1ZSb",
    "pkdrMfvE8fDQsdRiDnZd",
    "4KdaUovHY7l9sdii3JSS",
    "Uud2o2J28N0ssdIzu7BO",
    "dwd13RZ0ydZ4sdl5zaQm",
    "FVdQZpy2BvmisdUTxSqe",
    "2edQrZ0qEhTQsd3gopaj",
    "Geh2ooNvCRg9sdW2Micm",
    "k3D7y7p5j2Vlsd2HgSiR",
    "AVGXuAfjaR7osdY2ND7H",
    "Bi2YL5ywgQfrsd3HAZ6I",
    "FZKAnAskP0NYsdxgobzI",
    "NYIoCQN28T7Csd871fNw",
    "NrU9e90M7mPusdJdLxvw",
    "hL5WQwRzpW3Ssd9RTVkK",
    "cecAZ3O5Ly53sdGIrbFD",
    "09DDcGWQ7YElsdok1vgH",
    "ccTBfsVu65cmsdYHpr3X",
    "GULigXSwNwHcsdv0zbrn",
    "1TDxFoxKyfOnsdHXul6x",
    "fNpUx7QYahBUsdGd1ZSb",
    "pkCrMfvE8fDQsdRiDnZd",
    "4KZaUovHY7l9sdii3JSS",
    "Uu32o2J28N0ssdIzu7BO",
    "dwT13RZ0ydZ4sdl5zaQm",
    "FVrQZpy2BvmisdUTxSqe",
    "2enQrZ0qEhTQsd3gopaj",
    "Geh2ooNvCRg9sdW2Micm",
    "k3D7y7p5j2Vlsd2HgSiR",
    "AVGXuAfjaR7osdY2ND7H",
    "Bi2YL5ywgQfrsd3HAZ6I",
    "FZKAnAskP0NYsdxgobzI"
};
std::string JoinWords( std::vector< std::string > const& words )
{
   std::string sentence = "";
   for( auto const& w : words )
   {
      sentence += w;
   }

   return sentence;
}

/// replace spaces
bool ReplaceSpaces( char* str, int strLength, int bufferSize )
{
   int spaceCount = 0;
   int index = 0;
   for( int i = 0; i < strLength; ++i )
   {
      if( str[ i ] == ' ' )
      {
         spaceCount++;
      }
   }

   index = strLength + spaceCount * 2;
   if( index != bufferSize )
   {
      return false;
   }

   str[ index-- ] = '\0';
   for( int i = strLength - 1; i >= 0; --i )
   {
      if( str[ i ] == ' ' )
      {
         str[ index ] = 'X';
         str[ index - 1 ] = 'Y';
         str[ index - 2 ] = 'Z';
         index -= 3;
      }
      else
      {
         str[ index-- ] = str[ i ];
      }
   }

   return true;

   //int const size = 16;
   //char* str = new char[ size + 1 ];
   //str[ 0 ] = 'a';
   //str[ 1 ] = 'b';
   //str[ 2 ] = ' ';
   //str[ 3 ] = 'c';
   //str[ 4 ] = ' ';
   //str[ 5 ] = ' ';
   //str[ 6 ] = ' ';
   //str[ 7 ] = 'd';
   //str[ 8 ] = '\0';
   //
   //std::cout << str << std::endl;
   //ReplaceSpaces( str, 8, size );
   //std::cout << str << std::endl;
   //delete[] str;
   //str = nullptr;
}
bool ReplaceSpaces( std::string& source, std::string const replacer )
{
   if( replacer.empty() || source.empty() )
      return false;

   int spaces = 0;
   for( auto const& letter : source )
      if( letter == ' ' )
         spaces++;

   auto const originalSrcSize = source.size();
   source.resize( source.size() + spaces * ( replacer.size() - 1 ) );

   for( int origReversedIndex = originalSrcSize - 1, reversedIndex = source.size() - 1;
      origReversedIndex >= 0 && reversedIndex >= 0;
      --origReversedIndex )
   {
      if( source[ origReversedIndex ] == ' ' )
      {
         for( int k = replacer.size() - 1; k >= 0; --k )
         {
            source[ reversedIndex-- ] = replacer[ k ];
         }
      }
      else
      {
         source[ reversedIndex-- ] = source[ origReversedIndex ];
      }
   }

   return true;
}

/// check if one string is permutation of another in O(N), where N is lengths of the strings
int CharToPrime( unsigned char uc )
{
   static std::vector< int > const primes256
   {
      2,
      3,
      5,
      7,
      11,
      13,
      17,
      19,
      23,
      29,
      31,
      37,
      41,
      43,
      47,
      53,
      59,
      61,
      67,
      71,
      73,
      79,
      83,
      89,
      97,
      101,
      103,
      107,
      109,
      113,
      127,
      131,
      137,
      139,
      149,
      151,
      157,
      163,
      167,
      173,
      179,
      181,
      191,
      193,
      197,
      199,
      211,
      223,
      227,
      229,
      233,
      239,
      241,
      251,
      257,
      263,
      269,
      271,
      277,
      281,
      283,
      293,
      307,
      311,
      313,
      317,
      331,
      337,
      347,
      349,
      353,
      359,
      367,
      373,
      379,
      383,
      389,
      397,
      401,
      409,
      419,
      421,
      431,
      433,
      439,
      443,
      449,
      457,
      461,
      463,
      467,
      479,
      487,
      491,
      499,
      503,
      509,
      521,
      523,
      541,
      547,
      557,
      563,
      569,
      571,
      577,
      587,
      593,
      599,
      601,
      607,
      613,
      617,
      619,
      631,
      641,
      643,
      647,
      653,
      659,
      661,
      673,
      677,
      683,
      691,
      701,
      709,
      719,
      727,
      733,
      739,
      743,
      751,
      757,
      761,
      769,
      773,
      787,
      797,
      809,
      811,
      821,
      823,
      827,
      829,
      839,
      853,
      857,
      859,
      863,
      877,
      881,
      883,
      887,
      907,
      911,
      919,
      929,
      937,
      941,
      947,
      953,
      967,
      971,
      977,
      983,
      991,
      997,
      1009,
      1013,
      1019,
      1021,
      1031,
      1033,
      1039,
      1049,
      1051,
      1061,
      1063,
      1069,
      1087,
      1091,
      1093,
      1097,
      1103,
      1109,
      1117,
      1123,
      1129,
      1151,
      1153,
      1163,
      1171,
      1181,
      1187,
      1193,
      1201,
      1213,
      1217,
      1223,
      1229,
      1231,
      1237,
      1249,
      1259,
      1277,
      1279,
      1283,
      1289,
      1291,
      1297,
      1301,
      1303,
      1307,
      1319,
      1321,
      1327,
      1361,
      1367,
      1373,
      1381,
      1399,
      1409,
      1423,
      1427,
      1429,
      1433,
      1439,
      1447,
      1451,
      1453,
      1459,
      1471,
      1481,
      1483,
      1487,
      1489,
      1493,
      1499,
      1511,
      1523,
      1531,
      1543,
      1549,
      1553,
      1559,
      1567,
      1571,
      1579,
      1583,
      1597,
      1601,
      1607,
      1609,
      1613,
      1619
   };
   return primes256[ uc ];
}
bool IsPermutation( std::string str1, std::string str2 )
{
   if( str1.size() != str2.size() )
   {
      return false;
   }

   if( str1.empty() || str2.empty() )
   {
      return false;
   }

   int product1 = 1;
   int product2 = 1;

   for( std::size_t i = 0; i < str1.size(); ++i )
   {
      product1 *= CharToPrime( str1[ i ] );
      product2 *= CharToPrime( str2[ i ] );
   }

   return product1 == product2;

   // std::cout << IsPermutation( "?123!asZZd-@", "Z?s3!d2-1a@Z" ) << std::endl;

}

double FractionPart( double number )
{
   return number - static_cast< int >( number );
}

// Find Poisoned Bottle
class Bottle
{
public:
   explicit Bottle( std::size_t id )
      : _id( id )
   {}

   auto GetId() const { return _id; }

   void Poison() { _poisoned = true; }
   bool IsPoisoned() const { return _poisoned; }

   bool operator<( Bottle const& other ) { return _id < other._id; }

private:
   std::size_t _id;
   bool _poisoned = false;
};
class SingleUseTestStick
{
public:
   explicit SingleUseTestStick( std::size_t id )
      : _id( id )
   {}

   auto GetId() const { return _id;  }

   void Test( Bottle const& b )
   {
      if( b.IsPoisoned() )
      {
         _isPositive = true;
      }
   }

   bool IsPositive() const { return _isPositive; }

private:
   bool _isPositive = false;
   std::size_t _id;
};
auto GenerateBottlesBatch()
{
   auto const initialNumberOfBottles = 1000u;
   std::vector< Bottle > bottles;
   bottles.reserve( initialNumberOfBottles );

   for( auto i = 0u; i < initialNumberOfBottles; ++i )
   {
      bottles.emplace_back( i + 1);
   }

   std::random_device rd;
   std::mt19937 re( rd() );
   std::shuffle( bottles.begin(), bottles.end(), re );
   bottles.front().Poison();
   std::sort( bottles.begin(), bottles.end() );

   return bottles;
}
auto GenerateSticksPack()
{
   auto const initialNumberOfSticks = 10u;
   std::vector< SingleUseTestStick > sticks;
   sticks.reserve( initialNumberOfSticks );
   for( auto i = 0u; i < initialNumberOfSticks; ++i )
   {
      sticks.emplace_back( i );
   }

   return sticks;
}
void FindPoisonedBottle()
{
   auto bottles = GenerateBottlesBatch();

   for( auto const& b : bottles )
   {
      if( b.IsPoisoned() )
      {
         std::cout << __FUNCSIG__ << " " << b.GetId() << " bottle is poisoned. Binary:\n" << std::bitset< 10 >( b.GetId() ) << std::endl;
      }
   }

   auto sticks = GenerateSticksPack();

   for( auto bottleIndex = 0u; bottleIndex < bottles.size(); ++bottleIndex )
   {
      std::bitset< 10 > bs( bottles[ bottleIndex ].GetId() );
      for( auto bit = 0; bit < 10; ++bit )
      {
         if( bs[ bit ] )
         {
            sticks[ bit ].Test( bottles[ bottleIndex ] );
         }
      }
   }

   for( auto const& s : sticks )
   {
      std::cout << s.IsPositive() ? 1 : 0;
   }
   std::cout << std::endl;

   std::bitset< 10 > result;
   for( auto i = 0u; i < 10; ++i )
   {
      result[ i ] = sticks[ i ].IsPositive();
   }

   std::cout << "Test result: " << result.to_ulong() << std::endl;

}

// Test of user defined data with range based loops
class RangeBasedLoopFreeFunctionsServedDataType
{
private:
   using ContainerType = std::vector< int >;

public:
   using IteratorType = ContainerType::iterator;
   using ConstIteratorType = ContainerType::const_iterator;

private:
   friend IteratorType begin( RangeBasedLoopFreeFunctionsServedDataType const& );
   friend IteratorType end( RangeBasedLoopFreeFunctionsServedDataType const& );

   friend ConstIteratorType cbegin( RangeBasedLoopFreeFunctionsServedDataType const& );
   friend ConstIteratorType cend( RangeBasedLoopFreeFunctionsServedDataType const& );

public:
   RangeBasedLoopFreeFunctionsServedDataType( std::size_t const& size )
   {
      _data.reserve( size );
      for( auto i = 0u; i < size; ++i )
      {
         _data.emplace_back( i );
      }         
   }

   auto size() const { return _data.size(); }

private:
   ContainerType _data;
};
RangeBasedLoopFreeFunctionsServedDataType::IteratorType begin( RangeBasedLoopFreeFunctionsServedDataType const& t )
{
   return const_cast< RangeBasedLoopFreeFunctionsServedDataType& >( t )._data.begin();
}
RangeBasedLoopFreeFunctionsServedDataType::IteratorType end( RangeBasedLoopFreeFunctionsServedDataType const& t )
{
   return const_cast< RangeBasedLoopFreeFunctionsServedDataType& >( t )._data.end();
}
RangeBasedLoopFreeFunctionsServedDataType::ConstIteratorType cbegin( RangeBasedLoopFreeFunctionsServedDataType const& t )
{
   return t._data.cbegin();
}
RangeBasedLoopFreeFunctionsServedDataType::ConstIteratorType cend( RangeBasedLoopFreeFunctionsServedDataType const& t )
{
   return t._data.cend();
}

// multiplying numbers only with bit ">>" operation and ariphmetic "+"
int MinProductHelper( int, int );
int MinProduct( int a, int b )
{
   return MinProductHelper( std::min( a, b ), std::max( a, b ) );
}
int MinProductHelper( int smaller, int bigger )
{
   if( smaller == 0 )
   {
      return 0;
   }
   else if( smaller == 1 )
   {
      return bigger;
   }

   int s = smaller >> 1;  
   int halfProd = MinProductHelper( s, bigger );
   if( smaller % 2 == 0 )
   {
      return halfProd + halfProd;
   }
   else
   {
      return halfProd + halfProd + bigger;
   }
}

// generate all possible correct ( each '(' has ')' and vice versa) permurmation of '()'
void AddParen( std::vector< std::string >& parens, int leftRem, int rightRem, std::string& str, int index)
{
   if( leftRem < 0 || rightRem < leftRem )
   {
      return;
   }

   if( leftRem == 0 && rightRem == 0 )
   {
      parens.push_back( str );
   }
   else
   {
      str[ index ] = '(';
      AddParen( parens, leftRem - 1, rightRem, str, index + 1 );

      str[ index ] = ')';
      AddParen( parens, leftRem, rightRem - 1, str, index + 1 );
   }
}
std::vector< std::string > GenerateParens( int count )
{
   std::string str( count * 2, '\0' );
   std::vector< std::string > parens;
   AddParen( parens, count, count, str, 0 );
   return parens;
}

// swap numbers in place
template< class T >
std::enable_if_t < std::is_integral_v< T > >
SwapInPlace( T& left, T& right )
{
   left = left ^ right;
   right = left ^ right;
   left = left ^ right;
}
////other options:
//template< class T, std::enable_if_t< std::is_integral_v< T > > >
//void SwapInPlace( T& left, T& right )
//{
//   left = left ^ right;
//   right = left ^ right;
//   left = left ^ right;
//}
//
//template< class T, std::enable_if_t< std::is_floating_point_v< T > > >
//void SwapInPlace( T& left, T& right )
//{
//   left = left - right;
//   right = left + right;
//   left = right - left;
//}
//
//template< class T, std::enable_if_t< std::is_integral_v< T > >* = nullptr >
//void SwapInPlace( T& left, T& right )
//{
//   left = left ^ right;
//   right = left ^ right;
//   left = left ^ right;
//}
//
//template< class T, std::enable_if_t< std::is_floating_point_v< T > >* = nullptr >
//void SwapInPlace( T& left, T& right )
//{
//   left = left - right;
//   right = left + right;
//   left = right - left;
//}
template< class T >
std::enable_if_t < std::is_floating_point_v< T > >
SwapInPlace( T& left, T& right )
{
   left = left - right;
   right = left + right;
   left = right - left;
}

// T9
class T9Parser
{
private:
   T9Parser()
   {
      std::ifstream ifs( _wordsBankFileName );
      if( !ifs )
      {
         throw std::invalid_argument( std::string( __FUNCSIG__ ) + " | cant' open " + _wordsBankFileName );
      }

      std::size_t bigWordsCounter = 0;
      std::string word;
      while( ifs >> word )
      {
         std::string number = "";
         for( auto const& letter : word )
         {
            if( !std::isalpha( letter ) )
            {
               throw std::invalid_argument( std::string( __FUNCSIG__ ) + " bad letter: '" + letter + "'" );
            }

            number += _letter2digit.at( letter );
         }

         _number2words.insert( { number, word } );
      }
   }

private:
   struct MakeSharedEnabler;

public:
   static std::shared_ptr< T9Parser > Instance();

public:
   auto GetWords( std::string number )
   {
      for( auto const& digit : number )
      {
         if( !isdigit( digit ) )
         {
            throw std::invalid_argument( std::string( __FUNCSIG__ ) + digit + " is not a digit" );
         }
      }

      std::vector< std::string > result;
      auto const range = _number2words.equal_range( number );
      for( auto it = range.first; it != range.second; ++it )
      {
         result.push_back( it->second );
      }

      return result;
   }

private:
   std::unordered_map< char, char > const _letter2digit =
   { { 'a', '2' }, { 'b', '2' }, { 'c', '2' },
     { 'd', '3' }, { 'e', '3' }, { 'f', '3' },
     { 'g', '4' }, { 'h', '4' }, { 'i', '4' },
     { 'j', '5' }, { 'k', '5' }, { 'l', '5' },
     { 'm', '6' }, { 'n', '6' }, { 'o', '6' },
     { 'p', '7' }, { 'q', '7' }, { 'r', '7' }, { 's', '7' },
     { 't', '8' }, { 'u', '8' }, { 'v', '8' },
     { 'w', '9' }, { 'x', '9' }, { 'y', '9' }, { 'z', '9' }
   };

   std::unordered_multimap< std::string, std::string > _number2words;
   std::string const _wordsBankFileName = "words_alpha.txt";

private:
   // get/set weak ptr
   static std::weak_ptr < MakeSharedEnabler > WeakInstance( std::shared_ptr< T9Parser::MakeSharedEnabler > instance = nullptr )
   {
      static std::weak_ptr < MakeSharedEnabler > _weakInstance;
      if( instance )
      {
         _weakInstance = instance;
      }
      return _weakInstance;
   }
};
struct T9Parser::MakeSharedEnabler : T9Parser 
{
   MakeSharedEnabler() : T9Parser() {}
};
std::shared_ptr< T9Parser > T9Parser::Instance()
{
   if( auto instance = WeakInstance().lock() )
   {
      return instance;
   }

   auto instance = std::make_shared< MakeSharedEnabler >();
   static_cast< void >( WeakInstance( instance ) );
   return instance;
}
void TestT9Parser()
{
   std::cout << "Initializing parser...\n";
   auto parser = T9Parser::Instance();

   auto prompt = []() { std::cout << "Please enter a number to convert to word or `-1` to quit: "; };

   prompt();
   std::string input = "";
   while( std::cin >> input )
   {
      if( input == "-1" )
      {
         break;
      }

      decltype( parser->GetWords( input ) ) words;
      try
      {
         words = parser->GetWords( input );
      }
      catch( std::exception const& e )
      {
         std::cout << __FUNCSIG__ << " " << e.what() << std::endl;
         prompt();
         continue;
      }
      catch( ... )
      {
         std::cout << __FUNCSIG__ << " unhandled exception. " << std::endl;
         prompt();
         continue;
      }

      if( words.empty() )
      {
         std::cout << "No words for number <" << input << ">" << std::endl;
      }
      else
      {
         for( auto const& word : words )
         {
            std::cout << word << std::endl;
         }
      }
      prompt();
   }
}

// Reverse bits
constexpr int G_bitsInByte = 8;
template< class T, int bytes = sizeof( T ) >
std::enable_if_t< std::is_integral_v< T >, T >
ReverseBits( T number )
{
   int bits = bytes * G_bitsInByte;
   T result = 0;
   while( bits > 0 )
   {
      result |= ( number & 1 ) << ( bits - 1 );
      number >>= 1;
      --bits;
   }

   return result;
}
template< class T >
std::enable_if_t< std::is_integral_v< T >, bool > IsBitwisePalindrome( T number )
{
   return number == ReverseBits( number );
}

// Reverse number lexicographically
template< class T >
std::enable_if_t< std::is_unsigned_v< T >, T > 
ReverseNumber( T number )
{
   T result = 0;
   while( number )
   {
      result = result * 10 + number % 10;
      number /= 10;
   }

   return result;
}

// Type erasure
class TypeErasure_AbstractInterfaceWrapper
{
public:
   virtual double Advance( double number, double step ) const = 0;
   virtual ~TypeErasure_AbstractInterfaceWrapper() = 0
   {}
};

template< class CallableType >
class TypeErasure_ConcreteInterfaceWrapper : public TypeErasure_AbstractInterfaceWrapper
{
public: 
   template< class T, class = std::enable_if_t< std::is_convertible_v< T, CallableType > > >
   explicit TypeErasure_ConcreteInterfaceWrapper( T&& callable )
      : _callable( std::move( _callable ) )
   {}

   double Advance( double number, double step ) const override
   {
      return _callable( number, step );
   }

private:
   CallableType _callable;
};

class TypeErasure_CallableInterface
{
public:
   template< class CallableType >
   TypeErasure_CallableInterface( CallableType&& callable )
      : _callHandler( std::make_unique< TypeErasure_ConcreteInterfaceWrapper< CallableType > >( callable ) )
   {}

public:
   double operator()( double number, double steps ) const
   {
      return _callHandler->Advance( number, steps );
   }

private:
   std::unique_ptr< TypeErasure_AbstractInterfaceWrapper > _callHandler;
};

double TrippleCall( TypeErasure_CallableInterface const& ci )
{
   return ci( 1, .1 ) + ci( 2, .2 ) + ci( 4, .4 );
}

template< typename T >
void TypeErasure_FunctionPointers( std::shared_ptr< T > t )
{
   std::cout << *t << std::endl;
}

void AnyVisitorTest();
void TypeErasureTest()
{
   // Virtual functions
   std::vector< TypeErasure_CallableInterface > v;
   v.push_back( []( double n, double s ) { return n + s + n / 10; } );
   v.push_back( []( double, double ) { return 1.2345; } );
   v.push_back( []( double n, double s) { return ( n + s ) / ( n - s ) + 1; } );
   
   for( auto const& e : v  )
   { 
      std::cout << TrippleCall( e ) << std::endl;
   }
   
   // Function pointers 
   std::function< void( std::shared_ptr< void > ) > call;

   using TypeErasure_VoidFunc = void( * )( std::shared_ptr< void > );
   call = reinterpret_cast< TypeErasure_VoidFunc >( TypeErasure_FunctionPointers< std::string > );
   call( std::make_shared< std::string >( "Hi there!" ) );

   call = reinterpret_cast< TypeErasure_VoidFunc >( TypeErasure_FunctionPointers< int > );
   call( std::make_shared< int >( 33 ) );

   call = reinterpret_cast< TypeErasure_VoidFunc >( TypeErasure_FunctionPointers< char > );
   call( std::make_shared< char >( 33 ) );

   // std::any
   int i = 7;
   std::string str( "Hello, Type Erasure!" );
   double d = 2.3;

   std::vector< std::any > values;
   values.push_back( 1 );
   values.push_back( std::string( "Hello, Type Erasure!" ) );
   values.push_back( 1.1 );

   for( auto& a : values )
   {
      std::cout << a.type().name() << std::endl;
   }

   // any visitor
   AnyVisitorTest();
}

template< class T, class Visitor >
std::pair< std::type_index, std::function< void( std::any const& ) > >
PairTypeIndex2Visitor( Visitor const& visitor )
{
   return 
   { 
      std::type_index( typeid( T ) ), [visitor]( std::any const& any )
      {
         if constexpr( std::is_same_v< void, T > )
         {
            visitor();
         }
         else
         {
            visitor( std::any_cast< T const& >( any ) );
         }
      } 
   };  
}

std::unordered_map < std::type_index, std::function< void( std::any const& ) > >&
TypeIndex2Visitor()
{
   static std::unordered_map < std::type_index, std::function< void( std::any const& ) > > any2visitor
   {
      PairTypeIndex2Visitor< void >( []() { std::cout << "void: Any hasn't value!" << std::endl; } ),
      PairTypeIndex2Visitor< int >( []( auto const& obj ) { std::cout << obj << std::endl; } ),
      PairTypeIndex2Visitor< std::string >( []( auto const& obj ) { std::cout << obj << std::endl; } ),
      PairTypeIndex2Visitor< double >( []( auto const& obj ) { std::cout << obj << std::endl; } ),
   };

   return any2visitor;
}

void ProcessAny( std::any const& any )
{
   if( auto it = TypeIndex2Visitor().find( std::type_index( any.type() ) ); it != TypeIndex2Visitor().end() )
   {
      it->second( any );
   }
   else
   {
      std::cout << std::quoted( any.type().name() ) << " is not a registered type!" << std::endl;
   }
}

template< class T, class Visitor >
void RegisterAnyVisitor( Visitor const& visitor )
{
   TypeIndex2Visitor().insert( PairTypeIndex2Visitor< T >( visitor ) );
}

class TestClasForAnyVisitor
{
public:
   explicit TestClasForAnyVisitor( int data )
      : _data( data )
   {}

public:
   int GetData() const { return _data; }

private: 
   int _data;
};

void AnyVisitorTest()
{
   ProcessAny( std::any() );
   ProcessAny( std::any( 123 ) );
   ProcessAny( std::any( 4.56 ) );
   ProcessAny( std::any( std::string( "Hello, Any Visitor!" ) ) );
   ProcessAny( std::any( TestClasForAnyVisitor( 789 ) ) );
   RegisterAnyVisitor< TestClasForAnyVisitor >( []( auto const& obj ) { std::cout << obj.GetData() << std::endl; } );
   ProcessAny( std::any( TestClasForAnyVisitor( 789 ) ) );
}

using llu = long long unsigned;
llu GetFibonacciTermByIndex_RecursionImpl( llu index, std::unordered_map< llu, llu >& cache );
llu GetFibonacciTermByIndex_Recusion( llu index )
{
   if( index > 93 )
   {
      return std::numeric_limits< llu >::max();
   }

   std::unordered_map< llu, llu > cache;
   return GetFibonacciTermByIndex_RecursionImpl( index, cache );
}
llu GetFibonacciTermByIndex_RecursionImpl( llu index, std::unordered_map< llu, llu >& cache )
{
   if( auto it = cache.find( index ); it != cache.end() )
   {
      return it->second;
   }

   if( index == 0 )
   {
      return 0;
   }
   if( index < 3 )
   {
      return 1;
   }  

   cache[ index ] = GetFibonacciTermByIndex_RecursionImpl( index - 1, cache ) + GetFibonacciTermByIndex_RecursionImpl( index - 2, cache );
   return cache[ index ];
}

llu GetFibonacciTermByIndex_Iteration( llu index )
{
   if( index == 0 )
   {
      return 0;
   }
   if( index < 3 )
   {
      return 1;
   }
   if( index > 93 )
   {
      return std::numeric_limits< llu >::max();
   }

   llu fibAtIndexMinus1 = 1; // term at index 2
   llu fibAtIndex = fibAtIndexMinus1 + 1; // term at index 1 + term at index 2 = term at index 3
   // f( n ) = f( n - 1 ) + f( n - 2 )
   // f( n + 1 ) = f( n ) + f( n - 1 )
   for( llu k = 3; k < index; ++k )
   {
      llu nextFib = fibAtIndex + fibAtIndexMinus1;
      fibAtIndexMinus1 = fibAtIndex;
      fibAtIndex = nextFib;
   }

   return fibAtIndex;
}

template< class Container, class Deviation >
auto CheckDeviation( Container&& cont, Deviation&& dev )
{
   return std::adjacent_find( cont.begin(), cont.end(), [dev]( auto n, auto nplus1 ) 
      {
         return std::abs( nplus1 - n ) >= std::abs( dev );
      } );
}

template< class Iter >
auto Slide( Iter first, Iter last, Iter position )
{
   if( first < position )
   {
      return std::make_pair( std::rotate( first, last, position ), position );
   }
   if ( position < first )
   {
      return std::make_pair( position, std::rotate( position, first, last ) );
   }
   return std::make_pair( first, last );
}

template< class Iter, class Selector >
auto Gather( Iter first, Iter last, Iter gatherPoint, Selector s )
{
   auto not_s = [&s]( auto const& val ) { return !s( val ); };
   return std::make_pair( std::stable_partition( first, gatherPoint, not_s ), std::stable_partition( gatherPoint, last, s) );
}

#include <iostream>
#include <list>
#include <vector>

//You are playing a Texas Holdem poker game with two other players in flop street. There are 3 players in total. Each player can CHECK, BET,  FOLD, CALL (no raises).
//
//Print out all possible sequence lines for the current street( round ).
//
//For example :
//CHECK - CHECK - CHECK
//CHECK - BET - FOLD - FOLD"
// 
// 
// 
// 
// You are playing a Texas Holdem poker game with two other players in flop street. 
//  There are 3 players in total. Each player can CHECK, BET,  FOLD, CALL (no raises).
// 
// Print out all possible sequence lines for the current street( round ).
// 
// For example :
// CHECK - CHECK - CHECK
// CHECK - BET - FOLD - FOLD
// 2nd part : print out pot size( assume 60 chips starting pot ) for each line; bet is 10 chips
// 3rd part : Print out lines where the game ends AND print out intermediate lines with pot size
// 4th part : add a RAISE ( 20 chips ) for the (no reRAISE)

// FOR TWO PLAYERS
// BET   CALL
// BET   FOLD
// BET   RAISE
// CALL  CALL
// CALL  FOLD
// CALL  RAISE
// CHECK CHECK
// CHECK BET
// FOLD  CALL
// FOLD  FOLD
// FOLD  RAISE
// RAISE CALL
// RAISE FOLD

// FOR THREE PLAYERS
// BET   CALL  CALL
// BET   CALL  FOLD
// BET   CALL  RAISE CALL  CALL
// BET   CALL  RAISE CALL  FOLD
// BET   CALL  RAISE FOLD  CALL
// BET   CALL  RAISE FOLD  FOLD
// BET   FOLD  CALL
// BET   FOLD  FOLD  
// BET   FOLD  RAISE CALL
// BET   FOLD  RAISE FOLD
// BET   RAISE CALL  CALL
// BET   RAISE CALL  FOLD
// BET   RAISE FOLD  CALL 
// BET   RAISE FOLD  FOLD 
// CHECK CHECK CHECK
// CHECK CHECK BET   ...
// CHECK BET ...

enum class E_Decision
{
   BET,
   CALL,
   CHECK,
   FOLD,
   RAISE,

   INVALID
};

class DecisionSequence : private std::vector< E_Decision >
{
private:
   using Super = std::vector< E_Decision >;

public:
   explicit DecisionSequence( int numberOfPlayers )
      : _numberOfPlayers( numberOfPlayers  )
      , _activePlayers( numberOfPlayers )
      , _stepsLeft( numberOfPlayers )
   {
      // consider to throw if number of players is bad
      reserve( 3 * _numberOfPlayers - 1 );
   }

public: 
   using Super::begin;
   using Super::end; 

public:
   void PushBack( E_Decision d ) 
   { 
      emplace_back( d );
      if( ( _hasRaise == false ) && ( d == E_Decision::RAISE ) )
      {
         _hasRaise = true;
      }

      switch( d )
      {
      case E_Decision::BET:
      case E_Decision::RAISE:
         _stepsLeft = _activePlayers - 1;
         break;

      case E_Decision::CALL:
      case E_Decision::CHECK:
         --_stepsLeft;
         break;

      case E_Decision::FOLD:
         --_stepsLeft;
         --_activePlayers;
         break;
      }
   }

   E_Decision Back() const { return back(); }
   bool HasRaise() const { return _hasRaise; }
   bool IsComplete() const { return _stepsLeft == 0; }

private:
   bool _hasRaise = false;
   int _numberOfPlayers = 0;
   int _activePlayers = 0;
   int _stepsLeft = 0;
};

std::string Decision2Str( E_Decision d )
{
   switch( d )
   {
   case E_Decision::BET:      return "BET";
      break;
   case E_Decision::CALL:     return "CALL";
      break;                
   case E_Decision::CHECK:    return "CHECK";
      break;              
   case E_Decision::FOLD:     return "FOLD";
      break;
   case E_Decision::RAISE:    return "RAISE";
      break;
   case E_Decision::INVALID:  return "INVALID";
      break;
   }

   return "UKNOWN-DECISION!";
}

std::list < E_Decision > GetNextDecisions( E_Decision decision, bool includeRaise )
{
   switch( decision )
   {
   case E_Decision::BET:
   case E_Decision::CALL:
   case E_Decision::FOLD:
   {
      if( includeRaise )
      {
         return { E_Decision::CALL, E_Decision::FOLD, E_Decision::RAISE };
      }
      else
      { 
         return { E_Decision::CALL, E_Decision::FOLD };
      }
   }
      break;

   case E_Decision::CHECK:
      return { E_Decision::BET, E_Decision::CHECK };
      break;

   case E_Decision::RAISE:
      return { E_Decision::CALL, E_Decision::FOLD };
      break;
   }

   return {};
}

void GetAllDecisionPermutations_Impl( std::list< DecisionSequence >& result, int numberOfPlayers );

void TestPoker();

std::list< DecisionSequence >
GetAllDecisionPermutations( int numberOfPlayers )
{
   if( numberOfPlayers < 2 )
   {
      return {};
   }

   DecisionSequence bet( numberOfPlayers ), check( numberOfPlayers );

   bet.PushBack( E_Decision::BET );
   check.PushBack( E_Decision::CHECK );

   std::list< DecisionSequence > result{ bet, check }; // adding two initial decisions
   GetAllDecisionPermutations_Impl( result, numberOfPlayers );
   return result;
}

void GetAllDecisionPermutations_Impl( std::list< DecisionSequence >& result, int numberOfPlayers )
{
   auto first = result.begin();
   while( first != result.end() )
   {
      auto& sequence = *first;
      if( sequence.IsComplete() )
      {
         ++first;
      }
      else
      {
         auto nextPossibleDecisions = GetNextDecisions( sequence.Back(), !sequence.HasRaise() );

         // removing front before making list duplicates and 
         // saving it for later addition to the list
         auto late = nextPossibleDecisions.front();
         nextPossibleDecisions.pop_front();

         // duplicates creation
         auto const dublicates2add = nextPossibleDecisions.size();
         auto insertionPoint = first;
         ++insertionPoint; // incrementing before loop, so inserting after first
         for( auto i = 0; i < dublicates2add; ++i ) // we change insertionPoint twice inside the body of loop
         {
            insertionPoint = result.insert( insertionPoint, sequence ); // 1st

            auto& dub = *insertionPoint;
            dub.PushBack( nextPossibleDecisions.front() );
            nextPossibleDecisions.pop_front();

            ++insertionPoint; // 2nd
         }

         // inserting saved item
         sequence.PushBack( late );
      }
   }
}

template< class Container >
void PrintDecisionsStepByStep( Container const& decisions, int pot = 60, int bet = 10, int raise = 20 )
{
   bool betOccured = false;
   bool raiseOccured = false;
   int potInitial = pot;

   auto first = decisions.begin();
   auto trailing = first;
   ++trailing;
   while( true )
   {
      for( auto it = first; it != trailing; ++it )
      {
         auto& a_curDec = *it;
         auto dashPrinter = it;
         std::cout << Decision2Str( *it );
         ++dashPrinter;
         if( dashPrinter != trailing )
         {
            std::cout << " - ";
         }

         if( E_Decision::BET == *it && !betOccured )
         {
            betOccured = true;
            pot += bet;
         }

         if( E_Decision::RAISE == *it && !raiseOccured )
         {
            raiseOccured = true;
            pot += raise;
         }

         if( E_Decision::CALL == *it )
         {
            if( raiseOccured )
            {
               pot += raise;
            }
            else if( betOccured )
            {
               pot += bet;
            }
            else
            {}
         }
      }
      std::cout << ": " << pot << std::endl;
      pot = potInitial;
      
      betOccured = false;
      raiseOccured = false;

      if( trailing == decisions.end() )
      {
         return;
      }

      ++trailing;
   }
}

void TestPoker()
{
   // permutations w/o pot
   auto permutations = GetAllDecisionPermutations( 3 );
   for( auto& p : permutations )
   {
      for( auto decision : p )
      {
         std::cout << Decision2Str( decision ) << " ";
      }
      std::cout << std::endl;
   }

   std::cout << "############################" << std::endl;

   // all permutations step-by-step with pot
   for( auto const& p : permutations )
   {
      PrintDecisionsStepByStep( p );
      std::cout << "-----------------------------" << std::endl;
   }
}













template< class T >
int SummIntegers_helper( T&& t )
{
   return 0;
}

int SummIntegers_helper( int i )
{
   return i;
}

int SummIntegers()
{
   return 0;
}

template< class T, class ... Args >
int SummIntegers( T&& t, Args&& ... args )
{
   return SummIntegers_helper( t ) + SummIntegers( args... );
}


template< class T >
struct IsTargetType
{
   IsTargetType( T& t ){}
   int value = 0;
};

template<>
struct IsTargetType< int >
{
   IsTargetType( int i ) : value( i ){}
   int value = 0;
};

template< class ... Args >
constexpr int SummIntegersV2_structs( Args&& ... args )
{
   return (IsTargetType< Args >( args ).value + ...) ;
}


int main()
{
   std::cout << SummIntegersV2_structs("bla", 1, 2, 3, 4, "bla", 5 ) << "\n";
}