#pragma once

#include "DBDI_Base.hpp"

class DBDI_Derived2 : public DBDI_Base
{
   friend DBDI_Base::UP_DBDI_Base Factory( DBDI_Hierachy h );

private:
   DBDI_Derived2() {}
   ~DBDI_Derived2() override {}

   virtual void Init() override { _data = -100; }
};
