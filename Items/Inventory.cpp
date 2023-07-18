#include "Inventory.h"

Inventory::Inventory(){
    capacity = 5;
    noOfItems = 0;
    itemArray = new Item*[capacity];
    this->initialise();
}

Inventory::~Inventory(){
    for(int i = 0; i < noOfItems; i++){
        delete this->itemArray[i];
    }

    delete[] itemArray;
}

Inventory::Inventory(const Inventory &obj){
    this->capacity = obj.capacity;
    this->noOfItems = obj.noOfItems;
    this->itemArray = new Item*[this->capacity];

    for(int i = 0; i < this->noOfItems; i++){
        this->itemArray[i] = obj.itemArray[i]->clone();
    }

    initialise(this->noOfItems);

	this->smrtInv = obj.smrtInv;
}

Item& Inventory::operator[](const int index){
    if(index < 0 || index >= this->noOfItems)
        throw("BAD INDEX!");

    return *this->itemArray[index];
}

void Inventory::operator=(const Inventory &obj) {
	for (size_t i = 0; i < this->noOfItems; i++){
		delete this->itemArray[i];
	}
	delete[] this->itemArray;

	this->capacity = obj.capacity;
	this->noOfItems = obj.noOfItems;
	this->itemArray = new Item*[this->capacity];

	for (size_t i = 0; i < this->noOfItems; i++){
		this->itemArray[i] = obj.itemArray[i]->clone();
	}

	initialise(this->noOfItems);
}

void Inventory::addItem(const Item &item){

    if(this->noOfItems >= this->capacity){
        expand();
    }

   itemArray[this->noOfItems++] = item.clone();
}

void Inventory::removeItem(int index){
	if (index < 0 || index >= this->noOfItems) {
		throw("Out of bounds - remove item INVENTORY");
	}

	delete this->itemArray[index];
	this->itemArray[index] = this->itemArray[this->noOfItems-1];
	this->itemArray[this->noOfItems] = nullptr;
}

void Inventory::initialise(const int from){

    for(size_t i = from; i < capacity; i++){
        itemArray[i] = nullptr;
    }
}

void Inventory::expand(){
    this->capacity *= 2;

    Item** tempArray = new Item*[this->capacity];

    for(size_t i = 0; i < this->noOfItems; i++){
        tempArray[i] = this->itemArray[i];
    }

    delete[] this->itemArray;

    this->itemArray = tempArray;

    this->initialise(noOfItems);
}

void Inventory::AddItemVector(Item* i){
    inv.push_back(i);
}

void Inventory::addItemVectorSmart(shared_ptr<Item> i){
    //smrtInv.push_back(i);
    smrtInv.push_back(i);
}

shared_ptr<Item> Inventory::findItemSmart(int index) {
	smrtInvIt = smrtInv.begin();
	std::advance(smrtInvIt, index);

	return *smrtInvIt;
}

void Inventory::removeItemVectorSmart(shared_ptr<Item> i){
    smrtDEl = find(smrtInv.begin(), smrtInv.end(), i);
    smrtInv.erase(smrtDEl);
}

void Inventory::removeItemVector(Item* i){
    del = find(inv.begin(), inv.end(), i);
    inv.erase(del);
}

