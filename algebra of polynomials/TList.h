#ifndef __TLIST_H__
#define __TLIST_H__


template<typename T>
class TList {
private:
    struct TNode
    {
        T value;
        TNode* pNext;
    };

    size_t size;
    TNode* pFirst;

    TNode* getNodeAtPosition(size_t position) const {

        if (position >= size) { throw out_of_range("Index out of range"); }

        auto cur = pFirst;
        for (size_t i = 0; i < position; ++i)
        {
            if (cur == nullptr) { throw out_of_range("Invalid position"); }
            cur = cur->pNext;
        }
        return cur;
    }

public:
    TList() : pFirst(nullptr), size(0) {}

    TList(const TList& other) : pFirst(nullptr), size(0) {

        TNode* cur = other.pFirst;
        while (cur != nullptr)
        {
            pushBack(cur->value);
            cur = cur->pNext;
        }
    }

    TList& operator=(TList other) {

        swap(pFirst, other.pFirst);
        swap(size, other.size);

        return *this;
    }

    size_t getSize() const { return size; }

    bool isEmpty() const { return size == 0; }

    void pushBack(const T& _value) {

        if (pFirst == nullptr)
        {
            pFirst = new TNode{ _value, nullptr };
        }
        else
        {
            TNode* cur = pFirst;
            while (cur->pNext != nullptr) { cur = cur->pNext; }

            cur->pNext = new TNode{ _value, nullptr };
        }
        size++;
    }

    void pushFront(const T& _value) {

        TNode* node = new TNode{ _value, pFirst };
        pFirst = node;
        size++;
    }

    void popFront() {

        if (pFirst == nullptr) { throw out_of_range("List is empty"); }

        TNode* temp = pFirst;
        pFirst = pFirst->pNext;
        delete temp;
        size--;
    }

    void insertNodeAfter(size_t position, const T& _value) {

        TNode* currentNode = getNodeAtPosition(position);
        TNode* newNode = new TNode{ _value, currentNode->pNext };
        currentNode->pNext = newNode;
        size++;
    }

    void removeNodeAfter(size_t position) {

        if (position >= size) { throw out_of_range("Invalid position"); }

        if (position == 0) { popFront(); }

        else
        {
            TNode* currentNode = getNodeAtPosition(position);
            TNode* deletedNode = currentNode->pNext;
            currentNode->pNext = deletedNode->pNext;
            delete deletedNode;
            size--;
        }
    }

    T& getFront() {

        if (pFirst == nullptr) { throw out_of_range("List is empty"); }
        return pFirst->value;
    }

    const T& getValueAtPosition(size_t position) const {

        return getNodeAtPosition(position)->value;
    }

    void clear() {

        while (pFirst != nullptr)
        {
            TNode* temp = pFirst;
            pFirst = pFirst->pNext;
            delete temp;
        }
        size = 0;
    }

    friend ostream& operator<<(ostream& stream, const TList& list) {

        int cnt = 0;
        for (TNode* p = list.pFirst; p != nullptr; p = p->pNext)
        {
            if (p->value.coef >= 0 && cnt != list.getSize() && cnt != 0) { stream << '+'; }
            cnt++;

            stream << p->value;
        }
        return stream;
    }

    ~TList() {

        clear();
    }
};
#endif