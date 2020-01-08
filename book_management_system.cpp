//  BOOK DATA RECORDING SYSTEM - BY SARWAR ALI
//  Header Files Included
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
//  Function Declarations
int menu();
void end_window();
void start_window();
//  Book Data Type Declaration by Declaring Class
class book
{
    private:
     int book_id;
     char title[20];
     float price;
    public:
        book() //  Default Constructor
        {   book_id=0;
            strcpy(title,"No Title");
            price=0;
        }
        void get_book_data() //  Function to Take User Input
        {
            cout<<endl<<"\t\tEnter Book-id:";
            cin>>book_id;
            fflush(stdin);
            cout<<endl<<"\t\tEnter Title:";
            gets(title);
            cout<<endl<<"\t\tEnter Price:";
            cin>>price;
        }
        void show_book_data() //  Function to Show the Output
        {

            cout<<"\t\t\t  Book-id : "<<book_id<<endl<<"\t\t\t  Title : "<<title<<endl<<"\t\t\t  Price : "<<price<<endl<<endl;
        }
        int store_book();
        void view_books();
        void search_book(char*);
        int delete_book(char*);
        int update_book(char*);
};
int book::store_book() //  Function to Store the Record in File
{
    if(book_id==0&&price==0)
    {
        cout<<endl<<"\t\tBook Not Initialized !!";
        return 0;
    }
    else
    {
        ofstream fout;
        fout.open("file1.dat",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return 1;
    }
}
void book::view_books() //  Function to Show All Records
{
    ifstream fin;
    fin.open("file1.dat",ios::in|ios::binary);
    if(!fin)
        cout<<endl<<"\t\tFile Not Found !!";
    else
        {
        if(!fin.read((char*)this,sizeof(*this)))
          cout<<endl<<"\t\tSorry !! No Record Found...File is Empty";
       else{
        while(!fin.eof())
        {
            show_book_data();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        }}
}
void book::search_book(char *t) //  Function to Search any Record
{
    int counter=0;
    ifstream fin;
    fin.open("file1.dat",ios::in|ios::binary);
    if(!fin)
        cout<<endl<<"\t\tFile Not Found !!";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,title))
            {
                show_book_data();
                counter++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(counter==0)
            cout<<endl<<"\t\tSorry !! Record Not Found";
    }
    fin.close();
}
int book::delete_book(char *t) //  Function to Delete Any Record
{
    ifstream fin;
    ofstream fout;
    int flag=0;
    fin.open("file1.dat",ios::in|ios::binary);
    if(!fin)
        cout<<endl<<"\t\tFile Not Found !!";
    else
    {
        fout.open("tempfile.dat",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(t,title))
            {
                fout.write((char*)this,sizeof(*this));
            }
            if(strcmp(t,title)==0)
                flag=1;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        if(flag==1)
        {
            remove("file1.dat");
            rename("tempfile.dat","file1.dat");
            return 1;
        }
        else
        {
           cout<<endl<<"\t\tInvalid Record !! Record Not Found";
           remove("tempfile.dat");
           return (-1);
        }
    }
}
int book::update_book(char *t) //  Function to Update any Record
{
    fstream file; int flag=0;
    file.open("file1.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(t,title))
        {
            flag=1;
            get_book_data();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
    if(flag==0)
    {
        cout<<endl<<"\t\tRecord to be updated does not Exist !!";
        return -1;
    }
    else
        return 1;
}
int menu() //  Function for displaying menu
{
    int ch;
    cout<<"\n\n\n\t\t    Book Data Recording Management System\n"<<endl;
    cout<<endl<<"\t\t\t  1.Insert Record of Book"<<endl;
    cout<<endl<<"\t\t\t  2.Show All Book Records"<<endl;
    cout<<endl<<"\t\t\t  3.Search Book Record"<<endl;
    cout<<endl<<"\t\t\t  4.Delete Book Record"<<endl;
    cout<<endl<<"\t\t\t  5.Update Book Record"<<endl;
    cout<<endl<<"\t\t\t  6.Exit"<<endl;
    cout<<endl<<"\n\t\t\tEnter Your Choice:";
    cin>>ch;
    return ch;
}
void start_window() //  Function for Starting Window
{

   system("cls");
   system("color 47");
   cout<<"\n\n\n\n\n\n\t\t   BOOK DATA RECORDING MANAGEMENT SYSTEM !!"<<endl;
   cout<<endl<<"\t\t\t Github - sarwar1227"<<endl;
   cout<<endl<<"\t\t\t Coded By - SARWAR ALI "<<endl;
   cout<<endl<<"\t\t\t Language Used - C++"<<endl;
   cout<<endl<<"Source Code available at : https://github.com/sarwar1227/BOOK_MANAGEMENT_SYSTEM"<<endl;
   cout<<endl<<"\n\t\t\tPress Any Key to Continue.....!!!!\n"<<endl;
   getch();
   system("cls");
   char c=219;
   cout<<"\n\n\n\n\n\n\n\n\t\t\t\tLOADING...\n\n\t\t\t";
   for(int i=0;i<25;i++)
        {
            cout<<c;
            Sleep(25);
        }
    system("cls");
    system("color 2e");
}
void end_window() //  Function for Ending window
{
    system("cls");
    system("color 0e");
    cout<<"\n\n\n\n\n\n\t\tA Very Warm Thanks for using this Application !!\n\n\n\t\t\tHope You Have a Good Day\n\n\n\n\t\t\tPress amy key to Exit...";
    getch();
}
int main() //  Main Function
{
    book b; char temp[25]; int x;
    start_window();
    while(1)
    {
        system("cls");
        switch(menu())
        {
            case 1:
                b.get_book_data();
                b.store_book();
                cout<<endl<<"\t\tBook Record Successfully Inserted !!";
                break;
            case 2:
                b.view_books();
                break;
            case 3:
                cout<<endl<<"\t\tEnter Book Title for Searching:";
                fflush(stdin);
                gets(temp);
                b.search_book(temp);
                break;
            case 4:
                cout<<endl<<"\t\tEnter Book Title for Deleting:";
                fflush(stdin);
                gets(temp);
                x=b.delete_book(temp);
                if(x!=-1)
                 cout<<endl<<"\t\tRecord Successfully Deleted !!";
                break;
            case 5:
                cout<<endl<<"\t\tEnter Book Title for Updating:";
                fflush(stdin);
                gets(temp);
                x=b.update_book(temp);
                if(x!=-1)
                    cout<<endl<<"\t\tRecord Successfully Updated !!";
                break;
            case 6:
                end_window();
                exit(0);
            default:
                cout<<endl<<"\t\tYou Entered Invalid Choice !!";
            }
        getch();
    }
}
}
