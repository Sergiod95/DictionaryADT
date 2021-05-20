#include <iostream>
#include <string>

using namespace std;

template <class KeyType, class ItemType>
class Entry
{
    private:
        ItemType item;
        KeyType searchKey;
        Entry* next = nullptr;
        
    protected:
        void setKey(const KeyType& searchKey);
    public:
        Entry()
        {
            Entry* next = nullptr;
        };
        
        Entry(ItemType newEntry, KeyType Key)
        {
            item = newEntry;
            searchKey = Key;
            next = nullptr;
            
        };
        
        // modify the item and recover the key.
        ItemType getItem()const
        {
            return item;
        };
        
        KeyType getKey()const
        {
            return searchKey;
        };
        
        void setItem(const ItemType& newEntry)
        {
            item = newEntry;
        };
        
        // getNext and setNext to organize the pointers
        Entry<KeyType, ItemType>* getNext()
        {
            return next;
        };
        
        void setNext(Entry* newEntry)
        {
            next = newEntry;
        };
        
        //print item and search key but can be modified.
        void print()
        {
            cout<<item;
            cout<<" ";
            cout<<searchKey<<endl;
        };
        
};

template <class Entry, class KeyType, class ItemType>
class dictionaryADT
{
    private:
    // max_size in case it need to be modified for other uses
        const int max_size = 50;
        Entry* dict[50] ={};
        int itemCount = 0;
    public:
        dictionaryADT()
        {
           
        };
        
        
        bool isEmpty()
        {
            if(itemCount==0)
                return 1;
                
            return 0;
        };
        
        int getNumberOfItems()
        {
            return itemCount;
        };
        
        // add function search if there is no entry on the index if there is one it is added next to it; if not is added to the index.
        bool add(ItemType newItem, KeyType searchKey)
        {
            int hashNumber = hashing(searchKey);
            

            if(dict[hashNumber] == nullptr)
            {

                dict[hashNumber] = new Entry(newItem,searchKey);

            }
                
            else
            {

                Entry* oldEntry = dict[hashNumber];
                dict[hashNumber]= new Entry(newItem,searchKey);
                dict[hashNumber]->setNext(oldEntry);
                
            }
            itemCount++;
        };
        
        bool remove_entry(KeyType searchKey)
        {
            int hashNumber = hashing(searchKey);
            
            if(dict[hashNumber] == nullptr)
                return 0;
                
            Entry* currentPtr = dict[hashNumber];
            do
            {
                if(dict[hashNumber] -> getKey == searchKey)
                {
                    dict[hashNumber] = dict[hashNumber]->getNext();
                    return 1;
                }
                currentPtr = currentPtr -> getNext();
            }while(currentPtr != nullptr);
            return 0;
            
        };
        
        void clear()
        {
            for(int i = 0; i<max_size; i++)
            {
                dict[i]=nullptr;
            }
                
        };
        
        ItemType getItem(KeyType searchKey)
        {
            int hashNumber = hashing(searchKey);
            
            if(dict[hashNumber] == nullptr)
                return 0;
                
            Entry* currentPtr = dict[hashNumber];
            do
            {
                if(dict[hashNumber] -> getKey == searchKey)
                {
                    return dict[hashNumber] -> getItem();
                }
                currentPtr = currentPtr -> getNext();
            }while(currentPtr != nullptr);
            return 0;
        };
        
        bool contains(KeyType searchKey)
        {
            int hashNumber = hashing(searchKey);
            
            if(dict[hashNumber] == nullptr)
                return 0;
                
            Entry* currentPtr = dict[hashNumber];
            do
            {
                if(dict[hashNumber] -> getKey == searchKey)
                {
                    return 1;
                }
                currentPtr = currentPtr -> getNext();
            }while(currentPtr != nullptr);
            return 0;
        };
        
        //add all the digits of the number; can be modified for other implementations.
        int hashing(KeyType searchKey)
        {
            int result = 0;
            while (searchKey != 0)
            {
                result = result + searchKey % 10;
                searchKey = searchKey / 10;
            }
            return result;
        };
        
        // test print to show the Item, searchkey and the assigned Hashing number.
        void printTest()
        {
            for(int i = 0; i<max_size; i++)
            {
                if(dict[i] != nullptr)
                {
                    dict[i]->print();
                    cout<<"Hashing number: ";
                    cout<<hashing(dict[i]->getKey())<<endl;
                    if(dict[i]->getNext() != nullptr)
                    {
                        Entry* dummy = dict[i]->getNext();
                        do
                        {
                            dummy->print();
                            cout<<"Hashing number: ";
                            cout<<hashing(dict[i]->getKey())<<endl;
                            dummy = dummy -> getNext();
                        }while(dummy != nullptr);
                    }
                }
            }
        };
        

};

int main()
{
    //test with historical moments using the date as the search key(month/day/year which translates to mmddyyyy or mddyyyy if the month has a 0 for the first digit), the hashing is adding all the digits together.
    dictionaryADT<Entry<int,string>,int,string> test;
    test.add("Moon Landing",7201969);
    test.add("End World War II",9021945);
    test.add("Bombing of Pearl Harbor",12071941);
    test.add("United States Declaration of Independence",7041776);
    test.add("WWII begins as Germany invades Poland",9011939);
    test.add("First Atomic Bomb dropped in Hirishima",8061945);
    test.add("Congress passes 13th Amendment abolishing slavery",1311865);
    test.add("Ponce de Leon claims Florida for Spain",4081513);

    test.printTest();
    return 0;
}
