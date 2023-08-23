# Ejercicio 3
# A simple query.
# Supone la contraseña de la BDD es 'neo4j-ADP1'

from py2neo import Graph
from py2neo import Node, Relationship

my_graph = Graph(password='neo4j-ADP1')
keanu = my_graph.nodes.match("Person", name="Keanu Reeves").first()
print(keanu)
print("personas {}".format(len(my_graph.nodes.match("Person"))))

ca=my_graph.nodes.match(title="The Matrix").first()
print(ca)

for i in my_graph.nodes.match("Person").limit(10).all():
    print(i)
