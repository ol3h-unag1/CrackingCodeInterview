#pragma once

#include <memory>
#include "Random.hpp"

namespace MyDataStructuresImpl
{


template< class DataType >
class SingleLinkedNode
{
public:
   using DataPtr = std::shared_ptr< DataType >;
   using SingleLinkedNodePtr = std::shared_ptr< SingleLinkedNode >;

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
   SingleLinkedNodePtr CreateSingleLinkedNode( DataPtr data )
   {
      return std::make_shared< MakeSharedEnabler >( data );
   }

public:
   SingleLinkedNodePtr GetNext() const { return _next; }
   void SetNext( SingleLinkedNodePtr next ) { _next = next; }

   DataPtr GetData() const { return _data; };

private:
   SingleLinkedNodePtr _next;
   DataPtr _data;
};


auto GetRandomIntsLinkedList( std::size_t const listSize, int const min = -50, int const max = 50 )
{
   SingleLinkedNode< int >::SingleLinkedNodePtr head = nullptr;

   if( listSize < 1 )
      return head;

   head = SingleLinkedNode< int >::CreateSingleLinkedNode( std::make_shared< int >( RandomInt( min, max ) ) );
   auto listIterator = head;

   for( std::size_t i = 1; i < listSize; ++i )
   {
      listIterator->SetNext( SingleLinkedNode< int >::CreateSingleLinkedNode( std::make_shared< int >( RandomInt( min, max ) ) ) );
      listIterator = listIterator->GetNext();
   }

   return head;
}

template< class Node >
Node Advance( Node head, std::size_t steps )
{
   while( head && steps )
   {
      head = head->GetNext();
      steps--;
   }
   return head;
}

template< class Node >
Node CycleBegin( Node head )
{
   Node fast = head;
   Node slow = head;

   while( fast && fast->GetNext() )
   {
      slow = slow->GetNext();
      fast = fast->GetNext()->GetNext();

      if( slow == fast )
         break;
   }

   if( !fast || !fast->GetNext() )
      return nullptr;

   slow = head;
   while( slow != fast )
   {
      slow = slow->GetNext();
      fast = fast->GetNext();
   }

   return fast;
}

} // end of namespace MyDataStructuresImpl

/// test linked lists
//using namespace MyDataStructuresImpl;
//std::size_t const listSize = 15;
//auto head = GetRandomIntsLinkedList( listSize );
//auto listIterator = head;
//while( listIterator )
//{
//   std::cout << *listIterator->GetData() << "\t";
//   std::cout << listIterator << " ";
//   std::cout << listIterator.get() << std::endl;
//
//   listIterator = listIterator->GetNext();
//}
//
//std::cout << CycleBegin( head ) << std::endl;
//auto cycleBegin = Advance( head, 5 );
//Advance( head, listSize - 1 )->SetNext( cycleBegin );
//std::cout << CycleBegin( head ) << std::endl;
