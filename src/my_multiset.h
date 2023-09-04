#ifndef STLCONTAINERS_MULTISET_H
#define STLCONTAINERS_MULTISET_H

#include <utility>

#include "drevo.h"

namespace STL {
template <class T>
class multiset {
 public:
  class multisetIterator;
  using key_type = std::pair<T, size_t>;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = multisetIterator;
  using size_type = size_t;
  class multisetIterator {
   public:
    explicit multisetIterator(typename Tree<key_type>::iterator other)
        : iter_(other) {
      if (other.node() != nullptr)
        counter = (*other).second;
      else
        counter = 0;
    }

    multisetIterator &operator++() {
      if (counter > 1)
        --counter;
      else {
        ++iter_;
        if (iter_.node() != nullptr)
          counter = (*iter_).second;
        else
          counter = 0;
      }
      return *this;
    }

    reference operator*() const {
      if (!iter_.node()) throw std::logic_error("nullptr");
      return (*iter_).first;
    }

    bool operator==(const iterator &other) const {
      return iter_.node() == other.iter_.node();
    }
    bool operator!=(const iterator &other) const {
      return iter_.node() != other.iter_.node();
    }

   private:
    typename Tree<key_type>::iterator iter_;
    size_type counter;
    friend class multiset;
  };

  multiset() {}

  explicit multiset(std::initializer_list<T> const &values) {
    for (auto val : values) {
      insert(val);
    }
  }

  multiset(const multiset &other) : AVLTree(other.AVLTree) {}

  multiset(multiset &&other) noexcept : AVLTree(std::move(other.AVLTree)) {}

  multiset &operator=(const multiset &other) {
    AVLTree = other.AVLTree;
    return *this;
  }

  multiset &operator=(multiset &&other) noexcept {
    AVLTree = std::move(other.AVLTree);
    return *this;
  }

  ~multiset() {}

  bool empty() const noexcept { return AVLTree.size() ? false : true; }

  size_type size() const noexcept { return AVLTree.size(); }

  void clear() { AVLTree.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool status = false;
    auto target = AVLTree.FindMapTreeNode(std::make_pair(value, size_t{}));
    target ? (++(target->key.second), ++AVLTree.GetSize()) : (status = true);
    if (status) AVLTree.AppendValue(std::make_pair(value, 1));
    return std::make_pair(
        iterator(typename Tree<key_type>::iterator(
            AVLTree.FindMapTreeNode(std::make_pair(value, size_t{})))),
        status);
  }

  void erase(iterator pos) noexcept { AVLTree.erase(pos.iter_); }

  void swap(multiset &other) { std::swap(*this, other); }

  void merge(multiset &other) {
    for (auto val : other) {
      insert(val);
    }
    other.clear();
  }

  size_type count(const value_type &key) const noexcept {
    TreeNode<key_type> *tmp =
        AVLTree.FindMapTreeNode(std::make_pair(key, size_t{}));
    return tmp ? tmp->key.second : 0;
  }

  iterator find(const value_type &value) const {
    return iterator(typename Tree<key_type>::iterator(
        AVLTree.FindMapTreeNode(std::make_pair(value, size_t{}))));
  }

  bool contains(const value_type &value) const noexcept {
    return AVLTree.FindMapTreeNode(std::make_pair(value, size_t{})) ? true
                                                                    : false;
  }

  iterator lower_bound(const value_type &key) const noexcept {
    iterator tmp = begin();
    while (tmp.iter_.node() && *tmp < key) {
      ++tmp;
    }
    return tmp;
  }

  iterator upper_bound(const value_type &key) const noexcept {
    iterator tmp = begin();
    while (tmp.iter_.node() && *tmp <= key) {
      ++tmp;
    }
    return tmp;
  }

  std::pair<iterator, iterator> equal_range(
      const value_type &key) const noexcept {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator begin() const { return iterator(AVLTree.begin()); }

  iterator end() const { return iterator(AVLTree.end()); }

 private:
  Tree<key_type> AVLTree;
};
}  // namespace STL
#endif  // STLCONTAINERS_MULTISET_H
