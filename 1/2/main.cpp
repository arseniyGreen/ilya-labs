/* Бобров Илья КТСО-02-20 */

#include <iostream>
#include <list>
#include <string>

using std::string;

class Smartphone
{
private:
    string name;
    int screenSize; //w*h
    int camerasNum, batCapacity, dischargeHrs, price;
public:
    Smartphone(){ name = ""; camerasNum = screenSize = batCapacity = dischargeHrs = price = NULL;}
    Smartphone(string _name, int _camerasNum, int _screenSize, int _batCapacity, int _dischargeHrs, int _price)
    {
        name = _name; camerasNum = _camerasNum; screenSize = _screenSize; batCapacity = _batCapacity; dischargeHrs = _dischargeHrs; price = _price;
    }
    string getName(){ return name; }
    int getScreenSize(){ return screenSize; }
    int getCamerasNum(){ return camerasNum; }
    int getBatCapacity(){ return batCapacity; }
    int getDischargeHrs(){ return dischargeHrs; }
    int getPrice(){ return price; }

    void setName(string _name){ name = _name; }
    void setScreenSize(int _screenSize){ screenSize = _screenSize; }
    void setCamerasNum(int _camerasNum){ camerasNum = _camerasNum; }
    void setBatCapacity(int _batCapacity){ batCapacity = _batCapacity; }
    void setDischargeHrs(int _dischargeHrs){ dischargeHrs = _dischargeHrs; }
    void setPrice(int _price){ price = _price; }

    bool operator <(Smartphone& other)
    {
        if(price != other.price) return price < other.price;
        else
        {
            if(camerasNum != other.camerasNum) return camerasNum < other.camerasNum;
            else
            {
                if(screenSize != other.screenSize) return screenSize < other.screenSize;
                else
                {
                    return name < other.name;
                }
            }
        }
    }
    bool operator >(Smartphone& other)
    {
        if(price != other.price) return price > other.price;
        else
        {
            if(camerasNum != other.camerasNum) return camerasNum > other.camerasNum;
            else
            {
                if(screenSize != other.screenSize) return screenSize > other.screenSize;
                else
                {
                    return name > other.name;
                }
            }
        }
    }

    friend std::ostream& operator << (std::ostream& stream, Smartphone &s);
};

std::ostream &operator<<(std::ostream &stream, Smartphone &s) {
        stream << "\nName : " << s.getName();
        stream << "\nScreen Size : " << s.getScreenSize();
        stream << "\nCameras Number : " << s.getCamerasNum();
        stream << "\nBattery Capacity : " << s.getBatCapacity();
        stream << "\nDischarge Hours : " << s.getDischargeHrs();
        stream << "\nPrice : " << s.getPrice() << "\n";
        return stream;
}

template<class Type>
void push(std::list<Type>& lst, Type element)
{
    typename std::list<Type>::iterator it = lst.begin();

    while(it != lst.end() && *it < element)
    {
        if(*it > element) break;

        *it++;
    }
    lst.insert(it, element);
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
    std::cout << "\nList length : " << lst.size() << "\n";

    typename std::list<Type>::iterator iter = lst.begin();

    while(iter != lst.end())
    {
        std::cout << *iter << " ";
        *iter++;
    }
}

int main()
{
    Smartphone s21("Galaxy S21", 4, 2592000, 4000, 12, 63000);
    Smartphone pixel6("Pixel 6", 3, 2592000, 4614, 14, 62000);
    Smartphone iphone13p("iPhone 13 Pro", 4, 2962440, 3095, 8, 95000);
    Smartphone redminote10("Redmi Note 10 Pro", 4, 2592000, 5020, 13, 25000);
    Smartphone honor30i("Honor 30i", 3, 2592000, 4000, 12, 15000);

    std::list<Smartphone> list;
    push(list, s21);
    push(list, pixel6);
    push(list, iphone13p);
    push(list, redminote10);
    push(list, honor30i);

    printList(list);

    std::cout << "\nPop test:";
    Smartphone popVal = pop(list);
    std::cout << popVal;

    std::cout << "\nList after pop :";
    printList(list);

    return 0;
}