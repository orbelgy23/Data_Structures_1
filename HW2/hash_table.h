
#ifndef HW2_WET_HASH_TABLE_H
#define HW2_WET_HASH_TABLE_H

#include "DoubleLinkedList.h"

template<class T>
class HashTable {

    //some private fields
    int curr_size;
    int max_size;
    List<T>** arr;

    //some private methods
    void shrink(){
        int prev_size = max_size;
        max_size = get_prev_prime(max_size);
        List<T>** tmp = arr;
        arr = new List<T>*[max_size];
        for(int i = 0 ; i < max_size ; i++){
            arr[i] = new List<T>();
        }
        for(int i = 0 ; i < prev_size ; i++){
            NodeList<T>* head = tmp[i]->get_first();
            while(head != nullptr){
                NodeList<T>* node_to_move = head;
                head=head->get_next();
                arr[node_to_move->get_key() % max_size]->push_back_node(node_to_move);
            }
            tmp[i]->set_first(nullptr);
            tmp[i]->set_last(nullptr);
            delete tmp[i];
        }
        delete[] tmp;
    }

    void extend(){
        int prev_size = max_size;
        max_size = get_double_next_prime(max_size);
        List<T>** tmp = arr;
        arr = new List<T>*[max_size];
        for(int i = 0 ; i < max_size ; i++){
            arr[i] = new List<T>();
        }
        for(int i = 0 ; i < prev_size ; i++){
            NodeList<T>* head = tmp[i]->get_first();
            while(head!= nullptr){
                NodeList<T>* node_to_move = head;
                head=head->get_next();
                arr[node_to_move->get_key() % max_size]->push_back_node(node_to_move);
            }
            tmp[i]->set_first(nullptr);
            tmp[i]->set_last(nullptr);
            delete tmp[i];
        }
        delete[] tmp;
    }

public:

    //some public methods
    HashTable() : curr_size(0),max_size(7),arr(nullptr){          //init
        arr = new List<T>*[7];
        for(int i=0;i<7;i++){
            arr[i] = new List<T>();
        }
    }
    static bool is_prime(int prime){
        for (int i = 2; i < prime; i++)
        {       
            if(prime%i==0){
                return false;
            }
        }
        return true;
        
    }
    static int get_double_next_prime(int prime){
        int next_prime = 2*prime;
        while (true){
            if(is_prime(next_prime)){
                return next_prime;
            }
            next_prime++;
        }
        return -1;
    }
    static int get_prev_prime(int prime){
        int prev_prime = prime/2;
        while (prev_prime>1){
            if(is_prime(prev_prime)){
                return prev_prime;
            }
            prev_prime--;
        }
        return prime;
    }


    void remove(int element){
        bool is_found = arr[element%max_size]->remove(element);
        if(is_found) curr_size--;
        if(max_size/2 >= curr_size && max_size > 7){
            shrink();
        }
    }
    int get_curr_size(){
        return curr_size;
    }

    void add(T* element){
        int key = element->get_key();
        T* exist = arr[key % max_size]->find(key);
        if(exist == nullptr){
            arr[key % max_size]->push_back(element);
            curr_size++;
        }
        if(2*max_size <= curr_size){
            extend();
        }
    }
    
    T* find(int key){
        return arr[key%max_size]->find(key);
    }

//    void print_hash(){
//        for(int i=0 ; i < max_size ; i++){
//            std::cout << "i: " << i << " " << *this->arr[i] << std::endl;
//        }
//    }

//    friend ostream& operator<<(ostream& os, HashTable<T>& table){
//        table.print_hash();
//        return os;
//    }

    ~HashTable(){
        for(int i=0 ; i < this->max_size ; i++){
            delete this->arr[i];
        }
        delete[] arr;
    }
    
};



#endif //HW2_WET_HASH_TABLE_H
