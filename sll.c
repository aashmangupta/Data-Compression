//
// Created by Aashman Gupta on 1/16/18.
//

#include "sll.h"
#include <stdlib.h>
#include <assert.h>

typedef struct node{
    void* val;
    struct node* next;
} NODE;

struct sll {
    NODE* head;
    NODE* tail;
    int size;
    void (*display)(void*, FILE*);
    void (*free)(void *);
};

SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *)) {
    SLL *items = malloc(sizeof(SLL));

    assert(items != 0);

    items->head = NULL;
    items->tail = NULL;
    items->size = 0;
    items->display = d;
    items->free = f;

    return items;
}

void insertSLL(SLL *items,int index,void *value) {
    assert((index >= 0) && (index <= items->size));

    NODE* currNode = malloc(sizeof(NODE));
    currNode->val = value;

    if(items->tail == NULL) {                       //takes care of the tail when its null
        items->tail = currNode;
    }

    if(index == 0) {
        currNode->next = items->head;               //Insert to front
        items->head = currNode;
        items->size++;
    }

    else if(index == items->size) {                 //Insert to back
        items->tail->next = currNode;
        items->tail = currNode;
        items->size++;
        currNode->next = NULL;
    }


    else {                                          //Insert at nth position
        NODE* temp = items->head;

        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        currNode->next = temp->next;
        temp->next = currNode;
        items->size++;
    }
}

void displaySLL(SLL *items,FILE *fp) {
    fprintf(fp, "{");

    if(items == NULL) {
        fprintf(fp, "}");
        return;
    }

    NODE* temp = items->head;

    for(int i = 0; i < items->size; i++) {
        items->display(temp->val, fp);
        temp = temp->next;
        if(i != items->size-1) {
            fprintf(fp, ",");
        }
    }

    fprintf(fp, "}");
}

int sizeSLL(SLL *items) {
    if(items == NULL) {
        return 0;
    }
    return items->size;
}

void *removeSLL(SLL *items,int index) {
    assert((items->size > 0) && (index >= 0) && (index < items->size));

    void* deletedVal;
    NODE* freeThis;

    if(items->head == items->tail) {
        items->tail = NULL;
    }

    if(index == 0) {
        deletedVal = items->head->val;
        freeThis = items->head;
        items->head = items->head->next;
        items->size--;
        free(freeThis);
        return deletedVal;
    }

    else if (index == items->size -1) {
        NODE* temp = items->head;
        deletedVal = items->tail->val;
        freeThis = items->tail;

        for (int i = 0; i < items->size - 2; i++) {
            temp = temp->next;
        }
        items->tail = temp;
        temp->next = NULL;
        items->size--;
        free(freeThis);
        return deletedVal;
    }

    else {
        NODE* temp = items->head;
        for (int i = 0; i < index - 1 ; i++) {
            temp = temp->next;
        }
        deletedVal = temp->next->val;
        freeThis = temp->next;
        temp->next = temp->next->next;
        items->size--;
        free(freeThis);
        return deletedVal;
    }
}

void unionSLL(SLL *recipient,SLL *donor) {
    if(donor == NULL) {
        return;
    }

    if(recipient == NULL) {
        return;
    }

    if(donor->head == NULL) {
        return;
    }

    else if(recipient->head == NULL) {
        recipient->head = donor->head;
        recipient->tail = donor->tail;
        recipient->size = donor->size;
        donor->head = NULL;
        donor->tail = NULL;
        donor->size = 0;
        return;
    }

    recipient->tail->next = donor->head;
    recipient->tail = donor->tail;
    donor->head = NULL;
    donor->tail = NULL;
    recipient->size = recipient->size + donor->size;
    donor->size = 0;
}

void *getSLL(SLL *items,int index) {
    assert((index >= 0) && (index < items->size));

    if(index == 0) {
        return items->head->val;
    }

    else if(index == items->size - 1) {
        return items->tail->val;
    }

    else{
        NODE* temp = items->head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->val;
    }
}

void *setSLL(SLL *items,int index,void *value) {
    assert((index >= 0) && (index <= items->size));
    void* oldVal;

    if (index == items->size - 1) {
        oldVal = items->tail->val;
        items->tail->val = value;           //Add an if statement for setting and updating tail value
        return oldVal;
    }

    else if(index == items->size) {
        insertSLL(items, index, value);
        return NULL;

    }

    else {
        NODE* temp = items->head;
        for (int i = 0; i < index ; i++) {
            temp = temp->next;
        }
        oldVal = temp->val;
        temp->val = value;
        return oldVal;
    }
}

void displaySLLdebug(SLL *items,FILE *fp) {
    fprintf(fp, "head->");
    displaySLL(items, fp);
    fprintf(fp, ",tail->{");
    if(items != NULL) {
        if (items->tail != NULL) {
            items->display(items->tail->val, fp);
        }
    }

    fprintf(fp, "}");
}

void freeSLL(SLL *items) {
    if(items == NULL) {
        return;
    }
    NODE* temp = NULL;
    while(items->head != NULL) {
        if(items->free != NULL) {
            items->free(items->head->val);
        }
        temp = items->head->next;
        free(items->head);
        items->head = temp;
    }
    free(items);
}
