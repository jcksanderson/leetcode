class Solution:
    def findCenter(self, edges: List[List[int]]) -> int:
      edge_count = [0] * (len(edges) + 1)
      for node_1, node_2 in edges:
        edge_count[node_1 - 1] += 1
        edge_count[node_2 - 1] += 1
      return edge_count.index(max(edge_count)) + 1
