#include "Node.hpp"
#include <cstring>
#include <iostream>

Node::Node( int node_name ) {
    this->name = node_name;
    this->edge_list_size = 50;
    this->edge_count = 0;
    this->edge_list = new Edge*[50];

    for( int i{0}; i < this->edge_list_size; i++ ) {
        this->edge_list[i] = nullptr;
    }
}

Node::~Node() {
    for( int i{0}; i < this->edge_count; i++ ) {
        if( this->edge_list[i] != nullptr) {
            delete this->edge_list[i];
            this->edge_list[i] = nullptr; 
        }
    }
    delete[] this->edge_list;
}

int Node::get_name() {
    return this->name;
}

Edge** Node::get_edge_list() {
    return this->edge_list;
}

int Node::get_edge_count() {
    return this->edge_count;
}

void Node::resize_edge_list() {
    int new_size = this->edge_list_size * 2;
    Edge** new_array = new Edge*[new_size](); 

    for( int i{0}; i < this->edge_count; i++ ) {
        new_array[i] = this->edge_list[i];
    }

    delete[] this->edge_list;
    this->edge_list = new_array;
    this->edge_list_size = new_size;
}

void Node::add_edge( int a , int b , double d , double s ) {
    // First, check if the edge already exists
    for( int i{0}; i < this->edge_count; i++ ) {
        if( this->edge_list[i]->get_end_node() == b ) {
            // If the edge exists, update its properties
            this->edge_list[i]->set_distance( d );
            this->edge_list[i]->set_speed_limit( s );
            // Edge updated, no need to add a new one
            return; 
        }
    }

    // Check if we need to resize the edge list
    if (this->edge_count >= this->edge_list_size -3 ) {
        resize_edge_list();
    }

    // Add the new edge
    this->edge_list[this->edge_count] = new Edge(a, b, d, s);
    this->edge_count++;
}

bool Node::update_edge( int b , double A ) {
    for( int i{0}; i <= this->edge_count; i++ ) {
        if( this->edge_list[i] != nullptr && this->edge_list[i]->get_end_node() == b ) {
            this->edge_list[i]->set_adjustment_factor( A );
            return true;
        }
    }
    return false;
}

bool Node::print_node() {
    if( this->edge_count == 0 ) {
        std::cout << std::endl;
        return false;
    }

    for( int i{0}; i < this->edge_count; i++ ) {
        std::cout <<  this->edge_list[i]->get_end_node() << " ";
    }
    std::cout << std::endl;

    return true;
}

void Node::remove_edge_to_node( int a ) {
    int edge_index = -1;

    for( int i{0}; i < this->edge_count; i++ ) {
        if( this->edge_list[i] != nullptr && this->edge_list[i]->get_end_node() == a ) {
            edge_index = i;
            break;
        }
    }

    //Edge found
    if( edge_index != -1 ) {
        if( this->edge_list[edge_index] != nullptr ) {
            delete this->edge_list[edge_index];
            this->edge_list[edge_index] = nullptr;
        }

        for( int j{edge_index}; j < this->edge_count - 1; j++ ) {
            edge_list[j] = edge_list[j + 1];
        }
        this->edge_count--;
        this->edge_list[this->edge_count] = nullptr;
    }
}

Edge* Node::find_edge_to_node( int b ) {
    for( int i{0}; i < this->edge_count; i++) {
        if( this->edge_list[i] != nullptr && this->edge_list[i]->get_end_node() == b ) {
            return this->edge_list[i];
        }
    }
    return nullptr;
}