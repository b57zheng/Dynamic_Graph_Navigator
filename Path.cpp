#include "Path.hpp"
#include <iostream>

// To initialize starting node path with weight 0
Path::Path( int node_name , double weight ) {
    this->path = new int[50];
    this->size = 50;
    this->count = 1;
    this->weight = weight;

    for( int i{0}; i < this->size; i++ ) {
        this->path[i] = 0;
    }

    this->path[0] = node_name;
}

// To constructing new path
Path::Path( int* previous_path , int previous_path_count , int current_node , double weight ) {
    this->path = new int[50 + previous_path_count];
    this->size = 50 + previous_path_count;
    this->count = 1 + previous_path_count;
    this->weight = weight;
    
    for( int i{0}; i < this->size; i++ ) {
        this->path[i] = 0;
    }

    for( int i{0}; i < previous_path_count; i++ ) {
        this->path[i] = previous_path[i];
    }

    this->path[previous_path_count] = current_node;
}

Path::~Path() {
    delete[] this->path;
}

void Path::add_node_to_path( int path ) {
    if( this->count >= this->size - 3 ) {
        this->resize();
    }

    this->path[this->count++] = path;
}

int Path::get_last_node() {
        return this->path[this->count - 1];
}

int Path::get_count() {
    return this->count;
}

int* Path::get_path() {
    return this->path;
}

void Path::set_weight( double weight ) {
    this->weight = weight;
}

double Path::get_weight() {
    return this->weight;
}

void Path::resize() {
    int new_size = this->size * 2;
    int* new_array = new int[new_size](); 

    for( int i = 0; i < this->count; i++ ) {
        new_array[i] = this->path[i];
    }

    delete[] this->path;
    this->path = new_array;
    this->size = new_size;
}

void Path::print() {
    for( int i{0}; i < this->count; i++ ) {
        std::cout << this->path[i] << " ";
    }
    std::cout << std::endl;
}   