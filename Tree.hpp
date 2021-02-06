#pragma once

#include <algorithm>

namespace MyDataStructuresImpl
{


template< class DataType >
class BinaryTreeNode
{
public:
   using DataPtr = std::shared_ptr< DataType >;
   using BinaryTreeNodePtr = std::shared_ptr< BinaryTreeNode >;

private:
   struct MakeSharedEnabler : BinaryTreeNode< DataType >
   {
      MakeSharedEnabler( DataPtr data ) : BinaryTreeNode( data ) {}
   };

private:
   explicit BinaryTreeNode( DataPtr data )
      : _leftChild( nullptr )
      , _rightChild( nullptr )
      , _data( data )
   {}

public:   
   template< class U >
   static
   BinaryTreeNodePtr CreateBinaryTreeNode( U&& data )
   {
      return std::make_shared< MakeSharedEnabler >( std::make_shared< U >( std::forward< U >( data ) ) );
   }

public:
   BinaryTreeNodePtr GetLeftChild() const { return _leftChild; }
   BinaryTreeNodePtr SetLeftChild( BinaryTreeNodePtr node ) 
   { 
      _leftChild = node; 
      return _leftChild;
   }

   BinaryTreeNodePtr GetRightChild() const { return _rightChild; }
   BinaryTreeNodePtr SetRightChild( BinaryTreeNodePtr node ) 
   { 
      _rightChild = node;
      return _rightChild;
   }

   DataPtr GetData() const { return _data; };

private:
   BinaryTreeNodePtr _leftChild;
   BinaryTreeNodePtr _rightChild;

   DataPtr _data;
};

template< class NodeType >
std::size_t BinaryTreeHeight( NodeType const root, std::size_t const height = 0 )
{
   if( root == nullptr )
   {
      return height;
   }

   auto const leftHeight = BinaryTreeHeight( root->GetLeftChild(), height + 1 );
   auto const rightHeight = BinaryTreeHeight( root->GetRightChild(), height + 1 );

   return std::max( leftHeight, rightHeight );
}

template< class NodeType >
bool IsBalancedBinaryTree( NodeType const root )
{
   if( root == nullptr )
   {
      return false;
   }

   auto const leftHeight = BinaryTreeHeight( root->GetLeftChild() );
   auto const rightHeight = BinaryTreeHeight( root->GetRightChild() );

   return ( std::max( leftHeight, rightHeight ) - std::min( leftHeight, rightHeight ) < 2 );
}


namespace Private
{

struct HeightAndPredicate
{
   std::size_t height = 0u;
   bool predicate = true;
};

template< class NodeType >
HeightAndPredicate IsBalancedBinarySearchTree( NodeType const root, HeightAndPredicate hap = {} )
{
   if( root == nullptr )
   {
      return hap;
   }

   if( root->GetLeftChild() && ( *root->GetLeftChild()->GetData() > *root->GetData() ) )
   {
      return { 0u, false };
   }

   if( root->GetRightChild() && ( *root->GetRightChild()->GetData() < *root->GetData() ) )
   {
      return { 0u, false };
   }

   auto left = IsBalancedBinarySearchTree( root->GetLeftChild(), { hap.height + 1, true } );
   auto right = IsBalancedBinarySearchTree( root->GetRightChild(), { hap.height + 1, true } );

   return { std::max( left.height, right.height ), left.predicate && right.predicate };
}

} // end of Private namespace

template< class NodeType >
bool IsBalancedBinarySearchTree( NodeType const root )
{
   if( root == nullptr )
   {
      return false;
   }

   auto left = Private::IsBalancedBinarySearchTree( root->GetLeftChild() );
   if( left.predicate == false )
   {
      return false;
   }

   auto right = Private::IsBalancedBinarySearchTree( root->GetRightChild() );
   if( right.predicate == false )
   {
      return false;
   }

   return ( std::max( left.height, right.height ) - std::min( left.height, right.height ) < 2 );
}

// the way to declare CreateMinimalBST less verbose than using 
// template< class DataType, template< class DT, class ... Args > class Container, class ... Args >
// typename BinaryTreeNode< DataType >::BinaryTreeNodePtr
// CreateMinimalBST( Container< DataType, Args... > container )
// thou below declaration is dependent on Container::value_type
// template< class Container >
// typename BinaryTreeNode< typename std::remove_reference_t< Container >::value_type >::BinaryTreeNodePtr 
// CreateMinimalBST( Container&& container )
// {
// 
// }


template< class DataType, template< class DT, class ... Args > class Container, class ... Args >
typename BinaryTreeNode< DataType >::BinaryTreeNodePtr
CreateMinimalBST( Container< DataType, Args... >& container, typename Container< DataType, Args... >::iterator b, typename Container< DataType, Args... >::iterator e )
{
   if( b == e )
   {
      if( b == container.end() )
      {
         return nullptr;
      }

      return BinaryTreeNode< DataType >::CreateBinaryTreeNode( std::move( *b ) );;
   }

   auto mid = b;
   std::advance( mid, std::distance( mid, e ) / 2 );

   auto root = BinaryTreeNode< DataType >::CreateBinaryTreeNode( std::move( *mid ) );

   auto le = mid;
   std::advance( le, std::max( 0, std::distance( b, mid ) - 1 ) );
   root->SetLeftChild( CreateMinimalBST( container, b, le ) );

   std::advance( mid, 1 );
   root->SetRightChild( CreateMinimalBST( container, mid, e ) );

   return root;
}

template< class DataType, template< class DT, class ... Args > class Container, class ... Args >
typename BinaryTreeNode< DataType >::BinaryTreeNodePtr
CreateMinimalBST( Container< DataType, Args... > container, bool containerIsSorted )
{
   if( container.empty() )
   {
      return nullptr;
   }

   if( containerIsSorted == false )
   {
      container.sort();
   }

   return CreateMinimalBST( container, container.begin(), container.end() );
}


} // enf of MyDataStructuresImpl