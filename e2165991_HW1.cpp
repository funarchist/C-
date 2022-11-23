//Writer: Berk Alperen Bener,Date: 20.11.2021,Project: EE441 HW #1
#include<iostream>

using namespace std;

const int MAX_SIZE = 10; //Determines number of students that database can handle
class Student{  //Student is derived form Course class
private:
    int ID;
    string name;
    string surname;
    int quiz_scores[4] = {0,0,0,0}; // scores are default 0
    int hw_scores[3] = {0,0,0};
    int final_score = 0;
public:
    Student(){};
    void setID(int sID){ ID = sID;};            //All data members have set,get functions and to get functions to prevent accidental modifications they are const
    int getID()const{return ID;} ;
    void setname(string sname){name = sname;};
    string getname()const {return name;};
    void setsurname(string csurname){surname = csurname; };
    string getsurname()const {return surname;};
    int* getquiz_scores(){ return quiz_scores; };
    int* gethw_scores(){ return hw_scores; };
    int getfinal_score()const{return final_score;};
    void setquiz_scores(int array1[4]){for(int dum=0;dum<4;dum++){quiz_scores[dum] = array1[dum];}}; //array values that are taken from user are assigned individually
    void sethw_scores(int array2[3]){for(int dum=0;dum<4;dum++){hw_scores[dum] = array2[dum];}};
    void setfinal_score(int fin){final_score = fin;};
    float overallCourseScore();
};

class Course {
protected: // So we can access these data members from child class
    int num=0; // This keeps track the number of entries
    float weightQ = 0.3; //These variables are float but user enters integer values than we transform into float
    float weightHW = 0.3;
    float weightF= 0.4;

public:
    Student students[MAX_SIZE];
    Course(){}; //default values 30 percent,30 percenr and 40 percent
    int getNum()const{return num;}; //returns how many students are in the course
    void setweight(float x,float y,float z){this->weightQ = x;this->weightHW = y;this->weightF = z;};
    float getweightQ(){return weightQ;};
    float getweightHW(){return weightHW;};
    float getweightF(){return weightF;};
    void addNewStudent(int k, string l, string m); //ID,name,surname input respectively,adds new student to the course
    void updateWeights(int a,int b,int c); //updates weights
    void getStudentInfo(int ID) const; //returns a Student information given an ID,It is const so we prevent accidental modification
    void showAverage(); // calculates course averages for quiz, homework, final exam and overall course scores
};


Course course; //global course object is declared

//Student students[MAX_SIZE]; //Array of student object is declared, it can't be declared inside the Course Class because student class is derived from it.//

float Student::overallCourseScore(){
return ( course.getweightQ()*((float)(quiz_scores[0]+quiz_scores[1]+quiz_scores[2]+quiz_scores[3])/4.0) +
    course.getweightHW()*((float)(hw_scores[0]+hw_scores[1]+hw_scores[2])/3.0) +
    course.getweightF()*(final_score)); //average score for individual student
    }
void Course::addNewStudent(int nID, string fname, string fsurname) //adds new student to the course
{
    for(int k=0;k<num;k++)
        if(course.students[k].getID()==nID)
    {
        cerr<<"ID is not unique";
        return;
    }
    if(num<MAX_SIZE){ //Number of entries is limited to Max size
        course.students[num].setID(nID);
        course.students[num].setname(fname);
        course.students[num].setsurname(fsurname);
        num++;
    }
    else
    {
        cerr<<"Maximum number of student has been reached";
    }
}

void Course::getStudentInfo(int gID) const
{
int *p,*q; // to return arrays quiz and hw values we use integer pointer
    if((gID>(-1))) //Checks non-negative ID
    {
        for(int k=0;k<MAX_SIZE;k++)
        {
            if (course.students[k].getID() == gID) //search student object array by ID
            {
                cout<<course.students[k].getID()<<" "
                <<course.students[k].getname()<<" "
                <<course.students[k].getsurname()<<" ";  //until this point returns integer
                p = course.students[k].getquiz_scores();
                for(int y=0;y<4;y++){cout<< *(p+y)<<" ";}
                q = course.students[k].gethw_scores();
                for(int e=0;e<3;e++){cout<< *(q+e)<<" ";}      //quiz and hw scores are return by iterating over memory values
                cout<<" "<<course.students[k].getfinal_score(); // final score is returned as integer
                return;  //no more search since we found the matched student
            }
        }
    }
    cerr<<"Invalid ID"; //if ID is negative
}

void changeStudentScores(int cID, int quiz_scores[4], int hw_scores[3], int final_score) {
int err1=0,err2=0,err3=0; //So, in here when user writes the input quiz,hw,final values we check all these values in its own category for nonnegativity and not more than being 100
int ind1=0,ind2=0;        //If there exist multiple entry faults this algorithms gives where individual mistakes happened and in which category.
for(int x=0;x<4;x++){if((quiz_scores[x]<0)||(quiz_scores[x]>100)){err1 =1;ind1=(x+1); break;}}
for(int y=0;y<3;y++){if((quiz_scores[y]<0)||(quiz_scores[y]>100)){err2 =1;ind2=(y+1);break;}}
if((final_score<0)||(final_score>100)){err3 = 1;}

if(err1==1){ cout<<"Following Quiz's Value Is Out of Range:"<<ind1<<endl;}
if(err2==1){ cout<<"Following Homework's Value Is Out of Range:"<<ind2<<endl;}
if(err3==1){ cout<<"Final Exam Value Is Out Of Range"<<endl;}
if((err1 !=0)||(err2 !=0)||(err3!=0)){cout<<"Student's ID is valid, enter fixed results to the same ID ";return;} //We don't delete student ID,name and surname
                                                                                                                  //But exam results are default zero until user assign all results correctly
     if((cID>(-1))) //ID is checked for non negativity
        {
        for(int k=0;k<MAX_SIZE;k++)
            {
                if (course.students[k].getID() == cID) //search student object array by ID
                {
                    course.students[k].setquiz_scores(quiz_scores);   //change matched student scores with appropriate object functions
                    course.students[k].sethw_scores(hw_scores);
                    course.students[k].setfinal_score(final_score);
                    return; //no more search since we found the matched student
                }
            }
    }
    cerr<<"Invalid ID";
}


void Course::updateWeights(int fweightQ, int fweightHW, int fweightF){
  course.setweight((float)fweightQ/100.0,(float)fweightHW/100.0,(float)fweightF/100.0);
}

void Course::showAverage(){
int *qu,*hw;
int a1=0,a2=0,a3=0;
float a4=0.0;
for(int k=0;k<num;k++){  //we iterate over every students' quiz values and find the sum
        qu = course.students[k].getquiz_scores();
        for(int m=0;m<4;m++){
            a1 = a1 + *(qu+m);
        }
}
for(int k=0;k<num;k++){ //we iterate over every students' hw values and find the sum
        hw = course.students[k].gethw_scores();
        for(int m=0;m<3;m++){
            a2 = a2 + *(hw+m);
            cout<<endl;
        }
}
for(int k=0;k<num;k++){ a3 = a3 + course.students[k].getfinal_score();} //we iterate over every students' final values and find the sum
for(int k=0;k<num;k++){ a4 = a4 + course.students[k].overallCourseScore();} //we iterate over every students' overall course value values and find the sum

cout<<"Quizzes-Avg:"<<(float)a1/(float)(num*4)<<endl; // To find averages sum is divided by total number of quiz,hw,final exam and overall average numbers
cout<<"Homeworks-Avg:"<<(float)a2/(float)(num*3)<<endl;
cout<<"Final-Avg:"<<(float)a3/(float)num<<endl;
cout<<"Overall-Avg:"<<a4/(float)num<<endl;



}

void showAbove(int threshold) {
int cont = 0;
    for(int ab=0;ab<course.getNum();ab++)
        {
            if (course.students[ab].overallCourseScore()>threshold) //we iterate over all entries
            {
                cout<<course.students[ab].getID()<<" " //We print these values per student that is above the thereshold
                <<course.students[ab].getname()<<" "
                <<course.students[ab].getsurname()<<" "
                <<"Avg:"<<course.students[ab].overallCourseScore();
                cout<<endl;
                cont +=1;
            }
        }
        if(cont ==0){cout<<"There isn't any student above the threshold";} //Warning if all students are below the threshold
        else{return;}
}



void showBelow(int threshold)
{
int cont = 0;
   for(int ab=0;ab<course.getNum();ab++)
    {
        if (course.students[ab].overallCourseScore()<threshold) //we iterate over all entries
        {
                cout<<course.students[ab].getID()<<" " //We print these values per student that is below the thereshold
                <<course.students[ab].getname()<<" "
                <<course.students[ab].getsurname()<<" "
                <<"Avg:"<<course.students[ab].overallCourseScore();
                cout<<endl;
                cont +=1;
        }
    }
    if(cont ==0){cout<<"There isn't any student below the threshold";} //Warning if all students are above the threshold
    else{return;}

}


int main(){
int cweightQ,cweightHW,cweightF;
int num=0;
int aID,bID,cID,afinal,cfinal,threshold;
string aname,cname,asurname,csurname;
int aquiz[4],cquiz[4],ahomework[3],chomework[3];
cout<<"1. Add student"<<endl;                             //User Interface menu
cout<<"2. Search a student by ID"<<endl;
cout<<"3. Change a students score"<<endl;
cout<<"4. Update weights"<<endl;
cout<<"5. Show classroom average"<<endl;
cout<<"6. Show students with overall score above a threshold"<<endl;
cout<<"7. Show students with overall score below a threshold"<<endl;
cout<<"8. Exit"<<endl;
while(num != 8){   //UI asks for option selection until user decide to quıt program
cout<<endl<<"Enter your option:";
cin>>num;
switch(num){ //Menu activities are decided by switch-case
    case 1:
        cout<<"Enter student's ID, name, surname and scores (quizzes, homeworks, final)"<<endl;
        cin>>aID>>aname>>asurname>>aquiz[0]
        >>aquiz[1]>>aquiz[2]>>aquiz[3]
        >>ahomework[0]>>ahomework[1]>>ahomework[2]
        >>afinal;
        course.addNewStudent(aID,aname,asurname);     //To function for two segments of the input
        changeStudentScores(aID,aquiz,ahomework,afinal);
        break;
    case 2:
        cout<<"Enter student ID"<<endl;
        cin>>bID;
        course.getStudentInfo(bID);
        break;
    case 3:
        cout<<"Enter student's ID and his/her new scores:quiz_scores(4 value),hw_scores(3 value),final_score(1 value)"<<endl;
        cin>>cID>>cquiz[0]
        >>cquiz[1]>>cquiz[2]>>cquiz[3]
        >>chomework[0]>>chomework[1]>>chomework[2]
        >>cfinal;
        changeStudentScores(cID,cquiz,chomework,cfinal);
        break;
    case 4:
        cout<<"Enter new weights between (Quiz,Homework,Final) as Integer"<<endl;
        cin>>cweightQ>>cweightHW>>cweightF;
        course.updateWeights(cweightQ,cweightHW,cweightF);
        course.getweightQ();
        break;
    case 5:
        course.showAverage();
        break;
    case 6:
        cout<<"Enter Threshold:";
        cin>> threshold;
        showAbove(threshold);
        break;
    case 7:
        cout<<"Enter Threshold:";
        cin>> threshold;
        showBelow(threshold);
        break;
    case 8:
        cout<<"Program closed";
        exit(0);
        break;
}

}

return 0;
}
