from py2neo import Graph
from py2neo import NodeMatcher, RelationshipMatcher

my_graph = Graph(password='neo4j-ADP1')


relations=RelationshipMatcher(my_graph)
rm=relations.match(None, r_type="ACTED_IN")

file=open("actores.txt", "w")
c=1

s=set(rm)

for i in s:
	file.write(str(c)+"- "+i.start_node["name"]+"\n")
	c+=1

file.close()