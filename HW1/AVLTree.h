
#ifndef HW1_WET_AVLTREE_H
#define HW1_WET_AVLTREE_H
#include "iostream"

using namespace std;


template <class T, class S>
class Node {
private:
    T key;
    S* value;
    int height;
    Node* right_node;
    Node* left_node;
    Node* parent;

public:
    Node(T key, S* value) : key(key), value(value) ,height(0) ,right_node(nullptr), left_node(nullptr), parent(nullptr) {
    }
    int max_node(int a, int b){
        return a>b ? a:b;
    }
    T node_get_key(){
        return this->key;
    }
    S* node_get_value(){
        return this->value;
    }
    Node* node_get_parent(){
        return this->parent;
    }
    int node_get_height(){
        return this->height;
    }
    Node* node_get_left(){
        if(this != nullptr){
            return this->left_node;
        }
        return nullptr;
    }
    Node* node_get_right(){
        if(this != nullptr){
            return this->right_node;
        }
        return nullptr;

    }
    void update_height(){
        int r_height = 0;
        int l_height = 0;
        if(this!= nullptr){
            if (this->right_node!= nullptr){
                r_height = this->right_node->height;
            }
            if (this->left_node!= nullptr){
                l_height = this->left_node->height;
            }
            this->height = max_node(r_height,l_height) + 1;
        }
    }
    int get_balanced_factor(){
        if(this!= nullptr){
            if(this->left_node == nullptr){
                if(this->right_node == nullptr){
                    return 0;
                }
                return (-1) * this->right_node->height-1;
            }
            else{
                if(this->right_node== nullptr){
                    return this->left_node->height+1;
                }
                return (this->left_node->height) - (this->right_node->height);
            }
        }
        return 0;
    }
    Node* LL_Rotation(bool* change_root ){                        // LL rotation
        Node<T,S>* left_son = this->left_node;
        Node<T,S>* tmp = nullptr;
        if(this->parent == nullptr){
            *change_root = true;
        }
        else{
            if(this->parent->left_node == this){
                this->parent->left_node = left_son;
            }
            else{
                this->parent->right_node = left_son;
            }
        }
        if(left_son->right_node != nullptr){
            tmp = left_son->right_node;
            this->left_node = tmp; // update son of the right node
            tmp->parent = this; //update the parent of the right node
            left_son->parent = this->parent; //update the parent of the new root
            this->parent = left_son; //update the parent of the old root to be the new root
            left_son->right_node = this; //update the son of the left right node the be the old root
        }
        else{
            left_son->parent = this->parent;
            this->parent = left_son;
            left_son->right_node = this;
            this->left_node = nullptr;    
        }
        if(this->left_node == nullptr && this->right_node == nullptr){
            
            this->height = 0;
        }
        else{
            this->update_height();
        }
        left_son->update_height();


        return left_son;
    }
    Node* RR_Rotation(bool* change_root ){                           // RR rotation
        Node* right_son = this->right_node;
        Node* tmp = nullptr;
        if(this->parent == nullptr){
            *change_root = true;
        }
        else{
            if(this->parent->left_node == this){
                this->parent->left_node = right_son;
            }
            else{
                this->parent->right_node = right_son;
            }
        }
        if(right_son->left_node != nullptr){
            tmp = right_son->left_node;
            this->right_node = tmp; // update son of the right node
            tmp->parent = this; //update the parent of the right node
            right_son->parent = this->parent; //update the parent of the new root
            this->parent = right_son; //update the parent of the old root to be the new root
            right_son->left_node = this; //update the son of the left right node the be the old root
        }
        else{
            right_son->parent = this->parent;
            this->parent = right_son;
            right_son->left_node = this;
            this->right_node = nullptr;  
            //this->height = this->height-2;  
        }
        if(this->left_node == nullptr && this->right_node == nullptr){
            
            this->height = 0;
        }
        else{
            this->update_height();
        }
        right_son->update_height();

        return right_son;
    }
    Node* LR_Rotation(bool* change_root){                                          // LR rotation
        Node* left_son = this->left_node;
        // Node* right_son = this->right_node;
        Node* left_right_son = this->left_node->right_node;
        Node* left_right_right_son = left_right_son->right_node;
        Node* left_right_left_son = left_right_son->left_node;

        if(this->parent!=nullptr){
            if(this->parent->right_node == this){
                this->parent->right_node = left_right_son;
            }
            else{
                this->parent->left_node = left_right_son;
            }
        }
        else{
            *change_root = true;
        }
        left_right_son->parent = this->parent;

        left_son->parent = left_right_son;
        left_right_son->left_node = left_son;
        left_right_son->right_node = this;
        this->parent = left_right_son;
        this->left_node = left_right_right_son;
        if(left_right_right_son != nullptr){
            left_right_right_son->parent = this;
        }
        left_son->right_node = left_right_left_son;
        if(left_right_left_son != nullptr){
            left_right_left_son->parent = left_son;
        }
        if(this->left_node == nullptr && this->right_node == nullptr){
            this->height = 0;
        }
        else{
            this->update_height();
        }
        if(left_son->left_node == nullptr && left_son->right_node == nullptr){
            left_son->height = 0;
        }
        else{
            left_son->update_height();
        }
        
        left_right_son->update_height();

        return left_right_son;  
    }
    Node* RL_Rotation(bool* change_root){                                          // RL rotation
        Node* right_son = this->right_node;
        Node* right_left_son = this->right_node->left_node;
        Node* right_left_left_son = right_left_son->left_node;
        Node* right_left_right_son = right_left_son->right_node;
        if(this->parent!=nullptr){
            if(this->parent->left_node == this){
                this->parent->left_node = right_left_son;
            }
            else{
                this->parent->right_node = right_left_son;
            }
        }
        else{
            *change_root = true;
        }
        right_left_son->parent = this->parent;

        right_son->parent = right_left_son;
        right_left_son->right_node = right_son;
        right_left_son->left_node = this;
        this->parent = right_left_son;
        this->right_node = right_left_left_son;
        if(right_left_left_son != nullptr){
            right_left_left_son->parent = this;
        }
        right_son->left_node = right_left_right_son;
        if(right_left_right_son != nullptr){
            right_left_right_son->parent = right_son;
        }
        if(this->left_node == nullptr && this->right_node == nullptr){
            this->height = 0;
        }
        else{
            this->update_height();
        }
        if(right_son->left_node == nullptr && right_son->right_node == nullptr){
            right_son->height = 0;
        }
        else{
            right_son->update_height();
        }
        right_left_son->update_height();
        return right_left_son;  
    }
    Node* insert(T key, S* value, bool* flag, Node*& smallest){            //  NODE insert
        Node* root = nullptr;
        if(this->key == key){
            return nullptr;
        }
        if(this->key > key){
            if(this->left_node == nullptr){                          // no left node 
                this->left_node = new Node(key, value);
                this->left_node->parent = this;
                if(smallest == this){
                    smallest = this->left_node;
                }
            }
            else{
                this->left_node->insert(key, value, flag, smallest);
            }
            this->update_height();
            if(this->get_balanced_factor() > 1){                       //check if LL/LR is needed
                if(this->left_node->get_balanced_factor() == - 1){         //LR 
                    root = this->LR_Rotation(flag);
                }
                else{                                                       //LL
                    root = this->LL_Rotation(flag);
                }
                return root;
            }
        }
        else{
            if(this->right_node == nullptr){                       // no right node 
                this->right_node = new Node(key, value);
                this->right_node->parent = this;
            }
            else{
                this->right_node->insert(key, value, flag, smallest);
            }
            this->update_height();
             if(this->get_balanced_factor() < -1){                   //check if RR/RL is needed
                
              if(this->right_node->get_balanced_factor() == 1){
                root = this->RL_Rotation(flag);                
              }
              else{
                    root = this->RR_Rotation(flag);          //RR
              }
              return root;
            }
        } 
        return root;
    }
    Node* remove(T key, bool* change_root, Node*& smallest){                                    //Node remove
        Node* old_root = nullptr;
        if(this == nullptr){
            return this;
        }
        if(this->key < key){                          //search in right subtree
            this->right_node->remove(key, change_root, smallest);
        }
        else if(this->key > key){                      //search in left subtree
            this->left_node->remove(key, change_root, smallest);
        }
        else{                                                                       //we found the element to destroy
            if(this->right_node == nullptr || this->left_node == nullptr){            //only 1 child or 0 children
                Node* tmp = nullptr; //added recently
                if(this->left_node == nullptr){             //no left node 
                    if(this->parent != nullptr){            //check if "this" isnt the root
                        if(this->parent->left_node == this){        //this , it is left son for his parent
                            this->parent->left_node = this->right_node;
                         } 
                        else{                                       //this , it is right son for his parent
                            this->parent->right_node = this->right_node;
                        }
                        if(smallest==this && this->right_node == nullptr){ 
                            smallest = this->parent;
                        }
                    }
                    if(this->right_node != nullptr){      //exactly 1 child
                        this->right_node->parent = this->parent;
                        if(smallest==this){
                            smallest=this->right_node;
                        }
                    }
                    if(this->parent == nullptr && this->right_node == nullptr && this->left_node == nullptr){
                        if(smallest==this){
                            smallest=this->right_node;
                        }
                    }
                    tmp = this->right_node;
                }
                else{                                         //no right node
                    if(this->parent != nullptr){            //check if "this" isnt the root
                        if(this->parent->left_node == this){                               
                            this->parent->left_node = this->left_node;   //this , it is left son for his parent
                         } 
                        else{
                            this->parent->right_node = this->left_node;    //this , it is right son for his parent
                        }
                    }
                    if(this->left_node != nullptr){
                        this->left_node->parent = this->parent;                               

                    }
                    tmp = this->left_node;
                }
                if(this->parent == nullptr){
                    *change_root = true;
                }
                this->parent = nullptr;
                this->left_node=nullptr;
                this->right_node=nullptr;
                if(this->parent== nullptr ){
                    delete this;
                    return tmp;
                }
                delete this;
                return nullptr;
            }
            else{                                                 // 2 childrens exists
                 // find max key in the left child tree
                 Node* tmp = this->left_node;
                 while(tmp->right_node!=nullptr){
                     tmp = tmp->right_node;
                 }
                 this->key = tmp->key;
                 S* temp;
                 temp=this->value;
                 this->value = tmp->value;
                 tmp->value = temp;
                this->left_node->remove(tmp->key, change_root, smallest);    //check for the max value in the left sub tree
            }
        }
        //update height and check for rotation
        if(this->right_node == nullptr && this->left_node == nullptr){
            this->height=0;
        }
        else{
            this->update_height();
        }
        if(this->get_balanced_factor() == 2 && this->left_node->get_balanced_factor() >= 0){    //LL
            old_root = this->LL_Rotation(change_root);
        }   

        if(this->get_balanced_factor() == 2 && this->left_node->get_balanced_factor() == - 1){ //LR
            old_root = this->LR_Rotation(change_root);
        }

        if(this->get_balanced_factor() == -2 && this->right_node->get_balanced_factor() <= 0){   //RR
            old_root = this->RR_Rotation(change_root);
        }    

        if(this->get_balanced_factor() == -2 && this->right_node->get_balanced_factor() == 1){   //RL
            old_root = this->RL_Rotation(change_root);
        }
        return old_root;
    }
    ~Node(){
        if(this->left_node!= nullptr){
            delete this->left_node;
            this->left_node= nullptr;
        }
        if(this->right_node!= nullptr){
            delete this->right_node;
            this->right_node= nullptr;
        }
        if(this->value!= nullptr){
            delete this->value;
            this->value= nullptr;
        }
    }
    ostream& print_node(ostream& os){
        if(this == nullptr) return os;
        if(this->left_node!=nullptr){
            this->left_node->print_node(os);
        }
        os <<  "id: " << this->key  << ", Value: " << *this->value << endl;
        if(this->right_node!=nullptr){
            this->right_node->print_node(os);
        }
        return os;
    }
    S* find_node(T key){                                            //Node Insert
        if(this==nullptr){
            return nullptr;
        }
        if(this->key == key){
            return this->value;
        }
        else if(this->key > key){
            return this->left_node->find_node(key);
        }
        else return this->right_node->find_node(key);
    }
};




//AVL TREE
template <class T, class S>
class AVLTree {

    Node<T,S>* root;
    Node<T,S>* smallest;

public:
    AVLTree();
    void insert(T key, S* value);
    void remove(T key);
    T* get_smallest_key();
    S* get_smallest_value();
    Node<T,S>* get_smallest_node();
    int avl_get_height();
    Node<T,S>* get_root();
    void print_in_order();
    friend ostream& operator<<(ostream& os, const AVLTree& avlTree){
        return avlTree.root->print_node(os);
    }
    S* find(T key);
    bool is_empty();
    ~AVLTree();
};


template <class T, class S>
AVLTree<T,S>::AVLTree() : root(nullptr), smallest(nullptr){
}


template <class T, class S>
Node<T,S>* AVLTree<T,S>::get_root(){
    if(this!= nullptr){
        return this->root;
    }
    return nullptr;
}


template <class T, class S>
void AVLTree<T,S>::insert(T key, S* value){                               //  AVL insert
    if(this->root !=  nullptr){
        bool change_root = false;
        Node<T,S>* tmp = this->root->insert(key, value, &change_root, this->smallest);
        if(change_root){
            this->root = tmp;
        }
    }
    else{
        Node<T,S>* tmp = new Node<T,S>(key, value);
        this->root = tmp;
        this->smallest = tmp;
    }
}


template <class T, class S>
void AVLTree<T,S>::remove(T key){
    if(this->root != nullptr){
        bool change_root = false;
        Node<T,S>* tmp = this->root->remove(key, &change_root, this->smallest);
        if(change_root){
            this->root = tmp;
        }
    }
}


template <class T, class S>
T* AVLTree<T,S>::get_smallest_key(){
    return this->smallest->node_get_key();
}


template <class T, class S>
S* AVLTree<T,S>::get_smallest_value(){
    return this->smallest->node_get_value();
}


template <class T, class S>
Node<T,S>* AVLTree<T,S>::get_smallest_node(){
    return this->smallest;
}


template <class T, class S>
int AVLTree<T,S>::avl_get_height(){
    return this->root->node_get_height();
}


template <class T, class S>
bool AVLTree<T,S>::is_empty(){
    if (this->root == nullptr){
        return true;
    }
    return false;
}


template <class T, class S>
AVLTree<T,S>::~AVLTree()
{
    this->smallest= nullptr;
    if (this->root != nullptr){
        delete this->root;
        this->root= nullptr;
    }
}


template <class T, class S>
void AVLTree<T,S>::print_in_order(){
    this->root->print_node();
}


template<class T,class S>
S* AVLTree<T,S>::find(T key){
    S* new_value = this->root->find_node(key);
    return new_value;
}


#endif //HW1_WET_AVLTREE_H
