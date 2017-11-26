#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "itemList.h"

template <class Type>
class Mylist {
private:
    itemList<Type> *head;
    itemList<Type> *last;

    void AddListItem(Type name, Type info) {
        itemList<Type> *work;

        if (head == nullptr) {
            work = new itemList<Type>("0");
            work->next = nullptr;
            head = work;
            last = work;
            head->SetName(name);
            head->SetInfo(info);
            head->SetNum(Mylist::NumberListItem());
        }
        else {

            while (last->next != nullptr) {
                    last = last->next;
            }

            work = new itemList<Type>("0");
            work->next = nullptr;
            last->next = work;
            work->prev = last;
            work->SetName(name);
            work->SetInfo(info);
            work->SetNum(Mylist::NumberListItem());
            last = work;
        }
    }

    void AddListItem(int num, int idStation, Type Coordinates, Type name) {
        itemList<Type> *work;

        if (head == nullptr) {
            work = new itemList<Type>;
            work->next = nullptr;
            head = work;
            last = work;
            head->SetName(name);
            head->SetCoordinates(Coordinates);
            head->SetIdStation(idStation);
            head->SetNum(num);
        }
        else {

            while (last->next != nullptr) {
                    last = last->next;
            }

            work = new itemList<Type>;
            work->next = nullptr;
            last->next = work;
            work->prev = last;
            work->SetName(name);
            work->SetCoordinates(Coordinates);
            work->SetIdStation(idStation);
            work->SetNum(num);
            last = work;
        }
    }

    itemList<Type> *SearchListItem(Type name) {
        itemList<Type> *work;
        itemList<Type> *search;
        search = nullptr;
        work = head;

        while(work != nullptr) {

            if(work->GetName() == name) {
                search = work;
            }
            work = work->next;
        }
        return search;
    }

public:
    Mylist() {
        head = nullptr;
        last = nullptr;
    }

    virtual ~Mylist() {
        bool flag = DeleteList();
        if (!flag) {
            std::cout << std::endl << "No delete list";
        }
    }

    bool CheckNull() {
        if (head == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    int NumberListItem() { //повертає кількість листів
        int num(0);
        itemList<Type> *work;
        work = head;

        while (work != nullptr) {
            num++;
            work = work->next;
        }

        return num;
    }

    Type popName(int i) { //повертає назву по номеру
        itemList<Type> *work;
        Type u;
        work = head;

        if (i > Mylist::NumberListItem()) {
            return head->GetName();
        }
        else {
            while(work != nullptr) {

                if(work->GetNum() == i) {
                    return work->GetName();
                }
                work = work->next;
            }
        }
        return u;
    }

    int popStation(int i) {
        itemList<Type> *work;
        int u;
        work = head;

        if (i > Mylist::NumberListItem()) {
            return head->GetIdStation();
        }
        else {
            while(work != nullptr) {

                if(work->GetNum() == i) {
                    return work->GetIdStation();
                }
                work = work->next;
            }
        }
        return u;
    }

    Type popCoordinates(int i) {
        itemList<Type> *work;
        Type u;
        work = head;

        if (i > Mylist::NumberListItem()) {
            return head->GetCoordinates();
        }
        else {
            while(work != nullptr) {

                if(work->GetNum() == i) {
                    return work->GetCoordinates();
                }
                work = work->next;
            }
        }
        return u;
    }

    bool DeleteList(Type name) {
        itemList<Type> *work,*work1;
        bool flag = false;

        if (head == nullptr || work->next == ((void*)0xfeeefeee)) {
            flag = true;
        }
        else {
            while((head->GetName() == name) && (head != nullptr) && work->next != ((void*)0xfeeefeee)) {
                  work = head;
                  head = head->next;
                  delete work;
                  flag = true;
             }
             work = head;

             while(work->next != nullptr && work->next != ((void*)0xfeeefeee)) {

                if(work->next->GetName() == name) {
                  work1 = work->next;
                  work->next = work1->next;
                  delete work1;
                  flag = true;
                }
                else {
                  work = work->next;
                }
              }
        }
         return flag;
    }

    bool DeleteList() {
        itemList<Type> *work;
        bool flag = false;
        work = head;

        if (head == nullptr || work->next == ((void*)0xfeeefeee)) {
            flag = true;
        }
        else {
            while(work != nullptr && work->next != ((void*)0xfeeefeee)) {
               head = work->next;
               delete work;
               work = head;
               flag = true;
            }
            head = work;
        }
        return flag;
    }

    void push(Type name,Type info) {
        Mylist::AddListItem(name,info);
    }

    void push(int num, int idStation, Type Coordinates, Type name) {
        Mylist::AddListItem(num, idStation, Coordinates, name);
    }

    Type FrontName() {
        return head->GetName();
    }

    Type FrontInfo() {
        return head->GetInfo();
    }

    Type BackName() {
        return last->GetName();
    }

    Type BackInfo() {
        return last->GetInfo();
    }

    Type Search(Type name) {
        Type info;

        if (!CheckNull()) {
            info = FrontInfo();

            if (Mylist::SearchListItem(name) != nullptr) {
                info = Mylist::SearchListItem(name)->GetInfo();
            }
        }

        return info;
    }

    int Check(int i) { //перевірка чи є такий номер
        bool flag = false;

        itemList<Type> *work;
        work = head;

        if (i > Mylist::NumberListItem()) {
            return 111;
        }
        else {
            while(work != nullptr) {

                if(work->GetNum() == i) {
                    flag = true;
                }
                work = work->next;
            }
        }

        if (!flag) {
            return 112;
        }
        return 0;
    }

    Mylist& operator= ( Mylist right ) {
        head = right.head;
        last = right.last;
        return *this ;
    }

};

#endif // LIST_H
