//
// Created by Aashman Gupta on 2/14/18.
//

#include "heap.h"
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "stack.h"

struct heap {
    BST* tree;
    int size;
    QUEUE* itemQueue;
    STACK* itemStack;
    void (*display)(void *,FILE *);
    int (*comparator)(void *,void *);
    void (*free)(void *);
};

HEAP *newHEAP(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *)) {
    HEAP* heap1 = malloc(sizeof(HEAP));

    assert(heap1 != 0);

    heap1->tree = newBST(d, c, 0, f);
    heap1->itemQueue = newQUEUE(0, 0);
    heap1->itemStack = newSTACK(0, 0);
    heap1->display = d;
    heap1->comparator = c;
    heap1->free = f;
    heap1->size = 0;

    return heap1;
};

void insertHEAP(HEAP *h,void *value) {
    BSTNODE* currNode = newBSTNODE(value);
    BSTNODE* temp = 0;

    assert(currNode != 0);

    setBSTsize(h->tree, sizeBST(h->tree) + 1);
    h->size++;

    if(getBSTroot(h->tree) == 0) {
        setBSTroot(h->tree, currNode);
        enqueue(h->itemQueue, currNode);
        push(h->itemStack, currNode);        //deleted so leaves aren't pushed to stack
        return;
    }

    while(1) {
        temp = peekQUEUE(h->itemQueue);

        if (getBSTNODEleft(temp) == 0) {
            setBSTNODEleft(temp, currNode);
            setBSTNODEparent(currNode, temp);
            enqueue(h->itemQueue, currNode);
            push(h->itemStack, currNode);
            return;
        }

        else if (getBSTNODEright(temp) == 0) {
            setBSTNODEright(temp, currNode);
            setBSTNODEparent(currNode, temp);
            enqueue(h->itemQueue, currNode);
            push(h->itemStack, currNode);     //deleted so leaves aren't pushed to stack
            return;
        }
        else {
            dequeue(h->itemQueue);
        }
    }
}

void displayHEAPdebug(HEAP *h,FILE *fp) {
    fprintf(fp, "heap size: %d\n", sizeHEAP(h));

    if(h == 0) {
        fprintf(fp, "bst size: 0\n");
        return;
    }
    else {
        fprintf(fp, "bst size: %d\n", sizeBST(h->tree));
    }

    displayBSTdebug(h->tree, fp);
}

void displayHEAP(HEAP *h,FILE *fp) {
    if(h != 0) {
        displayBST(h->tree, fp);
    }
    return;
}

static void heapfiy(HEAP* h, BSTNODE* currNode) {
    BSTNODE* left = getBSTNODEleft(currNode);
    BSTNODE* right = getBSTNODEright(currNode);

    if((left == 0) && (right == 0)) {
        return;
    }

    BSTNODE* smallestVal = currNode;

    if ((left != 0) && ((h->comparator(getBSTNODEvalue(left), getBSTNODEvalue(currNode))) < 0)) {
        smallestVal = left;
    }

    if((right != 0) && (h->comparator(getBSTNODEvalue(right), getBSTNODEvalue(smallestVal)) < 0)) {
        smallestVal = right;
    }

    if(h->comparator(getBSTNODEvalue(smallestVal), getBSTNODEvalue(currNode)) != 0) {
        void* val = getBSTNODEvalue(smallestVal);
        setBSTNODEvalue(smallestVal, getBSTNODEvalue(currNode));
        setBSTNODEvalue(currNode, val);
        heapfiy(h, smallestVal);
    }
}

void buildHEAP(HEAP *h) {
    if(getBSTroot(h->tree) == 0) {
        return;
    }

    if((getBSTNODEright(getBSTroot(h->tree)) == 0) && (getBSTNODEleft(getBSTroot(h->tree)) == 0)) {
        return;
    }
    BSTNODE* tempNode;
    STACK* tempStack = newSTACK(0, 0);

    while(sizeSTACK(h->itemStack) != 0) {
        tempNode = pop(h->itemStack);
        heapfiy(h, tempNode);
        push(tempStack, tempNode);
    }

    while(sizeSTACK(tempStack) != 0) {
        push(h->itemStack, pop(tempStack));
    }
    freeSTACK(tempStack);
}

void *extractHEAP(HEAP *h) {
    void* retVal;

    if(h == 0) {
        return 0;
    }

    if(getBSTroot(h->tree) == 0) {
        return 0;
    }

    if((getBSTNODEleft(getBSTroot(h->tree)) == 0) && (getBSTNODEright(getBSTroot(h->tree)) == 0)) {
        retVal = getBSTNODEvalue(getBSTroot(h->tree));
        pruneLeafBST(h->tree, getBSTroot(h->tree));
        h->size--;
        return retVal;
    }

    retVal = getBSTNODEvalue(getBSTroot(h->tree));

    BSTNODE* leafNode = pop(h->itemStack);

    setBSTNODEvalue(getBSTroot(h->tree), getBSTNODEvalue(leafNode));

    pruneLeafBST(h->tree, leafNode);

	freeBSTNODE(leafNode, 0);

    heapfiy(h, getBSTroot(h->tree));

    h->size--;

    return retVal;
}

void *peekHEAP(HEAP *h) {
    if(h == 0) {
        return 0;
    }
    BSTNODE* temp = getBSTroot(h->tree);

    if(temp == 0) {
        return 0;
    }

    return getBSTNODEvalue(temp);
}

int  sizeHEAP(HEAP *h) {
    if(h == 0) {
        return 0;
    }
    return h->size;
}

void freeHEAP(HEAP *h) {
    freeBST(h->tree);
    freeSTACK(h->itemStack);
    freeQUEUE(h->itemQueue);
    free(h);
}
