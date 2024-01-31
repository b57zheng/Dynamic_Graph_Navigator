#include "Edge.hpp"

class Node {
    private:
        int name;
        Edge** edge_list;
        int edge_list_size;
        int edge_count;

    public:
        Node( int node_name );
        ~Node();
        int get_name();
        void resize_edge_list();
        Edge** get_edge_list();
        int get_edge_count();
        void add_edge( int a , int b , double d , double s );
        bool update_edge( int b , double A );
        bool print_node();
        void remove_edge_to_node( int a );
        Edge* find_edge_to_node( int b );
};
