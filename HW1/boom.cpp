

#include "boom.h"



//LECTURE METHODS
Lecture::Lecture(int id) : id(id){}
Lecture::~Lecture() {}




//COURSE METHODS
Course::Course(int id, AVLTree<int, Lecture>* lectures): id(id){
    this->lectures = lectures;
}
StatusType Course::add_lecture(int id){

    if(id<0){
        return INVALID_INPUT;
    }
    Lecture* current_lecture = this->lectures->find(id);
    if(current_lecture == nullptr){            // if there isn't lecture in the lectures tree (by id)
        Lecture* new_lecture = new Lecture(id);
        this->lectures->insert(id, new_lecture);
    }
    return SUCCESS;
}
AVLTree<int, Lecture>* Course::course_get_tree(){
    if(this != nullptr){
        return this->lectures;
    }
    return nullptr;
}
StatusType Course::remove_lecture(int id){
    if(id<0){
        return INVALID_INPUT;
    }
    this->lectures->remove(id);
    return SUCCESS;
}
Course::~Course(){
    if(this!= nullptr){
        if(this->lectures!= nullptr){
            delete this->lectures;
        }
        this->lectures = nullptr;
    }
}




//NODELIST METHODS
NodeList::NodeList(int key) :key(key), tree_courses(nullptr), next_node(nullptr), prev_node(nullptr){
    this->tree_courses = new AVLTree<int, Course>();
}
NodeList::~NodeList(){
    if(this->tree_courses != nullptr) {
        delete this->tree_courses;
    }
}
StatusType NodeList::insert_course_with_lectures(int id, AVLTree<int, Lecture>* lecture) {
    Course* new_course = new Course(id, lecture);
    this->tree_courses->insert(id, new_course);
    return SUCCESS;
}
NodeList* NodeList::remove_node_from_list(){
    if(this->next_node != nullptr && this->prev_node != nullptr){
        this->next_node->prev_node = this->prev_node;
        this->prev_node->next_node = this->next_node;
        delete this;
    }
    else if(this->prev_node != nullptr){
        this->prev_node->next_node = nullptr;
        NodeList* return_value = this->prev_node;
        this->prev_node = nullptr;
        delete this;
        return return_value;
    }
    return nullptr;
}
NodeList* NodeList::get_next(){
    return this->next_node;
}
NodeList* NodeList::get_prev(){
    return prev_node;
}
int NodeList::get_key(){
    return this->key;
}
void NodeList::display(){
    if(this !=nullptr){
        cout << "key: " << key << "value: " << tree_courses << endl;
        this->next_node->display();
    }
}
AVLTree<int, Course>* NodeList::nodeList_get_tree(){
    return this->tree_courses;
}
NodeList* NodeList::insert_before(int new_time , int classID , int courseID, bool flag){
    NodeList* new_node = new NodeList(new_time);
    if(flag == true){                                 //this function is called from 2 diffrent locations and does 2 different things
                                                      // this is why we check whether flag is true or false
        new_node -> prev_node = this;                 //here we insert the new node last
        this->next_node = new_node;
    }
    else{                                             //here we insert the new node right before 'this'
        new_node->next_node = this;
        new_node->prev_node = this->prev_node;
        this->prev_node->next_node = new_node;
        this->prev_node = new_node;  
    }

    AVLTree<int,Lecture>* lecture_tree = new AVLTree<int,Lecture>();   //create lecture_tree
    Lecture* new_lecture = new Lecture(classID);                       //create lecture
    lecture_tree->insert(classID , new_lecture);                       //insert lecture to lecture tree
    new_node->insert_course_with_lectures(courseID , lecture_tree);    //insert the course with all its lectures to the node
    return new_node;
}




//LIST METHODS
List::List(): first(nullptr), last(nullptr){                          //List Ct'r
    NodeList* new_node = new NodeList(0);
    first = new_node;
    last = new_node;
}
List::~List(){
    while(this->first != nullptr){
        NodeList* tmp = this->first;
        this->first = this->first->get_next();
        if(tmp!= nullptr){
            delete tmp;
            tmp= nullptr;
        }
    }
}
NodeList* List::get_first(){
    return this->first;
}
NodeList* List::get_last(){
    return this->last;
}
void List::set_last(NodeList* to_change){
    this->last = to_change;
}
NodeList* List::insert_before(NodeList* node_list ,int new_time , int classID , int CourseID){
    NodeList* return_value = node_list;
    bool flag = false;
    NodeList* tmp2= nullptr;
    while(node_list !=nullptr && new_time > node_list->get_key() ){
        node_list = node_list->get_next();
    }
    if(node_list == nullptr){                             //node_list == nullptr  ==> need to insert in last)
        flag = true;
        NodeList* tmp  = this->last->insert_before(new_time ,classID , CourseID , flag);
        this->last = tmp;
        if(return_value->nodeList_get_tree()->is_empty() && return_value->get_key()!=0){
            NodeList* change_prev = return_value->remove_node_from_list();
            if(change_prev != nullptr){
                this->last = change_prev;
            }
        }
        return tmp;
    }
    else{                                                //we need to insert the new node before another node
        if(new_time < node_list->get_key()){ //insert before node
            tmp2 = node_list->insert_before(new_time , classID , CourseID, flag);
        }
        if(new_time == node_list->get_key()){  //insert in current node
            Course* new_course = node_list->nodeList_get_tree()->find(CourseID);
            if(new_course!=nullptr){                   // course exist
                new_course->add_lecture(classID);
            }
            else{                                                            //course not exist in tree
                AVLTree<int, Lecture>* new_lectures_tree = new AVLTree<int, Lecture>();
                Lecture* new_lecture = new Lecture(classID);
                new_lectures_tree->insert(classID, new_lecture);
                node_list->insert_course_with_lectures(CourseID, new_lectures_tree);
            }
            tmp2=node_list;
        }
    }
    if(return_value->nodeList_get_tree()->is_empty() && return_value->get_key()!=0){
        NodeList* change_prev = return_value->remove_node_from_list();
        if(change_prev != nullptr){
            this->last = change_prev;
        }
    }
    return tmp2;
}




//LECTUREOFCOURSE METHODS
lecturesOfCourse::lecturesOfCourse(int courseID, int numOfClasses) : courseID(courseID), numOfClasses(numOfClasses), arr(new NodeList*[numOfClasses]){    //not complete
//    arr = new NodeList*[numOfClasses];

}
void lecturesOfCourse::set_arr(NodeList* node_list){
    for (int i = 0; i < this->numOfClasses; ++i) {
        this->arr[i] = node_list;
    }
}
NodeList* lecturesOfCourse::get_node_from_list(int index){
    return this->arr[index];
}
lecturesOfCourse::~lecturesOfCourse(){
    if(arr!= nullptr){
        delete[] this->arr;
        this->arr = nullptr;
    }
}
int lecturesOfCourse::get_num_of_classes(){
    return this->numOfClasses;
}
NodeList** lecturesOfCourse::get_arr(){
    return this->arr;
}
void lecturesOfCourse::set_node_in_list(int class_id, NodeList* node_list){
    this->arr[class_id] = node_list;
}




//BOOM METHODS
Boom::Boom() : main_tree(nullptr), priority_list(nullptr), zero_tree(nullptr) {     //Boom Ct'r
    this->main_tree = new AVLTree<int, lecturesOfCourse>();
    this->priority_list = new List();
    this->zero_tree = new AVLTree<int, ZeroTreeNode>();
}
Boom::~Boom(){
    if(this->main_tree!= nullptr){
        delete main_tree;
        main_tree=nullptr;
    }
    if(this->priority_list!= nullptr){
        delete priority_list;
        priority_list=nullptr;
    }
    if(this->zero_tree!= nullptr){
        delete zero_tree;
        zero_tree=nullptr;
    }
}
StatusType Boom::AddCourse (int courseID, int numOfClasses){                  //AddCourse
    if(this == nullptr || numOfClasses<=0 || courseID <= 0){     //check input validity
        return INVALID_INPUT;
    }
    if(this->main_tree->find(courseID) != nullptr){   //course with this id already exist
        return FAILURE;
    }
    else{
        lecturesOfCourse* new_lecture_of_course = new lecturesOfCourse(courseID,numOfClasses);
        ZeroTreeNode* new_zero_tree_node = new ZeroTreeNode(numOfClasses);
        this->zero_tree->insert(courseID,new_zero_tree_node);             //add this course to zero_tree
        new_lecture_of_course->set_arr(this->priority_list->get_first()); //set all arr ptr to node with time=0
        this->main_tree->insert(courseID , new_lecture_of_course);  //add lecture_of_course to the main tree
        return SUCCESS;
    }
}
StatusType Boom::RemoveCourse( int courseID){
    if(this == nullptr || courseID <= 0){               //check input validity
        return INVALID_INPUT;
    }
    lecturesOfCourse* lecture_of_course = this->main_tree->find(courseID);       //find the course in main_tree
    if(lecture_of_course == nullptr){ //if not exist in tree
        return FAILURE;
    }
    for(int i=0 ; i<lecture_of_course->get_num_of_classes() ;i++) {         //run over the arr entries
        if(lecture_of_course->get_arr()[i]->get_key() != 0 ){            //we check if lecture time is 0
            Course* course = lecture_of_course->get_arr()[i]->nodeList_get_tree()->find(courseID);
            course->remove_lecture(i);                       //remove the lecture from tree_courses (field of node list)
            if(course->course_get_tree()->is_empty()){    //we check if after delete lecture - the courses is empty
                lecture_of_course->get_arr()[i]->nodeList_get_tree()->remove(courseID);
            }
            if(lecture_of_course->get_arr()[i]->nodeList_get_tree()->is_empty() && lecture_of_course->get_arr()[i]->get_key()!=0){ //Node is empty
                NodeList* change_prev = lecture_of_course->get_arr()[i]->remove_node_from_list();
                if(change_prev != nullptr){
                    this->priority_list->set_last(change_prev);
                }
            }
        }
        lecture_of_course->get_arr()[i] = nullptr;

    }
    this->zero_tree->remove(courseID);       //remove the course from zero_tree
    this->main_tree->remove(courseID);       //remove the course from main_tree
    return SUCCESS;
}
StatusType Boom::WatchClass( int courseID, int classID, int time) {                // Boom WatchClass
    if (this == nullptr) {                                                //check input validity
        return INVALID_INPUT;
    }
    if (time <= 0 || classID < 0 || courseID <= 0) {                    //check input validity
        return INVALID_INPUT;
    }
    lecturesOfCourse *new_lecture_of_course = this->main_tree->find(courseID);  //check if course exist
    if (new_lecture_of_course == nullptr) {
        return FAILURE;
    }
    int numOfClasses = new_lecture_of_course->get_num_of_classes();

    if (classID + 1 > numOfClasses) {                                 //check input validity
        return INVALID_INPUT;
    }
    NodeList *new_node_list = new_lecture_of_course->get_node_from_list(classID);     //We get the lecture's node
    int current_time = new_node_list->get_key();                                    //we get the time of the node
    Course *new_course = new_node_list->nodeList_get_tree()->find(courseID);
    if(current_time == 0){                                      //lecture in zero time - remove from zerotree
        ZeroTreeNode* zero_node = this->zero_tree->find(courseID);
        zero_node->set_zero_node_bool(classID);
        if(zero_node->get_false_cells() == new_lecture_of_course->get_num_of_classes()){
            this->zero_tree->remove(courseID);
        }
    }
    else{                                                   //lecture time isn't 0
        new_course->course_get_tree()->remove(classID);    //remove lecture from course's lecture tree
        if(new_course->course_get_tree()->is_empty()){
            new_node_list->nodeList_get_tree()->remove(courseID);
        }
    }
    NodeList *current_node_list = this->priority_list->insert_before(new_node_list, current_time + time, classID,
                                                                     courseID);
    if (current_node_list == nullptr) {
        return FAILURE;
    }
    new_lecture_of_course->set_node_in_list(classID, current_node_list);   //change ptr in arr[classID] to the new node with the time
    return SUCCESS;
}
StatusType Boom::TimeViewed(int courseID, int classID, int* timeViewed){
    if (this == nullptr || courseID<=0 || classID <0){                      //check input validity
        return INVALID_INPUT;
    }
    lecturesOfCourse* new_lecture_of_course = this->main_tree->find(courseID);
    if(new_lecture_of_course == nullptr){                                   //check if course not exist
        return FAILURE;
    }
    if(classID+1>new_lecture_of_course->get_num_of_classes()){              //check input validity
        return INVALID_INPUT;
    }
    NodeList* new_node = new_lecture_of_course->get_node_from_list(classID);
    *timeViewed = new_node->get_key();
    return SUCCESS;
}
static void print_lectures(Node<int, Lecture>* current_lecture, int* count_lectures,int course_id, int* courses, int* classes, int num_of_classes){
    if(current_lecture == nullptr || *count_lectures >= num_of_classes) return;
    if(current_lecture->node_get_left()!=nullptr){
        print_lectures(current_lecture->node_get_left(), count_lectures, course_id, courses, classes, num_of_classes);
    }
    if(*count_lectures >= num_of_classes) return;
    courses[*count_lectures] = course_id;
    classes[*count_lectures] = current_lecture->node_get_key();
    *count_lectures = *count_lectures + 1;
    if(current_lecture->node_get_right()!=nullptr){
        print_lectures(current_lecture->node_get_right(), count_lectures, course_id, courses, classes, num_of_classes);
    }
}
static void print_get_most(Node<int, Course>* current_course, int* count_lectures, int* courses, int* classes, int num_of_classes){
    if(current_course == nullptr || *count_lectures >= num_of_classes) return;
    if(current_course->node_get_left()!=nullptr){
        print_get_most(current_course->node_get_left(), count_lectures, courses, classes, num_of_classes);
    }
    print_lectures(current_course->node_get_value()->course_get_tree()->get_root(),
                     count_lectures, current_course->node_get_key(), courses, classes, num_of_classes);
    if(current_course->node_get_right()!=nullptr){
        print_get_most(current_course->node_get_right(), count_lectures, courses, classes, num_of_classes);
    }
}
static void print_from_array(bool* arr, int* count_lectures,int course_id, int* courses, int* classes, int num_of_classes, int arr_size){
    for(int i=0 ; i<arr_size ; i++){
        if(arr[i]){
            if(*count_lectures >= num_of_classes) return;
            courses[*count_lectures] = course_id;
            classes[*count_lectures] = i;
            *count_lectures = *count_lectures + 1;
        }
    }
}
static void print_from_zero_time(Node<int, ZeroTreeNode>* current_course, int* count_lectures, int* courses, int* classes, int num_of_classes){
    if(current_course == nullptr || *count_lectures >= num_of_classes) return;
    if(current_course->node_get_left()!=nullptr){
        print_from_zero_time(current_course->node_get_left(), count_lectures, courses, classes, num_of_classes);
    }
    print_from_array(current_course->node_get_value()->zero_node_get_arr(), count_lectures,
            current_course->node_get_key(), courses, classes, num_of_classes, current_course->node_get_value()->get_arr_size());
    if(current_course->node_get_right()!=nullptr){
        print_from_zero_time(current_course->node_get_right(), count_lectures, courses, classes, num_of_classes);
    }
}
StatusType Boom::GetMostViewedClasses(int numOfClasses, int *courses, int *classes){
    if(this== nullptr || numOfClasses<=0){
        return INVALID_INPUT;
    }
    NodeList* tmp= this->priority_list->get_last();           //get the last node in list
    int count=0;
    if(this->main_tree->is_empty()){                          //check if our data structure isn't empty
        return FAILURE;
    }
    while(tmp->get_key() != 0 && count<numOfClasses){         //we run over list's nodes until we get to zero time node
        Node<int, Course>* ptr_course = tmp->nodeList_get_tree()->get_smallest_node();
        for (int i = 0; i < numOfClasses && ptr_course->node_get_parent()!= nullptr; i++) { //from smallest node we climb up
            ptr_course = ptr_course->node_get_parent();
        }
        print_get_most(ptr_course, &count, courses, classes, numOfClasses);   //this is our in-order printing to courses and classes arrays
        tmp = tmp->get_prev();
    }
    // now we are going to print lectures with zero time (in case we even need to print more)
    Node<int,ZeroTreeNode>* zero_node = this->zero_tree->get_smallest_node();
    for (int i = 0; i < numOfClasses - count && zero_node->node_get_parent()!= nullptr; i++) {
        zero_node = zero_node->node_get_parent();
    }
    print_from_zero_time(zero_node, &count, courses, classes, numOfClasses);
    if(tmp->get_key() == 0 && count<numOfClasses){
        return FAILURE;
    }
    return SUCCESS;
}




//ZEROTREENODE METHODS
ZeroTreeNode::ZeroTreeNode(int numOfClasses): arr_size(numOfClasses), false_cells(0), bool_arr(nullptr)  {
    this->bool_arr = new bool[numOfClasses];
    for(int i = 0 ; i < numOfClasses ; i++){
        this->bool_arr[i] = true;
    }
}
ZeroTreeNode::~ZeroTreeNode() {
    delete[] bool_arr;
}
void ZeroTreeNode::set_zero_node_bool(int id){
    if(bool_arr[id]){
        this->bool_arr[id] = false;
        this->false_cells++;
    }
}
int ZeroTreeNode::get_false_cells(){
    return this->false_cells;
}
bool* ZeroTreeNode::zero_node_get_arr(){
    return this->bool_arr;
}
int ZeroTreeNode::get_arr_size(){
    return this->arr_size;
}
