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

void Read(PERSON myArray[], int size);
void Display(PERSON a[], int size);
void NewCopy(string addToFile, PERSON a[], int size);
void FindRichest(PERSON a[], int N);
void Deposit(string customerName, PERSON a[], int size);


//puts information into the array from text file
void Read(PERSON myArray[], int size)
{
    string name;
    ifstream file;
    file.open("data.txt");
    string firstName;
    string lastName;
    float num;
    int i = 0;
    while(!file.eof())
    {
        //code from class
        file >> firstName;
        file >> lastName;
        file >> num;
        name = firstName + " " + lastName;
        strcpy(myArray[i].Name, name.c_str());
        myArray[i].Balance = num;
        i++;
    }
    
    file.close();
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
 
   cout << "The customer with maximum balance is: " << names << endl;

 


 

}

//Function intended to deposit balances and update them
void Deposit(string customerName, PERSON a[], int size)
{

  float input;
  cout << customerName << ", how much would you like to deposit? " << endl;
  cin >> input;
  for(int i= 0; i < size; i++)
  {
      //if the user inputted a name that is similar to one of the names in the text file
    if(customerName == a[i].Name)
   {
       //the current balance will be increased by whatever input the user selected
      a[i].Balance += input;
      cout << "New balance: " << a[i].Balance <<endl;
   }
 }
    
    cout << endl;

}





int main()
{
  
   string name;
   string custName;
   string temp;
   ifstream file;
   file.open("data.txt");
    int N = 0;
    
    //while loop to receive the number of lines in the text file
   while(!file.eof())
   {
       getline(file, temp);
       N++;
   }
    //decrement the N to be able to get the correct number of lines
    N--;
    file.close();
    cout << N << endl;
    
    //create an array that is large enough to hold all of the records in the file
    PERSON a[N];
    
    //Read in the file
    Read(a, N);
    
    //Calling all records in array
    Display(a, N);
    //Call customer with highest balance
    FindRichest(a, N);
    
    //ask user to input a name and then call the deposit function
    cout << "Enter your full name to deposit money: ";
    getline(cin, custName);
    Deposit(custName, a, N);
    
    //Call the copied array  in the same file
    NewCopy("data.txt", a, N);
    
   return 0;
    
}
