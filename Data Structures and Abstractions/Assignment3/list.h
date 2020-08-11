#ifndef _list_h
#define _list_h

class List{
    private:
        struct node {
            double x;
            double y;
            double z;
            char chain;
            struct node* next;
        };

        node *head;
        node *tail;
        int size;

    public:
        List();
        ~List();
        void append(double xx, double yy, double zz, char ch);
        void prepend(double xx, double yy, double zz, char ch);
        void print();
        void clear();
        void euclydeanDistAndWrite();

};

#endif