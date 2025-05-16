# Required imports
import numpy as np
import networkx as nx
from Boundaries import Boundaries
from Map import EPSILON

# Number of nodes expanded in the heuristic search (stored in a global variable to be updated from the heuristic functions)
NODES_EXPANDED = 0

def h1(current_node, objective_node) -> np.float32:
    """ First heuristic to implement """
    global NODES_EXPANDED
    NODES_EXPANDED += 1

    x1, y1 = current_node
    x2, y2 = objective_node

    manhattan_distance = abs(x1 - x2) + abs(y1 - y2)
    return manhattan_distance * EPSILON

def h2(current_node, objective_node) -> np.float32:
    """ Second heuristic to implement """
    global NODES_EXPANDED
    NODES_EXPANDED += 1

    x1, y1 = current_node
    x2, y2 = objective_node

    euclidean_distance = np.sqrt((x1 - x2)**2 + (y1 - y2)**2)
    return euclidean_distance * EPSILON

def build_graph(detection_map: np.array, tolerance: np.float32) -> nx.DiGraph:
    """Construye un grafo dirigido a partir del mapa de detección, aplicando la tolerancia"""
    height, width = detection_map.shape
    G = nx.DiGraph()

    # Direcciones posibles: arriba, abajo, izquierda, derecha
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    for i in range(height):
        for j in range(width):
            current_node = (i, j)
            current_value = detection_map[i, j]

            # Solo agregamos nodos si su valor está dentro del umbral
            if current_value <= tolerance:
                G.add_node(current_node)

                for dx, dy in directions:
                    ni, nj = i + dx, j + dy
                    # Verificamos si el vecino está dentro de los límites del mapa
                    if 0 <= ni < height and 0 <= nj < width:
                        neighbor_value = detection_map[ni, nj]

                        # Solo conectamos si la celda vecina también está dentro del umbral
                        if neighbor_value <= tolerance:
                            neighbor_node = (ni, nj)
                            # El coste de la arista es el valor de la celda destino
                            G.add_edge(current_node, neighbor_node, weight=neighbor_value)

    return G

def discretize_coords(high_level_plan: np.array, boundaries: Boundaries, map_width: np.int32, map_height: np.int32) -> np.array:
    """Convierte coordenadas geodésicas (lat, lon) en coordenadas discretas (i, j) de la malla"""

    # Crear los rangos discretos de latitudes y longitudes
    lat_range = np.linspace(boundaries.min_lat, boundaries.max_lat, map_height)
    lon_range = np.linspace(boundaries.min_lon, boundaries.max_lon, map_width)

    # Inicializamos la matriz de salida
    discretized_plan = np.zeros_like(high_level_plan, dtype=np.int32)

    for idx, (lat, lon) in enumerate(high_level_plan):
        # Buscar el índice más cercano a la latitud y longitud
        i = np.searchsorted(lat_range, lat) - 1
        j = np.searchsorted(lon_range, lon) - 1

        # Limitar dentro de los márgenes de la malla
        i = min(max(i, 0), map_height - 1)
        j = min(max(j, 0), map_width - 1)

        discretized_plan[idx] = [i, j]

    return discretized_plan

def path_finding(G: nx.DiGraph,
                 heuristic_function,
                 locations: np.array,
                 initial_location_index: np.int32,
                 boundaries: Boundaries,
                 map_width: np.int32,
                 map_height: np.int32) -> tuple:
    """Planifica una ruta completa entre los puntos de interés dados usando A*"""

    global NODES_EXPANDED
    NODES_EXPANDED = 0  # Reiniciamos el contador

    solution_plan = []

    # Visitamos los POIs en el orden dado, comenzando en el índice inicial
    for i in range(initial_location_index, len(locations) - 1):
        start = tuple(locations[i])
        end   = tuple(locations[i + 1])

        try:
            partial_path = nx.astar_path(G, source=start, target=end, heuristic=heuristic_function, weight='weight')
            # Guardamos como lista de strings (opcional para facilitar visualización posterior)
            path_as_str = [str(p) for p in partial_path]
            solution_plan.append(path_as_str)
        except nx.NetworkXNoPath:
            print(f"No hay camino entre {start} y {end}.")
            continue

    return solution_plan, NODES_EXPANDED

def compute_path_cost(G: nx.DiGraph, solution_plan: list) -> np.float32:
    """Calcula el coste total del plan de vuelo completo sumando los pesos de las aristas"""
    total_cost = 0.0

    for path in solution_plan:
        for i in range(len(path) - 1):
            u = eval(path[i])     # nodo origen como tupla
            v = eval(path[i + 1]) # nodo destino como tupla
            edge_weight = G[u][v]['weight']
            total_cost += edge_weight

    return total_cost