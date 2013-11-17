s = """nl2kr_token("t_1","Rename","(N/N)",-1)
nl2kr_token("t_2","data","N",-1)
nl2kr_token("t_3","Rename data","((S\\NP)\\((S\\NP)/NP))",-1)
nl2kr_token("t_4","Rename data","N",-1)
nl2kr_child_left("t_3","t_1")
nl2kr_child_left("t_4","t_1")
nl2kr_child_right("t_3","t_2")
nl2kr_child_right("t_4","t_2")
nl2kr_valid_rootNode("t_3")
nl2kr_valid_rootNode("t_4")
"""

dot_preamble = """digraph{ graph [ordering="out"];"""

class Node:
    def __init__(self):
        self.name = ""
        self.label =""
        self.grammar = ""
        self.left = ""
        self.right = ""

graph = {}
nodes = {}

def do_token(parameters):
    n = Node()
    n.name = parameters[0]
    n.label = parameters[1]
    n.grammar = parameters[2]
    
    graph[n.name] = n


def do_child_left(parameters):
    r = nodes[parameters[1]]
    r.left = parameters[0]

def do_child_right(parameters):
    r = nodes[parameters[1]]
    r.right = parameters[0]

def do_root(parameters):
    pass


def process(method, parameters):
    if(method == "nl2kr_token"):
        do_token(parameters)
    elif(method == "nl2kr_child_left"):
        do_child_left(parameters)
    elif(method == "nl2kr_child_right"):
        do_child_right(parameters)
    elif(method == "nl2kr_valid_rootNode"):
        do_root(parameters)
    else:
        print "Unknown method:", method


for line in s.split('\n'):
    i = line.find('(')
    method = line[:i]
    parameters = (line[i+1:-1]).split(',')
    process(method, parameters)
with open("graph.dot", "w") as f:
    f.write(dot_preamble)
    for c in nodes:
        f.write(nodes[c] + " -> " + c + "\n")

    f.write("}\n")

        
print graph
print nodes
