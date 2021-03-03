#pragma once

#include "DBDI_Base.hpp"

class DBDI_Derived1 : public DBDI_Base::MakeUniqueEnabler
{
private:
   struct MakeUniqueEnabler;

private:
   friend DBDI_Base::UP_DBDI_Base Factory( DBDI_Hierachy h );

private:
   DBDI_Derived1() {}
   ~DBDI_Derived1() override {}

   virtual void Init() override { _data = 100; }
};

struct DBDI_Derived1::MakeUniqueEnabler : DBDI_Derived1
{
   MakeUniqueEnabler() : DBDI_Derived1() {}
};