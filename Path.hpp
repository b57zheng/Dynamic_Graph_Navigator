class Path {
    private:
        int* path;
        double weight;
        int count;
        int size;

    public:
        Path( int node_name , double weight );
        Path( int* previous_path , int previous_path_count, int current_node , double weight );
        ~Path();

        void add_node_to_path( int path );
        int get_last_node();
        int get_count();
        int* get_path();
        void set_weight( double weight );
        double get_weight();
        void resize();
        void print();
};