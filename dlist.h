#ifndef DLIST_H
#define DLIST_H

#include "smartpointer.h"


template<typename T>
class DListItem {
private:
    T data;
    SmartPointer<DListItem<T>> next;
    SmartPointer<DListItem<T>> prev;
public:
    DListItem<T>(const T& data, SmartPointer<DListItem<T>> next, SmartPointer<DListItem<T>> prev): data(data), next(next), prev(prev) {}

    T getData() const {return data;}
    SmartPointer<DListItem<T>>& getNext() {return next;}
    SmartPointer<DListItem<T>>& getPrev() {return prev;}
    void setNext(SmartPointer<DListItem<T>> next) {this->next = next;}
    void setPrev(SmartPointer<DListItem<T>> prev) {this->prev = prev;}
};

template<typename T>
class DList {
private:
    SmartPointer<DListItem<T>> first, last;
    int length;

    int search(const T& data) {
        if (empty()) return -1;
        int counter = 0;
        SmartPointer<DListItem<T>> item = first;
        while (item->getData() != data) {
            if (item.Ptr() == last.Ptr()) return -1;
            item = item->getNext();
            counter++;
        }
        return counter;
    }

public:
    DList<T>(): length(0) {}
    ~DList<T>() {
        while (!empty()) pop_back();
    }


    bool empty() const {return length == 0;}
    int getLength() const {return length;}

    void push_back(const T& data) {
        if (empty()) {
            DListItem<T>* newItem = new DListItem<T>(data, nullptr, nullptr);
            first = newItem;
            last = first;
        } else {
            DListItem<T>* newItem = new DListItem<T>(data, nullptr, last);
            last = nullptr;
            last = newItem;
            last->getPrev()->setNext(last);
        }
        length++;
    }

    void push_front(const T& data) {
        if (empty()) {
            DListItem<T>* newItem = new DListItem<T>(data, nullptr, nullptr);
            first = newItem;
            last = first;
        } else {
            DListItem<T>* newItem = new DListItem<T>(data, first, nullptr);
            first = nullptr;
            first = newItem;
            first->getNext()->setPrev(first);
        }
        length++;
    }

    void pop_back() {
        if (!empty()) {
            if (length == 1) {
                first = nullptr;
                last = nullptr;
            } else {
                SmartPointer<DListItem<T>> pre_last = last->getPrev();
                last = nullptr;
                pre_last->setNext(nullptr);
                last = pre_last;
            }
            length--;
        }
    }

    void pop_front() {
        if (!empty()) {
            if (length == 1) {
                first = nullptr;
                last = nullptr;
            } else {
                SmartPointer<DListItem<T>> post_first = first->getNext();
                first = nullptr;
                post_first->setPrev(nullptr);
                first = post_first;
            }
            length--;
        }
    }

    bool insert(const T& data, const int index) {
        if (index >= 0 && index < length) {
            if (index == 0) {
                push_front(data);
            } else if (index == length - 1) {
                SmartPointer<DListItem<T>> newItem(new DListItem<T>(data, last, last->getPrev()));
                newItem->getPrev()->setNext(newItem);
                newItem->getNext()->setPrev(newItem);
                length++;
            } else {
                int counter = 0;
                SmartPointer<DListItem<T>> item = first;
                while (counter != index) {
                    item = item->getNext();
                    counter++;
                }
                SmartPointer<DListItem<T>> newItem(new DListItem<T>(data, item, item->getPrev()));

                newItem->getPrev()->setNext(newItem);
                newItem->getNext()->setPrev(newItem);
                length++;
            }
            return true;
        }
        return false;
    }

    bool exists(const T& data) {
        return search(data) != -1;
    }

    T getAt(const int index) {
        if (index < 0 || index >= length) throw std::invalid_argument("Index ist falsch");
        int counter = 0;
        SmartPointer<DListItem<T>> item = first;
        while (counter != index) {
            item = item->getNext();
            counter++;
        }
        return item->getData();
    }

    bool removeAt(const int index) {
        if (index >= 0 && index < length) {
            if (index == 0) {
                pop_front();
            } else if (index == length - 1) {
                pop_back();
            } else {
                int counter = 0;
                SmartPointer<DListItem<T>> item = first;
                while (counter != index) {
                    item = item->getNext();
                    counter++;
                }
                item->getPrev()->setNext(item->getNext());
                item->getNext()->setPrev(item->getPrev());
                length--;
            }
            return true;
        }
        return false;
    }

    bool remove(const T& data) {
        if (exists(data)) {
            const int index = search(data);
            return removeAt(index);
        }
        return false;
    }

    void invert() {
        if (!empty() && length > 1) {
            SmartPointer<DListItem<T>> helper = first;
            first = last;
            last = helper;

            first->setNext(first->getPrev());
            first->setPrev(nullptr);
            last->setPrev(last->getNext());
            last->setNext(nullptr);

            if (length == 2) return;

            SmartPointer<DListItem<T>> item = first->getNext();
            while (item.Ptr() != last.Ptr()) {
                SmartPointer<DListItem<T>> helper = item->getPrev();
                item->setPrev(item->getNext());
                item->setNext(helper);
                item = item->getNext();
            }
        }
    }

};

#endif // DLIST_H
