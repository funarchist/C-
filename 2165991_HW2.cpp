#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;



class Student {
private:
    int ID;                                      //Any student have ID that have 3 number
    int cot;                                     //This will be used to create dynamic array that have the size of number of choices that students have
    char *choice = new char [cot];               //The choices of individual student will be stored in this char array, with indexing them in preference order
public:
    Student(int id,int coun):ID(id),cot(coun){}; //As soon as line is read, corresponding student will be created by using this constructor function
    Student(){};                                 //Using this constructor object array will be created that can store students before grouping section
    int getSize()const{return cot;} ;            //Since choices array size=cot is private we need this accessing function
    int getID()const{return ID;} ;               //Since student ID is private we need this accessing function
    char* get_choice(){ return choice; };        //Since day choices array is private we need this accessing function
};


class Section{
private:
    char name;                                          //Section stack have names that are character representation of the days {W,T,F}
    int MaxStackSize;                                   //The capacity of day is dynamically determined
    Student *stacklist = new Student [MaxStackSize];    //We create dynamic array which has the size of the capacity of the corresponding day and store student objects
    int top;                                            //Variable to track stack condition and accomplish Pop,Push operations
public:
    void setname(char name1){name=name1;};              //Since section name is private we need this setting function
    char getname()const{return name;} ;                 //Since section name is private we need this getting function
    Section(int Size):top(-1) { MaxStackSize = Size; }; //This constructor is used to create stack objects as we read lines
    Section():top(-1),MaxStackSize(0){};                //This constructor object used to create stack that is used to store stack elements which are sections
    void Push(const Student& item);                     //Push operation that store Student object to section stack
    Student Pop(void);                                  //Pop operation that returns Student object from a section stack
    int StackFull(void)const;                           //Checking stack condition whether section is full
    int StackEmpty(void)const;                          //Checking stack condition whether section is empty which will be used int the part that lists students in the corresponding sections
};


int Section::StackFull(void) const { return top==(MaxStackSize-1); }   //Since top is started from -1, top value is MaxStackSize-1 when it reaches full capacity

int Section::StackEmpty(void) const { return top==-1; }   //If top is in starting position,section is empty

void Section::Push(const Student& item)  //We don't need StackFull checking inside the func implementation because we check it by StackFull() in the program
{
    top++;
    stacklist[top]=item;
}

Student Section::Pop(void)  //We don't need StackEmpty checking inside the func implementation because we check it by StackEmpty() in the program
{
    Student temp;
    temp=stacklist[top];   //As poping returns student objects before we decrease top we need to store that object
    top--;
    return temp;
}

class Waiting{
private:
    int MaxQsize;                                //Queue size will be determined dynamically as we find the number of students that are not imediatelly assigned to sections
    int front,rear,count;                        //Standard queue trackers
    Student* qlist = new Student[MaxQsize];      //Queue that stores students have dynamically determined size
public:
    Student* get_qlist(){ return qlist; };       //To get private list that  holds students
    Waiting(int qs):MaxQsize(qs),front(0),rear(0),count(0){}; //Constructor function that initializes queue with number of students that are not assigned imediatelly
    void Qinsert(const Student& item);          //Insert student to queue
    Student Qdelete(void);                      //Pops the student in the queue
    int QEmpty(void) const;                     //To determine whether we exhausted queue
    int getfront(void)const{return front;};   //To get current front value we need it because it is private
    int getrear(void)const{return rear;};      //To get current rear value we need it because it is private
};

int Waiting::QEmpty(void) const{ return(count==0); }  //Count have its initial value so nothing is inserted

void Waiting::Qinsert(const Student& item){  //It inserts to 1 after last element which is rear variable

qlist[rear] = item;
rear = rear+1;
count++;

}
Student Waiting::Qdelete(void){  //As it deletes it returns deleted student object and front points new first element

Student temp;
temp = qlist[front];
count--;
front = (front+1);
return temp;

}


int main()
{
    Student students[100];     //To store student objects before grouping operation
    Section sections[3];       //To store sections that holds days{T,W,f}
    int a =0;                  //To read first 3 lines
    int b =0;                  //To iterate over Student object array students, that we used to store students that are read from lines
    char letter;               // Will be used to read student choices from the line
    int scount = 0;            //Number of student counter
    ifstream inputtxt;
    inputtxt.open("preferences.txt");
    char output[100];
    if (inputtxt.is_open()) {
        while (!inputtxt.eof()) {
            if(a<3)   //We iterate over first 3 lines to get sections and their corresponding capacities
              {
                        inputtxt>>output;
                        sections[a] = Section((int)output[2]-48);   // Character that refers to capacity is in ASCII as a result we convert it to represented number by subtract it using 48
                        sections[a].setname(output[0]);             // First character is day name character representation
                        ++a;

                }

            else   //Operations after the first 3 lines
                {
                inputtxt >> output;
                int iD = 100*((int)output[0] - 48)+10*((int)output[1] - 48)+((int)output[2] - 48);  //Student number character is converted to integer
                int i=4;      //First 4 character is numbers and comma so we use this as offset to proceed to choices
                int ccount = 0;  //This counts choice number of corresponding student in line
                while(output[i] != NULL)          //Read choices until student choices ends
                {
                    letter = output[i];
                    if(letter == 'F' ||letter == 'T' ||letter == 'W')
                    {
                        ccount++;   // This is how many choices student in line have made
                    }
                    i++;
                }
                Student tempstudent(iD,ccount); //Initialize student object that have corresponding ID in line and array that have size the number of choices she did to store choices
                ++scount;  //As we create student object, student count is increased
                int k=4;  // We iterate over student choices with this offset
                int seq=0; // this index makes us store choices by its importance 0 most to 2 least if exists
                while(output[k] != NULL)  //Iterate over choices until no more
                    {
                    letter = output[k];
                    switch(letter) // With every choice we store that choice to student's choice array
                    {
                        case 'F':
                            tempstudent.get_choice()[seq] = 'F';
                            seq++;
                            break;
                        case 'T':
                            tempstudent.get_choice()[seq] = 'T';
                            seq++;
                            break;
                        case 'W':
                            tempstudent.get_choice()[seq] = 'W';
                            seq++;
                            break;
                        default:    //To skip comma
                            break;
                    }
                        k++;
                    }

                students[b] = tempstudent;  //Finally temporary student object is stored in student object array
                ++b;
                }

                }
    }

inputtxt.close();
Waiting que(2*scount);
Student g;
char *d;

//Here program accomplish grouping action.
for(int c =0;c<scount;c++) //takes student from student object array one by one until student number is reached
{
    g = students[c];
    d = g.get_choice();
    int e = g.getID();
    if(g.getSize() == 1)    //If stuednt have only 1 choice, she is imediatelly assigned to section if section is availanle
    {
            for(int check=0;check<3;++check)   //Since day and capacities can be given random we need to check to find matching section for student choice
            {
                if(sections[check].getname() == d[0])
                {
                    if(sections[check].StackFull() !=1)
                    {
                        sections[check].Push(g);  //If section is available student is put into that section
                    }
                    else
                    {
                        que.Qinsert(g);  //Even if it is student's only choice if section is not available put it into queue
                    }
                }
            }
    }
    else{

     que.Qinsert(g); //If student have more than one choice put it into queue
   }
}



Student q;
char *p;
int y = que.getfront();
int r = que.getrear();
for(int h = y;h<r;h++)  //We iterate over queue
{
    int flag = 0;
    q = que.get_qlist()[h]; //
    p = q.get_choice();
    for(int j=0;j<q.getSize();j++){ //First we get student choice from most to least wanted
        for(int check=0;check<3;check++)  //We iterate over section to find section that student have choseen
            {
                                   cout<<sections[check].getname()<<endl;
                    cout<<p[j]<<endl;
                    cout<<q.getID();
                if(sections[check].getname() == p[j])  //If there is a match between student choice and section we proceed to check if it is available
                {
                cout<<"possible";
                    if(sections[check].StackFull() != 1) //If section is available than we put that student into available section and set flag
                    {   sections[check].Push(q);
                        flag = 1;
                        cout<<"execution";
                        break;
                    }
                }
            }
            if(flag==1){break;}  //If this flag is set than we finish student placement if not we proceed to check other choices of student

    }
if(flag==1){que.Qdelete();} //If student is placed we delete it from queue
else if(flag ==0){que.Qinsert(que.Qdelete());};  //If student is not placed to their selection we put that student to the end of the queue
}

//Ouptut text file generation
char day;                          //This is to check sections' names
ofstream outputtxt;
outputtxt.open("results.txt");
for(int i=0;i<3;i++){ //We iterate over 3 days section
    day = sections[i].getname();
    switch(day)
    {
        case 'W':
            outputtxt<<"Wednesday:"<<endl;
            while(sections[i].StackEmpty() != 1)      //We pop all wednesday studens until all section is cleared    ( These popping sections until empty and getting ID repeated for other days too)
           {outputtxt<<sections[i].Pop().getID()<<endl;}  //we pop each students ID
            break;
        case 'T':
            outputtxt<<"Thursday:"<<endl;
            while(sections[i].StackEmpty() != 1)
           {outputtxt<<sections[i].Pop().getID()<<endl;}
            break;
        case 'F':
            outputtxt<<"Friday:"<<endl;
            while(sections[i].StackEmpty() != 1)
           {outputtxt<<sections[i].Pop().getID()<<endl;}
            break;
    }
}
outputtxt<<"Unassigned:"<<endl;
if(que.QEmpty() == 1){       //If queue is empty than there is not unassigned student "-" indicates this
    outputtxt<<"-"<<endl;
}
else{
    while(que.QEmpty() != 1)
    {outputtxt<<que.Qdelete().getID()<<endl;}   //The students that are in queue until now are not assigned so show it in here
}
outputtxt.close();
return 0;
};
