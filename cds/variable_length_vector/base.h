#pragma once


namespace cds {
    class variable_length_vector {
    public:
        unsigned int size;

        virtual ~variable_length_vector() {}

        virtual unsigned int vector_size() = 0;
        virtual unsigned int read(unsigned int index) = 0;
        virtual void push_back(unsigned int value) = 0;
    };
}
