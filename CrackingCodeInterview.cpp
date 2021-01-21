#include <iostream>

#include <cmath>

#include <vector>
#include <queue>
#include <string>

#include <limits>

#include <functional>
#include <utility>

#include <chrono>



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
std::vector< ABCD > foo()
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

/// recursion called from cycle
std::size_t const jobSize = 3;
std::size_t jobCallCounter = 0;
std::size_t jobsDoneCounter = 0;
void doJob( std::size_t jobSize )
{
    jobCallCounter++;
    for( std::size_t i = 0; i < jobSize; ++i )
    {
        jobsDoneCounter++;
    }
}
std::size_t recursiveCallCounter = 0;
std::size_t const cycleSize = 3;
void recursiveCall( std::size_t recursionNumber )
{
    recursiveCallCounter++;
    if( !recursionNumber )
    {
        doJob( jobSize );
    }
    else
    {
        for( std::size_t ñ = 0; ñ < cycleSize; ++ñ )
        {
            recursiveCall( recursionNumber - 1 );
        }
    }
}
//recursiveCall( 4 );
//std::cout << recursiveCallCounter << " recursive calls happened" << std::endl;
//std::cout << jobCallCounter << " job calls happened" << std::endl;
//std::cout << jobsDoneCounter << " jobs done" << std::endl;


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
double ArrayMedian( std::vector< int > const& sourceNumbers )
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
            BalanceHeaps( smallerHalf_MaxHeap, biggerHalf_MinHeap );
        }
        else
        {
            biggerHalf_MinHeap.push( number );
            BalanceHeaps( biggerHalf_MinHeap, smallerHalf_MaxHeap );
        }

        return GetMedian();
    }

private:
    template< class HeapType1, class HeapType2 >
    void BalanceHeaps( HeapType1& from, HeapType2& to )
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
    std::priority_queue< int > smallerHalf_MaxHeap;
    std::priority_queue< int, std::vector< int >, std::greater< int > > biggerHalf_MinHeap;
};


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
        sentence.append( w );
    }

    return sentence;
}
std::string JoinWordsBad( std::vector< std::string > const& words )
{
    std::string sentence = "";
    for( auto const& w : words )
    {
        sentence += w;
    }

    return sentence;
}

/// Execution time check
template< typename JobType >
void ExecutionTimeCheck( JobType job )
{
    auto t1 = std::chrono::high_resolution_clock::now();
    job();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "job execution took " << std::chrono::duration_cast< std::chrono::microseconds >( t2 - t1 ).count() << " microseconds. " << std::endl;
}
template< typename JobType, typename ... Args >
void ExecutionTimeCheck( JobType job, Args&& ... args )
{
    ExecutionTimeCheck( [ & ](){ job( std::forward< Args... >( args... ) ); } );
}

// replace spaces
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


int main()
{

}