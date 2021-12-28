#include <iostream>
#include <exception>
#include <map>

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

    bool operator <(const Smartphone& other) const
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
    bool operator >(const Smartphone& other) const
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

    bool operator ==(const Smartphone& other) const
    {
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

//узел
template<class K, class V>
class Node
{
protected:
    V data;
    K key;

    //не можем хранить Node, но имеем право хранить указатель
    Node* left;
    Node* right;
    Node* parent;

    //переменная, необходимая для поддержания баланса дерева
    int height;
public:
    //доступные извне переменные и функции
    virtual void setData(V d) { data = d; }
    virtual void setKey(K k){ key = k; }
    virtual V getData() { return data; }
    virtual K getKey() { return key; }
    int getHeight() { return height; }

    virtual Node* getLeft() { return left; }
    virtual Node* getRight() { return right; }
    virtual Node* getParent() { return parent; }

    virtual void setLeft(Node* N) { left = N; }
    virtual void setRight(Node* N) { right = N; }
    virtual void setParent(Node* N) { parent = N; }

    //Конструктор. Устанавливаем стартовые значения для указателей
    Node<K, V>(K k, V n)
    {
        data = n;
        key = k;
        left = right = parent = nullptr;
        height = 1;
    }

    Node()
    {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        data = 0;
        height = 1;
    }
    ~Node()
    {
        if(left != nullptr) delete left;
        if(right != nullptr) delete right;
    }

    virtual void print()
    {
        std::cout << "\n" << data;
    }

    virtual void setHeight(int h)
    {
        height = h;
    }

    template<class T1, class T2> friend std::ostream& operator<< (std::ostream& stream, Node<T1, T2>& N);
};

template<class T1, class T2>
std::ostream& operator<< (std::ostream& stream, Node<T1, T2>& N)
{
    stream << "\nNode key: " << N.key <<  "\nNode data: " << N.data << ", height: " << N.height;
    return stream;
}
template<class T1, class T2>
void print(Node<T1, T2>* N)
{
    Smartphone tmp = N->getData();
    std::cout << "\n"<< "Key: " << N->getKey() << "\tData :" << tmp;
}

template<class K, class V>
class Tree
{
protected:
    //корень - его достаточно для хранения всего дерева
    Node<K, V>* root;
public:
    //доступ к корневому элементу
    virtual Node<K, V>* getRoot() { return root; }

    //конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
    Tree<K, V>() { root = nullptr; }
    /* Destructor */
    ~Tree()
    {
        std::cout << "\nTree destructor invoked.";
        destroy(root);
        std::cout << "\nTree destructor done.";
    }

    void destroy(Node<K,V>* node)
    {
        if(node)
        {
            destroy(node->getLeft());
            destroy(node->getRight());
            delete node;
        }
    }

    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<K, V>* Add_R(Node<K, V>* N)
    {
        return Add_R(N, root);
    }

    virtual Node<K, V>* Add_R(Node<K, V>* New, Node<K, V>* Current)
    {
        if (New == nullptr) return nullptr;
        if (root == nullptr)
        {
            root = New;
            return New;
        }

        if (Current->getData() > New->getData())
        {
            //идем влево
            if (Current->getLeft() != nullptr)
                Current->setLeft(Add_R(New, Current->getLeft()));
            else
                Current->setLeft(New);
            Current->getLeft()->setParent(Current);
        }
        if (Current->getData() < New->getData())
        {
            //идем вправо
            if (Current->getRight() != nullptr)
                Current->setRight(Add_R(New, Current->getRight()));
            else
                Current->setRight(New);
            Current->getRight()->setParent(Current);
        }
        if (Current->getData() == New->getData())
            //нашли совпадение
            ;
        //для несбалансированного дерева поиска
        return Current;
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual Node<K, V>* Add(K k, V n)
    {
        Node<K, V>* N = new Node<K, V>(k, n);
        return Add_R(N);
    }

    //удаление узла
    virtual Node<K,V>* Remove(Node<K,V>* N)
    {
        if(root == nullptr) return nullptr;
        /* Leaf */
        if(N->getRight() == nullptr && N->getLeft() == nullptr){ return nullptr; }
        /* Single child */
        if(N->getRight() == nullptr){ return N->getLeft(); }
        if(N->getLeft() == nullptr) { return N->getRight(); }
        /* Two children */
        Node<K,V>* prev = N->getLeft();
        while(N->getRight() != nullptr) prev = prev->getRight();
        N->setData(prev->getData());
        N->setLeft(Remove(N->getLeft()));
        return N;
    }

    virtual Node<K, V>* Min(Node<K, V>* Current=nullptr)
    {
        //минимум - это самый "левый" узел. Идём по дереву всегда влево
        if (root == nullptr) return nullptr;

        if(Current==nullptr)
            Current = root;
        while (Current->getLeft() != nullptr)
            Current = Current->getLeft();

        return Current;
    }

    virtual Node<K, V>* Max(Node<K, V>* Current = nullptr)
    {
        //максимум - это самый "правый" узел. Идём по дереву всегда вправо
        if (root == nullptr) return nullptr;

        if (Current == nullptr)
            Current = root;
        while (Current->getRight() != nullptr)
            Current = Current->getRight();

        return Current;
    }


    //поиск узла в дереве
    virtual Node<K, V>* Find(V data)
    {
        if (root == nullptr) return nullptr;
        return Find_R(data, root);
    }

    virtual Node<K, V>* Find_Left()
    {
        Node<K, V>* ptr = root;
        while(ptr->getLeft() != nullptr){ ptr = ptr->getLeft(); }
        return ptr;
    }

    //поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
    virtual Node<K, V>* Find_R(V data, Node<K, V>* Current)
    {
        //база рекурсии
        if (Current == nullptr) return nullptr;

        if (Current->getData() == data) return Current;

        //рекурсивный вызов
        if (Current->getData() > data) return Find_R(data, Current->getLeft());

        if (Current->getData() < data) return Find_R(data, Current->getRight());

    }

    //три обхода дерева
    virtual void PreOrder(Node<K, V>* N, void (*f)(Node<K, V>*))
    {
        if (N != nullptr)
            f(N);
        if (N != nullptr && N->getLeft() != nullptr)
            PreOrder(N->getLeft(), f);
        if (N != nullptr && N->getRight() != nullptr)
            PreOrder(N->getRight(), f);
    }

    //InOrder-обход даст отсортированную последовательность
    virtual void InOrder(Node<K, V>* N, void (*f)(Node<K, V>*))
    {
        if (N != nullptr && N->getLeft() != nullptr)
            InOrder(N->getLeft(), f);
        if (N != nullptr)
            f(N);
        if (N != nullptr && N->getRight() != nullptr)
            InOrder(N->getRight(), f);
    }

    virtual void PostOrder(Node<K, V>* N, void (*f)(Node<K, V>*))
    {
        if (N != nullptr && N->getLeft() != nullptr)
            PostOrder(N->getLeft(), f);
        if (N != nullptr && N->getRight() != nullptr)
            PostOrder(N->getRight(), f);
        if (N != nullptr)
            f(N);
    }
};

template<class K, typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
    Node<K, ValueType>* ptr;
    Tree<K, ValueType>* T;

public:
    TreeIterator() { ptr = nullptr; T = nullptr; }
    TreeIterator(Node<K, ValueType>* p) { ptr = p; }
    TreeIterator(const TreeIterator& it) { ptr = it.ptr; }

    bool operator!=(TreeIterator const& other) const { return ptr != other.ptr; }
    bool operator==(TreeIterator const& other) const { return ptr == other.ptr; }
    Node<K, ValueType>& operator*()
    {
        if(ptr == nullptr){ std::cerr << "\nNo iterator found."; }
        else{ return *ptr; }
    }

    // Pre
    TreeIterator& operator++()
    {
        if(ptr->getRight())
        {
            ptr = ptr->getRight();
            while(ptr->getLeft() != nullptr)
            {
                ptr = ptr->getLeft();
            }
        }
        else
        {
            Node<K, ValueType>* before;
            do{
                before = ptr;
                ptr = ptr->getParent();
            }while(ptr != nullptr && before == ptr->getRight());
        }
        return *this;
    }

    // Post
    TreeIterator& operator++(int v)
    {
        TreeIterator<K, ValueType> old(*this);
        ++(*this);
        return old;
    }

    ValueType getData(){ return ptr->getData(); }
    K getKey(){ return ptr->getKey(); }

    TreeIterator& operator=(const TreeIterator& it) { ptr = it.ptr; return *this; }
    TreeIterator& operator=(Node<K, ValueType>* p) { ptr = p; return *this; }
};

template<class K, class V>
class IteratedTree : public Tree<K, V>
{
public:
    IteratedTree<K, V>() : Tree<K, V>() {}

    TreeIterator<K, V> begin() { TreeIterator<K, V> it = TreeIterator<K, V>(Tree<K, V>::Min()); return it; }
    TreeIterator<K, V> end() { TreeIterator<K, V> it = TreeIterator<K, V>(Tree<K, V>::Max()); return it; }
};

//AVL_Tree - потомок класса Tree
template<class K, class V>
class AVL_Tree : public IteratedTree<K, V>
{
protected:
    //определение разности высот двух поддеревьев
    int bfactor(Node<K, V>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != nullptr)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != nullptr)
            hr = p->getRight()->getHeight();
        return (hr - hl);
    }

    //при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
    //после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
    //значение могло поменяться
    void fixHeight(Node<K, V>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != nullptr)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != nullptr)
            hr = p->getRight()->getHeight();
        p->setHeight((hl > hr ? hl : hr) + 1);
    }

    //краеугольные камни АВЛ-деревьев - процедуры поворотов
    Node<K, V>* RotateRight(Node<K, V>* p) // правый поворот вокруг p
    {
        Node<K, V>* q = p->getLeft();
        p->setLeft(q->getRight());
        q->setRight(p);
        if (p == Tree<K, V>::root)
            Tree<K, V>::root = q;

        q->setParent(p->getParent());
        p->setParent(q);
        if (p->getLeft()!=nullptr) p->getLeft()->setParent(p);

        fixHeight(p);
        fixHeight(q);
        return q;
    }

    Node<K, V>* RotateLeft(Node<K, V>* q) // левый поворот вокруг q
    {
        Node<K, V>* p = q->getRight();
        q->setRight(p->getLeft());
        p->setLeft(q);
        if (q == Tree<K, V>::root)
            Tree<K, V>::root = p;

        p->setParent(q->getParent());
        q->setParent(p);
        if(q->getRight()!=nullptr) q->getRight()->setParent(q);

        fixHeight(q);
        fixHeight(p);
        return p;
    }

    //балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
    Node<K, V>* Balance(Node<K, V>* p) // балансировка узла p
    {
        fixHeight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->getRight()) < 0)
            {
                p->setRight(RotateRight(p->getRight()));
                p->getRight()->setParent(p);
            }
            return RotateLeft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->getLeft()) > 0)
            {
                p->setLeft(RotateLeft(p->getLeft()));
                p->getLeft()->setParent(p);
            }
            return RotateRight(p);
        }

        return p; // балансировка не нужна
    }

public:
    //конструктор AVL_Tree вызывает конструктор базового класса Tree
    AVL_Tree<K, V>() : IteratedTree<K, V>() {}

    virtual Node<K, V>* Add_R(Node<K, V>* N)
    {
        return Add_R(N, Tree<K, V>::root);
    }

    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<K, V>* Add_R(Node<K, V>* N, Node<K, V>* Current)
    {
        //вызываем функцию Add_R из базового класса
        Node<K, V>* AddedNode = Tree<K, V>::Add_R(N, Current);
        //применяем к добавленному узлу балансировку
        return Balance(AddedNode);
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual Node<K, V>* Add(K k, V n)
    {
        Node<K, V>* N = new Node<K, V>(k, n);
        return Add_R(N);
    }
};

//Search by key function
template<class K, class V>
V searchByKey(AVL_Tree<K, V> tree, K k)
{
    for(TreeIterator it = tree.Find_Left(); it != tree.end(); it++)
    {
        if(it.getKey() == k)
        {
            V data = it.getData();
            std::cout << "\nKey " << k << " found.\tValue by key: " << data << "\n";
            return it.getData();
        }
    }
    throw std::runtime_error("\nError! No key found!");
}


//Search by value function
template<class K, class V>
K searchByValue(AVL_Tree<K,V> tree, V value)
{
    for(TreeIterator it = tree.Find_Left(); it != tree.end(); it++)
    {
        if(it.getData() == value)
        {
            std::cout << "\nValue " << value << " found.\tKey by value: " << it.getKey() << "\n";
            return it.getKey();
        }
    }
    throw std::runtime_error("\nError! No value found!");
}

template <class T>
class HeapNode
{
private:
    T value;
public:
    T getValue() { return value; }
    void setValue(T v) { value = v; }
    int operator<(HeapNode N)
    {
        return (value < N.getValue());
    }
    int operator>(HeapNode N)
    {
        return (value > N.getValue());
    }
    void print()
    {
        std::cout << value;
    }
};
template <class T>
void print(HeapNode<T>* N)
{
    std::cout << N->getValue() << "\n";
}
template <class T>
class Heap
{
private:
    HeapNode<T>* arr;
    int len;
    int size;
public:
    int getCapacity() { return size; }
    int getCount() { return len; }
    HeapNode<T>& operator[](int index)
    {
        if (index < 0 || index >= len)
            return NULL;//?
        return arr[index];
    }
    Heap<T>(int MemorySize = 100)
    {
        arr = new HeapNode<T>[MemorySize];
        len = 0;
        size = MemorySize;
    }
    void Swap(int index1, int index2)
    {
        if ((index1 >= 0 && index1 < len) && (index2 >= 0 && index2 < len))
        {
            HeapNode<T> temp;
            temp = arr[index1];
            arr[index1] = arr[index2];
            arr[index2] = temp;
        }
    }
    void Copy(HeapNode<T>* dest, HeapNode<T>* source)
    {
        dest->setValue(source->getValue());
    }
    HeapNode<T>* GetLeftChild(int index)
    {
        if (index < 0 || index * 2+2 >= len)
            return NULL;
        return &arr[index * 2 + 1];
    }
    HeapNode<T>* GetRightChild(int index)
    {
        if (index < 0 || index * 2+3 >= len)
            return NULL;
        return &arr[index * 2 + 2];
    }
    HeapNode<T>* GetParent(int index)
    {
        if (index <= 0 || index >= len)
            return NULL;
        if (index % 2 == 0)
            return &arr[index / 2 - 1];
        return &arr[index / 2];
    }
    int GetLeftChildIndex(int index)
    {
        if (index < 0 || index * 2+2 >= len)
            return -1;
        return index * 2 + 1;
    }
    int GetRightChildIndex(int index)
    {
        if (index < 0 || index * 2+3 >= len)
            return -1;
        return index * 2 + 2;
    }
    int GetParentIndex(int index)
    {
        if (index <= 0 || index >= len)

            return -1;
        if (index % 2 == 0)
            return index / 2 - 1;
        return index / 2;
    }
    void SiftUp(int index = -1)
    {
        if (index == -1) index = len - 1;
        int parent = GetParentIndex(index);
        int index2 = GetLeftChildIndex(parent);
        if (index2 == index) index2 = GetRightChildIndex(parent);
        int max_index = index;
        if (index < len && index2 < len && parent >= 0)
        {
            if (arr[index] > arr[index2])
                max_index = index;
            if (arr[index] < arr[index2])
                max_index = index2;
        }
        if (parent < len && parent >= 0 && arr[max_index]>arr[parent])
        {
            Swap(parent, max_index);
            SiftUp(parent);
        }
    }
    template <class T1>
    void Add(T1 v)
    {
        HeapNode<T1>* N = new HeapNode<T1>;
        N->setValue(v);
        Add(N);
    }
    template <class T1>
    void Add(HeapNode<T1>* N)
    {
        if (len < size)
        {
            Copy(&arr[len], N);
            len++;
            SiftUp();
        }
    }
    void Straight(void(*f)(HeapNode<T>*))
    {
        int i;
        for (i = 0; i < len; i++)
        {
            f(&arr[i]);
        }
    }
    void InOrder(void(*f)(HeapNode<T>*), int index = 0)
    {
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
    }
    T ExtractMax()
    {
        int max = 0;
        T elem = arr[0].getValue();
        while (1)
        {
            if ((GetLeftChild(max) != NULL) && (GetRightChild(max) != NULL))
            {
                if (GetLeftChild(max)->getValue() > GetRightChild(max)->getValue())
                {
                    Swap(max, GetLeftChildIndex(max));
                    max = GetLeftChildIndex(max);

                }
                else
                {
                    Swap(max, GetRightChildIndex(max));
                    max = GetRightChildIndex(max);

                }
            }
            else if (GetLeftChild(max) != NULL)
            {
                Swap(max, GetLeftChildIndex(max));
                max = GetLeftChildIndex(max);
            }
            if (max > len-1)
            {
                max = GetParentIndex(max);
            }
            if ((GetLeftChildIndex(max) == -1) && (GetRightChildIndex(max) == -1))
            {
                Swap(max, len - 1);
                len--;
                SiftUp(max);
                break;
            }
        }
        return elem;
    }
    ~Heap()
    {
        delete []arr;
    }

};

int main()
{
    Smartphone s21("Galaxy S21", 4, 2592000, 4000, 12, 63000);
    Smartphone pixel6("Pixel 6", 3, 2592000, 4614, 14, 62000);
    Smartphone iphone13p("iPhone 13 Pro", 4, 2962440, 3095, 8, 95000);
    Smartphone redminote10("Redmi Note 10 Pro", 4, 2592000, 5020, 13, 25000);
    Smartphone honor30i("Honor 30i", 3, 2592000, 4000, 12, 15000);

    AVL_Tree<std::string, Smartphone> T;
    T.Add("Gal", s21); T.Add("P6", pixel6); T.Add("iph13p", iphone13p); T.Add("redmi", redminote10);
    T.Add("Hon", honor30i);

    Node<std::string, Smartphone>* M = T.Min();
    std::cout << "\nMin = " << M->getData().getName();
    std::cout << "\tFind " << s21.getName() << ": " << T.Find_R(s21, T.getRoot());

    void (*f_ptr)(Node<std::string, Smartphone>*); f_ptr = print;
    std::cout << "\n-----\nPreorder:";
    T.PreOrder(T.getRoot(), f_ptr);
    std::cout << "\n-----\nInorder:";
    T.InOrder(T.getRoot(), f_ptr);
    std::cout << "\n-----\nPostorder:";
    T.PostOrder(T.getRoot(), f_ptr);

    try
    {
        std::cout << "\n-----\nSearch by key: ";
        searchByKey(T, std::string("iph13p"));
        searchByKey(T, std::string("Random string"));
    } catch(const std::runtime_error& e){ std::cout << e.what(); };

    try
    {
        std::cout << "\n-----\nSearch by value: ";
        searchByValue(T, honor30i);
        searchByValue(T, Smartphone());
    } catch(const std::runtime_error& e){ std::cout << e.what(); };

    std::cout << "\n-----\nIterators:";
    TreeIterator<std::string, Smartphone> iterator = T.Find_Left();
    while (iterator != T.end())
    {
        std::cout << *iterator << " ";
        *iterator++;
    }

    Heap<Smartphone> h;
    h.Add(iphone13p);
    h.Add(honor30i);
    h.Add(pixel6);
    h.Add(redminote10);
    h.Add(s21);
    while (h.getCount() != 0)
    {
        Smartphone tmp = h.ExtractMax();
        std::cout << "Heap:" << tmp << std::endl;
    }

    return 0;
}