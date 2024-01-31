#include "Path_array.hpp"
#include <limits>
#include <iostream>

Path_array::Path_array() {
    this->path_array = new Path*[50];
    this->size = 50;
    this->count = 0;

    for( int i{0}; i < this->size; i++ ) {
        this->path_array[i] = nullptr;
    }
}

Path_array::~Path_array() {
    for( int i{0}; i < this->count; i++ ) {
        if( this->path_array[i] != nullptr) {
            delete this->path_array[i];
            this->path_array[i] = nullptr; 
        }
    }
    delete[] this->path_array;
}

int Path_array::get_count() {
    return  this->count;
}

void Path_array::insert( Path* path ) {
    if( this->count >= this->size - 3 ) {
        this->resize();
    }

    this->path_array[this->count++] = path;
}

void Path_array::resize() {
    int new_size = this->size * 2;
    Path** new_array = new Path*[new_size](); 

    for( int i{0}; i < this->count; i++ ) {
        new_array[i] = this->path_array[i];
    }

    delete[] this->path_array;
    this->path_array= new_array;
    this->size = new_size;
}

void Path_array::delete_path( Path* path ) {
    for( int i{0}; i < this->count; i++ ) {
        if( this->path_array[i] != nullptr && this->path_array[i] == path ) {
            delete this->path_array[i];

            for( int j{i}; j < this->count - 1; j++ ) {
                this->path_array[j] = this->path_array[j + 1];
            }
            this->count--;
        }
    }
}

Path* Path_array::min_weight_path() {
    double min_weight = __DBL_MAX__;
    Path* min_path = nullptr;

    for( int i{0}; i < this->count; i++ ) {
        if( this->path_array[i]->get_weight() < min_weight ) {
            min_weight = this->path_array[i]->get_weight();
            min_path = this->path_array[i];
        }
    }

    return min_path;
}

void Path_array::remove_path( Path* path ) {
    for( int i{0}; i < this->count; i++ ) {
        if( this->path_array[i] != nullptr && this->path_array[i] == path ) {
            this->path_array[i] = nullptr;

            for( int j{i}; j < this->count - 1; j++ ) {
                this->path_array[j] = this->path_array[j + 1];
            }
            this->count--;
            this->path_array[this->count] = nullptr;
        }
    }
}

bool Path_array::last_node_in_path_array( int last_node ) {
    for( int i{0}; i < this->count; i++ ) { 
        if( this->path_array[i] != nullptr && this->path_array[i]->get_last_node() == last_node ) {
            return true;
        }
    }

    return false;
}