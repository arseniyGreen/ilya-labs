/* Бобров Илья КТСО-02-20 */

#include <iostream>
#include <list>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>

template<class Type>
void push(std::list<Type>& lst, Type element)
{
    typename std::list<Type>::iterator iter = lst.begin();

    while(iter != lst.end() && *iter < element)
    {
        if(*iter > element) break;

        *iter++;
    }
    lst.insert(iter, element);
}

template<class Type>
Type pop(std::list<Type>& lst)
{
    typename std::list<Type>::iterator iter = --lst.end();

    Type returnValue = *iter;
    lst.erase(iter);

    return returnValue;
}

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

template<class Type>
std::list<Type> filter(std::list<Type>& first, bool (*predicate)(Type))
{
    std::list<Type> toReturn;

    typename std::list<Type>::iterator it = first.begin();
    while(it != first.end())
    {
        if(predicate(*it)) push(toReturn, *it);
        *it++;
    }
    return toReturn;
}

template<class Type>
void printList(std::list<Type>& lst)
{
    typename std::list<Type>::iterator iter = lst.begin();

    while(iter != lst.end())
    {
        std::cout << *iter << " ";
        *iter++;
    }
}

int main()
{
    srand(time(NULL));
    std::list<int> firstList;

    /* Fill list with random numbers */
    for(size_t i = 0; i < 10; i++)
    {
        firstList.push_back(rand() % 100 + 1);
    }

    firstList.sort();

    std::cout << "\nПервый список перед применением push : \n";
    printList(firstList);

    //Гарантируем наличие простых чисел
    push(firstList, 5);
    push(firstList, 3);
    push(firstList, 13);
    push(firstList, 23);

    std::cout << "\nПосле push : \n";
    printList(firstList);

    /* Pop test */
    int popValue = pop(firstList);

    std::cout << "\nПосле pop:\n";
    printList(firstList);
    std::cout << "\nPop вернул : " << popValue << "\n";

    /* Filter test */
    std::list<int> secondList = filter(firstList, isPrime);
    std::cout << "\nОтфильтрованный список: \n";
    printList(secondList);
    std::cout << "\n";

    return 0;
}