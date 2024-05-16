#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <stdexcept>
#include <cassert>
using namespace std;

//завдання 1

// Функція для зчитування чисел з клавіатури
std::vector<int> readFromKeyboard() {//Зчитує числа з клавіатури до тих пір, поки не введено некоректне значення.
    std::vector<int> input;//Створює вектор для зберігання введених чисел
    int n;
    std::cout << "Enter numbers (end with non-numeric input): ";
    while (std::cin >> n) {  //Зчитує числа до некоректного введення.
        input.push_back(n); //Додає зчитане число до вектора
    }
    std::cin.clear(); //Очищає прапор помилки
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ігнорує некоректне введення
    return input;
}

// Функція для зчитування чисел з файлу
std::vector<int> readFromFile(const std::string& numbers7) {//Зчитує числа з файлу, ім'я якого передається як параметр
    std::vector<int> input; //<int> - це інстанціювання шаблону для елементів типу int
    std::ifstream file(numbers7);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }
    int n;
    while (file >> n) {
        input.push_back(n);
    }
    return input;
}

// Функція для генерації випадкових чисел
std::vector<int> generateRandomNumbers(int count, int min, int max) {
    std::vector<int> numbers;
    std::srand(std::time(nullptr));
    for (int i = 0; i < count; ++i) {
        numbers.push_back(min + std::rand() % (max - min + 1));
    }
    return numbers;
}

template <typename T>//Це оголошення шаблону функції. Шаблони дозволяють створювати функції, які працюють з різними типами даних, визначеними при виклику
T findMin(const std::vector<T>& array) {
    if (array.empty()) {
        throw std::invalid_argument("Array is empty");
    }
    T minVal = array[0];
    for (const T& val : array) {
        if (val < minVal) {
            minVal = val;
        }
    }
    return minVal;
}

template <> //Це оголошення спеціалізації шаблону. Означає, що наступний блок коду є спеціалізацією для конкретного типу даних
const char* findMin(const std::vector<const char*>& array) { //функція не змінює вміст рядків
    if (array.empty()) {
        throw std::invalid_argument("Array is empty");
    }
    const char* minVal = array[0];
    for (const char* val : array) {
        if (std::strcmp(val, minVal) < 0) {
            minVal = val;
        }
    }
    return minVal;
}

void testInputHandling() {
    try {
        std::vector<int> keyboardInput = readFromKeyboard();
        std::cout << "Keyboard input: ";
        for (int val : keyboardInput) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        std::vector<int> fileInput = readFromFile("numbers7.txt");
        std::cout << "File input: ";
        for (int val : fileInput) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        std::vector<int> randomInput = generateRandomNumbers(10, 1, 100);
        std::cout << "Random input: ";
        for (int val : randomInput) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void testFindMin() {
    std::vector<int> intArray = { 10, 20, 5, 15 };
    std::cout << "Min in intArray: " << findMin(intArray) << std::endl;

    std::vector<double> doubleArray = { 10.5, 20.1, 5.5, 15.3 };
    std::cout << "Min in doubleArray: " << findMin(doubleArray) << std::endl;

    std::vector<const char*> charArray = { "zeta", "alpha", "epsilon", "beta" };
    std::cout << "Min in charArray: " << findMin(charArray) << std::endl;
}

//завдання 2

// Функція порівняння для масивів char* 
// Порівнює два рядки (char*) лексикографічно
int compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

// Функція сортування для масивів char* з використанням qsort
void sort(char* arr[], int n) {
    qsort(arr, n, sizeof(char*), compare);
}

// Функція порівняння для бінарного пошуку (для int)
template <typename T>
int compareForSearch(const T& a, const T& b) {
    if (a == b) {
        return 0;
    }
    else if (a < b) {
        return -1;
    }
    else {
        return 1;
    }
}

// Шаблонна функція бінарного пошуку
// Пошук елемента key в масиві arr з використанням функції порівняння cmp
template <typename T, typename Compare>
int binary_search(const T* arr, int size, const T& target, Compare compare) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int comparison_result = compare(arr[mid], target);
        if (comparison_result == 0) {
            return mid;
        }
        else if (comparison_result < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Element not found
}

template <typename T>
int binarySearch(T arr[], int size, const T& key, int (*cmp)(const T&, const T&)) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        int cmp_result = cmp(arr[middle], key);
        if (cmp_result == 0) {
            return middle; // Знайшли елемент
        }
        else if (cmp_result < 0) {
            left = middle + 1; // Шукаємо в правій половині
        }
        else {
            right = middle - 1; // Шукаємо в лівій половині
        }
    }
    return -1;  // Не знайдено
}

//завдання 3

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

    void allocateMemory() {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    void deallocateMemory() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    // Конструктор за замовчуванням
    Matrix(int r = 0, int c = 0) : rows(r), cols(c) {
        if (rows > 0 && cols > 0) {
            allocateMemory();
        }
        else {
            data = nullptr;
        }
    }

    // Конструктор копіювання
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocateMemory();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Деструктор
    ~Matrix() {
        if (data != nullptr) {
            deallocateMemory();
        }
    }

    // Перевантаження оператора присвоєння
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        // Деалокація існуючої пам'яті
        if (data != nullptr) {
            deallocateMemory();
        }

        rows = other.rows;
        cols = other.cols;
        allocateMemory();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }

        return *this;
    }

    // Перевантаження оператора індексації
    T* operator[](int index) {
        assert(index >= 0 && index < rows);
        return data[index];
    }

    // Перевантаження оператора додавання
    Matrix operator+(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Перевантаження оператора додавання з присвоєнням
    Matrix& operator+=(const Matrix& other) {
        assert(rows == other.rows && cols == other.cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] += other.data[i][j];
            }
        }

        return *this;
    }

    // Метод для вводу значень матриці з клавіатури
    void input() {
        std::cout << "Enter elements of the matrix (" << rows << "x" << cols << "):" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

    // Виведення матриці (для зручності тестування)
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << ' ';
            }
            cout << endl;
        }
    }
};

//завдання 4
template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next; //Вкладена структура Node містить дані та вказівник на наступний вузол. Конструктор вузла ініціалізує дані та вказівник.
        Node(const T& data, Node* next = nullptr)
            : data(data), next(next) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    class Iterator;

    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value, head);
        if (!head) {
            head = tail = newNode;
        }
        else {
            head = newNode;
        }
        ++size;
    }

    bool pop_front() {
        if (!head) return false;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr;
        --size;
        return true;
    }

    bool empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        Iterator& operator++() {//Виклик функтора
            if (current) current = current->next;
            return *this;
        }

        T& operator*() {
            return current->data;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
};

void Task1(){
    cout << "Testing input handling:" << endl;
    testInputHandling();

    cout << "Testing findMin function:" << endl;
    testFindMin();
}

void Task2(){ // Приклад використання
    // Приклад використання
    const int size = 5;
    char* strArr[size] = { const_cast<char*>("pear"), const_cast<char*>("apple"), const_cast<char*>("orange"), const_cast<char*>("banana"), const_cast<char*>("grape") };

    // Сортуємо масив
    sort(strArr, size);

    // Виводимо відсортований масив
    cout << "Sorted array: ";
    for (int i = 0; i < size; ++i) {
        cout << strArr[i] << " ";
    }
    cout << endl;

    int sorted_array[] = { 1, 3, 5, 7, 9, 11 };
    int size1 = sizeof(sorted_array) / sizeof(sorted_array[0]);
    int target = 7;
    int index = binary_search(sorted_array, size1, target, compareForSearch<int>);
    std::cout << "Target Value Index (" << target << "): " << index << std::endl;

    string sorted_strings[] = { "apple", "banana", "cherry", "date" };
    int size2 = sizeof(sorted_strings) / sizeof(sorted_strings[0]);
    string target_str = "cherry";
    int index_str = binary_search(sorted_strings, size2, target_str, compareForSearch<std::string>);
    cout << "Target Value Index (" << target_str << "): " << index_str << endl;


}

void Task3(){
    int rows, cols;

    cout << "Enter number of rows and columns for matrix 1: ";
    cin >> rows >> cols;
    Matrix<int> mat1(rows, cols);
    mat1.input();

    cout << "Enter number of rows and columns for matrix 2: ";
    cin >> rows >> cols;
    Matrix<int> mat2(rows, cols);
    mat2.input();

    Matrix<int> mat3 = mat1 + mat2;

    cout << "Matrix 1:" << endl;
    mat1.print();

    cout << "Matrix 2:" << endl;
    mat2.print();

    cout << "Matrix 3 (Matrix 1 + Matrix 2):" << endl;
    mat3.print();

    mat1 += mat2;
    cout << "Matrix 1 after += Matrix 2:" << endl;
    mat1.print();
}

void Task4(){
    List<int> list;

    // Додавання елементів у кінець списку
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    cout << "List after push_back operations: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Додавання елементів на початок списку
    list.push_front(0);
    list.push_front(-1);

    cout << "List after push_front operations: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Видалення елемента з початку списку
    list.pop_front();

    cout << "List after pop_front operation: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Перевірка на порожність списку
    cout << "Is the list empty? " << (list.empty() ? "Yes" : "No") << endl;

    // Розмір списку
    cout << "Size of the list: " << list.get_size() << endl;

    // Додавання більше елементів для демонстрації
    list.push_back(4);
    list.push_back(5);

    cout << "List after adding more elements: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

}


int main() {
    int choice;

    cout << "Choose task(1, 2, 3, 4):\n";
    cin >> choice;

    switch (choice) {
    case 1:
        Task1();
        break;
    case 2:
        Task2();
        break;
    case 3:
        Task3();
        break;
    case 4:
        Task4();
        break;
    default:
        cout << "Wrong choice!\n";
        break;
    }
   
    return 0;
}



