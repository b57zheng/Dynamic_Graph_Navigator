class Edge {
    private:
        int start_node;
        int end_node;
        double distance;
        double speed_limit;
        double adjustment_factor;
        double weight;

    public:
        Edge( int start_node , int end_node , double distance , double speed_limit );
        ~Edge();
        int get_start_node();
        int get_end_node();
        double get_weight();
        double get_adjustment_factor();
        void set_adjustment_factor( double adjustment_factor );
        void set_distance( double distance );
        void set_speed_limit( double speed_limit );
};