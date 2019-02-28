import networkx as nx
import itertools
import matplotlib.pyplot as plt
import shapely.geometry as spgeom
import shapely.affinity as spaffn
import numpy as np

class ResGraph():

    def __init__(self, elec_dict, elec_list, dir):
        self.g = nx.Graph()
        self.elec_dict = elec_dict
        self.elec_list = elec_list
        self.dir = dir
        self.z_bounds = []
        self.edge_ind = 0
        self.node_ind = 0
        self.setZMaxes()

        self.buildGraph()

        self.debugPrint()

    def setZMaxes(self):
        self.z_bounds.append(min(elec.z1 for elec in self.elec_list))
        self.z_bounds.append(max(elec.z2 for elec in self.elec_list))
        # print(self.z_bounds)

    def addFromOverlap(self, pair):
        a, b = pair

        #For the objects to form a node, either:
        # overlap in xy AND touch on z (vertical junction),  OR
        # overlap in z AND touch on xy (horizontal junction).

        box_a = spgeom.box(a.x1, a.y1, a.x2, a.y2)
        box_b = spgeom.box(b.x1, b.y1, b.x2, b.y2)
        # clockwise is -, counterclockwise is +, but the vertical axis in SiQAD is flipped.
        # Therefore, clockwise rotation on SiQAD GUI is +.
        box_a = spaffn.rotate(box_a, a.angle)
        box_b = spaffn.rotate(box_b, b.angle)
        line_a_z = spgeom.LineString([(a.z1,0),(a.z2,0)])
        line_b_z = spgeom.LineString([(b.z1,0),(b.z2,0)])

        # print("pair: ", a.id, b.id)
        # print("Box intersect: ",box_a.intersects(box_b))
        # print("Z touch", line_a_z.touches(line_b_z))
        #
        # print("Box touch",box_a.touches(box_b))
        # print("Z intersect",line_a_z.intersects(line_b_z))
        #
        #
        # print(box_a)
        # print(box_b)

        #Overlap exists between electrodes, this pair is connected.
        #Find which coordinate overlaps, ignore rotated ones for now.
        if (box_a.intersects(box_b) and line_a_z.touches(line_b_z)) or \
           (box_a.touches(box_b) and line_a_z.intersects(line_b_z)):

            # no rotation allowed for anything except vertical junctions
            #y and z coordinates form the intersection
            print("overlap!")
            if a.x1 == b.x2:
                box_a = spgeom.box(a.y1, a.z1, a.y2, a.z2)
                box_b = spgeom.box(b.y1, b.z1, b.y2, b.z2)
                inter = box_a.intersection(box_b)
                pos = [a.x1, inter.centroid.x, inter.centroid.y]
            if a.x2 == b.x1:
                box_a = spgeom.box(a.y1, a.z1, a.y2, a.z2)
                box_b = spgeom.box(b.y1, b.z1, b.y2, b.z2)
                inter = box_a.intersection(box_b)
                pos = [a.x2, inter.centroid.x, inter.centroid.y]

            # x and z coordinates form the intersection
            if a.y1 == b.y2:
                box_a = spgeom.box(a.x1, a.z1, a.x2, a.z2)
                box_b = spgeom.box(b.x1, b.z1, b.x2, b.z2)
                inter = box_a.intersection(box_b)
                pos = [inter.centroid.x, a.y1, inter.centroid.y]
            if a.y2 == b.y1:
                box_a = spgeom.box(a.x1, a.z1, a.x2, a.z2)
                box_b = spgeom.box(b.x1, b.z1, b.x2, b.z2)
                inter = box_a.intersection(box_b)
                pos = [inter.centroid.x, a.y2, inter.centroid.y]

            #x and y coordinates form the intersection
            #only allow rotation in the xy plane.
            if a.z1 == b.z2:
                box_a = spgeom.box(a.x1, a.y1, a.x2, a.y2)
                box_b = spgeom.box(b.x1, b.y1, b.x2, b.y2)
                box_a = spaffn.rotate(box_a, a.angle, origin='centroid')
                box_b = spaffn.rotate(box_b, b.angle, origin='centroid')
                inter = box_a.intersection(box_b)
                pos = [inter.centroid.x, inter.centroid.x, a.z1]
            if a.z2 == b.z1:
                box_a = spgeom.box(a.x1, a.y1, a.x2, a.y2)
                box_b = spgeom.box(b.x1, b.y1, b.x2, b.y2)
                box_a = spaffn.rotate(box_a, a.angle, origin='centroid')
                box_b = spaffn.rotate(box_b, b.angle, origin='centroid')
                inter = box_a.intersection(box_b)
                pos = [inter.centroid.x, inter.centroid.x, a.z2]
            includes = [a.id, b.id]
            curr_node = self.addNode(pos=pos, includes=includes)

    # Add in the nodes that connect to the ceiling
    def addCeilingNodes(self, net_elec):
        ceil_nodes = []
        for item in net_elec:
            #check if electrode connects to the ceiling
            if item.z2 == self.z_bounds[1]:
                #find the center of the intersection (in x and y)
                box = spgeom.box(item.x1, item.y1, item.x2, item.y2)
                center = box.centroid
                #add its center
                curr_node = self.addNode(pos=[center.x, center.y,item.z2], includes=[item.id])
                ceil_nodes.append(curr_node)
        return ceil_nodes

    def addFloorNodes(self, net_elec):
        floor_nodes = []
        for item in net_elec:
            #check if electrode connects to the floor
            if item.z1 == self.z_bounds[0]:
                #find the center of the intersection (in x and y)
                box = spgeom.box(item.x1, item.y1, item.x2, item.y2)
                center = box.centroid
                #add its center
                curr_node = self.addNode(pos=[center.x, center.y,item.z1], includes=[item.id])
                floor_nodes.append(curr_node)
        return floor_nodes

    # Adds an edge to the graph between two nodes a and b, where a and b are node keys.
    def addEdge(self, a, b, **kwargs):
        print("Connecting ", a, b)
        self.g.add_edge(a, b, **kwargs)

    # Adds a node to the graph at with a specified key. If no key is specified, the internal node index is used and incremented.
    def addNode(self, key=None, **kwargs):
        if key == None:
            key = self.node_ind
            self.node_ind += 1
        self.g.add_node(key, **kwargs)
        return key

    #nodes defined by electrode intersections
    def buildNodes(self, key):
        # Create all possible pair combinations of electrodes within a net
        pairs = itertools.combinations(self.elec_dict[key], 2)
        # Check for overlap
        for pair in pairs:
            self.addFromOverlap(pair)

    #gets the nodes that the electrode with a given id is involved with
    def getRelevantNodes(self, id):
        relevant_nodes = []
        for node in self.g.nodes(data='includes'):
            if node[1] != None and id in node[1]:
                relevant_nodes.append(node[0])
        return relevant_nodes

    def getDistanceDict(self, subgraph, rel_nodes):
        node_pos = subgraph.nodes(data='pos')
        pairs = [x for x in itertools.combinations(rel_nodes, 2) ]
        distances = []

        for pair in pairs:
            a, b = pair
            point_a = np.array(node_pos[a])
            point_b = np.array(node_pos[b])
            #Get the distance between node positions
            distances.append(np.linalg.norm(point_a - point_b))
        return dict(zip(pairs, distances))

    # Connect nodes based on distance.
    def connectSubgraph(self, sg, dist_dict):
        #sort the pairs based on their distances
        sorted_pairs = sorted(dist_dict, key=lambda x: (dist_dict[x]))
        #Number of connections that need to be made
        num_conn = len(sg.nodes()) - 1
        #Number of connections made
        curr_conn = 0
        for pair in sorted_pairs:
            #if a path exists between these two nodes on the main graph, try next pair
            if nx.has_path(self.g, pair[0],pair[1]):
                continue
            #skip if nodes are connected in subgraph, want UNIQUE paths.
            if nx.has_path(sg, pair[0], pair[1]):
                continue
            #no path exists between this pair of closest nodes.
            #create the connection in the subgraph
            a, b = pair
            sg.add_edge(a, b)
            print("Connecting ", a, b)

            #take note of how many connections we've made
            curr_conn += 1
            # break once we've made the required amount of connections in the subgraph
            if curr_conn == num_conn:
                break

        #merge the current graph (previous connections) with the subgraph (new connections)
        self.g = nx.compose(self.g, sg)

    #edges are defined by the electrode geometries
    def buildEdges(self):
        #sort the list of electrodes from highest to lowest.
        sorted_elec_list = sorted(self.elec_list, key=lambda x: (x.z2), reverse=True)
        #start from the top (geometrically)
        for item in sorted_elec_list:
            rel_nodes = self.getRelevantNodes(item.id)
            sg = self.g.subgraph(rel_nodes).copy()
            dist_dict = self.getDistanceDict(sg, rel_nodes)
            print("Working on electrode", item.id)
            self.connectSubgraph(sg, dist_dict)

    def buildGraph(self):
        self.g = nx.Graph()

        self.addNode("ceiling")
        self.addNode("floor")

        #Once per net, build from top down.
        for key in self.elec_dict.dict:
            #identify the electrodes that have the highest height.
            ceil_nodes = self.addCeilingNodes(self.elec_dict[key])
            #identify the electrodes that have the lowest height.
            floor_nodes = self.addFloorNodes(self.elec_dict[key])
            #Connect the ceiling nodes to ceiling
            for node in ceil_nodes:
                self.addEdge(node,"ceiling")
            #build intermediate nodes
            self.buildNodes(key)
            print(self.g.nodes())
            self.buildEdges()
            #Connect the floor nodes to floor
            for node in floor_nodes:
                self.addEdge(node,"floor")

        self.exportGraph()

    def exportGraph(self):
        plt.figure()
        nx.draw(self.g, with_labels=True)
        plt.savefig(self.dir+"/graph.pdf", bbox_inches='tight')

    def debugPrint(self):
        print(list(self.g.nodes(data=True)))

# if __name__ == "__main__":
#     pass
