# Marching-Cube
* Marching cube algorithm + making edited OFF file

## Input file
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
- Entire voxel size
- Number of voxel containing face(triangle)
- Sum/average of all face edgs
- Number of face
- Count of skinny triangle
- Ratio of skinny traingle / face
- Count of voxel containing skinny triangle
- Longest/shortest length of edge

## Output File
* face txt file(name : {step size}step_emd_{emd number}_face.txt)
  - Index set of vertex that construct face
* vertex txt file(name : {step size}step_emd_{emd number}_vertex.txt)
  - Vertex position
* default OFF File(name : {step size}step_emd_{emd number}.OFF)
  - Count of vertex, face, 0
  - Vertex position
  - Index set of vertex that construct face(not skinny triangle removed)
* Edited OFF file with skinny triangle information(name : V_{step size}step_emd_{emd number}.OFF)
  - Count of vertex, face, 0, number of voxel with polygon
  - Vertex position
  - Index set of vertex that construct face + boolean of skinny triangle
* Error information file(name : {step size}step_emd_{emd number}_ErrorInfo.txt)
  - Entire voxel size
  - Number of voxel containing face(triangle)
  - Sum/average of all face edgs
  - Number of face
  - Count of skinny triangle
  - Ratio of skinny traingle / face
  - Count of voxel containing skinny triangle
  - Longest/shortest length of edge
* Edge information files(name1 : {step size}step_emd_{emd number}_EdgePassCheck1.txt, name2 : {step size}step_emd_{emd number}_EdgePassCheck2.txt)
  - EdgePassCheck1 file : edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexIn Sum
  - EdgePassCheck2 file : edgePassBy2, edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexIn Sum

  * Component
    - edgepassBy2 : position of edges of voxel meeting the mesh by binary
    - edgepassNum : count of edges of voxel meeting the mesh
    - edgepassSum : calculate edgepassNum as binary depending on location
    - vertexInNum : count of vertices of voxel include in the mesh
    - vertexInSum : calculate vertexInNum as binary depending on location
    - b, c, h : positoin of voxel

## Reference
* [ACK 2021 Presentation](https://kiss.kstudy.com/Detail/Ar?key=3921316)
* [Paper](https://www.riss.kr/search/detail/DetailView.do?p_mat_type=be54d9b8bc7cdb09&control_no=8450137f0651b5caffe0bdc3ef48d419&keyword=)
