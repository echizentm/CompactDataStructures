#pragma once


namespace cds {
    class elias_fano_codes {
    public:
        unsigned int size;

        elias_fano_codes();

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}
