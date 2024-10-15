#include "Graph.h"
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Graph::Graph(const char* const & edgelist_csv_fn) {
    ifstream file(edgelist_csv_fn);
    string line;
    int index = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string u_label, v_label, weight;
        getline(ss, u_label, ',');
        getline(ss, v_label, ',');
        getline(ss, weight, '\n');
        
        edges.emplace_back(u_label, v_label, stod(weight));
        
        nodes_set.insert(u_label);
        nodes_set.insert(v_label);

        if (node_indices.count(u_label) == 0) {
          node_indices[u_label] = index++;  
        }
        if (node_indices.count(v_label) == 0) {
          node_indices[v_label] = index++;  
        }
    }
    file.close();
}

unsigned int Graph::num_nodes() {
    return nodes_set.size();
}

vector<string> Graph::nodes() {
    vector<string> nodes;
    for (const auto& node : nodes_set) {
        nodes.push_back(node);
    }
    return nodes;
}

unsigned int Graph::num_edges() {
    return edges.size();
}

unsigned int Graph::num_neighbors(string const & node_label) {
    unsigned int count = 0;
    for (const auto& edge : edges) {
        if (get<0>(edge) == node_label || get<1>(edge) == node_label) {
            count++;
        }
    }
    return count;
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
     for (const auto& edge : edges) {
        if ((get<0>(edge) == u_label && get<1>(edge) == v_label) ||
            (get<0>(edge) == v_label && get<1>(edge) == u_label)) {
            return get<2>(edge);
        }
    }
    return -1;
}

vector<string> Graph::neighbors(string const & node_label) {
    vector<string> neighbor_labels;
    for (const auto& edge : edges) {
        if (get<0>(edge) == node_label) {
            neighbor_labels.push_back(get<1>(edge));
        } else if (get<1>(edge) == node_label) {
            neighbor_labels.push_back(get<0>(edge));
        }
    }
    return neighbor_labels;
}

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    vector<string> path;
    if (start_label == end_label) {
        path.push_back(start_label);
        return path;
    }

    // Store parent of nodes in <parent, child> pair
    unordered_map<string, string> parent;
    queue<string> queue;
    unordered_set<string> visited;

    queue.push(start_label);
    visited.insert(start_label);

    while (!queue.empty()) {
        string curr = queue.front();
        queue.pop();

        vector<string> neighbors_list = neighbors(curr);
        for (const auto& neighbor : neighbors_list) {
            // If not visited
            if (visited.find(neighbor) == visited.end()) {
                queue.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = curr;
                if (neighbor == end_label) {
                    // Found the end node, construct the path
                    string node = neighbor;
                    while (node != start_label) {
                        path.push_back(node);
                        node = parent[node];
                    }
                    path.push_back(start_label);
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    return path;
}

vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    vector<tuple<string, string, double>> path;
    if (start_label == end_label) {
        path.emplace_back(start_label, start_label, -1);
        return path;
    }

    unordered_map<string, string> parent;
    unordered_map<string, double> distances;
    // greater is in <functional> header
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    unordered_set<string> visited;

    pq.push(pair<double, string>(0, start_label));
    distances[start_label] = 0;

    while (!pq.empty()) {
        string current_node = pq.top().second;
        pq.pop();

        if (visited.find(current_node) != visited.end()) {
            continue;
        }
        visited.insert(current_node);

        vector<string> neighbors_list = neighbors(current_node);
        for (const auto& neighbor : neighbors_list) {
            double weight = edge_weight(current_node, neighbor);
            double distance = distances[current_node] + weight;
            if (distances.find(neighbor) == distances.end() || distance < distances[neighbor]) {
                distances[neighbor] = distance;
                parent[neighbor] = current_node;
                pq.push(make_pair(distance, neighbor));
            }
        }
    }

    if (parent.find(end_label) == parent.end()) {
        return path;  // No path found
    }

    string node = end_label;
    while (node != start_label) {
        string parent_node = parent[node];
        double weight = edge_weight(parent_node, node);
        path.emplace_back(parent_node, node, weight);
        node = parent_node;
    }
    reverse(path.begin(), path.end());

    return path;
}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    vector<vector<string>> components;
    unordered_set<string> remaining_nodes = nodes_set;

    while (!remaining_nodes.empty()) {
        string start_node = *(remaining_nodes.begin());
        vector<string> component;
        queue<string> queue;

        queue.push(start_node);
        remaining_nodes.erase(start_node);
        component.push_back(start_node);

        while (!queue.empty()) {
            string curr = queue.front();
            queue.pop();

            vector<string> neighbors_list = neighbors(curr);
            for (const auto& neighbor : neighbors_list) {
                if (remaining_nodes.find(neighbor) != remaining_nodes.end()) {
                    double weight = edge_weight(curr, neighbor);
                    if (weight <= threshold) {
                        queue.push(neighbor);
                        remaining_nodes.erase(neighbor);
                        component.push_back(neighbor);
                    }
                }
            }
        }

        components.push_back(component);
    }

    return components;
}

double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
    if (start_label == end_label) {
        return 0;
    }
    // initialize a disjoint set containing all nodes in the graph
    DisjointSet ds(num_nodes());

    // Sort the edges in increasing order of weight
    vector<tuple<double, int, int>> sorted_edges;
    for (const auto& edge : edges) {
        int u = node_indices[get<0>(edge)];
        int v = node_indices[get<1>(edge)];
        double weight = get<2>(edge);
        sorted_edges.emplace_back(weight, u, v);
    }
    sort(sorted_edges.begin(), sorted_edges.end());

    // Process the edges and perform union-find
    for (const auto& edge : sorted_edges) {
        double weight = get<0>(edge);
        int u = get<1>(edge);
        int v = get<2>(edge);
        ds.unionSets(u, v);

        // Check if start_label and end_label are now in the same set
        int start_idx = node_indices[start_label];
        int end_idx = node_indices[end_label];
        if (ds.find(start_idx) == ds.find(end_idx)) {
            return weight;
        }
    }

    return -1;  // No path found
}
