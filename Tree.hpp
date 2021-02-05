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
std::size_t BinaryTreeHeight( NodeType const root, std::size_t height = 0 )
{
   if( root == nullptr )
   {
      return height;
   }

   auto leftHeight = BinaryTreeHeight( root->GetLeftChild(), height + 1 );
   auto rightHeight = BinaryTreeHeight( root->GetRightChild(), height + 1 );

   return std::max( leftHeight, rightHeight );
}

template< class NodeType >
bool IsBalancedBinaryTree( NodeType const root )
{
   if( root == nullptr )
   {
      return false;
   }


   return false;
}



} // enf of MyDataStructuresImpl