#pragma once

#include "DBDI_Base.hpp"


enum class DBDI_Hierachy
{
   DBDI_Derived1,
   DBDI_Derived2
};


DBDI_Base::UP_DBDI_Base Factory( DBDI_Hierachy h );