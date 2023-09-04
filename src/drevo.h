#ifndef STLCONTAINERS_DREVO_H
#define STLCONTAINERS_DREVO_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>

namespace STL {

template <class T>
class Tree;

template <class T>
struct TreeNode {
  T key;
  unsigned int height;
  TreeNode<T> *parent;
  TreeNode<T> *left;
  TreeNode<T> *right;
  friend class Tree<T>;
};

template <class T>
class Tree {
 public:
  class iterator {
   public:
    explicit iterator(TreeNode<T> *current) : current_(current) {}

    iterator &operator++() {
      if (!current_) throw std::out_of_range("Out of range");
      if (current_->right) {
        current_ = findmin(current_->right);
      } else {
        if (current_->parent) {
          TreeNode<T> *tmp = current_->parent;
          if (tmp->left == current_) {
            current_ = tmp;
          } else {
            do {
              current_ = tmp;
              tmp = current_->parent;
            } while (tmp && tmp->right == current_);
            if (tmp)
              current_ = tmp;
            else
              current_ = nullptr;
          }
        } else
          current_ = nullptr;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    iterator &operator--() {
      if (!current_) throw std::out_of_range("Out of range");
      if (current_->left) {
        current_ = findmax(current_->left);
      }

      else {
        if (current_->parent) {
          TreeNode<T> *tmp = current_->parent;
          if (tmp->right == current_) {
            current_ = tmp;
          } else {
            do {
              current_ = tmp;
              tmp = current_->parent;
            } while (tmp && tmp->left == current_);
            if (tmp)
              current_ = tmp;
            else
              current_ = nullptr;
          }
        } else
          current_ = nullptr;
      }
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }

    TreeNode<T> *node() const { return current_; }

    T &operator*() const {
      if (!current_) throw std::logic_error("nullptr");
      return current_->key;
    }

    TreeNode<T> *findmin(TreeNode<T> *root) const {
      return root->left ? findmin(root->left) : root;
    }

    TreeNode<T> *findmax(TreeNode<T> *root) const {
      return root->right ? findmax(root->right) : root;
    }

    bool operator==(const iterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const iterator &other) const {
      return current_ != other.current_;
    }

   private:
    TreeNode<T> *current_;
    friend Tree<T>;
  };

  class const_iterator {
   public:
    explicit const_iterator(TreeNode<T> *current) : current_(current) {}

    const_iterator &operator++() {
      if (!current_) throw std::out_of_range("Out of range");
      if (current_->right) {
        current_ = findmin(current_->right);
      }

      else {
        if (current_->parent) {
          TreeNode<T> *tmp = current_->parent;
          if (tmp->left == current_) {
            current_ = tmp;
          } else {
            do {
              current_ = tmp;
              tmp = current_->parent;
            } while (tmp && tmp->right == current_);
            if (tmp)
              current_ = tmp;
            else
              current_ = nullptr;
          }
        } else
          current_ = nullptr;
      }
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    const_iterator &operator--() {
      if (!current_) throw std::out_of_range("Out of range");
      if (current_->left) {
        current_ = findmax(current_->left);
      }

      else {
        if (current_->parent) {
          TreeNode<T> *tmp = current_->parent;
          if (tmp->right == current_) {
            current_ = tmp;
          } else {
            do {
              current_ = tmp;
              tmp = current_->parent;
            } while (tmp && tmp->left == current_);
            if (tmp)
              current_ = tmp;
            else
              current_ = nullptr;
          }
        } else
          current_ = nullptr;
      }
      return *this;
    }

    operator iterator() const { return iterator(current_); }

    TreeNode<T> *node() const { return current_; }

    const T &operator*() const {
      if (!current_) throw std::logic_error("nullptr");
      return current_->key;
    }

    TreeNode<T> *findmin(TreeNode<T> *root) const {
      return root->left ? findmin(root->left) : root;
    }

    TreeNode<T> *findmax(TreeNode<T> *root) const {
      return root->right ? findmax(root->right) : root;
    }

    bool operator==(const const_iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const const_iterator &other) const {
      return current_ != other.current_;
    }

   private:
    TreeNode<T> *current_;
    friend Tree<T>;
  };

  Tree() noexcept : size_(0), root_(nullptr) {}

  Tree(const Tree<T> &other) : size_(0), root_(nullptr) {
    for (auto val : other) {
      AppendValue(val);
    }
  }

  Tree(Tree<T> &&other) noexcept
      : size_(std::move(other.size_)), root_(std::move(other.root_)) {
    other.size_ = 0;
    other.root_ = nullptr;
  }

  Tree<T> &operator=(const Tree<T> &other) {
    clear();
    for (auto val : other) {
      AppendValue(val);
    }
    return *this;
  }

  Tree<T> &operator=(Tree<T> &&other) noexcept {
    root_ = std::move(other.root_);
    size_ = std::move(other.size_);
    other.root_ = nullptr;
    other.size_ = 0;
    return *this;
  }

  ~Tree() {
    if (root_ != nullptr) {
      ClearTreeNode(*root_);  // CHANGE IT, NO METHODS IN DESTRUCTORS
    }
    size_ = 0;
  }

  void AppendValue(const T &value) {
    root_ = insert(root_, value);
    size_++;
  }

  void erase(iterator pos) noexcept {
    root_ = remove(root_, pos.node()->key);
    size_--;
  }

  void clear() noexcept {
    if (root_) ClearTreeNode(*root_);
    root_ = nullptr;
    size_ = 0;
  }

  TreeNode<T> *FindTreeNode(const T &val) const {
    iterator tmp = this->begin();
    while (tmp.current_ != nullptr && tmp.current_->key != val) {
      ++tmp;
    }
    return tmp.current_;
  }

  TreeNode<T> *FindMapTreeNode(const T &val) const {
    iterator tmp = begin();
    while (tmp.current_ != nullptr && tmp.current_->key.first != val.first) {
      ++tmp;
    }
    return tmp.current_;
  }

  iterator begin() noexcept {
    return root_ ? iterator(findmin(root_)) : iterator(nullptr);
  }

  iterator end() noexcept {  // FIXFIXFIXFIX
    return iterator(nullptr);
  }

  const_iterator begin() const noexcept {
    return root_ ? const_iterator(findmin(root_)) : const_iterator(nullptr);
  }

  const_iterator end() const noexcept {  // FIXFIXFIXFIX
    return const_iterator(nullptr);
  }

  size_t size() const noexcept { return size_; }

  size_t &GetSize() noexcept { return size_; }

 protected:
  TreeNode<T> *insert(TreeNode<T> *root, const T &value) {
    if (!root) {
      TreeNode<T> *another_one = new TreeNode<T>;
      another_one->key = value;
      another_one->height = 1;
      another_one->left = nullptr;
      another_one->right = nullptr;
      another_one->parent = nullptr;
      return another_one;
    }
    if (value < root->key) {
      root->left = insert(root->left, value);
      root->left->parent = root;
    } else {
      root->right = insert(root->right, value);
      root->right->parent = root;
    }
    return balance(root);
  }

  TreeNode<T> *remove(TreeNode<T> *root, T value) noexcept {
    if (!root) return 0;
    if (value < root->key) {
      root->left = remove(root->left, value);
      if (root->left) root->left->parent = root;
    } else if (value > root->key) {
      root->right = remove(root->right, value);
      if (root->right) {
        root->right->parent = root;
      }
    } else  //  k == p->key
    {
      TreeNode<T> *l = root->left;
      TreeNode<T> *r = root->right;
      delete root;
      if (!r) {
        if (l) l->parent = nullptr;
        return l;
      }
      TreeNode<T> *min = findmin(r);
      min->parent = nullptr;
      min->right = removemin(r);
      if (min->right) min->right->parent = min;
      min->left = l;
      if (min->left) min->left->parent = min;
      return balance(min);
    }
    return balance(root);
  }

  TreeNode<T> *rotateright(
      TreeNode<T> *root) noexcept {  // правый поворот вокруг root
    TreeNode<T> *tmp = root->left;
    root->left = tmp->right;
    tmp->parent = root->parent;
    if (tmp->right) tmp->right->parent = root;
    tmp->right = root;
    root->parent = tmp;
    fixheight(root);
    fixheight(tmp);
    return tmp;
  }

  TreeNode<T> *rotateleft(
      TreeNode<T> *root) noexcept {  // левый поворот вокруг root
    TreeNode<T> *tmp = root->right;
    root->right = tmp->left;
    tmp->parent = root->parent;
    if (tmp->left) tmp->left->parent = root;
    tmp->left = root;
    root->parent = tmp;
    fixheight(root);
    fixheight(tmp);
    return tmp;
  }

  TreeNode<T> *balance(TreeNode<T> *root) noexcept {  // балансировка узла root
    fixheight(root);
    if (bfactor(root) > 1) {
      if (bfactor(root->right) < 0) root->right = rotateright(root->right);
      return rotateleft(root);
    }
    if (bfactor(root) < -1) {
      if (bfactor(root->left) > 0) root->left = rotateleft(root->left);
      TreeNode<T> *tmp = rotateright(root);
      return tmp;
    }
    return root;  // балансировка не нужна
  }

  unsigned int height(TreeNode<T> *root) const noexcept {
    return root ? root->height : 0;
  }

  int bfactor(TreeNode<T> *root) const noexcept {
    return height(root->right) - height(root->left);
  }

  void fixheight(TreeNode<T> *root) const noexcept {
    unsigned int hl = height(root->left);
    unsigned int hr = height(root->right);
    root->height = (hl > hr ? hl : hr) + 1;
  }

  TreeNode<T> *findmin(TreeNode<T> *root) const
      noexcept {  // поиск узла с минимальным ключом в дереве с корнем root
    return root->left ? findmin(root->left) : root;
  }

  TreeNode<T> *findmax(TreeNode<T> *root) const
      noexcept {  // поиск узла с максимальным ключом в дереве с корнем root
    return root->right ? findmax(root->right) : root;
  }

  TreeNode<T> *removemin(
      TreeNode<T> *root) noexcept {  // удаление узла с минимальным ключом из
                                     // дерева с корнем root
    if (root->left == 0) return root->right;
    root->left = removemin(root->left);
    return balance(root);
  }

  void ClearTreeNode(TreeNode<T> &root) noexcept {
    if (root.left != nullptr) {
      if (root.left->left == nullptr && root.left->right == nullptr)
        delete root.left;
      else
        ClearTreeNode(*(root.left));
    }

    if (root.right != nullptr) {
      if (root.right->left == nullptr && root.right->right == nullptr)
        delete root.right;
      else
        ClearTreeNode(*(root.right));
    }

    delete &root;
  }

 private:
  size_t size_;
  TreeNode<T> *root_;
};
}  // namespace STL

#endif  // STLCONTAINERS_SET_H
