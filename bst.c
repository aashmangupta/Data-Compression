//
// Created by Aashman Gupta on 2/6/18.
//
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"

//checked and passed
struct bstnode {
    void* value;
    BSTNODE* left;
    BSTNODE* right;
    BSTNODE* parent;
};

//checked and passed
BSTNODE *newBSTNODE(void *v) {
    BSTNODE* currNode = malloc(sizeof(BSTNODE));

    assert(currNode != 0);

    currNode->value = v;
    currNode->left = 0;
    currNode->right = 0;
    currNode->parent = 0;

    return currNode;
}

//checked and passed
void *getBSTNODEvalue(BSTNODE *n) {
    if(n == 0) {
        return 0;
    }
    return n->value;
}

//checked and passed
void setBSTNODEvalue(BSTNODE *n,void *value) {
    if(n == 0) {
        return;
    }
    n->value = value;
}

//checked and passed
BSTNODE *getBSTNODEleft(BSTNODE *n) {
    if(n == 0) {
        return 0;
    }

    return n->left;
}

//checked and passed
void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement) {
    if(n == 0) {
        return;
    }
    n->left = replacement;
}

//checked and passed
BSTNODE *getBSTNODEright(BSTNODE *n) {
    if(n == 0) {
        return 0;
    }
    return n->right;
}

//checked and passed
void setBSTNODEright(BSTNODE *n,BSTNODE *replacement) {
    if(n == 0) {
        return;
    }
    n->right = replacement;
}

//checked and passed
BSTNODE *getBSTNODEparent(BSTNODE *n) {
    if(n == 0) {
        return 0;
    }
    return n->parent;
}

//checked and passed
void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement) {
    if(n == 0) {
        return;
    }
    n->parent = replacement;
}

//checked and passed
void freeBSTNODE(BSTNODE *n,void (*f)(void *)) {
    if(n == 0) {
        return;
    }
    if(f != NULL) {
        f(n->value);
    }
    free(n);
}

//checked and passed
static void mySwapperFunc(BSTNODE* original, BSTNODE* replacement) {
    void* val = original->value;
    original->value = replacement->value;
    replacement->value = val;
}

//checked and passed
struct bst{
    BSTNODE* root;
    int sizeBST;
    void (*display)(void *,FILE *);
    int (*comparator)(void *,void *);
    void (*swapper)(BSTNODE *,BSTNODE *);
    void (*free)(void *);
};

//checked and passed
BST *newBST(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*s)(BSTNODE *,BSTNODE *), void (*f)(void *)) {
    BST* tree = malloc(sizeof(BST));

    assert(tree != 0);

    tree->sizeBST = 0;
    tree->root = 0;
    tree->display = d;
    tree->comparator = c;
    if(s != 0) {
        tree->swapper = s;
    }
    else {
        tree->swapper = mySwapperFunc;
    }
    tree->free = f;

    return tree;
}

//checked and passed
BSTNODE *getBSTroot(BST *t) {
    if(t == 0) {
        return 0;
    }
    return t->root;
}

//checked and passed
void setBSTroot(BST *t,BSTNODE *replacement) {
    if (t != 0) {
        t->root = replacement;
    }
}

//checked and passed
void setBSTsize(BST *t,int s) {
    if(t != 0) {
        t->sizeBST = s;
    }
}

                                //*******   MAJOR CODING BEGINS AT THIS POINT   *******//

//checked and passed
static BSTNODE *insertBSTHelper(BST* tree, BSTNODE* root, BSTNODE* insertion) {
    if(root == 0) {
        insertion->parent = root;
        root = insertion;
        return root;
    }

    else if(tree->comparator(root->value, insertion->value) > 0) {
        if(root->left == 0) {
            root->left = insertion;
            insertion->parent = root;
            return root;
        }

        else {
            root->left = insertBSTHelper(tree, root->left, insertion);
        }
    }

    else {
        if(root->right == 0) {
            root->right = insertion;
            insertion->parent = root;
            return root;
        }

        else {
            root->right = insertBSTHelper(tree, root->right, insertion);
        }
    }
    return root;
}

//checked and passed
BSTNODE *insertBST(BST *t,void *value) {
    if(t == 0) {
        return 0;
    }

    BSTNODE *currNode = newBSTNODE(value);

    assert(currNode != NULL);

    t->root = insertBSTHelper(t, t->root, currNode);

    t->sizeBST++;

    return currNode;
}

//checked and passed
static void displayBSTHelper(BST* tree, BSTNODE* root, FILE* fp, int flag) {
    if(root == 0) {
        return;
    }
    if(flag == 1000) {
        fprintf(fp, "[");
    }
    else {
        fprintf(fp, " [");
    }
    tree->display(root->value, fp);
    displayBSTHelper(tree, root->left, fp, 0);
    displayBSTHelper(tree, root->right, fp, 0);
    fprintf(fp, "]");
}

//checked and passed
void displayBST(BST *t,FILE *fp) {
    if(t->sizeBST == 0) {
        fprintf(fp, "[]");
        return;
    }
    displayBSTHelper(t, t->root, fp, 1000);
}

//checked and passed
static BSTNODE *findBSTHelper(BST *tree, BSTNODE* root, void* val) {
    if(root == 0) {
        return 0;
    }

    else if(tree->comparator(root->value, val) == 0) {
        return root;
    }

    else if(tree->comparator(root->value, val) > 0) {
        return findBSTHelper(tree, root->left, val);
    }

    else {
        return findBSTHelper(tree, root->right, val);
    }
}

//checked and passed
BSTNODE *findBST(BST *t,void *value) {
    if(t == 0) {
        return 0;
    }
    return findBSTHelper(t, t->root, value);
}

//checked and passed
static BSTNODE* findSuccessor(BSTNODE* currNode) {
    currNode = currNode->right;

    if(currNode == 0) {
        return 0;
    }

    while(currNode->left != 0) {
        currNode = currNode->left;
    }

    return currNode;
}

//checked and passed
static BSTNODE* findPredecessor(BSTNODE* currNode) {

    currNode = currNode->left;

    if(currNode == 0) {
        return currNode;
    }

    while(currNode->right != 0) {
        currNode = currNode->right;
    }

    return currNode;
}

//checked and passed
static BSTNODE* swapToLeafHelper(BST* tree, BSTNODE* currNode) {
    BSTNODE* newNode;

    if((currNode->left == 0) && (currNode->right == 0)) {
        return currNode;
    }

    else if(currNode->right != 0) {
        newNode = findSuccessor(currNode);
        tree->swapper(currNode, newNode);
        return swapToLeafHelper(tree, newNode);
    }

    else {
        newNode = findPredecessor(currNode);
        tree->swapper(currNode, newNode);
        return swapToLeafHelper(tree, newNode);
    }
}

//checked and passed
BSTNODE *swapToLeafBST(BST *t,BSTNODE *node) {
    if(t == NULL) {
        return 0;                       //if the tree is null.
    }

    if(node == 0) {
        return 0;
    }

    if((node->left == 0) && (node->right == 0)) {
        return node;
    }

    return swapToLeafHelper(t, node);
}

//checked and passed
void displayBSTdebug(BST *t,FILE *fp) {
    if(t->sizeBST == 0) {
        return;
    }

    QUEUE *items = newQUEUE(0, 0);

    BSTNODE* temp = t->root;

    enqueue(items, temp);

    while(sizeQUEUE(items) > 0) {
        int currSize = sizeQUEUE(items);

        while(currSize > 0) {
            temp = dequeue(items);

            t->display(temp->value, fp);

            if(currSize != 1) {
                fprintf(fp, " ");
            }

            if (temp->left != 0) {
                enqueue(items, temp->left);
            }
            if (temp->right != 0) {
                enqueue(items, temp->right);
            }
            currSize--;
        }
        fprintf(fp, "\n");
    }
    freeQUEUE(items);
}

//checked and passed
int sizeBST(BST *t) {
    if(t == 0) {
        return 0;
    }

    return t->sizeBST;
}

//checked and passed
static int findMaxHeight(BSTNODE* currNode) {
    if(currNode == 0) {
        return -1;
    }

    int leftHeight = findMaxHeight(currNode->left);
    int rightHeight = findMaxHeight(currNode->right);

    if(rightHeight > leftHeight) {
        return rightHeight + 1;
    }

    else {
        return leftHeight + 1;
    }
}

//checked and passed
static int findMinHeight(BSTNODE* currNode) {
    if(currNode == 0) {
        return -1;
    }

    if((currNode->left == 0) || (currNode->right == 0)) {
        return 0;
    }

    int left = findMinHeight(currNode->left);
    int right = findMinHeight(currNode->right);

    if(left < right) {
        return left + 1;
    }

    else {
        return right + 1;
    }
}

//checked and passed
void statisticsBST(BST *t,FILE *fp) {
    fprintf(fp, "Nodes: %d\n", t->sizeBST);

    int max = findMaxHeight(t->root);
    int min = findMinHeight(t->root);

    fprintf(fp, "Minimum depth: %d\n", min);
    fprintf(fp, "Maximum depth: %d\n", max);

}

//checked and passed
void pruneLeafBST(BST *t,BSTNODE *leaf) {
    if((leaf == 0) || (t == 0)) {
        return;
    }

    if(leaf->parent == 0) {
        t->sizeBST--;
        t->root = 0;
        return;
    }

    else if(leaf->parent->right == leaf) {
        leaf->parent->right = 0;
        leaf->parent = 0;
    }

    else if(leaf->parent->left == leaf) {
        leaf->parent->left = 0;
        leaf->parent = 0;
    }
    t->sizeBST--;
}

//checked and passed
BSTNODE *deleteBST(BST *t,void *value) {
    if(t == 0) {
        return 0;
    }

    BSTNODE* retVal = swapToLeafBST(t, findBST(t, value));
    pruneLeafBST(t, retVal);
    return  retVal;
}

//checked and passed
void freeHelper(BST* tree, BSTNODE* currNode) {
    if(currNode == 0) {
        return;
    }

    else {
        freeHelper(tree, currNode->right);
        tree->free(currNode->value);
        freeHelper(tree, currNode->left);
        //freeBSTNODE(currNode, tree->free);
    	//tree->free(currNode);
		free(currNode);
	}
}	

//checked and passed
void freeBST(BST *t) {
    if(t == 0) {
        return;
    }
    freeHelper(t, t->root);
    free(t);
}
