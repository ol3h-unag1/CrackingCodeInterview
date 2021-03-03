#include <iostream>

#include "DBDI_Base.hpp"
#include "DBDI_Factory.hpp"

void DBDI_Base::Print() const
{
   std::cout << _data << std::endl;
}

DBDI_Base::UP_DBDI_Base DBDI_Base::Create( DBDI_Hierachy h )
{
   UP_DBDI_Base p = Factory( h );
   p->Init();
   return p;
}