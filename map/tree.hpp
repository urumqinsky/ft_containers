//
// Created by Said Islamov on 15.08.2022.
//

#ifndef CONTAINERS_TREE_HPP
#define CONTAINERS_TREE_HPP

template<typename T>
struct node {
	struct node *parent, *left, *right;
	T key;
};

#endif //CONTAINERS_TREE_HPP
