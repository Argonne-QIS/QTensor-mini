from collections import namedtuple
from copy import deepcopy

Tensor = namedtuple('Tensor', ['indices', 'data'])

BipartiteGraph = namedtuple('BipartiteGraph', ['left_to_right', 'right_to_left'])

def flip(bipartite):
    """
    TODO
    """
    return Bipartite(bipartite.right_to_left, bipartite.left_to_right)

def transpose_tensor(tensor, new_tensor_idx):
    pass

def new_indices(first_idx, shared_indices, tensor_indices):
    pass

def get_shared_indices(tensors, bucket):
    shared_indices = set(tensors[bucket[0]].indices)
    for tensor_id in bucket[1:]:
        acc -= set(tensors[tensor_id].indices)
    return shared_indices

def merge_with_result(result_data, result_indices, tensor):# Replace these with the simplified bucket method
    # ---- Prepare inputs: transpose + reshape
    ixa, ixb = result_indices, tensor.indices
    common_ids = sorted(list(set.intersection(set(ixa), set(ixb))), key=int)
    distinct_a = [x for x in ixa if x not in common_ids]
    distinct_b = [x for x in ixb if x not in common_ids]
    transp_a = [ixa.index(x) for x in common_ids+distinct_a]
    transp_b = [ixb.index(x) for x in common_ids+distinct_b]
    a = result_data.transpose(transp_a)
    b = tensor.data.transpose(transp_b)
    n, m, k = 2**len(common_ids), 2**len(distinct_a), 2**len(distinct_b)
    a = a.reshape(n, m)
    b = b.reshape(n, k)
    # ----

    c = np.empty((n, m, k), dtype=np.complex128)
    tcontract.mkl_contract_complex(a, b, c)

    # ---- Post-process output
    result_indices = tuple(sorted(
        set(result_indices + tensor.indices),
        key=int)
    )
    ixc = common_ids + distinct_a + distinct_b
    assert len(result_indices) == len(ixc), 'Wrong transposition, please submit an issue'
    transp_c = [ixc.index(x) for x in result_indices]
    result_data = c.reshape(*[2 for _ in result_indices])
    result_data = result_data.transpose(transp_c)
    return result_data, result_indices
    # ----

def process_bucket(self, bucket, no_sum=False): # Replace these with the simplified bucket method
    result_indices = bucket[0].indices
    result_data = bucket[0].data

    # -- Contract first n-1 bucketns
    for tensor in bucket[1:-1]:
        result_data, result_indices = merge_with_result(result_data, result_indices, tensor)
    # --


    if len(result_indices) > 0:
        tag = result_indices[0].identity
    else:
        tag = 'f'

    if no_sum:
        if len(bucket)>1:
            last_tensor = bucket[-1]
            result_data, result_indices = merge_with_result(result_data, result_indices, last_tensor)

        result = opt.Tensor(f'E{tag}', result_indices,
                            data=result_data)
        return result

    if len(bucket)<2:
        result = opt.Tensor(f'E{tag}', result_indices[1:],
                            data=np.sum(result_data, axis=0))
        return result
    last_tensor = bucket[-1]

    # -- Contract with summation
    ixa, ixb = result_indices, last_tensor.indices
    # ---- Prepare inputs: transpose + reshape
    k, fm = result_indices[:1], result_indices[1:]
    fn = last_tensor.indices[1:]

    f = tuple(sorted(list(set.intersection(set(fm), set(fn))), key=int))
    # Sets don't store order, so use lists. Do we need order here?
    m = tuple([x for x in fm if x not in f])
    n = tuple([x for x in fn if x not in f])
    transp_a = [ixa.index(x) for x in k+f+m]
    transp_b = [ixb.index(x) for x in k+f+n]
    a = result_data.transpose(transp_a)
    b = last_tensor.data.transpose(transp_b)
    shapes_a = {i:s for i,s in zip(k+f+m, a.shape)}
    shapes_b = {i:s for i,s in zip(k+f+n, b.shape)}
    shapes = {**shapes_b, **shapes_a}
    K, F, M, N = [reduce(np.multiply, (shapes[i] for i in x), 1) for x in (k, f, m, n)]
    a = a.reshape(K, F, M)
    b = b.reshape(K, F, N)
    # ----

    # \sum_k A_{kfm} * B_{kfn} = C_{fmn}
    c = np.empty((F, M, N), dtype=np.complex128)
    tcontract.mkl_contract_sum(a, b, c)

    # ---- Post-process output
    result_indices = tuple(sorted(
        set(result_indices + last_tensor.indices),
        key=int)
    )
    assert result_indices[0] == k[0], 'Broken ordering, please report'
    result_indices = result_indices[1:]
    ixc = f + m + n
    assert len(result_indices) == len(ixc), 'Wrong transposition, please submit an issue'
    result_data = c.reshape([shapes[i] for i in ixc])
    transp_c = [ixc.index(x) for x in result_indices]
    result_data = result_data.transpose(transp_c)
    # ----
    # --
    result = opt.Tensor(f'E{tag}', result_indices, data=result_data)
    return result


def contract_tensor_bucket(tensors, idx, bucket):
    shared_indices = get_shared_indices(tensors, bucket)
    for tensor_id in bucket:
        tensor = tensors[tensor_id]
        new_indices(idx, shared_indices, tensor.indices)
        transpose_tensor(tensor, new_indices)
    

def bucket_elimination(hgraph, order, tensor_data):
    next_edge = max(hgraph.edge_to_nodes.keys()) # TODO Maybe replace this with an actual naming rule later?
    print(next_edge)
    for i, node in enumerate(order):
        print(f"Contract node {node}")
        print(f"{hgraph}")
        print("\n\n")
        edges = hgraph.node_to_edges[node]
        # bucket = [Tensor(hgraph.edge_to_nodes[edge], tensor_data[edge]) for edge in edges]
        # contract_tensor_bucket(node, bucket)
        neighbors = set()

        for edge in edges:
            neighbors |= hgraph.edge_to_nodes[edge]
            del(hgraph.edge_to_nodes[edge])

        for neighbor in neighbors:
            neighbor_edges = hgraph.node_to_edges[neighbor]
            neighbor_edges -= edges
            neighbor_edges.add(next_edge)

        hgraph.edge_to_nodes[next_edge] = neighbors
        next_edge += 1
        del(hgraph.node_to_edges[node])

