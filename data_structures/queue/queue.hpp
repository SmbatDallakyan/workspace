class Queue {
    private:
        struct node {
            node *next;
            node *prev;
            int data;
        };
        node *head;
        node *tail;
        int length;

    public:
        Queue();
        ~Queue();
        bool isEmpty();
        int getLength();
        void enqueue(int data);
        int dequeue(void);
};