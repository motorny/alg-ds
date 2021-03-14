struct node* node_create(int key) {
    struct node* new_node = NULL;
    if (new_node = (struct node*)malloc(sizeof(node))) {
        new_node->key = key;
        new_node->size = 1;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

struct node* node_find(struct node* root, int key)
{
    if (root == NULL)
        return 0;
    if (key == root->key)
        return root;
    if (key < root->key)
        return node_find(root->left, key);
    else
        return node_find(root->right, key);
}

int node_getsize(struct node* root)
{
    if (root == NULL)
        return 0;
    return root->size;
}

void node_fixsize(struct node* root)
{
    root->size = node_getsize(root->left) + node_getsize(root->right) + 1;
}

struct node* rot_right(struct node* ptr_node)
{
    struct node* rot_node = ptr_node->left;
    if (!rot_node) return ptr_node;
    ptr_node->left = rot_node->right;
    rot_node->right = ptr_node;
    rot_node->size = ptr_node->size;
    node_fixsize(ptr_node);
    return rot_node;
}

struct node* rot_left(struct node* ptr_node)
{
    struct node* rot_node = ptr_node->right;
    if (!rot_node) return ptr_node;
    ptr_node->right = rot_node->left;
    rot_node->left = ptr_node;
    rot_node->size = ptr_node->size;
    node_fixsize(ptr_node);
    return rot_node;
}

struct node* insertnode(struct node* ptr_node, int key)
{
    if (ptr_node == NULL)
        return node_create(key);
    if (key < ptr_node->key)
    {
        ptr_node->left = insertnode(ptr_node->left, key);
        return rot_right(ptr_node);
    }
    else
    {
        ptr_node->right = insertnode(ptr_node->right, key);
        return rot_left(ptr_node);
    }
}

struct node* insert(struct node* ptr_node, int key)
{
    if (ptr_node == NULL)
        ptr_node = node_create(key);
    if (rand() % (ptr_node->size + 1) == ptr_node->size)
        return insertnode(ptr_node, key);
    if (ptr_node->key > key)
        ptr_node->left = insert(ptr_node->left, key);
    else
        ptr_node->right = insert(ptr_node->right, key);
    node_fixsize(ptr_node);
    return ptr_node;
}

struct node* join(struct node* ptr_node1, struct node* ptr_node2)
{
    if (ptr_node1 == NULL)
        return ptr_node2;
    if (ptr_node2 == NULL)
        return ptr_node1;

    if (rand() % (ptr_node1->size + ptr_node2->size) < ptr_node1->size)
    {
        ptr_node1->right = join(ptr_node1->right, ptr_node2);
        node_fixsize(ptr_node1);
        return ptr_node1;
    }
    else
    {
        ptr_node2->left = join(ptr_node1, ptr_node2->left);
        node_fixsize(ptr_node2);
        return ptr_node2;
    }
}

struct node* remove_node(struct node* node, int key)
{
    if (node == NULL)
        return node;

    if (node->key == key)
    {
        struct node* q = join(node->left, node->right);
        free(node);
        return q;
    }
    else if (key < node->key)
        node->left = remove_node(node->left, key);
    else
        node->right = remove_node(node->right, key);
    return node;
}
