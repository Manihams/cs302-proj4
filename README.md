Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]


Table:

| N     | Elapsed Time (s)   | Memory Usage (KB)  |
|-------|--------------------|--------------------|
| 10    | 0.0000             | 3345               |
| 20    | 0.0000             | 3380               |
| 50    | 0.0000             | 3331               |
| 100   | 0.0000             | 3463               |
| 200   | 0.0300             | 3904               |
| 500   | 0.2480             | 6550               |
| 1000  | 1.0400             | 15956              |

