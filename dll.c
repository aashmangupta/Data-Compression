//
// Created by Aashman Gupta on 1/22/18.
// Doubl

#include "dll.h"
#include <stdlib.h>
#include <assert.h>


typedef struct node {
    void* val;
    struct node* next;
    struct node* prev;
} NODE;

struct dll {
    NODE* head;
    NODE* tail;
    int size;
    void (*display)(void*, FILE*);
    void (*free)(void *);
};

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)) {
    DLL* items = malloc(sizeof(DLL));

    assert(items != 0);

    items->head = NULL;
    items->tail = NULL;
    items->size = 0;
    items->display = d;
    items->free = f;

    return items;
}

void insertDLL(DLL *items,int index,void *value) {
    assert((index >= 0) && (index <= items->size));

    NODE* currNode = malloc(sizeof(NODE));
    currNode->val = value;

    if(items->tail == NULL) {                       //takes care of the tail when its null
        items->tail = currNode;
    }

    if(index == 0) {
        currNode->next = items->head;
        currNode->prev = NULL;
        if(items->head != NULL) {
            items->head->prev = currNode;
        }
        items->head = currNode;
        items->size++;
    }

    else if(index == items->size) {
        currNode->next = NULL;
        currNode->prev = items->tail;
        items->tail->next = currNode;
        items->tail = currNode;
        items->size++;
    }

    else {
        NODE* temp = items->head;

        int half = (items->size - 1) / 2;

        if(index < half) {
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
        }

        else {
            temp = items->tail;

            for (int i = items->size - 1; i >= index ; i--) {
                temp = temp->prev;
            }
        }

        currNode->prev = temp;
        currNode->next = temp->next;
        temp->next->prev = currNode;
        temp->next = currNode;
        items->size++;
    }
    return;
}

int sizeDLL(DLL *items) {
    if(items == NULL) {
        return 0;
    }
    return items->size;
}

void *removeDLL(DLL *items,int index) {
    assert((items->size > 0) && (index >= 0) && (index < items->size));

    void *deletedVal;
    NODE* freeThis;

    if(items->head == items->tail) {
        deletedVal = items->tail->val;
        freeThis = items->tail;
        items->tail = NULL;
        items->head = NULL;
        items->size--;
        free(freeThis);
        return deletedVal;
    }

    if(index == 0) {
        deletedVal = items->head->val;
        freeThis = items->head;
        items->head->next->prev = NULL;
        items->head = items->head->next;
        items->size--;
        free(freeThis);
        return deletedVal;
    }

    else if(index == items->size - 1) {
        deletedVal = items->tail->val;
        freeThis = items->tail;

        items->tail->prev->next = NULL;
        items->tail = items->tail->prev;
        items->size--;
        free(freeThis);
        return deletedVal;
    }

    else {
        NODE* temp = items->head;

        int half = (items->size - 1) / 2;

        if(index < half) {
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
        }

        else {
            temp = items->tail;

            for (int i = items->size - 1; i > index ; i--) {
                temp = temp->prev;
            }
        }

        deletedVal = temp->val;
        freeThis = temp;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(freeThis);
        items->size--;
        return deletedVal;
    }
}

void displayDLL(DLL *items,FILE *fp) {
    fprintf(fp, "{{");

    if(items == NULL) {
        fprintf(fp, "}}");
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

    fprintf(fp, "}}");
    return;
}

void displayDLLdebug(DLL *items,FILE *fp) {
    fprintf(fp, "head->");
    displayDLL(items, fp);
    fprintf(fp, ",tail->{{");
    if(items != NULL) {
        if (items->tail != NULL) {
            items->display(items->tail->val, fp);
        }
    }
    fprintf(fp, "}}");
}

void *getDLL(DLL *items,int index) {
    assert((index >= 0) && (index < items->size));
    if(index == 0) {
        return items->head->val;
    }

    else if(index == items->size - 1) {
        return items->tail->val;
    }

    else{
        NODE* temp = items->head;

        int half = (items->size - 1) / 2;

        if(index < half) {
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
        }

        else {
            temp = items->tail;

            for (int i = items->size - 1; i > index ; i--) {
                temp = temp->prev;
            }
        }

        return temp->val;
    }
}

void *setDLL(DLL *items,int index,void *value) {
    assert((index >= 0) && (index <= items->size));
    void* oldVal;
    if ((index == 0) && (items->size > 0)) {
        oldVal = items->head->val;
        items->head->val = value;
        return oldVal;
    }

    else if(index == items->size) {
        insertDLL(items, index, value);
        return NULL;
    }

    else {
        NODE* temp;

        int half = (index / 2) + 1;


        if(index < half) {
            temp = items->head;

            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
        }

        else {
            temp = items->tail;

            for (int i = items->size - 1; i > index ; i--) {
                temp = temp->prev;
            }
        }

        oldVal = temp->val;
        temp->val = value;
        return oldVal;
    }
}

void unionDLL(DLL *recipient,DLL *donor) {

    if(donor == NULL) {
        return;
    }

    if(recipient == NULL) {
        return;
    }

    if (donor->head == NULL) {
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

    else {
        recipient->tail->next = donor->head;
        donor->head->prev = recipient->tail;
        recipient->tail = donor->tail;
        recipient->size = recipient->size + donor->size;
        donor->head = NULL;
        donor->tail = NULL;
        donor->size = 0;
    }
}

void freeDLL(DLL *items) {
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

