
#ifndef HW1_WET_AVLTREE_H
#define HW1_WET_AVLTREE_H
#include "iostream"

using namespace std;


template <class S>
class Node {
private:
    int rank; 
    S* value;
    int height;
    Node* right_node;
    Node* left_node;
    Node* parent;

public:
    Node(S* value) : rank(1), value(value) ,height(0) ,right_node(nullptr), left_node(nullptr), parent(nullptr) {
    }
    int max_node(int a, int b){
        return a>b ? a:b;
    }
    int node_get_rank(){
        return this->rank;
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
        Node* left_son = this->left_node;
        Node* tmp = nullptr;
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
        this->update_rank();
        left_son->update_height();
        left_son->update_rank();


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
        this->update_rank();
        right_son->update_height();
        right_son->update_rank();


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
        this->update_rank();
        if(left_son->left_node == nullptr && left_son->right_node == nullptr){
            left_son->height = 0;
        }
        else{
            left_son->update_height();
        }
        left_son->update_rank();
        left_right_son->update_height();
        left_right_son->update_rank();

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
        this->update_rank();
        if(right_son->left_node == nullptr && right_son->right_node == nullptr){
            right_son->height = 0;
        }
        else{
            right_son->update_height();
        }
        right_son->update_rank();

        right_left_son->update_height();
        right_left_son->update_rank();

        return right_left_son;  
    }
    void update_rank(){
        this->rank = 1;
        if(this->left_node!=nullptr){
            this->rank += this->left_node->rank;
        }
        if(this->right_node!=nullptr){
            this->rank += this->right_node->rank;
        }
    }
    Node* insert(S* value, bool* flag, Node*& smallest, bool* inserted){            //  NODE insert
        Node* root = nullptr;
        if(*this->value == *value){
            return nullptr;
        }
        if(!(*this->value < *value)){
            if(this->left_node == nullptr){                          // no left node 
                this->left_node = new Node(value);
                *inserted = true;
                this->left_node->parent = this;
                if(smallest == this){
                    smallest = this->left_node;
                }
            }
            else{
                this->left_node->insert(value, flag, smallest, inserted);
            }
            this->update_height();
            this->update_rank();
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
                this->right_node = new Node(value);
                *inserted = true;
                this->right_node->parent = this;
            }
            else{
                this->right_node->insert(value, flag, smallest, inserted);
            }
            this->update_height();
            this->update_rank();
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
    Node* remove(S* value, bool* change_root, Node*& smallest, bool* removed){                                    //Node remove
        Node* old_root = nullptr;
        if(this == nullptr){
            return this;
        }
        if(*this->value < *value){                          //search in right subtree
            this->right_node->remove(value, change_root, smallest, removed);
        }
        else if(!(*this->value < *value) && !(*this->value == *value)){                      //search in left subtree
            this->left_node->remove(value, change_root, smallest, removed);
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
                        if(smallest==this && this->right_node == nullptr){ //need to repair
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
                    *removed = true;
                    return tmp;
                }
                delete this;
                *removed = true;
                return nullptr;
            }
            else{                                                 // 2 childrens exists
                 // find max key in the left child tree
                Node* tmp = this->left_node;
                while(tmp->right_node!=nullptr){
                    tmp = tmp->right_node;
                }
                S* temp;
                temp=this->value;
                this->value = tmp->value;
                tmp->value = temp;
                 this->left_node->remove(tmp->value, change_root, smallest, removed);    //check for the max value in the left sub tree
            }
        }
        //update height and check for rotation
        if(this->right_node == nullptr && this->left_node == nullptr){
            this->height=0;
        }
        else{
            this->update_height();
        }
        this->update_rank();
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
//    ostream& print_node(ostream& os){
//        if(this == nullptr) return os;
//        if(this->left_node!=nullptr){
//            this->left_node->print_node(os);
//        }
//        os  << " Value: " << *this->value << " Rank: " << this->rank << endl;
//        if(this->right_node!=nullptr){
//            this->right_node->print_node(os);
//        }
//        return os;
//    }
    S* find_node(S* value){                                            //Node Insert
        if(this==nullptr){
            return nullptr;
        }
        if(this->value == *value){
            return this->value;
        }
        else if(!(this->value < value)){
            return this->left_node->find_node(value);
        }
        else return this->right_node->find_node(value);
    }
};




//AVL TREE
template <class S>
class AVLTree {
    int numOfElements;
    Node<S>* root;
    Node<S>* smallest;

public:
    AVLTree();
    void insert(S* value);
    void remove(S* value);
    int avl_get_height();
    Node<S>* get_root();

    S* find(S* value);
    int tree_get_elements_num();
    bool is_empty();
    ~AVLTree();
    //    void print_in_order();
    //    friend ostream& operator<<(ostream& os, const AVLTree& avlTree){
    //        return avlTree.root->print_node(os);
    //    }
};


template <class S>
AVLTree<S>::AVLTree() : numOfElements(0), root(nullptr), smallest(nullptr) {
}


template <class S>
Node<S>* AVLTree<S>::get_root(){
    if(this!= nullptr){
        return this->root;
    }
    return nullptr;
}


template <class S>
void AVLTree<S>::insert(S* value){                               //  AVL insert
    Node<S>* tmp = nullptr;
    if(this->root !=  nullptr){
        bool change_root = false;
        bool inserted = false;
        tmp = this->root->insert(value, &change_root, this->smallest, &inserted);
        if(change_root){
            this->root = tmp;
        }
        if(inserted == true){
            this->numOfElements++;
        }
    }
    else{
        tmp = new Node<S>(value);
        this->root = tmp;
        this->smallest = tmp;
        this->numOfElements++;
    }
}


template <class S>
void AVLTree<S>::remove(S* value){
    if(this->root != nullptr){
        bool change_root = false;
        bool removed = false;;
        Node<S>* tmp = this->root->remove(value, &change_root, this->smallest, &removed);
        if(change_root){
            this->root = tmp;
        }
        if(removed){
            this->numOfElements -= 1;
        }
    }
}



template <class S>
int AVLTree<S>::avl_get_height(){
    return this->root->node_get_height();
}


template <class S>
bool AVLTree<S>::is_empty(){
    if (this->root == nullptr){
        return true;
    }
    return false;
}


template <class S>
AVLTree<S>::~AVLTree()
{
    this->smallest= nullptr;
    if (this->root != nullptr){
        delete this->root;
        this->root= nullptr;
    }
}


//template <class S>
//void AVLTree<S>::print_in_order(){
//    this->root->print_node(cout);
//}


template <class S>
S* AVLTree<S>::find(S* value){
    S* new_value = this->root->find_node(value);
    return new_value;
}

template <class S>
int AVLTree<S>::tree_get_elements_num(){
    return this->numOfElements;
}


#endif //HW1_WET_AVLTREE_H
