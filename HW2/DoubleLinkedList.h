
#ifndef HW2_WET_DOUBLELINKEDLIST_H
#define HW2_WET_DOUBLELINKEDLIST_H
#include <iostream>
#include <istream>
#include <ostream>
using std::ostream;
using std::endl;

template<class T>
class NodeList {          
    T* element;
    NodeList* next_node;
    NodeList* prev_node;

public:

    explicit NodeList(T* element): element(element), next_node(nullptr), prev_node(nullptr){
    }
    ~NodeList(){
        delete this->element;
    }
    
    NodeList* remove_node_from_list(NodeList*& first, NodeList*& last){
        if(this == first){
        first = first->get_next();
        if(this->get_next()== nullptr){
            last = nullptr;
        }
        delete this;
        return nullptr;
        }
        if(this->next_node != nullptr && this->prev_node != nullptr){
            this->next_node->prev_node = this->prev_node;
            this->prev_node->next_node = this->next_node;
            delete this;
        }
        else if(this->prev_node != nullptr){
            this->prev_node->next_node = nullptr;
            last = this->prev_node;
            this->prev_node = nullptr;
            delete this;
        }
        return nullptr;
    }
    
    NodeList* get_next(){
        return next_node;
    }
    NodeList* get_prev(){
        return prev_node;
    }
    T* get_element(){
        return this->element;
    }
    int get_key(){
        return this->element->get_key();
    }
    void set_next(NodeList* element){
        this->next_node = element;
    }
    void set_prev(NodeList* element){
        this->prev_node = element;
    }    
//    StatusType insert_course_with_lectures(int id, AVLTree<int, Lecture>* lecture);
//    NodeList* insert_before(int new_time , int classID , int courseID,bool flag);
//    void display();
//    AVLTree<int, Course>* nodeList_get_tree();
};



template<class T>
class List{
    NodeList<T>* first;
    NodeList<T>* last;
public:
    List():first(nullptr), last(nullptr){
        
    }
    ~List(){
        while(this->first != nullptr){
        NodeList<T>* tmp = this->first;
        this->first = this->first->get_next();
        if(tmp!= nullptr){
            delete tmp;
            tmp= nullptr;
            }
        }
    }
//    friend ostream& operator<<(ostream& os,const List& list){
//        NodeList<T>* tmp = list.first;
//        if(tmp == nullptr) return os;
//        os << "first: " << tmp->get_key() << " , " << "last: " << list.last->get_key() <<endl;
//
//        while(tmp!= nullptr){
//            os << "key: " << *tmp->get_element();
//            tmp = tmp->get_next();
//        }
//        return os;
//    }
    NodeList<T>* get_first(){
        return this->first;
    }
    NodeList<T>* get_last(){
        return this->last;
    }
    void set_last(NodeList<T>* to_change){
        this->last = to_change;
    }
    void set_first(NodeList<T>* to_change){
        this->first = to_change;
    }
    
    T* find(int key){
     NodeList<T>* head = this->first;
     while(head != nullptr){
         if(head->get_key() == key){
             return head->get_element();
         }
         head=head->get_next();
     }
     return nullptr;
    }

    void push_back_node(NodeList<T>* element){
        NodeList<T>* first = this->get_first();
        if(first==nullptr){
            this->first = element;
            this->last = element;
            element->set_prev(nullptr);
            element->set_next(nullptr);
        }
        else{
            element->set_prev(nullptr);
            element->set_next(first);
            first->set_prev(element);
            this->first = element;
        }
    }

    void push_back(T* element){
        NodeList<T>* new_node = new NodeList<T>(element);
        NodeList<T>* first = this->get_first();
        if(first==nullptr){
            this->first = new_node;
            this->last = new_node;
        }
        else{
            new_node->set_next(first);
            first->set_prev(new_node);
            this->first = new_node;
        }
    }
    bool remove(int element){
        NodeList<T>* head=first;
        while(head!= nullptr){
        if(head->get_key()==element){
            head->remove_node_from_list(first,last);
            return true;
        }
        head=head->get_next();
        }
        return false;
    }
};

#endif //HW2_WET_DOUBLELINKEDLIST_H
