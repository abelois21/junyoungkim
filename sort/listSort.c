#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static int greator(int l, int r) {
    if(l > r) return 1;
    else return 0;
}

static int less(int l, int r) {
    if(l < r) return 1;
    else return 0;
}

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct PRIORITY_QUEUE {
    int* buf;
    int size;
    int capacity;
    int (*comp)(int, int);  
} PRIORITY_QUEUE;

// quick sort for list
void qSortList(struct ListNode** head, int(*comp)(int, int));
void qsPartition(struct ListNode* head, struct ListNode* tail, struct ListNode** nHead, struct ListNode** nTail,
	int(*comp)(int, int));
// merge sort for list
struct ListNode* mSortList(struct ListNode* head, int(*comp)(int, int));
// heap sort for list
struct ListNode* hSortList(struct ListNode* head, int(*comp)(int, int)); 
// priority queue for heap sort
void pq_initialize(PRIORITY_QUEUE* pq, int (*comp)(int, int));
void pq_push(PRIORITY_QUEUE* pq, int i);
int pq_pop(PRIORITY_QUEUE* pq);
// check sorting is appropriate
int checkSorting(struct ListNode* head, int(*comp)(int, int));

int main(int argc, char** argv) {
    double t1, t2;
    clock_t start;

    start = time();
    qSortList(head, ASCENDING);
    t1 = time() - start;
    if(!checkSorting(head, ASCENDING)) printf("error sorting is not working\n");
    start = time();
    qSortList(head, DESCENDING);
    t2 = time() - start;
    if(!checkSorting(head, DESCENDING)) printf("error sorting is not working\n");
    printf("quick sort - ascending consuming time: %lf, descending consuming time: %lf\n", t1, t2);

    start = time();
    mSortList(head, ASCENDING);
    t1 = time() - start;
    if(!checkSorting(head, ASCENDING)) printf("error sorting is not working\n");
    start = time();
    mSortList(head, DESCENDING);
    t2 = time() - start;
    if(!checkSorting(head, DESCENDING)) printf("error sorting is not working\n");
    printf("merge sort - ascending consuming time: %lf, descending consuming time: %lf\n", t1, t2);

    start = time();
    hSortList(head, ASCENDING);
    t1 = time() - start;
    if(!checkSorting(head, ASCENDING)) printf("error sorting is not working\n");
    start = time();
    hSortList(head, DESCENDING);
    t2 = time() - start;
    if(!checkSorting(head, DESCENDING)) printf("error sorting is not working\n");
    printf("heap sort - ascending consuming time: %lf, descending consuming time: %lf\n", t1, t2);

    return 0;
}


// quick sort for list
void qSortList(struct ListNode** head, int(*comp)(int, int)){
    struct ListNode *temp, **tail;
    temp = *head;
    tail = &temp;

    while((*tail)->next) *tail = (*tail)->next;

    qSortPart(head, tail, comp);
}

// sort from leftmost to rightmost-1 
void qsPartition(struct ListNode** head, struct ListNode** tail, int(*comp)(int, int)) {
    struct ListNode *cur, *pivot = tail, *temp;

    while(!(comp((*head)->val, pivot->val))) {
	temp = *head;
	*head = (*head)->next;
	temp->next = pivot->next;
	pivot->next = temp;

	if(*head == pivot) return;	// all of the elements are assigned to rightside of pivot
    }

    cur = (*head)->next;
    while(!(comp(cur->val, pivot->val))) {
	temp = cur;
	cur = cur->next;
	temp->next = pivot->next;
	pivot->next = temp;

	if(!cur) break;
    }

    while(temp->next) temp = temp->next;
    *tail = temp;

}

void qSortPart(struct ListNode** head, struct ListNode** tail, int(*comp)(int, int)) {
    struct ListNode *temp, *pivot = *tail;
    qsPartition(head, tail);				// tail is pivot

    if(!(*head == pivot || (*head)->next == pivot)) {	// List has only one element
	temp = (*head)->next;
	while(temp->next != pivot) {
	    temp = temp->next;
	}

	temp->next = NULL;
    	qSortPart(head, &temp, comp);
    	temp->next = pivot;
    }

    if(!(pivot == *tail || pivot->next == *tail)) {
        temp = pivot->next;

    	pivot->next = NULL;
    	qSortPart(&temp, tail, comp);
        pivot->next = temp;

    }
}


// merge sort for list
struct ListNode* mSortList(struct ListNode* head, int(*comp)(int, int)){
    ;
}

// heap sort for list
struct ListNode* hSortList(struct ListNode* head, int(*comp)(int, int)){ 
    PRIORITY_QUEUE pq;
    pq_initialize(&pq, comp);
}

int checkSorting(struct ListNode* head, int(*comp)(int, int)) {
    int prev = head->val;

    while(!head) {
	if(comp(prev - head->val) < 0) return 0;
	prev = head->val;
	head = head->next;
    }
    return 1;
}

void pq_initialize(PRIORITY_QUEUE* pq, int (*comp)(int, int)) {
    pq->size = 0;
    pq->capacity = 1000;
    if((buf = (int*)malloc(sizeof(int)*pq->capacity)) == (void*)0) exit(1);
    memset(buf, 0, sizeof(int)*pq->capacity);
    pq->comp = comp;
}

void pq_push(PRIORITY_QUEUE* pq, int i) {
    int idx = ++pq->size;
    int* buf = pq->buf;
    
    if(pq->size == pq->capacity) {
        pq->capacity *= 2;
        if((pq->buf = realloc(pq->buf, pq->capacity * sizeof(int))) == (void*)0) exit(1);
    }
    
    pq->buf[idx] = i;
    
    while(idx > 1) {
        if(pq->comp(buf[idx], buf[idx/2]) < 0) break;
        swap(buf+idx, buf+idx/2);
        idx /= 2;
    }
}

int pq_pop(PRIORITY_QUEUE* pq) {
    int t_idx, idx = 1, rst = pq->buf[1];
    int* buf = pq->buf;
    swap(pq->buf+1, pq->buf+pq->size);
    pq->size--;
    
    while(idx <= size/2) {
        if(idx*2 == size) {     // only has left node
            t_idx = idx*2;
        } else {
            if(comp(buf[idx*2], buf[idx*2+1])) {
                t_idx = idx*2;
            } else {
                t_idx = idx*2+1;
            }
        }
        
        if(comp(buf[t_idx], buf[idx])) {
            swap(buf+t_idx, buf+idx);
            idx = t_idx;
        } else break;
    }
    
    return rst;
}

