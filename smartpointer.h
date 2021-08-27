#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include <vector>


template<typename T>
struct Reference {
public:
    Reference<T>(T* ptr, unsigned int cnt = 1): ptr(ptr), counter(cnt) {}

    T* ptr;
    unsigned int counter;
};

template<typename T>
class ReferenceCounter {
private:
    static std::vector<Reference<T>*> refs;
public:
    static bool hasReference(T* ptr) {
        for (Reference<T>* ref : refs) if (ref->ptr == ptr) return true;
        return false;
    }

    static void addPtrToReferences(T* ptr) {
        if (hasReference(ptr)) {
            for (Reference<T>* ref : refs) {
                if (ref->ptr == ptr) {
                    ref->counter++;
                    break;
                }
            }
        } else {
            Reference<T>* newRef = new Reference<T>(ptr);
            refs.push_back(newRef);
        }
    }

    static void removePtrFromReferences(T* ptr) {
        if (hasReference(ptr)) {
            for (int i = 0; i < refs.size(); i++) {
                Reference<T>* ref = refs[i];
                if (ref->ptr == ptr) {
                    if (ref->counter == 1) {
                        delete ref;
                        refs.erase(refs.begin()+i);
                    } else {
                        ref->counter--;
                    }
                    break;
                }
            }
        }
    }
};

template<typename T>
std::vector<Reference<T>*> ReferenceCounter<T>::refs;


template<typename T>
class SmartPointer {
private:
    T* zeigerAufObjekt;

    void loescheObjekt() {
        if (zeigerAufObjekt != nullptr) ReferenceCounter<T>::removePtrFromReferences(zeigerAufObjekt);
    }
public:
    SmartPointer<T>(T* p = nullptr): zeigerAufObjekt(p) {
        if (p != nullptr) ReferenceCounter<T>::addPtrToReferences(p);
    }
    ~SmartPointer<T>() {
        loescheObjekt();
    }

    SmartPointer<T>(SmartPointer<T>& sm) {
        zeigerAufObjekt = sm.Ptr();
        if (zeigerAufObjekt != nullptr) ReferenceCounter<T>::addPtrToReferences(zeigerAufObjekt);
    }

    T* operator->() const {return zeigerAufObjekt;}
    T& operator*() const {return *zeigerAufObjekt;}

    SmartPointer<T>& operator=(T *p) {
        if (zeigerAufObjekt == nullptr) {
            if (p != nullptr) {
                zeigerAufObjekt = p;
                ReferenceCounter<T>::addPtrToReferences(zeigerAufObjekt);
            }
            return *this;
        } else if (p == nullptr) {
            ReferenceCounter<T>::removePtrFromReferences(zeigerAufObjekt);
            zeigerAufObjekt = nullptr;
            return *this;
        } else throw std::invalid_argument("Dieser Zeiger zeigt bereits auf ein Objekt. Deswegen kann ihm keine neue Adresse zugewiesen werden.");
    }

    SmartPointer<T>& operator=(SmartPointer<T>& sm) {
        if (this->zeigerAufObjekt != nullptr) ReferenceCounter<T>::removePtrFromReferences(zeigerAufObjekt);
        this->zeigerAufObjekt = sm.Ptr();
        if (zeigerAufObjekt != nullptr) ReferenceCounter<T>::addPtrToReferences(zeigerAufObjekt);
        return *this;
    }

    operator bool() const {return zeigerAufObjekt != nullptr;}

    T* Ptr() {return zeigerAufObjekt;}
};

#endif // SMARTPOINTER_H
