#ifndef STLCONTAINERS_MAP_H
#define STLCONTAINERS_MAP_H

#include "drevo.h"

namespace STL {

template <class T, class K>
class map {
 public:
  using key_type = T;
  using value_type = K;
  using tree_type = std::pair<T, K>;
  using reference = tree_type &;
  using const_reference = const tree_type &;
  using iterator = typename Tree<tree_type>::iterator;
  using const_iterator = typename Tree<tree_type>::const_iterator;
  using size_type = size_t;

  map() {}

  explicit map(std::initializer_list<tree_type> const &values) {
    for (auto val : values) {
      insert(val);
    }
  }

  map(const map &other) : AVLTree(other.AVLTree) {}

  map(map &&other) : AVLTree(std::move(other.AVLTree)) {}

  map &operator=(const map &other) {
    AVLTree = other.AVLTree;
    return *this;
  }

  map &operator=(map &&other) {
    AVLTree = std::move(other.AVLTree);
    return *this;
  }

  ~map() {}

  K &at(const T &key) const {
    TreeNode<tree_type> *t = AVLTree.FindMapTreeNode(std::make_pair(key, 0));
    if (!(t)) throw std::out_of_range("Incorrect index");
    return t->key.second;
  }
  K &operator[](const T &key) {
    bool status = contains(key);
    if (!status) insert(key, K{});
    return at(key);
  }

  iterator begin() const noexcept { return AVLTree.begin(); }

  iterator end() const noexcept { return AVLTree.end(); }

  bool empty() const noexcept { return AVLTree.size() ? false : true; }

  size_type size() const noexcept { return AVLTree.size(); }

  void clear() { AVLTree.clear(); }

  std::pair<iterator, bool> insert(const tree_type &value) {
    bool status = contains(value.first);
    if (!status) AVLTree.AppendValue(value);
    iterator t = iterator(AVLTree.FindMapTreeNode(value));
    return std::make_pair(t, !status);
  }

  std::pair<iterator, bool> insert(const T &key, const K &obj) {
    tree_type value = std::make_pair(key, obj);
    return insert(value);
  }

  std::pair<iterator, bool> insert_or_assign(const T &key, const K &obj) {
    bool status = contains(key);
    if (status)
      at(key) = obj;
    else {
      tree_type value = std::make_pair(key, obj);
      insert(value);
    }
    iterator t = iterator(AVLTree.FindMapTreeNode(std::make_pair(key, K{})));
    return std::make_pair(t, !status);
  }

  void erase(iterator pos) noexcept { AVLTree.erase(pos); }
  void swap(map &other) { std::swap(*this, other); }

  void merge(map &other) {
    for (auto val : other) {
      insert(val);
    }
    other.clear();
  }
  bool contains(const T &key) const noexcept {
    return AVLTree.FindMapTreeNode(std::make_pair(key, K{})) ? true : false;
  }

 private:
  Tree<tree_type> AVLTree;
};
}  // namespace STL

#endif  // #define STLCONTAINERS_MAP_H

