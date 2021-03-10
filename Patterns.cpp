#include <iostream>

#include "Patterns.hpp"

#include "Util.hpp"


//////////////////////////////////////////////////////
//Factory Method://///////////////////////////////////
//////////////////////////////////////////////////////

void FM_Product1::Operation() const
{
   COUT_FUNCSIG_2SPOT_SPACE;
   if( _dataProvider )
   {
      std::cout << " Data: " << _dataProvider() << std::endl;
   }
   else
   {
      std::cout << "Error. No data provider!" << std::endl;
   }
}

void FM_Product2::Operation() const
{
   COUT_FUNCSIG_2SPOT_SPACE;
   if( _dataProvider )
   {
      std::cout << " Data: " << ( _dataProvider() + _dataProvider() ) << std::endl;
   }
   else
   {
      std::cout << "Error. No data provider!" << std::endl;
   }
}

std::unique_ptr<FM_Product_Interface> FM_Creator1::CreateProduct() const
{
   auto p1 = std::make_unique< FM_Product1 >();
   p1->SetDataProvider( []() { return 1; } );
   return p1;
}

std::unique_ptr<FM_Product_Interface> FM_Creator2::CreateProduct() const
{
   auto p2 = std::make_unique< FM_Product2 >();
   p2->SetDataProvider( []() { return 2; } );
   return p2;
}

void FM_Test( std::initializer_list< std::unique_ptr<FM_Product_Interface> > products )
{
   for( auto const& p : products )
   {
      p->Operation();
   }
}
