from py2neo import Graph
from py2neo import NodeMatcher, RelationshipMatcher

my_graph = Graph(password='neo4j-ADP1')

nodes = NodeMatcher(my_graph)

nm = nodes.match("Person").where("_.born > 1960").all()

file=open("personas_1960.txt", "w")
c=1

for i in nm:
	file.write(str(c)+"- "+i["name"]+", "+str(i["born"])+"\n")
	c+=1

file.close()