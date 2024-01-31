#include "Edge.hpp"

Edge::Edge( int start_node , int end_node , double distance , double speed_limit ) {
    this->start_node = start_node;
    this->end_node = end_node;
    this->distance = distance;
    this->speed_limit = speed_limit;

    this->adjustment_factor = 1;
    this->weight = (this->distance) / (this->speed_limit);
}

Edge::~Edge() {

}

int Edge::get_start_node() {
    return this->start_node;
}

int Edge::get_end_node() {
    return this->end_node;
}

double Edge::get_weight() {
    return this->weight;
}

double Edge::get_adjustment_factor() {
    return this->adjustment_factor;
}

void Edge::set_adjustment_factor( double adjustment_factor ) {
    this->adjustment_factor = adjustment_factor;
    this->weight = (this->distance) / (this->speed_limit * this->adjustment_factor);
}

void Edge::set_distance( double distance ) {
    this->distance = distance;
    this->weight = (this->distance) / (this->speed_limit * this->adjustment_factor);
}

void Edge::set_speed_limit( double speed_limit ) {
    this->speed_limit = speed_limit;
    this->weight = (this->distance) / (this->speed_limit * this->adjustment_factor);
}