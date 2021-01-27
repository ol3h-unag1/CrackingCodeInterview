#pragma once

#include <memory>

#include <memory>

namespace MyDataStructuresImpl
{


template< class DataType >
class SingleLinkedNode
{
public:
   using DataPtr = std::shared_ptr< DataType >;
   using NodePtr = std::shared_ptr< SingleLinkedNode >;

private:
   struct MakeSharedEnabler : SingleLinkedNode< DataType >
   {
      MakeSharedEnabler( DataPtr data ) : SingleLinkedNode( data ) {}
   };

private:
   explicit SingleLinkedNode( DataPtr data )
      : _next( nullptr )
      , _data( data )
   {}

public:   
   static 
   NodePtr CreateNode( DataPtr data )
   {
      return std::make_shared< MakeSharedEnabler >( data );
   }

public:
   NodePtr GetNext() const { return _next; }
   void SetNext( NodePtr next ) { _next = next; }

   DataPtr GetData() const { return _data; };

private:
   NodePtr _next;
   DataPtr _data;
};


} // end of namespace MyDataStructuresImpl