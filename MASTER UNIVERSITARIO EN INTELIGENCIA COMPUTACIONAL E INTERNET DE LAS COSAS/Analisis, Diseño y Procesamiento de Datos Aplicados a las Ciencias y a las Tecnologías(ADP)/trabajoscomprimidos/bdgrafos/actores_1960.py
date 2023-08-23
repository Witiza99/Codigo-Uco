from py2neo import Graph
from py2neo import NodeMatcher, RelationshipMatcher
from py2neo import Node

my_graph = Graph(password='neo4j-ADP1')

relations=RelationshipMatcher(my_graph)
rm=relations.match(None,r_type="ACTED_IN" ).where("a.born > 1960").all()

file=open("actores_1960.txt", "w")
c=1

s=set(rm)

for i in s:
	file.write(str(c)+"- "+i.start_node["name"]+": "+str(i.start_node["born"])+"\n")
	c+=1

file.close()