#include <iostream>
#include "Array.h"

void testSetSize()
{
    std::cout << "\nTEST SET SIZE\n";
    Array<int>* array = new Array<int>(3);

    int a = 12;
    int b = 33;
    int c = 55;
    int d = -123;
    array->add(&a);
    array->add(&b);
    array->display();

    array->setSize(5, 2);
    array->display();
    array->add(&c);
    array->display();
    array->setSize(2, 3);
    array->display();
    array->add(&d);
    array->display();
}

void testRemoveAt()
{
    std::cout << "\nTEST REMOVE AT\n";
    Array<int>* array = new Array<int>(5);
    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;
   
    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->add(&d);

    array->display();
    array->removeAt(2);
    array->display();

    array->removeAt(0);
    array->display();

    array->removeAt(1);
    array->display();

}

void testRemoveAll()
{
    std::cout << "\nTEST REMOVE ALL\n";
    Array<int>* array = new Array<int>(5);
    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;

    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->add(&d);

    array->display();
    array->removeAll();
    array->display();
}

void testFreeExtra()
{
    std::cout << "\nTEST FREE EXTRA\n";
    Array<int>* array = new Array<int>(5);
    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;

    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->add(&d);

    array->display();
    array->freeExtra();
    array->display();
}

void testSetAt()
{
    std::cout << "\nTEST SET AT\n";
    Array<int>* array = new Array<int>(5);
    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;

    array->setAt(0, &a);
    array->display();
    array->setAt(2, &b);
    array->display();
    array->setAt(4, &c);
    array->display();
    
}

void testAppend()
{
    std::cout << "\nTEST APPEND\n";
    Array<int>* array1 = new Array<int>(3);
    Array<int>* array2 = new Array<int>(2);

    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;

    array1->add(&a);
    array1->add(&b);

    array2->add(&c);
    array2->add(&d);

    array1->append(*array2);
    array1->display();
}

void testInsertAt()
{
    std::cout << "\nTEST INSERT AT\n";
    Array<int>* array = new Array<int>(3);

    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;
    int e = -7;
    int f = 0;

    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->display();
    array->insertAt(1, &d);
    array->display();
    array->insertAt(0, &e);
    array->display();
    array->insertAt(5, &f);
    array->display();
}

void testGetData()
{
    std::cout << "\nTEST GET DATA\n";
    Array<int>* array = new Array<int>(4);
    int a = 5;
    int b = -33;
    int c = 1;
   
    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->display();

    int** arrayData = array->getData(); 

	std::cout << "\nМассив: ";
	for (int i = 0; i < array->getSize(); i++) {
		if (arrayData[i] != nullptr)
			std::cout << *arrayData[i];
		else
			std::cout << "nullptr";

		std::cout << " ";
	}
    std::cout << "\n";
}

void testOperator()
{
    std::cout << "\nTEST OPERATOP []\n";
    Array<int>* array = new Array<int>(4);
    int a = 5;
    int b = -33;
    int c = 1;

    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->display();

    std::cout << "\n array[2] = " << (*array)[2] << '\n';
}

void testOperatorCopy()
{
    std::cout << "\nTEST OPERATOP =\n";

    Array<int>* array1 = new Array<int>(3);
    Array<int>* array2 = new Array<int>(2);

    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;

    array1->add(&a);
    array1->add(&b);
    array1->display();
    array2->add(&c);
    array2->add(&d);
    array2->display();

    *array1 = *array2;

    array1->display();
}

void testAdd()
{
    std::cout << "\nTEST ADD\n";

    Array<int>* array = new Array<int>(2);
    int a = 12;
    int b = 33;
    int c = 43;
    int d = 53;

    array->add(&a);
    array->add(&b);
    array->add(&c);
    array->add(&d);

    array->display();
 
}

int main()
{
    setlocale(LC_ALL, "Russian");

    testSetSize();
    testRemoveAt();
    testRemoveAll();
    testFreeExtra();
    testSetAt();
    testAppend();
    testInsertAt();
    testGetData();
    testOperator();
    testOperatorCopy();
    testAdd();
}

