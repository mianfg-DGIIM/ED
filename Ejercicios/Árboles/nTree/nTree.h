#ifndef __nTree_h_
#define __nTree_h_

#include <cassert>
#include <list>

/**
 * @brief TDA nTree
 * 
 * \b Definición:
 * Una instancia \e tree del tipo de dato abstracto \e nTree sobre un dominio
 * \e T se puede construir como:
 * [...]
 */
template <class T>
class nTree {
private:
    struct node {
        T tag;
        struct node *parent;
        std::list<node*> children;
    }
    struct node *laraiz;
    void destroy(node &n);
    void copy(node &destination, node &origin);
    int count(node &n);
    int countSiblings(node &n);
    bool isEqual(node &n1, node &n2);
    void writeTree(std::ostream &out, node *n) const;
    void readTree(std::istream &in, node *&n);
public:
    typedef struct node *Node;
    nTree();
    nTree(const T &element);
    nTree(const nTree<T> &tree);
    ~nTree();
    nTree<T>& operator=(const nTree<T> &tree);
    void assignRoot(const T &element);
    Node root() const;
    Node child(const Node n, int position) const;
    Node father(const Node n) const;
    T& tag(const Node n);
    const T& tag(const Node n) const;
    void assignSubtree(const nTree<T> &origin, const Node n);
    void pruneChild(Node n, nTree<T> &destination, int position);
    void insertChild(Node n, nTree<T> &branch, int position);
    void clear();
    int size();
    bool empty() const;
    bool height(Node n) const;
    void reverse(Node n);
    bool operator==(const nTree<T> &tree) const;
    bool operator!=(const nTree<T> &tree) const;
    friend nTree<T> retrieveTree(string pre, string in, string post);
    
    template <class T>
    friend std::istream& operator>>(std::istream &in, nTree<T> &tree);
    template <class T>
    friend std::ostream& operator<<(std::ostream &in, const nTree<T> &tree);

    class pre_iterator {
    private:
        Node p;
    public:
        pre_iterator() : p(0) {}
        pre_iterator(const Node &n) : p(n) {}
        pre_iterator(const pre_iterator &i) : p(i.p) {}
        const T& operator*() const {
            assert(p != 0);
            return p->tag;
        }
        T& operator*() {
            assert(p != 0);
            return p->tag;
        }
        bool operator==(const pre_iterator &i) {
            return p == i.p;
        }
        bool operator!=(const pre_iterator &i) {
            return p != i.p;
        }
        //[...]
    }
};

#endif