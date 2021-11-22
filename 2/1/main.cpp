/* Бобров КТСО-02-20 */

#include <iostream>
#include <string>
#include <map>
#include <utility>

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
    int getScreenSize() const{ return screenSize; }
    int getCamerasNum() const { return camerasNum; }
    int getBatCapacity() const { return batCapacity; }
    int getDischargeHrs() const { return dischargeHrs; }
    int getPrice() const { return price; }

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

    bool operator ==(const Smartphone& other){
        return name == other.name && screenSize == other.screenSize && camerasNum == other.camerasNum && batCapacity == other.batCapacity && dischargeHrs == other.dischargeHrs && price == other.price;
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

bool isBigger(const Smartphone s){ return s.getPrice() > 50000; }

template<class Key, class Value>
std::map<Key, Value> filter(std::map<Key, Value>& tree, bool (*predicate)(Value))
{
    std::map<Key, Value> newTree;
    typename std::map<Key, Value>::iterator iter = tree.begin();
    while(iter != tree.end())
    {
        if(predicate(iter->second))
        {
            newTree[iter->first] = iter->second;
        }
        *iter++;
    }
    return newTree;
}

template<class Key, class Value>
void printTree(std::map<Key, Value> tree)
{
    typename std::map<Key, Value>::iterator iter = tree.begin();
    while(iter != tree.end())
    {
        std::cout << "Ключ : " << iter->first << " || Значение : " << iter->second << "\n";
        iter++;
    }
}

template<class Key, class Value>
Value findByKey(std::map<Key, Value> tree, Key key)
{
    if(tree.count(key) == 1)
    {
        std::cout << "\nКлюч найден. Значение по ключу : " << tree.at(key) << "\n";
    }
    else
    {
        std::cout << "\nНет совпадений!\n";
    }
    return tree.at(key);
}

template<class Key, class Value>
Key findByValue(std::map<Key, Value> tree, Value value)
{
    typename std::map<Key, Value>::iterator iter = tree.begin();
    while(iter != tree.end())
    {
        if(iter->second == value){ std::cout << "\nЗначение найдено: " << value <<
        " Ключ для значения: " << iter->first;return iter->first; }
        *iter++;
    }
    std::cout << "\nНет совпадений!\n";
    return NULL;
}

int main() {
    Smartphone s21("Galaxy S21", 4, 2592000, 4000, 12, 63000);
    Smartphone pixel6("Pixel 6", 3, 2592000, 4614, 14, 62000);
    Smartphone iphone13p("iPhone 13 Pro", 4, 2962440, 3095, 8, 95000);
    Smartphone redminote10("Redmi Note 10 Pro", 4, 2592000, 5020, 13, 25000);
    Smartphone honor30i("Honor 30i", 3, 2592000, 4000, 12, 15000);

    std::map<std::string, Smartphone> myTree;

    myTree["Glxy"] = s21;
    myTree["pxl6"] = pixel6;
    myTree["iphone"] = iphone13p;
    myTree["xiaomi"] = redminote10;
    myTree["honor"] = honor30i;

    printTree(myTree);

    std::cout << "\nFilter test\n";
    std::map<std::string, Smartphone> filteredTree = filter(myTree, isBigger);
    printTree(filteredTree);

    std::cout << "\nKey search test:\n";
    findByKey(myTree, std::string("FB")); //success
    findByKey(myTree, std::string("RANDOM STRING")); //fail

    std::cout << "\nValue search test:\n";
    Smartphone sameIPhone("iPhone 13 Pro", 4, 2962440, 3095, 8, 95000);
    Smartphone anotherIPhone("iPhone XR", 3, 2962440, 2500, 7, 55000);
    findByValue(myTree, sameIPhone);
    findByValue(myTree, anotherIPhone);

    return 0;
}
