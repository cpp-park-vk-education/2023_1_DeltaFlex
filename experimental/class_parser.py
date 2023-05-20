#!/bin/python
import argparse
import re

parser = argparse.ArgumentParser(
    prog='Анализатор компонентов',
    description='Анализирует и создает новые компоненты')

parser.add_argument('src')

args = parser.parse_args()

import json

def parse_cpp_file_to_json(file_path):
    with open(file_path, 'r') as f:
        content = f.read()
        
    class_details = {}
    lines = content.split('\n')
    i = 0
    while i < len(lines):
        if lines[i].startswith('class'):
            class_name = lines[i].split()[1].replace(':', '')
            class_details[class_name] = {}
            # class_details[class_name]['methods'] = {'private': [], 'public': [], 'protected': []}
            class_details[class_name]['variables'] = {'private': [], 'public': [], 'protected': []}

            cur_section = 'private'

            i += 1
            while i < len(lines) and not lines[i].startswith('};'):
                if lines[i].startswith('//') or lines[i].startswith('/*'):
                    i += 1
                    continue
                elif lines[i].startswith('public') or lines[i].startswith('private') or lines[i].startswith('protected'):
                    cur_section = lines[i].split()[0].replace(':', '')
                    i += 1
                    continue
                elif cur_section != 'public':
                    i += 1
                    continue
                elif '(' in lines[i] and ')' in lines[i]:# and ';' not in lines[i]:
                    i += 1
                    continue
                elif ';' in lines[i]:
                    variable_details = {}
                    variable_signature = lines[i].strip().replace('\t', ' ')
                    try:
                        variable_name = variable_signature.split()[0]
                    except:
                        i += 1
                        continue
                    variable_details['signature'] = variable_signature
                    variable_details['name'] = variable_name
                    class_details[class_name]['variables'][cur_section].append(variable_details)

                i += 1
        i += 1
    return json.dumps(class_details, indent=2)
    # return class_details


data = parse_cpp_file_to_json(args.src)
print(data)
# for classname in data:
#     print('Должно быть сгенерировано: ' + classname)
#     for i, data in enumerate(data[classname]['variables']['public']):
#         print(f'[{i}]: тип: [{data["name"]}], сигнатура: [{data["signature"]}]')