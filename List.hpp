#pragma once

#include <memory>

#include <memory>

// class A {
// public:
//    static shared_ptr<A> Create();
// 
// private:
//    A() {}
// 
//    struct MakeSharedEnabler;
// };
// 
// struct A::MakeSharedEnabler : public A {
//    MakeSharedEnabler() : A() {
//    }
// };
// 
// shared_ptr<A> A::Create() {
//    return make_shared<MakeSharedEnabler>();
// }

namespace MyDataStructuresImpl
{


template< class DataType >
class SingleLinkedNode
{
private:
   using DataPtr = std::shared_ptr< DataType >;
   using NodePtr = std::shared_ptr< SingleLinkedNode >;

private:
   struct MakeSharedEnabler : SingleLinkedNode< DataType >
   {
      MakeSharedEnabler( DataPtr data ) : SingleLinkedNode( data ) {}
      MakeSharedEnabler( NodePtr next, DataPtr data ) : SingleLinkedNode( next, data ) {}
   };

private:
   explicit SingleLinkedNode( DataPtr data )
      : _next( nullptr )
      , _data( data )
   {}

   explicit SingleLinkedNode( NodePtr next, DataPtr data )
      : _next( next )
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