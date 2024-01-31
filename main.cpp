#include "illegal_exception.hpp"
#include "Graph.hpp"

int main();

int main() {
    Graph* graph;
    graph = new Graph();
    std::string cmd;

    while( std::cin >> cmd ) {
        if( cmd == "LOAD" ) {
            std::string filename;
            std::cin >> filename;
            std::fstream fin( filename.c_str(), std::fstream::in );

            graph->load(fin);
            fin.close();
        }

        else if( cmd == "INSERT") {
            int a = 0;
            int b = 0;
            double d = 0.0;
            double s = 0.0;

            std::cin >> a >> b >> d >> s;
            
            try {
                graph->insert( a , b , d , s );
                std::cout << "success" << std::endl;
            } catch( illegal_exception& e ) {
                std::cout << e.what() << std::endl;
            }
        }

        //The program will be terminated if a > 2147483647
        else if( cmd == "PRINT" ) {
            int a = 0;

            std::cin >> a;

            try {
                if( ! graph->print( a ) ) {
                    std::cout << "failure" << std::endl;
                }
            } catch( illegal_exception& e ) {
                std::cout << e.what() << std::endl;     
            } 
        }

        else if( cmd == "DELETE") {
            int a = 0;

            std::cin >> a;

            try {
                if( graph->delete_node( a ) ) {
                    std::cout << "success" << std::endl;
                } else {
                    std::cout << "failure" << std::endl;
                }
            } catch( illegal_exception& e ) {
                std::cout << e.what() << std::endl;
            }
        }

        else if( cmd == "LOWEST" ) {
            int a = 0;
            int b = 0;

            std::cin >> a >> b;

            try {
                graph->lowest( a , b );
            } catch( illegal_exception& e ) {
                std::cout << e.what() << std::endl;
            }
        }

        else if( cmd == "TRAFFIC" ) {
            int a = 0;
            int b = 0;
            double A = 0;

            std::cin >> a >> b >> A;

            try {
                if( graph->traffic( a , b , A ) ) {
                    std::cout << "success" << std::endl;
                } else {
                    std::cout << "failure" << std::endl;
                }
            } catch( illegal_exception& e ) {
                std::cout << e.what() << std::endl;
            }
        }

        else if( cmd == "UPDATE" ) {
            std::string filename;
            std::cin >> filename;
            std::fstream fin( filename.c_str(), std::fstream::in );

            if( graph->update( fin ) ) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std:: endl;
            }
        }

        else if( cmd == "PATH" ) {
            int a = 0;
            int b = 0;

            std::cin >> a >> b;
            try {
                graph->path( a , b );
            } catch( illegal_exception& e ) {
                std::cout << e.what() << std::endl;
            }
        }
        
        else if( cmd == "END" ) {
            delete graph;
            graph = nullptr;

            return 0; 
        }
    }
}
