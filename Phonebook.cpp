#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;

const int TABLE_SIZE = 128;

/*
* PhoneBookNode Class Declaration
* A PhoneBookNode represents an entry into the Phone book hash table
*/

class PhoneBookNode {
   public:
   string name; // represents the key
   string phoneNumber; // represents the value
   PhoneBookNode* next; // represents the next node with the same key.
   // Constructor to initialize a node
   
   PhoneBookNode(string name, string number){
      this->name = name;
      this->phoneNumber = number;
      this->next = NULL;
   }
};

/*
* Phone Book HashMap Class Declaration
* A Phone Book stores all the <name, numbers> entries into itself.
*/
class PhoneBook {
   private:
   PhoneBookNode** htable; // represents the hash table
   public:
   
   // default Constructor to initialize the PhoneBook to its initial state
   
   PhoneBook() {
      
      // create an initial hash table of size 128
      
      htable = new PhoneBookNode*[TABLE_SIZE];
      for (int i = 0; i < TABLE_SIZE; i++)
         htable[i] = NULL;
   }
   
   // destructor to dynamically delete memory space taken up by the hash table
   
   ~PhoneBook() {
      for (int i = 0; i < TABLE_SIZE; ++i) {
         PhoneBookNode* entry = htable[i];
         while (entry != NULL) {
            PhoneBookNode* prev = entry;
            entry = entry->next;
            delete prev;
         }
      }
      delete[] htable;
   }
   /*
   * Hash Function: This function obtains the key value by adding the ASCII values of
   * all the characters present int he name. And then, it obtains the hash value from the key.
   */
   int HashFunc(string name) {
      int key = 0;
      // Key = sum of ASCII of all characters present in the string 'name'
      for(int i=0; i<name.length(); i++) {
         key += name.at(i);
      }
      // hash value = key % TABLE_SIZE
      return key % TABLE_SIZE;
   }
   // Insert a Phone number for a given name
   
   void Insert(string name, string number) {
      
      // first obtain the hash value
      
      int hash_val = HashFunc(name);
      PhoneBookNode* prev = NULL;
      PhoneBookNode* entry = htable[hash_val];
      
      // if the given name already has some linked to it,
      // then we need to add this number at the end.
      //loop to first find the node after which this number needs to be inserted.
      
      while (entry != NULL) {
         prev = entry;
         entry = entry->next;
      }
      if (entry == NULL) {
         // insert the number at this position
         entry = new PhoneBookNode(name, number);
         if (prev == NULL) {
            htable[hash_val] = entry;
         } else {
            prev->next = entry;
         }
      }
      // the name given doesn't have any number linked to it.
      // Hence, link this number with the given name.
      else {
         entry->phoneNumber = number;
      }
      cout<<"\n"<<name<<" => "<<number<<" is added to your phone directory \n";
   }
   // Retrieves the numbers linked to the given name
   
   int Retrieve(string name)
   {
      bool flag = false; // determines whether the provided name has any number linked to it.
      int hash_val = HashFunc(name);
      PhoneBookNode* entry = htable[hash_val];
      // if the name has multiple numbers linked to it, print everyone of them.
      while (entry != NULL) {
         if (entry->name == name) {
            cout<<entry->phoneNumber<<" ";
            flag = true;
         }
         entry = entry->next;
      }
      // if flag is false, it means that the name does not have any number linked to it.
      if (!flag)
         return -1;
   }
};

// Main Contains Menu

int main()
{
   PhoneBook hash;
   string name, number;
   int choice;
   while (1)
   {
      cout<<"\n1.Insert element into the Phone Book"<<endl;
      cout<<"2.Retrieve numbers using name"<<endl;
      cout<<"3.Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>choice;
      switch(choice)
      {
         case 1:
         cout<<"Enter the name: ";
         cin>>name;
         cout<<"Enter the phone number: ";
         cin>>number;
         hash.Insert(name, number);
         break;
         case 2:
         cout<<"Enter the name to be searched: ";
         cin>>name;
         cout<<"Number(s) linked to name "<<name<<" : ";
         if (hash.Retrieve(name) == -1) {
            cout<<"No number(s) found with the name: "<<name<<endl;
            continue;
         }
         break;
         case 3:
         cout<<"Thank You";
         exit(1);
         default:
         cout<<"\nEnter correct option\n";
      }
   }
   return 0;
}