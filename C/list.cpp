/*#include "list.h"

list::list() {
    itemList *head;
    head = NULL;
}

virtual list::~list() {
    list::DeleteList();
}

void list::push(Type name, QString info) {
    list::AddListItem(name,info);
}

void list::AddListItem(QString name, QString info) {
    if (head == NULL) {
        work = new itemList;
        work->next = NULL;
        head = work;
        last = work;
        head->info = info;
        head->name = name;
    }
    while (last->next != NULL) {
            last = last->next;
    }
    else {

        work = new itemList;
        work->next = NULL;
        last->next = work;
        work->info = info;
        work->name = name;
        last=work;
    }
}

bool list::DeleteList(QString name) {
    itemLis *work,*work1;
    bool flag = false;

    while((head->name == name) && (head != NULL)) {
          work = head;
          head = head->next;
          delete work;
          flag = true;
     }
     work = head;

     while(work->next != NULL) {

        if(work->next->name == name) {
          work1=work->next;
          work->next=work1->next;
          delete work1;
          flag = true;
        }
        else {
          work = work->next;
        }
      }
     return flag;
}

bool list::DeleteList() {
    itemLis *work;
    bool flag = false;
    work = head;

    while(work != NULL) {
       head=work->next;
       delete work;
       work = head;
       flag = true;
    }
    head=work;
    return flag;
}

itemList list::SearchListItem(QString name) {
    itemList *work;
    itemList *search;
    search = NULL;
    work = head;

    while(work != NULL) {

        if(work->name == name) {
            search = work;
        }
        work = work->next;
    }
    return search;
}

int list::NumberListItem() {
    int num(0);
    itemList *work;
    work = head;

    while (work != NULL) {
        num++;
        work = work->next;
    }

    return num;
}

QString list::Search(QString name) {
    QString info;

    if (list::SearchListItem(name) != NULL) {
        info = list::SearchListItem(name)->info;
    }
    else {
        info = "Item not found";
    }
    return info;
}

QString list::FrontName() {
    return head->name;
}

QString list::FrontInfo() {
    return head->info;
}

QString list::BackName() {
    return last->name;
}

QString list::BackInfo() {
    return last->info;
}
*/

