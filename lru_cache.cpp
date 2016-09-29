//
// Created by Kirill Antonov on 27.09.2016.
//

#include <iostream>
#include "lru_cache.h"


lru_cache::iterator::iterator(node *x) : my_el(x) { }

lru_cache::iterator::~iterator() {
    (*my_el).~node();
}

lru_cache::value_type lru_cache::iterator::operator*() const {
    return value_type(my_el->key, *my_el->mapped);
}

lru_cache::iterator lru_cache::iterator::operator++(int) {
    iterator tmp = *this;
    *this = iterator(lru_cache::bst_tree::get_next(this->my_el));
    return lru_cache::iterator(tmp);
}

lru_cache::iterator &lru_cache::iterator::operator++() {
    *this = iterator(lru_cache::bst_tree::get_next(this->my_el));
    return *this;
}

lru_cache::iterator &lru_cache::iterator::operator--() {
    *this = iterator(lru_cache::bst_tree::get_prev(this->my_el));
    return *this;
}

lru_cache::iterator lru_cache::iterator::operator--(int) {
    iterator tmp = *this;
    *this = iterator(lru_cache::bst_tree::get_prev(this->my_el));
    return lru_cache::iterator(tmp);
}

lru_cache::bst_tree::bst_tree() : fake_node(0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) { }

lru_cache::node *lru_cache::bst_tree::find(key_type x) {
    return search(fake_node.left, x);
}

lru_cache::node *lru_cache::bst_tree::search(node *x, key_type k) {
    if (x == nullptr || k == x->key) return x;
    if (k < x->key) {
        return search(x->left, k);
    } else {
        return search(x->right, k);
    }
}

lru_cache::node *lru_cache::bst_tree::insert(node *x) {
    s++;
    return _insert(fake_node.left, x);
}

lru_cache::node *lru_cache::bst_tree::_insert(node *x, node *z) {
    if (x == nullptr) {
        z->parent = &fake_node;
        fake_node.left = z;
        return z;
    }
    while (x != nullptr) {
        if (z->key > x->key) {
            if (x->right != nullptr) {
                x = x->right;
            } else {
                z->parent = x;
                x->right = z;
                break;
            }
        } else if (z->key < x->key) {
            if (x->left != nullptr) {
                x = x->left;
            } else {
                z->parent = x;
                x->left = z;
                break;
            }
        }
    }
    return z;
}

lru_cache::node *lru_cache::bst_tree::_erase(node *x) {
    node *p = x->parent;
    //std::cout << x->key << std::endl;
    if (x->left == nullptr && x->right == nullptr) {
        if (x == p->left) {
            p->left = x->right;
        } else {
            p->right = x->right;
        }
    } else if (x->left == nullptr) {
        if (x == p->left) {
            p->left = x->right;
        } else {
            p->right = x->right;
        }
        x->right->parent = p;
    } else if (x->right == nullptr) {
        if (x == p->left) {
            p->left = x->left;
        } else {
            p->right = x->left;
        }
        x->left->parent = p;
    } else {
        node *best_node = get_next(x);
        bool bad = (x->right == best_node);
        this->_erase(best_node);
        //std::cout << x->right->key << std::endl;
        if (p->left == x) {
            p->left = best_node;
        } else {
            p->right = best_node;
        }
        best_node->parent = p;
        best_node->left = x->left;
        if (!bad) {
            best_node->right = x->right;
            x->right->parent = best_node;
        } else {
            best_node->right = nullptr;
        }
        x->left->parent = best_node;
    }
    return x;
}

lru_cache::node *lru_cache::bst_tree::begin() const {
    return get_min(fake_node.left);
}

lru_cache::node *lru_cache::bst_tree::end() const {
    return get_max(fake_node.left);
}

lru_cache::node *lru_cache::bst_tree::get_max(node *x) {
    if (x->right == nullptr) {
        return x;
    }
    return get_max(x->right);
}

lru_cache::node *lru_cache::bst_tree::get_min(node *x) {
    if (x->left == nullptr) {
        return x;
    }
    return get_min(x->left);
}

lru_cache::bst_tree::~bst_tree() {
    fake_node.~node();
}

lru_cache::node *lru_cache::bst_tree::get_next(node *x) {
    if (x->right != nullptr) {
        return get_min(x->right);
    }
    node *y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

lru_cache::node *lru_cache::bst_tree::get_prev(node *x) {
    if (x->left != nullptr) {
        return get_max(x->left);
    }
    node *y = x->parent;
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

size_t lru_cache::bst_tree::size() const {
    return s;
}

lru_cache::node *lru_cache::bst_tree::erase(node *x) {
    s--;
    return _erase(x);
}

lru_cache::node::node(key_type key, mapped_type *mapped, node *left, node *right, node *parent, node *next, node *prev)
        : key(
        key), mapped(mapped), left(left), right(right), parent(parent), next(next), prev(prev) { }

lru_cache::list::list(size_t capacity) : capacity(capacity),
                                         fake_node(0, 0, nullptr, nullptr, nullptr, &fake_node, &fake_node) { }

lru_cache::iterator lru_cache::list::insert(node *place, node *x) {
    s++;
    node *prev_node = place->prev;
    x->prev = prev_node;
    x->next = place;
    place->prev = x;
    prev_node->next = x;
    return lru_cache::iterator(x);
}

lru_cache::list::~list() {
    fake_node.~node();
}

lru_cache::node *lru_cache::list::erase(node *x) {
    s--;
    node *prev_node = x->prev;
    node *next_node = x->next;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    return x;
}

lru_cache::node *lru_cache::list::begin() const {
    return fake_node.next;
}

lru_cache::node *lru_cache::list::end() const {
    return fake_node.prev;
}

size_t lru_cache::list::size() const {
    return s;
}

void lru_cache::list::update_latest_node(node *x) {
    this->erase(x);
    this->insert(this->begin(), x);
}

lru_cache::lru_cache(size_t capacity) : mem(capacity), set() { }

lru_cache::iterator lru_cache::find(key_type x) {
    node *found = set.find(x);
    if (!(found == nullptr || found->key != x)) {
        mem.update_latest_node(found);
        return found;
    }
    return set.end();
}

std::pair<lru_cache::iterator, bool> lru_cache::insert(value_type x) {
    node *it = set.find(x.first);
    if (it == nullptr || it->key != x.first) {
        if (mem.capacity == mem.size()) {
            node *useless_node = mem.end();
            set.erase(useless_node);
            mem.erase(useless_node);
            delete (useless_node);
        }
        mapped_type *ptr = new mapped_type(x.second);
        node *newnode = new node(x.first, ptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        set.insert(newnode);
        return std::make_pair(mem.insert(mem.begin(), newnode), true);
    }
    mem.update_latest_node(it);
    return std::make_pair(iterator(it), false);
}

void lru_cache::erase(iterator it_on_x) {
    node *x = it_on_x.my_el;
    set.erase(x);
    mem.erase(x);
    delete x->mapped;
    delete x;
}

bool lru_cache::iterator::operator==(const iterator &x) const {
    return this->my_el == x.my_el;
}

bool lru_cache::iterator::operator!=(const iterator &x) const {
    return !(*this == x);
}

lru_cache::iterator lru_cache::begin() const {
    return lru_cache::iterator(set.begin());
}

lru_cache::iterator lru_cache::end() const {
    return lru_cache::iterator(set.end());
}

lru_cache::~lru_cache() {
    while (mem.size() > 0) {
        node *x = mem.erase(mem.begin());
        set.erase(x);
        delete x->mapped;
        delete x;
    }
    set.~bst_tree();
    mem.~list();
}



















