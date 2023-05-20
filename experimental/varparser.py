import re

def parse_cplusplus_variables(definition):
    variables = definition.replace(';', '').split(',')
    *var_type, first_var = variables[0].split()
    var_type = ' '.join(var_type)
    variables = [first_var] + variables[1:]
    # print(var_type, variables)
    for var in variables:
        p_counter = var.count('*')
        print({'type': var_type + p_counter * '*', 'name': var.replace('*', '').strip()})

    # return parsed_variables


print(parse_cplusplus_variables("std::vector<int *> **abobers, *niggers;"))