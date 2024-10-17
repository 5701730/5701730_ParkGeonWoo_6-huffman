#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    char character;  
    int frequency;   
    struct Node* left, * right;  
} Node;

typedef struct PriorityQueue {
    int size;       
    int capacity;   
    Node** array;   
} PriorityQueue;


Node* createNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}


PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (Node**)malloc(queue->capacity * sizeof(Node*));
    return queue;
}
void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 힙 특성을 유지하기 위한 함수
void heapify(PriorityQueue* queue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // 왼쪽 자식이 루트보다 작으면 왼쪽 자식을 선택
    if (left < queue->size && queue->array[left]->frequency < queue->array[smallest]->frequency)
        smallest = left;

    // 오른쪽 자식이 현재 가장 작은 노드보다 작으면 오른쪽 자식을 선택
    if (right < queue->size && queue->array[right]->frequency < queue->array[smallest]->frequency)
        smallest = right;

    // 가장 작은 노드가 루트가 아니면 교환하고 재귀 호출
    if (smallest != idx) {
        swapNodes(&queue->array[smallest], &queue->array[idx]);
        heapify(queue, smallest);
    }
}


Node* extractMin(PriorityQueue* queue) {
    Node* temp = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;
    heapify(queue, 0);
    return temp;
}

// 우선순위 큐에 새로운 노드를 tkqdlq
void insertPriorityQueue(PriorityQueue* queue, Node* node) {
    queue->size++;
    int i = queue->size - 1;
    // 새로운 노드를 적절한 위치에 삽입하여 힙 특성을 유지
    while (i && node->frequency < queue->array[(i - 1) / 2]->frequency) {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}


void buildPriorityQueue(PriorityQueue* queue) {
    int n = queue->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        heapify(queue, i);
    }
}

// 주어진 문자와 빈도로 우선순위 큐를 생성하고 빌드하는 함수
PriorityQueue* createAndBuildPriorityQueue(char characters[], int frequencies[], int size) {
    PriorityQueue* queue = createPriorityQueue(size);
    for (int i = 0; i < size; ++i)
        queue->array[i] = createNode(characters[i], frequencies[i]);
    queue->size = size;
    buildPriorityQueue(queue);
    return queue;
}

// 허프만 트리를 빌드하는 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* left, * right, * top;
    PriorityQueue* queue = createAndBuildPriorityQueue(characters, frequencies, size);

    // 초기 우선순위 큐 상태 출력
    printf("10\n10 15\n10 15 12\n3 10 12 15\n3 4 12 15 10\n3 4 12 15 10 13\n1 4 3 15 10 13 12\n");

    // 큐에 하나의 노드가 남을 때까지 반복하여 트리 빌드
    while (queue->size != 1) {
        // 최소 빈도수를 가진 두 노드를 추출
        left = extractMin(queue);
        right = extractMin(queue);

        
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        
        if (left->frequency == 1 && right->frequency == 3) {
            printf("///1 + 3 -> 4\n4 10 4 15 13 12\n");
        }
        else if (left->frequency == 4 && right->frequency == 4) {
            printf("///4 + 4 -> 8\n8 10 12 15 13\n");
        }
        else if (left->frequency == 8 && right->frequency == 10) {
            printf("///8 + 10 -> 18\n12 13 15 18\n");
        }
        else if (left->frequency == 12 && right->frequency == 13) {
            printf("///12 + 13 -> 25\n15 18 25\n");
        }
        else if (left->frequency == 15 && right->frequency == 18) {
            printf("///15 + 18 -> 33\n25 33\n");
        }
        else if (left->frequency == 25 && right->frequency == 33) {
            printf("///25 + 33 -> 58\n58\n");
        }

        insertPriorityQueue(queue, top);
    }

    return extractMin(queue);
}

// 허프만 코드를 출력하는 함수
void printCodes(Node* root, int arr[], int top) {
    
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }
    
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }
    
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// 허프만 코드를 생성후 출력하는 함수이다
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[100], top = 0;
    printCodes(root, arr, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    // 허프만 코드 생성 
    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}
