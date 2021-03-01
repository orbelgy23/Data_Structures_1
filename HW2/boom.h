
#ifndef HW1_WET_BOOM_H
#define HW1_WET_BOOM_H


#include "library2.h"
#include "hash_table.h"
#include "AVLTree.h"
#include <iostream>

using std::ostream;
using std::endl;



class Lecture{
   int id;
   int time;
public:
   explicit Lecture(int id);
//   friend ostream& operator<<(ostream& os, Lecture& lecture){
//       os << "Lecture number: " << lecture.id <<" Time: " << lecture.time;
//       return os;
//   }
   ~Lecture() = default;
   int get_key();
   int get_time();
   void set_time(int time);
   void add_time(int time);
};



class Course{
   int id;
   HashTable<Lecture> lectures;
public:
   Course(int id);
//   friend ostream& operator<<(ostream& os, Course& course){
//       os << endl << "Course id " << course.id <<endl;
//      os << course.lectures <<endl;
//       os << "----------------------" <<endl;
//
//       return os;
//   }
   StatusType add_lecture(int lecture_id);
   int get_key();
   HashTable<Lecture>* get_hash_table();
   
   ~Course() = default;

};







class LectureTreeNode{
   int time;
   int course_id;
   int lecture_id;
public:
   LectureTreeNode(int time,int course_id, int lecture_id);
   bool operator<(const LectureTreeNode&);
   bool operator==(const LectureTreeNode&);
   ~LectureTreeNode() = default;
   int TreeNode_get_time();
   int TreeNode_get_course_id();
   int TreeNode_get_lecture_id();
//   friend ostream& operator<<(ostream& os, LectureTreeNode& lecture_node_tree){
//       os << " Time- " << lecture_node_tree.time << " CourseID- " << lecture_node_tree.course_id <<" LectureID- " << lecture_node_tree.lecture_id;
//       return os;
//   }
};




class Boom{
   HashTable<Course> main_table;
   AVLTree<LectureTreeNode> time_tree;
    
public:
    Boom() = default;
    ~Boom() = default;

    StatusType AddCourse (int courseID);
    StatusType AddClass(int courseID, int* classID);
    StatusType RemoveCourse( int courseID);
    StatusType TimeViewed(int courseID, int classID, int* timeViewed);
    StatusType WatchClass(int courseID, int classID, int time);
    StatusType GetIthWatchedClass(int i, int* courseID, int* classID);
//    friend ostream& operator<<(ostream& os, Boom& boom){
//        os << boom.main_table <<endl;
//        os << boom.time_tree <<endl;
//        return os;
//    }
};




#endif //HW1_WET_BOOM_H
