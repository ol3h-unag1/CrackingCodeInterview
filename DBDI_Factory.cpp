#include <iostream>
#include <exception>
#include <memory>


#include "DBDI_Factory.hpp"
#include "DBDI_Derived1.hpp"
#include "DBDI_Derived2.hpp"

DBDI_Base::UP_DBDI_Base Factory( DBDI_Hierachy h )
{
   DBDI_Base::UP_DBDI_Base ret = nullptr;

   switch( h )
   {
   case DBDI_Hierachy::DBDI_Derived1:
      try
      {
         ret.reset( new DBDI_Derived1 );
      }
      catch( std::exception& e )
      {
         std::cout << e.what() << std::endl;
      }
      catch( ... )
      {
         std::cout << __FUNCSIG__ << " : " << __LINE__ <<  ": unhandled exception" << std::endl;
      }
      break;

   case DBDI_Hierachy::DBDI_Derived2:
      try
      {
         ret.reset( new DBDI_Derived2 );
      }
      catch( std::exception& e )
      {
         std::cout << e.what() << std::endl;
      }
      catch( ... )
      {
         std::cout << __FUNCSIG__ << " : " << __LINE__ << ": unhandled exception" << std::endl;
      }
      break;
   }

   return ret;
}