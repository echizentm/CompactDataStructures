#pragma once


namespace cds {
    class variable_length_vector {
    public:
        uint64_t size;

        virtual ~variable_length_vector() {}

        virtual uint64_t vector_size() = 0;
        virtual uint64_t read(uint64_t index) = 0;
        virtual void push_back(uint64_t value) = 0;
    };
}
