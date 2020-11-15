basemap = """
########
########
########
########
########
########
######&#
########

########
########
########
########
########
########
######&#
########

########
######0#
########
####%%##
###%&%##
########
########
########

########
######0#
########
####%%%#
###%&%%#
######%#
##%%%%%#
########

########
######0#
#####%##
###%####
###%####
#%#%##%#
#####%&#
########
"""
colmap = """
rrrrrrrr
r      r
r      r
r      r
r      r
r      r
r     gr
rrrrrrrr

rrrrrrrr
r r  r r
r r  r r
r r    r
r r  r r
r r  r r
r    rgr
rrrrrrrr

rrrrrrrr
r r   gr
r   rrrr
r rrRR r
r rRgR r
r rrrr r
r      r
rrrrrrrr

rrrrrrrr
r r   gr
r   rrrr
r rrRRRr
r rRgRRr
r rrrrRr
r RRRRRr
rrrrrrrr

rrrrrrrr
r r rrgr
r    R r
rr Rrr r
r  R   r
rR R  Rr
r    Rgr
rrrrrrrr
"""

basemap = basemap.replace("\n","")
colmap = colmap.replace("\n","")

basemapf = open("../bin/basemap.dat","w")
basemapf.write(basemap)
basemapf.close()

colmapf = open("../bin/colmap.dat","w")
colmapf.write(colmap)
colmapf.close()