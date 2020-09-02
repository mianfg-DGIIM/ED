template <class T>
void nTree<T>::destroy(node &n) {
    if (n != 0) {
        std::list<node*>::iterator it;
        for ( it = n->children.begin(); it != n->children.end(); ++it ) {
            destroy(*it);
            delete n;
        }
    }
}

template <class T>
void nTree<T>::copy(node &destination, node &origin) {
    if (origin == 0)
        destination = 0;
    else {
        destination = new node;
        destination->tag = origin->tag;
        std::list<node*>::iterator it;
        for ( it = origin->children.begin(); it != origin->children.end(); ++it ) {
            copy();
        }
    }
}