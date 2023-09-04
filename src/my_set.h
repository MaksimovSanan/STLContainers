#ifndef STLCONTAINERS_SET_H
#define STLCONTAINERS_SET_H

#include "drevo.h"

namespace STL {

template <class T>
class set {
 public:
  using key_type = T;
  using value_type = key_type;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename Tree<T>::iterator;
  using const_iterator = typename Tree<T>::const_iterator;
  using size_type = size_t;

  set() {}

  explicit set(std::initializer_list<T> const &values) {
    for (auto val : values) {
      insert(val);
    }
  }

  set(const set &other) : AVLTree(other.AVLTree) {}

  set(set &&other) : AVLTree(std::move(other.AVLTree)) {}

  set<T> &operator=(const set &other) {
    AVLTree = other.AVLTree;
    return *this;
  }

  set<T> &operator=(set &&other) {
    AVLTree = std::move(other.AVLTree);
    return *this;
  }

  ~set() {}

  bool empty() const { return AVLTree.size() ? false : true; }

  size_type size() const { return AVLTree.size(); }

  void clear() { AVLTree.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool status = (AVLTree.FindTreeNode(value) == nullptr) ? true : false;
    if (status) AVLTree.AppendValue(value);
    iterator t = iterator(AVLTree.FindTreeNode(value));
    return std::make_pair(t, status);
  }

  void erase(iterator pos) noexcept { AVLTree.erase(pos); }

  void swap(set &other) { std::swap(*this, other); }

  void merge(set &other) {
    for (auto val : other) {
      insert(val);
    }
    other.clear();
  }

  iterator find(const key_type &key) const noexcept {
    return iterator(AVLTree.FindTreeNode(key));
  }

  bool contains(const key_type &key) const noexcept {
    return AVLTree.FindTreeNode(key) ? true : false;
  }

  iterator begin() const noexcept { return AVLTree.begin(); }

  iterator end() const noexcept { return AVLTree.end(); }

 private:
  Tree<T> AVLTree;
};
}  // namespace STL
#endif  // STLCONTAINERS_SET_H
