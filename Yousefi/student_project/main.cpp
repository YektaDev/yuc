#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "models/student.hpp"

using namespace std;


int main()
{
    Student* student;

    student = new Student;
    //student->setcode(1)->setname("habib")->setAverage(18)->debug();
    
    Student* student;

    student = new Student;
    student->setcode(1)->setname("ali")->setaverage(14)->add();    
    student->setcode(2)->setname("omid")->setaverage(18)->add();
    student->setcode(1)->setname("ali")->setaverage(14)->add();  // repeat
    student->setcode(5)->setname("omid")->setaverage(18)->add();
    //student->list(); 

    if(! student->setcode(5)->setname("ali")->setaverage(18)->add())   
    {
        cout << "success" << endl;
    }
    else
    {
        cout << student-> getError() << endl;
    }
    
    
    if (student->setname("ali")->find(field::name))
    {
        student->debug();
    }
    else
    {
        cout << "not found!!" << endl;
    }
    
    delete student;


    student->list();

    delete student;
}






