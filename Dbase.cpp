#include<iostream>
#include<vector>
#include<string.h>
#include<iomanip>
#include<fstream>
using namespace std;

struct Date
 {
    unsigned short int Year;
    unsigned short int Month;
    unsigned short int Day;
 }; 
 struct Student 
 {
    string Firstname;
    string Lastname;
    unsigned long long int ID; 
    Date Birthday; 
    float Grade;
 };
           
 struct Class
{
    string ClassName;
    float Average; 
    unsigned short int Capacity;
    vector <Student> Data; 
 }; 
void SelectClass(string);
void AddClass(string);//
void RemoveClass(string);
void AddStudent(string, Date, unsigned long int, float);
void RemoveStudent(unsigned long long int);
void Search(unsigned long long int); //search by id
void Search(string, string); //search by fullname
void ShowClass(string);//show selected class
void ShowAll();//show information of classes
void showselect();//show selected class
void SortByName(); //sort by name
void SortByID(); //sort by id
void Save();//save in files
void start();
void BasuHelp();//help for commmands line
void BasuRank();//Rank A, B, C ,D ,E
vector<Class> Database;
string choose;//
int main()
{
    start();
    return 0;
}
void start()
{
    vector<string> command; 
    while(1)
    {
       cout<<"-------------------------------------------"<<endl;
       cout<<"Data base\\"<<choose<<endl;
       cout<<"-------------------------------------------"<<endl;
       cout<<"enter command:"<<endl;
       string str;
       string temp;
       int countspace=0;//for count spaces
       int tempspace=0;//compare with space
       getline(cin,str);
       for(auto j:str)
          if(j==' ')
             countspace++;
            // cout<<countspace;
       for(char i:str)
       { 
          if(tempspace==countspace)
             temp+=i;
          else
          {
          if(i != ' ')
          temp+=tolower(i);//for lower alphba
          else
          {   
          command.push_back(temp);
          temp.clear();
          tempspace++;
          //cout<<tempspace;
          }
          }
       }
       command.push_back(temp); 
      
       if(command[0]=="exit"&& command.size()==1)
          break;
       else if((command.size())==4 && command.at(0)=="basu")
       {   
          if(command.at(1)=="add" && command.at(2)=="class")
             AddClass(command.at(3));
                
          else if(command.at(1)=="select" && command.at(2)=="class")
          { 
            // choose=command.at(3);
             SelectClass(command.at(3));
          }
          else if(command.at(1)=="remove"&& command.at(2)=="class" )
             RemoveClass(command.at(3));
                
          else if(command.at(1)=="remove"&& command.at(2)=="student" )
          {  
             RemoveStudent(stoull(command.at(3)));
 
          }
          else
             cerr<<"uncorrect comand"<<endl;
         
   
       }
      else if((command.size())==3 && command.at(0)=="basu")
      {
          if(command.at(1)=="add" && command.at(2)=="student")
          {      
             string nameNewStd;
             unsigned long long int idnew;
             float mark;
             Date newdate;
             cout<<"enter FullName new std:"<<"(---Length of first name=5---Lsat name=7---)"<<endl;
             cin>>nameNewStd;
             cout<<"enter grade new std:"<<endl;
             cin>>mark;
             cout<<"enter id new std:"<<"(---length=10---)"<<endl;
             cin>>idnew;
             cout<<"enter birthday new student:(****Year****)"<<endl;
             cin>>newdate.Year;
             cout<<"enter birthday new student:(****Month****)"<<endl;
             cin>>newdate.Month;
             cout<<"enter birthday new student:(****Day****)"<<endl;
             cin>>newdate.Day;
             AddStudent(nameNewStd,newdate,idnew, mark);
          
          }
          else if(command.at(1)=="show" && command.at(2)=="select")
          {
             showselect();
          }
       
          else if(command.at(1)=="select"&& command.at(2)=="none")
          { 
             choose.clear();
             cout<<"Database\\"<<endl;
          }
        
          else if(command.at(1)=="search")
          {
                   
             if(command.at(2).size()==10)  
             {
              Search(stoull(command.at(2)));
             }
             if(command.at(2).size()==12)
             {  
                string fn;//first name
                string ln;//last name
                int count=0;//for count in range based for
                for(auto i:command.at(2))
                {
                   count++;
                   if(count<=5)
                   fn+=i;
                   else
                   ln+=i;
                }
                Search(fn,ln);
             }
          }

          else if(command.at(1)=="show")
             ShowClass(command.at(2));

         
          else if(command.at(1)=="sort" && command.at(2)=="name")
             SortByName();
         
          else if(command.at(1)=="sort" && command.at(2)=="id")
             SortByID();
        
          else
          {
             cerr<<"uncorrect comand"<<endl;
          }
       
  
       }

       else if((command.size())==2 && command.at(0)=="basu")
       {
          if(command.at(1)=="show")
             ShowAll();  
      
          else if(command.at(1)=="save")
             Save();
      
          else if(command.at(1)=="help")
             BasuHelp();
       
          else if(command.at(1)=="clear")
             system("cls");
       
          else if(command.at(1)=="rank")
             BasuRank();
      
          else 
             cerr<<"uncorrect comand"<<endl;
       }
       
       else
          cerr<<"uncorrect comand "<<endl;
   
       command.clear();

    }  
}
//-------------------------------------------------------------------------------------------------
void AddClass(string cl)
{
    Class newclass;
    ifstream inpute(cl.c_str(),ios::in) ;
    if(!inpute)
       exit(1);
    getline(inpute,newclass.ClassName);
    // cout<<newclass.ClassName<<endl;
     inpute>>newclass.Capacity;
    // cout<<setw(2)<<newclass.Capacity<<endl;
    for(int i=0;i<newclass.Capacity;i++)
    {
       char slash;
       Student newstudent;
       inpute>>newstudent.Firstname;
       inpute>>newstudent.Lastname;
       inpute>>newstudent.Birthday.Year>>slash>>newstudent.Birthday.Month>>slash>>newstudent.Birthday.Day;
       inpute>>newstudent.Grade;
       inpute>>newstudent.ID;
       newclass.Data.push_back(newstudent);

    }
    Database.push_back(newclass) ;
}
//--------------------------------------------------------------------------------------------

void SelectClass(string selectingclass)
{
    choose=selectingclass;
   // cout<<" Database\\";
    //cout<<selectingclass<<endl;
}
//--------------------------------------------------------------------------------------------
void RemoveClass(string removingclass)
{ 
    int counter=0;
    for(auto i:Database)
    { /* string temp=" ";
      for(auto j:i.ClassName)
      temp+=tolower(j);
       */
       if(i.ClassName==removingclass)
       {
           Database.erase(Database.begin()+counter);
          break;
       }
       counter++;

    }

}
//------------------------------------------------------------------------------------------------------

void RemoveStudent(unsigned long long int username)
{
    for(auto &i:Database)
       if(i.ClassName==choose)
       {
          int count=0;
          for(auto j:i.Data)
          {
             if(j.ID==username)
             i.Data.erase(i.Data.begin()+count);
             count++;
          }
          i.Capacity--;
          break;
       }

}
//----------------------------------------------------------------------------------------------------------
void showselect()
{
    for(auto &i:Database)
      if(i.ClassName==choose)
      {
       for(auto j:i.Data)
       {
          cout<<j.Firstname<<" "<<j.Lastname<<"  ";
          cout<<j.Birthday.Year<<"\\";
          cout<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
          cout<<setw(2)<<j.Birthday.Day<<"  ";
          cout<<setfill('0')<<setw(5)<<j.Grade<<"  ";
          cout<<j.ID<<endl;
       }
       break;
    }

}
//------------------------------------------------------------------------------------------------------------
void ShowAll()
{
    for(auto k:Database)
    {
       cout<<k.ClassName<<endl;
       cout<<k.Capacity<<endl;
       //cout<<k.Average;
       for(auto j:k.Data)
       { 
          cout<<j.Firstname<<" "<<j.Lastname<<"  ";
          cout<<j.Birthday.Year<<"\\";
          cout<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
          cout<<setw(2)<<j.Birthday.Day<<"  ";
          cout<<setw(5)<<j.Grade;                       
          cout<<" "<<j.ID<<endl;
       }
   cout<<"------------------------------------------"<<endl;
  
  }
}
//------------------------------------------------------------------------------------------------------

void ShowClass(string showingclass)
{
    for(auto &i:Database)
    if(i.ClassName==showingclass)
    {
       for(auto j:i.Data)
       {
          cout<<j.Firstname<<" "<<j.Lastname<<"  ";
          cout<<j.Birthday.Year<<"\\";
          cout<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
          cout<<setw(2)<<j.Birthday.Day<<"  ";
          cout<<setfill('0')<<setw(5)<<j.Grade<<"  ";
          cout<<j.ID<<endl;
       }
       break;
    }
}
//-----------------------------------------------------------------------------------------------
void AddStudent(string fullname, Date birth, unsigned long int idnew, float grd)
{
    for(auto &i:Database)
       if(choose==i.ClassName)
       {  
          int counter=0;
          Student nstudent;
          for(auto &j:fullname)
          {
             counter++;
             if(counter<=5)
                nstudent.Firstname+=j;
             else
                nstudent.Lastname+=j; 
          }
          nstudent.Birthday=birth;
          nstudent.ID=idnew;
          nstudent.Grade=grd;
          i.Data.push_back(nstudent);
          i.Capacity++;
          break;
       }

}
//-------------------------------------------------------------------------------------------------
void Search(unsigned long long int searchingId)
{
    for(auto i:Database)
       if(i.ClassName==choose)
       {
          for(auto j:i.Data)
             if(j.ID==searchingId)
             { 
                cout<<j.Firstname<<" "<<j.Lastname<<"  ";
                cout<<j.Birthday.Year<<"\\";
                cout<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
                cout<<setw(2)<<j.Birthday.Day<<"  ";
                cout<<setfill('0')<<setw(5)<<j.Grade<<"  ";
                cout<<j.ID<<endl;
             }
          break;
       }
 
} 
//--------------------------------------------------------------------------------------------------------

void Search(string fname, string lname)
{
    for(auto i:Database)
       if(i.ClassName==choose)
       {
          for(auto j:i.Data)
             if(j.Firstname==fname && j.Lastname==lname)
             {
                cout<<j.Firstname<<" "<<j.Lastname<<"  ";
                cout<<j.Birthday.Year<<"\\";
                cout<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
                cout<<setw(2)<<j.Birthday.Day<<"  ";
                cout<<setfill('0')<<setw(5)<<j.Grade<<"  ";
                cout<<j.ID<<endl;
             }
          break;
       }
} 
//--------------------------------------------------------------------------------------------------
void SortByName()
{
    for(auto &i:Database)
    {
       if(i.ClassName==choose)
       {
          for(auto &j:i.Data)
          {  
             for(auto &k:i.Data)
             {
                for(int p=0;p<7;p++)
                {
                   if(j.Lastname.at(p) < k.Lastname.at(p))
                   {  
                      Student nstd;
                      nstd=j;
                      j=k;
                      k=nstd;
                      break;
                   }
                   else if(j.Lastname.at(p)==k.Lastname.at(p))
                      continue;
                   else 
                      break;
                }
             }

          }
   /* for(auto m:i.Data)
    cout<<m.Lastname<<endl;*/
          break;
       
       }
   }
}
//---------------------------------------------------------------------------------------------------------
void SortByID()
{
    for(auto &i:Database)
    {
       if(i.ClassName==choose)
       {
          for(auto &j:i.Data)
          {  
             for(auto &k:i.Data)
             {
                for(int p=0;p<10;p++)
                {
                   if(j.ID > k.ID)
                   { 
                      Student nstd;
                      nstd=j;
                      j=k;
                      k=nstd;
                      break;
                   }
                   else if(j.Grade==k.Grade)
                      continue;

                   else 
                      break;
                }
             }
          }
  
          break;
       
       }
   }

} 
//----------------------------------------------------------------------------------------------------------
void Save()
{
    for(auto i:Database)
    {
       string filename;
       cout<<"enter fileName:(L6.basu/L7.basu/....)"<<endl;
       cin>>filename;
       ofstream outpute(filename.c_str(),ios::out);
       if(!outpute)
          exit (1);
       outpute<<i.ClassName<<endl;
       outpute<<i.Capacity<<endl;
       for(auto j:i.Data)
       {
          outpute<<j.Firstname<<" "<<j.Lastname<<"  ";
          outpute<<j.Birthday.Year<<"\\";
          outpute<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
          outpute<<setw(2)<<j.Birthday.Day<<"  ";
          outpute<<setfill('0')<<setw(5)<<j.Grade<<"  ";
          outpute<<j.ID<<endl;
       }

    }
}



//-------------------------------------------------------------------------------------------------------------
void BasuHelp()
{
   cout<<"basu add class (namefile)"<<"\t"<<"--------->"<<"\t"<<"add a class from file"<<"\n\n";
   cout<<"basu remove class (class name)"<<"\t"<<"--------->"<<"\t"<<"remove a student from data"<<"\n\n";
   cout<<"basu add student "<<"\t\t"<<"--------->"<<"\t"<<"add a student to selected class"<<"\n\n";
   cout<<"basu remove student <ID>"<<"\t"<<"--------->"<<"\t"<<"remove a student from selected class by id"<<"\n\n";
   cout<<"basu select class <>Class Name"<<"\t"<<"--------->"<<"\t"<<" to selected  a class"<<"\n\n";
   cout<<"basu select none"<<"\t\t"<<"--------->"<<"\t"<<"none select class"<<"\n\n";
   cout<<"basu search <ID>"<<"\t\t"<<"--------->"<<"\t"<<"Search student by ID"<<"\n\n";
   cout<<"basu search <FullName>"<<"\t\t"<<"--------->"<<"\t"<<"search student by fullname"<<"\n\n";
   cout<<"basu show "<<"\t\t\t"<<"--------->"<<"\t"<<"show all students"<<"\n\n";
   cout<<"basu show <ClassName>"<<"\t\t"<<"--------->"<<"\t"<<"show students of class"<<"\n\n";
   cout<<"basu sort id"<<"\t\t\t"<<"--------->"<<"\t"<<"sort students of selected class by id"<<"\n\n";
   cout<<"basu sort name"<<"\t\t\t"<<"--------->"<<"\t"<<"sort students of selected class by name"<<"\n\n";
   cout<<"basu show select"<<"\t\t"<<"--------->"<<"\t"<<"show students of selected class"<<"\n\n";
   cout<<"basu save"<<"\t\t\t"<<"--------->"<<"\t"<<"save classess in files"<<"\n\n";
   cout<<"basu clear"<<"\t\t\t"<<"--------->"<<"\t"<<"clear system"<<"\n\n";
   cout<<"basu rank"<<"\t\t\t"<<"--------->"<<"\t"<<"rank of students of selected class(A\\B\\C\\D\\E\\) "<<"\n\n";
   cout<<"exit"<<"\t\t\t\t"<<"--------->"<<"\t"<<"for exit"<<"\n\n";
   
}
//-------------------------------------------------------------------------------------------------------
void BasuRank()
{
    for(auto &i:Database)
    {
       if(i.ClassName==choose)//check class selected
       {
          for(auto j:i.Data)
          {
             if(j.Grade>=18)
                cout<<"rank A"<<" ";
             if(j.Grade<18 && j.Grade>=15)
                cout<<"rank B"<<" ";
             if(j.Grade>=12 && j.Grade<15)
                cout<<"rank C"<<" ";
             if(j.Grade>=10 && j.Grade<12)
                cout<<"rank D"<<" ";
             if(j.Grade<10)
                cout<<"rank E"<<" ";  
             cout<<j.Firstname<<" "<<j.Lastname<<"  ";
             cout<<j.Birthday.Year<<"\\";
             cout<<setw(2)<<j.Birthday.Month<<setfill('0')<<"\\";
             cout<<setw(2)<<j.Birthday.Day<<"  ";
             cout<<setfill('0')<<setw(5)<<j.Grade<<"  ";
             cout<<j.ID<<endl;


          }
       }
    }
}
