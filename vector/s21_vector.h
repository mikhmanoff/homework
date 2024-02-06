#ifndef S21VECTOR_H
#define S21VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

/*
HEADER FILE
*/
namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  reference operator=(vector &&v);

  //  ElementAccess
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data();

  // Iterators
  iterator begin();
  iterator end();

  //  Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type new_capacity);
  size_type capacity();
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_t size_;
  size_t capacity_;
  value_type *arr_;
};

template <class value_type>
vector<value_type>::vector() : size_(0U), capacity_(0U), arr_(nullptr) {}

template <class value_type>
vector<value_type>::vector(size_type n) : size_(n), capacity_(n) {
  if (n > 0) arr_ = new value_type[n];
}

template <class value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()),
      capacity_(items.size()),
      arr_(new value_type[items.size()]) {
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i++] = *it;
  }
}

template <class value_type>
vector<value_type>::vector(const vector &v)
    : size_(v.size_),
      capacity_(v.capacity_),
      arr_(new value_type[v.capacity_]) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }
};

template <class value_type>
vector<value_type>::vector(vector &&v)
    : size_(v.size_), capacity_(v.capacity_), arr_(v.arr_) {
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
  arr_ = std::exchange(v.arr_, nullptr);
}

template <class value_type>
typename vector<value_type>::reference vector<value_type>::operator=(
    vector &&v) {
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
  arr_ = std::exchange(v.arr_, nullptr);
  return *this;
}

template <class value_type>
vector<value_type>::~vector() {
  delete[] arr_;
  arr_ = nullptr;
}

template <class value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos > (*this).size()) throw std::out_of_range("vector.at: out of range");
  return arr_[pos];
}

template <class value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return (*this).at(pos);
}

template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  if ((*this).size() == 0) throw std::out_of_range("front: out_of_range");
  return (*this).at(0);
}

template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  if ((*this).size() == 0) throw std::out_of_range("back: out_of_range");
  return this->at(size_ - 1);
}

template <class value_type>
value_type *vector<value_type>::data() {
  return arr_;
}

//  -------------------------------------------

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return arr_;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return arr_ + size_;
}

//  -------------------------------------------
template <class value_type>
bool vector<value_type>::empty() {
  return size_ == 0;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return size_;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <class value_type>
void vector<value_type>::reserve(size_type new_capacity) {
  if (new_capacity > max_size())
    throw std::out_of_range("reserve: out of range");
  if (new_capacity < capacity_) size_ = new_capacity;

  value_type *buf = new value_type[new_capacity];
  std::copy(arr_, arr_ + (capacity_ < new_capacity ? capacity_ : new_capacity),
            buf);
  delete[] arr_;
  arr_ = buf;
  capacity_ = new_capacity;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
  return capacity_;
}

template <class value_type>
void vector<value_type>::shrink_to_fit() {
  capacity_ = size_;
}

template <class value_type>
void vector<value_type>::clear() {
  size_ = 0;
  delete[] arr_;
  arr_ = new value_type[capacity_];
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos > end() || pos < begin())
    throw std::out_of_range("insert: out of range");
  int realpos = (pos - begin());
  reserve(++size_);

  for (iterator it = end() - 1; it != begin() + realpos; --it) {
    *it = *(it - 1);
  }
  *(begin() + realpos) = value;
  return pos;
}

template <class value_type>
void vector<value_type>::erase(iterator pos) {
  size_type check = pos - arr_;
  if (check > size_) throw std::out_of_range("erase: out of range");

  for (iterator it = pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --size_;
}

template <class value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ + 1 > capacity_) this->reserve(this->size() + 1);
  ++size_;
  arr_[size_ - 1] = value;
}

template <class value_type>
void vector<value_type>::pop_back() {
  --size_;
}

template <class value_type>
void vector<value_type>::swap(vector &other) {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->arr_, other.arr_);
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  int realpos = (pos - begin()) - 1;
  return ((++realpos, insert(begin() + realpos, std::forward<Args>(args))),
          ...);
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

}  // namespace s21
#endif