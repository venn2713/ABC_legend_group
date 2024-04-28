// –еализаци€ красно-черного дерева
template <typename Key, typename Value>
class RedBlackTree {
private:
    struct Node {
        Key key;
        Value value;
        bool is_red;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& key, const Value& value) : key(key), value(value), is_red(true), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        }
        else if (y == y->parent->right) {
            y->parent->right = x;
        }
        else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }

    void fix_insertion(Node* z) {
        while (z->parent != nullptr && z->parent->is_red) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotate_left(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    rotate_right(z->parent->parent);
                }
            }
            else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotate_right(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    rotate_left(z->parent->parent);
                }
            }
        }
        root->is_red = false;
    }
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    Node* minimum(Node* x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }

    Node* search(Node* x, const Key& key) {
        if (x == nullptr || key == x->key) {
            return x;
        }
        if (key < x->key) {
            return search(x->left, key);
        }
        else {
            return search(x->right, key);
        }
    }

    void fix_deletion(Node* x) {
        while (x != root && !x->is_red) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->is_red) {
                    w->is_red = false;
                    x->parent->is_red = true;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (!w->left->is_red && !w->right->is_red) {
                    w->is_red = true;
                    x = x->parent;
                }
                else {
                    if (!w->right->is_red) {
                        w->left->is_red = false;
                        w->is_red = true;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->right->is_red = false;
                    rotate_left(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w->is_red) {
                    w->is_red = false;
                    x->parent->is_red = true;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (!w->right->is_red && !w->left->is_red) {
                    w->is_red = true;
                    x = x->parent;
                }
                else {
                    if (!w->left->is_red) {
                        w->right->is_red = false;
                        w->is_red = true;
                        rotate_left(w);
                        w = x->parent->left;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->left->is_red = false;
                    rotate_right(x->parent);
                    x = root;
                }
            }
        }
        x->is_red = false;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        Node* z = new Node(key, value);
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nullptr) {
            root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->left = nullptr;
        z->right = nullptr;
        z->is_red = true;
        fix_insertion(z);
    }
    void erase(const Key& key) {
        Node* z = search(root, key);
        if (z == nullptr) {
            throw std::out_of_range("Key not found");
        }
        Node* y = z;
        Node* x;
        bool y_original_color = y->is_red;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->is_red;
            x = y->right;
            if (y->parent == z) {
                if (x != nullptr) {
                    x->parent = y;
                }
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) {
                    y->right->parent = y;
                }
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->is_red = z->is_red;
        }
        if (!y_original_color) {
            fix_deletion(x);
        }
        delete z;
    }

    Value& search(const Key& key) {
        Node* result = search(root, key);
        if (result == nullptr) {
            throw std::out_of_range("Key not found");
        }
        return result->value;
    }

    void inorder_traversal(Node* x, std::ostream& os) const {
        if (x != nullptr) {
            inorder_traversal(x->left, os);
            os << x->key << ": ";
            x->value.print(os);
            os << std::endl;
            inorder_traversal(x->right, os);
        }
    }

    void print(std::ostream& os) const {
        inorder_traversal(root, os);
    }

    ~RedBlackTree() {
        // Implement proper destruction of the tree to avoid memory leaks.
    }
};

//  ласс, объедин€ющий красно-черное дерево и абстрактный класс таблицы полиномов.
class PolynomialTableWithRedBlackTree : public IPolynomialTable {
private:
    RedBlackTree<std::string, Polynomial> tree;
    std::string table_name = "PolynomialTableWithRedBlackTree";

public:
    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        tree.insert(name, polynomial);
    }

    Polynomial& getPolynomial(const std::string& name) override {
        return tree.search(name);
    }

    void removePolynomial(const std::string& name) override {
        //tree.erase(name);
        return;
    }

    std::string getTableName() const override {
        return table_name;
    }

    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        tree.print(os);
        os << "-----------" << std::endl;
    }
};