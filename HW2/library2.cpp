
#ifndef HW2_W_LIBRARY2
#define HW2_W_LIBRARY2

#include"library2.h"
#include "boom.h"

void *Init() {
    Boom *DS = new Boom();
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID) {
    return ((Boom *)DS)-> AddCourse(courseID);
}


StatusType RemoveCourse(void *DS, int courseID){
    return ((Boom *)DS)-> RemoveCourse(courseID);

}
StatusType AddClass(void* DS, int courseID, int* classID){
    return ((Boom *)DS)-> AddClass(courseID, classID);

}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    return ((Boom *)DS)-> WatchClass(courseID, classID, time);


}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    return ((Boom *)DS)-> TimeViewed(courseID, classID, timeViewed);

}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID){
    return ((Boom *)DS)-> GetIthWatchedClass(i, courseID, classID);

}

void Quit(void** DS){
    delete *((Boom**)DS);
    *DS= nullptr;
}


#endif //HW2_W_LIBRARY2