
#include <iostream> 
#include <cstdlib> 
using namespace std; 
  
#define MAX_TREE_HT 100 					// menghitung panjangnya huffman-tree
  
// sebuah node untuk huffmen-tree
struct MinHeapNode { 
  
    char data; 								// bagian inputan karakter 
  
    
    unsigned frek; 							// frekuensi karakter
  
    
    struct MinHeapNode *kiri, *kanan; 		// bagian kiri dan kanan dari simpul
}; 
  
 
// semua anggota/koleksi di huffman-tree 
struct MinHeap { 
  
    
    unsigned size; 							// ukuran koleksi 
  
    
    unsigned kapasitas; 						// Kapasitas
  
    
    struct MinHeapNode** array; 
}; 
  

struct MinHeapNode* newNode(char data, unsigned frek) 
{ 
    struct MinHeapNode* temp 
        = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 
  
    temp->kiri = temp->kanan = NULL; 
    temp->data = data; 
    temp->frek = frek; 
  
    return temp; 
} 
  

struct MinHeap* createMinHeap(unsigned kapasitas) 
  
{ 
  
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  
    // current size is 0 
    minHeap->size = 0; 
  
    minHeap->kapasitas = kapasitas; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
kapasitas * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  

// penukaran
void swapMinHeapNode(struct MinHeapNode** a, 
                    struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  

void minHeapify(struct MinHeap* minHeap, int idx) 
  
{ 
  
    int smallest = idx; 
    int kiri = 2 * idx + 1; 
    int kanan = 2 * idx + 2; 
  
    if (kiri < minHeap->size && minHeap->array[kiri]-> 
frek < minHeap->array[smallest]->frek) 
        smallest = kiri; 
  
    if (kanan < minHeap->size && minHeap->array[kanan]-> 
frek < minHeap->array[smallest]->frek) 
        smallest = kanan; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
  
// Pengecekan
// apakah tumpukan bernilai 1 atau tidak
int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  
// nilai minimal pada tumpukan node
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] 
        = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  
// pembuatan node baru untuk koleksi atau tumpukan
void insertMinHeap(struct MinHeap* minHeap, 
                struct MinHeapNode* minHeapNode) 
  
{ 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->frek < minHeap->array[(i - 1) / 2]->frek) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
  
// pembuatan koleksi
void buildMinHeap(struct MinHeap* minHeap) 
  
{ 
  
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
  
// pencetakan array 
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        cout<< arr[i]; 
  
    cout<<"\n"; 
} 
  
int isLeaf(struct MinHeapNode* akar) 
  
{ 
  
    return !(akar->kiri) && !(akar->kanan); 
} 
  

struct MinHeap* createAndBuildMinHeap(char data[], int frek[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], frek[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
// The main function that builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(char data[], int frek[], int size) 
  
{ 
    struct MinHeapNode *kiri, *kanan, *atas; 
  
    // membuat min heap baru lagi
    struct MinHeap* minHeap = createAndBuildMinHeap(data, frek, size); 
  
    
    while (!isSizeOne(minHeap)) { 
  
        
        kiri = extractMin(minHeap); 
        kanan = extractMin(minHeap); 
  
         
        atas = newNode('$', kiri->frek + kanan->frek); 
  
        atas->kiri = kiri; 
        atas->kanan = kanan; 
  
        insertMinHeap(minHeap, atas); 
    } 
  
    // huffman-tree telah terbentuk
    return extractMin(minHeap); 
} 
  
// Pencetakan code huffman-tree atau dekripsi
void printCodes(struct MinHeapNode* akar, int arr[], int atas) 
  
{ 
  
    // 0 untuk bagian kiri dan rekursif
    if (akar->kiri) { 
  
        arr[atas] = 0; 
        printCodes(akar->kiri, arr, atas + 1); 
    } 
  
    // 1 untuk bagian kanan dan rekursif 
    if (akar->kanan) { 
  
        arr[atas] = 1; 
        printCodes(akar->kanan, arr, atas + 1); 
    } 
  
    // IJIka simpul maka ia mengantuk salah satu inputan dari array
    if (isLeaf(akar)) { 
  
        cout<< akar->data <<": "; 
        printArr(arr, atas); 
    } 
} 
  

void HuffmanCodes(char data[], int frek[], int size) 
  
{ 
    // Construct Huffman Tree 
    struct MinHeapNode* akar 
        = buildHuffmanTree(data, frek, size); 
  
    // pencetakan kode huffman
    int arr[MAX_TREE_HT], atas = 0; 
  
    printCodes(akar, arr, atas); 
} 
  
//kendali program
int main() 
{ 
  
    char arr[] = { 'u', 'a', 'h', '_', 't', 'b', 'n' }; 
    int frek[] = { 4, 7, 1, 6, 2, 1,1 }; 
  
    int size = sizeof(arr) / sizeof(arr[0]); 
  
    HuffmanCodes(arr, frek, size); 
  
    return 0; 
}
