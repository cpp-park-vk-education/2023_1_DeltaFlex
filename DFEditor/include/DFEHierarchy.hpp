#pragma once

#include <memory>
#include <list>
#include <stack>
#include <unordered_map>
#include <algorithm>

/*!
    \brief Список деревьев для создания иерархии между объектами.
    \warning Не может содержать два одинаковых объекта.
    \warning Для объектов должна быть определена операция сравнения.
    \param[in] T Тип объектов.
    \param[in] Hash Функция хеширования объектов, по умолчанию std::hash<T>
    \todo Добавление детей к родителям, а не только создание корней.

    Данный класс создаёт иерархию между объектами, при этом у одного узла может быть сколько угодно прямых потомоков.
    Особенности:
    - Дерево владеет shared_ptr объектов и сделано для того, чтобы разделять эти объекты с другим классами.
    - Дерево получает сырые указатели на объекты и делает из них shared_ptr.
    - При удалении узла также удаляются все его потомки.
*/
template<typename T, typename Hash = std::hash<T>>
class DFEHierarchy
{
    using TSPtr = std::shared_ptr<T>;

    struct Node
    {
        Node() : mp_value(nullptr) { mp_parent.reset(); }
        explicit Node(T *value) : mp_value(value) { mp_parent.reset(); }
        explicit Node(T *value, const std::shared_ptr<Node> &parent) : mp_value(value), mp_parent(parent) {}

        TSPtr mp_value;
        std::weak_ptr<Node>mp_parent;
        std::list<std::shared_ptr<Node>>mp_children;
    };

    using NodeSPtr = std::shared_ptr<Node>;
    using NodeWPtr = std::shared_ptr<Node>;

public:
    DFEHierarchy() : nodes(new Node()) {}
    ~DFEHierarchy();

    bool AddRoot(T *object);
    bool Has(const TSPtr &object);
private:
    void ClearNode(NodeSPtr &node);

    NodeSPtr nodes;
    std::unordered_map<TSPtr, std::pair<bool, NodeWPtr>>existing_nodes;
};

template<typename T, typename Hash>
DFEHierarchy<T, Hash>::~DFEHierarchy()
{
    ClearNode(nodes);
}

template<typename T, typename Hash>
bool DFEHierarchy<T, Hash>::AddRoot(T *object)
{
    bool has = existing_nodes.at(TSPtr(object)).first;

    if (has)
        return false;

    NodeSPtr new_node{new Node(object)};

    nodes->mp_children.push_back(new_node);
    
    existing_nodes.at(new_node->mp_value) = std::make_pair(true, new_node);

    return true;
}

template<typename T, typename Hash>
bool DFEHierarchy<T, Hash>::Has(const TSPtr &object)
{
    bool has = existing_nodes.at(object).first;

    if (!has)
        existing_nodes.erase(existing_nodes.find(object));
    
    return has;
}

template<typename T, typename Hash>
void DFEHierarchy<T, Hash>::ClearNode(NodeSPtr &node)
{    
    std::stack<NodeSPtr>stack;

    while (!stack.empty())
    {
        NodeSPtr cur_node = stack.top();
        stack.pop();

        for (auto &elem: cur_node->mp_children)
            stack.push(elem);

        existing_nodes.erase(existing_nodes.find(cur_node->mp_value));
    }

    if (node->mp_parent.expired())
    {
        Node *parent = node->mp_parent.lock().get();
        parent->mp_children.erase(std::find(parent->mp_children.begin(), parent->mp_children.end(), node));
    }
}
