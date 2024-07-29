#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
    T* data = nullptr;
    Node* next, * prev;

    Node* copy();
    Node() {};
    Node(T* dataNode);
    ~Node();
};

template <typename T>
Node<T>::Node(T* dataNode)
{
    data = dataNode;
    next = prev = nullptr;
}

template <typename T>
inline Node<T>::~Node()
{
    if (prev)
        prev->next = next;

    if (next)
        next->prev = prev;
}

template <typename T>
Node<T>* Node<T>::copy()
{
    Node* copyNode = new Node(data);
    if (next != nullptr) {
        Node* copyNext = next->copy();
        copyNode->next = copyNext;
        copyNext->prev = copyNode;
    }
    return copyNode;
}

template <typename T>
class Array 
{
public:
    explicit Array(const int size);
    ~Array();

    void display();
    int getSize();
    void setSize(int size, int grow = 1);
    int getUpperBound();
    bool isEmpty();
    void freeExtra();
    void removeAll();
    T* getAt(int index);
    void setAt(int index, T* value);
    void add(T* data);
    void append(Array& array);
    T** getData();
    void insertAt(int index, T* data);
    void removeAt(int index);
    T& operator[](const int& index);
    Array& operator=(const Array<T>& array);

private:
    Node<T>* arrayBegin_, *arrayEnd_;
    int size_;
    int grow_ = 1;
    Array* copy();
};

template <typename T>
Array<T>::Array(const int size)
{
    if (size < 1)
        throw "\a\x1b[31mSize < 1!!!\n\x1b[0m";

    arrayBegin_ = new Node<T>();
    arrayEnd_ = arrayBegin_;

    for (int ii = 1; ii < size; ii++) {
        Node<T>* node = new Node<T>();
        arrayEnd_->next = node;
        node->prev = arrayEnd_;
        arrayEnd_ = node;
    }
    size_ = size;
    
}

template <typename T>
Array<T>::~Array() {
    removeAll();
}

template <typename T>
void Array<T>::setSize(int size, int grow)
{
    if (size < 1 || grow < 1)
        throw "\a\x1b[31mSize or grow < 1!!!\n\x1b[0m";

    if (size_ < size) {
        int newSize = size - size_;

        for (int ii = 0; ii < newSize; ii++) {
            Node<T>* node = new Node<T>();
            arrayEnd_->next = node;
            node->prev = arrayEnd_;
            arrayEnd_ = node;
        }
    }
    else if (size_ > size)
    {
        int newSize = size_ - size;
        Node<T>* temp = arrayEnd_;

        for (int ii = 0; ii < newSize; ii++)
        {
            Node<T>* tempPrev = temp->prev;
            delete temp;
            temp = tempPrev;
        }
        arrayEnd_ = temp;
    }
 
    size_ = size;
    grow_ = grow;
}

template <typename T>
void Array<T>::add(T* data)
{
    if (size_ == 0) {
        arrayBegin_ = new Node<T>();
        arrayEnd_ = arrayBegin_;
        size_ = 1;
    }
   
    Node<T>* temp = arrayEnd_;

    bool isAdd = false;

    while (temp != nullptr) {
        
        if ((temp->data == nullptr && temp->prev != nullptr && temp->prev->data != nullptr) || 
            (temp->prev == nullptr && temp->data == nullptr)) {
            temp->data = data;
            isAdd = true;
        }
        temp = temp->prev;
    }
    if (!isAdd) {

        for (int ii = 0; ii < grow_; ii++) {
            Node<T>* node = new Node<T>();
            if (ii == 0)
                node->data = data;
            arrayEnd_->next = node;
            node->prev = arrayEnd_;
            arrayEnd_ = node;
        }
    }
}

template <typename T>
int Array<T>::getSize()
{
    return this->size_;
}

template <typename T>
int Array<T>::getUpperBound()
{
    Node<T>* temp = arrayEnd_;

    for (int index = size_ - 1; index >= 0; index--)
    {
        if (temp->data != nullptr) {
            return index;
        }
        temp = temp->prev;
    }
   
    return -1;
}

template <typename T>
inline bool Array<T>::isEmpty()
{
    return size_ == 0;
}

template <typename T>
void  Array<T>::freeExtra()
{
    int index = getUpperBound();

	Node<T>* temp = arrayEnd_;

	for (int ii = size_ - 1; ii > index; ii--)
	{
		Node<T>* tempPrev = temp->prev;
		delete temp;
		temp = tempPrev;
	}
	arrayEnd_ = temp;
}

template <typename T>
void Array<T>::removeAll()
{
    while (arrayEnd_ != nullptr)
    {
        Node<T>* nextEnd = arrayEnd_->prev;
        delete arrayEnd_;
        arrayEnd_ = nextEnd;
    }

    size_ = 0;
}

template <typename T>
T* Array<T>::getAt(int index)
{
    if(index < 0 || index >= size_)
        throw "\a\x1b[31mIndex incorrect!!!\n\x1b[0m";

    Node<T>* tempBegin = arrayBegin_;

    for (int ii = 0; ii < size_; ii++) {
        if (index == ii)
            return tempBegin->data;
        tempBegin = tempBegin->next;
    }
}

template <typename T>
void Array<T>::setAt(int index, T* value)
{
    if (index < 0 || index >= size_)
        throw "\a\x1b[31mIndex incorrect!!!\n\x1b[0m";
    Node<T>* temp = arrayBegin_;

    for (int ii = 0; ii < size_; ii++) {
        if (index == ii) {
            temp->data = value;
            break;
        }
        temp = temp->next;
    }
}

template <typename T>
Array<T>* Array<T>::copy()
{
    Array<T>* copyArray = new Array<T>(size_);
    copyArray->arrayBegin_ = arrayBegin_->copy();
    copyArray->size_ = size_;
    copyArray->grow_ = grow_;

    Node<T>* temp = arrayBegin_;

    while (temp != nullptr) {

        if (temp->next == nullptr) {
            copyArray->arrayEnd_ = temp;
            break;
        }
        temp = temp->next;
    }
    return copyArray;

}

template <typename T>
void Array<T>::append(Array<T>& array)
{
   Array<T>* arraycopy = array.copy();
   arrayEnd_->next = arraycopy->arrayBegin_;
   arraycopy->arrayBegin_->prev = arrayEnd_;
}

template <typename T>
T** Array<T>::getData()
{
    T** data = new T*[size_];
    Node<T>* temp = arrayBegin_;

    for (int ii = 0; ii < size_; ii++) {
        data[ii] = temp->data;
        temp = temp->next;
    }

    return data;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& array)
{
    std::cout << "\nОтработал оператор копирования\n";

    if (this == &array)
        return *this;

    this->~Array();

    Node<T>* temp = array.arrayBegin_;

    while (temp != nullptr) {
        add(temp->data);
        temp = temp->next;
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[](const int& index)
{
    return *getAt(index);
}

template <typename T>
void Array<T>::insertAt(int index, T* data)
{
    if (index < 0 || index > size_)
        throw "\a\x1b[31mIndex incorrect!!!\n\x1b[0m";

    Node<T>* nodeInsert = new Node<T>(data);

    if (index == 0)
    {
        nodeInsert->prev = nullptr;
        nodeInsert->next = arrayBegin_;

        if (arrayBegin_ != nullptr)
            arrayBegin_->prev = nodeInsert;

        if (size_ == 0)
            arrayBegin_ = arrayEnd_ = nodeInsert;
        else
            arrayBegin_ = nodeInsert;
    }
    else if (index == size_) {

        nodeInsert->next = nullptr;
        nodeInsert->prev = arrayEnd_;

        if (arrayEnd_ != nullptr)
            arrayEnd_->next = nodeInsert;

        if (size_ == 0)
            arrayBegin_ = arrayEnd_ = nodeInsert;
        else
            arrayEnd_ = nodeInsert;
    }
    else
    {
        int i = 0;

        Node<T>* beginInsert = arrayBegin_;

        while (i < index)
        {
            beginInsert = beginInsert->next;
            i++;
        }

        Node<T>* prevInsert = beginInsert->prev;

        if (prevInsert != nullptr && size_ != 1)
            prevInsert->next = nodeInsert;

        nodeInsert->next = beginInsert;
        nodeInsert->prev = prevInsert;
        beginInsert->prev = nodeInsert;
    }
    size_++;
}

template <typename T>
void  Array<T>::removeAt(int index)
{
    if (index < 0 || index > size_)
        throw "\a\x1b[31mIndex incorrect!!!\n\x1b[0m";

    int i = 0;
    Node<T>* delBegin = arrayBegin_;

    while (i < index)
    {
        delBegin = delBegin->next;
        i++;
    }

    Node<T>* delPrev = delBegin->prev; 
    Node<T>* delAfter = delBegin->next; 

    if (delPrev != nullptr && size_ != 1)
        delPrev->next = delAfter;

    if (delAfter != nullptr && size_ != 1)
        delAfter->prev = delPrev;

    if (index == 0)
        arrayBegin_ = delAfter; 

    if (index == size_)
        arrayEnd_ = delPrev;

    delete delBegin;

    size_--;
}

template <typename T>
void  Array<T>::display() 
{
    if (isEmpty())
        std::cout << "\nArray is empty!" << std::endl;
    else 
    {
        Node<T>* tmpNode = arrayBegin_;
        while (tmpNode != nullptr) {

            if(tmpNode->data != nullptr)
               std::cout <<*(tmpNode->data);
            else
                std::cout << "nullptr";

            tmpNode = tmpNode->next;
            if (tmpNode != nullptr)
                std::cout << " <-> ";
        }
    }
    std::cout << '\n';

}

