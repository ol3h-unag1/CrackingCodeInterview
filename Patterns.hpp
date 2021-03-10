#pragma once

#include <memory>
#include <functional>


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

class FM_Product_Interface : public VirtualDestrutor_Interface
{
protected:
   FM_Product_Interface() {}

private:
   friend class FM_Creator_Inteface;
   using ProductDataProviderType = std::function< int() >;

public:
   virtual void Operation() const = 0;
   void SetDataProvider( ProductDataProviderType dp ) { _dataProvider = dp; }

protected:
   ProductDataProviderType _dataProvider = nullptr;
};

class FM_Product1 : public FM_Product_Interface 
{
public:
   void Operation() const override;
};

class FM_Product2 : public FM_Product_Interface
{
public:
   void Operation() const override;
};

class FM_Creator_Inteface : public VirtualDestrutor_Interface
{
public:
   virtual std::unique_ptr< FM_Product_Interface > CreateProduct() const = 0;
};

class FM_Creator1 : public FM_Creator_Inteface
{
public:
   std::unique_ptr< FM_Product_Interface > CreateProduct() const override;
};

class FM_Creator2 : public FM_Creator_Inteface
{
public:
   std::unique_ptr< FM_Product_Interface > CreateProduct() const override;
};

void FM_Test( std::initializer_list< std::unique_ptr<FM_Product_Interface> > );