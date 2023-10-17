#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "Weapon.h"
#include "Armour.h"
#include <vector>
#include <algorithm>
#include <memory>

class Inventory{

public:
    Inventory();
    Inventory(const Inventory &obj);
    virtual ~Inventory();
    inline int size() const { return this->noOfItems;}
	inline int smrtSize() { return this->smrtInv.size(); }
    Item& operator[](const int index);
	void operator=(const Inventory &obj);
    void addItem(const Item &Item);
    void removeItem(int index);


    inline void debugVector(){
		cout << "==INVENTORY==\n";
        for(this->smrtInvIt = smrtInv.begin(); smrtInvIt != smrtInv.end(); smrtInvIt++){
            cout << (*smrtInvIt)->debugPrint() << endl;
        }
    }

	inline string getInvAsString() {

		string str = "";

		for (this->smrtInvIt = smrtInv.begin(); smrtInvIt != smrtInv.end(); smrtInvIt++) {
			str += (*smrtInvIt)->toString() + "\n";
		}

		return str + "\n";
	}

	inline std::string getInvItemAsString(int choice){

        string str = "";
        choice--;
        std::advance(smrtInvIt, choice);

        str = smrtInv[choice]->toString();
		return str + "\n";
	}

	inline std::vector<std::string> getInvAsVecOps(){

        std::vector<std::string> result;
        std::string str;
        for(smrtInvIt = smrtInv.begin(); smrtInvIt != smrtInv.end(); smrtInvIt++){

            str += to_string(smrtInvIt - smrtInv.begin()+1) + ": ";
            str += (*smrtInvIt)->getName() + " " + (*smrtInvIt)->getTypeStr();
            result.push_back(str);
            str = "";
        }

        return result;
	}

	inline string getInvAsStringSave() {
		string str;

		for (this->smrtInvIt = smrtInv.begin(); smrtInvIt != smrtInv.end(); smrtInvIt++) {
			if ((*smrtInvIt)->getItemType() == itemTypes::WEAPON) {
				str += (*smrtInvIt)->toStringSave();
			}
		}
		str += "\n";
		for (this->smrtInvIt = smrtInv.begin(); smrtInvIt != smrtInv.end(); smrtInvIt++) {
			if ((*smrtInvIt)->getItemType() == itemTypes::ARMOUR) {
				str += (*smrtInvIt)->toStringSave();
			}
		}

		return str;
	}

    //Test vector
    void AddItemVector(Item* i);
    void removeItemVector(Item* i);

    void addItemVectorSmart(shared_ptr<Item>);
	shared_ptr<Item> findItemSmart(int index);
    void removeItemVectorSmart(shared_ptr<Item>);

private:
    int capacity;
    int noOfItems;

    vector<shared_ptr<Item>> smrtInv;
    vector<shared_ptr<Item>>::iterator smrtInvIt;
    vector<shared_ptr<Item>>::iterator smrtDEl;


    vector<Item*> inv;
    vector<Item*>::iterator invIt;
    vector<Item*>::iterator del;


    //TODO: Probably should be a vector
    Item** itemArray;

    void initialise(const int from = 0);
    void expand();
};

#endif // INVENTORY_H

