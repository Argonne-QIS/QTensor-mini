Tensor = namedtuple('Tensor', ['indices', 'data'])
HyperGraph = namedtuple('HyperGraph', ['edge_to_nodes',  'node_to_edges']) # 

def contract_tensor_bucket(idx, tensors):
    pass

def bucket_elimination(hgraph, order, tensor_data):
    for i, node in enumerate(order):
        edges = hgraph.node_to_edges[node]
        # bucket = [Tensor(hgraph.edge_to_nodes[edge], tensor_data[edge]) for edge in edges]
        # contract_tensor_bucket(node, bucket)
        neighbors = set()

        for edge in edges:
            neighbors |= hgraph.edge_to_nodes[edge]

        for neighbor in neighbors:
            neighbor_edges = hgraph.node_to_edges[neighbor]
            neighbor_edges -= edges
            neihbors_edges.add(all_neighbors)

