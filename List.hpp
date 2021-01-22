#pragma once

#include <memory>

namespace MyDataStructuresImpl
{

template< class DataType >
class List
{

public:
   template< class DataType >
   class Node
   {
      friend class List< DataType >;

   private:
      Node* GetNext() const { return _next; }
      Node* SetNext( Node* n ) { _next = n; }      
      std::shared_ptr< DataType > GetData() const { return _data; };

   private:
      Node* _next;
      std::shared_ptr< DataType > _data;
   };

private:
   Node< DataType > _head;
};

} // end of namespace MyDataStructuresImpl