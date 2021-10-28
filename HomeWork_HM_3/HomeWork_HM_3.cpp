#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <forward_list>
#include <numeric>

using namespace std;

//firstTask
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
void pushBackAverage(forward_list<T>& list) {
    auto amount = distance(list.begin(), list.end());
    list.insert_after(next(list.before_begin(), amount), accumulate(list.begin(), list.end(), static_cast<T>(0)) / (amount == 0 ? 1 : amount));
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
void printList(const forward_list<T>& list) {
    cout << "List: ";
    for (auto row : list) {
        cout << row << " ";
    }
    cout << endl;
};

void firstTask() {
    forward_list<float> list{ 2, 6, 10, 9 };
    printList(list);
    pushBackAverage(list);
    printList(list);
};
//firstTask
//secondTask
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class squareMatrix {
private:
    vector<vector<T>> _data;
    size_t _size;
public:
    explicit squareMatrix(size_t size) : _size(size) {
        vector<T> empty(size, T{});
        _data.resize(size, empty);
    };

    vector<T>& operator[](int index) {
        return _data[index];
    };

    explicit squareMatrix(const vector<vector<T>>& data) : _size(data.size()) {
        copy(data.begin(), data.end(), back_inserter(_data));
    };

    double getDeterminant() const {
        const double EPS = 1E-6;
        vector<vector<T>> _copy;
        copy(_data.begin(), _data.end(), back_inserter(_copy));
        double det = 1;
        for (size_t i = 0; i < _size; ++i) {
            size_t k = i;
            for (size_t j = i + 1; j < _size; ++j)
                if (abs(_copy[j][i]) > abs(_copy[k][i]))
                    k = j;
            if (abs(_copy[k][i]) < EPS) {
                det = 0;
                break;
            }
            swap(_copy[i], _copy[k]);
            if (i != k)
                det = -det;
            det *= _copy[i][i];
            for (size_t j = i + 1; j < _size; ++j)
                _copy[i][j] /= _copy[i][i];
            for (size_t j = 0; j < _size; ++j)
                if (j != i && abs(_copy[j][i]) > EPS)
                    for (size_t k = i + 1; k < _size; ++k)
                        _copy[j][k] -= _copy[i][k] * _copy[j][i];
        }
        return det;
    };
};

void secondTask() {
    squareMatrix<float> sm(vector<vector<float>>{ vector<float>{1.f, 2.f}, vector<float>{4.f, 5.f} });
    cout << "Determinant: " << sm.getDeterminant() << endl;
};
//secondTask
//thirdTask
template <typename T>
class myVector {
private:
    T* _data;
    const size_t _size;
public:
    explicit myVector(initializer_list<T> value) : _size(value.size()) { 
        _data = new T[value.size()];
        copy(value.begin(), value.end(), _data);
    };

    explicit myVector(const myVector& copy) : _size(copy._size) {
        _data = new T[copy.size()];
        std::copy(copy._data.begin(), copy._data.end(), _data);
    };

    ~myVector() { delete[] _data; };

    class myIterator : public iterator<input_iterator_tag, T> {
    private:
        T* _point;
    public:
        explicit myIterator(T* point) : _point(point) {};
        myIterator(const myIterator& iterator) : _point(iterator._point) {};
        const T& operator*() const { return *_point; };
        myIterator& operator++() {
            ++_point;
            return *this;
        };
        bool operator!=(const myIterator& other) const { return _point != other._point; };
        bool operator==(const myIterator& other) const { return _point == other._point; };
    };

    myIterator begin() { return myIterator(_data); };
    myIterator end() { return myIterator(_data + _size); };
};

void thirdTask() {
    myVector<int> vec{ 1, 2, 3 };
    cout << "My vector: ";
    for (auto el : vec) {
        cout << el << " ";
    }
    cout << endl;
};
//thirdTask
int main()
{
    firstTask();
    secondTask();
    thirdTask();
}
