#include "Path.hpp"

class Path_array {
    private:
        Path** path_array;
        int size;
        int count;
    
    public:
        Path_array();
        ~Path_array();
        int get_count();
        void insert( Path* path );
        void resize();
        void delete_path( Path* path );
        Path* min_weight_path();
        void remove_path( Path* path );
        bool last_node_in_path_array( int last_node );
};