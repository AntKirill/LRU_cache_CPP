//
// Created by Kirill Antonov on 27.09.2016.
//

#ifndef LRU_CACHE_LRU_CACHE_H
#define LRU_CACHE_LRU_CACHE_H


#include <iostream>

struct lru_cache {

    // Вы можете определить эти тайпдефы по вашему усмотрению.
    typedef int key_type;
    typedef int mapped_type;
    typedef std::pair<key_type, mapped_type> value_type;

    // Bidirectional iterator
    struct iterator;

    // Создает пустой lru_cache с указанной capacity.
    lru_cache(size_t capacity);

    // Деструктор. Вызывается при удалении объектов lru_cache.
    // Инвалидирует все итераторы ссылающиеся на элементы этого lru_cache
    // (включая итераторы ссылающиеся на элементы следующие за последними).
    ~lru_cache();

    // Поиск элемента.
    // Возвращает итератор на элемент найденный элемент, либо end().
    // Если элемент найден, он помечается как наиболее поздно использованный.
    iterator find(key_type);

    // Вставка элемента.
    // 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
    //    на уже присутствующий элемент и false.
    // 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
    //    элемент и true.
    // Если после вставки число элементов кеша превышает capacity, самый давно не
    // использованный элемент удаляется. Все итераторы на него инвалидируется.
    // Вставленный либо найденный с помощью этой функции элемент помечается как наиболее поздно
    // использованный.
    std::pair<iterator, bool> insert(value_type);

    // Удаление элемента.
    // Все итераторы на указанный элемент инвалидируются.
    void erase(iterator);

    // Возващает итератор на элемент с минимальный ключом.
    iterator begin() const;

    // Возващает итератор на элемент следующий за элементом с максимальным ключом.
    iterator end() const;



private:
    struct node {
        key_type key;
        mapped_type mapped;

        node *left;
        node *right;
        node *parent;

        node *next;
        node *prev;

        node(key_type key, mapped_type mapped, node *left, node *right, node *parent, node *next, node *prev);


    };

    struct bst_tree {

        bst_tree();


        node *insert(node*);

        node *find(key_type);

        node *erase(node *);

        node *begin() const;

        node *end() const;

        static node *get_next(node *);

        static node *get_prev(node *);

        size_t size() const;

    private:
        node fake_node;

        size_t s = 0;

        node *search(node *, key_type);

        node *_insert(node *, node *);

        node *_erase(node *);

        static node *get_max(node *); //from root of subtree

        static node *get_min(node *);
    } set;

    struct list {
        const size_t capacity;

        list(size_t capacity);


        iterator insert(node *, node *); //(where? , what? ) //returns iterator on node which was inserted

        node *erase(node *); //returns node that was erased

        node *begin() const;

        node *end() const;

        size_t size() const;

        void update_latest_node(node *); //make node that has been already latest in list

    private:
        node fake_node;

        size_t s = 0;
    } mem;
};

struct lru_cache::iterator {

    iterator(node *);

    ~iterator();

    value_type operator*() const;

    iterator &operator++();

    iterator operator++(int);

    iterator &operator--();

    iterator operator--(int);

    bool operator==(const iterator &) const;

    bool operator!=(const iterator &) const;

    friend void lru_cache::erase(iterator);

private:
    node *my_el;
};

#endif //LRU_CACHE_LRU_CACHE_H
