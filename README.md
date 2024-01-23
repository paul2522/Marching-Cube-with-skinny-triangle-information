# Marching-Cube-RST
* Marching cube algorithm + Remove Skinny Triangle
  
## Requirement file
* EMDB density file(sit : pdb to xyz)
  - Resoultion change applied
  - Format : (num)step_emd_(EMDB_Number).sit
    * num : 1 ~ 9
  
## Input
* EMDB number
* EMDB specific contour_level
* Skinny triangle length threshold
  - Average length of edges on all triangles divided by 100
  
## Output
* OFF file with skinny triangle removed
  - Count of vertex, face
  - Vertex position
  - Index set of vertex that construct face
* Error information file
  - Entire voxel size
  - Number of voxel containing face(triangle)
  - Sum/average of all face edgs
  - Number of face
  - Count of skinny triangle
  - Ratio of skinny traingle / face
  - Count of voxel containing skinny triangle
  - Longest/shortest length of edge
* Edge information file
  - edgepassNum : count of edges of voxel meeting the mesh
  - edgepassSum : calculate edgepassNum as binary depending on location
  - vertexInNum : count of vertices of voxel include in the mesh
  - vertexInSum : calculate vertexInNum as binary depending on location
  - b, c, h : positoin of voxel

## Reference
* [한국정보처리학회 ACK2021(추계학술발표대회)](https://kiss.kstudy.com/Detail/Ar?key=3921316)
