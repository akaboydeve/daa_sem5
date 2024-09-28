#include <stdio.h>
#include <stdlib.h>

// Structure to represent a symbol (alphabet and frequency)
typedef struct
{
    char alphabet;
    int frequency;
} SYMBOL;

// Huffman Tree Node structure
struct MinHeapNode
{
    SYMBOL symbol;
    struct MinHeapNode *left, *right;
};

// Min Heap structure
struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

// Function to create a new Huffman Tree node
struct MinHeapNode *createNode(char alphabet, int frequency)
{
    struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    temp->symbol.alphabet = alphabet;
    temp->symbol.frequency = frequency;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to create a MinHeap of given capacity
struct MinHeap *createMinHeap(unsigned capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// Swap function for heap nodes
void swapNodes(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Min-Heapify function
void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
        smallest = right;

    if (smallest != idx)
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if the size of the heap is 1
int isSizeOne(struct MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

// Extract the minimum frequency node from the heap
struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    struct MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a new node into MinHeap
void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->symbol.frequency < minHeap->array[(i - 1) / 2]->symbol.frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Build the min heap
void buildMinHeap(struct MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Check if the node is a leaf
int isLeaf(struct MinHeapNode *root)
{
    return !(root->left) && !(root->right);
}

// Create and build a min heap with symbols
struct MinHeap *createAndBuildMinHeap(SYMBOL symbols[], int size)
{
    struct MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(symbols[i].alphabet, symbols[i].frequency);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Build the Huffman Tree
struct MinHeapNode *buildHuffmanTree(SYMBOL symbols[], int size)
{
    struct MinHeapNode *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(symbols, size);

    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->symbol.frequency + right->symbol.frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// In-order traversal of the Huffman Tree
void inorderTraversal(struct MinHeapNode *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        if (root->symbol.alphabet != '$')
            printf("%c ", root->symbol.alphabet);
        inorderTraversal(root->right);
    }
}

// Main function to drive the program
int main()
{
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    SYMBOL symbols[n];
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &symbols[i].alphabet); // Notice the space before %c
    }

    printf("Enter their frequencies: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &symbols[i].frequency);
    }

    struct MinHeapNode *root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
