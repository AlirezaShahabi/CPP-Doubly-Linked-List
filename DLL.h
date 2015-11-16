
// Doubly-Linked List 

#ifndef LinkedList_H
#define LinkedList_H

#include <algorithm>
#include <iostream>

template <typename T> class DLL {
friend void swap(DLL<T>& lhs, DLL<T>& rhs) {
    using std::swap;
    swap(lhs.head, rhs.head);
    swap(lhs.length, rhs.length);
}
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T inp):data(inp),prev(nullptr),next(nullptr) {}
        Node():data(),prev(nullptr),next(nullptr) {}
    };
    Node* head;
    size_t length;
    // private utility functions
    void copy_helper(Node*&, Node*);
    Node* find_helper(Node*, size_t) const;
    Node* find_helper(Node*, const T&, size_t&) const;
    void delete_helper(Node*);
public:
    // constructor - assignment - destructor
    DLL();
    DLL(const DLL&);
    DLL& operator=(DLL);
    DLL(DLL&&);
    ~DLL();
    // print information
    void print_length() const;
    void print_data_at_index(size_t) const;
    void print_index_by_data(const T&) const;
    void print_forward(std::ostream&) const;
    void print_reverse(std::ostream&) const;
    // update - add - remove
    DLL& update_node(const T&, const T&);
    DLL& update_node(const T&, size_t);
    DLL& add_node_front(const T&);
    DLL& add_node_middle(const T&, size_t);
    DLL& add_node_end(const T&);
    DLL& rem_node(const T&);
    DLL& splice(size_t, const DLL&);
    // reverse
    void reverse_list();
};

#endif





// constructor - assignment - operator - - - - - - - - - - - - - - - - - - - - - - -


// constructor
template <typename T> DLL<T>::DLL():head(nullptr),length(0) {}

// copy constructor
template <typename T> DLL<T>::DLL(const DLL& rhs):head(new Node),length(rhs.length) {
    if (rhs.head) {copy_helper(head, rhs.head);}
}

// assignment operator (copy-move)
template <typename T> DLL<T>& DLL<T>::operator=(DLL rhs) {
    swap(*this, rhs);
    return *this;
}

// move constructor
template <typename T> DLL<T>::DLL(DLL&& rhs):DLL() {swap(*this, rhs);}

// destructor
template <typename T> DLL<T>::~DLL() {delete_helper(head);}


// public member functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


// print the length of the list
template <typename T> void DLL<T>::print_length() const {
    std::cout << "length = " << length << std::endl;
}

// print the Node at the index
template<typename T> void DLL<T>::print_data_at_index(size_t index) const {
    if (!head) {
        std::cout << "list is empty!" << std::endl;
    } else {
        Node* ans = find_helper(head, index);
        if (ans) {
            std::cout << ans->data << " is at index " << index << std::endl;
        } else {
            std::cout << index << " is out of bound" << std::endl;
        }
    }
}

// print the node with the data
template<typename T> void DLL<T>::print_index_by_data(const T& data) const {
    if (!head) {
        std::cout << "list is empty" << std::endl;
    } else {
        size_t index = 0;
        Node* ans = find_helper(head, data, index);
        if (ans) {
            std::cout << ans->data << " is at index " << index << std::endl;
        } else {
            std::cout << data << " is not in the list" << std::endl;
        }
    }
}

// print all the nodes from head to the end.
// assuming that type T can be output to screen
template <typename T> void DLL<T>::print_forward(std::ostream& os) const {
    if (!head) {
        os << "list is empty!" << std::endl;
    } else {
        Node* temp = head;
        while (temp) {
            os << temp->data << "  ";
            temp = temp->next;
        }
        os << std::endl << std::endl;
    }
}

// print all the nodes from the end to head.
// assuming that type T can be output to screen
template <typename T> void DLL<T>::print_reverse(std::ostream& os) const {
    if (!head) {
        os << "list is empty!" << std::endl;
    } else {
        Node* temp = find_helper(head, length-1);
        while (temp) {
            os << temp->data << "  ";
            temp = temp->prev;
        }
        os << std::endl << std::endl;
    }
}

// update the value of the node with old_val
template <typename T> DLL<T>& DLL<T>::update_node(const T& old_val, const T& new_val) {
    if (!head) {
        std::cout << "list is empty!" << std::endl;
    } else {
        size_t index = 0;
        Node* ans = find_helper(head, old_val, index);
        if (ans) {
            ans->data = new_val;
        } else {
            std::cout << old_val << " not in the list!" << std::endl;
        }
    }
    return *this;
}

// update the value of the node at index
template <typename T> DLL<T>& DLL<T>::update_node(const T& new_val, size_t index) {
    if (!head) {
        std::cout << "list is empty!" << std::endl;
    } else {
        Node* ans = find_helper(head, index);
        if (ans) {
            ans->data = new_val;
        } else {
            std::cout << "index out of bound!" << std::endl;
        }
    }
    return *this;
}

// add node to the front of the list
template <typename T> DLL<T>& DLL<T>::add_node_front(const T& data) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
    } else {
        Node* temp = head;
        new_node->next = temp;
        temp->prev = new_node;
        head = new_node;
    }
    ++length;
    return *this;
}

// add node to the middle of the list
template <typename T> DLL<T>& DLL<T>::add_node_middle(const T& data, size_t index) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
        ++length;
    } else if (index == 0) {
        add_node_front(data);
    } else {
        Node* ans = find_helper(head, index-1);
        Node* temp = ans->next;
        new_node->prev = ans;
        new_node->next = temp;
        ans->next  = new_node;
        temp->prev = new_node;
        ++length;
    }
    return *this;
}

// add node to the end of the list
template <typename T> DLL<T>& DLL<T>::add_node_end(const T& data) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
    } else {
        Node* ans = find_helper(head, length-1);
        ans->next = new_node;
        new_node->prev = ans;
    }
    ++length;
    return *this;
}

// remove the node with data from the list
template<typename T> DLL<T>& DLL<T>::rem_node(const T& data) {
    if (!head) {
        std::cout << "list is empty!" << std::endl;
    } else if (head->data == data) {
        Node* temp = head;
        Node* delptr = head;
        head = temp->next;
        head->prev = nullptr;
        delptr->next = nullptr;
        delete delptr;
        --length;
    } else {
        size_t index = 0;
        Node* ans = find_helper(head, data, index);
        if (ans) {
            Node* delptr = ans;
            Node* temp_prev = ans->prev;
            Node* temp_next = ans->next;
            temp_prev->next = temp_next;
            if (temp_next) {temp_next->prev = temp_prev;}
            delptr->prev = nullptr;
            delptr->next = nullptr;
            delete delptr;
            --length;
        } else {
            std::cout << data << " is not in the list!" << std::endl;
        }
    }
    return *this;
}

// make a deep copy of inp_list at the location of index in the current list
template<typename T> DLL<T>& DLL<T>::splice(size_t index, const DLL& inp_list) {
    if (!head) {
        copy_helper(head, inp_list.head);
    } else {
        Node* new_head = new Node;
        copy_helper(new_head, inp_list.head);
        Node* new_end = find_helper(new_head, inp_list.length-1);
        if (index == 0) {
            Node* temp = head;
            new_end->next = temp;
            temp->prev = new_end;
            head = new_head;
        } else {
            Node* location = find_helper(head, index-1);
            Node* location_next = location->next;
            location->next = new_head;
            new_head->prev = location;
            new_end->next = location_next;
            location_next->prev = new_end;
        }
        length += inp_list.length;
    }
    return *this;
}

// reverse the list
template<typename T> void DLL<T>::reverse_list() {
    if (head && head->next) {
        Node* temp = nullptr;
        Node* curr = head;
        while (curr) {
            Node* curr_next = curr->next;
            Node* curr_prev = curr->prev;
            curr->prev = curr_next;
            curr->next = curr_prev;
            temp = curr;
            curr = curr_next;
        }
        head = temp;
    }
}


// private utility functions - - - - - - - - - - - - - - - - - - - - - - - - - - - -


// used by copy constructor and splice
// make a deep copy of the list started at source into target
template <typename T> void DLL<T>::copy_helper(Node*& target, Node* source) {
    if (!source) {
        target = nullptr;
    } else {
        Node* creator = new Node(source->data);
        creator->prev = source->prev ? (new Node(source->prev->data)):nullptr;
        target = creator;
        Node* iterator1 = source;
        Node* iterator2 = source->next;
        while (iterator2) {
            creator->next = new Node;
            Node* temp = creator;
            creator = creator->next;
            creator->data = iterator2->data;
            creator->prev = temp;
            iterator1 = iterator2;
            iterator2 = iterator2->next;
        }
        creator->next = nullptr;
    }
}

// used by: print_data_at_index, print_reverse, update_node, add_node_middle
// add_node_end, splice. returns a pointer to the node at index n
template <typename T>
typename DLL<T>::Node* DLL<T>::find_helper(Node* temp, size_t n) const {
    size_t index = 0;
    while (index != n && temp->next) {
        temp = temp->next;
        ++index;
    }
    return (index == n ? temp:nullptr);
}

// used by: print_index_by_data, update_node, rem_node. returns a pointer to the
// node with data, also updates n to the index
template <typename T>
typename DLL<T>::Node* DLL<T>::find_helper(Node* temp, const T& data, size_t& n)
const {
    while (temp && temp->data != data) {
        temp = temp->next;
        ++n;
    }
    return (temp->data == data ? temp:nullptr);
}

// used by destructor, deletes all the nodes from temp to the end
template <typename T> void DLL<T>::delete_helper(Node* temp) {
    while (temp) {
        Node* delptr = temp;
        temp = temp->next;
        delptr->prev = nullptr;
        delptr->next = nullptr;
        delete delptr;
    }
}


