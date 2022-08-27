//
// Created by Reaper Lando on 8/27/22.
//

#ifndef CONTAINERS_NODE_HPP
#define CONTAINERS_NODE_HPP

namespace ft {
    template<class T>
    struct node {
        T			value;
        struct node	*parent;
        struct node	*left;
        struct node	*right;
        bool		color;
    };
}

#endif //CONTAINERS_NODE_HPP
