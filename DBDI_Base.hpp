#pragma once

#include <memory>

class DBDI_Base;

enum class DBDI_Hierachy;

class DBDI_Base
{
public:
   using UP_DBDI_Base = std::unique_ptr< DBDI_Base >;

public:
   DBDI_Base() {}
   virtual ~DBDI_Base() {}

public:
   void Print() const;

private:
   virtual void Init() = 0;

public:   
   static UP_DBDI_Base Create( DBDI_Hierachy h );

protected:
   int _data = -1;
};