#pragma once

#include <exception>
#include <type_traits>

#include "List.hpp"

namespace MyDataStructuresImpl
{

template< class DataType >
class Stack
{
public:
   using ElementType = DataType;

private:
   using ListType = SingleLinkedNode< DataType >;
   using NodePtr = typename SingleLinkedNode< DataType >::SingleLinkedNodePtr;

public:
   Stack() 
      : _top( nullptr )
   {}

public:
   template< class U >
   void Push( U&& data )
   {
      auto const createNodeFromData = [&]()
      {
         return ListType::CreateSingleLinkedNode( std::make_shared< DataType >( std::forward< U >( data ) ) );
      };

      if( _top )
      {
         auto newTop = createNodeFromData();
         newTop->SetNext( _top );
         _top = newTop;
      }
      else
      {
         _top = createNodeFromData();
      }
   }

   void Pop()
   {
      if( _top )
      {
         _top = _top->GetNext();
      }
   }

   DataType Top() const
   {
      if( _top )
      {
         return *_top->GetData();
      }
      else
      {
         throw std::runtime_error( "Stack is empty!" );
      }
   }

   bool Empty() const { return _top == nullptr; }

private:
   NodePtr _top;
};

template< class Stack >
void SortStackWithStack( Stack&& main )
{
   using StackType = std::remove_reference_t< Stack >;
   StackType aux;

   while( main.Empty() == false )
   {
      typename StackType::ElementType const mainTopTmp = std::move( main.Top() );
      main.Pop();

      while( aux.Empty() == false && aux.Top() > mainTopTmp )
      {
         main.Push( std::move( aux.Top() ) );
         aux.Pop();
      }

      aux.Push( std::move( mainTopTmp ) );
   }

   while( aux.Empty() == false )
   {
      main.Push( std::move( aux.Top() ) );
      aux.Pop();
   }
}


} // end of namespace MyDataStructuresImpl

/// stack
//MyDataStructuresImpl::Stack< int > viewStack;
//
//for( int i = 0; i < 10; ++i )
//{
//   viewStack.Push( RandomInt( -100, 100 ) );
//}
//
//decltype( auto ) stackToSort = viewStack;
//while( viewStack.Empty() == false )
//{
//   std::cout << viewStack.Top() << std::endl;
//   viewStack.Pop();
//}
//
//std::cout << "Sorting..." << std::endl;
//
//MyDataStructuresImpl::SortStackWithStack( stackToSort );
//while( stackToSort.Empty() == false )
//{
//   std::cout << stackToSort.Top() << std::endl;
//   stackToSort.Pop();
//}
