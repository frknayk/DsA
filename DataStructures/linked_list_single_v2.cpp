#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
private:
    int data;
    Node* next;
public:
    Node(int);
    ~Node();
    void set_data(int);
    int get_data();
    void set_next(Node*);
    Node* get_next();
};
Node::Node(int data){
    this->data = data;
    this->next = NULL;
}

Node::~Node(){
    if(this->next != NULL)
        delete this->next;
}

void Node::set_data(int data){
    this->data=data;
}

int Node::get_data(){
    return this->data;
}

void Node::set_next(Node* next){
    this->next=next;
}

Node* Node::get_next(){
    return this->next;
}

class SingleLinkedList{
private:
    Node* head;
    Node* tail;
    Node* search(int);

public:
    SingleLinkedList();
    ~SingleLinkedList();
    void clear_list();
    void add_node(int);
    void remove_node(int);
    void print_list();
    bool contains(int);

};

SingleLinkedList::SingleLinkedList(){
    head=NULL;
    tail=NULL;
}

SingleLinkedList::~SingleLinkedList(){
    if(head!=NULL)
        delete head;
}

bool SingleLinkedList::contains(int data){

    Node* p=head;
    while(p!=NULL && p->get_data()!=data)
        p=p->get_next();
    if(p==NULL)
        return false;
    else
        return true;

}

void SingleLinkedList::clear_list(){
    if(head!=NULL)
        delete head;
    head=NULL;
    tail=NULL;
}

Node* SingleLinkedList::search(int data){
    Node *p=head;

    if(data<=head->get_data())
        return NULL;
    else{
        while(p->get_next()){
            if(p->get_next()->get_data()>=data)
                return p;
            p=p->get_next();
        }
        return p;
    }

}

void SingleLinkedList::add_node(int n){
    Node* new_node = new Node(n);
    if(head==NULL){
        head=new_node;
        tail=new_node;
    }
    else{
        Node* prev = this->search(n);

        if(prev==NULL){
            new_node->set_next(head);
            head=new_node;
        }
        else if(prev==tail){
            tail->set_next(new_node);
            tail=new_node;
        }
        else{
            new_node->set_next(prev->get_next());
            prev->set_next(new_node);
        }
    }

}

void SingleLinkedList::remove_node(int n){
    Node* prev = this->search(n);

    if(head==tail){
        delete head;
        head=NULL;
        tail=NULL;
    }
    else{
        if(prev==NULL){
            Node* old_head=head;
            head=head->get_next();
            old_head->set_next(NULL);
            delete old_head;
        }
        else if(prev->get_next()==tail){
            tail=prev;
            delete tail->get_next();
            tail->set_next(NULL);
        }
        else if(prev == tail){
            cout<<"Element not found"<<endl;
        }
        else{
            Node* cur = prev->get_next();
            prev->set_next(cur->get_next());
            cur->set_next(NULL);
            delete cur;
        }
    }

}

void SingleLinkedList::print_list(){
    Node* p=head;

    cout << "||->";
    while(p!=tail){
        cout<<p->get_data()<<"->";
        p=p->get_next();
    }
    if(p!=NULL)
        cout<<p->get_data()<<endl;

}


int main(){
    SingleLinkedList* s=new SingleLinkedList();

    s->add_node(5);
    s->add_node(1);
    s->add_node(10);
    s->add_node(8);

    s->print_list();
    //s->clear_list();
    if(s->contains(10))
        cout<<"s contains 10"<<endl;
    s->remove_node(5);
    s->remove_node(1);
    if(!s->contains(1))
        cout<<"s does not contain 1"<<endl;
    s->remove_node(10);
    s->remove_node(8);

    s->print_list();
    return 0;
}