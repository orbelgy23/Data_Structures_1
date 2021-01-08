
#ifndef HW1_WET_BOOM_H
#define HW1_WET_BOOM_H


#include "AVLTree.h"
#include "library.h"




class ZeroTreeNode{
    int arr_size;
    int false_cells;
    bool* bool_arr;
public:
    explicit ZeroTreeNode(int numOfClasses);
    ~ZeroTreeNode();
    void set_zero_node_bool(int id);
    int get_false_cells();
    bool* zero_node_get_arr();
    int get_arr_size();
};




class Lecture{
    int id;
public:
    explicit Lecture(int id);
    friend ostream& operator<<(ostream& os,const Lecture& lecture){
        os << "Lecture number: " << lecture.id;
        return os;
    }
    ~Lecture();
};




class Course{
    int id;
    AVLTree<int, Lecture>* lectures;
public:
    Course(int id, AVLTree<int, Lecture>* lectures);
    friend ostream& operator<<(ostream& os,const Course& course){
        os << endl << "Course id " << course.id <<endl;
        os << *course.lectures <<endl;
        return os;
    }
    StatusType add_lecture(int id);
    AVLTree<int, Lecture>* course_get_tree();
    StatusType remove_lecture(int id);
    ~Course();

};




class NodeList {
    int key;
    AVLTree<int, Course>* tree_courses;
    NodeList* next_node;
    NodeList* prev_node;

public:
    explicit NodeList(int key);
    ~NodeList();
    StatusType insert_course_with_lectures(int id, AVLTree<int, Lecture>* lecture);
    NodeList* insert_before(int new_time , int classID , int courseID,bool flag);
    NodeList* remove_node_from_list();
    NodeList* get_next();
    NodeList* get_prev();
    void display();
    int get_key();
    AVLTree<int, Course>* nodeList_get_tree();
};




class List{
    NodeList* first;
    NodeList* last;
public:
    List();
    ~List();
    friend ostream& operator<<(ostream& os,const List& list){
        NodeList* tmp = list.first;
        while(tmp!= nullptr){
            os << "Time: " << tmp->get_key() <<endl;
            os << *tmp->nodeList_get_tree() << endl;
            tmp = tmp->get_next();
        }
        return os;
    }
    NodeList* get_first();
    NodeList* get_last();
    void set_last(NodeList*);
    NodeList* insert_before(NodeList* node_list ,int new_time , int classID , int CourseID);
};




class lecturesOfCourse{
    int courseID;
    int numOfClasses;
    NodeList** arr;
public:
    lecturesOfCourse(int numOfClasses,int courseID);
    void set_arr(NodeList* node_list);
    ~lecturesOfCourse();
    NodeList* get_node_from_list(int index);
    int get_num_of_classes();
    NodeList** get_arr();
    void set_node_in_list(int class_id, NodeList* node_list);
    friend ostream& operator<<(ostream& os, const lecturesOfCourse& lecturesOfCourse1){
        os << lecturesOfCourse1.courseID;
        return os;
    }
};




class Boom{
    AVLTree<int, lecturesOfCourse>* main_tree;
    List* priority_list;
    AVLTree<int, ZeroTreeNode>* zero_tree;
public:
    Boom();
    ~Boom();
    StatusType AddCourse (int courseID, int numOfClasses);
    StatusType RemoveCourse( int courseID);
    StatusType TimeViewed(int courseID, int classID, int* timeViewed);
    StatusType WatchClass(int courseID, int classID, int time);
    StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes);
    friend ostream& operator<<(ostream& os,const Boom& boom){
        os << *boom.main_tree <<endl;
        os << *boom.priority_list;
        return os;
    }
};




#endif //HW1_WET_BOOM_H
