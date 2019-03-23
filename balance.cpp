//Sahil Sheth
//CPSC 301-01
//Assignment 2 File I/O

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

struct  PERSON {
    char  Name[20];
    float Balance;
  };


PERSON * readData(int &N);
void Display(PERSON a[], int size);
void NewCopy(string addToFile, PERSON a[], int size);
void FindRichest(PERSON a[], int N);
void Deposit(PERSON *a, int size, string customerName, float amount);
void printmenu();



void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records"<< endl;
    cout << "2. Deposit funds"<< endl;
    cout << "3. Find Highest Balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

//puts information into the array from text file
PERSON * readData(int &N)
{
    string line;
    ifstream inFile;
    inFile.open("data.txt");
    while(!inFile.eof())
    {
        getline(inFile, line);
        N++;
    }
    N--;
    inFile.close();
    
    PERSON * people = NULL;
    people = new PERSON[N];
    string firstName;
    string lastName;
    string fullName;
    ifstream anotherFile;
    anotherFile.open("data.txt");
    if(anotherFile)
    {
        for(int i=0; i< N; i++)
        {
            anotherFile >> firstName;
            anotherFile >> lastName;
            anotherFile >> people[i].Balance;
            fullName = firstName + " " + lastName;
            strcpy(people[i].Name, fullName.c_str());
            
        }
    }
    
    anotherFile.close();
    return people;
    
}


//the records will be listed with the full names and balances
void Display(PERSON a[], int size)
{
  cout << "Name" << "  " << "Balance" << endl;
  cout<< "-----------------------------------------------" << endl;
  for(int i = 0; i < size; i++)
  {
    cout << a[i].Name << " " << a[i].Balance << endl;
  }
}

//Copy array a in the same file
void NewCopy(string addToFile, PERSON a[], int size)
{
  fstream newFile;
  newFile.open(addToFile.c_str());
  for(int i = 0; i< size; i++)
  {
   newFile << a[i].Name << " " << a[i].Balance << endl;
  }
    newFile.close();
    cout << "File Updated..." << endl;
}

//Display the name of customer with maximum balance
void FindRichest(PERSON a[], int size)
{
 //Create 2 PERSON objects that will be holding the balances
 PERSON tempBalance, anotherTempBalance;
 //create the local char array to be able to print name
 char names[20];
 //get float number to equal to the initial balance
 float rich = a[0].Balance;
 for(int i = 0; i < size; i++)
 {
     //make tempBalance equal the initial array
    tempBalance.Balance = a[i].Balance;
     
     //make anotherTempBalance equal the initial array +1
    anotherTempBalance.Balance = a[i+1].Balance;
     //if the balance is greater than the initial balances
    if(anotherTempBalance.Balance > tempBalance.Balance)
    {
        //update to include the name that has the highest balance
        rich = a[i+1].Balance;
        strcpy(names, a[i+1].Name);
    }
 }
 
   cout << "Highest balance: " << names << endl;

 


 

}

//Function intended to deposit balances and update them
void Deposit(PERSON *a, int size, string customerName, float amount)
{

    cout << "Enter name: " << endl;
    getline(cin, customerName);
    
    for(int i = 0; i < size; i++)
    {
        if(customerName == a[i].Name)
        {
            cout << "Amount: " << endl;
            cin >> amount;
            a[i].Balance += amount;
            cout << "New Balance: " << a[i].Balance << endl;
        }
        
        
    }

}






int main()
{
    int choice;
    int N = 0;
    string inputName;
    float userAmount = 0.0;
    PERSON * array = NULL;
    array = readData(N);
    
    do
    {
        
        printmenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Act on display
                Display(array, N);
                break;
                
            case 2:
                // Act on deposit
          
                
                cin.ignore();
                Deposit(array, N, inputName, userAmount);
                break;
                
            case 3:
                // Act highest balance
                FindRichest(array, N);
                break;
                
            case 4:
                // Act on update records
                NewCopy("data.txt", array, N);
                break;
                
            case 5:
                // Must call update records here before exiting the program
                NewCopy("data.txt", array, N);
                break;
                
            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
    } while(choice != 5);
    return 0;
}

