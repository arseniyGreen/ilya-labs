/* Бобров Илья КТСО-02-20 */

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

template <class T>
class Element
{
    //элемент связного списка
private:
    //указатель на предыдущий и следующий элемент
    Element* next;
    Element* prev;
    //информация, хранимая в поле
    T field;
public:
    Element(T value)
    { field = value; next = prev = nullptr; }

    //доступ к полю *next
    virtual Element* getNext() { return next; }
    virtual void setNext(Element* value) { next = value; }

    //доступ к полю *prev
    virtual Element* getPrevious() { return prev; }
    virtual void setPrevious(Element* value) { prev = value; }

    //доступ к полю с хранимой информацией field
    virtual T getValue() { return field; }
    virtual void setValue(T value) { field = value; }

    template<class T1> friend ostream& operator<< (ostream& ustream, Element<T1>& obj);

    bool operator < (const Element<T>& other) const { return field < other.field; }
    bool operator > (const Element<T>& other) const { return field > other.field; }
    bool operator >=(const Element<T>& other) const { return field >= other.field; }
    bool operator <=(const Element<T>& other) const { return field <= other.field; }

    Element operator*() { return field; }
};

template <class T>
ostream & operator << (ostream& ustream, Element<T>& obj)
{
    ustream << obj.field;
    return ustream;
}

template <class T>
class LinkedListParent
{
protected:
    //достаточно хранить начало и конец
    Element<T>* head;
    Element<T>* tail;

    //для удобства храним количество элементов
    int num;
public:
    virtual int Number() { return num; }

    virtual Element<T>* getBegin() { return head; }
    virtual Element<T>* getEnd() { return tail; }

    LinkedListParent()
    {
        //конструктор без параметров
        //cout << "\nParent constructor";
        head = tail = nullptr; //t
        num = 0;
    }
    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление

    virtual Element<T>* push(T value) = 0;
    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление

    virtual Element<T>* pop() = 0;

    virtual ~LinkedListParent()
    {
        //деструктор - освобождение памяти
        //cout << "\nParent destructor";
    }

    //получение элемента по индексу - какова асимптотическая оценка этого действия ?
    virtual Element<T>*operator[](int i)
    {
        //индексация
        if (i < 0 || i > num) return NULL;

        int k = 0;
        //ищем k-й элемент - вставем в начало и отсчитываем i шагов вперед
        Element<T>* cur = head;

        for (k = 0; k < i; k++)
        {
            cur = cur->getNext();
        }
        return cur;
    }
    template<class T1> friend ostream& operator<< (ostream& ustream, LinkedListParent<T1>& obj);
    template<class T1> friend istream& operator>> (istream& ustream, LinkedListParent<T1>& obj);
};
template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
    if (typeid(ustream).name() == typeid(ofstream).name())
    {
        ustream << obj.num << "\n";
        for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
            ustream << current->getValue() << " ";

        return ustream;
    }

    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;

    for (Element<T>* current = obj.getBegin(); current != nullptr; current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue() << "\n";

    return ustream;
}
template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
    //чтение из файла и консоли совпадают
    int len;
    ustream >> len;

    //здесь надо очистить память под obj, установить obj.num = 0
    double v = 0;
    for (int i = 0; i < len; i++)
    {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
    Element<ValueType>* ptr;
public:
    ListIterator() { ptr = nullptr; }
    ListIterator(Element<ValueType>* p) { ptr = p; }
    ListIterator(const ListIterator& it) { ptr = it.ptr; }

    bool operator!=(ListIterator const& other) const { return ptr->getValue() != other.ptr->getValue(); }

    bool operator==(ListIterator const& other) const { return ptr->getValue() == other.ptr->getValue(); }

    ValueType getValue() const
    { return ptr->getValue(); }

    Element<ValueType>& operator*()
    {
        if(ptr != nullptr) return *ptr;
        else cout << "\nNo iterator!\n";
    }

    ListIterator& operator++()
    {
        if (ptr->getNext() != nullptr && ptr != nullptr) ptr = ptr->getNext();
        return *this;
    }

    ListIterator& operator++(int v)
    {
        if (ptr->getNext() != nullptr && ptr != nullptr) ptr = ptr->getNext();
        return *this;
    }

    ListIterator& operator--()
    {
        if (ptr->getPrevious() != nullptr && ptr != nullptr) ptr = ptr->getPrevious();
        return *this;
    }

    ListIterator& operator--(int v)
    {
        if (ptr->getPrevious() != nullptr && ptr != nullptr) ptr = ptr->getPrevious();
        return *this;
    }

    ListIterator& operator=(const ListIterator & it)
    { ptr = it.ptr; return *this; }

    ListIterator& operator=(Element<ValueType>* p)
    { ptr = p; return *this; }

};

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
    IteratedLinkedList() : LinkedListParent<T>()
    { /*cout << "\nIteratedLinkedList constructor";*/ }
    virtual ~IteratedLinkedList()
    { /*cout << "\nIteratedLinkedList destructor";*/ }

    ListIterator<T> begin()
    {
        ListIterator<T> it = LinkedListParent<T>::head;
        return it;
    }
    ListIterator<T> end()
    {
        ListIterator<T> it = LinkedListParent<T>::tail;
        return it;
    }
};

template<class T>
class Queue : public IteratedLinkedList<T>
{
public:
    Queue() : IteratedLinkedList<T>() { std::cout << "\nQueue constructor"; }
    ~Queue() { std::cout << "\nQueue destructor"; }

    Element<T>* push(T value) override
    {
        Element<T>* newElement = new Element<T>(value);
        if(LinkedListParent<T>::head == nullptr)
        {
            LinkedListParent<T>::head = LinkedListParent<T>::tail = newElement;
            LinkedListParent<T>::num++;
        }
        else if(LinkedListParent<T>::num == 1)
        {
            newElement->setPrevious(LinkedListParent<T>::head);
            LinkedListParent<T>::head->setNext(newElement);
            LinkedListParent<T>::tail = newElement;
            LinkedListParent<T>::num++;
        }
        else
        {
            LinkedListParent<T>::tail->setNext(newElement);
            newElement->setPrevious(LinkedListParent<T>::tail);
            LinkedListParent<T>::tail = newElement;
            LinkedListParent<T>::num++;
        }
        return LinkedListParent<T>::tail;
    }

    Element<T>* pop() override
    {
        Element<T>* ptr = LinkedListParent<T>::head;
        LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();
        LinkedListParent<T>::head->setPrevious(nullptr);
        LinkedListParent<T>::num--;

        return ptr;
    }

};

template<class T>
class OrderedQueue : public Queue<T>
{
public:
    OrderedQueue() : Queue<T>(){ std::cout << "\nOrderedQueue constructor\n"; }
    ~OrderedQueue()
    {
        std::cout << "OrderedQueue destructor";
        while(LinkedListParent<T>::head != nullptr)
        {
            Element<T>* ptr = LinkedListParent<T>::head->getNext();
            delete LinkedListParent<T>::head;
            LinkedListParent<T>::head = ptr;
        }
    }

    Element<T>* push(T value) override
    {
        Element<T>* newEl = new Element<T>(value);

        if (LinkedListParent <T>::head != nullptr)
        {
            ListIterator<T> it = LinkedListParent<T>::head;

            if (*newEl >= *it)
            {
                LinkedListParent<T>::head->setPrevious(newEl);
                newEl->setNext(LinkedListParent<T>::head);
                LinkedListParent<T>::head = newEl;
                LinkedListParent<T>::num++;
                return LinkedListParent<T>::tail;
            }
            *it++;

            while (it != LinkedListParent<T>::tail)
            {
                if (*newEl >= *it)
                {
                    //?
                    Element<T> curr = *it;
                    Element<T> prev = *it--;

                    newEl->setPrevious(&prev);
                    newEl->setNext(&curr);
                    curr.setPrevious(newEl);
                    LinkedListParent<T>::num++;
                    return LinkedListParent<T>::tail;
                }
                *it++;
            }

            if (*newEl >= *it)
            {
                Element<T> curr = *it;
                Element<T> prev = *it--;

                newEl->setPrevious(&prev);
                curr.setPrevious(newEl);
                newEl->setNext(&curr);
            }
            else
            {
                newEl->setPrevious(LinkedListParent<T>::tail);
                LinkedListParent<T>::tail->setNext(newEl);
                LinkedListParent<T>::tail = newEl;
            }
        }
        else
            LinkedListParent<T>::tail = LinkedListParent<T>::head = newEl;

        LinkedListParent<T>::num++;
        return LinkedListParent<T>::tail;
    }
};

template<class Type>
bool isPrime(Type x)
{
    if(x < 2) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;
    for(size_t i = 3; pow(i, 2) < x; i+=2)
    {
        if(x % i == 0) return false;
    }
    return true;
}

template<class T>
void filter(Queue<T>& queue, Queue<T>& newQueue, bool (*predicate)(T))
{
    ListIterator it = queue.begin();
    while (it != queue.end())
    {
        if (predicate((*it).getValue())) { newQueue.push((*it).getValue()); }
        *it++;
    }
    std::cout << "Filtering done!\n";
}

int main()
{
    Queue<int> S;
    S.push(11);
    S.push(-35);
    S.push(332);
    S.push(-10);
    S.push(62);
    S.push(-41);
    S.push(13);
    S.push(25);
    S.push(31);
    S.push(12);

    cout << "\n" << S;
    cout << "\n";
    Element<int>* e1 = S.pop();
    cout << "\nElement = " << e1->getValue() << "\n";
    cout << S;
    cout << "\nIndex in the Queue class: " << S[1]->getValue() << "\n";
    cout << S;

    std::cout << "Filter test:\n";
    Queue<int> filteredQueue;
    filter(S, filteredQueue, isPrime);
    std::cout << "Filtered queue : " << filteredQueue << "\n";

    OrderedQueue<int> q2;
    q2.push(-13);
    q2.push(-90);
    q2.push(100);

    std::cout << "\nOrdered queue test : \n" << q2;

    Element<int>* pop2 = q2.pop();
    std::cout << "\nOQ pop returned " << pop2->getValue() << '\n';

    return 0;
}
