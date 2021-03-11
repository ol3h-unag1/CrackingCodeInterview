#pragma once

#include <memory>
#include <functional>

namespace DesignPatternsImpl
{

//////////////////////////////////////////////////////
//Helpers:////////////////////////////////////////////
//////////////////////////////////////////////////////

class VirtualDestrutor_Interface
{
public:
   virtual ~VirtualDestrutor_Interface() = 0
   {}
};


//////////////////////////////////////////////////////
//Factory Method://///////////////////////////////////
//////////////////////////////////////////////////////

class Product_Interface : public VirtualDestrutor_Interface
{
protected:
   Product_Interface() {}

private:
   friend class Creator_Inteface;
   using ProductDataProviderType = std::function< int() >;

public:
   virtual void Operation() const = 0;
   void SetDataProvider( ProductDataProviderType dp ) { _dataProvider = dp; }

protected:
   ProductDataProviderType _dataProvider = nullptr;
};

class Product1 : public Product_Interface
{
public:
   void Operation() const override;
};

class Product2 : public Product_Interface
{
public:
   void Operation() const override;
};

class Creator_Inteface : public VirtualDestrutor_Interface
{
public:
   virtual std::unique_ptr< Product_Interface > CreateProduct() const = 0;
};

class Creator1 : public Creator_Inteface
{
public:
   std::unique_ptr< Product_Interface > CreateProduct() const override;
};

class Creator2 : public Creator_Inteface
{
public:
   std::unique_ptr< Product_Interface > CreateProduct() const override;
};

void Factory_Test( std::initializer_list< std::unique_ptr< Product_Interface > > );

//////////////////////////////////////////////////////
//Adapter:////////////////////////////////////////////
//////////////////////////////////////////////////////

class RoundHole : public VirtualDestrutor_Interface
{
public:
   explicit RoundHole( double radius )
      : _radius( radius )
   {}

   virtual double GetRadius() const { return _radius; }

private:
   double _radius;
};


class SquarePeg
{
public:
   explicit SquarePeg( double sideSize )
      : _sideSize( sideSize )
   {}

   double GetSideSize() const { return _sideSize; }

private:
   double _sideSize;
};


class SquarePegAdapter : public RoundHole
{
public:
   explicit SquarePegAdapter( std::unique_ptr< SquarePeg > sp )
      : RoundHole( -1 )
      , _squarePeg( std::move( sp ) )
   {}

   double GetRadius() const override { return _squarePeg->GetSideSize() * sqrt( 2 ) / 2; }

private:
   std::unique_ptr< SquarePeg > _squarePeg;
};

 void Adapter_Test( std::initializer_list< std::unique_ptr< RoundHole > > );

} // end of DesignPatternsImpl namespace