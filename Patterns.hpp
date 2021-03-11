#pragma once

#include <memory>

#include <functional>

#include <array>

#include <vector>
#include <string>

#include <cassert>

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

//////////////////////////////////////////////////////
//Bridge://///////////////////////////////////////////
//////////////////////////////////////////////////////

namespace BridgeHelpers
{

inline std::size_t AdvanceAndWrapAroundSize( std::size_t index, std::size_t size, bool forward )
{
   if( forward )
   {
      ++index;
      index %= size;
   }
   else
   {
      if( index == 0 )
      {
         index = size - 1;
      }
      else
      {
         --index;
      }
   }

   return index;
}

}

class Device_Interface : public VirtualDestrutor_Interface
{
public:
   virtual void Enable() = 0;
   virtual void Disable() = 0;    
   virtual bool IsEnabled() const = 0;

   virtual int GetVolume() const = 0;
   virtual void SetVolume( int ) = 0;

   virtual void NextChannel() = 0;
   virtual void PreviousChannel() = 0;
};

class Remote_Interface : public VirtualDestrutor_Interface
{
public:
   explicit Remote_Interface( std::unique_ptr< Device_Interface > device )
      : _device( std::move( device ) )
   {}

public:
   virtual void TogglePower() = 0;
   
   virtual void ToggleMute() = 0;

   virtual void SetVolume( int ) = 0;

   virtual void AdvanceChannel( int ) = 0;

protected:
   std::unique_ptr< Device_Interface > _device;
};

class Radio : public Device_Interface
{
 public:
    void Enable() override { _enabled = true; }
    void Disable() override { _enabled = false; }
    bool IsEnabled() const override { return false; }

   int GetVolume() const override 
   {
      if( _enabled )
      {
         return _volume;
      }
      
      return -1;
   }  
   void SetVolume( int volume ) 
   {
      if( _enabled == false )
      {
         return;
      }
      _volume = volume;
   }

   void NextChannel() override
   {
      if( _enabled == false )
      {
         return;
      }
      _currentFreqIndex = BridgeHelpers::AdvanceAndWrapAroundSize( _currentFreqIndex, _registeredFrequencies.size(), true );      
   }
   void PreviousChannel() 
   {
      if( _enabled == false )
      {
         return;
      }
      _currentFreqIndex = BridgeHelpers::AdvanceAndWrapAroundSize( _currentFreqIndex, _registeredFrequencies.size(), false );
   }

   double GetCurrentFreq() const 
   { 
      if( _enabled == false )
      {
         return -1.0;
      }

      return _registeredFrequencies[ _currentFreqIndex ]; 
   }

private:
   bool _enabled = false;
   int _volume = 0;

   std::size_t _currentFreqIndex = 0;

   static inline std::array< double, 7 > _registeredFrequencies = { 80.5, 86.9, 92.4, 99.0, 101.7, 105.3, 107.1 };
};

class TV : public Device_Interface
{
   enum class E_POWER_STATES
   {
      ON,
      SLEEP,
      OFF
   };

public:
   void Enable() override
   {
      if( _pwrState == E_POWER_STATES::SLEEP )
      {
         _pwrState = E_POWER_STATES::ON;
      }
   }
   void Disable() override
   {
      if( _pwrState == E_POWER_STATES::ON )
      {
         _pwrState = E_POWER_STATES::SLEEP;
      }
   }
   bool IsEnabled() const override { return _pwrState != E_POWER_STATES::OFF;  }
   
   int GetVolume() const override
   {
      if( _pwrState == E_POWER_STATES::OFF )
      {
         return -1;
      }

      return _volume;
   }

   void SetVolume( int vol ) override
   {
      if( IsEnabled() )
      {
         _volume = vol;
      }
   };

   void NextChannel() override
   {
      HandleNextPrevChannel( true );
   }
   void PreviousChannel() override
   {
      HandleNextPrevChannel( false );
   }

   std::string GetCurrentChannel() const { return _channels[ _currentChannelIndex ]; }

private:
   void HandleNextPrevChannel( bool next)
   {
      if( IsEnabled() == false )
      {
         return;
      }
      if( _pwrState == E_POWER_STATES::SLEEP )
      {
         _pwrState = E_POWER_STATES::ON;
      }
      _currentChannelIndex = BridgeHelpers::AdvanceAndWrapAroundSize( _currentChannelIndex, _channels.size(), next );
   }
   
private:
   E_POWER_STATES _pwrState;
   int _volume;

   std::size_t _currentChannelIndex = 0;
   static inline std::vector< std::string > _channels = { "SportTV", "Discovery", "National Geographic", "24//7 NEWS", "Action Movies" };
};

class RC : public Remote_Interface
{
public:
   explicit RC( std::unique_ptr< Device_Interface > device )
      : Remote_Interface( std::move( device ) )
   {
      assert( "RC::RC( std::unique_ptr< Device_Interface > device ) Error! No device!", _device != nullptr );
   }

   void TogglePower() override 
   {
      if( _device->IsEnabled() )
      {
         _device->Disable();
      }
      else
      {
         _device->Enable();
      }
   }

   void ToggleMute() override
   {
      static int previousVolume = 0;
      static bool muted = false;

      if( muted )
      {
         _device->SetVolume( previousVolume );
      }
      else if ( int deviceVolume = _device->GetVolume(); deviceVolume != 0 )
      {         
         previousVolume = deviceVolume;
         _device->SetVolume( 0 );

         muted = true;
      }

   }

   void SetVolume( int volume ) override 
   {
      assert( "RC::SetVolume volume must be >= 0", volume >= 0 );
      
      _device->SetVolume( volume );
   }

   void AdvanceChannel( int steps ) override 
   {
      if( steps < 0 )
      {
         while( steps < 0 )
         {
            _device->PreviousChannel();
            ++steps;
         }

         return;
      }

      if( steps > 0 )
      {
         while( steps > 0 )
         {
            _device->NextChannel();
            --steps;
         }
         
         return;
      }
   }
};


void Test_Bridge( std::initializer_list < std::unique_ptr< Remote_Interface > > );

} // end of DesignPatternsImpl namespace