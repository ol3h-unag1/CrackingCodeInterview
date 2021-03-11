#include <iostream>

#include "Patterns.hpp"

#include "Util.hpp"

namespace DesignPatternsImpl
{

//////////////////////////////////////////////////////
//Factory Method://///////////////////////////////////
//////////////////////////////////////////////////////

void Product1::Operation() const
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

void Product2::Operation() const
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

std::unique_ptr< Product_Interface > Creator1::CreateProduct() const
{
   auto p1 = std::make_unique< Product1 >();
   p1->SetDataProvider( []() { return 1; } );
   return p1;
}

std::unique_ptr< Product_Interface > Creator2::CreateProduct() const
{
   auto p2 = std::make_unique< Product2 >();
   p2->SetDataProvider( []() { return 2; } );
   return p2;
}

void Factory_Test( std::initializer_list< std::unique_ptr< Product_Interface > > products )
{
   for( auto const& p : products )
   {
      p->Operation();
   }
}

//////////////////////////////////////////////////////
//Adapter:////////////////////////////////////////////
//////////////////////////////////////////////////////

void Adapter_Test( std::initializer_list< std::unique_ptr< RoundHole > > holes )
{
   for( auto const& h : holes )
   {
      std::cout << h << ": has radius of " << h->GetRadius() << std::endl;
   }
}

//////////////////////////////////////////////////////
//Bridge://///////////////////////////////////////////
//////////////////////////////////////////////////////

void Test_Bridge( std::initializer_list<std::unique_ptr<Remote_Interface>> remoteControls )
{
   for( auto& rc : remoteControls )
   {
      rc->TogglePower();
      rc->AdvanceChannel( 1 );
      rc->AdvanceChannel( -2 );
      rc->SetVolume( 50 );
      rc->ToggleMute();
      rc->TogglePower();
   }
}

}
