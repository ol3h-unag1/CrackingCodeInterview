#pragma once

#include "DBDI_Base.hpp"

class DBDI_Derived2 : public DBDI_Base::MakeUniqueEnabler
{
private:
   struct MakeUniqueEnabler;

private:
   friend DBDI_Base::UP_DBDI_Base Factory( DBDI_Hierachy h );

private:
   DBDI_Derived2() {}
   ~DBDI_Derived2() override {}

   virtual void Init() override { _data = -100; }
};

struct DBDI_Derived2::MakeUniqueEnabler : DBDI_Derived2
{
   MakeUniqueEnabler() : DBDI_Derived2() {}
};