#include "Node.hpp"
#include <fstream>

class Graph {
    private:
        Node** node_list;
        int node_list_size;
        int node_list_count;

    public:
        Graph();
        ~Graph();
        void resize_node_list();
        void load( std::fstream& fin );
        void insert( int a , int b , double d , double s );
        bool print( int a );
        bool delete_node( int a );
        void path( int a , int b ); 
        bool traffic( int a , int b , double A );
        void lowest( int a , int b );
        bool update( std::fstream& fin );
};