#include <iostream>
using namespace std;
//
//Проведите эксперимент, подтверждающий или
//опровергающий утверждение о том, что в среднем
//быстрая сортировка эффективнее пирамидальной.
//

void heapify(int arr[], int n, int i) {
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2
    // Если левый дочерний элемент больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;
    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;
    // Если самый большой элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);
    // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n) {
    // Построение кучи (перегруппируем массив)
    for (int i = n/2-1; i >= 0; i--)
        heapify(arr, n, i);
    // Один за другим извлекаем элементы из кучи
    for (int i = n-1; i >= 0; i--) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);
        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

int main() {
    int n = 0;
    cout << "Enter n:";
    cin >> n;
    int arr[n];
    cout << "Please, enter:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    heapSort(arr, n);
    cout << "Sorted array is \n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
    return 0;
}