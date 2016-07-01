#ifndef command_h
#define command_h

typedef struct command_param_node {

  char * param_name;
  int value;
  command_param_node_t * next_node;

} command_param_node_t;

typedef struct command_tag {

  int id;
  char * name;
  unsigned int num_param;
  command_param_node_t * start_pram_list;

} command_t;

#endif



