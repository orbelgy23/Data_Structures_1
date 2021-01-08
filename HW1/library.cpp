
#ifndef HW1_W_LIBRARY
#define HW1_W_LIBRARY
#include"library.h"
#include "boom.h"

void *Init() {
    Boom *DS = new Boom();
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses) {
    return ((Boom *)DS)-> AddCourse(courseID, numOfClasses);
}


StatusType RemoveCourse(void *DS, int courseID){
    return ((Boom *)DS)-> RemoveCourse(courseID);

}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    return ((Boom *)DS)-> WatchClass(courseID, classID, time);


}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    return ((Boom *)DS)-> TimeViewed(courseID, classID, timeViewed);

}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes){
    return ((Boom *)DS)-> GetMostViewedClasses(numOfClasses, courses, classes);

}

void Quit(void** DS){
    delete *((Boom**)DS);
    *DS= nullptr;
}


#endif //HW1_W_LIBRARY