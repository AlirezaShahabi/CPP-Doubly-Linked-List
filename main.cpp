
// tester function for DLL (Doubly Linked List) class

#include "DLL.h"
#include <iostream>
#include <string>

int main() {

    DLL<std::string> list1;
    list1.add_node_end("jack").add_node_end("alex");
    list1.add_node_end("sam").add_node_end("tim").add_node_end("jimmy");
    list1.add_node_end("michael").add_node_end("steve");
    list1.add_node_front("thom").add_node_front("bryan");
    
    std::cout << "list1: " << std::endl;
    list1.print_forward(std::cout);
    list1.print_reverse(std::cout);
    
    DLL<std::string> list2(list1);
    list2.update_node("steve","ANTHONY");
    list2.update_node("PETER",1);
    
    std::cout << "list2: " << std::endl;
    list2.print_forward(std::cout);
    list2.print_reverse(std::cout);
    
    DLL<std::string> list3;
    list3 = list2;
    list3.add_node_middle("FRANK",2).add_node_middle("ROBERT",6);
    
    std::cout << "list3: " << std::endl;
    list3.print_forward(std::cout);
    list3.print_reverse(std::cout);
    
    list3.rem_node("bryan").rem_node("sam").rem_node("ANTHONY");
    
    std::cout << "list3: " << std::endl;
    list3.print_forward(std::cout);
    list3.print_reverse(std::cout);
    
    DLL<std::string> list4(std::move(list1));
    std::cout << "list4: " << std::endl;
    list4.print_forward(std::cout);
    list4.print_reverse(std::cout);
    std::cout << "list1: " << std::endl;
    list1.print_forward(std::cout);

    DLL<std::string> list5;
    list5.add_node_end("sara").add_node_end("lily");
    list5.add_node_end("angela").add_node_end("tina");
    list5.add_node_front("rose").add_node_middle("susan",3);
    
    std::cout << "list5: " << std::endl;
    list5.print_forward(std::cout);
    
    list5.print_data_at_index(2);
    list5.print_index_by_data("tina");
    
    DLL<std::string> list6;
    
    list6 = std::move(list5);
    std::cout << "list6: " << std::endl;
    list6.print_forward(std::cout);

    list6.reverse_list();
    std::cout << "list6: " << std::endl;
    list6.print_forward(std::cout);
    
    std::cout << "list5: " << std::endl;
    list5.print_forward(std::cout);
    
    list3.splice(0,list6);
    std::cout << "list3: " << std::endl;
    list3.print_forward(std::cout);
    
    list3.splice(11,list6);
    std::cout << "list3: " << std::endl;
    list3.print_forward(std::cout);

    return 0;
}


