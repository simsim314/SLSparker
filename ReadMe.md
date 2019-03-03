SLSparker is an application which searches for target spark, placing 53 most common ash objects (more common than eater) inside rectangular range iterativelly. Shooting glider from constant position, and checks for the target each generation. 

Based on LifeAPI and uses openmp. 

You need an input file with definitions of the format (see also p22.in file): 

max-gen 100  
sl1-range -10, -10, 20, 20  
sl2-range -10, -10, 20, 20  

target-rle 2bo$b3o$ob3o$o2b3o$b4o$2b2o!  
target-rle 2b2o$b4o$3o2bo$b3obo$2b3o$3bo!  

two-only
top-range -10, -10, 20, 1  
top-rle 2o$2o!  

report-top 100
max-result 10000

--------------

Eplanation: 

- Searches for multiple targets defined with target-rle prefix. 
- If top-rle is not defined, the search uses list of all 53 SLs options. 
- The glider is always shot from the same place (x, x) and the SLs are iterativelly moved inside the range. 
- top-range height must be 1, otherwise the search will repeat the same option. 
- The default of sls ranges is (-10, -7, 20, 7) and top range (-10, -8, 20, 1)
- The delimeter is space. 
- You must include at least one target-rle. 


### max-gen: 
Every soup will search for the target up to max gen. 

### sl1-range, sl2-range: 
A range (minx, miny, width, height) for SL 

### target-rle
The rle of the target to be located anywhere inside the soup. 

### top-rle
If you have some predefind SL configuration that can increase the chances, use it. Otherwise just don't use it al all. 
If you just want 2SLs search instead of 3, use block and place it in the corner. 

### two-only
Two only will use only two SLs and will ignore anything regarding the top.

### max-result
Will search until the number of results has reached max-result value. If you don't need all the results and you have already what you want in 100 search results, and you don't need all the million other results. 

### report-top
Will report only partial result which were with minimal population at the moment of location of the spark. 


	
