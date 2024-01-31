#include "Graph.hpp"
#include "illegal_exception.hpp"
#include "Path_array.hpp"
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Graph::Graph() {
    this->node_list_size = 50;
    this->node_list_count = 0;
    this->node_list = new Node*[50];

    for( int i{0}; i < this->node_list_size; i++ ) {
        this->node_list[i] = nullptr;
    }
}

Graph::~Graph() {
    for( int i{0}; i < this->node_list_size; i++ ) {
        if( this->node_list[i] != nullptr ) {
            delete this->node_list[i];
            this->node_list[i] = nullptr;
        }
    }
    delete[] this->node_list;    
}


void Graph::resize_node_list() {
    int new_size = this->node_list_size * 2;
    Node** new_array = new Node*[new_size](); 

    for( int i = 0; i < this->node_list_count; i++ ) {
        new_array[i] = this->node_list[i];
    }

    delete[] this->node_list;
    this->node_list = new_array;
    this->node_list_size = new_size;
}


void Graph::load( std::fstream& fin ) {
    int a = 0;
    int b = 0;
    double d = 0.0;
    double s = 0.0;

    // Read line by line from the file
    std::string line;
    while( std::getline(fin, line) ) {
        std::istringstream iss(line);

        // Read the command and the parameters from the line
        if( ! ( iss >> a >> b >> d >> s ) ) {
            // Skip the current line and continue with the next one.
            continue; 
        }

        this->insert(a, b, d, s);
    }

    // Output success after loading the file
    std::cout << "success" << std::endl;
}


void Graph::insert( int a , int b , double d , double s ) {
    if( a > 500000 || b > 500000 || a <= 0 || b <= 0 || d <= 0 || s <= 0 ) {
        throw illegal_exception();
    }

    Node* node_a = nullptr;
    Node* node_b = nullptr;

    // Check if nodes exist and find them
    for( int i = 0; i < this->node_list_count; i++ ) {
        if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == a ) {
            node_a = this->node_list[i];
        } else if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == b ) {
            node_b = this->node_list[i];
        }
    }

    // Resize the node list if needed
    if( this->node_list_count >= this->node_list_size - 3 ) {
        resize_node_list();
    }

    // Add node A if not found
    if( node_a == nullptr ) {
        node_a = new Node( a );
        this->node_list[this->node_list_count++] = node_a;
    }

    // Add node B if not found
    if( node_b == nullptr ) {
        node_b = new Node( b );
        this->node_list[this->node_list_count++] = node_b;
    }

    //add the edge between A and B
    node_a->add_edge( a , b , d , s );
    node_b->add_edge( b , a , d , s );
}


bool Graph::print( int a ) {
    if( a > 500000 || a <= 0 ) {
        throw illegal_exception();
    }

    for( int i{0}; i < this->node_list_count; i++ ) {
        if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == a ) {
            this->node_list[i]->print_node();
            return true;
        }
    }
    
    return false;
}


bool Graph::delete_node( int a ) {
    if( a > 500000 || a <= 0 ) {
        throw illegal_exception();
    }

    //return false if the graph is empty
    if( this->node_list_count == 0) {
        return false;
    }

    Node* node_to_delete = nullptr;
    int index_to_delete = -1;

    // Find the node and its index
    for( int i{0}; i < this->node_list_count; i++ ) {
        if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == a ) {
            node_to_delete = this->node_list[i];
            index_to_delete = i;
            break;
        }
    }

    // If the node was not found, return false
    if( node_to_delete == nullptr ) {
        return false;
    }

    // Iterate over all nodes and remove edges pointing to node 'a'
    for( int i{0}; i < this->node_list_count; i++ ) {
        if( this->node_list[i] != nullptr ) {
            this->node_list[i]->remove_edge_to_node( a );
        }
    }

    // delete the node 
    if( node_to_delete != nullptr ) {
        delete node_to_delete;
        this->node_list[index_to_delete] = nullptr;
    }


    // Shift the nodes in the array to fill the gap
    for( int j = index_to_delete; j < this->node_list_count - 1; j++ ) {
        this->node_list[j] = this->node_list[j + 1];
    }
    this->node_list_count--;
    this->node_list[this->node_list_count] = nullptr;

    return true;
}


void Graph::path( int a , int b ) { 
    if( a > 500000 || b > 500000 || a <= 0 || b <= 0 ) {
        throw illegal_exception();
    }

    //return false if the graph is empty
    if( this->node_list_count == 0 ) {
        std::cout << "failure" << std::endl;
        return;
    }

    Path_array* visited = new Path_array();
    Path_array* explored = new Path_array();

    explored->insert( new Path( a , 0 ) );

    while( explored != nullptr && explored->get_count() != 0 ) {
        // find min weight path in the explored array
        Path* current_path = explored->min_weight_path();
        if( current_path == nullptr || current_path->get_count() == 0 ) {
            break;
        }
        // extract last node and weight from current path
        int last_node = current_path->get_last_node();
        double current_weight = current_path->get_weight();
        int current_count = current_path->get_count();

        //if last node is the target node, print the path and release the memory allocated to visited and explored
        if( last_node == b ) {
            current_path->print();

            delete visited;
            delete explored;

            return;
        } else {
            // move current path to visited and remove it from explored
            visited->insert( current_path );
            explored->remove_path( current_path );
        }

        Node* current_node = nullptr;
        for( int i{0}; i < this->node_list_count; i++ ) {
            // find node from the node array list
            if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == last_node ) {
                current_node = node_list[i];
                break;
            }
        }

        if( current_node != nullptr ) {
            // find edges and number of edges connected to the last node
            Edge** current_edges = current_node->get_edge_list();
            int current_edge_count = current_node->get_edge_count();
            for( int i{0}; i < current_edge_count; i++ ) {
                int end_node = current_edges[i]->get_end_node();
                // if the end node of current edge is not in the visited array
                if( ! visited->last_node_in_path_array( end_node ) ) {
                    // add new path to the explored array
                    Path* new_path = new Path( current_path->get_path(), current_count , end_node , current_weight + current_edges[i]->get_weight() ); 
                    explored->insert( new_path ); 
                }
            }
        }

    }

    //there is no connection between a and b
    std::cout << "failure" << std::endl;
    
    delete visited;
    delete explored;

    return;  
} 


bool Graph::traffic( int a , int b , double A ) {
    if( a > 500000 || b > 500000 || a <= 0 || b <= 0 ) {
        throw illegal_exception();
    }

    if( A > 1 || A < 0 ) {
        return false;
    }

    bool found_a = false;
    bool found_b = false;

    for( int i{0}; i < this->node_list_count; i++ ) {
        if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == a ) {
            found_a = this->node_list[i]->update_edge( b , A );
        }
        if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == b ) {
            found_b = this->node_list[i]->update_edge( a , A );
        }
    }

    if( found_a && found_b ) {
        return true;
    }

    return false;
}

bool Graph::update( std::fstream& fin ) {
    int a = 0;
    int b = 0;
    double A = 0.0;
    bool update_found = false;
    bool valid_traffic = false;

    // Read line by line from the file
    std::string line;
    while( std::getline(fin, line) ) {
        std::istringstream iss(line);

        // Read the command and the parameters from the line
        if( ! ( iss >> a >> b >> A ) ) {
            // Skip the current line and continue with the next one.
            continue; 
        }

        Node* node_a = nullptr;

        //find node a
        for( int i = 0; i < this->node_list_count; i++ ) {
            if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == a ) {
                node_a = this->node_list[i];
            }
        }

        //node was found
        if( node_a != nullptr ) {
            Edge* current_edge = node_a->find_edge_to_node( b );
            if( current_edge != nullptr && current_edge->get_adjustment_factor() != A ) {
                //update the adjustment factor and set update found to true.
                valid_traffic = traffic( a , b , A );
                update_found = true;
            }
        }
    }

    if( update_found && valid_traffic ) {
        return true;
    } else {
        return false;
    }
}


void Graph::lowest( int a , int b ) {
    if( a > 500000 || b > 500000 || a <= 0 || b <= 0 ) {
        throw illegal_exception();
    }

    if( this->node_list_count == 0 ) {
        std::cout << "failure" << std::endl;
        return;
    }

    Path_array* visited = new Path_array();
    Path_array* explored = new Path_array();

    explored->insert( new Path( a , 0 ) );

    while( explored != nullptr && explored->get_count() != 0 ) {
        // find min weight path in the explored array
        Path* current_path = explored->min_weight_path();
        if( current_path == nullptr || current_path->get_count() == 0 ) {
            break;
        }
        // extract last node and weight from current path
        int last_node = current_path->get_last_node();
        double current_weight = current_path->get_weight();
        int current_count = current_path->get_count();

        //if last node is the target node, return weight of the path.
        if( last_node == b ) {
            std::cout << "lowest is " << current_weight << std::endl;

            delete visited;
            delete explored;

            return;
        } else {
            // move current path to visited and remove it from explored
            visited->insert( current_path );
            explored->remove_path( current_path );
        }

        Node* current_node = nullptr;
        for( int i{0}; i < this->node_list_count; i++ ) {
            // find node from the node array list
            if( this->node_list[i] != nullptr && this->node_list[i]->get_name() == last_node ) {
                current_node = node_list[i];
                break;
            }
        }

        if( current_node != nullptr ) {
            // find edges and number of edges connected to the last node
            Edge** current_edges = current_node->get_edge_list();
            int current_edge_count = current_node->get_edge_count();
            for( int i{0}; i < current_edge_count; i++ ) {
                int end_node = current_edges[i]->get_end_node();
                // if the end node of current edge is not in the visited array
                if( ! visited->last_node_in_path_array( end_node ) ) {
                    // add new path to the explored array
                    Path* new_path = new Path( current_path->get_path(), current_count , end_node , current_weight + current_edges[i]->get_weight() ); 
                    explored->insert( new_path ); 
                }
            }
        }
    }

    //there is no connection between a and b
    std::cout << "failure" << std::endl;
    
    delete visited;
    delete explored;

    return;
}

