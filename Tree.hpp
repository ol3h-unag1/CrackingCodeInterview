#pragma once


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


namespace 
{

struct HeightAndPredicate
{
   std::size_t height = 0u;
   bool predicate = true;
};

template< class NodeType >
HeightAndPredicate IsBalancedBinarySearchTree_Private( NodeType const root, HeightAndPredicate hap = {} )
{
   if( root == nullptr )
   {
      return hap;
   }

   if( root->GetLeftChild() && ( *root->GetLeftChild()->GetData() > *root->GetLeftChild()->GetData() ) )
   {
      return { 0u, false };
   }

   if( root->GetRightChild() && ( *root->GetRightChild()->GetData() < *root->GetLeftChild()->GetData() ) )
   {
      return { 0u, false };
   }

   auto left = IsBalancedBinarySearchTree_Private( root->GetLeftChild(), { hap.height + 1, true } );
   auto right = IsBalancedBinarySearchTree_Private( root->GetRightChild(), { hap.height + 1, true } );

   return { std::max( left.height, right.height ), left.predicate && right.predicate };
}

} // and of anonymous namespace

template< class NodeType >
bool IsBalancedBinarySearchTree( NodeType const root )
{
   if( root == nullptr )
   {
      return false;
   }

   auto left = IsBalancedBinarySearchTree_Private( root->GetLeftChild() );
   if( left.predicate == false )
   {
      return false;
   }

   auto right = IsBalancedBinarySearchTree_Private( root->GetRightChild() );
   if( right.predicate == false )
   {
      return false;
   }

   return ( std::max( left.height, right.height ) - std::min( left.height, right.height ) < 2 );
}


} // enf of MyDataStructuresImpl