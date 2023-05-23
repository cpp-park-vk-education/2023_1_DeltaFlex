#pragma once

#include <memory>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "DFESceneObject.hpp"

/*!
    \brief Список деревьев для создания иерархии между объектами.
    \warning Не может содержать два одинаковых объекта.
    \todo Работа с детьми, а не только с корнями.

    Данный класс создаёт иерархию между объектами, при этом у одного узла может быть сколько угодно прямых потомоков.
    Особенности:
    - Дерево владеет shared_ptr объектов и сделано для того, чтобы разделять эти объекты с другим классами.
    - Дерево получает сырые указатели на объекты и делает из них shared_ptr.
    - При удалении узла также удаляются все его потомки.
*/
class DFEHierarchy
{
    struct Node;
    using NodeSPtr = std::shared_ptr<Node>;
    using ISPtr = std::shared_ptr<IDFESceneObject>;

    struct Node
    {
        Node() : mp_value(nullptr) { mp_parent.reset(); }
        explicit Node(IDFESceneObject *value) : mp_value(value) { mp_parent.reset(); }
        explicit Node(const ISPtr &value) : mp_value(value) { mp_parent.reset(); }
        explicit Node(IDFESceneObject *value, const NodeSPtr &parent) : mp_value(value), mp_parent(parent) {}
        explicit Node(const ISPtr &value, const NodeSPtr &parent) : mp_value(value), mp_parent(parent) {}

        ISPtr mp_value;
        NodeSPtr mp_parent;
        std::list<NodeSPtr>mp_children;
    };

public:
    DFEHierarchy() : nodes(new Node()) {}
    ~DFEHierarchy() = default;

    bool AddRoot(IDFESceneObject *object)
    {
        auto elem = existing_nodes.find(object->GetSName());

        if (elem != existing_nodes.end())
            return false;

        NodeSPtr new_node{new Node(object, nodes)};

        nodes->mp_children.push_back(new_node);
        
        existing_nodes[new_node->mp_value->GetSName()] = new_node;

        return true;
    }

    bool AddRoot(const ISPtr &object)
    {
        auto elem = existing_nodes.find(object->GetSName());

        if (elem != existing_nodes.end())
            return false;

        NodeSPtr new_node{new Node(object, nodes)};

        nodes->mp_children.push_back(new_node);
        
        existing_nodes[new_node->mp_value->GetSName()] = new_node;

        return true;
    }
    
    bool Has(const QString &object_name)
    {
        auto elem = existing_nodes.find(object_name.toStdString());

        if (elem == existing_nodes.end())
            return false;
        
        return true;
    }

    bool Has(const IDFESceneObject *object)
    {
        auto elem = existing_nodes.find(object->GetSName());

        if (elem == existing_nodes.end() || elem->second->mp_value.get() != object)
            return false;
        
        return true;
    }

    bool Has(const ISPtr &object)
    {
        auto elem = existing_nodes.find(object->GetSName());

        if (elem == existing_nodes.end() || elem->second->mp_value != object)
            return false;
        
        return true;
    }

    bool Delete(const IDFESceneObject *object)
    {
        auto elem = existing_nodes.find(object->GetSName());

        if (elem == existing_nodes.end() || elem->second->mp_value.get() != object)
            return false;

        ClearNode(existing_nodes[object->GetSName()]);

        return true;
    }

    ISPtr &Get(const QString &object_name)
    {
        auto elem = existing_nodes.find(object_name.toStdString());

        if (elem == existing_nodes.end())
            throw std::runtime_error("Try to get not existing element of DFEHierarchy.");

        return elem->second->mp_value;
    }

    // Only root drawing
    void Draw(QPainter &painter)
    {
        for (const auto &elem: nodes->mp_children)
            elem->mp_value->Draw(painter);
    }

private:
    // Only root deleting, because children's existing_nodes must be cleared too
    void ClearNode(const NodeSPtr &node)
    {    
        if (node->mp_parent != nullptr)
        {
            Node *parent = node->mp_parent.get();
            parent->mp_children.erase(std::find(parent->mp_children.begin(), parent->mp_children.end(), node));
            existing_nodes.erase(node->mp_value->GetSName());
        }
    }

    NodeSPtr nodes;
    std::unordered_map<std::string, NodeSPtr>existing_nodes;
};
