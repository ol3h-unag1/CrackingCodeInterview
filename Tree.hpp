#pragma once

#include <algorithm>

#include <iostream>


namespace MyDataStructuresImpl
{


template< class DataType >
class BinaryTreeNode
{
public:
   using DataPtrType = std::shared_ptr< DataType >;
   using BinaryTreeNodePtrType = std::shared_ptr< BinaryTreeNode >;

private:
   struct MakeSharedEnabler : BinaryTreeNode< DataType >
   {
      MakeSharedEnabler( DataPtrType data ) : BinaryTreeNode( data ) {}
   };

private:
   explicit BinaryTreeNode( DataPtrType data )
      : _leftChild( nullptr )
      , _rightChild( nullptr )
      , _data( data )
   {}

public:   
   template< class U >
   static
   BinaryTreeNodePtrType CreateBinaryTreeNode( U&& data )
   {
      return std::make_shared< MakeSharedEnabler >( std::make_shared< U >( std::forward< U >( data ) ) );
   }

public:
   BinaryTreeNodePtrType GetLeftChild() const { return _leftChild; }
   BinaryTreeNodePtrType SetLeftChild( BinaryTreeNodePtrType node ) 
   { 
      _leftChild = node; 
      return _leftChild;
   }

   BinaryTreeNodePtrType GetRightChild() const { return _rightChild; }
   BinaryTreeNodePtrType SetRightChild( BinaryTreeNodePtrType node ) 
   { 
      _rightChild = node;
      return _rightChild;
   }

   DataPtrType GetData() const { return _data; };

private:
   BinaryTreeNodePtrType _leftChild;
   BinaryTreeNodePtrType _rightChild;

   DataPtrType _data;
};

class BinaryTreeFunctions
{
public:
   template< class NodeType >
   static
   bool IsBST( NodeType const root )
   {
      if( root == nullptr )
      {
         return false;
      }

      return IsBST_Impl( root, nullptr, nullptr );
   }

   template< class NodeType >
   static
   bool IsBalancedBST( NodeType const root )
   {
      if( root == nullptr )
      {
         return false;
      }

      auto left = IsBalancedBST_Impl( root->GetLeftChild() );
      if( left.predicate == false )
      {
         return false;
      }

      auto right = IsBalancedBST_Impl( root->GetRightChild() );
      if( right.predicate == false )
      {
         return false;
      }

      return ( std::max( left.height, right.height ) - std::min( left.height, right.height ) < 2 );
   }

   template< class DataType, template< class DT, class ... Args > class Container, class ... Args >
   typename BinaryTreeNode< DataType >::BinaryTreeNodePtrType
   static
   CreateMinimalBST( Container< DataType, Args... > container, bool needSort )
   {
      if( container.empty() )
      {
         return nullptr;
      }

      if( needSort )
      {
         std::sort( std::begin( container ), std::end( container ) );
      }

      return CreateMinimalBST_Impl( container, 0, static_cast< int >( container.size() ) - 1 );
   }

private:
   template< class NodeType >
   static
   bool IsBST_Impl( NodeType const root, typename std::remove_reference_t< decltype(*root) >::DataPtrType const min, typename std::remove_reference_t< decltype( *root ) >::DataPtrType const max )
   {
      if( root == nullptr )
      {
         return true;
      }

      if( min != nullptr && ( *root->GetData() <= *min ) )
      {
         return  false;
      }

      if( max != nullptr && ( *root->GetData() > *max ) )
      {
         return  false;
      }

      return IsBST_Impl( root->GetLeftChild(), nullptr, root->GetData() ) && IsBST_Impl( root->GetRightChild(), root->GetData(), nullptr );
   }

   // template< class Container >
   // typename BinaryTreeNode< typename std::remove_reference_t< Container >::value_type >::BinaryTreeNodePtr 
   // CreateMinimalBST( Container&& container )
   // {
   // 
   // }
   // above commented lines are the way to declare CreateMinimalBST less verbose than code used below 
   // thou above declaration is dependent on Container::value_type
   template< class DataType, template< class DT, class ... Args > class Container, class ... Args >
   typename BinaryTreeNode< DataType >::BinaryTreeNodePtrType
   static
   CreateMinimalBST_Impl( Container< DataType, Args... >& container, int start, int end )
   {
      if( end < start )
      {
         return nullptr;
      }

      int mid = ( start + end ) / 2;
      auto root = BinaryTreeNode< DataType >::CreateBinaryTreeNode( std::move( container[ mid ] ) );
      root->SetLeftChild( CreateMinimalBST_Impl( container, start, mid - 1 ) );
      root->SetRightChild( CreateMinimalBST_Impl( container, mid + 1, end ) );

      return root;
   }

   // helper struct 
   struct HeightAndPredicate
   {
      std::size_t height = 0u;
      bool predicate = true;
   };

   template< class NodeType >
   static
   HeightAndPredicate IsBalancedBST_Impl( NodeType const root, HeightAndPredicate hap = {} )
   {
      if( root == nullptr || hap.predicate == false )
      {
         return hap;
      }

      if( root->GetLeftChild() && ( *root->GetLeftChild()->GetData() > *root->GetData() ) )
      {
         return { hap.height, false };
      }

      if( root->GetRightChild() && ( *root->GetRightChild()->GetData() <= *root->GetData() ) )
      {
         return { hap.height, false };
      }

      auto left = IsBalancedBST_Impl( root->GetLeftChild(), { hap.height + 1, true } );
      auto right = IsBalancedBST_Impl( root->GetRightChild(), { hap.height + 1, true } );

      return { std::max( left.height, right.height ), left.predicate && right.predicate };
   }

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

   return ( std::abs( leftHeight - rightHeight ) < 2 );
}

// tests
//auto createRandomIntNode = []( int const min, int const max ) { return MyDataStructuresImpl::BinaryTreeNode< int >::CreateBinaryTreeNode( RandomInt( min, max ) ); };
//auto createNodeFromValue = []( auto&& value ) { return MyDataStructuresImpl::BinaryTreeNode< int >::CreateBinaryTreeNode( std::forward< std::remove_reference_t< decltype( value ) > >( value ) ); };

//auto r = createNodeFromValue( 100 );
//auto rL = r->SetLeftChild( createNodeFromValue( 75 ) );
//auto rR = r->SetRightChild( createNodeFromValue( 125 ) );
//auto rLL = rL->SetLeftChild( createNodeFromValue( 75 ) );
//auto rLLL = rLL->SetLeftChild( createNodeFromValue( 25 ) );
//auto rLLLL = rLLL->SetLeftChild( createNodeFromValue( 10 ) );
//
//std::cout << "MyDataStructuresImpl::BinaryTreeHeight: " << MyDataStructuresImpl::BinaryTreeHeight( r ) << std::endl;
//std::cout << "MyDataStructuresImpl::IsBalancedBinaryTree: " << MyDataStructuresImpl::IsBalancedBinaryTree( r ) << std::endl;
//std::cout << "MyDataStructuresImpl::MyDataStructuresImpl::BinaryTreeFunctions::IsBST: " << MyDataStructuresImpl::BinaryTreeFunctions::IsBST( r ) << std::endl;
//std::cout << "MyDataStructuresImpl::MyDataStructuresImpl::BinaryTreeFunctions::IsBalancedBST: " << MyDataStructuresImpl::BinaryTreeFunctions::IsBalancedBST( r ) << std::endl;
//
//std::vector< int > numbersVector;
//for( int i = 0; i < 15; ++i )
//{
//   numbersVector.push_back( i );
//}
//
//auto bstRoot = MyDataStructuresImpl::BinaryTreeFunctions::CreateMinimalBST( numbersVector, true );
//std::cout << " CreateMinimalBST " << std::endl;
//std::cout << "MyDataStructuresImpl::BinaryTreeHeight: " << MyDataStructuresImpl::BinaryTreeHeight( bstRoot ) << std::endl;
//std::cout << "MyDataStructuresImpl::IsBalancedBinaryTree: " << MyDataStructuresImpl::IsBalancedBinaryTree( bstRoot ) << std::endl;
//std::cout << "MyDataStructuresImpl::MyDataStructuresImpl::BinaryTreeFunctions::IsBST: " << MyDataStructuresImpl::BinaryTreeFunctions::IsBST( bstRoot ) << std::endl;
//std::cout << "MyDataStructuresImpl::MyDataStructuresImpl::BinaryTreeFunctions::IsBalancedBST: " << MyDataStructuresImpl::BinaryTreeFunctions::IsBalancedBST( bstRoot ) << std::endl;

} // enf of MyDataStructuresImpl