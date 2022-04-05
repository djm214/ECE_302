#include "binary_search_tree.h"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    clone(rhs.root);
}

// this is an alternative implementation using a stack to simulate the recursion
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::clone(Node<KeyType, ItemType>* rhs)
{
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(const BinarySearchTree<KeyType, ItemType>& rhs)
{
    if (&rhs == this)
        return *this;

    destroy();

    root = 0;
    clone(rhs.root);

    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    Node<KeyType, ItemType>* curr = new Node<KeyType, ItemType>;
    Node<KeyType, ItemType>* prev = new Node<KeyType, ItemType>;
    Node<KeyType, ItemType>* standIn = new Node<KeyType, ItemType>;

    curr->data = item;
    curr->key = key;
    prev = 0; //set previous to null
    
    if(root == 0)
    {
        root = curr; //insert at the root
        return true;
    }

    standIn = root; //a standIn pointer for traversal to right insertion point

    while(standIn != 0)
    {
        if(key == standIn->data)
        {
            return false;
        }

        if(key < standIn->data)
        {
            prev = standIn; //set previous properlly
            standIn = standIn->left; //properlly progress standIn
        }
        else if(key > standIn->data)
        {
            prev = standIn; //set previous properlly
            standIn = standIn->right; //properlly progress standIn
        }
    }

    if(prev->data > key)
    {
        prev->left = curr; //set the pointer to be inserted to left
    }
    else
    {
        prev->right = curr; //set the pointer to be inserted to right
    }
    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
    {
        return false; // empty tree
    }

    // case one thing in the tree
    if(root->left == 0 && root->right == 0)
    {
        root = 0; //remove root
    }

    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    Node<KeyType, ItemType>* in;

    // case, found deleted item at leaf
    if(curr->left == 0 && curr->right == 0)
    {
        curr->data = 0;
        curr->key = 0;
    }

    // case, item to delete has only a right child
    if(curr->left == 0 && curr->right != 0)
    {
        curr = curr->right;
        curr->right = 0;
    }

    // case, item to delete has only a left child
    if(curr->left != 0 && curr->right == 0)
    {
        curr = curr->left;
        curr->left = 0;
    }

    // case, item to delete has two children
    if(curr->left != 0 && curr->right != 0)
    {
        inorder(curr_parent,in,curr);
    }

    return true; //insert succeeded
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    // move right once
    curr = parent;
    curr = curr->right;
    // move left as far as possible
    while(curr != 0)
    {
        in = curr; //will hold the leftmost before curr reaches null
        curr = curr->left; //traverses as left as possible unit it is null
    }

    parent->data = in->data;
    in = 0; //make in a nullptr

}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(ItemType arr[], int size) {
    //check for duplicate items in the input array
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if((arr[i] == arr[j]) && i != j)
            {
                throw(std::logic_error("there are duplicate items in the array"));
            }
        }
    }

    destroy();
    ItemType sortArray[size];

    //use the tree to sort the array items
    for(int i = 0; i < size; i++)
    {
        insert(arr[i],arr[i]);
    }

    //inorder traversal using stacks
    std::stack<Node<KeyType, ItemType>*> s;
    int i =0; //will keep track of loops in while
    Node<KeyType, ItemType>* curr = root;

    while(!s.empty())
    {
        while(curr != 0)
        {
            s.push(curr); //add current node to stack
            curr = curr->left; //progress the pointer
        }

        while(curr->right == 0)
        {
            curr = s.top(); //take top of stack
            s.pop(); //remove the nullptr in the stack

            sortArray[i] = curr->data; //adds to the sorted list
            i++; //increment i
        }
        curr = curr->right;
        sortArray[i] = curr->data
    }

    //overwrite input array values with sorted values
    for(int i = 0; i < size; i++)
    {
        arr[i] = sortArray[i];
    }
}
