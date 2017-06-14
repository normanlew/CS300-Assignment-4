// Norman Lew
// CS 300
// Spring 2017

// Assignment 4

// This assignment adds the function isAVL() to the BinarySearchTree class.  isAVL() checks to see if the tree is an AVL tree.


#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// bool isAVL()           --> Returns whether the Binary Search Tree is an AVL tree
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
/**
 * Move assignment
 */
BinarySearchTree & operator=(BinarySearchTree && rhs)
{
	std::swap(root, rhs.root);
	return *this;
}


/**
 * Find the smallest item in the tree.
 * Throw UnderflowException if empty.
 */
const Comparable & findMin() const
{
	if (isEmpty())
		throw UnderflowException{ };
	return findMin(root)->element;
}

/**
 * Find the largest item in the tree.
 * Throw UnderflowException if empty.
 */
const Comparable & findMax() const
{
	if (isEmpty())
		throw UnderflowException{ };
	return findMax(root)->element;
}

/**
 * Returns true if x is found in the tree.
 */
bool contains(const Comparable & x) const
{
	return contains(x, root);
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
bool isEmpty() const
{
	return root == nullptr;
}

/**
 * Print the tree contents in sorted order.
 */
void printTree(ostream & out = cout) const
{
	if (isEmpty())
		out << "Empty tree" << endl;
	else
		printTree(root, out);
}

/**
 * Make the tree logically empty.
 */
void makeEmpty()
{
	makeEmpty(root);
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
void insert(const Comparable & x)
{
	insert(x, root);
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
void insert(Comparable && x)
{
	insert(std::move(x), root);
}

/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
void remove(const Comparable & x)
{
	remove(x, root);
}

/**
* Returns whether the Binary Search Tree is an AVL tree.
*/
bool isAVL()
{
	// This variable is used to store whether the tree is an AVL tree.  It is also returned from the function.  It will also be
	// used as a variable to pass into helper functions to see see if other nodes are balanced in the tree.
	bool treeIsAVL = true;

	// If the root node is unbalanced, it is not an AVL tree.  We can stop the function here and return false.
	if (!(abs(height(root->left) - height(root->right)) <= 1))
	{
		treeIsAVL = false;
	}

	// If the root node is balanced, check all other nodes for balance
	if (treeIsAVL)
	{
		nodeIsBalanced(treeIsAVL, root->left);
		nodeIsBalanced(treeIsAVL, root->right);
	}

	return treeIsAVL;
}



  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;

	// Internal method to return the height of a node 
	// (Note, this is not the height in the traditional tree-sense of the word, but it works for our purposes, which is to generate
	// a number used in a calculation to see if a tree or subtree is balanced).
	int height(BinaryNode *c)
	{
		if (c == NULL)
			return 0;
		else
			return (1 + max(height(c->left), height(c->right)));
	}

	// Internal method to see if a node is balanced.  Instead of returning a boolean value, it will change the boolean value that
	// is passed to the method.  It also checks to see if all other nodes below it are balanced as well.
	void nodeIsBalanced(bool &c, BinaryNode *d)
	{
		if (c == true)
		{
			if (d != NULL)
			{
				if (!(abs(height(d->left) - height(d->right)) <= 1))
				{
					c = false;
					return;
				}
					
				nodeIsBalanced(c, d->left);
				nodeIsBalanced(c, d->right);
			}
				
		}
	}


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
