#include <iostream>
#include <exception>
#include <memory>


#include "DBDI_Factory.hpp"
#include "DBDI_Derived1.hpp"
#include "DBDI_Derived2.hpp"

DBDI_Base::UP_DBDI_Base Factory( DBDI_Hierachy h )
{
   switch( h )
   {
   case DBDI_Hierachy::DBDI_Derived1:
      return std::make_unique< DBDI_Derived1::MakeUniqueEnabler >();
      break;

   case DBDI_Hierachy::DBDI_Derived2:
      return std::make_unique< DBDI_Derived2::MakeUniqueEnabler >();
      break;
   }

   return nullptr;
}