
#include "boom.h"



//LECTURE METHODS

Lecture::Lecture(int id) : id(id), time(0) {}
int Lecture::get_time(){
    return this->time;
}
void Lecture::set_time(int time){
    this->time = time;
}
int Lecture::get_key(){
    return this->id;
}
void Lecture::add_time(int time){
    this->time += time;
    return;
}




//COURSE METHODS
Course::Course(int id): id(id), lectures(){
}

StatusType Course::add_lecture(int lecture_id){
   if(id<0){
       return INVALID_INPUT;
   }
   Lecture* current_lecture = lectures.find(id);
   if(current_lecture == nullptr){                     // if there isn't lecture in the lectures tree (by id)
       Lecture* new_lecture = new Lecture(lecture_id);
       lectures.add(new_lecture);
   }
   else{
       return FAILURE;
   }
   return SUCCESS;
 }



int Course::get_key(){
    return this->id;
}
HashTable<Lecture>* Course::get_hash_table(){
    return &this->lectures;
}









// LectureTreeNode METHODS
LectureTreeNode::LectureTreeNode(int time, int course_id, int lecture_id):time(time), course_id(course_id), lecture_id(lecture_id){
}

bool LectureTreeNode::operator==(const LectureTreeNode& lecture_tree_node){
    return time == lecture_tree_node.time && course_id == lecture_tree_node.course_id && lecture_id == lecture_tree_node.lecture_id;
}

bool LectureTreeNode::operator<(const LectureTreeNode& lecture_tree_node){
    if(*this == lecture_tree_node){
        return false;
    }
    if(this->time < lecture_tree_node.time){
        return true;
    }
    else if(this->time > lecture_tree_node.time){
        return false;
    }
    else{
        if(this->course_id < lecture_tree_node.course_id){             
            return false;
        }
        else if(this->course_id > lecture_tree_node.course_id){
            return true;
        }
      else{
            if(this->lecture_id < lecture_tree_node.lecture_id){             
                return false;
            }
            else if(this->lecture_id > lecture_tree_node.lecture_id){
                return true;
            }
      }
    }
    return false;
}




int LectureTreeNode::TreeNode_get_time(){
    return this->time;
}
int LectureTreeNode::TreeNode_get_course_id(){
    return this->course_id;
}
int LectureTreeNode::TreeNode_get_lecture_id(){
    return this->lecture_id;
}




//BOOM METHODS

StatusType Boom::AddCourse (int courseID){                //AddCourse
   if(this == nullptr || courseID <= 0){                  //check input validity
       return INVALID_INPUT;
   }
   if(this->main_table.find(courseID) != nullptr){       //course with this id already exist
       return FAILURE;
   }
   else{
       Course* new_course = nullptr;
       try{
           new_course = new Course(courseID);
       }
       catch(const std::bad_alloc& e){
           delete this;
           return ALLOCATION_ERROR;

       }
       this->main_table.add(new_course);                 //we send to add -> Course object
   }
   return SUCCESS;
}

StatusType Boom::RemoveCourse(int courseID){
   if(this == nullptr || courseID <= 0){               //check input validity
       return INVALID_INPUT;
   }
   Course* course = this->main_table.find(courseID);
   if(course == nullptr){     //try to find the course in the boom
       return FAILURE;
   };       
   int num_of_classes = course->get_hash_table()->get_curr_size();
   for(int i=0 ; i < num_of_classes ; i++){            //remove lectures from time_tree(avl tree)
        Lecture* lecture = course->get_hash_table()->find(i);
        LectureTreeNode* to_delete;
        try{
            to_delete = new LectureTreeNode(lecture->get_time() , courseID , i);
        }
        catch(const std::bad_alloc& e){
            delete this;
            return ALLOCATION_ERROR;
        }
        this->time_tree.remove(to_delete);
        delete to_delete;
   }
   this->main_table.remove(courseID);                  //remove the course from main_table
   return SUCCESS;

}

StatusType Boom::AddClass(int courseID, int* classID){
   if(this == nullptr || courseID <= 0){                  //check input validity
       return INVALID_INPUT;
   }
   Course* course = this->main_table.find(courseID);
   if(course == nullptr){
       return FAILURE;
   }
   HashTable<Lecture>* lectures = course->get_hash_table();
   int curr_size = lectures->get_curr_size();
   Lecture* lecture;
   try{
        lecture = new Lecture(curr_size);

   }
   catch(const std::bad_alloc& e){
       delete this;
       return ALLOCATION_ERROR;
   }
   
   lectures->add(lecture);
   *classID = curr_size;
   return SUCCESS;
}
   



StatusType Boom::WatchClass(int courseID, int classID, int time) {                // Boom WatchClass
    if (this == nullptr || time <= 0 || classID < 0 || courseID <= 0) {           //check input validity 
        return INVALID_INPUT;
    }
    Course* to_course = this->main_table.find(courseID);
    if(to_course == nullptr){                         //check if course not exist
        return FAILURE;
    }
    HashTable<Lecture>* lectures_table = to_course->get_hash_table();
    if(lectures_table->get_curr_size()< classID + 1){
        return INVALID_INPUT;
    }
    Lecture* lecture = lectures_table->find(classID);
    int old_time = lecture->get_time();            //save old time to remove the old node from tree
    lecture->add_time(time); 
    //we want to add the node to time tree
    int new_time = lecture->get_time();           //save new time to add the new node to tree
    
    //remove the old from tree
    LectureTreeNode* old_node;
    try{
        old_node = new LectureTreeNode(old_time, courseID, classID);
    }
    catch(const std::bad_alloc& e){
        delete this;
        return ALLOCATION_ERROR;
    }



    this->time_tree.remove(old_node);
    delete old_node;

    //add the new one to the tree
    LectureTreeNode* new_node;
    try{
        new_node = new LectureTreeNode(new_time, courseID, classID);
    }
    catch(const std::bad_alloc& e){
        delete this;
        return ALLOCATION_ERROR;
    }


    this->time_tree.insert(new_node);

    return SUCCESS;
}





StatusType Boom::TimeViewed(int courseID, int classID, int* timeViewed){    //TIME VIEWED
   if (this == nullptr || courseID<=0 || classID <0){                      //check input validity
        return INVALID_INPUT;
   }
   Course* to_course = this->main_table.find(courseID);
   if(to_course == nullptr){                         //check if course not exist
       return FAILURE;
   }
   HashTable<Lecture>* lectures_table = to_course->get_hash_table();
   if(lectures_table->get_curr_size()< classID + 1){
       return INVALID_INPUT;
   }
   Lecture* lecture = lectures_table->find(classID);
   *timeViewed = lecture->get_time();

    return SUCCESS;
}




static void print_in_index(Node<LectureTreeNode>* root , int* index , int* courseID, int* classID){
    Node<LectureTreeNode>* tmp = root;
    if(*index == 1 && tmp->node_get_left() == nullptr){ //index == 1 and no left node
        *courseID = tmp->node_get_value()->TreeNode_get_course_id();
        *classID = tmp->node_get_value()->TreeNode_get_lecture_id();
        return;
    }
    if(tmp->node_get_left() == nullptr){
        *index -= 1;
        print_in_index(tmp->node_get_right(), index , courseID , classID);
        return;
    }
    int left_rank = tmp->node_get_left()->node_get_rank();
    if(left_rank + 1 == *index){                                       //if 'this' is the node to print
        *courseID = tmp->node_get_value()->TreeNode_get_course_id();
        *classID = tmp->node_get_value()->TreeNode_get_lecture_id();
        return;
    }
    else if(left_rank + 1 < *index){                                  //if we need to go to right_node
        *index -= left_rank + 1;
        tmp = tmp->node_get_right();
    }
    // else if(left_rank == index){
    //     *courseID = tmp->node_get_left()->node_get_value->TreeNode_get_course_id();
    //     *classID = tmp->node_get_left()->node_get_value->TreeNode_get_lecture_id();   
    //     return;
    // }
    else{
        tmp = tmp->node_get_left();
    }
    print_in_index(tmp, index , courseID , classID);
}


StatusType Boom::GetIthWatchedClass(int i , int* courseID , int* classID){
   if(this== nullptr || i <= 0){
       return INVALID_INPUT;
   }
   int tree_size = this->time_tree.tree_get_elements_num();
   if(tree_size < i){
       return FAILURE;
   }
   int index = tree_size - i + 1;
   Node<LectureTreeNode>* ptr_node = this->time_tree.get_root();
   print_in_index(ptr_node, &index, courseID, classID);     //find the node in the correct index
   return SUCCESS; 
}
