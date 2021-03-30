# From Video Turotial Here: https://www.youtube.com/watch?v=VjUWwrW9EVY&t=20s

import onnx
from onnx import helper, checker
from onnx import TensorProto
import re

def createGraphMemberMap(graph_member_list):
    member_map=dict();
    for n in graph_member_list:
        member_map[n.name]=n;
    return member_map

model = onnx.load("net.onnx")
graph = model.graph

#Generate a name for all node if they have none.
nodeIdx = 0;
for n in graph.node:
    print("node: \n\t" + str(n).replace("\n", "\n\t"))
    if n.name == '':
        n.name = str(n.op_type) + str(nodeIdx)
        nodeIdx += 1
    #print("name: " + str(n.name))

node_map = createGraphMemberMap(graph.node)               # convert to dict
input_map = createGraphMemberMap(graph.input)             # convert to dict
output_map = createGraphMemberMap(graph.output)           # convert to dict
initializer_map = createGraphMemberMap(graph.initializer) # convert to dict

#print("input_map: " + str(input_map.keys()))
#print("output_map: " + str(output_map.keys()))
#print("node_map: " + str(node_map.keys()))
#print("initializer map: " + str(initializer_map.keys()))

for key in node_map.keys():
    print("key: " + key)
    if "Clip" in key:
        print("removing key: " + str(key))
        graph.node.remove(node_map[key])

onnx.save(model, "netout.onnx")


