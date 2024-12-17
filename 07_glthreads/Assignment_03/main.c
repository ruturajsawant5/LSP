#include "glthread.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct emp_ {

    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glthread_node_t glnode;
} emp_t; 

emp_t *
glnode_to_employee (glthread_node_t *glnode) {
    return ((char*)glnode) - offsetof(emp_t, glnode);
}
void
print_emp_details(glthread_node_t *glnode){
    emp_t *emp = glnode_to_employee(glnode);
    printf("Employee name = %s\n", emp->name);
    printf("salary = %u\n", emp->salary);
    printf("designation = %s\n", emp->designation);
    printf("emp_id = %u\n", emp->emp_id);
}

int main(){
/*Creating one employee object*/

    emp_t *emp  = calloc(1, sizeof(emp_t));

    strncpy(emp->name, "Neha", strlen("Neha"));

    emp->salary = 50000;

    strncpy(emp->designation, "HR", strlen("HR"));

    emp->emp_id = 21;

   

/*Invoking fn to print employee details*/

    print_emp_details (&emp->glnode);

}